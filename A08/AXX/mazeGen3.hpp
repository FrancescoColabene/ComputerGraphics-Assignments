enum Angles {TL = 1, TR = 2, BL = 3, BR = 4};

// class used to create a matrix with more information about the maze
class SQUARE {
public:
	SQUARE() {}
	int block = 0;
	// presence of a vertex in the said direction
	bool topLeft = false;
	bool topRight = false;
	bool botLeft = false;
	bool botRight = false;
	// indexes of the vertices: assigned in a later cycle, -1 implies no vertex
	int iTopLeft = -1;
	int iTopRight = -1;
	int iBotLeft = -1;
	int iBotRight = -1;
	
	// functions used to invert the value of a vertex
	void invertTopLeft() { topLeft = !topLeft; }
	void invertTopRight() { topRight = !topRight; }
	void invertBotLeft() { botLeft = !botLeft; }
	void invertBotRight() { botRight = !botRight; }
	
	void setTrue()
	{
		topLeft = true;
		topRight = true;
		botLeft = true;
		botRight = true;
	}

	// check if the square has a vertex in one of the directions
	bool hasTop() { return topLeft || topRight; }
	bool hasBot() { return botLeft || botRight; }
	bool hasLeft() { return topLeft || botLeft; }
	bool hasRight() { return topRight || botRight; }

	// check if the square has a vertex by checking the indexes 
	bool hasITop() { return iTopLeft != -1 || iTopRight != -1; }
	bool hasIBot() { return iBotLeft != -1 || iBotRight != -1; }
	bool hasILeft() { return iTopLeft != -1 || iBotLeft != -1; }
	bool hasIRight() { return iTopRight != -1 || iBotRight != -1; }

	// check if a block has at least one top and one bot vertex
	bool canStartRow() {
		return (hasTop() && hasBot());
	}
	// check if a block has at least one left and one right vertex
	bool canStartCol() {
		return (hasLeft() && hasRight());
	}
};

// Create a pair of vertices at a certain coordinate, higher up first
void createVerticalVertixes(int z, int x, std::vector<float>& vPos) {
	vPos.push_back(x); vPos.push_back(1.0); vPos.push_back(z);
	vPos.push_back(x); vPos.push_back(0.0); vPos.push_back(z);
}

// Function used to invert vertices if there are adjacent blocks; this algorithm creates a good situation at the end
// If a block contains a vertex, it's always 2 vertices (because of the way the maze is built)
void handleVertixes(SQUARE** sMaze, int r, int rmax, int c, int cmax)
{
	// Only one of the changes is done because I add one block at a time, the order doesn't matter
	// change top adjacent block
	if (r > 0 && sMaze[r - 1][c].block != 0) {
		sMaze[r][c].invertTopLeft(); sMaze[r][c].invertTopRight();
		sMaze[r - 1][c].invertBotLeft(); sMaze[r - 1][c].invertBotRight();
	} else 
	// change bot adjacent block
	if (r < (rmax - 1) && sMaze[r + 1][c].block != 0) {
		sMaze[r][c].invertBotLeft(); sMaze[r][c].invertBotRight();
		sMaze[r + 1][c].invertTopLeft(); sMaze[r + 1][c].invertTopRight();
	} else
	// change left adjacent block
	if (c > 0 && sMaze[r][c - 1].block != 0) {
		sMaze[r][c].invertTopLeft(); sMaze[r][c].invertBotLeft();
		sMaze[r][c - 1].invertTopRight(); sMaze[r][c - 1].invertBotRight();
	}
	// change right adjacent block
	else
	if (c < (cmax - 1) && sMaze[r][c + 1].block != 0) {
		sMaze[r][c].invertTopRight(); sMaze[r][c].invertBotRight();
		sMaze[r][c + 1].invertTopLeft(); sMaze[r][c + 1].invertBotLeft();
	}
}

// Creates the vertices based on the given SQUARE values
// After creating a pair of vertices it assign to adjacent blocks, if they are walls, the indexes of the vertices
void instantiateVertixes(SQUARE** sMaze, int r, int rmax, int c, int cmax, int &index, std::vector<float>& vPos)
{
	/*
	memo
	
	left  -> c = c
	right -> c = c + 1
	top   -> r = r
	bot   -> r = r + 1
	*/ 

	// TopLeft
	if (sMaze[r][c].topLeft) {
		createVerticalVertixes(r, c, vPos);
		sMaze[r][c].iTopLeft = index;
		// check top
		if (r > 0 && sMaze[r - 1][c].block != 0) 
			sMaze[r - 1][c].iBotLeft = index;
		// check left
		if (c > 0 && sMaze[r][c - 1].block != 0) 
			sMaze[r][c - 1].iTopRight = index;
		// check diagonal
		if (c > 0 && r > 0 && sMaze[r - 1][c - 1].block != 0) 
			sMaze[r - 1][c - 1].iBotRight  = index;
		index += 2;
	}
	// TopRight
	if (sMaze[r][c].topRight) {
		createVerticalVertixes(r, c + 1, vPos);
		sMaze[r][c].iTopRight = index;
		// check right
		if (c > 0 && sMaze[r][c - 1].block != 0) 
			sMaze[r][c - 1].iTopLeft = index;
		// check top
		if (r < rmax - 1 && sMaze[r + 1][c].block != 0)
			sMaze[r + 1][c].iBotRight = index;
		// check diagonal
		if (c > 0 && r < rmax - 1 && sMaze[r + 1][c - 1].block != 0)
			sMaze[r + 1][c - 1].iBotLeft = index;
		index += 2;
	}
	// BotLeft
	if (sMaze[r][c].botLeft) {
		createVerticalVertixes(r + 1, c, vPos);
		sMaze[r][c].iBotLeft = index;
		// check bot
		if (r > 0 && sMaze[r - 1][c].block != 0)
			sMaze[r - 1][c].iTopLeft = index;
		// check left
		if (c < cmax - 1 && sMaze[r][c + 1].block != 0)
			sMaze[r][c + 1].iBotRight = index;
		// check diagonal
		if (r > 0 && c < cmax - 1 && sMaze[r - 1][c + 1].block != 0)
			sMaze[r - 1][c + 1].iTopRight = index;
		index += 2;
	}
	// BotRight
	if (sMaze[r][c].botRight) {
		createVerticalVertixes(r + 1, c + 1, vPos);
		sMaze[r][c].iBotRight = index;
		// check bot
		if (r < rmax - 1 && sMaze[r + 1][c].block != 0)
			sMaze[r + 1][c].iTopRight = index;
		// check right
		if (c < cmax - 1 && sMaze[r][c + 1].block != 0)
			sMaze[r][c + 1].iBotLeft = index;
		// check diagonal
		if (r < rmax - 1 && c < cmax - 1 && sMaze[r + 1][c + 1].block != 0)
			sMaze[r + 1][c + 1].iTopLeft = index;
		index += 2;
	}
}

// Create a rectangle (two triangles) with the given indexes
// Since indexes are created always in the same way, the way to create a rectangle is always the same
void createRektangle(int a, int b, int c, int d, std::vector<int> &vIdx) 
{
	vIdx.push_back(a); vIdx.push_back(b); vIdx.push_back(c);
	vIdx.push_back(b); vIdx.push_back(c); vIdx.push_back(d);
}

// Return the index, if it exist, of a certain angle of a given square
int takeIndex(SQUARE** sMaze, int r, int rmax, int c, int cmax, Angles angle) {
	int finalIndex = -1;
	switch (angle)
	{
	case TL:
		if (sMaze[r][c].iTopLeft != -1) {
			finalIndex = sMaze[r][c].iTopLeft;
			break;
		}
		if (r > 0 && sMaze[r - 1][c].iBotLeft != -1) {
			finalIndex = sMaze[r - 1][c].iBotLeft;
			break;
		}
		if (c > 0 && sMaze[r][c - 1].iTopRight != -1) {
			finalIndex = sMaze[r][c - 1].iTopRight;
			break;
		}
		if (r > 0 && c > 0 && sMaze[r - 1][c - 1].iBotRight != -1) {
			finalIndex = sMaze[r - 1][c - 1].iBotRight;
			break;
		}
	case TR:
		if (sMaze[r][c].iTopRight != -1) {
			finalIndex = sMaze[r][c].iTopRight;
			break;
		}
		if (r > 0 && sMaze[r - 1][c].iBotRight != -1) {
			finalIndex = sMaze[r - 1][c].iBotRight;
			break;
		}
		if (c < cmax - 1 && sMaze[r][c + 1].iTopLeft != -1) {
			finalIndex = sMaze[r][c + 1].iTopLeft;
			break;
		}
		if (r > 0 && c < cmax - 1 && sMaze[r - 1][c + 1].iBotLeft != -1) {
			finalIndex = sMaze[r - 1][c + 1].iBotLeft;
			break;
		}

		break;
	case BL:
		if (sMaze[r][c].iBotLeft != -1) {
			finalIndex = sMaze[r][c].iBotLeft;
			break;
		}
		if (r < rmax - 1 && sMaze[r + 1][c].iTopLeft != -1) {
			finalIndex = sMaze[r + 1][c].iTopLeft;
			break;
		}
		if (c > 0 && sMaze[r][c - 1].iBotRight != -1) {
			finalIndex = sMaze[r][c - 1].iBotRight;
			break;
		}
		if (r < rmax - 1 && c > 0 && sMaze[r + 1][c - 1].iTopRight != -1) {
			finalIndex = sMaze[r + 1][c - 1].iTopRight;
			break;
		}
		break;
	case BR:
		if (sMaze[r][c].iBotRight != -1) {
			finalIndex = sMaze[r][c].iBotRight;
			break;
		}
		if (r < rmax - 1 && sMaze[r + 1][c].iTopRight != -1) {
			finalIndex = sMaze[r + 1][c].iTopRight;
			break;
		}
		if (c < cmax - 1 && sMaze[r][c + 1].iBotLeft != -1) {
			finalIndex = sMaze[r][c + 1].iBotLeft;
			break;
		}
		if (r < rmax - 1 && c < cmax - 1 && sMaze[r + 1][c + 1].iTopLeft != -1) {
			finalIndex = sMaze[r + 1][c + 1].iTopLeft;
			break;
		}
		break;
	default:
		return -1;
		break;
	}
	return finalIndex;
}

void Assignment08::createMazeMesh(int row, int col, char **maze) {
	// The procedure gets in input the number of rows <row> of the maze, and the number of columns <col>
	// Element <maze[r][c]>, with 0 <= r <= row-1 and 0 <= c <= col-1 contains:
	//		Symbol ' ' if there is an empty space
	//		Symbol '#' if there is a wall
	//
	// Example: The following piece of code executes the instruction in the ... section
	//          if there is a wall in position r=5, c=7
	//
	// int r, c;
	// r = 5; c = 7;
	// if(maze[r][c] == '#') {
	//		...
	// }
	//
	// The example below creates a square, with four vertices and two triangles.
	// It must be deleted and replaced with your code creating the mesh of the maze.

	SQUARE** squareMaze = new SQUARE* [row];
	for (int i = 0; i < row; ++i)
		squareMaze[i] = new SQUARE[col];

	bool consecutiveWall = false;
    bool newWall = false;
	bool cycle = true;

	// assign blocks and vertices to squares 
	// at the end we have a matrix of SQUARE with the block attribute based on the wall and the minimum amount of vertices needed to create the maze
	// vertices are not duplicated - for every vertex there's one of the 4 adjacent that has that said vertex true, false for everyone else
	int blockCounter = 1;
	bool finished = false;
	for (int r = 0; r < row; r++) {
		for (int c = 0; c < col; c++) {
			if (maze[r][c] == '#')
			{
				newWall = true;
				maze[r][c] = 'x';
				squareMaze[r][c].block = blockCounter;
				squareMaze[r][c].setTrue();
				while (not finished) 
				{
					finished = true;
					for (int rx = r; rx < row; rx++)
					{
						for (int cx = 0; cx < col; cx++)
						{
							if (maze[rx][cx] == '#')
							{
								if ((rx > 0 && squareMaze[rx][cx].block == 0 && squareMaze[rx - 1][cx].block == blockCounter) ||
									(cx > 0 && squareMaze[rx][cx].block == 0 && squareMaze[rx][cx - 1].block == blockCounter) ||
									(rx < row - 1 && squareMaze[rx][cx].block == 0 && squareMaze[rx + 1][cx].block == blockCounter) ||
									(cx < col - 1 && squareMaze[rx][cx].block == 0 && squareMaze[rx][cx + 1].block == blockCounter))
								{
									maze[rx][cx] = 'x';
									squareMaze[rx][cx].block = blockCounter;
									squareMaze[rx][cx].setTrue();
									handleVertixes(squareMaze, rx, row, cx, col);
									
									finished = false;
								}
							}
						}
					}
				}
			}
			finished = false;
			if (newWall) 
			{
				newWall = false;
				blockCounter++;
			}
		}
	}

	// Debug print
	//printf("\n");
	//for (int r = 0; r < row; r++) {
	//	for (int c = 0; c < col; c++) {
	//		if (r > 9 && c > 9) printf("pos %d,%d: %d %d %d %d    ", r, c, squareMaze[r][c].topLeft, squareMaze[r][c].botLeft, squareMaze[r][c].topRight, squareMaze[r][c].botRight);
	//		else if (r > 9 && c <= 9) printf("pos %d, %d: %d %d %d %d    ", r, c, squareMaze[r][c].topLeft, squareMaze[r][c].botLeft, squareMaze[r][c].topRight, squareMaze[r][c].botRight);
	//		else if (r <= 9 && c > 9) printf("pos  %d,%d: %d %d %d %d    ", r, c, squareMaze[r][c].topLeft, squareMaze[r][c].botLeft, squareMaze[r][c].topRight, squareMaze[r][c].botRight);
	//		else printf("pos  %d, %d: %d %d %d %d    ", r, c, squareMaze[r][c].topLeft, squareMaze[r][c].botLeft, squareMaze[r][c].topRight, squareMaze[r][c].botRight);
	//		//printf("%d", squareMaze[r][c].block);
	//	}
	//	printf("\n");
	//}
	//printf("\n");
		
	// create the vertices needed for the maze
	int indexCounter = 0;
	for (int r = 0; r < row; r++) {
		for (int c = 0; c < col; c++) {
			if (squareMaze[r][c].block != 0)
			{
				instantiateVertixes(squareMaze, r, row, c, col, indexCounter, vPos);
			}
		}
	}
	
	// cycle to create top rectangles
	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < col; c++)
		{
			if (squareMaze[r][c].block != 0)
			{
				// fill row
				if (squareMaze[r][c].canStartRow()) 
				{
					int leftTop = squareMaze[r][c].iTopLeft != -1 ? squareMaze[r][c].iTopLeft : squareMaze[r][c].iTopRight;
					int leftBot = squareMaze[r][c].iBotLeft != -1 ? squareMaze[r][c].iBotLeft : squareMaze[r][c].iBotRight;
					finished = false;
					int cx = c;
					while (not finished) 
					{
						if (cx < col - 1) cx++;
						else {
							finished = true;
						}
						if (squareMaze[r][cx].canStartRow() && not finished)
						{
							int rightTop = squareMaze[r][cx].iTopRight != -1 ? squareMaze[r][cx].iTopRight : squareMaze[r][cx].iTopLeft;
							int rightBot = squareMaze[r][cx].iBotRight != -1 ? squareMaze[r][cx].iBotRight : squareMaze[r][cx].iBotLeft;
							createRektangle(leftTop, leftBot, rightTop, rightBot, vIdx);
							finished = true;
						}
						else if (squareMaze[r][cx].block == 0) finished = true;
					}
				}
				// fill columns
				if (squareMaze[r][c].canStartCol())
				{
					int topLeft = squareMaze[r][c].iTopLeft != -1 ? squareMaze[r][c].iTopLeft : squareMaze[r][c].iBotLeft;
					int topRight = squareMaze[r][c].iTopRight != -1 ? squareMaze[r][c].iTopRight : squareMaze[r][c].iBotRight;
					finished = false;
					int rx = r;
					while (not finished)
					{
						if (rx < row - 1) rx++;
						else {
							finished = true;
						}
						if (squareMaze[rx][c].canStartCol() && not finished)
						{
							int botLeft = squareMaze[rx][c].iBotLeft != -1 ? squareMaze[rx][c].iBotLeft : squareMaze[rx][c].iTopLeft;
							int botRight = squareMaze[rx][c].iBotRight != -1 ? squareMaze[rx][c].iBotRight : squareMaze[rx][c].iTopRight;
							createRektangle(topLeft, topRight, botLeft, botRight, vIdx);
							finished = true;
						}
						else if (squareMaze[rx][c].block == 0) finished = true;
					}
				}
			}
		}
	}

	// create an int matrix to store vertixes indexes to avoid ambiguity 
	int** finalVertixes = new int * [row + 1];
	for (int i = 0; i < row + 1; ++i)
		finalVertixes[i] = new int[col + 1];

	// initilialize it
	for (int i = 0; i < row + 1; i++)
	{
		for (int j = 0; j < col + 1; j++)
		{
			finalVertixes[i][j] = -1;
		}
	}

	// assign the correct values
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (squareMaze[i][j].block != 0) 
			{
				if (squareMaze[i][j].topLeft) {
					finalVertixes[i][j] = squareMaze[i][j].iTopLeft;
				}
				if (squareMaze[i][j].topRight) {
					finalVertixes[i][j + 1] = squareMaze[i][j].iTopRight;
				}
				if (squareMaze[i][j].botLeft) {
					finalVertixes[i + 1][j] = squareMaze[i][j].iBotLeft;
				}
				if (squareMaze[i][j].botRight) {
					finalVertixes[i + 1][j + 1] = squareMaze[i][j].iBotRight;
				}
			}
		}
	}

	// print the final state of the matrix
	/*printf("\n");
	for (int i = 0; i < row + 1; i++)
	{
		for (int j = 0; j < col + 1; j++)
		{
			int temp = finalVertixes[i][j];
			if (temp >= 100) printf("[%d]", temp);
			else if (temp >= 10) printf("[ %d]", temp);
			else if (temp == -1) printf("[ - ]");
			else printf("[  %d]", temp);
		}
		printf("\n");
	}*/
;
	// cycle to create walls
	// horizontal
	for (int r = 0; r < row + 1; r++)
	{
		for (int c = 0; c < col + 1; c++)
		{
			// save the first index found
			int x = finalVertixes[r][c];
			if (x != -1)
			{
				// search on the same row to close the wall
				int cx = c;
				finished = false;
				while (not finished)
				{
					if (cx < col) cx++;
					else {
						finished = true;
					}
					// controls if i'm watching a wall
					if (cx < col && r < row && squareMaze[r][cx - 1].block == 0) {
						// if it's the first row, finding an empty block means stop
						if (r == 0) {
							finished = true;
						}
						// if it's not, check the upper block, empty means that the wall i'm trying to create is wrong
						if (r > 0 && squareMaze[r - 1][cx - 1].block == 0)
						{
							finished = true;
						}
					}
					// special case for the last row, same as r==0 above
					if (r == 15 && squareMaze[r - 1][cx - 1].block == 0) {
						finished = true;
					}

					// check if there's a vertex 
					int y = finalVertixes[r][cx];
					if (y != -1 && not finished)
					{
						// if it's the first or last row, do it
						if (r == 0 || r == row)
						{
							createRektangle(x, x + 1, y, y + 1, vIdx);
							finished = true;
						}
						else
						{
							// otherwise I must check if it's a legit wall, T example
							if (squareMaze[r][cx - 1].block == 0 || squareMaze[r - 1][cx - 1].block == 0)
							{
								createRektangle(x, x + 1, y, y + 1, vIdx);
							}
							finished = true;
						}
					}
				}
			}
		}
	}
	// vertical
	for (int r = 0; r < row + 1; r++)
	{
		for (int c = 0; c < col + 1; c++)
		{
			// save the first index found
			int x = finalVertixes[r][c];
			if (x != -1)
			{
				// search on the same row to close the wall
				int rx = r;
				finished = false;
				while (not finished)
				{
					if (rx < row) rx++;
					else {
						finished = true;
					}

					// controls if i'm watching a wall
					if (rx < row && c < col && squareMaze[rx - 1][c].block == 0) { 
						// if it isn't a wall, check the left block: empty means that the wall i'm trying to create is wrong
						if (r > 0 && squareMaze[rx - 1][c - 1].block == 0)
						{
							finished = true;
						}
					}

					// check if there's a vertex
					int y = finalVertixes[rx][c];
					if (y != -1 && not finished)
					{
						// if it's the first or last column, do it
						if (c == 0 || c == col)
						{
							createRektangle(x, x + 1, y, y + 1, vIdx);
							finished = true;
						}
						else
						{
							// otherwise I must check if it's a legit wall, T example
							if (squareMaze[rx - 1][c].block == 0 || squareMaze[rx - 1][c - 1].block == 0)
							{
								createRektangle(x, x + 1, y, y + 1, vIdx);
							}
							finished = true;
						}
					}
				}
			}
		}
	}
	
	// Creates the floor by reusing the vertex always present at the edge of the maze
	vIdx.push_back(finalVertixes[0][0]+1); vIdx.push_back(finalVertixes[15][0]+1); vIdx.push_back(finalVertixes[15][15]+1);	// First triangle
	vIdx.push_back(finalVertixes[0][0]+1); vIdx.push_back(finalVertixes[0][15]+1); vIdx.push_back(finalVertixes[15][15]+1);	// Second triangle

	// free the memory
	for (int i = 0; i < row; ++i)
		delete[] squareMaze[i];
	delete[] squareMaze;
	for (int i = 0; i < row + 1; ++i)
		delete[] finalVertixes[i];
	delete[] finalVertixes;
}
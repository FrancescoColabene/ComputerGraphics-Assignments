
class SQUARE {
public:
	SQUARE() {}
	bool topLeft = false;
	bool topRight = false;
	bool botLeft = false;
	bool botRight = false;
};

void createFourVertixesRow(int x, int z, std::vector<float>& vPos) {

	vPos.push_back(x);		vPos.push_back(0.0); vPos.push_back(z);
	vPos.push_back(x);		vPos.push_back(0.0); vPos.push_back(z + 1.0);
	vPos.push_back(x);		vPos.push_back(1.0); vPos.push_back(z);
	vPos.push_back(x);		vPos.push_back(1.0); vPos.push_back(z + 1.0);

}

void createFourVertixesCol(int x, int z, std::vector<float> &vPos) {

	vPos.push_back(x);		  vPos.push_back(0.0); vPos.push_back(z);		
	vPos.push_back(x + 1.0);  vPos.push_back(0.0); vPos.push_back(z);		
	vPos.push_back(x);		  vPos.push_back(1.0); vPos.push_back(z);		
	vPos.push_back(x + 1.0);  vPos.push_back(1.0); vPos.push_back(z);

}

void createRettangol1(int vertexIndex, std::vector<int> &vIdx) {

	vIdx.push_back(vertexIndex); vIdx.push_back(vertexIndex + 1); vIdx.push_back(vertexIndex + 3);
	vIdx.push_back(vertexIndex); vIdx.push_back(vertexIndex + 2); vIdx.push_back(vertexIndex + 3);
	// this generates the down face - it's not needed
	//vIdx.push_back(vertexIndex); vIdx.push_back(vertexIndex + 4); vIdx.push_back(vertexIndex + 5);
	//vIdx.push_back(vertexIndex); vIdx.push_back(vertexIndex + 1); vIdx.push_back(vertexIndex + 5);

	vIdx.push_back(vertexIndex); vIdx.push_back(vertexIndex + 2); vIdx.push_back(vertexIndex + 6);
	vIdx.push_back(vertexIndex); vIdx.push_back(vertexIndex + 4); vIdx.push_back(vertexIndex + 6);

	vIdx.push_back(vertexIndex + 1); vIdx.push_back(vertexIndex + 3); vIdx.push_back(vertexIndex + 7);
	vIdx.push_back(vertexIndex + 1); vIdx.push_back(vertexIndex + 5); vIdx.push_back(vertexIndex + 7);

	vIdx.push_back(vertexIndex + 3); vIdx.push_back(vertexIndex + 2); vIdx.push_back(vertexIndex + 6);
	vIdx.push_back(vertexIndex + 3); vIdx.push_back(vertexIndex + 7); vIdx.push_back(vertexIndex + 6);

	vIdx.push_back(vertexIndex + 4); vIdx.push_back(vertexIndex + 6); vIdx.push_back(vertexIndex + 7);
	vIdx.push_back(vertexIndex + 4); vIdx.push_back(vertexIndex + 5); vIdx.push_back(vertexIndex + 7);

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

	/*SQUARE** easierMaze = new SQUARE* [row];
	for (int i = 0; i < row; ++i)
		easierMaze[i] = new SQUARE[col];*/

	int vertexIndex = 0;
	bool consecutiveWall = false;
	
	for (int i = 0; i < row; i++)
	{
		for (int j = 1; j < col - 1; j++)
		{
			// scanning rows first i = 0 -> j = 0,1,2,3...
			// if it is a wall
			if (maze[i][j] == '#') 
			{
				// if it is new
				if (!consecutiveWall) 
				{
					// placing initial vertixes 
					createFourVertixesRow(j, i, vPos);
				}
				// if it's the last one of the row
				if(j == col - 2)
				{
					// those vertixes have to be on the right side of the cube
					j++;
					// placing final vertixes
					createFourVertixesRow(j, i, vPos);
					// creating triangles and updating the vertexIndex
					createRettangol1(vertexIndex, vIdx);
					vertexIndex += 8;
				}
				consecutiveWall = true;
			}
			// if it is not a wall
			else 
			{
				// if the previous one was a wall
				if(consecutiveWall)
				{
					// placing final vertixes
					createFourVertixesRow(j, i, vPos);
					// creating triangles
					createRettangol1(vertexIndex, vIdx);
					// updating the vertexIndex and setting consecutiveWallto false
					vertexIndex += 8;
					consecutiveWall = false;
				}
			}
		}
		// resetting the consecutiveWall to false for next row
		consecutiveWall = false;
	}
	
	// creates vertix for the left column
	createFourVertixesCol(0, 0, vPos);
	createFourVertixesCol(0, row, vPos);

	// creates the faces with triangles
	createRettangol1(vertexIndex, vIdx);

	// updating the vertexIndex
	vertexIndex += 8;


	// creates vertix for the right column
	createFourVertixesCol(col-1, 0, vPos);
	createFourVertixesCol(col-1, row, vPos);

	// creates the faces with triangles
	createRettangol1(vertexIndex, vIdx);

	// updating the vertexIndex
	vertexIndex += 8;


	// FLOOR
	vPos.push_back(0.0); vPos.push_back(0.0); vPos.push_back(0.0);	// vertex 0
	vPos.push_back(row); vPos.push_back(0.0); vPos.push_back(0.0);	// vertex 1
	vPos.push_back(0.0); vPos.push_back(0.0); vPos.push_back(col);	// vertex 2
	vPos.push_back(row); vPos.push_back(0.0); vPos.push_back(col);	// vertex 3

	vIdx.push_back(vertexIndex); vIdx.push_back(vertexIndex + 1); vIdx.push_back(vertexIndex + 3);	// First triangle
	vIdx.push_back(vertexIndex); vIdx.push_back(vertexIndex + 2); vIdx.push_back(vertexIndex + 3);	// Second triangle
	
	vertexIndex += 4;

	/*or (int i = 0; i < row; ++i)
		delete[] easierMaze[i];
	delete[] easierMaze;*/
}

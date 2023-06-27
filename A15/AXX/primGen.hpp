void createTriangles(std::vector<uint32_t> &vIdx, int count) {
	vIdx.push_back(count);     vIdx.push_back(count + 1); vIdx.push_back(count + 2);
	vIdx.push_back(count + 1); vIdx.push_back(count + 2); vIdx.push_back(count + 3);
}

void Assignment15::createBoxMesh(std::vector<Vertex> &vDef, std::vector<uint32_t> &vIdx) {
	// The primitive built here is a box centered in the origin, with proportions respecting the texture.

	/*
	coordinate UV per averlo dritto:
	0,1; 1,1; 0,0; 1,0
	*/

	int vertexCounter = 0;
	
	// Creating the front face
	vDef.push_back({ {0,0,1}, {1,0,0}, {0.435f,0.817f} });
	vDef.push_back({ {0,0,2}, {1,0,0}, {0.09f ,0.817f} });
	vDef.push_back({ {0,1,1}, {1,0,0}, {0.435f,0.18f} });
	vDef.push_back({ {0,1,2}, {1,0,0}, {0.09f ,0.18f} });
	createTriangles(vIdx, vertexCounter);
	vertexCounter += 4;

	// Creating the back face
	vDef.push_back({ {-0.26,0,1}, {0,0,-1}, {0.525f,0.817f} });
	vDef.push_back({ {-0.26,0,2}, {0,0,-1}, {0.87f ,0.817f} });
	vDef.push_back({ {-0.26,1,1}, {0,0,-1}, {0.525f,0.18f} });
	vDef.push_back({ {-0.26,1,2}, {0,0,-1}, {0.87f ,0.18f} });
	createTriangles(vIdx, vertexCounter);
	vertexCounter += 4;

	// Creating the top face
	vDef.push_back({ {-0.26,1,2}, {0,1,0}, {0.09f,0.0f} });
	vDef.push_back({ {-0.26,1,1}, {0,1,0}, {0.435f,0.0f} });
	vDef.push_back({ {0    ,1,2}, {0,1,0}, {0.09f,0.184f} });
	vDef.push_back({ {0    ,1,1}, {0,1,0}, {0.435f,0.184f} });
	createTriangles(vIdx, vertexCounter);
	vertexCounter += 4;

	// Creating the bot face
	vDef.push_back({ {0,0,1}, {0,-1,0}, {0.435f,0.816f} });
	vDef.push_back({ {0,0,2}, {0,-1,0}, {0.09f ,0.816f} });
	vDef.push_back({ {-0.26,0,    1}, {0,-1,0}, {0.435f,1.0f} });
	vDef.push_back({ {-0.26,0,    2}, {0,-1,0}, {0.09f ,1.0f} });
	createTriangles(vIdx, vertexCounter);
	vertexCounter += 4;

	// Creating the left face
	vDef.push_back({ {-0.26,0,2}, {0,0,1}, {   0.0f, 0.818f} });
	vDef.push_back({ {0    ,0,2}, {0,0,1}, {0.0915f, 0.818f} });
	vDef.push_back({ {-0.26,1,2}, {0,0,1}, {   0.0f, 0.18f} });
	vDef.push_back({ {0    ,1,2}, {0,0,1}, {0.0915f, 0.18f} });
	createTriangles(vIdx, vertexCounter);
	vertexCounter += 4;

	// Creating the right face
	vDef.push_back({ {-0.26,0,1}, {0,0,-1}, {0.524f, 0.818f} });
	vDef.push_back({ {-0.26,1,1}, {0,0,-1}, {0.524f, 0.18f} });
	vDef.push_back({ {0    ,0,1}, {0,0,-1}, {0.433f, 0.818f} });
	vDef.push_back({ {0    ,1,1}, {0,0,-1}, {0.433f, 0.18f} });
	createTriangles(vIdx, vertexCounter);
	vertexCounter += 4;

	/*
	// INIZIO IMPLEMENTAZIONE SENZA BORDI BIANCHI
	//Creating the front face
	vDef.push_back({ {0,0,0}, {0,0,1}, {0.0945f,0.81f} });
	vDef.push_back({ {1,0,0}, {0,0,1}, {0.43f,0.81f} });
	vDef.push_back({ {0,1,0}, {0,0,1}, {0.0945f,0.1895f} });
	vDef.push_back({ {1,1,0}, {0,0,1}, {0.43f,0.1895f} });
	createTriangles(vIdx, vertexCounter);
	vertexCounter += 4;

	// Creating the back face
	vDef.push_back({ {0,0,-0.26}, {0,0,-1}, {0.53f,0.81f} });
	vDef.push_back({ {1,0,-0.26}, {0,0,-1}, {0.867f,0.81f} });
	vDef.push_back({ {0,1,-0.26}, {0,0,-1}, {0.53f,0.1895f} });
	vDef.push_back({ {1,1,-0.26}, {0,0,-1}, {0.867f,0.1895f} });
	createTriangles(vIdx, vertexCounter);
	vertexCounter += 4;

	// Creating the top face
	vDef.push_back({ {0,1,-0.26}, {0,1,0}, {0.0945f,0} });
	vDef.push_back({ {1,1,-0.26}, {0,1,0}, {0.43f,0} });
	vDef.push_back({ {0,1,    0}, {0,1,0}, {0.0945f,0.1777f} });
	vDef.push_back({ {1,1,    0}, {0,1,0}, {0.43f,0.1777f} });
	createTriangles(vIdx, vertexCounter);
	vertexCounter += 4;*/

}

#define M_PI 3.141595f
void Assignment15::createSphereMesh(std::vector<Vertex> &vDef, std::vector<uint32_t> &vIdx) {
	// The primitive built here is a sphere of radius 1, centered in the origin, on which the Mars texture is applied seamless.
	
	float horizontalStep = M_PI / 30; //  =~ 0.157f, 0.0785f
	float verticalStep = 0.005f;
	float duePI = M_PI * 2;

	int diff = ceil(duePI / horizontalStep); // =40

	//for (float angle = 0.0f; angle <= 6.28f; angle += verticalStep)
	//{
	//	vDef.push_back({ {0.0f,  1.0f, 0.0f}, {0.0f,   1.0f, 0.0f} , {(angle) / 6.28f, 0.001f} });	// Top vertex: index=0,2,4,6,8, ..., 38
	//	vDef.push_back({ {0.0f, -1.0f, 0.0f}, {0.0f,  -1.0f, 0.0f} , {(angle) / 6.28f, 0.999f} });	// Bot vertex: index=1,3,5,7,9, ..., 39
	//}

	// in totale creo 78 vertici
	int vertexCounter = 0;

	float radius;
	glm::vec3 temp, minusTemp;

	int steps = ceil(2.0f / verticalStep);
	for (int i = 1; i < steps; i++)
	{
		float height = -1 + verticalStep * i;
		for (int j = 0; j < diff; j++)
		{
			float angle = horizontalStep * j;
			radius = sqrt(1.0f - pow(height, 2));
			temp = glm::vec3(radius * cos(angle), height, radius * sin(angle));
			minusTemp = -temp;

			vDef.push_back({ temp, temp , { 0.5 + atan2(minusTemp.z, minusTemp.x) / duePI, 0.5f + asin(minusTemp.y) / M_PI}});
			//printf("temp = (%f, %f, %f)\n", temp.x, temp.y, temp.z);
			//printf("(%f, %f)\n", 0.5f + atan2(minusTemp.z, minusTemp.x) / duePI, 0.5f + asin(minusTemp.y) / M_PI);
			vertexCounter++;
		}
		// Creating a copy of the first vertix to close the texture
		radius = sqrt(1.0f - pow(height, 2));
		temp = glm::vec3(radius * cos(0), height, radius * sin(0));
		minusTemp = -temp;
		vDef.push_back({ temp, temp , { 1 , 0.5f + asin(minusTemp.y) / M_PI } });
		//printf("temp = (%f, %f, %f)\n", temp.x, temp.y, temp.z);
		//printf("(%f, %f)\n", 1.0f , (1.0f - height) / 2.0f);
		vertexCounter++;
	}

	// Creating the vertices
	//for (float height = -1.0f + (horizontalStep); height <= 1.0f - (horizontalStep); height += horizontalStep)
	//{
	//  // Creating a circle of vertices at a certain height
	//  for (float angle = 0.0f; angle < 6.28f; angle += verticalStep)
	//  {
	//    
	//    radius = sqrt(1.0f - pow(height, 2));
	//    temp = glm::vec3(radius * cos(angle), height, radius * sin(angle));

	//    vDef.push_back({ temp, temp , { (angle)/6.28f , (1.0f-height) / 2.0f } });
	//    //printf("(%f, %f)\n", (angle) / 6.28f, (1.0f - height) / 2.0f);
	//    vertexCounter++;
	//  }
	//  // Creating a copy of the first vertix to close the texture
	//  radius = sqrt(1.0f - pow(height, 2));
	//  temp = glm::vec3(radius * cos(0), height, radius * sin(0));
	//  vDef.push_back({ temp, temp , { 1.0f , (1.0f - height) / 2.0f } });
	//  //printf("(%f, %f)\n", 1.0f , (1.0f - height) / 2.0f);
	//  vertexCounter++;
	//}

	//printf("\n\ndiff ceil: %f, diff floor: %f\n\n\n", ceil(6.28f / verticalStep), floor(6.28f / verticalStep));

	// Creating triangles between vertices (excluding the first and last row)
	int level = 0;
	for (int count = level; count < vertexCounter - diff - 1; count++)
	{
		if (count != level + diff - 1) {
			vIdx.push_back(count); vIdx.push_back(count + 1); vIdx.push_back(count + diff + 1);
			vIdx.push_back(count + 1); vIdx.push_back(count + diff + 1); vIdx.push_back(count + diff + 2);
		}
		else {
			vIdx.push_back(count); vIdx.push_back(count + 1); vIdx.push_back(count + diff + 1);
			vIdx.push_back(count + 1); vIdx.push_back(count + diff + 1); vIdx.push_back(count + diff + 2);
			count++;
			level += (diff + 1);
		}
	}

	// Creating vertices for top
	int vertexPointer = vertexCounter;
	for (int i = 0; i < diff - 1; i++)
	{
		float angle = horizontalStep * i;
		vDef.push_back({ {0,1,0} , {0,1,0}, { (angle) / duePI, 0 }});
		vertexCounter++;
	}
	vDef.push_back({ {0,1,0} , {0,1,0}, { 1, 0 } });
	vertexCounter++;

	// Creating verices for bot
	for (int i = 0; i < diff - 1; i++)
	{
		float angle = horizontalStep * i;
		vDef.push_back({ {0,-1,0} , {0,-1,0}, { (angle) / duePI, 1 } });
		vertexCounter++;
	}
	vDef.push_back({ {0,-1,0} , {0,-1,0}, { 1, 1 } });
	vertexCounter++;

	// Creating top triangles
	for (int count = 0; count < diff; count++)
	{
		vIdx.push_back(vertexPointer + count); vIdx.push_back(vertexPointer - diff + count - 1); vIdx.push_back(vertexPointer - diff + count);
	}
	vIdx.push_back(vertexPointer + diff - 1); vIdx.push_back(vertexPointer - 1); vIdx.push_back(vertexPointer - 2);

	vertexPointer += diff;
	// Creating bot triangles
	for (int count = 0; count < diff; count++)
	{
		vIdx.push_back(vertexPointer + count); vIdx.push_back(count); vIdx.push_back(count + 1);
	}
	vIdx.push_back(vertexPointer + diff - 1); vIdx.push_back(diff - 1); vIdx.push_back(diff);
}


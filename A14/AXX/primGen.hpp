void Assignment14::createCubeMesh(std::vector<Vertex> &vDef, std::vector<uint32_t> &vIdx) {
	// The procedure fills array vPos with the positions of the vertices and of the normal vectors of the mesh
/*	vDef.push_back({{0.0f, 0.0f, 0.1f}, {0.5f, 0.0f, 0.866f}});	// vertex 0 - Position and Normal
	vDef.push_back({{1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}});	// vertex 1 - Position and Normal
	vDef.push_back({{0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}});	// vertex 2 - Position and Normal
	vDef.push_back({{1.0f, 1.0f, 0.1f}, {-0.5f, 0.0f, 0.866f}});// vertex 3 - Position and Normal

	// The procedures also fill the array vIdx with the indices of the vertices of the triangles
	vIdx.push_back(0); vIdx.push_back(1); vIdx.push_back(2);	// First triangle
	vIdx.push_back(1); vIdx.push_back(2); vIdx.push_back(3);	// Second triangle
	
	// The primitive built here is a cube centered in the origin, whose edge lenght is 2.
*/	
	// Initializing vertexCounter
	int vertexCounter = 0;
	
	// Creating back face vertices
	vDef.push_back({ {-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f} });
	vDef.push_back({ { 1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f} });
	vDef.push_back({ {-1.0f,  1.0f, -1.0f}, {0.0f, 0.0f, -1.0f} });
	vDef.push_back({ { 1.0f,  1.0f, -1.0f}, {0.0f, 0.0f, -1.0f} });
	// Creating back face triangles
	vIdx.push_back(vertexCounter); vIdx.push_back(vertexCounter+1); vIdx.push_back(vertexCounter+2);	
	vIdx.push_back(vertexCounter+1); vIdx.push_back(vertexCounter+2); vIdx.push_back(vertexCounter+3);

	vertexCounter += 4;

	// Creating front face vertices
	vDef.push_back({ {-1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f} });	
	vDef.push_back({ { 1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f} });	
	vDef.push_back({ {-1.0f,  1.0f, 1.0f}, {0.0f, 0.0f, 1.0f} });	
	vDef.push_back({ { 1.0f,  1.0f, 1.0f}, {0.0f, 0.0f, 1.0f} });
	// Creating front face triangles
	vIdx.push_back(vertexCounter);     vIdx.push_back(vertexCounter + 1); vIdx.push_back(vertexCounter + 2);	
	vIdx.push_back(vertexCounter + 1); vIdx.push_back(vertexCounter + 2); vIdx.push_back(vertexCounter + 3);	

	vertexCounter += 4;

	// Creating right face vertices
	vDef.push_back({ {1.0f, -1.0f, -1.0f}, {1.0f, 0.0f, 0.0f} });	
	vDef.push_back({ {1.0f, -1.0f,  1.0f}, {1.0f, 0.0f, 0.0f} });	
	vDef.push_back({ {1.0f,  1.0f, -1.0f}, {1.0f, 0.0f, 0.0f} });	
	vDef.push_back({ {1.0f,  1.0f,  1.0f}, {1.0f, 0.0f, 0.0f} });
	// Creating right face trinagles
	vIdx.push_back(vertexCounter);     vIdx.push_back(vertexCounter + 1); vIdx.push_back(vertexCounter + 2);	
	vIdx.push_back(vertexCounter + 1); vIdx.push_back(vertexCounter + 2); vIdx.push_back(vertexCounter + 3);	

	vertexCounter += 4;

	// Creating left face vertices
	vDef.push_back({ {-1.0f, -1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f} });
	vDef.push_back({ {-1.0f, -1.0f,  1.0f}, {-1.0f, 0.0f, 0.0f} });
	vDef.push_back({ {-1.0f,  1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f} });
	vDef.push_back({ {-1.0f,  1.0f,  1.0f}, {-1.0f, 0.0f, 0.0f} });
	// Creating left face triangles
	vIdx.push_back(vertexCounter);     vIdx.push_back(vertexCounter + 1); vIdx.push_back(vertexCounter + 2);
	vIdx.push_back(vertexCounter + 1); vIdx.push_back(vertexCounter + 2); vIdx.push_back(vertexCounter + 3);

	vertexCounter += 4;

	// Creating top face vertices
	vDef.push_back({ {-1.0f, 1.0f, -1.0f}, {0.0f, 1.0f, 0.0f} });
	vDef.push_back({ {-1.0f, 1.0f,  1.0f}, {0.0f, 1.0f, 0.0f} });
	vDef.push_back({ { 1.0f, 1.0f, -1.0f}, {0.0f, 1.0f, 0.0f} });
	vDef.push_back({ { 1.0f, 1.0f,  1.0f}, {0.0f, 1.0f, 0.0f} });
	// Creating top face vertices
	vIdx.push_back(vertexCounter);     vIdx.push_back(vertexCounter + 1); vIdx.push_back(vertexCounter + 2);
	vIdx.push_back(vertexCounter + 1); vIdx.push_back(vertexCounter + 2); vIdx.push_back(vertexCounter + 3);

	vertexCounter += 4;

	// Creating bot face vertices
	vDef.push_back({ {-1.0f, -1.0f, -1.0f}, {0.0f, -1.0f, 0.0f} });	// vertex 0 - Position and Normal
	vDef.push_back({ {-1.0f, -1.0f,  1.0f}, {0.0f, -1.0f, 0.0f} });	// vertex 1 - Position and Normal
	vDef.push_back({ { 1.0f, -1.0f, -1.0f}, {0.0f, -1.0f, 0.0f} });	// vertex 2 - Position and Normal
	vDef.push_back({ { 1.0f, -1.0f,  1.0f}, {0.0f, -1.0f, 0.0f} });// vertex 3 - Position and Normal
	// Creating bot face vertices
	vIdx.push_back(vertexCounter);     vIdx.push_back(vertexCounter + 1); vIdx.push_back(vertexCounter + 2);	// First triangle
	vIdx.push_back(vertexCounter + 1); vIdx.push_back(vertexCounter + 2); vIdx.push_back(vertexCounter + 3);	// Second triangle
}

// Function to create a vertex and assign it the correct normal
void createVertex(std::vector<Vertex>& vDef, float x, float z) {
	glm::vec3 normalVector = -glm::normalize( glm::vec3(cos(z) * cos(x), -1.0f, -sin(x) * sin(z)) );
	vDef.push_back({ {x, sin(x) * cos(z), z}, normalVector});
}

void Assignment14::createFunctionMesh(std::vector<Vertex> &vDef, std::vector<uint32_t> &vIdx) {
	// The procedure fills array vPos with the positions of the vertices and of the normal vectors of the mesh
	// The procedures also fill the array vIdx with the indices of the vertices of the triangles
	// The primitive built here is the surface y = sin(x) * cos(z) with -3 <= x <= 3 and -3 <= z <= 3.

	// Initializing vertexCounter and step (to determine the number of vertices -> higher numbers leads to less vertices)
	int vertexCounter = 0;
	float step = 0.3f;
	 
	for (float i = -3.0f; i <= 3.0f; i+=step)
	{
		// Creating the first two vertices of the row
		createVertex(vDef, i, -3.0f);
		createVertex(vDef, i + step, -3.0f);
		for (float j = -3.0f;j <= 3.0f; j+=step)
		{
			// Creating the next two needed vertices
			createVertex(vDef, i     , j+step);
			createVertex(vDef, i+step, j+step);
			// Creating the triangles to link the previous vertices
			vIdx.push_back(vertexCounter);   vIdx.push_back(vertexCounter+1); vIdx.push_back(vertexCounter+2);
			vIdx.push_back(vertexCounter+1); vIdx.push_back(vertexCounter+2); vIdx.push_back(vertexCounter+3);
			// Increment the vertexCounter by 2 to utilize again the previous vertices
			vertexCounter += 2;
		}
		// Reset the vertexCounter for the new row
		vertexCounter += 2;
	}
}

void Assignment14::createCylinderMesh(std::vector<Vertex> &vDef, std::vector<uint32_t> &vIdx) {
	// The procedure fills array vPos with the positions of the vertices and of the normal vectors of the mesh
	// The procedures also fill the array vIdx with the indices of the vertices of the triangles
	// The primitive built here is a cylinder, with radius 1, and height 2, centered in the origin.
	
	// Creating the center vertices for higher and lower circles
	vDef.push_back({ {0.0f,  1.0f, 0.0f} , {0.0f,  1.0f, 0.0f} });
	vDef.push_back({ {0.0f, -1.0f, 0.0f} , {0.0f, -1.0f, 0.0f} });
	// Initializing vertexCounter and step 
	int vertexCounter = 2;
	float step = 0.157f;
	// Create the first two vertices for the loop, also needed at the end
	vDef.push_back({ {cos(0),  1.0f, sin(0)} , {0.0f,  1.0f, 0.0f} });
	vDef.push_back({ {cos(0), -1.0f, sin(0)} , {0.0f, -1.0f, 0.0f} });
	for (float i = step; i <= 6.28f; i+=step)
	{
		// Create another vertex for the upper circle and create a triangle with it
		vDef.push_back({ {cos(i), 1.0f, sin(i)},{0.0f, 1.0f, 0.0f} });
		vIdx.push_back(0); vIdx.push_back(vertexCounter); vIdx.push_back(vertexCounter + 2);
		// Create another vertex for the lower circle and create a triangle with it
		vDef.push_back({ {cos(i), -1.0f, sin(i)},{0.0f, -1.0f, 0.0f} });
		vIdx.push_back(1); vIdx.push_back(vertexCounter+1); vIdx.push_back(vertexCounter + 3);
		// Update the vertexCounter
		vertexCounter += 2;
	}
	// Creating the last two triangles to close the first vertices with the last ones
	vIdx.push_back(0); vIdx.push_back(2); vIdx.push_back(vertexCounter);
	vIdx.push_back(1); vIdx.push_back(3); vIdx.push_back(vertexCounter + 1);
	// Reset the vertexCounter for the other cycle
	vertexCounter += 2;

	// Creating the border
	// Saving the vertexCounter to close the border at the end
	int saved = vertexCounter;
	// Creating the first two vertices, they have the same normal because they're on the same axis
	glm::vec3 normal = glm::normalize(glm::vec3(cos(0), 0.0f, sin(0)));
	vDef.push_back({ {cos(0), -1.0f, sin(0)}, normal });
	vDef.push_back({ {cos(0),  1.0f, sin(0)}, normal });
	for (float i = step; i <= 6.28f; i += step)
	{
		// Creating another two vertices as before
		glm::vec3 normal = glm::normalize(glm::vec3(cos(i), 0.0f, sin(i)));
		vDef.push_back({ {cos(i), -1.0f, sin(i)}, normal });
		vDef.push_back({ {cos(i),  1.0f, sin(i)}, normal });

		// Creating triangles between the last 4 vertices
		vIdx.push_back(vertexCounter); vIdx.push_back(vertexCounter + 1); vIdx.push_back(vertexCounter + 3);
		vIdx.push_back(vertexCounter); vIdx.push_back(vertexCounter + 2); vIdx.push_back(vertexCounter + 3);
		// Updating the vertexCounter by 2 to reuse the last two vertices
		vertexCounter += 2;
	}
	// Creating the last two triangles to close the first vertices with the last ones
	vIdx.push_back(saved); vIdx.push_back(saved + 1);     vIdx.push_back(vertexCounter + 1);
	vIdx.push_back(saved); vIdx.push_back(vertexCounter); vIdx.push_back(vertexCounter + 1);
}

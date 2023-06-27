

void GameLogic(Assignment07 *A, float Ar, glm::mat4 &ViewPrj, glm::mat4 &World) {
	// The procedure must implement the game logic  to move the character in third person.
	// Input:
	// <Assignment07 *A> Pointer to the current assignment code. Required to read the input from the user
	// <float Ar> Aspect ratio of the current window (for the Projection Matrix)
	// Output:
	// <glm::mat4 &ViewPrj> the view-projection matrix of the camera
	// <glm::mat4 &World> the world matrix of the object
	// Parameters
	// Camera FOV-y, Near Plane and Far Plane
	const float FOVy = glm::radians(45.0f);
	const float nearPlane = 0.1f;
	const float farPlane = 100.f;
	
	// Player starting point
	const glm::vec3 StartingPosition = glm::vec3(-41.50, 0.0, -19.5);

	// Camera target height and distance
	const float camHeight = 0.25;
	const float camDist = 1.5;
	// Camera Pitch limits
	const float minPitch = glm::radians(-8.75f);
	const float maxPitch = glm::radians(60.0f);
	// Rotation and motion speed
	const float ROT_SPEED = glm::radians(120.0f);
	const float MOVE_SPEED = 2.0f;

	// Integration with the timers and the controllers
	// returns:
	// <float deltaT> the time passed since the last frame
	// <glm::vec3 m> the state of the motion axes of the controllers (-1 <= m.x, m.y, m.z <= 1)
	// <glm::vec3 r> the state of the rotation axes of the controllers (-1 <= r.x, r.y, r.z <= 1)
	// <bool fire> if the user has pressed a fire button (not required in this assignment)
	float deltaT;
	glm::vec3 m = glm::vec3(0.0f), r = glm::vec3(0.0f);
	bool fire = false;
	A->getSixAxis(deltaT, m, r, fire);

	// Game Logic implementation
	// Current Player Position - static variables make sure that their value remain unchanged in subsequent calls to the procedure
	static glm::vec3 playerPosition = StartingPosition, oldPos = StartingPosition, newPos = StartingPosition, newPos2 = StartingPosition;

	// To be done in the assignment
	glm::mat4 ViewMatrix, ProjectionMatrix, WorldMatrix;

	const float LAMBDAROT = 20.0f, 
				LAMBDAMOV = 10.0f, 
				DEADZONE = 0.2f;

	static bool updatePos = false;

	static float yaw = 0.0f,    pitch = 0.0f, roll = 0.0f,
				 yawOld = 0.0f, pitchOld = 0.0f,
				 yawNew = 0.0f, pitchNew = 0.0f,  
				 playerYaw = 0.0f, playerYawOld = 0.0;

	// computing angles
	pitch -= ROT_SPEED * r.x * deltaT;
	pitch = pitch < minPitch ? minPitch :
		(pitch > maxPitch ? maxPitch : pitch);
	yaw -= ROT_SPEED * r.y * deltaT;
	roll += ROT_SPEED * r.z * deltaT;

	// computing the versors and updating the player position
	glm::vec3 ux = glm::vec3(glm::rotate(glm::mat4(1),
		yaw, glm::vec3(0, 1, 0)) *
		glm::vec4(1, 0, 0, 1));
	glm::vec3 uy = glm::vec3(0, 1, 0);
	glm::vec3 uz = glm::vec3(glm::rotate(glm::mat4(1),
		yaw, glm::vec3(0, 1, 0)) *
		glm::vec4(0, 0, -1, 1));
	playerPosition += ux * MOVE_SPEED * m.x * deltaT;
	playerPosition += uz * MOVE_SPEED * m.z * deltaT;
	// blocking the player from going under the terrain
	if ((playerPosition + uy * MOVE_SPEED * m.y * deltaT).y < 0.0f) {
		playerPosition.y = 0.0f;
	}
	else
	{
		playerPosition += uy * MOVE_SPEED * m.y * deltaT;
	}
	
	
	// damping implementation
	pitchNew = (pitchOld * exp(-LAMBDAROT * deltaT)) + pitch * (1 - exp(-LAMBDAROT * deltaT));
	pitchOld = pitchNew;

	yawNew = (yawOld * exp(-LAMBDAROT * deltaT)) + yaw * (1 - exp(-LAMBDAROT * deltaT));
	yawOld = yawNew;
	
	// deadzone implementation
	if (glm::length((playerPosition-oldPos)) > DEADZONE) {
		updatePos = true;
	}

	if (updatePos) {
		newPos = (oldPos * exp(-LAMBDAMOV * deltaT)) + playerPosition * (1 - exp(-LAMBDAMOV * deltaT));
		oldPos = newPos;
		if (oldPos == playerPosition) {
			updatePos = false;
		}
	}
	
	// player rotating independently from the camera
	if (m.x != 0 || m.z != 0)
		playerYaw = yaw + (atan2(m.z, m.x) - glm::radians(90.0f));
	playerYawOld = playerYaw;
	
	// World Matrix
	WorldMatrix = 
		glm::translate(glm::mat4(1), playerPosition) *
		glm::mat4(glm::quat(glm::vec3(0, playerYaw, 0))) *
		glm::scale(glm::mat4(1), glm::vec3(1));
	World = WorldMatrix;

	// World Matrix used for the camera
	WorldMatrix = glm::translate(glm::mat4(1), oldPos) *
		glm::mat4(glm::quat(glm::vec3(0, yawNew, 0))) *
		glm::scale(glm::mat4(1), glm::vec3(1));

	// calculating the View-Projection Matrix
	glm::vec3 cameraPosition;
	glm::vec4 temp = WorldMatrix * glm::vec4(0, camHeight + (camDist * sin(pitchNew)), camDist * cos(pitchNew), 1);
	cameraPosition = glm::vec3(temp.x, temp.y, temp.z);

	glm::vec3 targetPointedPosition;
	targetPointedPosition = glm::vec3(newPos.x, newPos.y + camHeight, newPos.z);

	ViewMatrix = glm::lookAt(cameraPosition, targetPointedPosition, glm::vec3(0, 1, 0));
	ViewMatrix = glm::rotate(glm::mat4(1), roll, glm::vec3(0,0,1)) * ViewMatrix;

	ProjectionMatrix = glm::perspective(FOVy, Ar, nearPlane, farPlane);
	ProjectionMatrix[1][1] *= -1;

	ViewPrj = ProjectionMatrix * ViewMatrix;
}

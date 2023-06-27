

void SetupMatrices(Assignment03 *A) {
/**************
 Method Matrix(int N, glm::mat4 M) of object A,
 receives in N the number of the matrix that needs to be set, and the matrix in M
***************/

	glm::mat4 S, TraslationMatrix, RotationMatrix, TraslationMatrix2, ScalingMatrix, ID;

	ID = glm::mat4(1);
	
	// To solve the puzzle: scale 2x proportionally, centered in (2,0,-3)
	
	/*S = glm::mat4(1);
	S = glm::translate(S, glm::vec3(2,0,-3));
	S = glm::scale(S, glm::vec3(2,2,2));
	S = glm::translate(S, glm::vec3(-2, 0, 3));*/
	
	TraslationMatrix = glm::translate(ID, glm::vec3(2,0,-3));
	ScalingMatrix = glm::scale(ID, glm::vec3(2, 2, 2));

	S = TraslationMatrix * ScalingMatrix * glm::inverse(TraslationMatrix);

	A->Matrix(1, S); // sets the matrix corresponding to piece 1

	// To solve the puzzle: scale 3x on an axis oriented 45 degrees between the x and z axis and passing through point (1,0,0)

	/*S = glm::mat4(1);
	S = glm::translate(S, glm::vec3(1,0,0));
	S = glm::rotate(S, glm::radians(45.0f), glm::vec3(0, 1, 0));
	S = glm::scale(S, glm::vec3(3,1,1));
	S = glm::rotate(S, glm::radians(-45.0f), glm::vec3(0, 1, 0));
	S = glm::translate(S, glm::vec3(-1, 0, 0));*/

	TraslationMatrix = glm::translate(ID, glm::vec3(1.0f, 0.0f, 0.0f));
	RotationMatrix = glm::rotate(ID, glm::radians(45.0f), glm::vec3(0, 1, 0));
	ScalingMatrix = glm::scale(ID, glm::vec3(3, 1, 1));

	S = TraslationMatrix * RotationMatrix * ScalingMatrix * glm::inverse(RotationMatrix) * glm::inverse(TraslationMatrix);

	A->Matrix(2, S); // sets the matrix corresponding to piece 2

	// To solve the puzzle: find it yourself! Hint: compose a rotation around an arbitrary point with a translation

	// Move the piece in the right place, then apply a normal rotation (traslation to the center, rotation, inverse of translation)

	TraslationMatrix = glm::translate(ID, glm::vec3(-1,0,-1));
	TraslationMatrix2 = glm::translate(ID, glm::vec3(-1,0,-2));
	RotationMatrix = glm::rotate(ID, glm::radians(45.0f), glm::vec3(0,1,0));

	S = glm::inverse(TraslationMatrix2) * RotationMatrix * TraslationMatrix2 * TraslationMatrix;

	A->Matrix(3, S); // sets the matrix corresponding to piece 3

	// To solve the puzzle: rotate 60 degree around the y axis, centered in (-1,0,-2)

	/*S = glm::mat4(1);
	S = glm::translate(S, glm::vec3(-1,0,-2));
	S = glm::rotate(S, glm::radians(60.0f), glm::vec3(0,1,0));
	S = glm::translate(S, glm::vec3(1,0,2));*/

	TraslationMatrix = glm::translate(ID, glm::vec3(-1,0,-2));
	RotationMatrix = glm::rotate(ID, glm::radians(60.0f), glm::vec3(0, 1, 0));

	S = TraslationMatrix * RotationMatrix * glm::inverse(TraslationMatrix);

	A->Matrix(4, S); // sets the matrix corresponding to piece 4

	// To solve the puzzle: rotate -90 degree around an arbitrary axis passing in (-1,0,0). 
	// The x axis can be aligned to this arbitrary direction with a rotation of -45 around the y axis.

	/*S = glm::mat4(1);
	S = glm::translate(S, glm::vec3(-1,0,0));
	S = glm::rotate(S, glm::radians(-45.0f), glm::vec3(0,1,0));
	S = glm::rotate(S, glm::radians(-90.0f), glm::vec3(1,0,0));
	S = glm::rotate(S, glm::radians(45.0f), glm::vec3(0,1,0));
	S = glm::translate(S, glm::vec3(1, 0, 0));*/

	TraslationMatrix = glm::translate(ID, glm::vec3(-1,0,0));
	RotationMatrix = glm::rotate(ID, glm::radians(-45.0f), glm::vec3(0, 1, 0));
	TraslationMatrix2 = glm::rotate(ID, glm::radians(-90.0f), glm::vec3(1, 0, 0));

	S = TraslationMatrix * RotationMatrix * TraslationMatrix2 * glm::inverse(RotationMatrix) * glm::inverse(TraslationMatrix);

	A->Matrix(5, S); // sets the matrix corresponding to piece 5

	// To solve the puzzle: find it yourself! Hint: compose a non-proportional scaling that 
	// halves the object along one of the main axes, centered in an arbitrary point, with a translation

	/*S = glm::mat4(1);
	S = glm::scale(S, glm::vec3(0.5,1,1));
	S = glm::translate(S, glm::vec3(1,0,0));*/

	ScalingMatrix = glm::scale(ID, glm::vec3(0.5, 1, 1));
	TraslationMatrix = glm::translate(ID, glm::vec3(1,0,0));

	S = ScalingMatrix * TraslationMatrix;

	A->Matrix(6, S); // sets the matrix corresponding to piece 6
	
}

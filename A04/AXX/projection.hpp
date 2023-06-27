
glm::mat4 RotationX(float x) {
	x = glm::radians(x);
	return glm::rotate(glm::mat4(1), x, glm::vec3(1, 0, 0));
	//return glm::mat4(1,0,0,0, 0,cos(x),-sin(x),0, 0,sin(x),cos(x),0, 0,0,0,1);
}

glm::mat4 RotationY(float x) {
	x = glm::radians(x);
	return glm::rotate(glm::mat4(1), x, glm::vec3(0, 1, 0));
	//return glm::mat4(cos(x),0,sin(x),0, 0,1,0,0, -sin(x),0,cos(x),0, 0,0,0,1);
}

void SetupProjectionMatrices(Assignment04 *A, float Ar) {
/**************
 Method Matrix(int N, glm::mat4 M) of object A,
 receives in N the number of the matrix that needs to be set, and the matrix in M
***************/

	glm::mat4 S, Orthogonal, Cabinet;
	float w = 10.0f;

	Orthogonal = glm::ortho(-w,w,-(w/Ar),(w/Ar), -50.0f, 50.0f);
	Orthogonal = glm::scale(glm::mat4(1.0f), glm::vec3(1, -1, 1)) * Orthogonal;

	// Isometric projection
	S = Orthogonal * RotationX(35.26f) * RotationY(-45.0f);

	A->Matrix(1, S); // sets the matrix corresponding to piece 1

	// Dimetric
	S = Orthogonal * RotationX(60.0f) * RotationY(-45.0f);

	A->Matrix(2, S); // sets the matrix corresponding to piece 2

	// Trimetric
	S = Orthogonal * RotationX(20.0f) * RotationY(-70.0f);

	A->Matrix(3, S); // sets the matrix corresponding to piece 3

	// Cabinet
	float reductionFactor = 0.5f;
	float angle = glm::radians(30.0f);
	Cabinet = glm::mat4(1,0,0,0, 0,1,0,0, -reductionFactor * cos(angle), -reductionFactor * sin(angle),1,0, 0,0,0,1);

	S = Orthogonal * Cabinet;

	A->Matrix(4, S); // sets the matrix corresponding to piece 4

}


void SetupProjectionMatrices(Assignment05 *A, float Ar) {
/**************
 Method Matrix(int N, glm::mat4 M) of object A,
 receives in N the number of the matrix that needs to be set, and the matrix in M
***************/

	glm::mat4 PerspectiveProjectionMatrix, PerspectiveProjectionMatrix2, PerspectiveProjectionMatrix3, PerspectiveProjectionMatrix4;
	
	
	// Fov-y = 60 deg

	float n = 0.1f, f = 50.0f, t, b, l, r, angle, tang;

	angle = glm::radians(60.0f);
	tang = tan(angle / 2);
	
	t = n * tang;
	b = -n * tang;
	l = -Ar * n * tang;
	r = Ar * n * tang;

	// matrice semplificata
	PerspectiveProjectionMatrix = glm::mat4(1/(Ar*tang),0,0,0,  0,-1/tang,0,0,  0,0,f/(n-f),-1,  0,0,(n*f)/(n-f),0);
	// matrice non semplificata
	PerspectiveProjectionMatrix2 = glm::mat4((2*n)/(r-l),0,0,0,  0,2*n/(b-t),0,0,  (r+l)/(r-l),(t+b)/(b-t),f/(n-f),-1,  0,0,(n*f)/(n-f),0);
	// perspective function
	PerspectiveProjectionMatrix3 = glm::perspective(angle, Ar, n, f);
	PerspectiveProjectionMatrix3[1][1] *= -1;
	// frustum function
	PerspectiveProjectionMatrix4 = glm::scale(glm::mat4(1.0f), glm::vec3(1,-1,1)) * glm::frustum(l, r, b, t, n, f);

	A->Matrix(1, PerspectiveProjectionMatrix4); // sets the matrix corresponding to piece 1


	// Fov-y = 105 deg

	angle = glm::radians(45.0f);

	// perspective function
	PerspectiveProjectionMatrix = glm::perspective(angle, Ar, n, f);
	PerspectiveProjectionMatrix[1][1] *= -1;

	A->Matrix(2, PerspectiveProjectionMatrix); // sets the matrix corresponding to piece 2


	// Fov-y = 25 deg

	angle = glm::radians(25.0f);

	// perspective function
	PerspectiveProjectionMatrix = glm::perspective(angle, Ar, n, f);
	PerspectiveProjectionMatrix[1][1] *= -1;

	A->Matrix(3, PerspectiveProjectionMatrix); // sets the matrix corresponding to piece 3


	// Right View, Fov-y = 45 deg
	
	// standard solution

	angle = glm::radians(45.0f);
	tang = tan(angle/2);

	t = n * tang;
	b = -n * tang;
	l = 0.0f;
	r = Ar * n * tang * 2;

	PerspectiveProjectionMatrix = glm::frustum(l, r, b, t, n, f);
	PerspectiveProjectionMatrix = glm::scale(glm::mat4(1.0), glm::vec3(1, -1, 1)) * PerspectiveProjectionMatrix;

	A->Matrix(4, PerspectiveProjectionMatrix);

	// second solution: Fov-x = 45 deg

	angle = glm::radians(45.0f);
	tang = tan(angle/2);

	t = (n * tang) / Ar;
	b = (- n * tang) / Ar;
	l = 0.0f;
	r = n * tang * 2;

	PerspectiveProjectionMatrix2 = glm::frustum(l,r,b,t,n,f);
	PerspectiveProjectionMatrix2 = glm::scale(glm::mat4(1.0), glm::vec3(1, -1, 1)) * PerspectiveProjectionMatrix2;


	A->Matrix(4, PerspectiveProjectionMatrix2); // sets the matrix corresponding to piece 4

}

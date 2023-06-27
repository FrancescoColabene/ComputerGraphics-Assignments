

void SetupTriangles(Assignment01 *A) {
/**************
 Function Triangle(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b)

 draws a triangle connecting points (x1,y1)  (x2, y2) and (x3, y3), colored with the (r,g,b) specified color.
 vertex are expressed in Normalized screen coordinates, (i.e. in range [-1,+1]), following the Vulkan convention.
 The red, green and blue (r,g,b) values are in the range [0,1].
 
 Using function Triangle(...) try to draw a children house, similar to the one below.
 
 First remove the two function below (given only as an example), and replace them with your own.
 Since it is a C program, you can use for loops if you think it can be helpful in your drawing.
 The for() command below that draws a sun like shape in exact center of the screen near the top,
 is an example on how you can use it: please remove it, and replace it with your own code.
 It is not necessery to use a for loop if you do not really need it: it has been put here only as
 an example to help students not familiar with C++.
***************/

	A->Triangle(0.12,-0.92, 0.3,-0.67, 0.12,-0.42, 1,0.5,0.5);

	A->Triangle(0.49,-0.92, 0.31, -0.67, 0.49, -0.42, 0.2,0.7,1);

	A->Triangle(0.305,-0.67, 0.12,-0.41, 0.305,-0.16, 0.5,0,0.5);
	A->Triangle(0.305,-0.67, 0.49,-0.41, 0.305,-0.16, 0.5,0,0.5);

	A->Triangle(0.12,-0.40, 0.38,-0.055, 0.12,0.31, 0.9,0.9,0);

	A->Triangle(0.115, -0.40, -0.26, 0.1, 0.115, 0.64, 0.8,0,0);

	A->Triangle(-0.26,0.11, 0.25,0.84, -0.26,0.84, 0,0.6,1);

	A->Triangle(-0.268,0.84, -0.64,0.84, -0.44,0.59, 0.4,0.7,0);
	A->Triangle(-0.81,0.59, -0.64,0.84, -0.44,0.59, 0.4,0.7,0);
}

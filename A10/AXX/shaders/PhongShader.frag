#version 450#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragPos;layout(location = 1) in vec3 fragNorm;layout(location = 2) in vec2 fragUV;

layout(location = 0) out vec4 outColor;

layout(set = 0, binding = 1) uniform GlobalUniformBufferObject {
	float time;} gubo;

void main() {
	vec3 Norm = fragNorm;		float y = fragPos.y;	float t = gubo.time;	float r = 0.0f, g = 0.0f, b = 0.0f;
	/***** Insert the code here to compute the correct value of r, g and b ****/	float h = mod((t/3) + y, 6);	if(h < 1) 				 { r=1.0f; 	   g=h; 	   b=0.0f;}	else if(h < 2 && h >= 1) { r=2.0f - h; g=1.0f; 	   b=0.0f;}	else if(h < 3 && h >= 2) { r=0.0f; 	   g=1.0f;	   b=h - 2.0f;}	else if(h < 4 && h >= 3) { r=0.0f; 	   g=4.0f - h; b=1.0f;}	else if(h < 5 && h >= 4) { r=h - 4.0f; g=0.0f; 	   b=1.0f;}	else if(h >= 5) 		 { r=1.0f; 	   g=0.0f; 	   b=6.0f-h;}		/***** Leave it as is from this point on ****/		outColor = vec4(r, g, b, 1.0);}
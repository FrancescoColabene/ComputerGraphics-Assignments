#version 450#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragPos;layout(location = 1) in vec3 fragNorm;layout(location = 2) in vec2 fragUV;

layout(location = 0) out vec4 outColor;layout(binding = 1) uniform sampler2D tex;

layout(binding = 2) uniform GlobalUniformBufferObject {
	vec3 lightDir;
	vec4 lightColor;
	vec3 eyePos;
} gubo;

vec3 BRDF(vec3 V, vec3 N, vec3 L, vec3 Md, float sigma) {	//vec3 V  - direction of the viewer	//vec3 N  - normal vector to the surface	//vec3 L  - light vector (from the light model) direction of the light	//vec3 Md - main color of the surface	//float sigma - Roughness of the model		float theta1 = acos(dot(L,N));	float theta2 = acos(dot(N,V));	float alpha = max(theta1, theta2);	float beta = min(theta1, theta2);	float A = 1 - (0.5 * (pow(sigma,2)/(pow(sigma,2)+0.33)));	float B = 0.45 * (pow(sigma,2)/(pow(sigma,2)+0.09));	vec3 vi = normalize(L - (dot(L,N)) * N );	vec3 vr = normalize(V - (dot(V,N)) * N );	float G = max(0, dot(vi,vr));	vec3 tempL = Md * clamp(dot(L,N), 0.0, 1.0);		vec3 res = tempL * (A + B * G * sin(alpha) * tan(beta));	return res;}void main() {	vec3 Norm = normalize(fragNorm);	vec3 EyeDir = normalize(gubo.eyePos - fragPos);		vec3 lightDir = gubo.lightDir;	vec3 lightColor = gubo.lightColor.rgb;	vec3 DiffSpec = BRDF(EyeDir, Norm, lightDir, texture(tex, fragUV).rgb, 1.1f);	vec3 Ambient = texture(tex, fragUV).rgb * 0.05f;		outColor = vec4(clamp(0.95 * (DiffSpec) * lightColor.rgb + Ambient,0.0,1.0), 1.0f);}
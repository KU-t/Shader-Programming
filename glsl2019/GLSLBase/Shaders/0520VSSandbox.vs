#version 450

layout(location = 0) in vec3 a_Position; 
const float PI = 3.141592;

uniform float uTime;

void main()
{
	vec3 newPos = a_Position;

	float newx = 2;
	newPos.x *= newx;

	float newy = 0.5 * sin(2*PI*(newPos.x + 0.5) + uTime);
	newPos.y += newy;

	gl_Position = vec4(newPos,1);
}
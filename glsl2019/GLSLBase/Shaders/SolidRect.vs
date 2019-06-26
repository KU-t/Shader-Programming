#version 450

#define rad(x) x * 3.141592 / 180

layout(location = 0) in vec4 a_Position; // x,y,z,value
layout(location = 1) in vec4 a_Color; // r,g,b,a

out vec4 v_Color;

uniform float u_Time;	// 1.f

void main()
{
	vec3 temp;
	vec3 movecircle;
	float Time = u_Time;
	
	v_Color = a_Color;

	temp = a_Position.xyz;
	temp.x -= 0.5;

	//temp.x += 0.5 * cos(rad(Time));
	//temp.y += 0.5 * sin(rad(Time));

	gl_Position = vec4(temp, 1); // a_Position이면 통채로 넘어감
}

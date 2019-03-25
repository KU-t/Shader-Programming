#version 450

#define rad(x) x * 3.141592 / 180

layout(location = 0) in vec4 a_Position; // x,y,z,value
//layout(location = 0) in vec3 a_Position;	// x,y,z

layout(location = 1) in vec4 a_Color; // r,g,b,a

uniform float u_Time;	// 1.f

void main()
{
	vec3 temp;
	vec3 movecircle;

	temp = a_Position.xyz;

	temp.x += 0.5 * cos(rad(u_Time));
	temp.y += 0.5 * sin(rad(u_Time));

	//gl_Position = vec4(a_Position * 1.0, 1);	//rectangle  화면에 보이는 비율
	//gl_Position = vec4(temp, 1); // a_Position이면 통채로 넘어감
}

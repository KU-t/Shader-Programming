#version 450
//190325
//vertex shader에서 적용되는 연산은 모든 vertex에 수행

in vec3 a_Position;	// x,y,z
in vec3 a_Vel;

uniform float u_Time;

void main()
{
	vec3 newPos = a_Position.xyz;

	float newTime = fract(u_Time);	
	// fract() == 소수점을 떼는 함수 -> 0 ~ 1

	newPos += 0.0001 * a_Vel * u_Time;

	gl_Position = vec4(newPos.xyz, 1); // a_Position이면 통채로 넘어감
}

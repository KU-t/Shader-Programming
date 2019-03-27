#version 450
//190325
//vertex shader���� ����Ǵ� ������ ��� vertex�� ����

in vec3 a_Position;	// x,y,z
in vec3 a_Vel;

uniform float u_Time;

void main()
{
	vec3 newPos = a_Position.xyz;

	float newTime = fract(u_Time);	
	// fract() == �Ҽ����� ���� �Լ� -> 0 ~ 1

	newPos += 0.0001 * a_Vel * u_Time;

	gl_Position = vec4(newPos.xyz, 1); // a_Position�̸� ��ä�� �Ѿ
}

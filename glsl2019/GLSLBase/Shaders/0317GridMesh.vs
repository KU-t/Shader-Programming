#version 450

layout(location = 0) in vec4 a_Position; // x,y,z,value

void main()
{

	gl_Position = vec4(a_Position);	//rectangle  ȭ�鿡 ���̴� ����
}

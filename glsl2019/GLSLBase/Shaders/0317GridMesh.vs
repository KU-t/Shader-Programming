#version 450

layout(location = 0) in vec4 a_Position; // x,y,z,value

void main()
{

	gl_Position = vec4(a_Position);	//rectangle  화면에 보이는 비율
}

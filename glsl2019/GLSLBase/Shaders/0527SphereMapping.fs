#version 450

in float v_Grey;

out vec4 FragColor;


void Wave(){
	FragColor = vec4(1, 1, 1, 1)* v_Grey;
}

void SphereMapping(){
	FragColor = vec4(1, 1, 1, 1);
}

void main()
{
	Wave();
	
	//SphereMapping();
}

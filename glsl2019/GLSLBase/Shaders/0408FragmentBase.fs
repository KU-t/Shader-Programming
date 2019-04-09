#version 450

layout(location=0) out vec4 FragColor;

in vec4 v_Color;
in vec2 v_Orixy;
in float v_Radius;

void main(){

	vec4 newColor = v_Color;

	float dis = sqrt((v_Orixy.x * v_Orixy.x) + (v_Orixy.y * v_Orixy.y));
	if(dis < v_Radius)	{
		newColor.a = pow(1 - dis / v_Radius, 2);
	}
	else
		newColor.a = 0.f;
	FragColor = newColor;	// RGBA
}

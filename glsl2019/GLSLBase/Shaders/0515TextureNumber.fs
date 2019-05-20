#version 450

in vec2 vTexPos;

out vec4 FragColor;

uniform sampler2D uTexSampler;

uniform int uNumber;

void main()
{
	vec2 newTex = vTexPos;
	float newy = float(uNumber);
	newTex.y = newTex.y/10.0 + newy/10.0; // texture위치 + 처음위치
    FragColor = texture(uTexSampler, newTex);
	
}

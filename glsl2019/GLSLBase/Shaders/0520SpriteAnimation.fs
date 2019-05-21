#version 450

in vec2 vTexPos;

out vec4 FragColor;

uniform sampler2D uTexSampler;

uniform float uNumber;
uniform float uResolX;
uniform float uResolY;

void main()
{
	vec2 newTex;

	float x_index = floor(fract(uNumber / uResolX) * uResolX);
	float y_index = floor(floor(uNumber / uResolX));
	
	// tex coord
	newTex.x = vTexPos.x / uResolX + x_index / uResolX; //이미지 x크기 + x-offset
	newTex.y = vTexPos.y / uResolY + y_index / uResolY; //이미지 y크기 + y-offset

	FragColor = texture(uTexSampler, vec2(newTex.x, newTex.y));
}

#version 450

in vec2 vTexPos;

out vec4 FragColor;

uniform float uTime;

uniform sampler2D uTexSampler;

void main()
{
    vec2 newTexPos = vec2(vTexPos.x, uTime/6.0 + vTexPos.y/6.0); // 처음위치 + texture위치
    FragColor = texture(uTexSampler, newTexPos);
	
}

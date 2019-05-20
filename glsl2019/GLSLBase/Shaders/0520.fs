#version 450

in vec2 vTexPos;

out vec4 FragColor;

uniform sampler2D uTexSampler;

uniform int uNumber[3];

void main()
{
	vec2 newTex = vTexPos;
	// x_tex coord
	newTex.x = fract(vTexPos.x * 3.0); // 가로 3개
	
	//cal index
	int newindex = int(floor(vTexPos.x * 3.0)); // 가로 3개의 index

	float newy = 9.0 - float(uNumber[newindex]); // index를 찾아서 y축의 기준으로
	newTex.y = newTex.y/10.0 + newy/10.0;	// newy(index)에서 원래만큼 더해
    
	FragColor = texture(uTexSampler, newTex);
}

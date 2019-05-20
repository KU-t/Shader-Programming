#version 450

in vec2 vTexPos;

out vec4 FragColor;

uniform sampler2D uTexSampler;

uniform int uNumber[3];

void main()
{
	vec2 newTex = vTexPos;
	// x_tex coord
	newTex.x = fract(vTexPos.x * 3.0); // ���� 3��
	
	//cal index
	int newindex = int(floor(vTexPos.x * 3.0)); // ���� 3���� index

	float newy = 9.0 - float(uNumber[newindex]); // index�� ã�Ƽ� y���� ��������
	newTex.y = newTex.y/10.0 + newy/10.0;	// newy(index)���� ������ŭ ����
    
	FragColor = texture(uTexSampler, newTex);
}

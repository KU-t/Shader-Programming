#version 450

in vec2 v_UV;

out vec4 FragColor;

uniform sampler2D uTexSampler;
uniform float uTime;

const int imagex = 6;
const int imagey = 5;

void main()
{
	float newtime = uTime;
	int newindexx = int(newtime) % imagex;
	int newindexy = int(newtime) / imagex;

	vec2 newTex = v_UV;

	float newx = float(newindexx);
	newTex.x = newTex.x / imagex + newx / imagex;

	float newy = float(imagey) - float(newindexy); // index�� ã�Ƽ� y���� ��������
	newTex.y = 1.0 - (newTex.y / imagey + newy / imagey);	// newy(index)���� ������ŭ ����
    
	FragColor = texture(uTexSampler, newTex);
}

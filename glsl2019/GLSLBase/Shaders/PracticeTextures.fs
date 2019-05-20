#version 450

in vec2 v_UV;

out vec4 FragColor;

uniform sampler2D uTexSampler;

void main()
{
	vec2 newUV;
	
	int newindexX = int(floor(v_UV.x * 2 ));
	int newindexY = int(floor(v_UV.y * 5 ));
	
	newUV.x = fract(v_UV.x * 2.0);

	float newy = 9.0 - float(newindexX + newindexY * 2);
	newUV.y = fract((v_UV.y / 10.0 + newy / 10.0) * 5.0);

	FragColor = texture(uTexSampler, newUV);
}

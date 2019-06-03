#version 450

in float v_color;
in vec2 v_Tex;

out vec4 FragColor;
in float v_Grey;

uniform sampler2D u_Texture;
uniform sampler2D u_TextureSnow;
uniform sampler2D u_TextureSGrass;

void main()
{
	vec4 snowColor = texture(u_TextureSnow,v_Tex * 10) * v_Grey;
	vec4 grassColor = texture(u_TextureSGrass,v_Tex * 10) * (1 - v_Grey);
	vec4 finalColor = snowColor + grassColor;

	//FragColor = texture(u_Texture,vec2(v_Tex.x, 1.0 - v_Tex.y));
	//FragColor = vec4(1.f,1.f,1.f,1.f);

	FragColor = finalColor;
}

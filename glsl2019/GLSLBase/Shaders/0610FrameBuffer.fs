#version 450

layout(location=0) out vec4 FragColor;

uniform sampler2D u_Texture;
uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;
uniform sampler2D u_Texture3;

in vec2 v_Tex;

uniform float u_Time;

void main()
{
	//default
	vec2 newTex = v_Tex;
	vec4 newColor = texture(u_Texture, newTex);
	FragColor = newColor;
}

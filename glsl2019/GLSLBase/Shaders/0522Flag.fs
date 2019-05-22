#version 450

in float v_color;
in vec2 v_Tex;

out vec4 FragColor;

uniform sampler2D u_Texture;

void main()
{
	float newcolor = v_color;
	//FragColor = vec4(0,0,newcolor,1);	// RGBA
	FragColor = texture(u_Texture,vec2(v_Tex.x, 1.0 - v_Tex.y));
}

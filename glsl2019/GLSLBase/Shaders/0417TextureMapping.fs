#version 450

layout(location=0) out vec4 FragColor;

const float PI = 3.141592;

in vec2 v_UV;

uniform sampler2D u_Texture;
uniform float u_Time;

void main(){
	
	vec4 newcolor = vec4(v_UV,0,1);

	float rad = sin((v_UV.x + u_Time) * 2 * PI);

	if(0.5 * rad + 0.495 > v_UV.y || v_UV.y > 0.5 * rad + 0.505){
		newcolor = vec4(0);
	}

	FragColor = newcolor;
	//FragColor = texture(u_Texture,v_UV);
}

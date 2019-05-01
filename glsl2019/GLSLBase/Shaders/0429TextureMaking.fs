#version 450

uniform sampler2D u_Texture;
in vec2 v_UV;
uniform float u_Time;
out vec4 FragColor;

void main(){
	//좌표로 노는거 시험내기 너무좋아
	//vec2 newUV = fract(2 * v_UV);
	//vec2 newUV = fract(2 * v_UV + vec2(u_Time, sin(u_Time) ) );

	vec2 newUV = abs(v_UV - vec2(0, 0.5)) + vec2(0, 0.5) + vec2(0, 0.5);

	//vec2 newUV = v_UV;
	//if(newUV.x > 0.5) 	newUV.x = 1.0 - newUV.x;
	//if(newUV.y > 0.5) 	newUV.y = 1.0 - newUV.y;

	//vec4 newColor = vec4(newUV, 0, 0);
	//FragColor = newColor;

	FragColor = texture(u_Texture,newUV);
}

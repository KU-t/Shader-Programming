#version 450

uniform sampler2D u_Texture;
in vec2 v_UV;
uniform float u_Time;
out vec4 FragColor;

void main(){
	
	/*vec2 newUV = v_UV;
	vec4 newColor = texture(u_Texture, newUV);
	FragColor = newColor;*/

	/*float s = 4;
	vec2 newUV[5];
	vec4 newColor[5];

	newUV[0] = vec2(v_UV.x, v_UV.y);
	newUV[1] = vec2(v_UV.x - 1 / s, v_UV.y);
	newUV[2] = vec2(v_UV.x + 1 / s, v_UV.y);
	newUV[3] = vec2(v_UV.x, v_UV.y - 1 / s);
	newUV[4] = vec2(v_UV.x, v_UV.y - 1 / s);

	newColor[0] = texture(u_Texture, newUV[0]);
	newColor[1] = texture(u_Texture, newUV[1]);
	newColor[2] = texture(u_Texture, newUV[2]);
	newColor[3] = texture(u_Texture, newUV[3]);
	newColor[4] = texture(u_Texture, newUV[4]);
	
	vec4 finalColor = newColor[0] + newColor[1] + newColor[2] + newColor[3] + newColor[4];
	finalColor /= 5;
	FragColor = finalColor;*/

	//1
	//vec2 newUV = vec2(v_UV.x, 2 * abs(v_UV.y - 0.5));

	//2
	/*vec2 newUV;
	newUV.x = fract(v_UV.x * 3.0);
	newUV.y = v_UV.y / 3.0;	// 0 ~ 1/3
	newUV.y += floor(v_UV.x * 3.0) / 3.0;*/

	//3
	/*vec2 newUV;
	newUV.x = fract(v_UV.x * 3.0);
	newUV.y = v_UV.y / 3.0;	// 0 ~ 1/3
	newUV.y += floor((1 - v_UV.x) * 3.0) / 3.0;
	// == newUV.y += (2 - floor(v_UV.x * 3.0)) / 3.0;
	*/

	//4
	vec2 newUV;
	newUV.x = v_UV.x;
	newUV.y = (2 - floor( v_UV.y * 3.0)) / 3;	// 2/3, 1/3, 0/3
	newUV.y += fract( v_UV.y * 3.0) / 3.0;
	
	//5


	FragColor = texture(u_Texture,newUV);
}

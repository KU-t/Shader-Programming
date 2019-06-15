#version 450

layout(location=0) out vec4 FragColor;

uniform sampler2D u_Texture;


in vec2 v_Tex;

uniform float u_Time;
uniform float u_Blursize;
uniform vec2 u_Texelsize;

void main()
{	
	float size = u_Blursize / 2.0;
	vec2 xDir = vec2(1.0, 0.0);
	vec2 yDir = vec2(0.0, 1.0);
	vec3 newColor = vec3(0.0, 0.0, 0.0);
	float count = 0.0;
	float Maxdistance = length(size * vec2(1.0, 0.0) * u_Texelsize);

	for(float x = -size; x <size ; x+=1.0){
		for(float y = -size; y < size; y+=1.0){
			// 샘플링 되는 새로운 위치
			vec2 newTex = v_Tex + x * xDir * u_Texelsize + y * yDir * u_Texelsize;
			float distance = length(newTex - v_Tex);
			float add = clamp(1.0 - distance / Maxdistance, 0.f, 1.f);

			vec4 temp = texture(u_Texture,newTex);
			temp = clamp(temp -  vec4(1.0), 0.0, 100.0);
			newColor += temp.rgb * add;

			//blur가 얼마나 짙은지
			count += 0.2f;
		}
	}

	FragColor = vec4(newColor/count + texture(u_Texture, v_Tex).rgb, 1.0);

	//default
	//vec2 newTex = v_Tex;
	//vec4 newColor = texture(u_Texture, newTex);
	//FragColor = newColor;
}

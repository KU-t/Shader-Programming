#version 450

const float PI = 3.141592;

in vec3 a_Position; 

out vec3 v_Pos;
out vec2 v_Tex;
out float v_Grey;
out vec3 v_Norm;

uniform float uTime;
uniform mat4 u_ProjView;
uniform sampler2D u_TextureHeight;

void main()
{

	float gap = 10.0 / 100.0;

	// 0 ~ 1
	vec2 newUV = vec2(0.5) + a_Position.xy; 

	// right¿¡ ÀÖ´Â ÁÂÇ¥
	vec2 newUVRight = vec2(0.5) + a_Position.xy + vec2(gap, 0.0); 

	// up¿¡ ÀÖ´Â ÁÂÇ¥
	vec2 newUVUp = vec2(0.5) + a_Position.xy + vec2(0.0, gap);

	float newHeight = texture(u_TextureHeight, newUV).r;
	float newHeightRight = texture(u_TextureHeight, newUVRight).r;
	float newHeightUp = texture(u_TextureHeight, newUVUp).r;

	vec3 newPos = vec3(a_Position.xy,a_Position.z + newHeight * 0.5);
	vec3 newPosRight = vec3(a_Position.xy + vec2(gap, 0.0) ,a_Position.z + newHeightRight * 0.5);
	vec3 newPosUp = vec3(a_Position.xy + vec2(0.0, gap) ,a_Position.z + newHeightUp * 0.5);

	vec3 ToRightvec = newPosRight - newPos;
	vec3 ToUpvec = newPosUp - newPos;

	vec3 norm = cross(ToRightvec, ToUpvec);

	float alpha = fract(uTime / 10.0) * 2 * PI;

	mat4 Spin = mat4(
				cos(alpha), sin(alpha), 0, 0,
				-sin(alpha), cos(alpha), 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);

	gl_Position = u_ProjView * vec4(newPos,1.f);
	v_Grey = newHeight;
	v_Tex = newUV;
	v_Norm = normalize(norm);
	v_Pos = a_Position;
}
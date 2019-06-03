#version 450

const float PI = 3.141592;

in vec3 a_Position; 
out vec2 v_Tex;
out float v_Grey;

uniform float uTime;
uniform mat4 u_ProjView;
uniform sampler2D u_TextureHeight;

void main()
{
	vec2 newUV = vec2(0.5) + a_Position.xy;

	float newHeight = texture(u_TextureHeight, newUV).r;
	vec3 newPos = vec3(a_Position.xy,a_Position.z + newHeight * 1.0);

	float alpha = fract(uTime / 3.0) * 2 * PI;

	mat4 Spin = mat4(
				cos(alpha), sin(alpha), 0, 0,
				-sin(alpha), cos(alpha), 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);

	gl_Position = u_ProjView * Spin * vec4(newPos,1.f);
	v_Grey = newHeight;
	v_Tex = newUV;
}
#version 450

in vec3 a_Position;
in vec2 a_UV;
in float u_Time;

out vec2 v_UV;

void main(){
	v_UV = a_UV;

	float newx = sin(2 * 3.14 * u_Time);
	float newy = cos(2 * 3.14 * u_Time);

	vec3 newPos = vec3(newx, newy, 0);
	
	gl_Position = vec4(a_Position.xyz, 1); 
}

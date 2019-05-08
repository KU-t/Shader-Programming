#version 450

in vec3 a_Position;
in vec2 a_UV;
in float u_Time;

out vec2 v_UV;
out vec3 v_Position;

void main(){
	v_UV = a_UV;
	v_Position = a_Position;
	gl_Position = vec4(a_Position.xyz, 1); 
}

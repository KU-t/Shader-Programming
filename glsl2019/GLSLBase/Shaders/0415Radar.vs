#version 450

in vec3 a_Position;	// x,y,z
in vec2 a_UV;

out vec2 v_Position;
out vec2 v_UV;

void main(){
	
	v_Position = a_Position.xy;
	v_UV = a_UV;
	gl_Position = vec4(a_Position.xyz, 1); 
}

#version 450

uniform sampler2D u_Texture0;
uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;
uniform sampler2D u_Texture3;
uniform sampler2D u_Texture4;
uniform sampler2D u_Texture5;

in vec2 v_UV;
in vec3 v_Position;

uniform float u_Time;
out vec4 FragColor;

void main(){
	
	vec2 newUV = v_UV;
	vec3 newPosition = v_Position;

	/*if(newUV.x < 0.5 && newUV.y < 0.5){
		FragColor = texture(u_Texture0, vec2(fract(newUV.x * 2), fract(newUV.y * 2)));
	}
	else if(newUV.x > 0.5 && newUV.y < 0.5){
		FragColor = texture(u_Texture1, vec2(fract(newUV.x * 2), fract(newUV.y * 2)));
	}
	else if(newUV.x < 0.5 && newUV.y > 0.5){
		FragColor = texture(u_Texture2, vec2(fract(newUV.x * 2), fract(newUV.y * 2)));
	}
	else if(newUV.x > 0.5 && newUV.y > 0.5){
		FragColor = texture(u_Texture3, vec2(fract(newUV.x * 2), fract(newUV.y * 2)));
	}*/


	if(newUV.x < 0.5 ){
		if( newUV.y > 0.666666666){
			FragColor = texture(u_Texture0, vec2(fract(newUV.x * 2), fract(newUV.y * 3)));
		}
		else if( newUV.y > 0.333333333){
			FragColor = texture(u_Texture1, vec2(fract(newUV.x * 2), fract(newUV.y * 3)));
		}
		else{
			FragColor = texture(u_Texture2, vec2(fract(newUV.x * 2), fract(newUV.y * 3)));
		}
	}

	else if(newUV.x >= 0.5){
		if( newUV.y > 0.666666666){
			FragColor = texture(u_Texture3, vec2(fract(newUV.x * 2), fract(newUV.y * 3)));
		}
		else if( newUV.y > 0.333333333){
			FragColor = texture(u_Texture4, vec2(fract(newUV.x * 2), fract(newUV.y * 3)));
		}
		else{
			FragColor = texture(u_Texture5, vec2(fract(newUV.x * 2), fract(newUV.y * 3)));
		}
	}

	
}

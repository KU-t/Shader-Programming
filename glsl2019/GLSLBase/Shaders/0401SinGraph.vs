#version 450

in vec3 a_Position;	// x,y,z
in vec2 a_StartLifeTime;

uniform float u_Time;

const float PI = 3.141592;

void main(){
	vec3 newPos = a_Position.xyx;
	
	float startTime = a_StartLifeTime.x;
	float lifeTime = a_StartLifeTime.y;

	float newTime = u_Time - startTime;

	if(newTime > 0){
		float life = newTime;

		float remaininglife = lifeTime - life;

		remaininglife = 1.f;
		newTime = mod(newTime, lifeTime);
		
		if(remaininglife < 0){
			newPos = vec3(100000,10000,10000);
		}

		else{
			newPos.x += newTime * (a_StartLifeTime.y /3);
			newPos.y += sin(newTime * 2 * PI) * (a_StartLifeTime.x / 3) * 0.5;
		}
	}
	
	else{
		newPos = vec3(100000,10000,10000);
	}

	gl_Position = vec4(newPos.xyz, 1);
}

#version 450

in vec3 a_Position;	// x,y,z
// attribute vec3 a_Postition;
in vec3 a_Vel;
in vec4 a_StartLifeRatioAmp;
in float a_RandV;
in vec4 a_RGB;

//Varying --> fragment shader input
out vec4 v_Color;
out vec2 v_Orixy;
out float v_Radius;

uniform float u_Time;

const float PI = 3.141592;
const mat3 c_RP = mat3(0, -1 , 0, 1, 0, 0, 0, 0, 0);
const vec3 c_Gravity = vec3(0, -100, 0);

void main(){
	vec3 newPos = a_Position;
	vec3 newVel = a_Vel;

	v_Orixy.xy = newPos.xy;
	v_Radius = abs(a_Position.x);

	float startTime = a_StartLifeRatioAmp.x;
	float lifeTime = a_StartLifeRatioAmp.y;
	float ratio = a_StartLifeRatioAmp.z;
	float amp = a_StartLifeRatioAmp.w;

	float newTime = u_Time - startTime;

	float alpha = (lifeTime - newTime) / lifeTime;

	if(newTime > 0){

		newPos.x += sin(a_RandV * 2 * PI) / 2;
		newPos.y += cos(a_RandV * 2 * PI) / 2;

		newTime=mod(newTime,lifeTime);

		newVel = newVel + c_Gravity * newTime;

		newPos += newPos + a_Vel * newTime + 0.5 * c_Gravity * newTime * newTime; // �߷�

		vec3 vSin = a_Vel * c_RP;
		newPos = newPos + vSin * sin(newTime * PI * 2 * ratio) * amp;
	}
	
	else{
		newPos = vec3(100000,10000,10000);
	}

	gl_Position = vec4(newPos.xyz, 1);
	
	v_Color = a_RGB;
	v_Color.a = alpha;
}

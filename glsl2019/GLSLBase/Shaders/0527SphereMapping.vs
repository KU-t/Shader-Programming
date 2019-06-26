#version 450

const float PI = 3.141592;

in vec3 a_Position; 
out float v_Grey;

uniform float uTime;
uniform vec2 uPoints[3];

void Wave(){
	float grey = 0;
	vec3 newPos = a_Position;

	for(int i = 0 ; i < 3; ++i){
		vec2 target = a_Position.xy;
		vec2 source = uPoints[i];
		float newTime = uTime;

		// 0 ~ 0.5 --> 0 ~ 2PI
		//float dis = length(target - source) * 4 * PI;

		// 
		float dis = length(target - source) * 4 * PI * 2 * float(i);

		grey += sin(dis - newTime); // +하면 방향 밖으로
	}

	newPos.z += grey;

	v_Grey = (grey + 1.0)/2.0;
	
	gl_Position = vec4(newPos,1);
}

void SphereMapping(){
	float r = 0.5;

	// beta : -0.5 ~ 0.5 -(+0.5)-> 0 ~ 1.0 --> 0 ~ 2PI
	float beta = (a_Position.x + 0.5) * 2 * PI;

	// theta : -0.5 ~ 0.5 -(+0.5)-> 0 ~ 1.0 --> 0 ~ 2PI
	float theta = (a_Position.y + 0.5) * 2 * PI;
	
	vec3 newSpherePos = a_Position;

	newSpherePos = vec3(
		r * sin(theta) * cos(beta),
		r * sin(theta) * sin(beta),
		r * cos(theta)
	);

	// 평면에서 구로 매핑과정
	// a_Position : 평면 | newSpherePos : 구 매핑
	float newSphereTime = (sin(uTime) + 1.0 ) / 2.0;
	
	//vec3 TransSpherePos = a_Position * newSphereTime + newSpherePos * (1 - newSphereTime);
	vec3 TransSpherePos = mix(a_Position, newSpherePos, newSphereTime);

	gl_Position = vec4(TransSpherePos,1);
}

void main(){
	//Wave();
	SphereMapping();
}


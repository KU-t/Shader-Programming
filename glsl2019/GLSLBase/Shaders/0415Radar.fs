#version 450

layout(location=0) out vec4 FragColor;

const float PI = 3.141592;

in vec2 v_Position;
in vec2 v_UV;

uniform float u_Time;
uniform vec2 u_Points[5];


void main(){
	vec2 newUV = v_UV - vec2(0.5, 0.5);	// -0.5 ~ 0.5, x, y
	
	float pointGrey = 0;

	float distance = length(newUV);
	float newTime = fract(u_Time);
	float ringwidth = 0.2;

	if( newTime < distance && distance < newTime + ringwidth){
		float temp = (distance - newTime) / ringwidth;
		pointGrey += temp;

		for(int i = 0; i < 5; ++i){
		vec2 newPoint = u_Points[i];
		vec2 newVec = newPoint - newUV;
		float distance = sqrt(newVec.x * newVec.x + newVec.y * newVec.y);

			if(distance < 0.1){	// 그리는 원의 반지름
				pointGrey += 0.5 * pow((1 - (distance / 0.1)), 10); 
				// * distance 가중치
			}
		}
	}

	FragColor = vec4(pointGrey);
}

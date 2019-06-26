#version 450

layout(location=0) out vec4 FragColor;

const float PI = 3.141592;

in vec2 v_Position;
in vec2 v_UV;

uniform vec2 u_Points[5];

void main(){
	vec2 newUV = v_UV - vec2(0.5, 0.5);	// -0.5 ~ 0.5, x, y
	
	float pointGrey = 0;

	for(int i = 0; i < 5; ++i){
		vec2 newPoint = u_Points[i];
		vec2 newVec = newPoint - newUV;
		float distance = sqrt(newVec.x*newVec.x + newVec.y*newVec.y);

		if(distance < 0.2){	// 그리는 원의 반지름
			pointGrey += 0.2 * distance * 10; // * distance 가중치
		}
	}

	//float distance = sqrt(v_Position.x * v_Position.x + v_Position.y * v_Position.y);
	//float grey = sin(distance * PI * 4 * 25); // 5주기

	//if( 0.49 < distance && distance < 0.5)	FragColor = vec4(v_Position.xy + vec2(0.5,0.5), 0 ,1);
	//else 	FragColor = vec4(0);

	//FragColor = vec4(newUV.xy, 0, 1);
	FragColor = vec4(pointGrey);
	//FragColor = vec4(1);
}

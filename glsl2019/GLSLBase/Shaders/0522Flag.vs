#version 450

const float PI = 3.141592;

in vec3 a_Position; 
out float v_color;
out vec2 v_Tex;

uniform float uTime;

void main()
{
	vec3 newPos = a_Position;

	// 0과 가까울수록 움직이지 않는 가중치 : 0 ~ 1
	float additionalValueX = newPos.x + 0.5;
	float additionalValueY = newPos.y + 0.5;
	
	// 우측으로 갈수록 주기가 커져
	float periodX = 1.0 + (1.0 - additionalValueX) * 0.5;
	float periodY = 1.0 + additionalValueX * 0.5;

	// sin함수 주기 (깃발 펄럭이는 속도)
	// [-0.5 ~ 0.5] -(+0.5)-> [0 ~ 1] -(x2 * PI xxx)
	float valueX = (2 * PI * (additionalValueY) * periodX) - uTime * 12;
	float valueY = (2 * PI * (additionalValueX) * periodY) - uTime * 8;

	// sin값 (펄럭이는 폭)
	float sinvalueX = 0.1 * sin(valueX);
	float sinvalueY = 0.2 * sin(valueY);
	
	// scale
	//newPos.y = newPos.y * ((1.0 - additionalValueX) * 0.5 + 0.5 );

	// 그리기 좌표
	//newPos.x = newPos.x - sinvalueX * additionalValueX;
	newPos.y = newPos.y + sinvalueY * additionalValueX;

	v_color = sinvalueY + 0.5;

	gl_Position = vec4(newPos,1);
	v_Tex = vec2(0.5) + a_Position.xy;
}
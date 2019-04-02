#version 450
//190325
//vertex shader에서 적용되는 연산은 모든 vertex에 수행

in vec3 a_Position;	// x,y,z
in vec3 a_Vel;
in vec2 a_StartLife;

uniform float u_Time;	//	0.....
uniform bool u_Reapeat = true;

const vec3 c_Gravity = vec3(0, -1, 0);

void main()
{
	vec3 newPos = a_Position.xyz;

	float startTime = a_StartLife.x;
	float lifeTime = a_StartLife.y;

	float newTime = u_Time - startTime;	// newTime > 0 일 경우에만 그린다.

	// Pos = Pos(init) + Vel(init) * Time
	// Pos = Pos(init) + Vel(init) * Time + (a * Time * Time) / 2
	// Vel = Vel(init) + a * Time
	
	if(newTime > 0) {
		float life = newTime;

		float remaininglife = lifeTime - life;

		if(u_Reapeat == true) {
			remaininglife = 1.f;
			newTime = mod(newTime, lifeTime);
		}

		if( remaininglife < 0) {
			newPos = vec3(10000, 100000,10000);	
			// 성능에 영향이 있나?? 뷰포트 밖으로 나가면 프레그먼트 쉐이더에 넘어가지 않는다
		}

		else{
			newPos += a_Vel * newTime + 0.5 * c_Gravity * newTime * newTime;
		}
	}
	
	else {
		newPos = vec3(10000, 100000,10000);
	}

	gl_Position = vec4(newPos.xyz, 1); // a_Position이면 통채로 넘어감
}

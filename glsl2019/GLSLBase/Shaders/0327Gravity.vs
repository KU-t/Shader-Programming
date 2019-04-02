#version 450
//190325
//vertex shader���� ����Ǵ� ������ ��� vertex�� ����

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

	float newTime = u_Time - startTime;	// newTime > 0 �� ��쿡�� �׸���.

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
			// ���ɿ� ������ �ֳ�?? ����Ʈ ������ ������ �����׸�Ʈ ���̴��� �Ѿ�� �ʴ´�
		}

		else{
			newPos += a_Vel * newTime + 0.5 * c_Gravity * newTime * newTime;
		}
	}
	
	else {
		newPos = vec3(10000, 100000,10000);
	}

	gl_Position = vec4(newPos.xyz, 1); // a_Position�̸� ��ä�� �Ѿ
}

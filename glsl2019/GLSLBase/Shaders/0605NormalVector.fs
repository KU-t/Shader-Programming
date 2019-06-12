#version 450

in vec3 v_Pos;
in float v_color;
in vec2 v_Tex;
in vec3 v_Norm;
in float v_Grey;

out vec4 FragColor;

uniform float uTime;
uniform vec3 u_CameraPos;
uniform sampler2D u_Texture;
uniform sampler2D u_TextureSnow;
uniform sampler2D u_TextureSGrass;

// ī�޶� ��ġ
const vec3 c_CameraDir = vec3(0.f, -0.7f, 0.5f);
// ���� ��ġ -> ī�޶��ֺ�
const vec3 c_Light1 = vec3(1.f, 0.f, 1.f);
// �� ������
const float c_cirR = 0.5;
const float PI = 3.141592;


void main()
{
	vec4 snowColor = texture(u_TextureSnow,v_Tex * 10) * v_Grey;
	vec4 grassColor = texture(u_TextureSGrass,v_Tex * 10) * (1 - v_Grey);
	vec4 finalColor = snowColor + grassColor;

	float a = 0.4f;
	float d = 0.5f;
	float s = 1.f;

	
	float alpha = fract(uTime / 10.0) * 2 * PI;
	
	
	vec3 newLightpos = vec3(u_CameraPos.x * sin(alpha) * c_cirR, u_CameraPos.y , u_CameraPos.z * cos(alpha) * c_cirR);

	vec3 lightDir = newLightpos - v_Pos;
	// ambient : (1,1,1,1) -> ���
	vec3 ambientcolor = vec3(1, 1, 1);
	
	// diffuse : 
	// clamp : dot�� ����� 0 ~ 1 �� 
	float diffuse = clamp(dot(lightDir,v_Norm), 0.0, 1.0);
	vec3 diffusecolor = vec3(1.f,1.f,1.f);
	
	vec3 reflectDir = reflect(lightDir, v_Norm);

	//���� ī�޶� �ٶ󺸴� ����
	vec3 viewDir = v_Pos - c_CameraDir;
	
	// specular : 
	vec3 speccolor = vec3(1.f,1.f,1.f);
	float spec = clamp(dot(viewDir,reflectDir), 0.0, 1.0);
	// ����
	spec = pow(spec,12.0);

	vec3 newColor = ambientcolor * a + diffusecolor * diffuse * d + speccolor * spec * s;

	vec4 outColor = vec4(newColor.x * finalColor.x, newColor.y * finalColor.y,
	newColor.z * finalColor.z, finalColor.x );

	FragColor = vec4(newColor, 1);
}

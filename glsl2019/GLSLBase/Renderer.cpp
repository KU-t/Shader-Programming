#include "stdafx.h"
#include "Renderer.h"
#include "LoadPng.h"
#include <Windows.h>
#include <cstdlib>
#include <cassert>

Renderer::Renderer(int windowSizeX, int windowSizeY)
{
	Initialize(windowSizeX, windowSizeY);
}

Renderer::~Renderer()
{

}

void Renderer::Initialize(int windowSizeX, int windowSizeY)
{
	//Set window size
	m_WindowSizeX = windowSizeX;
	m_WindowSizeY = windowSizeY;

	//Load shaders
	m_SolidRectShader = CompileShaders("./Shaders/SolidRect.vs", "./Shaders/SolidRect.fs");
	m_SimpleVelShader = CompileShaders("./Shaders/0325Simplevel.vs", "./Shaders/0325Simplevel.fs");
	m_GravityShader = CompileShaders("./Shaders/0327Gravity.vs", "./Shaders/0327Gravity.fs");
	m_SingraphShader = CompileShaders("./Shaders/0401SinGraph.vs", "./Shaders/0401SinGraph.fs");
	m_DirectionSinShader = CompileShaders("./Shaders/0403DirectionSinGraph.vs", "./Shaders/0403DirectionSinGraph.fs");
	m_FragmentBaseShader = CompileShaders("./Shaders/0408FragmentBase.vs", "./Shaders/0408FragmentBase.fs");
	m_InterpolationBaseShader = CompileShaders("./Shaders/0410InterpolationBase.vs", "./Shaders/0410InterpolationBase.fs");
	m_RadarShader = CompileShaders("./Shaders/0415Radar.vs", "./Shaders/0415Radar.fs");
	m_FillAlpha = CompileShaders("./Shaders/0415FillAlpha.vs", "./Shaders/0415FillAlpha.fs");
	
	//Load Textures
	//m_ParticleTexture0 = CreatePngTexture("./Textures/t0.png");
	//m_ParticleTexture1 = CreatePngTexture("./Textures/t1.png");
	//m_ParticleTexture2 = CreatePngTexture("./Textures/t2.png");

	//Create VBOs
	CreateVertexBufferObjects();
}

void Renderer::CreateVertexBufferObjects(){

	/*{

	float size = 0.02f;
	// DrawRect()  init
	float rect[] = {
		// xyz,xyz,xyz 3개
		// xyz, value
	-size, -size, 0.f, 0.5f,
	-size, size, 0.f, 0.5f,
	size, size, 0.f, 0.5f, //Triangle1
	-size, -size, 0.f, 0.5f,
	size, size, 0.f, 0.5f,
	size, -size, 0.f, 0.5f //Triangle2
	};

	glGenBuffers(1, &m_VBORect);	// m_VBORect에 rect[] 만들겠다.
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);	// GL_ARRAY_BUFFER 는 하나만 존재, Bind 조심해서 설정
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);	// GPU상으로 올림 , GL_STATIC_DRAW : 바뀌지 않는 값 (여러 유형 있음)

	float color[] = {
	
	-0.5, -0.5, 0.f, 0.1f,
	-0.5, 0.5, 0.f, 0.2f,
	0.5, 0.5, 0.f, 0.3f, //Triangle1
	-0.5, -0.5, 0.f, 0.4f,
	0.5, 0.5, 0.f, 0.5f,
	0.5, -0.5, 0.f, 0.6f //Triangle2
	};

	glGenBuffers(1, &m_VBORectcolor);	// m_VBORect에 rect[] 만들겠다.
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORectcolor);	// GL_ARRAY_BUFFER 는 하나만 존재, Bind 조심해서 설정
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);	// GPU상으로 올림 , GL_STATIC_DRAW : 바뀌지 않는 값 (여러 유형 있음)

	//DrawTri()함수 init
	float triangleVertex[] = { -1,0,0,0,1,0,1,0,0 };	//9float

	glGenBuffers(1, &m_VBOLecture);	// 개수는 하나 방금 만든 m_VBOLecture를 집어넣고 만든다.
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture);	//	이놈을 올리는데 대상은 GL_ARRAY_BUFFER, 올린건  m_VBOLecture
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertex), triangleVertex, GL_STATIC_DRAW);	// 버퍼 데이타를 통해 gpu 메모리에 올리는 작업, triangleVertex 사이즈만큼 올릴거고 
	}*/

	//DrawRandRect() init
	//GenQuadsVBO(1000);

	//DrawGridMesh() init
	//GridMeshVBO();

	//DrawProxyGeometry() init
	//CreateProxyGeometry();

	//DrawSimpleVel() init
	//GenQuadsVBO_Vel(1000);

	//DrawGravity(); init
	//GenQuadsVBO_Gra(1000);

	//DrawSinGraph(); init
	//GenQuadsVBO_Sin(1000, false, &m_VBO_SinGraph, &m_Count_SinGraph);

	//DrawDirectionSin(); init
	//GenQuadsVBO_DirectionSin(100000, false, &m_VBO_DirectionSinGraph, &m_Count_DirectionSinGraph);

	//DrawDirectionSin(); init
	//GenQuadsVBO_FragmentBase(100000, false, &m_VBO_FragmentBase, &m_Count_FragmentBase);

	//DrawInterpolation(); init
	//GenQuadsVBO_InterpolationBase(&m_VBO_InterpolationBase, &m_Count_InterpolationBase);

	//Draw0415
	GenQuadsVBO_Radar(&m_VBO_Radar, &m_Count_Radar);
}

void Renderer::GenQuadsVBO(int count){
	float randX, randY;
	float size = 0.002f;
	float arraySize = count * 3 * 6;	// 3대신 4
	float *vertices = new float[arraySize];

	for (int i = 0; i < count; i++) {
		int index = i * 18;	// 24

		randX = 2.f * (((float)rand() / RAND_MAX) - 0.5);
		randY = 2.f * (((float)rand() / RAND_MAX) - 0.5);
		
		{
		vertices[index] = randX - size;	index++;
		vertices[index] = randY - size;	index++;
		vertices[index] = 0.f;					index++;

		//vertices[index] = (float)i;	index++;

		vertices[index] = randX - size;	index++;
		vertices[index] = randY + size;	index++;
		vertices[index] = 0.f;					index++;

		//vertices[index] = (float)i;	index++;

		vertices[index] = randX + size;	index++;
		vertices[index] = randY + size;	index++;
		vertices[index] = 0.f;					index++;

		//vertices[index] = (float)i;	index++;

		}

		{
		vertices[index] = randX - size;	index++;
		vertices[index] = randY - size;	index++;
		vertices[index] = 0.f;					index++;

		//vertices[index] = (float)i;	index++;

		vertices[index] = randX + size;	index++;
		vertices[index] = randY - size;	index++;
		vertices[index] = 0.f;					index++;

		//vertices[index] = (float)i;	index++;

		vertices[index] = randX + size;	index++;
		vertices[index] = randY + size;	index++;
		vertices[index] = 0.f;					index++;

		//vertices[index] = (float)i;	index++;
		}
	}

	glGenBuffers(1, &m_VBOQuads);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOQuads);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * arraySize, vertices, GL_STATIC_DRAW);

	m_VBOQuads_VertexCount = 6 * count;
}

void Renderer::GenQuadsVBO_Vel(int count)
{
	int verticesPerQuad = 6;	// 사각형에 몇개의 vertex
	int floatsPervertex = 3 + 3;	// xyz, velx, vely, velz, 
	int countQuad = count;	// 몇개의 쿼드

	float size = 0.002f;
	int arraySize = countQuad * verticesPerQuad * floatsPervertex;	// 3대신 4 // vertex개수
	float *vertices = new float[arraySize];

	for (int i = 0; i < countQuad; i++) {
		
		int index = i * verticesPerQuad * floatsPervertex;	// 24 // 한루프당 개수
		
		float randX, randY;
		float randVelX, randVelY, randVelZ;

		randX = 2.f * (((float)rand() / RAND_MAX) - 0.5);
		randY = 2.f * (((float)rand() / RAND_MAX) - 0.5);

		randVelX = 2.f * (((float)rand() / RAND_MAX) - 0.5);
		randVelY = 2.f * (((float)rand() / RAND_MAX) - 0.5);
		randVelZ = 0.f;

		{
			// 1번쨰
			vertices[index] = randX - size;	index++;
			vertices[index] = randY - size;	index++;
			vertices[index] = 0.f;					index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			//vertices[index] = (float)i;	index++;

			// 2번째
			vertices[index] = randX - size;	index++;
			vertices[index] = randY + size;	index++;
			vertices[index] = 0.f;					index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			//vertices[index] = (float)i;	index++;

			// 3번째
			vertices[index] = randX + size;	index++;
			vertices[index] = randY + size;	index++;
			vertices[index] = 0.f;					index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			//vertices[index] = (float)i;	index++;

		}

		{
			// 4번째
			vertices[index] = randX - size;	index++;
			vertices[index] = randY - size;	index++;
			vertices[index] = 0.f;					index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			//vertices[index] = (float)i;	index++;

			// 5번째
			vertices[index] = randX + size;		index++;
			vertices[index] = randY - size;		index++;
			vertices[index] = 0.f;						index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			//vertices[index] = (float)i;	index++;

			// 6번째
			vertices[index] = randX + size;		index++;
			vertices[index] = randY + size;		index++;
			vertices[index] = 0.f;						index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			//vertices[index] = (float)i;	index++;
		}
	}

	glGenBuffers(1, &m_VBOQuads);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOQuads);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * arraySize, vertices, GL_STATIC_DRAW);

	m_VBOQuads_VertexCount = 6 * count;
}

void Renderer::GenQuadsVBO_Gra(int count) {
	int verticesPerQuad = 6;	// 사각형에 몇개의 vertex
	int floatsPervertex = 3 + 3 + 2;	// xyz, velx, vely, velz, lifetime, starttime
	int countQuad = count;	// 몇개의 쿼드

	float size = 0.002f;
	int arraySize = countQuad * verticesPerQuad * floatsPervertex;	// 3대신 4 // vertex개수
	float *vertices = new float[arraySize];

	for (int i = 0; i < countQuad; i++) {

		int index = i * verticesPerQuad * floatsPervertex;	// 24 // 한루프당 개수

		float randX, randY;
		float randVelX, randVelY, randVelZ;

		float startTime, lifeTime;
		float startTimeMax = 5.f;
		float lifeTimeMax = 3.f;

		randX = 0.f;// 2.f * (((float)rand() / RAND_MAX) - 0.5);
		randY = - 0.5f;// 2.f * (((float)rand() / RAND_MAX) - 0.5);

		randVelX = 2.f * (((float)rand() / RAND_MAX) - 0.5);
		randVelY = 2.f *(((float)rand() / RAND_MAX));
		randVelZ = 0.f;

		startTime = ((float)rand() / RAND_MAX) * startTimeMax;
		lifeTime = ((float)rand() / RAND_MAX) * lifeTimeMax;
		{
			// 1번쨰
			vertices[index] = randX - size;	index++;
			vertices[index] = randY - size;	index++;
			vertices[index] = 0.f;					index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			vertices[index] = startTime;			index++;
			vertices[index] = lifeTime;				index++;
			//vertices[index] = (float)i;	index++;

			// 2번째
			vertices[index] = randX - size;	index++;
			vertices[index] = randY + size;	index++;
			vertices[index] = 0.f;					index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			vertices[index] = startTime;			index++;
			vertices[index] = lifeTime;				index++;
			//vertices[index] = (float)i;	index++;

			// 3번째
			vertices[index] = randX + size;	index++;
			vertices[index] = randY + size;	index++;
			vertices[index] = 0.f;					index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			vertices[index] = startTime;			index++;
			vertices[index] = lifeTime;				index++;
			//vertices[index] = (float)i;	index++;

		}

		{
			// 4번째
			vertices[index] = randX - size;	index++;
			vertices[index] = randY - size;	index++;
			vertices[index] = 0.f;					index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			vertices[index] = startTime;			index++;
			vertices[index] = lifeTime;				index++;
			//vertices[index] = (float)i;	index++;

			// 5번째
			vertices[index] = randX + size;		index++;
			vertices[index] = randY - size;		index++;
			vertices[index] = 0.f;						index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			vertices[index] = startTime;			index++;
			vertices[index] = lifeTime;				index++;
			//vertices[index] = (float)i;	index++;

			// 6번째
			vertices[index] = randX + size;		index++;
			vertices[index] = randY + size;		index++;
			vertices[index] = 0.f;						index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			vertices[index] = startTime;			index++;
			vertices[index] = lifeTime;				index++;
			//vertices[index] = (float)i;	index++;
		}
	}

	glGenBuffers(1, &m_VBOQuads);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOQuads);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * arraySize, vertices, GL_STATIC_DRAW);

	m_VBOQuads_VertexCount = 6 * count;
}

void Renderer::GenQuadsVBO_Sin(int count,bool random, GLuint* ID,GLuint* vCount) {
	int verticesPerQuad = 6;	// 사각형에 몇개의 vertex
	int floatsPervertex = 3 + 3 + 3;	// xyz, velx, vely, velz, starttime, lifetime, input
	int countQuad = count;	// 몇개의 쿼드

	float size = 0.002f;
	int arraySize = countQuad * verticesPerQuad * floatsPervertex;	 // vertex개수
	float *vertices = new float[arraySize];

	for (int i = 0; i < countQuad; i++) {

		int index = i * verticesPerQuad * floatsPervertex;	 // 한루프당 개수

		float randX, randY;
		float randVelX, randVelY, randVelZ;

		float startTime, lifeTime;
		float startTimeMax = 5.f;
		float lifeTimeMax = 5.f;

		if (random) {
			randX = 2.f * (((float)rand() / RAND_MAX) - 0.5);
			randY = 2.f * (((float)rand() / RAND_MAX) - 0.5);
		}

		else {
			randX = 0.f;
			randY = 0.f;
		}

		randVelX = 0.f;// (((float)rand() / RAND_MAX) - 0.5);
		randVelY = 0.f;
		randVelZ = 0.f;

		startTime = ((float)rand() / RAND_MAX) * startTimeMax;
		lifeTime = ((float)rand() / RAND_MAX) * lifeTimeMax;
		{
			// 1번쨰
			vertices[index] = randX - size;	index++;
			vertices[index] = randY - size;	index++;
			vertices[index] = 0.f;					index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			vertices[index] = startTime;			index++;
			vertices[index] = lifeTime;				index++;
			vertices[index] = 0;				index++;
			//vertices[index] = (float)i;	index++;

			// 2번째
			vertices[index] = randX - size;	index++;
			vertices[index] = randY + size;	index++;
			vertices[index] = 0.f;					index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			vertices[index] = startTime;			index++;
			vertices[index] = lifeTime;				index++;
			vertices[index] = 0;				index++;
			//vertices[index] = (float)i;	index++;

			// 3번째
			vertices[index] = randX + size;	index++;
			vertices[index] = randY + size;	index++;
			vertices[index] = 0.f;					index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			vertices[index] = startTime;			index++;
			vertices[index] = lifeTime;				index++;
			vertices[index] = 0;				index++;
			//vertices[index] = (float)i;	index++;

		}

		{
			// 4번째
			vertices[index] = randX - size;	index++;
			vertices[index] = randY - size;	index++;
			vertices[index] = 0.f;					index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			vertices[index] = startTime;			index++;
			vertices[index] = lifeTime;				index++;
			vertices[index] = 0;				index++;
			//vertices[index] = (float)i;	index++;

			// 5번째
			vertices[index] = randX + size;		index++;
			vertices[index] = randY - size;		index++;
			vertices[index] = 0.f;						index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			vertices[index] = startTime;			index++;
			vertices[index] = lifeTime;				index++;
			vertices[index] = 0;				index++;
			//vertices[index] = (float)i;	index++;

			// 6번째
			vertices[index] = randX + size;		index++;
			vertices[index] = randY + size;		index++;
			vertices[index] = 0.f;						index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			vertices[index] = startTime;			index++;
			vertices[index] = lifeTime;				index++;
			vertices[index] = 0;				index++;
			//vertices[index] = (float)i;	index++;
		}
	}

	GLuint vboID = 0;

	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * arraySize, vertices, GL_STATIC_DRAW);

	*vCount = countQuad * verticesPerQuad;
	*ID = vboID;
}

void Renderer::GenQuadsVBO_DirectionSin(int count, bool random, GLuint* ID, GLuint* vCount) {
	int verticesPerQuad = 6;	// 사각형에 몇개의 vertex
	int floatsPervertex = 3 + 3 + 5;	// xyz, velx, vely, velz, starttime, lifetime, input
	int countQuad = count;	// 몇개의 쿼드

	float size = 0.001f;
	int arraySize = countQuad * verticesPerQuad * floatsPervertex;	 // vertex개수
	float *vertices = new float[arraySize];

	for (int i = 0; i < countQuad; i++) {

		int index = i * verticesPerQuad * floatsPervertex;	 // 한루프당 개수

		float randX, randY;
		float randVelX, randVelY, randVelZ;

		float startTime, lifeTime;
		float ratio, amp;
		float startTimeMax = 5.f;
		float lifeTimeMax = 5.f;
		float ratioMax = 5.f;
		float ampMax = 0.2f;
		float randValue = 0, randthres = 0;

		if (random) {
			randX = 2.f * (((float)rand() / RAND_MAX) - 0.5);
			randY = 2.f * (((float)rand() / RAND_MAX) - 0.5);
		}

		else {
			randX = 0.f;
			randY = 0.f;
		}

		randVelX = (((float)rand() / RAND_MAX) - 0.5);
		randVelY = (((float)rand() / RAND_MAX) - 0.5);
		randVelZ = (((float)rand() / RAND_MAX) - 0.5);

		startTime = ((float)rand() / RAND_MAX) * startTimeMax;
		lifeTime = ((float)rand() / RAND_MAX) * lifeTimeMax;
		ratio = ((float)rand() / RAND_MAX) * ratioMax;
		amp =  ((float)rand() / RAND_MAX) * ampMax;
		randValue = ((float)rand() / RAND_MAX);

		{
			// 1번쨰
			vertices[index] = randX - size;	index++;
			vertices[index] = randY - size;	index++;
			vertices[index] = 0.f;					index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			vertices[index] = startTime;			index++;
			vertices[index] = lifeTime;				index++;
			vertices[index] = ratio;				index++;
			vertices[index] = amp;				index++;
			vertices[index] = randValue;				index++;
			//vertices[index] = (float)i;	index++;

			// 2번째
			vertices[index] = randX - size;	index++;
			vertices[index] = randY + size;	index++;
			vertices[index] = 0.f;					index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			vertices[index] = startTime;			index++;
			vertices[index] = lifeTime;				index++;
			vertices[index] = ratio;				index++;
			vertices[index] = amp;				index++;
			vertices[index] = randValue;				index++;
			//vertices[index] = (float)i;	index++;

			// 3번째
			vertices[index] = randX + size;	index++;
			vertices[index] = randY + size;	index++;
			vertices[index] = 0.f;					index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			vertices[index] = startTime;			index++;
			vertices[index] = lifeTime;				index++;
			vertices[index] = ratio;				index++;
			vertices[index] = amp;				index++;
			vertices[index] = randValue;				index++;
			//vertices[index] = (float)i;	index++;

		}

		{
			// 4번째
			vertices[index] = randX - size;	index++;
			vertices[index] = randY - size;	index++;
			vertices[index] = 0.f;					index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			vertices[index] = startTime;			index++;
			vertices[index] = lifeTime;				index++;
			vertices[index] = ratio;				index++;
			vertices[index] = amp;				index++;
			vertices[index] = randValue;				index++;
			//vertices[index] = (float)i;	index++;

			// 5번째
			vertices[index] = randX + size;		index++;
			vertices[index] = randY - size;		index++;
			vertices[index] = 0.f;						index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			vertices[index] = startTime;			index++;
			vertices[index] = lifeTime;				index++;
			vertices[index] = ratio;				index++;
			vertices[index] = amp;				index++;
			vertices[index] = randValue;				index++;
			//vertices[index] = (float)i;	index++;

			// 6번째
			vertices[index] = randX + size;		index++;
			vertices[index] = randY + size;		index++;
			vertices[index] = 0.f;						index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			vertices[index] = startTime;			index++;
			vertices[index] = lifeTime;				index++;
			vertices[index] = ratio;				index++;
			vertices[index] = amp;				index++;
			vertices[index] = randValue;				index++;
			//vertices[index] = (float)i;	index++;
		}
	}

	GLuint vboID = 0;

	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * arraySize, vertices, GL_STATIC_DRAW);

	*vCount = countQuad * verticesPerQuad;
	*ID = vboID;
}

void Renderer::GenQuadsVBO_FragmentBase(int count, bool random, GLuint* ID, GLuint* vCount) {
	int verticesPerQuad = 6;	// 사각형에 몇개의 vertex
	int floatsPervertex = 3 + 3 + 5 + 4;	// xyz, velx, vely, velz, starttime, lifetime, ratio, amp, Value, R, G, B, a
	int countQuad = count;	// 몇개의 쿼드

	float size = 0.02f;
	int arraySize = countQuad * verticesPerQuad * floatsPervertex;	 // vertex개수
	float *vertices = new float[arraySize];

	for (int i = 0; i < countQuad; i++) {

		int index = i * verticesPerQuad * floatsPervertex;	 // 한루프당 개수

		float randX, randY;
		float randVelX, randVelY, randVelZ;

		float startTime, lifeTime;
		float ratio, amp;
		float startTimeMax = 1.f;
		float lifeTimeMax = 0.2f;
		float ratioMax = 5.f;
		float ampMax = 0.2f;
		float randValue = 0, randthres = 0;

		float randR;
		float randG;
		float randB;
		float randa;

		if (random) {
			randX = 2.f * (((float)rand() / RAND_MAX) - 0.5);
			randY = 2.f * (((float)rand() / RAND_MAX) - 0.5);
		}

		else {
			randX = 0.f;
			randY = 0.f;
		}

		randVelX = 0.f;
		randVelY = 0.f;
		randVelZ = 0.f;

		startTime = ((float)rand() / RAND_MAX) * startTimeMax;
		lifeTime = ((float)rand() / RAND_MAX) * lifeTimeMax;
		ratio = 0.f;
		amp = 0.f;
		randValue = ((float)rand() / RAND_MAX);

		randR = (float)(rand() % 1000) * 0.001;
		randG = (float)(rand() % 1000) * 0.001;
		randB = (float)(rand() % 1000) * 0.001;
		randa = 1.f;

		{
			// 1번쨰
			vertices[index] = randX - size;	index++;
			vertices[index] = randY - size;	index++;
			vertices[index] = 0.f;					index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			vertices[index] = startTime;			index++;
			vertices[index] = lifeTime;				index++;
			vertices[index] = ratio;				index++;
			vertices[index] = amp;				index++;
			vertices[index] = randValue;				index++;

			vertices[index] = randR;				index++;
			vertices[index] = randG;				index++;
			vertices[index] = randB;				index++;
			vertices[index] = randa;				index++;
			//vertices[index] = (float)i;	index++;

			// 2번째
			vertices[index] = randX - size;	index++;
			vertices[index] = randY + size;	index++;
			vertices[index] = 0.f;					index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			vertices[index] = startTime;			index++;
			vertices[index] = lifeTime;				index++;
			vertices[index] = ratio;				index++;
			vertices[index] = amp;				index++;
			vertices[index] = randValue;				index++;

			vertices[index] = randR;				index++;
			vertices[index] = randG;				index++;
			vertices[index] = randB;				index++;
			vertices[index] = randa;				index++;
			//vertices[index] = (float)i;	index++;

			// 3번째
			vertices[index] = randX + size;	index++;
			vertices[index] = randY + size;	index++;
			vertices[index] = 0.f;					index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			vertices[index] = startTime;			index++;
			vertices[index] = lifeTime;				index++;
			vertices[index] = ratio;				index++;
			vertices[index] = amp;				index++;
			vertices[index] = randValue;				index++;

			vertices[index] = randR;				index++;
			vertices[index] = randG;				index++;
			vertices[index] = randB;				index++;
			vertices[index] = randa;				index++;
			//vertices[index] = (float)i;	index++;

		}

		{
			// 4번째
			vertices[index] = randX - size;	index++;
			vertices[index] = randY - size;	index++;
			vertices[index] = 0.f;					index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			vertices[index] = startTime;			index++;
			vertices[index] = lifeTime;				index++;
			vertices[index] = ratio;				index++;
			vertices[index] = amp;				index++;
			vertices[index] = randValue;				index++;

			vertices[index] = randR;				index++;
			vertices[index] = randG;				index++;
			vertices[index] = randB;				index++;
			vertices[index] = randa;				index++;
			//vertices[index] = (float)i;	index++;

			// 5번째
			vertices[index] = randX + size;		index++;
			vertices[index] = randY - size;		index++;
			vertices[index] = 0.f;						index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			vertices[index] = startTime;			index++;
			vertices[index] = lifeTime;				index++;
			vertices[index] = ratio;				index++;
			vertices[index] = amp;				index++;
			vertices[index] = randValue;				index++;

			vertices[index] = randR;				index++;
			vertices[index] = randG;				index++;
			vertices[index] = randB;				index++;
			vertices[index] = randa;				index++;
			//vertices[index] = (float)i;	index++;

			// 6번째
			vertices[index] = randX + size;		index++;
			vertices[index] = randY + size;		index++;
			vertices[index] = 0.f;						index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			vertices[index] = startTime;			index++;
			vertices[index] = lifeTime;				index++;
			vertices[index] = ratio;				index++;
			vertices[index] = amp;				index++;
			vertices[index] = randValue;				index++;

			vertices[index] = randR;				index++;
			vertices[index] = randG;				index++;
			vertices[index] = randB;				index++;
			vertices[index] = randa;				index++;
			//vertices[index] = (float)i;	index++;
		}
	}

	GLuint vboID = 0;

	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * arraySize, vertices, GL_STATIC_DRAW);

	*vCount = countQuad * verticesPerQuad;
	*ID = vboID;
}

void Renderer::GenQuadsVBO_InterpolationBase(GLuint * ID, GLuint * vCount){

	int verticesPerQuad = 6;	// 사각형에 몇개의 vertex
	int floatsPervertex = 3 + 2 + 5 + 5;	// xyz, uv, empty10

	float size = 0.5f;
	int arraySize =  verticesPerQuad * floatsPervertex;	 // vertex개수
	float *vertices = new float[arraySize];

	{
		int index = 0;	 // 한루프당 개수

		float randX = 0.f, randY = 0.f;

		{
			// 1번쨰
			vertices[index] = randX - size;	index++;
			vertices[index] = randY - size;	index++;
			vertices[index] = 0.f;					index++;

			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			//vertices[index] = (float)i;	index++;

			// 2번째
			vertices[index] = randX - size;	index++;
			vertices[index] = randY + size;	index++;
			vertices[index] = 0.f;					index++;

			vertices[index] = 0.f;			index++;
			vertices[index] = 1.f;			index++;

			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			//vertices[index] = (float)i;	index++;

			// 3번째
			vertices[index] = randX + size;	index++;
			vertices[index] = randY + size;	index++;
			vertices[index] = 0.f;					index++;

			vertices[index] = 1.f;			index++;
			vertices[index] = 1.f;			index++;

			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			//vertices[index] = (float)i;	index++;

		}

		{
			// 4번째
			vertices[index] = randX - size;	index++;
			vertices[index] = randY - size;	index++;
			vertices[index] = 0.f;					index++;

			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;

			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			//vertices[index] = (float)i;	index++;

			// 5번째
			vertices[index] = randX + size;		index++;
			vertices[index] = randY - size;		index++;
			vertices[index] = 0.f;						index++;

			vertices[index] = 1.f;			index++;
			vertices[index] = 0.f;			index++;

			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			//vertices[index] = (float)i;	index++;

			// 6번째
			vertices[index] = randX + size;		index++;
			vertices[index] = randY + size;		index++;
			vertices[index] = 0.f;						index++;

			vertices[index] = 1.f;			index++;
			vertices[index] = 1.f;			index++;

			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			//vertices[index] = (float)i;	index++;
		}
	}

	GLuint vboID = 0;

	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * arraySize, vertices, GL_STATIC_DRAW);

	*vCount = verticesPerQuad;
	*ID = vboID;
}

void Renderer::GenQuadsVBO_Radar(GLuint * ID, GLuint * vCount) {

	int verticesPerQuad = 6;	// 사각형에 몇개의 vertex
	int floatsPervertex = 3 + 2 + 5 + 5;	// xyz, uv, empty10

	float size = 1.f;
	int arraySize = verticesPerQuad * floatsPervertex;	 // vertex개수
	float *vertices = new float[arraySize];

	{
		int index = 0;	 // 한루프당 개수

		float randX = 0.f, randY = 0.f;

		{
			// 1번쨰
			vertices[index] = randX - size;	index++;
			vertices[index] = randY - size;	index++;
			vertices[index] = 0.f;					index++;

			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;

			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			//vertices[index] = (float)i;	index++;

			// 2번째
			vertices[index] = randX - size;	index++;
			vertices[index] = randY + size;	index++;
			vertices[index] = 0.f;					index++;

			vertices[index] = 0.f;			index++;
			vertices[index] = 1.f;			index++;

			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			//vertices[index] = (float)i;	index++;

			// 3번째
			vertices[index] = randX + size;	index++;
			vertices[index] = randY + size;	index++;
			vertices[index] = 0.f;					index++;

			vertices[index] = 1.f;			index++;
			vertices[index] = 1.f;			index++;

			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			//vertices[index] = (float)i;	index++;

		}

		{
			// 4번째
			vertices[index] = randX - size;	index++;
			vertices[index] = randY - size;	index++;
			vertices[index] = 0.f;					index++;

			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;

			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			//vertices[index] = (float)i;	index++;

			// 5번째
			vertices[index] = randX + size;		index++;
			vertices[index] = randY - size;		index++;
			vertices[index] = 0.f;						index++;

			vertices[index] = 1.f;			index++;
			vertices[index] = 0.f;			index++;

			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			//vertices[index] = (float)i;	index++;

			// 6번째
			vertices[index] = randX + size;		index++;
			vertices[index] = randY + size;		index++;
			vertices[index] = 0.f;						index++;

			vertices[index] = 1.f;			index++;
			vertices[index] = 1.f;			index++;

			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			vertices[index] = 0.f;			index++;
			//vertices[index] = (float)i;	index++;
		}
	}

	GLuint vboID = 0;

	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * arraySize, vertices, GL_STATIC_DRAW);

	*vCount = verticesPerQuad;
	*ID = vboID;
}

void Renderer::GridMeshVBO()
{
	float StartPointX = -0.5f;
	float StartPointY = -0.5f;
	float	EndPointX = 0.5f;
	float EndPointY = 0.5f;

	int PointCountX = 32;
	int PointCountY = 32;

	float arraysize = PointCountX * PointCountY * 3;

	float Width = EndPointX - StartPointX;
	float Height = EndPointY - StartPointY;

	float* point = new float[PointCountX * PointCountY * 2];

	for (int y = 0; y < PointCountY; y++) {
		for (int x = 0; x < PointCountX; x++) {
			point[(x + PointCountY * y) * 2 + 0] = StartPointX + Width * ((float)x/PointCountX-1);
			point[(x + PointCountY * y) * 2 + 1] = StartPointY + Height * ((float)y/PointCountY-1);
		}
	}

	float* vertices = new float[PointCountX * PointCountY * 3];
	int PointIndex = 0;

	for (int y = 0; y < PointCountY; y++) {
		for (int x = 0; x < PointCountX; x++) {
			vertices[PointIndex++] = point[(x + PointCountY * y) * 2 + 0];
			vertices[PointIndex++] = point[(x + PointCountY * y) * 2 + 1];
			vertices[PointIndex++] = 0.f;

			vertices[PointIndex++] = point[((x + 1) + PointCountY * (y + 1)) * 2 + 0];
			vertices[PointIndex++] = point[((x + 1) + PointCountY * (y + 1)) * 2 + 1];
			vertices[PointIndex++] = 0.f;

			vertices[PointIndex++] = point[(x + PointCountY * (y + 1)) * 2 + 0];
			vertices[PointIndex++] = point[(x + PointCountY * (y + 1)) * 2 + 1];
			vertices[PointIndex++] = 0.f;

			vertices[PointIndex++] = point[(x + PointCountY * y) * 2 + 0];
			vertices[PointIndex++] = point[(x + PointCountY * y) * 2 + 1];
			vertices[PointIndex++] = 0.f;

			vertices[PointIndex++] = point[((x + 1) + PointCountY * y) * 2 + 0];
			vertices[PointIndex++] = point[((x + 1) + PointCountY * y) * 2 + 1];
			vertices[PointIndex++] = 0.f;

			vertices[PointIndex++] = point[((x + 1) + PointCountY * (y + 1)) * 2 + 0];
			vertices[PointIndex++] = point[((x + 1) + PointCountY * (y + 1)) * 2 + 1];
			vertices[PointIndex++] = 0.f;
		}
	}

	glGenBuffers(1, &m_VBOGrid);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOGrid);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * arraysize, vertices, GL_STATIC_DRAW);

	m_VBOGrid_VertexCount =3;
}

void Renderer::CreateProxyGeometry()
{
	float basePosX = -0.5f;
	float basePosY = -0.5f;
	float targetPosX = 0.5f;
	float targetPosY = 0.5f;

	int pointCountX = 32;
	int pointCountY = 32;

	float width = targetPosX - basePosX;
	float height = targetPosY - basePosY;

	float* point = new float[pointCountX*pointCountY * 2];
	float* vertices = new float[(pointCountX - 1)*(pointCountY - 1) * 2 * 3 * 3];
	m_Count_ProxyGeo = (pointCountX - 1)*(pointCountY - 1) * 2 * 3;

	//Prepare points
	for (int x = 0; x < pointCountX; x++)
	{
		for (int y = 0; y < pointCountY; y++)
		{
			point[(y*pointCountX + x) * 2 + 0] = basePosX + width * (x / (float)(pointCountX - 1));
			point[(y*pointCountX + x) * 2 + 1] = basePosY + height * (y / (float)(pointCountY - 1));
		}
	}

	//Make triangles
	int vertIndex = 0;
	for (int x = 0; x < pointCountX - 1; x++)
	{
		for (int y = 0; y < pointCountY - 1; y++)
		{
			//Triangle part 1
			vertices[vertIndex] = point[(y*pointCountX + x) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[(y*pointCountX + x) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
			vertices[vertIndex] = point[((y + 1)*pointCountX + (x + 1)) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[((y + 1)*pointCountX + (x + 1)) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
			vertices[vertIndex] = point[((y + 1)*pointCountX + x) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[((y + 1)*pointCountX + x) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;

			//Triangle part 2
			vertices[vertIndex] = point[(y*pointCountX + x) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[(y*pointCountX + x) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
			vertices[vertIndex] = point[(y*pointCountX + (x + 1)) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[(y*pointCountX + (x + 1)) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
			vertices[vertIndex] = point[((y + 1)*pointCountX + (x + 1)) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[((y + 1)*pointCountX + (x + 1)) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
		}
	}

	glGenBuffers(1, &m_VBO_ProxyGeo);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_ProxyGeo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(pointCountX - 1)*(pointCountY - 1) * 2 * 3 * 3, vertices, GL_STATIC_DRAW);
}

void Renderer::AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType){

	// ShaderType = 여러가지

	//쉐이더 오브젝트 생성
	GLuint ShaderObj = glCreateShader(ShaderType);

	if (ShaderObj == 0) {
		//Shader 생성 실패
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
	}

	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];
	Lengths[0] = (GLint)strlen(pShaderText);
	//쉐이더 코드를 쉐이더 오브젝트에 할당
	glShaderSource(ShaderObj, 1, p, Lengths);

	//할당된 쉐이더 코드를 컴파일
	glCompileShader(ShaderObj);

	GLint success;
	// ShaderObj 가 성공적으로 컴파일 되었는지 확인
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];

		//OpenGL 의 shader log 데이터를 가져옴
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		printf("%s \n", pShaderText);
	}

	// ShaderProgram 에 attach!!
	glAttachShader(ShaderProgram, ShaderObj);
}

bool Renderer::ReadFile(char* filename, std::string *target)
{
	std::ifstream file(filename);
	if (file.fail())
	{
		std::cout << filename << " file loading failed.. \n";
		file.close();
		return false;
	}
	std::string line;
	while (getline(file, line)) {
		target->append(line.c_str());
		target->append("\n");
	}
	return true;
}

GLuint Renderer::CompileShaders(char* filenameVS, char* filenameFS)
{
	GLuint ShaderProgram = glCreateProgram(); //빈 쉐이더 프로그램 생성

	if (ShaderProgram == 0) { //쉐이더 프로그램이 만들어졌는지 확인
		fprintf(stderr, "Error creating shader program\n");
	}

	std::string vs, fs;

	//shader.vs 가 vs 안으로 로딩됨
	if (!ReadFile(filenameVS, &vs)) {
		printf("Error compiling vertex shader\n");
		return -1;
	};

	//shader.fs 가 fs 안으로 로딩됨
	if (!ReadFile(filenameFS, &fs)) {
		printf("Error compiling fragment shader\n");
		return -1;
	};

	// ShaderProgram 에 vs.c_str() 버텍스 쉐이더를 컴파일한 결과를 attach함
	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);

	// ShaderProgram 에 fs.c_str() 프레그먼트 쉐이더를 컴파일한 결과를 attach함
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };

	//Attach 완료된 shaderProgram 을 링킹함
	glLinkProgram(ShaderProgram);

	//링크가 성공했는지 확인
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);

	if (Success == 0) {
		// shader program 로그를 받아옴
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << filenameVS << ", " << filenameFS << " Error linking shader program\n" << ErrorLog;
		return -1;
	}

	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << filenameVS << ", " << filenameFS << " Error validating shader program\n" << ErrorLog;
		return -1;
	}

	glUseProgram(ShaderProgram);
	std::cout << filenameVS << ", " << filenameFS << " Shader compiling is done.\n";

	return ShaderProgram;
}

unsigned char * Renderer::loadBMPRaw(const char * imagepath, unsigned int& outWidth, unsigned int& outHeight)
{
	std::cout << "Loading bmp file " << imagepath << " ... " << std::endl;
	outWidth = -1;
	outHeight = -1;
	// Data read from the header of the BMP file
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;
	// Actual RGB data
	unsigned char * data;

	// Open the file
	FILE * file = NULL;
	fopen_s(&file, imagepath, "rb");
	if (!file)
	{
		std::cout << "Image could not be opened, " << imagepath << " is missing. " << std::endl;
		return NULL;
	}

	if (fread(header, 1, 54, file) != 54)
	{
		std::cout << imagepath << " is not a correct BMP file. " << std::endl;
		return NULL;
	}

	if (header[0] != 'B' || header[1] != 'M')
	{
		std::cout << imagepath << " is not a correct BMP file. " << std::endl;
		return NULL;
	}

	if (*(int*)&(header[0x1E]) != 0)
	{
		std::cout << imagepath << " is not a correct BMP file. " << std::endl;
		return NULL;
	}

	if (*(int*)&(header[0x1C]) != 24)
	{
		std::cout << imagepath << " is not a correct BMP file. " << std::endl;
		return NULL;
	}

	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	outWidth = *(int*)&(header[0x12]);
	outHeight = *(int*)&(header[0x16]);

	if (imageSize == 0)
		imageSize = outWidth * outHeight * 3;

	if (dataPos == 0)
		dataPos = 54;

	data = new unsigned char[imageSize];

	fread(data, 1, imageSize, file);

	fclose(file);

	std::cout << imagepath << " is succesfully loaded. " << std::endl;

	return data;
}

GLuint Renderer::CreatePngTexture(char * filePath)
{
	//Load Pngs: Load file and decode image.
	std::vector<unsigned char> image;
	unsigned width, height;
	unsigned error = lodepng::decode(image, width, height, filePath);
	if (error != 0)
	{
		lodepng_error_text(error);
		assert(error == 0);
		return -1;
	}

	GLuint temp;
	glGenTextures(1, &temp);

	glBindTexture(GL_TEXTURE_2D, temp);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);

	return temp;
}

GLuint Renderer::CreateBmpTexture(char * filePath)
{
	//Load Bmp: Load file and decode image.
	unsigned int width, height;
	unsigned char * bmp
		= loadBMPRaw(filePath, width, height);

	if (bmp == NULL)
	{
		std::cout << "Error while loading bmp file : " << filePath << std::endl;
		assert(bmp != NULL);
		return -1;
	}

	GLuint temp;
	glGenTextures(1, &temp);

	glBindTexture(GL_TEXTURE_2D, temp);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bmp);

	return temp;
}

float radian = 0.f;

void Renderer::DrawRect()	// 사각형 그리기
{
	glUseProgram(m_SolidRectShader);

	GLuint uTimeID = glGetUniformLocation(m_SolidRectShader, "u_Time");
	GLuint aPosID = glGetAttribLocation(m_SolidRectShader, "a_Position");
	GLuint aColID = glGetAttribLocation(m_SolidRectShader, "a_Color");	// color 사용안하면 이상한값 호출됨
	
	radian += 0.1f;
	glUniform1f(uTimeID, radian);	// 매 프레임마다 1번씩 CPU-> GPU




	//int attribPosition = glGetAttribLocation(m_SolidRectShader, "a_Position");
	glEnableVertexAttribArray(aPosID);	// == glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);// 총 18개의 float 포인터가 들어가 있음 6개 (x,y,z)
	glVertexAttribPointer(aPosID, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0); // 4개 x,y,z,value 읽고 4개씩 건너 뛰어라
	// == glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0); // 3개 x,y,z만 읽고 4개씩 건너 뛰어라
	// array에서 m_VBORect에 들어가 내용물을 3개씩 끊어서
	// == glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);	

	glEnableVertexAttribArray(aColID); // == glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORectcolor);
	glVertexAttribPointer(aColID, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	// == glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);	// 그려라! 함수, GL_TRIANGLES : 프리미티브 (삼각형 형태로 안을 칠해라), 6개의 vertex를 그려라
	// 0번째에서 시작을 해서 6개씩 읽으면서 그려라

	glDisableVertexAttribArray(aPosID);
	glDisableVertexAttribArray(aColID);
}

void Renderer::DrawTriangle()
{
	glUseProgram(m_SolidRectShader);

	int attribPosition = glGetAttribLocation(m_SolidRectShader, "a_Position");
	glEnableVertexAttribArray(attribPosition);
	
	
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture);	// ***************삼각형 그리기

	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);// 0번지에서 3개식 float형태로 몰라도되고, 0,0

	glDrawArrays(GL_TRIANGLES, 0, 3);	//

	glDisableVertexAttribArray(attribPosition);
	
}

void Renderer::DrawRandRect()
{
	glUseProgram(m_SolidRectShader);

	int attribPosition = glGetAttribLocation(m_SolidRectShader, "a_Position");
	glEnableVertexAttribArray(attribPosition);

	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBOQuads);

		glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);// 0번지에서 3개식 float형태로 몰라도되고, 0,0	3==4

		glDrawArrays(GL_TRIANGLES, 0, m_VBOQuads_VertexCount);	// 3 == m_VBOQuads_VertexCount

		glDisableVertexAttribArray(attribPosition);
	}
}

void Renderer::DrawGridMesh()
{
	glUseProgram(m_SolidRectShader);

	int attribPosition = glGetAttribLocation(m_SolidRectShader, "a_Position");
	glEnableVertexAttribArray(attribPosition);

	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBOGrid);

		glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

		glDrawArrays(GL_TRIANGLES, 0, m_VBOGrid_VertexCount);

		glDisableVertexAttribArray(attribPosition);
	}
}

void Renderer::DrawProxyGeometry()
{
	glUseProgram(m_SolidRectShader);

	int attribPosition = glGetAttribLocation(m_SolidRectShader, "a_Position");
	glEnableVertexAttribArray(attribPosition);

	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO_ProxyGeo);	

		glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);	//	float 포인터3개씩 float size 3개씩 넘어간다
		
		glDrawArrays(GL_LINE_STRIP, 0, m_Count_ProxyGeo);

		glDisableVertexAttribArray(attribPosition);
	}
}

float p_time = 0.f;

void Renderer::DrawSimpleVel(){
	glUseProgram(m_SimpleVelShader);

	GLuint uTimeID = glGetUniformLocation(m_SimpleVelShader, "u_Time");
	GLuint uPosID = glGetAttribLocation(m_SimpleVelShader, "a_Position");
	GLuint uVelID = glGetAttribLocation(m_SimpleVelShader, "a_Vel");
	
	p_time +=1.f;
	glUniform1f(uTimeID, p_time);

	glEnableVertexAttribArray(uPosID);	// 시험에서 잘틀려
	glEnableVertexAttribArray(uVelID);
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBOQuads);

		//
		// x1, y1, z1, vx1, vy1, vz1,  x2, y2, z2, vx2, vy2, vz2, .......  로 저장
		//

		// uPosID는 위치만 가져와야되
		glVertexAttribPointer(uPosID, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
		// float 포인트 3개씩 읽어온다 (위치)
		// float 포인트 처음부터 6개씩 건너 뛴다

		// uVelID는 속도만 가져와야되
		glVertexAttribPointer(uVelID, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (GLvoid*)(sizeof(float)*3));
		// float 포인트 3개씩 읽어온다 (위치)
		// float 포인트 처음부터 6개씩 건너 뛴다
		// 처음위치를 sizeof(float) * )만큼 변경한다.

		glDrawArrays(GL_TRIANGLES, 0, m_VBOQuads_VertexCount);	// 3 == m_VBOQuads_VertexCount

		glDisableVertexAttribArray(uPosID);
		glDisableVertexAttribArray(uVelID);
	}
}

void Renderer::DrawGravity(){
	glUseProgram(m_GravityShader);

	GLuint uTimeID = glGetUniformLocation(m_GravityShader, "u_Time");
	GLuint uRepeat = glGetUniformLocation(m_GravityShader, "u_Repeat");
	GLuint aPosID = glGetAttribLocation(m_GravityShader, "a_Position");
	GLuint aVelID = glGetAttribLocation(m_GravityShader, "a_Vel");
	GLuint aStartLife = glGetAttribLocation(m_GravityShader, "a_StartLife");
	p_time += 1.f / 6000.f ;
	glUniform1f(uTimeID, p_time);

	glEnableVertexAttribArray(aPosID);	// 시험에서 잘틀려
	glEnableVertexAttribArray(aVelID);
	glEnableVertexAttribArray(aStartLife);

	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBOQuads);

		// 0x 1y 2z 3vx 4vy 5vz 6s 7l 8x 9y 10z 11vx 12vy 13vz 14s 15l 16x 17y 18z 19vx 20vy 21vz 22s 23l 

		glVertexAttribPointer(aPosID, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
		glVertexAttribPointer(aVelID, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid*)(sizeof(float) * 3));
		glVertexAttribPointer(aStartLife, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid*)(sizeof(float) * 6));
		
		glDrawArrays(GL_TRIANGLES, 0, m_VBOQuads_VertexCount);	// 3 == m_VBOQuads_VertexCount

		glDisableVertexAttribArray(aPosID);
		glDisableVertexAttribArray(aVelID);
	}
}

void Renderer::DrawSinGraph() {
	GLuint Shader = m_SingraphShader;

	glUseProgram(Shader);
	
	GLuint uTimeID = glGetUniformLocation(Shader, "u_Time");
	glUniform1f(uTimeID, p_time);
	p_time += 1.f / 6000.f;

	GLuint aPosID = glGetAttribLocation(Shader, "a_Position");

	GLuint aStartLifeID = glGetAttribLocation(Shader, "a_StartLifeTime");

	glEnableVertexAttribArray(aPosID);	// 시험에서 잘틀려
	glEnableVertexAttribArray(aStartLifeID);

	int ObjectVertex = 9;
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO_SinGraph);

		// 0x 1y 2z 3vx 4vy 5vz 6s 7l 8x 9y 10z 11vx 12vy 13vz 14s 15l 16x 17y 18z 19vx 20vy 21vz 22s 23l 

		glVertexAttribPointer(aPosID, 3, GL_FLOAT, GL_FALSE, sizeof(float) * ObjectVertex, 0);
		glVertexAttribPointer(aStartLifeID, 2, GL_FLOAT, GL_FALSE, sizeof(float) * ObjectVertex, (GLvoid*)(sizeof(float)*6));

		glDrawArrays(GL_TRIANGLES, 0, m_Count_SinGraph);	// 3 == m_VBOQuads_VertexCount

		glDisableVertexAttribArray(aPosID);
		glDisableVertexAttribArray(aStartLifeID);
	}
}

void Renderer::DrawDirectionSin() {
	GLuint Shader = m_DirectionSinShader;

	glUseProgram(Shader);

	GLuint uTimeID = glGetUniformLocation(Shader, "u_Time");
	glUniform1f(uTimeID, p_time);
	p_time += 1.f / 6000.f;

	GLuint aPosID = glGetAttribLocation(Shader, "a_Position");
	GLuint aVelID = glGetAttribLocation(Shader, "a_Vel");
	GLuint aStartLifeRatioAmpID = glGetAttribLocation(Shader, "a_StartLifeRatioAmp");
	GLuint aRandVID = glGetAttribLocation(Shader, "a_RandV");

	glEnableVertexAttribArray(aPosID);	// 시험에서 잘틀려
	glEnableVertexAttribArray(aVelID);
	glEnableVertexAttribArray(aStartLifeRatioAmpID);
	glEnableVertexAttribArray(aRandVID);

	int ObjectVertex = 11;
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO_DirectionSinGraph);

		// 0x 1y 2z 3vx 4vy 5vz 6s 7l 8r 9a 

		glVertexAttribPointer(aPosID, 3, GL_FLOAT, GL_FALSE, sizeof(float) * ObjectVertex, 0);
		glVertexAttribPointer(aVelID, 3, GL_FLOAT, GL_FALSE, sizeof(float) * ObjectVertex, (GLvoid*)(sizeof(float) * 3));
		glVertexAttribPointer(aStartLifeRatioAmpID, 4, GL_FLOAT, GL_FALSE, sizeof(float) * ObjectVertex, (GLvoid*)(sizeof(float) * 6));
		glVertexAttribPointer(aRandVID, 1, GL_FLOAT, GL_FALSE, sizeof(float) * ObjectVertex, (GLvoid*)(sizeof(float) * 10));

		glDrawArrays(GL_TRIANGLES, 0, m_Count_DirectionSinGraph);	// 3 == m_VBOQuads_VertexCount

		glDisableVertexAttribArray(aPosID);
		glDisableVertexAttribArray(aVelID);
		glDisableVertexAttribArray(aStartLifeRatioAmpID);
		glDisableVertexAttribArray(aRandVID);
	}
}

void Renderer::DrawFragmentBase() {
	GLuint Shader = m_FragmentBaseShader;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glUseProgram(Shader);

	GLuint uTimeID = glGetUniformLocation(Shader, "u_Time");
	glUniform1f(uTimeID, p_time);
	p_time += 1.f / 6000.f;

	GLuint aPosID = glGetAttribLocation(Shader, "a_Position");
	GLuint aVelID = glGetAttribLocation(Shader, "a_Vel");
	GLuint aStartLifeRatioAmpID = glGetAttribLocation(Shader, "a_StartLifeRatioAmp");
	GLuint aRandVID = glGetAttribLocation(Shader, "a_RandV");
	GLuint aRGBID = glGetAttribLocation(Shader, "a_RGB");


	glEnableVertexAttribArray(aPosID);	// 시험에서 잘틀려
	glEnableVertexAttribArray(aVelID);
	glEnableVertexAttribArray(aStartLifeRatioAmpID);
	glEnableVertexAttribArray(aRandVID);
	glEnableVertexAttribArray(aRGBID);

	int ObjectVertex = 15;
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO_FragmentBase);

		// 0x 1y 2z 3vx 4vy 5vz 6s 7l 8r 9a 

		glVertexAttribPointer(aPosID, 3, GL_FLOAT, GL_FALSE, sizeof(float) * ObjectVertex, 0);
		glVertexAttribPointer(aVelID, 3, GL_FLOAT, GL_FALSE, sizeof(float) * ObjectVertex, (GLvoid*)(sizeof(float) * 3));
		glVertexAttribPointer(aStartLifeRatioAmpID, 4, GL_FLOAT, GL_FALSE, sizeof(float) * ObjectVertex, (GLvoid*)(sizeof(float) * 6));
		glVertexAttribPointer(aRandVID, 1, GL_FLOAT, GL_FALSE, sizeof(float) * ObjectVertex, (GLvoid*)(sizeof(float) * 10));
		glVertexAttribPointer(aRGBID, 4, GL_FLOAT, GL_FALSE, sizeof(float) * ObjectVertex, (GLvoid*)(sizeof(float) * 11));

		glDrawArrays(GL_TRIANGLES, 0, m_Count_FragmentBase);	// 3 == m_VBOQuads_VertexCount

		glDisableVertexAttribArray(aPosID);
		glDisableVertexAttribArray(aVelID);
		glDisableVertexAttribArray(aStartLifeRatioAmpID);
		glDisableVertexAttribArray(aRandVID);
		glDisableVertexAttribArray(aRGBID);
	}
}

void Renderer::DrawInterpolationBase() {
	GLuint Shader = m_InterpolationBaseShader;

	glUseProgram(Shader);


	GLuint aPosID = glGetAttribLocation(Shader, "a_Position");
	GLuint aUVID = glGetAttribLocation(Shader, "a_UV");

	glEnableVertexAttribArray(aPosID);	// 시험에서 잘틀려
	glEnableVertexAttribArray(aUVID);

	int ObjectVertex = 15;
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO_InterpolationBase);

		// 0x 1y 2z 3vx 4vy 5vz 6s 7l 8r 9a 

		glVertexAttribPointer(aPosID, 3, GL_FLOAT, GL_FALSE, sizeof(float) * ObjectVertex, 0);
		glVertexAttribPointer(aUVID, 2, GL_FLOAT, GL_FALSE, sizeof(float) * ObjectVertex, (GLvoid*)(sizeof(float) * 3));
		
		glDrawArrays(GL_TRIANGLES, 0, m_Count_InterpolationBase);	// 3 == m_VBOQuads_VertexCount

		glDisableVertexAttribArray(aPosID);
		glDisableVertexAttribArray(aUVID);
	}
}

void Renderer::DrawRadar() {
	GLuint Shader = m_RadarShader;

	glUseProgram(Shader);

	float points[] = { -0.25, 0.25, -0.25, -0.25, -0, 0, 0.25, -0.25, 0.25, 0.25 };

	GLuint aPosID = glGetAttribLocation(Shader, "a_Position");
	GLuint aUVID = glGetAttribLocation(Shader, "a_UV");
	
	GLuint uPointsID = glGetUniformLocation(Shader, "u_Points");
	glUniform2fv(uPointsID, 5, points);

	GLuint uTimeID = glGetUniformLocation(Shader, "u_Time");
	p_time += 0.0001f;
	glUniform1f(uTimeID, p_time);

	//int uTex = glGetUniformLocation(Shader, "uTexSampler");
	//glUniform1i(uTex, 0);
	//glActiveTexture(GL_TEXTURE0);	// 0번지 텍스쳐를쓰겠다
	//glBindTexture(GL_TEXTURE_2D, m_ParticleTexture0);


	glEnableVertexAttribArray(aPosID);	// 시험에서 잘틀려
	glEnableVertexAttribArray(aUVID);

	int ObjectVertex = 15;
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO_Radar);

		// 0x 1y 2z 3vx 4vy 5vz 6s 7l 8r 9a 

		glVertexAttribPointer(aPosID, 3, GL_FLOAT, GL_FALSE, sizeof(float) * ObjectVertex, 0);
		glVertexAttribPointer(aUVID, 2, GL_FLOAT, GL_FALSE, sizeof(float) * ObjectVertex, (GLvoid*)(sizeof(float) * 3));

		glDrawArrays(GL_TRIANGLES, 0, m_Count_Radar);	// 3 == m_VBOQuads_VertexCount

		glDisableVertexAttribArray(aPosID);
		glDisableVertexAttribArray(aUVID);
	}
}

void Renderer::FillAlpha(float alpha) {
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, alpha);

}
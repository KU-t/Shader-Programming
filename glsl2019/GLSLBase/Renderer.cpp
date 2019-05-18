#include "stdafx.h"
#include "Renderer.h"
#include "LoadPng.h"
#include <Windows.h>
#include <cstdlib>
#include <cassert>
#include <iostream>

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
	m_RandQuadsShader = CompileShaders("./Shaders/0313RandRect.vs", "./Shaders/0313RandRect.fs");
	m_GridMeshShader = CompileShaders("./Shaders/0317GridMesh.vs", "./Shaders/0317GridMesh.fs");
	m_SimpleVelShader = CompileShaders("./Shaders/0325Simplevel.vs", "./Shaders/0325Simplevel.fs");
	m_GravityShader = CompileShaders("./Shaders/0327Gravity.vs", "./Shaders/0327Gravity.fs");
	m_SingraphShader = CompileShaders("./Shaders/0401SinGraph.vs", "./Shaders/0401SinGraph.fs");
	m_DirectionSinShader = CompileShaders("./Shaders/0403DirectionSinGraph.vs", "./Shaders/0403DirectionSinGraph.fs");
	m_FragmentBaseShader = CompileShaders("./Shaders/0408FragmentBase.vs", "./Shaders/0408FragmentBase.fs");
	m_InterpolationBaseShader = CompileShaders("./Shaders/0410InterpolationBase.vs", "./Shaders/0410InterpolationBase.fs");
	m_RadarShader = CompileShaders("./Shaders/0415Radar.vs", "./Shaders/0415Radar.fs");
	m_TextureMapping = CompileShaders("./Shaders/0417TextureMapping.vs", "./Shaders/0417TextureMapping.fs");
	m_TextureMaking = CompileShaders("./Shaders/0429TextureMaking.vs", "./Shaders/0429TextureMaking.fs");
	m_TextureTransUV = CompileShaders("./Shaders/0501TextureTransUV.vs", "./Shaders/0501TextureTransUV.fs");
	m_Textures = CompileShaders("./Shaders/0508Textures.vs", "./Shaders/0508Textures.fs");
	m_TexturesAnimation = CompileShaders("./Shaders/0513Animation.vs", "./Shaders/0513Animation.fs");
	m_TexturesRect = CompileShaders("./Shaders/0515TextureNumber.vs", "./Shaders/0515TextureNumber.fs");
	m_TexturesRects = CompileShaders("./Shaders/0515TextureNumbers.vs", "./Shaders/0515TextureNumbers.fs");

	//Load Textures
	m_TextureFence = CreatePngTexture("./Textures/Fence.png");
	m_TextureSky = CreatePngTexture("./Textures/Sky.png");
	m_TextureLUFFY = CreatePngTexture("./Textures/LUFFY.png");
	m_TextureRGB = CreatePngTexture("./Textures/rgb.png");
	m_TextureNumber = CreatePngTexture("./Textures/Numbers/Numbers.png");

	//Create VBOs
	CreateVertexBufferObjects();
}

void Renderer::CreateVertexBufferObjects(){
	//DrawRect() init
	//GenQuadsVBO_Rect();

	//DrawTri() init
	//GenQuadsVBO_Tri();

	//DrawRandRect() init
	//GenQuadsVBO_Rand(1000);

	//DrawGridMesh() init
	//GenQuadsVBO_GridMesh();

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

	//DrawRadar(); init
	//GenQuadsVBO_Radar(&m_VBO_Radar, &m_Count_Radar);

	//DrawTextureMapping(); init
	//GenQuadsVBO_TextureMapping(&m_VBO_TextureMapping, &m_Count_TextureMapping);

	//DrawTextureSampling(); init
	//GenQuadsVBO_TextureMaking(&m_VBO_TextureMaking, &m_Count_TextureMaking);

	//DrawDrawTextureTransUV(); init
	//GenQuadsVBO_TextureTransUV(&m_VBO_TextureTransUV, &m_Count_TextureTransUV);

	//DrawTextures(); init
	//GenQuadsVBO_Textures(&m_VBO_Textures, &m_Count_Textures);

	//DrawTexturesAnimation(); init
	//GenQuadsVBO_TexturesAnimation(&m_VBO_TexturesAnimation, &m_Count_TexturesAnimation);

	//DrawNumber() || DrawNumbers(); init
	GenQuadsVBO_TexturesRect(&m_VBO_TexturesRect, &m_Count_TexturesRect);
}

void Renderer::GenQuadsVBO_Rect() {
	
	float size = 0.4f;
	// DrawRect()  init
	float rect[] = {
		// xyz,xyz,xyz 3��
		// xyz, value
	-size, -size, 0.f, 0.5f,
	-size, size, 0.f, 0.5f,
	size, size, 0.f, 0.5f, //Triangle1
	-size, -size, 0.f, 0.5f,
	size, size, 0.f, 0.5f,
	size, -size, 0.f, 0.5f //Triangle2
	};

	glGenBuffers(1, &m_VBORect);	// m_VBORect�� rect[] ����ڴ�.
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);	// GL_ARRAY_BUFFER �� �ϳ��� ����, Bind �����ؼ� ����
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);	// GPU������ �ø� , GL_STATIC_DRAW : �ٲ��� �ʴ� �� (���� ���� ����)

	float color[] = {

	0.0, 0.0, 0.f, 1.f,
	0.0, 1.0, 0.f, 1.f,
	1.0, 1.0, 0.f, 1.f, //Triangle1
	0.0, 0.0, 0.f, 1.f,
	1.0, 1.0, 0.f, 1.f,
	1.0, 0.0, 0.f, 1.f //Triangle2
	};

	glGenBuffers(1, &m_VBORectcolor);	// m_VBORectcolor�� color[] ����ڴ�.
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORectcolor);	// GL_ARRAY_BUFFER �� �ϳ��� ����, Bind �����ؼ� ����
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);	// GPU������ �ø� , GL_STATIC_DRAW : �ٲ��� �ʴ� �� (���� ���� ����)

}

void Renderer::GenQuadsVBO_Tri() {
	float triangleVertex[] = { -1,0,0,0,1,0,1,0,0 };	//9float

	glGenBuffers(1, &m_VBOTri);	// ������ �ϳ� ��� ���� m_VBOLecture�� ����ְ� �����.
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTri);	//	�̳��� �ø��µ� ����� GL_ARRAY_BUFFER, �ø���  m_VBOTri
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertex), triangleVertex, GL_STATIC_DRAW);	// ���� ����Ÿ�� ���� gpu �޸𸮿� �ø��� �۾�, triangleVertex �����ŭ �ø��Ű� 
}

void Renderer::GenQuadsVBO_Rand(int count){
	float randX, randY;
	float size = 0.002f;
	float arraySize = count * 3 * 6;	// �簢�� 1���� 6���� ��/ 1���� ������ 3���� xyz��ǥ / �簢�� count��
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

	glGenBuffers(1, &m_VBORandQuads);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORandQuads);	// ���� array�������� ���ڴ�.
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * arraySize, vertices, GL_STATIC_DRAW);

	m_VBORandQuads_VertexCount = 6 * count;
}

void Renderer::GenQuadsVBO_GridMesh()
{
	float StartPointX = -0.5f;
	float StartPointY = -0.5f;
	float	EndPointX = 0.5f;
	float EndPointY = 0.5f;

	int PointCountX = 32;
	int PointCountY = 32;

	float Width = EndPointX - StartPointX;
	float Height = EndPointY - StartPointY;

	float* point = new float[PointCountX * PointCountY * 2];
	float* vertices = new float[(PointCountX - 1)*(PointCountY - 1) * 2 * 3 * 3];

	for (int x = 0; x < PointCountX; x++) {
		for (int y = 0; y < PointCountY; y++) {
			point[(y + PointCountX * x) * 2 + 0] = StartPointX + Width * (x/(float)(PointCountX - 1));
			point[(y + PointCountX * x) * 2 + 1] = StartPointY + Height * (y/(float)(PointCountY - 1));
		}
	}

	int PointIndex = 0;

	for (int x = 0; x < PointCountX - 1; x++) {
		for (int y = 0; y < PointCountX - 1; y++) {
			vertices[PointIndex++] = point[(y + PointCountX * x) * 2 + 0];
			vertices[PointIndex++] = point[(y + PointCountX * x) * 2 + 1];
			vertices[PointIndex++] = 0.f;

			vertices[PointIndex++] = point[((y + 1) + PointCountX * (x + 1)) * 2 + 0];
			vertices[PointIndex++] = point[((y + 1) + PointCountX * (x + 1)) * 2 + 1];
			vertices[PointIndex++] = 0.f;

			vertices[PointIndex++] = point[((y+1) + PointCountX * x) * 2 + 0];
			vertices[PointIndex++] = point[((y+1) + PointCountX * x) * 2 + 1];
			vertices[PointIndex++] = 0.f;

			vertices[PointIndex++] = point[(y + PointCountX * x) * 2 + 0];
			vertices[PointIndex++] = point[(y + PointCountX * x) * 2 + 1];
			vertices[PointIndex++] = 0.f;

			vertices[PointIndex++] = point[(y + PointCountX * (x+1)) * 2 + 0];
			vertices[PointIndex++] = point[(y + PointCountX * (x+1)) * 2 + 1];
			vertices[PointIndex++] = 0.f;

			vertices[PointIndex++] = point[((y + 1) + PointCountX * (x + 1)) * 2 + 0];
			vertices[PointIndex++] = point[((y + 1) + PointCountX * (x + 1)) * 2 + 1];
			vertices[PointIndex++] = 0.f;
		}
	}

	glGenBuffers(1, &m_VBOGrid);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOGrid);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (PointCountX - 1)*(PointCountY - 1) * 2 * 3 * 3, vertices, GL_STATIC_DRAW);

	m_VBOGrid_VertexCount = (PointCountX - 1)*(PointCountY - 1) * 2 * 3;
}

void Renderer::GenQuadsVBO_Vel(int count)
{
	int verticesPerQuad = 6;	// �簢���� ��� vertex
	int floatsPervertex = 3 + 3;	// xyz, velx, vely, velz, 
	int countQuad = count;	// ��� ����

	float size = 0.002f;
	int arraySize = countQuad * verticesPerQuad * floatsPervertex;	// 3��� 4 // vertex����
	float *vertices = new float[arraySize];

	for (int i = 0; i < countQuad; i++) {
		
		int index = i * verticesPerQuad * floatsPervertex;	// 24 // �ѷ����� ����
		
		float randX, randY;
		float randVelX, randVelY, randVelZ;

		randX = 2.f * (((float)rand() / RAND_MAX) - 0.5);
		randY = 2.f * (((float)rand() / RAND_MAX) - 0.5);

		randVelX = 2.f * (((float)rand() / RAND_MAX) - 0.5);
		randVelY = 2.f * (((float)rand() / RAND_MAX) - 0.5);
		randVelZ = 0.f;

		{
			// 1����
			vertices[index] = randX - size;	index++;
			vertices[index] = randY - size;	index++;
			vertices[index] = 0.f;					index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			//vertices[index] = (float)i;	index++;

			// 2��°
			vertices[index] = randX - size;	index++;
			vertices[index] = randY + size;	index++;
			vertices[index] = 0.f;					index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			//vertices[index] = (float)i;	index++;

			// 3��°
			vertices[index] = randX + size;	index++;
			vertices[index] = randY + size;	index++;
			vertices[index] = 0.f;					index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			//vertices[index] = (float)i;	index++;

		}

		{
			// 4��°
			vertices[index] = randX - size;	index++;
			vertices[index] = randY - size;	index++;
			vertices[index] = 0.f;					index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			//vertices[index] = (float)i;	index++;

			// 5��°
			vertices[index] = randX + size;		index++;
			vertices[index] = randY - size;		index++;
			vertices[index] = 0.f;						index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			//vertices[index] = (float)i;	index++;

			// 6��°
			vertices[index] = randX + size;		index++;
			vertices[index] = randY + size;		index++;
			vertices[index] = 0.f;						index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			//vertices[index] = (float)i;	index++;
		}
	}

	glGenBuffers(1, &m_VBOSimpleVel);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOSimpleVel);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * arraySize, vertices, GL_STATIC_DRAW);

	m_VBOSimpleVel_VertexCount = 6 * count;
}

void Renderer::GenQuadsVBO_Gra(int count) {
	int verticesPerQuad = 6;	// �簢���� ��� vertex
	int floatsPervertex = 3 + 3 + 2;	// xyz, velx, vely, velz, lifetime, starttime
	int countQuad = count;	// ��� ����

	float size = 0.002f;
	int arraySize = countQuad * verticesPerQuad * floatsPervertex;	// 3��� 4 // vertex����
	float *vertices = new float[arraySize];

	for (int i = 0; i < countQuad; i++) {

		int index = i * verticesPerQuad * floatsPervertex;	// 24 // �ѷ����� ����

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
			// 1����
			vertices[index] = randX - size;	index++;
			vertices[index] = randY - size;	index++;
			vertices[index] = 0.f;					index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			vertices[index] = startTime;			index++;
			vertices[index] = lifeTime;				index++;
			//vertices[index] = (float)i;	index++;

			// 2��°
			vertices[index] = randX - size;	index++;
			vertices[index] = randY + size;	index++;
			vertices[index] = 0.f;					index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			vertices[index] = startTime;			index++;
			vertices[index] = lifeTime;				index++;
			//vertices[index] = (float)i;	index++;

			// 3��°
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
			// 4��°
			vertices[index] = randX - size;	index++;
			vertices[index] = randY - size;	index++;
			vertices[index] = 0.f;					index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			vertices[index] = startTime;			index++;
			vertices[index] = lifeTime;				index++;
			//vertices[index] = (float)i;	index++;

			// 5��°
			vertices[index] = randX + size;		index++;
			vertices[index] = randY - size;		index++;
			vertices[index] = 0.f;						index++;

			vertices[index] = randVelX;			index++;
			vertices[index] = randVelY;			index++;
			vertices[index] = randVelZ;			index++;

			vertices[index] = startTime;			index++;
			vertices[index] = lifeTime;				index++;
			//vertices[index] = (float)i;	index++;

			// 6��°
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

	glGenBuffers(1, &m_VBOGravity);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOGravity);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * arraySize, vertices, GL_STATIC_DRAW);

	m_VBOGravity_VertexCount = 6 * count;
}

void Renderer::GenQuadsVBO_Sin(int count,bool random, GLuint* ID,GLuint* vCount) {
	int verticesPerQuad = 6;	// �簢���� ��� vertex
	int floatsPervertex = 3 + 3 + 3;	// xyz, velx, vely, velz, starttime, lifetime, input
	int countQuad = count;	// ��� ����

	float size = 0.002f;
	int arraySize = countQuad * verticesPerQuad * floatsPervertex;	 // vertex����
	float *vertices = new float[arraySize];

	for (int i = 0; i < countQuad; i++) {

		int index = i * verticesPerQuad * floatsPervertex;	 // �ѷ����� ����

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
			// 1����
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

			// 2��°
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

			// 3��°
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
			// 4��°
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

			// 5��°
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

			// 6��°
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

	glGenBuffers(1, &vboID);//vbo�� 0 ���� ����µ� �̰� ���̵�� ���ڴ�. �̷��� �Ⱦ��� vboID�� m_VBO_�����ΰɷ� �ٲ��ߴ�
	glBindBuffer(GL_ARRAY_BUFFER, vboID);// ���� array�������� ���ڴ�.
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * arraySize, vertices, GL_STATIC_DRAW);

	*vCount = countQuad * verticesPerQuad;
	*ID = vboID;
}

void Renderer::GenQuadsVBO_DirectionSin(int count, bool random, GLuint* ID, GLuint* vCount) {
	int verticesPerQuad = 6;	// �簢���� ��� vertex
	int floatsPervertex = 3 + 3 + 5;	// xyz, velx, vely, velz, starttime, lifetime, input
	int countQuad = count;	// ��� ����

	float size = 0.001f;
	int arraySize = countQuad * verticesPerQuad * floatsPervertex;	 // vertex����
	float *vertices = new float[arraySize];

	for (int i = 0; i < countQuad; i++) {

		int index = i * verticesPerQuad * floatsPervertex;	 // �ѷ����� ����

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
			// 1����
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

			// 2��°
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

			// 3��°
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
			// 4��°
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

			// 5��°
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

			// 6��°
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
	int verticesPerQuad = 6;	// �簢���� ��� vertex
	int floatsPervertex = 3 + 3 + 5 + 4;	// xyz, velx, vely, velz, starttime, lifetime, ratio, amp, Value, R, G, B, a
	int countQuad = count;	// ��� ����

	float size = 0.02f;
	int arraySize = countQuad * verticesPerQuad * floatsPervertex;	 // vertex����
	float *vertices = new float[arraySize];

	for (int i = 0; i < countQuad; i++) {

		int index = i * verticesPerQuad * floatsPervertex;	 // �ѷ����� ����

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
			// 1����
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

			// 2��°
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

			// 3��°
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
			// 4��°
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

			// 5��°
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

			// 6��°
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

	int verticesPerQuad = 6;	// �簢���� ��� vertex
	int floatsPervertex = 3 + 2 + 5 + 5;	// xyz, uv, empty10

	float size = 0.5f;
	int arraySize =  verticesPerQuad * floatsPervertex;	 // vertex����
	float *vertices = new float[arraySize];

	{
		int index = 0;	 // �ѷ����� ����

		float randX = 0.f, randY = 0.f;

		{
			// 1����
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

			// 2��°
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

			// 3��°
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
			// 4��°
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

			// 5��°
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

			// 6��°
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

	int verticesPerQuad = 6;	// �簢���� ��� vertex
	int floatsPervertex = 3 + 2 + 5 + 5;	// xyz, uv, empty10

	float size = 1.f;
	int arraySize = verticesPerQuad * floatsPervertex;	 // vertex����
	float *vertices = new float[arraySize];

	{
		int index = 0;	 // �ѷ����� ����

		float randX = 0.f, randY = 0.f;

		{
			// 1����
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

			// 2��°
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

			// 3��°
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
			// 4��°
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

			// 5��°
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

			// 6��°
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

void Renderer::GenQuadsVBO_TextureMapping(GLuint * ID, GLuint * vCount) {

	int verticesPerQuad = 6;	// �簢���� ��� vertex
	int floatsPervertex = 3 + 2 + 5 + 5;	// xyz, uv, empty10

	float size = 0.5f;
	int arraySize = verticesPerQuad * floatsPervertex;	 // vertex����
	float *vertices = new float[arraySize];

	{
		int index = 0;	 // �ѷ����� ����

		float randX = 0.f, randY = 0.f;

		{
			// 1����
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

			// 2��°
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

			// 3��°
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
			// 4��°
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

			// 5��°
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

			// 6��°
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

void Renderer::GenQuadsVBO_TextureMaking(GLuint * ID, GLuint * vCount) {

	int verticesPerQuad = 6;	// �簢���� ��� vertex
	int floatsPervertex = 3 + 2 + 5 + 5;	// xyz, uv, empty10

	float size = 0.5f;
	int arraySize = verticesPerQuad * floatsPervertex;	 // vertex����
	float *vertices = new float[arraySize];

	{
		int index = 0;	 // �ѷ����� ����

		float randX = 0.f, randY = 0.f;

		{
			// 1����
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

			// 2��°
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

			// 3��°
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
			// 4��°
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

			// 5��°
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

			// 6��°
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

	static const GLulong checkerboard[] =
	{
	0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000,
	0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF,
	0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000,
	0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF,
	0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000,
	0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF,
	0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000,
	0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF
	};

	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkerboard);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

}

void Renderer::GenQuadsVBO_TextureTransUV(GLuint * ID, GLuint * vCount) {

	int verticesPerQuad = 6;	// �簢���� ��� vertex
	int floatsPervertex = 3 + 2 + 5 + 5;	// xyz, uv, empty10

	float size = 0.5f;
	int arraySize = verticesPerQuad * floatsPervertex;	 // vertex����
	float *vertices = new float[arraySize];

	{
		int index = 0;	 // �ѷ����� ����

		float randX = 0.f, randY = 0.f;

		{
			// 1����
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

			// 2��°
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

			// 3��°
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
			// 4��°
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

			// 5��°
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

			// 6��°
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

	static const GLulong checkerboard[] =
	{
	0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000,
	0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF,
	0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000,
	0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF,
	0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000,
	0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF,
	0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000,
	0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF
	};

	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkerboard);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

}

void Renderer::GenQuadsVBO_Textures(GLuint * ID, GLuint * vCount) {

	int verticesPerQuad = 6;	// �簢���� ��� vertex
	int floatsPervertex = 3 + 2 + 5 + 5;	// xyz, uv, empty10

	float size = 0.5f;
	int arraySize = verticesPerQuad * floatsPervertex;	 // vertex����
	float *vertices = new float[arraySize];

	{
		int index = 0;	 // �ѷ����� ����

		float randX = 0.f, randY = 0.f;

		{
			// 1����
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

			// 2��°
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

			// 3��°
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
			// 4��°
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

			// 5��°
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

			// 6��°
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

	GLulong textureSmile[]
		=
	{
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF,
	0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
	0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
	0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
	};
	glGenTextures(1, &gTextureID0);
	glBindTexture(GL_TEXTURE_2D, gTextureID0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureSmile);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	GLulong textureSmile1[]
		=
	{
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
	0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
	0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
	};
	glGenTextures(1, &gTextureID1);
	glBindTexture(GL_TEXTURE_2D, gTextureID1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureSmile1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	GLulong textureSmile2[]
		=
	{
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
	0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
	0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
	};
	glGenTextures(1, &gTextureID2);
	glBindTexture(GL_TEXTURE_2D, gTextureID2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureSmile2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	GLulong textureSmile3[]
		=
	{
	0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00,
	0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
	0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
	0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
	};
	glGenTextures(1, &gTextureID3);
	glBindTexture(GL_TEXTURE_2D, gTextureID3);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureSmile3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	GLulong textureSmile4[]
		=
	{
	0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00,
	0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
	0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
	0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
	};
	glGenTextures(1, &gTextureID4);
	glBindTexture(GL_TEXTURE_2D, gTextureID4);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureSmile4);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	GLulong textureSmile5[]
		=
	{
	0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00,
	0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00,
	0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
	0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
	};
	glGenTextures(1, &gTextureID5);
	glBindTexture(GL_TEXTURE_2D, gTextureID5);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureSmile5);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void Renderer::GenQuadsVBO_TexturesAnimation(GLuint * ID, GLuint * vCount) {

	float vertPosTex[30] =
	{
	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.0f, 1.0f, 0.0f
	};

	glGenBuffers(1, &m_VBO_TexturesAnimation);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_TexturesAnimation);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertPosTex), vertPosTex, GL_STATIC_DRAW);

	GLulong textureSmileTotal[]
		=
	{
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF,
	0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
	0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
	0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,

	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
	0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
	0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,

	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
	0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
	0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,

	0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00,
	0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
	0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
	0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,

	0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00,
	0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
	0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
	0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,

	0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00,
	0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00,
	0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
	0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
	};
	glGenTextures(1, &gTextureIDTotal);
	glBindTexture(GL_TEXTURE_2D, gTextureIDTotal);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 48, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureSmileTotal);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void Renderer::GenQuadsVBO_TexturesRect(GLuint * ID, GLuint * vCount) {

	float vertPosTex[30] =
	{
	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.0f, 1.0f, 0.0f
	};

	glGenBuffers(1, &m_VBO_TexturesRect);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_TexturesRect);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertPosTex), vertPosTex, GL_STATIC_DRAW);
}

void Renderer::AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType){

	// ShaderType = ��������

	//���̴� ������Ʈ ����
	GLuint ShaderObj = glCreateShader(ShaderType);

	if (ShaderObj == 0) {
		//Shader ���� ����
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
	}

	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];
	Lengths[0] = (GLint)strlen(pShaderText);
	//���̴� �ڵ带 ���̴� ������Ʈ�� �Ҵ�
	glShaderSource(ShaderObj, 1, p, Lengths);

	//�Ҵ�� ���̴� �ڵ带 ������
	glCompileShader(ShaderObj);

	GLint success;
	// ShaderObj �� ���������� ������ �Ǿ����� Ȯ��
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];

		//OpenGL �� shader log �����͸� ������
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		printf("%s \n", pShaderText);
	}

	// ShaderProgram �� attach!!
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
	GLuint ShaderProgram = glCreateProgram(); //�� ���̴� ���α׷� ����

	if (ShaderProgram == 0) { //���̴� ���α׷��� ����������� Ȯ��
		fprintf(stderr, "Error creating shader program\n");
	}

	std::string vs, fs;

	//shader.vs �� vs ������ �ε���
	if (!ReadFile(filenameVS, &vs)) {
		printf("Error compiling vertex shader\n");
		return -1;
	};

	//shader.fs �� fs ������ �ε���
	if (!ReadFile(filenameFS, &fs)) {
		printf("Error compiling fragment shader\n");
		return -1;
	};

	// ShaderProgram �� vs.c_str() ���ؽ� ���̴��� �������� ����� attach��
	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);

	// ShaderProgram �� fs.c_str() �����׸�Ʈ ���̴��� �������� ����� attach��
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };

	//Attach �Ϸ�� shaderProgram �� ��ŷ��
	glLinkProgram(ShaderProgram);

	//��ũ�� �����ߴ��� Ȯ��
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);

	if (Success == 0) {
		// shader program �α׸� �޾ƿ�
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

void Renderer::DrawRect()	// �簢�� �׸���
{
	glUseProgram(m_SolidRectShader);

	GLuint uTimeID = glGetUniformLocation(m_SolidRectShader, "u_Time");
	GLuint aPosID = glGetAttribLocation(m_SolidRectShader, "a_Position");
	GLuint aColID = glGetAttribLocation(m_SolidRectShader, "a_Color");	// color �����ϸ� �̻��Ѱ� ȣ���
	
	radian += 0.1f;
	glUniform1f(uTimeID, radian);	// �� �����Ӹ��� 1���� CPU-> GPU

	//int attribPosition = glGetAttribLocation(m_SolidRectShader, "a_Position");
	glEnableVertexAttribArray(aPosID);	// == glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);// �� 18���� float �����Ͱ� �� ���� 6�� (x,y,z)
	glVertexAttribPointer(aPosID, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0); // 4�� x,y,z,value �а� 4���� �ǳ� �پ��
	// == glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0); // 3�� x,y,z�� �а� 4���� �ǳ� �پ��
	// array���� m_VBORect�� �� ���빰�� 3���� ���
	// == glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);	

	glEnableVertexAttribArray(aColID); // == glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORectcolor);
	glVertexAttribPointer(aColID, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	// == glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);	// �׷���! �Լ�, GL_TRIANGLES : ������Ƽ�� (�ﰢ�� ���·� ���� ĥ�ض�), 6���� vertex�� �׷���
	// 0��°���� ������ �ؼ� 6���� �����鼭 �׷���

	glDisableVertexAttribArray(aPosID);
	glDisableVertexAttribArray(aColID);
}

void Renderer::DrawTriangle()
{
	glUseProgram(m_SolidRectShader);

	GLuint attribPosition = glGetAttribLocation(m_SolidRectShader, "a_Position");
	GLuint aColorID = glGetAttribLocation(m_SolidRectShader, "a_Color");
	GLuint rad = glGetUniformLocation(m_SolidRectShader, "u_Time");

	//solidRect.fs Į�� ����
	glEnableVertexAttribArray(attribPosition);
	radian += 0.1;
	glUniform1f(rad, radian);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTri);	// 

	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);// 0�������� 3���� float���·� ���󵵵ǰ�, 0,0

	glDrawArrays(GL_TRIANGLES, 0, 3);	//

	glDisableVertexAttribArray(attribPosition);
	
}

void Renderer::DrawRandRect()
{
	glUseProgram(m_RandQuadsShader);

	int attribPosition = glGetAttribLocation(m_RandQuadsShader, "a_Position");
	glEnableVertexAttribArray(attribPosition);

	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBORandQuads);

		glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);// 0�������� 3���� float���·� ���󵵵ǰ�, 0,0	3==4

		glDrawArrays(GL_TRIANGLES, 0, m_VBORandQuads_VertexCount);	// 6 * count == m_VBOQuads_VertexCount

		glDisableVertexAttribArray(attribPosition);
	}
}

void Renderer::DrawGridMesh()
{
	glUseProgram(m_GridMeshShader);

	glEnableVertexAttribArray(0);

	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBOGrid);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

		glDrawArrays(GL_LINE_STRIP, 0, m_VBOGrid_VertexCount);

		glDisableVertexAttribArray(0);
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

	glEnableVertexAttribArray(uPosID);	// ���迡�� ��Ʋ��
	glEnableVertexAttribArray(uVelID);
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBOSimpleVel);

		//
		// x1, y1, z1, vx1, vy1, vz1,  x2, y2, z2, vx2, vy2, vz2, .......  �� ����
		//

		// uPosID�� ��ġ�� �����;ߵ�
		glVertexAttribPointer(uPosID, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
		// float ����Ʈ 3���� �о�´� (��ġ)
		// float ����Ʈ ó������ 6���� �ǳ� �ڴ�

		// uVelID�� �ӵ��� �����;ߵ�
		glVertexAttribPointer(uVelID, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (GLvoid*)(sizeof(float)*3));
		// float ����Ʈ 3���� �о�´� (��ġ)
		// float ����Ʈ ó������ 6���� �ǳ� �ڴ�
		// ó����ġ�� sizeof(float) * )��ŭ �����Ѵ�.

		glDrawArrays(GL_TRIANGLES, 0, m_VBOSimpleVel_VertexCount);	// 6 * count == m_VBOQuads_VertexCount

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

	glEnableVertexAttribArray(aPosID);	// ���迡�� ��Ʋ��
	glEnableVertexAttribArray(aVelID);
	glEnableVertexAttribArray(aStartLife);

	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBOGravity);

		// 0x 1y 2z 3vx 4vy 5vz 6s 7l 8x 9y 10z 11vx 12vy 13vz 14s 15l 16x 17y 18z 19vx 20vy 21vz 22s 23l 

		glVertexAttribPointer(aPosID, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
		glVertexAttribPointer(aVelID, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid*)(sizeof(float) * 3));
		glVertexAttribPointer(aStartLife, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid*)(sizeof(float) * 6));
		
		glDrawArrays(GL_TRIANGLES, 0, m_VBOGravity_VertexCount);	// 6 * count == m_VBOQuads_VertexCount

		glDisableVertexAttribArray(aPosID);
		glDisableVertexAttribArray(aVelID);
		glDisableVertexAttribArray(aStartLife);
	}
}

void Renderer::DrawSinGraph() {
	GLuint Shader = m_SingraphShader;

	glUseProgram(Shader);
	
	GLuint uTimeID = glGetUniformLocation(Shader, "u_Time");
	p_time += 1.f / 6000.f;
	glUniform1f(uTimeID, p_time);

	GLuint aPosID = glGetAttribLocation(Shader, "a_Position");

	GLuint aStartLifeID = glGetAttribLocation(Shader, "a_StartLifeTime");

	glEnableVertexAttribArray(aPosID);	// ���迡�� ��Ʋ��
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
	p_time += 1.f / 6000.f;
	glUniform1f(uTimeID, p_time);

	GLuint aPosID = glGetAttribLocation(Shader, "a_Position");
	GLuint aVelID = glGetAttribLocation(Shader, "a_Vel");
	GLuint aStartLifeRatioAmpID = glGetAttribLocation(Shader, "a_StartLifeRatioAmp");
	GLuint aRandVID = glGetAttribLocation(Shader, "a_RandV");

	glEnableVertexAttribArray(aPosID);	// ���迡�� ��Ʋ��
	glEnableVertexAttribArray(aVelID);
	glEnableVertexAttribArray(aStartLifeRatioAmpID);
	glEnableVertexAttribArray(aRandVID);

	int ObjectVertex = 11;
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO_DirectionSinGraph);

		// 0x 1y 2z 3vx 4vy 5vz 6s 7l 8r 9a 10 11 

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


	glEnableVertexAttribArray(aPosID);	// ���迡�� ��Ʋ��
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

	float v[] = {0,0,0,0.2,0.2,0.2,0.2,0,0.1,0.1};
	GLuint uV = glGetUniformLocation(Shader, "u_Points");
	glUniform2fv(uV, 5, v);


	glEnableVertexAttribArray(aPosID);	// ���迡�� ��Ʋ��
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

	float points[] = { -0.25, 0.25, -0.25, -0.25, -0.1, 0.1, 0.25, -0.25, 0.25, 0.25 };

	GLuint aPosID = glGetAttribLocation(Shader, "a_Position");
	GLuint aUVID = glGetAttribLocation(Shader, "a_UV");
	
	GLuint uPointsID = glGetUniformLocation(Shader, "u_Points");
	glUniform2fv(uPointsID, 5, points);

	GLuint uTimeID = glGetUniformLocation(Shader, "u_Time");
	p_time += 0.0001f;

	glUniform1f(uTimeID, p_time);

	glEnableVertexAttribArray(aPosID);	// ���迡�� ��Ʋ��
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

void Renderer::DrawTextureMapping() {
	GLuint Shader = m_TextureMapping;

	glUseProgram(Shader);// �� ���α׷��� ���ڴ�. (==Shader)

	GLuint aPosID = glGetAttribLocation(Shader, "a_Position");//Shader�� s_Position��
	GLuint aUVID = glGetAttribLocation(Shader, "a_UV");

	GLuint uTimeID = glGetUniformLocation(Shader, "u_Time");
	p_time += 0.0001;
	glUniform1f(uTimeID, p_time);

	//attribute ���
	glEnableVertexAttribArray(aPosID);	// ���迡�� ��Ʋ��
	glEnableVertexAttribArray(aUVID);
	
	//int uTexID = glGetUniformLocation(Shader, "u_Texture");
	
	int ObjectVertex = 15;
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO_TextureMapping);

		glVertexAttribPointer(aPosID, 3, GL_FLOAT, GL_FALSE, sizeof(float) * ObjectVertex, 0);
		glVertexAttribPointer(aUVID, 2, GL_FLOAT, GL_FALSE, sizeof(float) * ObjectVertex, (GLvoid*)(sizeof(float) * 3));

		// Ʈ���̾ޱ��� �׸��� �� m_Count_TextureMapping���� �ﰢ���� �̿��� �׸���.
		glDrawArrays(GL_TRIANGLES, 0, m_Count_TextureMapping);

		glDisableVertexAttribArray(aPosID);
		glDisableVertexAttribArray(aUVID);
	}
}

void Renderer::DrawTextureMaking() {
	GLuint Shader = m_TextureMaking;

	glUseProgram(Shader);// �� ���α׷��� ���ڴ�. (==Shader)

	GLuint aPosID = glGetAttribLocation(Shader, "a_Position");//Shader�� s_Position��
	GLuint aUVID = glGetAttribLocation(Shader, "a_UV");

	GLuint uTimeID = glGetUniformLocation(Shader, "u_Time");
	p_time += 0.0001;
	glUniform1f(uTimeID, p_time);

	GLuint uTexID = glGetUniformLocation(Shader, "u_Texture");
	glUniform1i(uTexID, 0);
	glActiveTexture(GL_TEXTURE0);
	//BindTexture != BindBuffer
	glBindTexture(GL_TEXTURE_2D, m_TextureLUFFY);


	//attribute ���
	glEnableVertexAttribArray(aPosID);	// ���迡�� ��Ʋ��
	glEnableVertexAttribArray(aUVID);


	int ObjectVertex = 15;
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO_TextureMaking);

		glVertexAttribPointer(aPosID, 3, GL_FLOAT, GL_FALSE, sizeof(float) * ObjectVertex, 0);
		glVertexAttribPointer(aUVID, 2, GL_FLOAT, GL_FALSE, sizeof(float) * ObjectVertex, (GLvoid*)(sizeof(float) * 3));

		// Ʈ���̾ޱ��� �׸��� �� m_Count_TextureMapping���� �ﰢ���� �̿��� �׸���.
		glDrawArrays(GL_TRIANGLES, 0, m_Count_TextureMaking);

		glDisableVertexAttribArray(aPosID);
		glDisableVertexAttribArray(aUVID);
	}
}

void Renderer::DrawTextureTransUV() {
	GLuint Shader = m_TextureTransUV;

	glUseProgram(Shader);// �� ���α׷��� ���ڴ�. (==Shader)

	GLuint aPosID = glGetAttribLocation(Shader, "a_Position");//Shader�� s_Position��
	GLuint aUVID = glGetAttribLocation(Shader, "a_UV");

	GLuint uTimeID = glGetUniformLocation(Shader, "u_Time");
	p_time += 0.0001;
	glUniform1f(uTimeID, p_time);

	GLuint uTexID = glGetUniformLocation(Shader, "u_Texture");
	glUniform1i(uTexID, 0);
	glActiveTexture(GL_TEXTURE0);
	//BindTexture != BindBuffer
	glBindTexture(GL_TEXTURE_2D, m_TextureRGB);


	//attribute ���
	glEnableVertexAttribArray(aPosID);	// ���迡�� ��Ʋ��
	glEnableVertexAttribArray(aUVID);


	int ObjectVertex = 15;
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO_TextureTransUV);

		glVertexAttribPointer(aPosID, 3, GL_FLOAT, GL_FALSE, sizeof(float) * ObjectVertex, 0);
		glVertexAttribPointer(aUVID, 2, GL_FLOAT, GL_FALSE, sizeof(float) * ObjectVertex, (GLvoid*)(sizeof(float) * 3));

		// Ʈ���̾ޱ��� �׸��� �� m_Count_TextureMapping���� �ﰢ���� �̿��� �׸���.
		glDrawArrays(GL_TRIANGLES, 0, m_Count_TextureTransUV);

		glDisableVertexAttribArray(aPosID);
		glDisableVertexAttribArray(aUVID);
	}
}

void Renderer::DrawTextures() {
	GLuint Shader = m_Textures;

	glUseProgram(Shader);// �� ���α׷��� ���ڴ�. (==Shader)

	GLuint aPosID = glGetAttribLocation(Shader, "a_Position");//Shader�� s_Position��
	GLuint aUVID = glGetAttribLocation(Shader, "a_UV");

	GLuint uTimeID = glGetUniformLocation(Shader, "u_Time");
	p_time += 0.0001;
	glUniform1f(uTimeID, p_time);

	GLuint uTexID0 = glGetUniformLocation(Shader, "u_Texture0");
	glUniform1i(uTexID0, 0);

	GLuint uTexID1 = glGetUniformLocation(Shader, "u_Texture1");
	glUniform1i(uTexID1, 1);

	GLuint uTexID2 = glGetUniformLocation(Shader, "u_Texture2");
	glUniform1i(uTexID2, 2);

	GLuint uTexID3 = glGetUniformLocation(Shader, "u_Texture3");
	glUniform1i(uTexID3, 3);

	GLuint uTexID4 = glGetUniformLocation(Shader, "u_Texture4");
	glUniform1i(uTexID4, 4);

	GLuint uTexID5 = glGetUniformLocation(Shader, "u_Texture5");
	glUniform1i(uTexID5, 5);
	
	//uniform
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gTextureID0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, gTextureID1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, gTextureID2);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, gTextureID3);

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, gTextureID4);

	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, gTextureID5);


	//attribute ���
	glEnableVertexAttribArray(aPosID);	// ���迡�� ��Ʋ��
	glEnableVertexAttribArray(aUVID);


	int ObjectVertex = 15;
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO_Textures);

		glVertexAttribPointer(aPosID, 3, GL_FLOAT, GL_FALSE, sizeof(float) * ObjectVertex, 0);
		glVertexAttribPointer(aUVID, 2, GL_FLOAT, GL_FALSE, sizeof(float) * ObjectVertex, (GLvoid*)(sizeof(float) * 3));

		// Ʈ���̾ޱ��� �׸��� �� m_Count_TextureMapping���� �ﰢ���� �̿��� �׸���.
		glDrawArrays(GL_TRIANGLES, 0, m_Count_Textures);

		glDisableVertexAttribArray(aPosID);
		glDisableVertexAttribArray(aUVID);
	}
}

float gTimeStamp;

void Renderer::DrawTexturesAnimation() {
	GLuint Shader = m_TexturesAnimation;

	glUseProgram(Shader);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gTextureIDTotal);

	int uniformTex = glGetUniformLocation(Shader, "uTexSampler");
	glUniform1i(uniformTex, 0);

	int uniformTime = glGetUniformLocation(Shader, "uTime");
	glUniform1f(uniformTime, gTimeStamp);

	gTimeStamp += 1.f;
	if (gTimeStamp > 5.f)
		gTimeStamp = 0.f;

	int attrribPosition = glGetAttribLocation(Shader, "Position");
	int attrribTexPos = glGetAttribLocation(Shader, "TexPos");

	glEnableVertexAttribArray(attrribPosition);
	glEnableVertexAttribArray(attrribTexPos);

	int ObjectVertex = 5;
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO_TexturesAnimation);
		glVertexAttribPointer(attrribPosition, 3, GL_FLOAT, GL_FALSE, ObjectVertex * sizeof(float), 0);
		glVertexAttribPointer(attrribTexPos, 2, GL_FLOAT, GL_FALSE, ObjectVertex * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	}

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(attrribPosition);
	glDisableVertexAttribArray(attrribTexPos);
}

void Renderer::DrawNumber(int number) {
	GLuint Shader = m_TexturesRect;

	glUseProgram(Shader);

	//uniform inputs
	GLuint u_Num = glGetUniformLocation(Shader, "uNumber");
	glUniform1i(u_Num, 9 - number);
	
	
	//vertex Setting : vertex shader���� ����
	int a_Pos = glGetAttribLocation(Shader, "Position");
	int a_TexPos = glGetAttribLocation(Shader, "TexPos");

	glEnableVertexAttribArray(a_Pos);
	glEnableVertexAttribArray(a_TexPos);

	int ObjectVertex = 5;

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_TexturesRect);

	glVertexAttribPointer(a_Pos, 3, GL_FLOAT, GL_FALSE, sizeof(float) * ObjectVertex, 0);
	glVertexAttribPointer(a_TexPos, 2, GL_FLOAT, GL_FALSE, sizeof(float) * ObjectVertex, (GLvoid*)(sizeof(float) * 3));


	//Texture Setting
	GLuint uTex = glGetUniformLocation(Shader, "u_Texture");
	//�������� �ؽ����߿� 0��° ������ ���ڴ�.
	glUniform1d(uTex, 0);
	//gltexture0����
	glActiveTexture(GL_TEXTURE0);
	//
	glBindTexture(GL_TEXTURE_2D, m_TextureNumber);

	//Draw
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Restore to default
	glDisableVertexAttribArray(a_Pos);
	glDisableVertexAttribArray(a_TexPos);
}

void Renderer::DrawNumbers(int* number) {
	GLuint Shader = m_TexturesRects;

	glUseProgram(Shader);

	//uniform inputs
	GLuint u_Num = glGetUniformLocation(Shader, "uNumber");
	glUniform1iv(u_Num, 3, number);


	//vertex Setting : vertex shader���� ����
	int a_Pos = glGetAttribLocation(Shader, "Position");
	int a_TexPos = glGetAttribLocation(Shader, "TexPos");

	glEnableVertexAttribArray(a_Pos);
	glEnableVertexAttribArray(a_TexPos);

	int ObjectVertex = 5;

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_TexturesRect);

	glVertexAttribPointer(a_Pos, 3, GL_FLOAT, GL_FALSE, sizeof(float) * ObjectVertex, 0);
	glVertexAttribPointer(a_TexPos, 2, GL_FLOAT, GL_FALSE, sizeof(float) * ObjectVertex, (GLvoid*)(sizeof(float) * 3));


	//Texture Setting
	GLuint uTex = glGetUniformLocation(Shader, "u_Texture");
	//�������� �ؽ����߿� 0��° ������ ���ڴ�.
	glUniform1d(uTex, 0);
	//gltexture0����
	glActiveTexture(GL_TEXTURE0);
	//
	glBindTexture(GL_TEXTURE_2D, m_TextureNumber);

	//Draw
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Restore to default
	glDisableVertexAttribArray(a_Pos);
	glDisableVertexAttribArray(a_TexPos);
}
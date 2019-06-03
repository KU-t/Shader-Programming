#pragma once

#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "Dependencies\glew.h"
#include "Dependencies\wglew.h"
#include "Dependencies\glm/glm.hpp"
#include "Dependencies\glm/gtc/matrix_transform.hpp"
#include "Dependencies\glm/gtx/euler_angles.hpp"

class Renderer
{
public:
	Renderer(int windowSizeX, int windowSizeY);
	~Renderer();

	GLuint CreatePngTexture(char * filePath);
	GLuint CreateBmpTexture(char * filePath);
	   
	void DrawRect();
	void DrawTriangle();
	void DrawRandRect();
	void DrawGridMesh();
	void DrawSimpleVel();
	void DrawGravity();
	void DrawSinGraph();
	void DrawDirectionSin();
	void DrawFragmentBase();
	void DrawInterpolationBase();
	void DrawRadar();
	void DrawTextureMapping();
	void DrawTextureMaking();
	void DrawTextureTransUV();
	void DrawTextures();
	void PracticeTextures();
	void DrawTexturesAnimation();
	void DrawNumber(int number);
	void DrawNumbers(int* number);
	void PracticeAnimation();
	void DrawSpriteAnimation(int number);
	void DrawVSSandbox();
	void DrawFlag();
	void DrawSphereMapping();
	void DrawSimpleCube();
	void DrawFlag_Camera();
	void DrawHeightmap();

	void InitOrthoMatrices();
	void InitOrthoMatrices(float, float, float, float, float, float, float, float, float);
	void InitPerspectMatrices();
	void InitPerspectMatrices(float, float, float, float, float, float, float, float, float);

private:
	void Initialize(int windowSizeX, int windowSizeY);
	bool ReadFile(char* filename, std::string *target);
	void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
	GLuint CompileShaders(char* filenameVS, char* filenameFS);
	void CreateVertexBufferObjects(); 

	void GenQuadsVBO_Rect();
	void GenQuadsVBO_Tri();
	void GenQuadsVBO_Rand(int count);
	void GenQuadsVBO_GridMesh();
	void GenQuadsVBO_Vel(int count);
	void GenQuadsVBO_Gra(int count);
	void GenQuadsVBO_Sin(int count, bool random, GLuint * ID, GLuint * vCount);
	void GenQuadsVBO_DirectionSin(int count, bool random, GLuint * ID, GLuint * vCount);
	void GenQuadsVBO_FragmentBase(int count, bool random, GLuint * ID, GLuint * vCount);
	void GenQuadsVBO_InterpolationBase(GLuint * ID, GLuint * vCount);
	void GenQuadsVBO_Radar(GLuint * ID, GLuint * vCount);
	void GenQuadsVBO_TextureMapping(GLuint * ID, GLuint * vCount);
	void GenQuadsVBO_TextureMaking(GLuint * ID, GLuint * vCount);
	void GenQuadsVBO_TextureTransUV(GLuint * ID, GLuint * vCount);
	void GenQuadsVBO_Textures(GLuint * ID, GLuint * vCount);
	void GenQuadsVBO_PracticeTextures(GLuint * ID, GLuint * vCount);
	void GenQuadsVBO_TexturesAnimation(GLuint * ID, GLuint * vCount);
	void GenQuadsVBO_TexturesRect(GLuint * ID, GLuint * vCount);
	void GenQuadsVBO_PracticeAnimation(GLuint * ID, GLuint * vCount);
	void GenQuadsVBO_SpriteAnimation(GLuint * ID, GLuint * vCount);
	void GenQuadsVBO_VSSandbox(GLuint * ID, GLuint * vCount);
	void GenQuadsVBO_Flag(GLuint * ID, GLuint * vCount);
	void GenQuadsVBO_SphereMapping(GLuint * ID, GLuint * vCount);
	void GenQuadsVBO_SimpleCube(GLuint * ID, GLuint * vCount);
	void GenQuadsVBO_Flag_Camera(GLuint * ID, GLuint * vCount);
	void GenQuadsVBO_Heightmap(GLuint * ID, GLuint * vCount);

	unsigned char * Renderer::loadBMPRaw(const char * imagepath, unsigned int& outWidth, unsigned int& outHeight);

	bool m_Initialized = false;
	
	unsigned int m_WindowSizeX = 0;
	unsigned int m_WindowSizeY = 0;

	// DrawRect
	GLuint m_VBORect = 0;
	GLuint m_VBORectcolor = 0;

	//DrawTriangle
	GLuint m_VBOTri = 0;

	//DrawRandRect
	GLuint m_VBORandQuads = 0;
	GLuint m_VBORandQuads_VertexCount = 0;

	//DrawGridmesh
	GLuint m_VBOGrid = 0;
	GLuint m_VBOGrid_VertexCount = 0;

	//DrawSimpleVel
	GLuint m_VBOSimpleVel = 0;
	GLuint m_VBOSimpleVel_VertexCount = 0;

	//DrawGravity
	GLuint m_VBOGravity = 0;
	GLuint m_VBOGravity_VertexCount = 0;

	//DrawSinGraph
	GLuint m_VBO_SinGraph = 0;
	GLuint m_Count_SinGraph = 0;

	//DrawDirectionSinGraph
	GLuint m_VBO_DirectionSinGraph = 0;
	GLuint m_Count_DirectionSinGraph = 0;

	//DrawFragmentBase
	GLuint m_VBO_FragmentBase = 0;
	GLuint m_Count_FragmentBase = 0;

	//DrawInterpolationBase
	GLuint m_VBO_InterpolationBase = 0;
	GLuint m_Count_InterpolationBase = 0;

	//DrawRadar
	GLuint m_VBO_Radar = 0;
	GLuint m_Count_Radar = 0;

	//DrawTextureMapping
	GLuint m_VBO_TextureMapping = 0;
	GLuint m_Count_TextureMapping = 0;

	//DrawTextureMaking
	GLuint m_VBO_TextureMaking = 0;
	GLuint m_Count_TextureMaking = 0;
	GLuint m_TextureID = 0;

	//DrawTextureTransUV
	GLuint m_VBO_TextureTransUV = 0;
	GLuint m_Count_TextureTransUV = 0;

	//DrawTextures
	GLuint m_VBO_Textures = 0;
	GLuint m_Count_Textures = 0;

	//PracticeTextures
	GLuint m_VBO_PracticeTextures = 0;
	GLuint m_Count_PracticeTextures = 0;

	//DrawTexturesAnimation
	GLuint m_VBO_TexturesAnimation = 0;
	GLuint m_Count_TexturesAnimation = 0;
	GLuint gTextureIDTotal = 0;

	//DrawNumber
	GLuint m_VBO_TexturesRect = 0;
	GLuint m_Count_TexturesRect = 0;
	//GLuint gTextureIDTotal = 0;

	//PracticeAnimation
	GLuint m_VBO_PracticeAnimation = 0;
	GLuint m_Count_PracticeAnimation = 0;

	//DrawSpriteAnimation
	GLuint m_VBO_SpriteAnimation = 0;
	GLuint m_Count_SpriteAnimation = 0;

	//DrawVSSandbox
	GLuint m_VBO_VSSandbox = 0;
	GLuint m_Count_VSSandbox = 0;

	//DrawFlag
	GLuint m_VBO_Flag = 0;
	GLuint m_Count_Flag = 0;

	//DrawSphereMapping
	GLuint m_VBO_SphereMapping = 0;
	GLuint m_Count_SphereMapping = 0;

	//DrawSimpleCube
	GLuint m_VBO_SimpleCube = 0;
	GLuint m_Count_SimpleCube = 0;
	GLuint m_VBO_Flag_Camera = 0;
	GLuint m_Count_Flag_Camera = 0;

	//DrawHeightmap
	GLuint m_VBO_Heightmap = 0;
	GLuint m_Count_Heightmap = 0;


	//Matrices
	glm::mat4 m_ViewMat4;
	glm::mat4 m_OrthoProjMat4;
	glm::mat4 m_PersProjMat4;
	glm::mat4 m_ViewProjMat4;
	glm::vec3 m_v3CameraPos;
	glm::vec3 m_v3CameraLookat;
	glm::vec3 m_v3CameraUp;


	//Shaders
	GLuint m_SolidRectShader = 0;
	GLuint m_RandQuadsShader = 0;
	GLuint m_GridMeshShader = 0;
	GLuint m_SimpleVelShader = 0;
	GLuint m_GravityShader = 0;
	GLuint m_SingraphShader = 0;
	GLuint m_DirectionSinShader = 0;
	GLuint m_FragmentBaseShader = 0;
	GLuint m_InterpolationBaseShader = 0;
	GLuint m_RadarShader = 0;
	GLuint m_TextureMapping = 0;
	GLuint m_TextureMaking = 0;
	GLuint m_TextureTransUV = 0;
	GLuint m_Textures = 0;
	GLuint m_PracticeTextures = 0;
	GLuint m_TexturesAnimation = 0;
	GLuint m_TexturesRect = 0;
	GLuint m_TexturesRects = 0;
	GLuint m_PracticeAnimation = 0;
	GLuint m_SpriteAnimation = 0;
	GLuint m_VSSandbox = 0;
	GLuint m_Flag = 0;
	GLuint m_SphereMapping = 0;
	GLuint m_SimpleCube = 0;
	GLuint m_Flag_Camera = 0;
	GLuint m_Heightmap = 0;

	//Textures
	GLuint gTextureID = 0;
	GLuint gTextureID0 = 0;
	GLuint gTextureID1 = 0;
	GLuint gTextureID2 = 0;
	GLuint gTextureID3 = 0;
	GLuint gTextureID4 = 0;
	GLuint gTextureID5 = 0;

	GLuint m_TextureFence = 0;
	GLuint m_TextureSky = 0;
	GLuint m_TextureLUFFY = 0;
	GLuint m_TextureRGB = 0;
	GLuint m_TextureNumber = 0;
	GLuint m_TexturePingo = 0;
	GLuint m_TextureKorea = 0;
	GLuint m_TextureHeightmap = 0;
	GLuint m_TextureSnow = 0;
	GLuint m_TextureGrass = 0;
	
};


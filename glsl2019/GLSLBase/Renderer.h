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
	void DrawProxyGeometry();
	void DrawSimpleVel();

private:
	void Initialize(int windowSizeX, int windowSizeY);
	bool ReadFile(char* filename, std::string *target);
	void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
	GLuint CompileShaders(char* filenameVS, char* filenameFS);
	void CreateVertexBufferObjects(); 

	void GenQuadsVBO(int count);
	void GenQuadsVBO_Vel(int count);
	void GridMeshVBO();
	void CreateProxyGeometry();

	unsigned char * Renderer::loadBMPRaw(const char * imagepath, unsigned int& outWidth, unsigned int& outHeight);

	bool m_Initialized = false;
	
	unsigned int m_WindowSizeX = 0;
	unsigned int m_WindowSizeY = 0;

	// DrawRect
	GLuint m_VBORect = 0;
	GLuint m_VBORectcolor = 0;

	//DrawTriangle
	GLuint m_VBOLecture = 0;

	//DrawRandRect
	GLuint m_VBOQuads = 0;
	GLuint m_VBOQuads_VertexCount = 0;

	//DrawGridmesh
	GLuint m_VBOGrid = 0;
	GLuint m_VBOGrid_VertexCount = 0;

	//DrawProxygeometry
	GLuint m_VBO_ProxyGeo = 0;
	GLuint m_Count_ProxyGeo = 0;

	//Shaders
	GLuint m_SolidRectShader = 0;
	GLuint m_SimpleVelShader = 0;
};


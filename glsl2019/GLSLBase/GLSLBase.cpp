/*
Copyright 2018 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"

Renderer *g_Renderer = NULL;

int g_WindowSizeX = 400;
int g_WindowSizeY = 400;

void RenderScene(void)
{
	// 1. 화면을 지운다.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// 2. 화면을 그린다.
	//g_Renderer->DrawRect();
	//g_Renderer->DrawTriangle();
	//g_Renderer->DrawRandRect();
	//g_Renderer->DrawGridMesh();
	//g_Renderer->DrawSimpleVel();
	//g_Renderer->DrawGravity();
	//g_Renderer->DrawSinGraph();
	//g_Renderer->DrawDirectionSin();
	//g_Renderer->DrawFragmentBase();
	//g_Renderer->DrawInterpolationBase();
	//g_Renderer->DrawRadar();
	//g_Renderer->DrawTextureMapping();
	//g_Renderer->DrawTextureMaking();
	//g_Renderer->DrawTextureTransUV();
	//g_Renderer->DrawTextures();
	//g_Renderer->PracticeTextures();
	//g_Renderer->DrawTexturesAnimation();
	//g_Renderer->DrawNumber(9);
	//int number[] = { 3, 4, 5 };
	//g_Renderer->DrawNumbers(number);
	//g_Renderer->PracticeAnimation();
	//static int gAninum = 0;
	//gAninum = (gAninum + 1) % 3000;
	//g_Renderer->DrawSpriteAnimation(gAninum/100);
	//g_Renderer->DrawVSSandbox();
	//g_Renderer->DrawFlag();
	//g_Renderer->DrawSphereMapping();
	//g_Renderer->DrawSimpleCube();
	//g_Renderer->DrawFlag_Camera();
	//g_Renderer->DrawHeightmap();
	g_Renderer->DrawNormalVector();

	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(g_WindowSizeX, g_WindowSizeY);
	glutCreateWindow("GLSL KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_4_6"))
	{
		std::cout << " GL Version is 4.6\n ";
	}
	else
	{
		std::cout << "GLEW 4.6 not supported\n ";
	}

	// Initialize Renderer
	g_Renderer = new Renderer(g_WindowSizeX, g_WindowSizeY);

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_Renderer;

    return 0;
}


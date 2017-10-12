/*
render.cpp
contains rendering functions

Toy Leksut
*/

#include "main.h"

// extern
void initScene();
void display();

// initialize scene, set lighting
void initScene()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);	
	glDisable(GL_DITHER);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);

	// material
	GLfloat mat_a[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat mat_d[] = { .7f , .7f, .7f, 1.0f }; //{0.4f, 0.4f, 0.4f, 1.0f};
	GLfloat mat_s[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat shine[] = { 128.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_a);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_d);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_s);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine);

	// lighting
	glLoadIdentity();
	GLfloat pos1[] = { 0.1f, 0.1f, -0.02f, 0.0f };
	GLfloat pos2[] = { -0.1f, 0.1f, -0.02f, 0.0f };
	GLfloat pos3[] = { 0.0f, 0.0f, 0.1f, 0.0f };
	GLfloat col1[] = { .5f, .5f, .5f, 1.0f }; //{.05f, .05f, .6f, 1.0f};
	GLfloat col2[] = { .5f, .5f, .5f, 1.0f }; //{.6f, .05f, .05f, 1.0f};
	GLfloat col3[] = { .7f, .7f, .7f, 1.0f }; //{1.0f, 1.0f, 1.0f, 1.0f};

	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, pos1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, col1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, col1);

	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_POSITION, pos2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, col2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, col2);

	glEnable(GL_LIGHT2);
	glLightfv(GL_LIGHT2, GL_POSITION, pos3);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, col3);
	glLightfv(GL_LIGHT2, GL_SPECULAR, col3);
}

void display()
{

}
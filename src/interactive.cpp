/*
interactive.cpp
contains interactive features

Toy Leksut
*/

#include "main.h"


// extern
void specialKeyUp(int key, int x, int y);


void specialKeyUp(int key, int x, int y)
{
	int rot_angle = 15;
	switch (key) {
	case GLUT_KEY_LEFT:
		rotateMesh(mainMesh, Y_AXIS, -rot_angle);
		printf("left\n");
		break;
	case GLUT_KEY_RIGHT:
		rotateMesh(mainMesh, Y_AXIS, rot_angle);
		printf("right\n");
		break;
	case GLUT_KEY_UP:
		rotateMesh(mainMesh, X_AXIS, -rot_angle);
		printf("up\n");
		break;
	case GLUT_KEY_DOWN:
		rotateMesh(mainMesh, X_AXIS, rot_angle);
		printf("down\n");
		break;
	}
	glutPostRedisplay();
}
/*
render.cpp
contains rendering functions

Toy Leksut
*/

#include "main.h"

// extern
void initScene();
void display();
void idle();
void setPose(const MooMesh& moomesh);
void rotateMesh(MooMesh& moomesh, int axis_id, float angle);
void renderMesh(const MooMesh& moomesh, int colorMode);

// initialize scene, set lighting
void initScene()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);	
	glDisable(GL_DITHER);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	// material
	GLfloat mat_ambient_and_diffuse[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat mat_specular[] = {0.5, 0.5, 0.5, 1.0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_ambient_and_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 50.0);

	// light 0: default
	// ambient 0,0,0,1
	// diffuse 1,1,1,1
	// specular 1,1,1,1
	// position 0,0,1,0
	GLfloat l0_ambient[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat l0_diffuse[] = {0.5, 0.5, 0.5, 1.0};
	GLfloat l0_specular[] = {0.0, 0.0, 0.0, 0.0};
	GLfloat l0_position[] = {0.25, 0.85, 0.75, 0.0};
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l0_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, l0_position);

	// light 1
	GLfloat l1_ambient[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat l1_diffuse[] = {0.1, 0.0, 0.0, 1.0};
	GLfloat l1_specular[] = {0.0, 0.0, 0.0, 0.0};
	GLfloat l1_position[] = {-0.7, -0.5, 0.0, 0.0};
	glLightfv(GL_LIGHT1, GL_AMBIENT, l1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, l1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, l1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, l1_position);

	// light 2
	GLfloat l2_ambient[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat l2_diffuse[] = {0.0, 0.0, 0.1, 1.0};
	GLfloat l2_specular[] = {0.1, 0.1, 0.1, 1.0};
	GLfloat l2_position[] = {0.7, -0.5, 0.0, 0.0};
	glLightfv(GL_LIGHT2, GL_AMBIENT, l2_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, l2_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, l2_specular);
	glLightfv(GL_LIGHT2, GL_POSITION, l2_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);

	// set view
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	// set projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(test_mode) {
		getTestMesh(mainMesh);
	}
	else {
		loadMesh(input_list[0], mainMesh);
	}
	setPose(mainMesh);
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderMesh(mainMesh);
	glutSwapBuffers();
}

void idle()
{
}

void setPose(const MooMesh& moomesh)
{
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixd(moomesh.projection_matrix);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLoadMatrixd(moomesh.modelview_matrix);
}

void rotateMesh(MooMesh& moomesh, int axis_id, float angle)
{
	float axis[3] = { 0.0, 0.0, 0.0 };
	axis[axis_id] = 1.0;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(moomesh.translation[0], moomesh.translation[1], moomesh.translation[2]);
	glRotated(angle, axis[0], axis[1], axis[2]);
	glTranslated(-moomesh.translation[0], -moomesh.translation[1], -moomesh.translation[2]);
	glMultMatrixd(moomesh.modelview_matrix);

	updateMeshView(moomesh);
}

/*
render mesh with an option to use vertex color or texture map
*/
void renderMesh(const MooMesh& moomesh, int colorMode)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (colorMode) {

	case RENDER_VERTEX_COLOR:
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(3, GL_UNSIGNED_BYTE, 0, moomesh.mesh.vertex_colors());
		break;

	case RENDER_TEXTURE_MAP:
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, moomesh.mesh.texcoords2D());
		break;

	default:
		glEnable(GL_LIGHTING);
		break;
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, moomesh.mesh.points());

	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, moomesh.mesh.vertex_normals());

	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(moomesh.faceIds.size()), GL_UNSIGNED_INT, &moomesh.faceIds[0]);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);
}


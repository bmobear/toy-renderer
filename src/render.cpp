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
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	glShadeModel(GL_SMOOTH);

	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
	

	// material
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	// light 0
	GLfloat light0_position[] = { 0.2, 0.5, 0.8, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	// light 1
	GLfloat light1_position[] = { 0.0, 1.0, 0.0, 0.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
//	glEnable(GL_LIGHT1);

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


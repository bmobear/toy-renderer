/*
main.cpp
an entry point for 3D model renderer

Toy Leksut
*/

#include "main.h"

GLuint fbo_query, fbo_query_color, fbo_query_depth;
GLuint fbo_render, fbo_render_color, fbo_render_depth;


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE | GLUT_ALPHA);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Hello World Window");

	// initialize glew
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	// initialize framebuffers 
	//initFBO(fbo_render, fbo_render_color, fbo_render_depth);
	//glBindFramebuffer(GL_FRAMEBUFFER, fbo_render);

	// initialize scene
	initScene();

	// start rendering
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMainLoop();

	// clean up
	//cleanupFBO(fbo_render, fbo_render_color, fbo_render_depth);

	// wait to exit
	getchar();
	return 0;
}
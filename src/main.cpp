/*
main.cpp
an entry point for 3D model renderer

Toy Leksut
*/

#include "main.h"


GLuint fbo_query, fbo_query_color, fbo_query_depth;
GLuint fbo_render, fbo_render_color, fbo_render_depth;
MooMesh mainMesh;
bool test_mode = false;

int main(int argc, char **argv)
{
	switch(argc) {
		case 1:
			// test mode: draw a cube
			printf("Test mode: draw a cube\n");
			test_mode = true;
			break;
		case 3:
			// read from filelist.txt
			setIO(argv[1], argv[2]);
			break;
		default:
			printf("Usage: toy-renderer <filelist.txt> <output_dir>\n");
			exit(-1);
	}
	

	///////////// init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE | GLUT_ALPHA);
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


	glutDisplayFunc(display);
	glutIdleFunc(idle);

#ifdef INTERACTIVE_MODE
	glutSpecialUpFunc(specialKeyUp);
#endif

	

	glutMainLoop();

	// clean up
	//cleanupFBO(fbo_render, fbo_render_color, fbo_render_depth);

	// wait to exit
	getchar();
	return 0;
}
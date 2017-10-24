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
	

#ifdef OFFSCREEN_RENDER
	initGLXContext();
#else
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE | GLUT_ALPHA);
	glutCreateWindow("Toy Renderer");
#endif

	// initialize glew (after getting context)
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

#ifdef OFFSCREEN_RENDER
	initFBO(fbo_render, fbo_render_color, fbo_render_depth);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo_render);
	initScene();

	// process each 3D model one by one
	if(input_list.empty()) {
		printf("empty");
	}
	else {
		printf("%d models to render", input_list.size());
	}

	// render


	// clean up
	cleanupFBO(fbo_render, fbo_render_color, fbo_render_depth);
	OSMesaDestroyContext(ctx);

#else 

	initScene();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutSpecialUpFunc(specialKeyUp);
	glutMainLoop();

#endif

	// wait to exit
	getchar();
	return 0;
}
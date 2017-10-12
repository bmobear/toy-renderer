#pragma once

/*
	INCLUDE
*/
// IO
#include <stdio.h>

// OpenGL
#include <GL/glew.h>
#include <GL/glut.h>

/*
	NAMESPACE
*/
using namespace std;

/*
	EXTERNAL VARIABLES
*/
extern GLuint fbo_query, fbo_query_color, fbo_query_depth;		// dynamic size based on query image
extern GLuint fbo_render, fbo_render_color, fbo_render_depth;	// fixed size based on frontal.glcam


//------------------------------------------------------------
//=====================    RENDERER    =======================
//------------------------------------------------------------

// renderer.cpp
extern void initScene();
extern void display();

// framebuffer.cpp
extern void initFBO(GLuint& framebuffer, GLuint& colorbuffer, GLuint& depthbuffer);
extern void cleanupFBO(GLuint& framebuffer, GLuint& colorbuffer, GLuint& depthbuffer);
extern void updateFBO(GLuint& colorbuffer, GLuint& depthbuffer, int winWidth, int winHeight);

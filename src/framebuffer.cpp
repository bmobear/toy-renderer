/*
framebuffer.cpp
contains OpenGL framebuffer routine functions

Toy Leksut
*/

#include "main.h"


// extern
void initFBO(GLuint& framebuffer, GLuint& colorbuffer, GLuint& depthbuffer);
void cleanupFBO(GLuint& framebuffer, GLuint& colorbuffer, GLuint& depthbuffer);
void updateFBO(GLuint& colorbuffer, GLuint& depthbuffer, int winWidth, int winHeight);

// intern
void initColorBuffer(GLuint& colorbuffer);
void initDepthBuffer(GLuint& depthbuffer);

#define USE_RENDER_COLOR_BUFFER true	// in opposed to texture

///////////////////////////////////////////////////////////////////



void initColorBuffer(GLuint& colorbuffer)
{
	// there are two options for render buffer
	// 1. texture
	// 2. render buffer

	if (USE_RENDER_COLOR_BUFFER) {
		glGenRenderbuffers(1, &colorbuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, colorbuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, WINDOW_WIDTH, WINDOW_HEIGHT);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorbuffer);
	}
	else {
		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &colorbuffer);
		glBindTexture(GL_TEXTURE_2D, colorbuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorbuffer, 0);
	}

	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	glReadBuffer(GL_COLOR_ATTACHMENT0);
}


void initDepthBuffer(GLuint& depthbuffer)
{
	glGenRenderbuffers(1, &depthbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, WINDOW_WIDTH, WINDOW_HEIGHT);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthbuffer);
}


void initFBO(GLuint& framebuffer, GLuint& colorbuffer, GLuint& depthbuffer)
{
	// create FBO
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	// create color buffer and depth buffer
	initColorBuffer(colorbuffer);
	initDepthBuffer(depthbuffer);

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		printf("Failed to create frame buffer\n");
		exit(-1);
	}
}


void cleanupFBO(GLuint& framebuffer, GLuint& colorbuffer, GLuint& depthbuffer)
{
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	if (USE_RENDER_COLOR_BUFFER) {
		glDeleteRenderbuffers(1, &colorbuffer);
	}
	else {
		glBindTexture(GL_TEXTURE_2D, 0);
		glDeleteTextures(1, &colorbuffer);
	}
	glDeleteRenderbuffers(1, &depthbuffer);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDeleteFramebuffers(1, &framebuffer);
}


void updateFBO(GLuint& colorbuffer, GLuint& depthbuffer, int winWidth, int winHeight)
{
	// simply re-initialize the storage, according to glRenderbufferStorage API
	// glRenderbufferStorage establishes the data storage, format, and dimensions of a renderbuffer object's image. 
	// Any existing data store for the renderbuffer is deleted and the contents of the new data store are undefined.


	// color 
	if (USE_RENDER_COLOR_BUFFER) {
		glBindRenderbuffer(GL_RENDERBUFFER, colorbuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, winWidth, winHeight);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}
	else {
		glBindTexture(GL_TEXTURE_2D, colorbuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, winWidth, winHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	// depth
	glBindRenderbuffer(GL_RENDERBUFFER, depthbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, winWidth, winHeight);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

}
#pragma once

/*
	INCLUDE
*/
// IO
#include <stdio.h>

// OpenMesh
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <OpenMesh/Core/Geometry/VectorT.hh>

// OpenGL
#include <GL/glew.h>
#include <GL/glut.h>

/*
	DEFINE
*/
#define RENDER_VERTEX_COLOR	1
#define RENDER_TEXTURE_MAP	-1
#define WINDOW_WIDTH		512
#define WINDOW_HEIGHT		512
#define X_AXIS				0
#define Y_AXIS				1
#define	Z_AXIS				2

/*
	NAMESPACE
*/
using namespace std;
typedef OpenMesh::TriMesh_ArrayKernelT<>  Mesh;

/*
	EXTERNAL VARIABLES
*/
extern GLuint fbo_query, fbo_query_color, fbo_query_depth;		// dynamic size based on query image
extern GLuint fbo_render, fbo_render_color, fbo_render_depth;	// fixed size based on frontal.glcam

/*
	CLASS
*/
class MooMesh
{
public:
	Mesh mesh;
	float center[3];
	float radius;
	vector<uint> faceIds;
	double projection_matrix[16];
	double modelview_matrix[16];
	float translation[3];
};

//------------------------------------------------------------
//=====================    RENDERER    =======================
//------------------------------------------------------------

// renderer.cpp
extern void initScene();
extern void display();
extern void idle();
extern void renderMesh(const MooMesh& moomesh, int colorMode = 0);

// framebuffer.cpp
extern void initFBO(GLuint& framebuffer, GLuint& colorbuffer, GLuint& depthbuffer);
extern void cleanupFBO(GLuint& framebuffer, GLuint& colorbuffer, GLuint& depthbuffer);
extern void updateFBO(GLuint& colorbuffer, GLuint& depthbuffer, int winWidth, int winHeight);

//------------------------------------------------------------
//=================      MESH PROCESSING     =================
//------------------------------------------------------------

// mesh.cpp
extern void loadMesh(const string meshFile, MooMesh& out_moomesh);
extern void getTestMesh(MooMesh& testmesh);
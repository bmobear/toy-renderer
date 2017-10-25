#pragma once

/*
	MODE
*/
#undef INTERACTIVE_MODE


/*
	INCLUDE
*/
// IO
#include <stdio.h>
#include <fstream>

// boost
#include <boost/filesystem.hpp>

// OpenCV
#include <opencv2/opencv.hpp>

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
#define WINDOW_WIDTH		256
#define WINDOW_HEIGHT		256
#define X_AXIS				0
#define Y_AXIS				1
#define	Z_AXIS				2


/*
	NAMESPACE
*/
using namespace std;
using namespace cv;
typedef OpenMesh::TriMesh_ArrayKernelT<>  Mesh;


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


/*
	GLOBAL VARIABLES
*/
extern GLuint fbo_query, fbo_query_color, fbo_query_depth;		// dynamic size based on query image
extern GLuint fbo_render, fbo_render_color, fbo_render_depth;	// fixed size based on frontal.glcam
extern MooMesh mainMesh;
extern vector<string> input_list;
extern boost::filesystem::path output_dir;
extern bool test_mode;


//------------------------------------------------------------
//=====================    RENDERER    =======================
//------------------------------------------------------------

// render.cpp
extern void initScene();
extern void display();
extern void dummyDisplay();
extern void idle();
extern void render();
extern void renderMesh(const MooMesh& moomesh, int colorMode = 0);
extern void rotateMesh(MooMesh& moomesh, int axis_id, float angle);

// framebuffer.cpp
extern void initFBO(GLuint& framebuffer, GLuint& colorbuffer, GLuint& depthbuffer);
extern void cleanupFBO(GLuint& framebuffer, GLuint& colorbuffer, GLuint& depthbuffer);
extern void updateFBO(GLuint& colorbuffer, GLuint& depthbuffer, int winWidth, int winHeight);

#ifdef INTERACTIVE_MODE
	// interactive.cpp
	extern void specialKeyUp(int key, int x, int y);
#endif

//------------------------------------------------------------
//=================      MESH PROCESSING     =================
//------------------------------------------------------------

// mesh.cpp
extern void loadMesh(const string meshFile, MooMesh& out_moomesh);
extern void getTestMesh(MooMesh& testmesh);
extern void updateMeshView(MooMesh& moomesh);
extern void setMeshView(MooMesh& moomesh);


//------------------------------------------------------------
//================ =      IO / UTILS       ===================
//------------------------------------------------------------

// utils.cpp
extern void setIO(const string filelist, const string output_dir);
extern void transferDraw(Mat& out_img);
extern void writeImage(const Mat& img, const boost::filesystem::path outfile);
extern void showImage(const Mat& img);
extern bool verifyDir(const string pathstr);
extern bool verifyFile(const string pathstr);

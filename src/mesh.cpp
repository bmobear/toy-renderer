/*
mesh.cpp
contains mesh processing functions

Toy Leksut
*/

#include "main.h"

// extern
void loadMesh(const string meshFile, MooMesh& out_moomesh);
void getTestMesh(MooMesh& testmesh);

// intern
void updateMeshRadius(MooMesh& moomesh);
void updateMeshFaceIds(MooMesh& moomesh);
void setMeshVertexColor(MooMesh& moomesh);
void setMeshView(MooMesh& moomesh);

void loadMesh(const string meshFile, MooMesh& out_moomesh)
{
	out_moomesh.mesh.request_face_normals();
	out_moomesh.mesh.request_vertex_normals();
	out_moomesh.mesh.request_vertex_colors();
	out_moomesh.mesh.request_vertex_texcoords2D();

	if (!OpenMesh::IO::read_mesh(out_moomesh.mesh, meshFile)) {
		printf("Failed to load mesh file: %s\n", meshFile.c_str());
		exit(-1);
	}

	out_moomesh.mesh.update_normals();
	updateMeshRadius(out_moomesh);
	updateMeshFaceIds(out_moomesh);
	setMeshView(out_moomesh);
}

void updateMeshRadius(MooMesh& moomesh) 
{
	Mesh mesh = moomesh.mesh;

	// compute mesh center and radius 
	Mesh::ConstVertexIter  cv_it(mesh.vertices_begin()), cv_end(mesh.vertices_end());
	Mesh::Point bbMin, bbMax, p;
	float minZ = FLT_MAX;
	float maxZ = FLT_MIN;
	bbMin = bbMax = mesh.point(*cv_it);
	for (; cv_it != cv_end; ++cv_it)
	{
		p = mesh.point(*cv_it);

		bbMin.minimize(p);
		bbMax.maximize(p);
		minZ = ((p[2] < minZ) ? p[2] : minZ);
		maxZ = ((p[2] > maxZ) ? p[2] : maxZ);
	}

	p = 0.5f*(bbMin + bbMax);
	moomesh.center[0] = p[0];
	moomesh.center[1] = p[1];
	moomesh.center[2] = p[2];
	moomesh.radius = 0.5f*(bbMin - bbMax).norm();
}

void updateMeshFaceIds(MooMesh& moomesh)
{
	// collect face ids  
	Mesh::ConstFaceIter f_it, f_end = moomesh.mesh.faces_end();
	Mesh::ConstFaceVertexIter fv_it;
	moomesh.faceIds.clear();
	moomesh.faceIds.reserve(moomesh.mesh.n_faces() * 3);
	for (f_it = moomesh.mesh.faces_sbegin(); f_it != f_end; ++f_it) {
		fv_it = moomesh.mesh.cfv_iter(*f_it);
		moomesh.faceIds.push_back(fv_it->idx()); ++fv_it;
		moomesh.faceIds.push_back(fv_it->idx()); ++fv_it;
		moomesh.faceIds.push_back(fv_it->idx());
	}
}

void setMeshView(MooMesh& moomesh)
{
	float fov = 45.0;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, WINDOW_WIDTH*1.0/WINDOW_HEIGHT, 0.01f*moomesh.radius, 10.0f*moomesh.radius);
	glGetDoublev(GL_PROJECTION_MATRIX, moomesh.projection_matrix);

	double modelview_matrix[16];
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview_matrix);
	float x = -float(modelview_matrix[0] * moomesh.center[0] + 
		modelview_matrix[4] * moomesh.center[1] +
		modelview_matrix[8] * moomesh.center[2] +
		modelview_matrix[12]);
	float y = -float(modelview_matrix[1] * moomesh.center[0] +
		modelview_matrix[5] * moomesh.center[1] +
		modelview_matrix[9] * moomesh.center[2] +
		modelview_matrix[13]);
	float z = -float(modelview_matrix[2] * moomesh.center[0] +
		modelview_matrix[6] * moomesh.center[1] +
		modelview_matrix[10] * moomesh.center[2] +
		modelview_matrix[14] + 3.0*moomesh.radius);
	glTranslated(x, y, z);
	glMultMatrixd(modelview_matrix);
	glGetDoublev(GL_MODELVIEW_MATRIX, moomesh.modelview_matrix);
}

void setMeshVertexColor(MooMesh& moomesh)
{
	// set vertex color
	Mesh::VertexIter v_it, v_end(moomesh.mesh.vertices_end());
	Mesh::Color mesh_color(150, 150, 150);
	for (v_it = moomesh.mesh.vertices_begin(); v_it != v_end; ++v_it)
	{
		moomesh.mesh.set_color(*v_it, mesh_color);
	}
}

void getTestMesh(MooMesh& testmesh)
{
	Mesh mesh;

	// generate vertices
	Mesh::VertexHandle vhandle[8];
	vhandle[0] = mesh.add_vertex(Mesh::Point(-1, -1, 1));
	vhandle[1] = mesh.add_vertex(Mesh::Point(1, -1, 1));
	vhandle[2] = mesh.add_vertex(Mesh::Point(1, 1, 1));
	vhandle[3] = mesh.add_vertex(Mesh::Point(-1, 1, 1));
	vhandle[4] = mesh.add_vertex(Mesh::Point(-1, -1, -1));
	vhandle[5] = mesh.add_vertex(Mesh::Point(1, -1, -1));
	vhandle[6] = mesh.add_vertex(Mesh::Point(1, 1, -1));
	vhandle[7] = mesh.add_vertex(Mesh::Point(-1, 1, -1));

	// generate (quadrilateral) faces
	std::vector<Mesh::VertexHandle>  face_vhandles;
	face_vhandles.clear();
	face_vhandles.push_back(vhandle[0]);
	face_vhandles.push_back(vhandle[1]);
	face_vhandles.push_back(vhandle[2]);
	face_vhandles.push_back(vhandle[3]);
	mesh.add_face(face_vhandles);

	face_vhandles.clear();
	face_vhandles.push_back(vhandle[7]);
	face_vhandles.push_back(vhandle[6]);
	face_vhandles.push_back(vhandle[5]);
	face_vhandles.push_back(vhandle[4]);
	mesh.add_face(face_vhandles);
	face_vhandles.clear();
	face_vhandles.push_back(vhandle[1]);
	face_vhandles.push_back(vhandle[0]);
	face_vhandles.push_back(vhandle[4]);
	face_vhandles.push_back(vhandle[5]);
	mesh.add_face(face_vhandles);
	face_vhandles.clear();
	face_vhandles.push_back(vhandle[2]);
	face_vhandles.push_back(vhandle[1]);
	face_vhandles.push_back(vhandle[5]);
	face_vhandles.push_back(vhandle[6]);
	mesh.add_face(face_vhandles);
	face_vhandles.clear();
	face_vhandles.push_back(vhandle[3]);
	face_vhandles.push_back(vhandle[2]);
	face_vhandles.push_back(vhandle[6]);
	face_vhandles.push_back(vhandle[7]);
	mesh.add_face(face_vhandles);
	face_vhandles.clear();
	face_vhandles.push_back(vhandle[0]);
	face_vhandles.push_back(vhandle[3]);
	face_vhandles.push_back(vhandle[7]);
	face_vhandles.push_back(vhandle[4]);
	mesh.add_face(face_vhandles);

	mesh.request_face_normals();
	mesh.request_vertex_normals();
	mesh.update_normals();

	testmesh.mesh = mesh;
	updateMeshRadius(testmesh);
	updateMeshFaceIds(testmesh);
	setMeshView(testmesh);
}
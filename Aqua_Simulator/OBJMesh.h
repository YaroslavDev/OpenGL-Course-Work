#ifndef OBJMESH_H
#define OBJMESH_H

#include "Util.h"

#define POINTS_PER_VERTEX 3
#define TOTAL_FLOATS_IN_TRIANGLE 9

class OBJMesh
{
public:
	OBJMesh();
	~OBJMesh();

	void Render();
	float* CalculateNormal(float* coord1,float* coord2,float* coord3 );
	int Load(char *filename);	// Loads the model
	void Release();				// Releases the memory
private:
	void generateMeshInfo();
private:
	unsigned int meshHandle;

	float *verts;
	float *faceTris;
	float *norms;
	long connectedPoints;
	long connectedTris;
};

#endif //OBJMESH_H
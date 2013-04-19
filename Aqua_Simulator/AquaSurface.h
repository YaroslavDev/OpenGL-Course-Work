#ifndef AQUASURFACE_H
#define AQUASURFACE_H

#include "Util.h"

class AquaSurface
{
public:
	AquaSurface(const std::string& texname, float len = 10.0f, UINT nRows = 10);
	~AquaSurface();

	void setViewProj(const glm::mat4& view, const glm::mat4& proj);
	void update(float dt);
	void render();
protected:
	void buildMesh();
	void buildEffect(const std::string& effectname);
private:
	//Square surface
	float length;
	UINT rows;
	//Mesh data
	UINT meshHandle;
	std::vector<VERTEX> m_Vertices;
	float *posCoords;
	float *texCoords;
	DWORD numIndices;
	DWORD *indices;
	std::vector<DWORD> m_Indices;
	//Texture
	cTexture* tex;
	//Shader program
	GLSLProgram prog;
	//View Proj data
	glm::mat4 view;
	glm::mat4 proj;
};

#endif //AQUASURFACE_H
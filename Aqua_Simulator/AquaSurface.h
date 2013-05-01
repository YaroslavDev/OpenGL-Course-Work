#ifndef AQUASURFACE_H
#define AQUASURFACE_H

#include "Util.h"

class AquaSurface
{
public:
	AquaSurface(const std::string& texname,
				const std::string& nrm_tex,
				float len = 10.0f, UINT nRows = 10);
	~AquaSurface();

	void setViewProj(const glm::mat4& view, const glm::mat4& proj);
	void update(float dt);
	void render();

	//Aqua set methods
	void setWaveActive(int wave, int isActive);
	void setWaveFrequency(int wave, double f);
	void setWaveAmplitude(int wave, double a);
	void setWaveAngularNumber(int wave, double an);
	void setWavePhase(int wave, double ph);
	void setWavePosX(int wave, double x);
	void setWavePosZ(int wave, double z);
	//Aqua get methods
	int getWaveActive(int wave) const;
	double getWaveFrequency(int wave) const;
	double getWaveAmplitude(int wave) const;
	double getWaveAngularNumber(int wave) const;
	double getWavePhase(int wave) const;
	double getWavePosX(int wave) const;
	double getWavePosZ(int wave) const;

	void setLightPositon(const glm::vec4& lpos);
protected:
	void buildMesh();
	void buildEffect(const std::string& effectname);
private:
	//Square surface
	float length;
	UINT rows;

	int waveActive[4];
	float waveFrequency[4];
	float waveAmplitude[4];
	float waveAngularNumber[4];
	float wavePhase[4];
	float wavePosX[4];
	float wavePosZ[4];

	glm::vec4 lightpos;
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
	cTexture* nrm_tex;
	//Shader program
	GLSLProgram prog;
	//View Proj data
	glm::mat4 view;
	glm::mat4 proj;
};

#endif //AQUASURFACE_H
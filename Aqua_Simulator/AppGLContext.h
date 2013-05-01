#ifndef APPGLCONTEXT_H
#define APPGLCONTEXT_H

#include "Util.h"
#include "GLSLProgram.h"
#include "AppFrame.h"
#include "Mesh.h"
#include "AquaSurface.h"
#include "Skybox.h"

class AppFrame;

class AppGLContext : public wxGLContext
{
public:
	AppGLContext(wxGLCanvas *canvas);
	virtual ~AppGLContext();

	void render();
	void update(float dt);
	void initShaders();
	void updateAppFrame(int wave);	//init gui with values from glContext
	void setProjectionMatrix(float fov, float aspect, float nearZ, float farZ);
	void setModulationColor(float r, float g, float b, float a);
	void setAppFrame(AppFrame*	frame);

	void reloadMesh(const char * filepath);
	//Aqua surface methods
	void setWaveActive(int wave, int isActive);
	void setWaveFrequency(int wave, double f);
	void setWaveAmplitude(int wave, double a);
	void setWaveAngularNumber(int wave, double an);
	void setWavePhase(int wave, double ph);
	void setWavePosX(int wave, double x);
	void setWavePosZ(int wave, double z);
	//Light methods
	void setLightPosX(double x);
	void setLightPosY(double y);
	void setLightPosZ(double z);
protected:
	void setMatrices();
private:
	AppFrame	*mainFrame;	//host frame; to access GUI

	bool glsl120fallback;
	GLSLProgram prog;
	CMesh	*seabed;
	CMesh	*dolphin;
	mat4	dolphinWorld;
	cTexture tex;
	mat4 model;
	mat4 view;
	mat4 projection;

	cTimer fpsTimer;
	int fpsCount;

	AquaSurface *aquaSurf;

	SkyBox*	sky;

	glm::vec4 lightPos;
};

#endif //APPGLCONTEXT_H
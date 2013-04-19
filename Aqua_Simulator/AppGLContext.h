#ifndef APPGLCONTEXT_H
#define APPGLCONTEXT_H

#include "Util.h"
#include "GLSLProgram.h"
#include "AppFrame.h"
#include "Mesh.h"
#include "AquaSurface.h"

class AppFrame;

class AppGLContext : public wxGLContext
{
public:
	AppGLContext(wxGLCanvas *canvas);
	virtual ~AppGLContext();

	void render();
	void update(float dt);
	void initShaders();
	void setProjectionMatrix(float fov, float aspect, float nearZ, float farZ);
	void setModulationColor(float r, float g, float b, float a);
	void setAppFrame(AppFrame*	frame);

	void reloadMesh(const char * filepath);
protected:
	void setMatrices();
private:
	AppFrame	*mainFrame;	//host frame; to access GUI

	bool glsl120fallback;
	GLSLProgram prog;
	CMesh	*mesh;
	cTexture tex;
	mat4 model;
	mat4 view;
	mat4 projection;
	float angle;
	cTimer fpsTimer;
	int fpsCount;

	AquaSurface *aquaSurf;
};

#endif //APPGLCONTEXT_H
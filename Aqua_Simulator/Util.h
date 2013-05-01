#ifndef UTIL_H
#define UTIL_H

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "glew.h"
#include "glm\glm.hpp"
#include "glm\gtc\quaternion.hpp"
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform2.hpp>
#include "wx\glcanvas.h"

#include "cTimer.h"
#include "cTexture.h"
#include "GLSLProgram.h"
#include <fstream>
#include <vector>
#include <string>

/*  Necessary libs:

	wxmsw29ud_gl.lib
	opengl32.lib
	glu32.lib
	glew32.lib
	soil.lib
	wxmsw29ud_core.lib
	wxbase29ud.lib
*/

#define SAFE_DELETE(x) { if(x) { delete (x); (x)=NULL; } }

#define SAFE_DELETE_ARRAY(x) { if(x) { delete[] (x); (x)=NULL; } }

#define SAFE_ARRAY_SETVALUE(arr, size, index, val) { if( index>=0 && index<size ) { arr[index] = val; } }

// control ids
enum
{
    SpinTimer = wxID_HIGHEST + 1
};

// Vertex format
struct VERTEX
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texcoord;
};

// Material properties per mesh subset
struct Material
{
	Material() : tex(NULL) 
	{
		tex = new cTexture();
	}
	Material(const Material& mat)
	{
		strcpy(strName, mat.strName);
		vAmbient = mat.vAmbient;
		vDiffuse = mat.vDiffuse;
		vSpecular = mat.vSpecular;

		nShininess = mat.nShininess;
		fAlpha = mat.fAlpha;
		bSpecular = mat.bSpecular;

		strTexture = mat.strTexture;

		tex = mat.tex;
	}
	Material& operator=(const Material& mat)
	{
		strcpy(strName, mat.strName);
		vAmbient = mat.vAmbient;
		vDiffuse = mat.vDiffuse;
		vSpecular = mat.vSpecular;

		nShininess = mat.nShininess;
		fAlpha = mat.fAlpha;
		bSpecular = mat.bSpecular;

		strTexture = mat.strTexture;

		tex = mat.tex;
	}
	~Material() 
	{ 
		SAFE_DELETE(tex); 
	}
    char   strName[MAX_PATH];

    glm::vec3 vAmbient;
    glm::vec3 vDiffuse;
    glm::vec3 vSpecular;

    int nShininess;
    float fAlpha;

    bool bSpecular;

	std::string strTexture;
	cTexture *tex;
};

// ----------------------------------------------------------------------------
// helper functions
// ----------------------------------------------------------------------------

void CheckGLError();

class GLUtils
{
public:
    GLUtils();

    static int checkForOpenGLError(const char *, int);
    static void dumpGLInfo(bool dumpExtensions = false);
};

#endif //UTIL_H
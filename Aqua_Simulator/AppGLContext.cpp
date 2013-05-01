#include "AppGLContext.h"

AppGLContext::AppGLContext(wxGLCanvas	*canvas)
	: wxGLContext(canvas),
	mainFrame(NULL),
	seabed(NULL),
	aquaSurf(NULL),
	sky(NULL)
{
	SetCurrent(*canvas);

	GLenum err = glewInit();
	if( GLEW_OK != err )
	{
		wxLogError("Can't initialize GLEW! Error: %s", glewGetErrorString(err));
	}

	glsl120fallback = false;
	fpsCount = 0;
	
	initShaders();

	seabed = new CMesh();
	seabed->Create("seabed.obj");
	seabed->setGLSLProgram(&prog);

	aquaSurf = new AquaSurface("aqua.jpg", "aqua_nrm.png", 10.0f, 80);

	sky = new SkyBox();
	sky->loadCubeMap("texture/pos_x.jpg",
					 "texture/neg_x.jpg",
					 "texture/pos_y.jpg",
					 "texture/neg_y.jpg",
					 "texture/pos_z.jpg",
					 "texture/neg_z.jpg");
	sky->buildEffect("cubemap");

	//Initialize light data
	lightPos = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

	CheckGLError();
}

AppGLContext::~AppGLContext()
{
	SAFE_DELETE(seabed);
	SAFE_DELETE(aquaSurf);
	SAFE_DELETE(sky);
}

void AppGLContext::updateAppFrame(int wave)
{
	//Update GUI according to glContext values
	mainFrame->setIsActiveCheckBox( aquaSurf->getWaveActive(wave) );
	mainFrame->setFrequencySpin( aquaSurf->getWaveFrequency(wave) );
	mainFrame->setAmplitudeSpin( aquaSurf->getWaveAmplitude(wave) );
	mainFrame->setAngularWaveSpin( aquaSurf->getWaveAngularNumber(wave) );
	mainFrame->setPhaseSpin( aquaSurf->getWavePhase(wave) );
	mainFrame->setWavePosXSpin( aquaSurf->getWavePosX(wave) );
	mainFrame->setWavePosZSpin( aquaSurf->getWavePosZ(wave) );

	mainFrame->setLightPosXSpin( lightPos.x );
	mainFrame->setLightPosYSpin( lightPos.y );
	mainFrame->setLightPosZSpin( lightPos.z );
}

void AppGLContext::initShaders()
{
	if(glsl120fallback==false)
	{
		if( ! prog.compileShaderFromFile("shader/texture.vs",GLSLShader::VERTEX) )
		{
			printf("Vertex shader failed to compile!\n%s",
				   prog.log().c_str());
			exit(1);
		}
		if( ! prog.compileShaderFromFile("shader/texture.fs",GLSLShader::FRAGMENT))
		{
			printf("Fragment shader failed to compile!\n%s",
				   prog.log().c_str());
			exit(1);
		}
	}
	else
	{
		if( ! prog.compileShaderFromFile("shader/120/texture.vs",GLSLShader::VERTEX) )
		{
			printf("Vertex shader failed to compile!\n%s",
				   prog.log().c_str());
			exit(1);
		}
		if( ! prog.compileShaderFromFile("shader/120/texture.fs",GLSLShader::FRAGMENT))
		{
			printf("Fragment shader failed to compile!\n%s",
				   prog.log().c_str());
			exit(1);
		}
	}

	//bind attributes in case of glsl 1.20 fallback
	if(glsl120fallback)
	{		
		glBindAttribLocation(prog.getHandle(), 0, "VertexPosition");
		glBindAttribLocation(prog.getHandle(), 1, "VertexNormal");
		glBindAttribLocation(prog.getHandle(), 2, "VertexTexCoord");
	}

    if( ! prog.link() )
    {
        printf("Shader program failed to link!\n%s",
               prog.log().c_str());
        exit(1);
    }

	glEnable(GL_DEPTH_TEST);

    view = glm::lookAt(vec3(0.0f,1.25f,2.25f), vec3(0.0f,0.0f,0.0f), vec3(0.0f,1.0f,0.0f));
    projection = mat4(1.0f);
}
void AppGLContext::setMatrices()
{
	if( seabed )
	{
		seabed->setViewProj(view, projection);
		seabed->setLightPos(lightPos);
	}
	if( aquaSurf )
	{
		aquaSurf->setViewProj(view, projection);
		aquaSurf->setLightPositon(lightPos);
	}
	if( sky )
	{
		sky->setViewProj(view, projection);
	}
}

void AppGLContext::setAppFrame(AppFrame*	frame)
{
	mainFrame = frame;
}

void AppGLContext::setProjectionMatrix(float fov, float aspect, float nearZ, float farZ)
{
	projection = glm::perspective(fov, aspect, nearZ, farZ);
}

void AppGLContext::setModulationColor(float r, float g, float b, float a)
{
	//TODO
}

void AppGLContext::update(float dt)
{
	static float eye_x = 0.0f, eye_z = 0.0f;
	static float time = 0.0f;
	time += dt;

	eye_x = 3.0f*cosf(0.25f*time);
	eye_z = 3.0f*sinf(0.25f*time);

	view = glm::lookAt(vec3(eye_x,1.25f,eye_z), vec3(0.0f,0.0f,0.0f), vec3(0.0f,1.0f,0.0f));

    setMatrices();

	if( aquaSurf )
	{
		aquaSurf->update(dt);
	}
}

void AppGLContext::render()
{
	//calc fps & update status bar
	fpsTimer.AdvanceTime();
	fpsCount++;	
	if(fpsTimer.GetElapsedTime()>1)
	{	
		if( mainFrame )
		{
			char tempBuf[512];		
			sprintf(tempBuf,"FPS: %d",fpsCount);
			mainFrame->getStatusBar()->SetStatusText(tempBuf);
		}
		fpsTimer.Reset();
		fpsCount=0;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if( seabed )
	{
		seabed->Render();
	}

	if( aquaSurf )
	{
		aquaSurf->render();
	}

	if( sky )
	{
		sky->render();
	}

    CheckGLError();
}

void AppGLContext::reloadMesh(const char *filepath)
{
	seabed->Create(filepath);
}

//Aqua set methods
void AppGLContext::setWaveActive(int wave, int isActive)
{
	aquaSurf->setWaveActive(wave, isActive);
}
void AppGLContext::setWaveFrequency(int wave, double f)
{
	aquaSurf->setWaveFrequency(wave, f);
}
void AppGLContext::setWaveAmplitude(int wave, double a)
{
	aquaSurf->setWaveAmplitude(wave, a);
}
void AppGLContext::setWaveAngularNumber(int wave, double an)
{
	aquaSurf->setWaveAngularNumber(wave, an);
}
void AppGLContext::setWavePhase(int wave, double ph)
{
	aquaSurf->setWavePhase(wave, ph);
}
void AppGLContext::setWavePosX(int wave, double x)
{
	aquaSurf->setWavePosX(wave, x);
}
void AppGLContext::setWavePosZ(int wave, double z)
{
	aquaSurf->setWavePosZ(wave, z);
}

//Light set methods
void AppGLContext::setLightPosX(double x)
{
	lightPos.x = x;
}
void AppGLContext::setLightPosY(double y)
{
	lightPos.y = y;
}
void AppGLContext::setLightPosZ(double z)
{
	lightPos.z = z;
}
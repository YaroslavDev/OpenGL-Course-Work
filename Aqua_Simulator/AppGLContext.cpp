#include "AppGLContext.h"

AppGLContext::AppGLContext(wxGLCanvas	*canvas)
	: wxGLContext(canvas),
	mainFrame(NULL),
	mesh(NULL),
	aquaSurf(NULL)
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

	aquaSurf = new AquaSurface("aqua.jpg", 2.0f, 20);

	CheckGLError();
}

AppGLContext::~AppGLContext()
{
	SAFE_DELETE(mesh);
	SAFE_DELETE(aquaSurf);
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

    prog.use();

	glEnable(GL_DEPTH_TEST);

	mesh = new CMesh();
	mesh->Create("cup.obj");

    view = glm::lookAt(vec3(0.0f,1.25f,2.25f), vec3(0.0f,0.0f,0.0f), vec3(0.0f,1.0f,0.0f));
    projection = mat4(1.0f);

    angle = 0.0;

    prog.setUniform("Light.Intensity", vec3(2.0f,2.0f,2.0f) );

    // Load texture file
    const char * texName = "texture/brick1.jpg";
	
    // Copy file to OpenGL
    glActiveTexture(GL_TEXTURE0); 
	glBindTexture(GL_TEXTURE_2D, mesh->GetMaterial(2)->tex->GetTextureHandle());   
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    prog.setUniform("Tex1", 0);
}
void AppGLContext::setMatrices()
{
	mat4 mv = view * model;
	prog.use();
    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("NormalMatrix",
                    mat3( vec3(mv[0]), vec3(mv[1]), vec3(mv[2]) ));
    prog.setUniform("MVP", projection * mv);

	if( aquaSurf )
	{
		aquaSurf->setViewProj(view, projection);
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
	float angVel = 30.0f;
	static float angle = 0.0f;
	angle += angVel*dt;

	model = mat4(1.0f);
	//model *= glm::rotate(angle, vec3(0.0f,1.0f,0.0f));
    model *= glm::rotate(angle, vec3(1.0f,0.0f,0.0f));
    //model *= glm::rotate(angle, vec3(0.0f,0.0f,1.0f));
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

	prog.use();

	glActiveTexture(GL_TEXTURE0); 
	glBindTexture(GL_TEXTURE_2D, mesh->GetMaterial(2)->tex->GetTextureHandle());   
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    prog.setUniform("Tex1", 0);
	
    prog.setUniform("Light.Position", vec4(0.0f,0.0f,0.0f,1.0f) );
    prog.setUniform("Material.Kd", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Ks", 0.95f, 0.95f, 0.95f);
    prog.setUniform("Material.Ka", 0.1f, 0.1f, 0.1f);
    prog.setUniform("Material.Shininess", 100.0f);

	prog.setUniform("MVP", projection * view * model);

	mesh->Render();

	if( aquaSurf )
	{
		aquaSurf->render();
	}

    CheckGLError();
}

void AppGLContext::reloadMesh(const char *filepath)
{
	mesh->Create(filepath);
}
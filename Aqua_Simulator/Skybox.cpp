#include "skybox.h"
#include "defines.h"

#include <glew.h>


SkyBox::SkyBox()
	: cubeTex(-1)
{
    float side = 50.0f;
    float side2 = side / 2.0f;
    float v[24*3] = {
        // Front
       -side2, -side2, side2,
        side2, -side2, side2,
        side2,  side2, side2,
       -side2,  side2, side2,
       // Right
        side2, -side2, side2,
        side2, -side2, -side2,
        side2,  side2, -side2,
        side2,  side2, side2,
       // Back
       -side2, -side2, -side2,
       -side2,  side2, -side2,
        side2,  side2, -side2,
        side2, -side2, -side2,
       // Left
       -side2, -side2, side2,
        side2,  side2, side2,
       -side2,  side2, -side2,
       -side2, -side2, -side2,
       // Bottom
       -side2, -side2, side2,
       -side2, -side2, -side2,
        side2, -side2, -side2,
        side2, -side2, side2,
       // Top
       -side2,  side2, side2,
        side2,  side2, side2,
        side2,  side2, -side2,
       -side2,  side2, -side2
    };

    GLuint el[] = {
        0,2,1,0,3,2,
        4,6,5,4,7,6,
        8,10,9,8,11,10,
        12,14,13,12,15,14,
        16,18,17,16,19,18,
        20,22,21,20,23,22
    };

    unsigned int handle[2];
    glGenBuffers(2, handle);

    glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
    glBufferData(GL_ARRAY_BUFFER, 24 * 3 * sizeof(float), v, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(GLuint), el, GL_STATIC_DRAW);

    glGenVertexArrays( 1, &vaoHandle );
    glBindVertexArray(vaoHandle);

    glVertexAttribPointer( (GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)0 + (0)) );
    glEnableVertexAttribArray(0);  // Vertex position

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle[1]);

    glBindVertexArray(0);
}

void SkyBox::loadCubeMap(const std::string& pos_x,
						 const std::string& neg_x,
						 const std::string& pos_y,
						 const std::string& neg_y,
						 const std::string& pos_z,
						 const std::string& neg_z)
{
	cubeTex = SOIL_load_OGL_cubemap(pos_x.c_str(), neg_x.c_str(),
									pos_y.c_str(), neg_y.c_str(),
									pos_z.c_str(), neg_z.c_str(),
									SOIL_LOAD_RGBA,
									SOIL_CREATE_NEW_ID,
									SOIL_FLAG_MIPMAPS|SOIL_FLAG_INVERT_Y);
}

void SkyBox::buildEffect(const std::string& effectname)
{
	char path[1024];
	sprintf(path, "shader\\%s.vs", effectname.c_str());
	if( ! prog.compileShaderFromFile(path, GLSLShader::VERTEX) )
	{
		printf("Vertex shader failed to compile!\n%s",
			   prog.log().c_str());
		exit(1);
	}
	sprintf(path, "shader\\%s.fs", effectname.c_str());
	if( ! prog.compileShaderFromFile(path, GLSLShader::FRAGMENT))
	{
		printf("Fragment shader failed to compile!\n%s",
			   prog.log().c_str());
		exit(1);
	}

    if( ! prog.link() )
    {
        printf("Shader program failed to link!\n%s",
               prog.log().c_str());
        exit(1);
    }
}

void SkyBox::setViewProj(const glm::mat4& _view, const glm::mat4& _proj)
{
	view = _view;
	proj = _proj;
}

void SkyBox::render()
{
	prog.use();

	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTex);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	prog.setUniform("MVP", proj * view);
	prog.setUniform("CubeMapTex", 0);

    glBindVertexArray(vaoHandle);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, ((GLubyte *)0 + (0)));
}

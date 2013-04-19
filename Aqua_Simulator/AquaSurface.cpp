#include "AquaSurface.h"

AquaSurface::AquaSurface(const std::string& texname, float len, UINT nrows)
	: length(len), rows(nrows), tex(NULL), numIndices(0)
{
	tex = new cTexture();
	tex->LoadFromFile(texname);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex->GetTextureHandle());   
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	buildEffect("aquasurf");
	buildMesh();
}

AquaSurface::~AquaSurface()
{
	SAFE_DELETE(tex);
	SAFE_DELETE_ARRAY(posCoords);
	SAFE_DELETE_ARRAY(texCoords);
	SAFE_DELETE_ARRAY(indices);
}

void AquaSurface::buildMesh()
{
	int numVerts = rows*rows;
	int numCellRows = rows - 1;
	int numTris = 2*numCellRows*numCellRows;

	posCoords = new float[3*numVerts];
	texCoords = new float[2*numVerts];

	//Build vertices
	float xOffset = -length*0.5f;
	float zOffset = -length*0.5f;

	float dx = length / (float)(rows-1);
	float dz = dx;

	float dtex = 1.0f / (float)(rows-1);

	int k=0, l=0;
	for(float i=0; i<rows; i++)
	{
		for(float j=0; j<rows; j++)
		{
			posCoords[k+0] = j*dx + xOffset;
			posCoords[k+1] = 0.0f;
			posCoords[k+2] = i*dz + zOffset;

			texCoords[l+0] = j*dtex;
			texCoords[l+1] = i*dtex;

			k+=3;
			l+=2;
		}
	}
	//Build indices
	numIndices = 3*numTris;

	indices = new DWORD[numIndices];
	k = 0;
	for(DWORD i=0; i < numCellRows; i++)
	{
		for(DWORD j=0; j < numCellRows; j++)
		{
			//Clockwise winding order
			indices[k]   =   i   * rows + j;
			indices[k + 1] =   i   * rows + j + 1;
			indices[k + 2] = (i+1) * rows + j;
					
			indices[k + 3] = (i+1) * rows + j;
			indices[k + 4] =   i   * rows + j + 1;
			indices[k + 5] = (i+1) * rows + j + 1;

			//Counter-clockwise winding order
			/*indices[k]     =   i   * rows + j;
			indices[k + 1] = (i+1) * rows + j;
			indices[k + 2] =   i   * rows + j + 1;
					
			indices[k + 3] =   i   * rows + j + 1;
			indices[k + 4] = (i+1) * rows + j;
			indices[k + 5] = (i+1) * rows + j + 1;*/

			// next quad
			k += 6;
		}
	}

	glGenVertexArrays( 1, &meshHandle );
    glBindVertexArray(meshHandle);

    unsigned int handle[3];
    glGenBuffers(3, handle);

    glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
	glBufferData(GL_ARRAY_BUFFER, numVerts * 3 * sizeof(float), posCoords, GL_STATIC_DRAW);
    glVertexAttribPointer( (GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)) );
    glEnableVertexAttribArray(0);  // Vertex position

    glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
    glBufferData(GL_ARRAY_BUFFER, numVerts * 2 * sizeof(float), texCoords, GL_STATIC_DRAW);
    glVertexAttribPointer( (GLuint)1, 2, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)) );
    glEnableVertexAttribArray(1);  // texture coords

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(GLuint), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void AquaSurface::buildEffect(const std::string& effectname)
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

	//glEnable(GL_DEPTH_TEST);
}

void AquaSurface::setViewProj(const glm::mat4& _view, const glm::mat4& _proj)
{
	view = _view;
	proj = _proj;

	glm::mat4 pv = proj * view;
	prog.use();
	prog.setUniform("MVP", pv);
}

void AquaSurface::update(float dt)
{
	prog.use();
	static float totalTime = 0.0f;
	totalTime += dt;
	prog.setUniform("dt", totalTime);
}

void AquaSurface::render()
{
	prog.use();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex->GetTextureHandle());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	prog.setUniform("Tex1", 0);

	prog.setUniform("Light.Intensity", vec3(2.0f,2.0f,2.0f) );
	prog.setUniform("Light.Position", vec4(0.0f,2.0f,0.0f,1.0f) );
    prog.setUniform("Material.Kd", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Ks", 0.95f, 0.95f, 0.95f);
    prog.setUniform("Material.Ka", 0.1f, 0.1f, 0.1f);
    prog.setUniform("Material.Shininess", 100.0f);

	glBindVertexArray(meshHandle);
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, ((GLubyte *)NULL + (0)));
}
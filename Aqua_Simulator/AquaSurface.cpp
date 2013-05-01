#include "AquaSurface.h"

AquaSurface::AquaSurface(const std::string& texname, 
						const std::string& nrm_texname,
						float len, UINT nrows)
	: length(len), rows(nrows), tex(NULL), numIndices(0)
{
	tex = new cTexture();
	tex->LoadFromFile(texname);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex->GetTextureHandle());   
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	nrm_tex = new cTexture();
	nrm_tex->LoadFromFile(nrm_texname);
	/*glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, nrm_tex->GetTextureHandle());   
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);*/

	buildEffect("aquasurf");
	buildMesh();

	//Initialize aqua data
	waveActive[0] = 1;			waveActive[1] = 1;			waveActive[2] = 0;			waveActive[3] = 0; 
	waveFrequency[0] = 3.0f;	waveFrequency[1] = 5.0f;	waveFrequency[2] = 1.0f;	waveFrequency[3] = 2.0f;
	waveAmplitude[0] = 0.04f;	waveAmplitude[1] = 0.02f;	waveAmplitude[2] = 0.03f;	waveAmplitude[3] = 0.02f;
	waveAngularNumber[0]=10.0f;	waveAngularNumber[1]=7.0f;	waveAngularNumber[2]=8.0f;	waveAngularNumber[3] = 9.0f;
	wavePhase[0] = 0.0f;		wavePhase[1] = 0.2f;		wavePhase[2] = 0.3f;		wavePhase[3] = 0.4f;
	wavePosX[0] = 0.0f;			wavePosX[1] = 1.5f;			wavePosX[2] = 0.0f;			wavePosX[3] = -1.5f;
	wavePosZ[0] = 0.0f;			wavePosZ[1] = 0.0f;			wavePosZ[2] = -1.5f;		wavePosZ[3] = 0.0f;

	//Initialize light data
	lightpos = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
}

AquaSurface::~AquaSurface()
{
	SAFE_DELETE(tex);
	SAFE_DELETE(nrm_tex);
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
}

void AquaSurface::setViewProj(const glm::mat4& _view, const glm::mat4& _proj)
{
	view = _view;
	proj = _proj;
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

	glEnablei(GL_BLEND, 0);

	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex->GetTextureHandle());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	prog.setUniform("Tex1", 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, nrm_tex->GetTextureHandle());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	prog.setUniform("NormalTex", 1);

	prog.setUniform("Light.Intensity", vec3(1.0f, 1.0f, 1.0f) );
	prog.setUniform("Light.Position", lightpos );
    prog.setUniform("Material.Kd", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Ks", 1.0f, 1.0f, 1.0f);
    prog.setUniform("Material.Ka", 0.1f, 0.1f, 0.1f);
    prog.setUniform("Material.Shininess", 100.0f);

	prog.setUniform("MVP", proj * view);

	prog.setUniformArray("active", 4, waveActive);
	prog.setUniformArray("w", 4, waveFrequency);
	prog.setUniformArray("a", 4, waveAmplitude);
	prog.setUniformArray("k", 4, waveAngularNumber);
	prog.setUniformArray("p", 4, wavePhase);
	prog.setUniformArray("c_x", 4, wavePosX);
	prog.setUniformArray("c_z", 4, wavePosZ);

	glBindVertexArray(meshHandle);
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, ((GLubyte *)NULL + (0)));

	glDisablei(GL_BLEND, 0);
}

void AquaSurface::setLightPositon(const glm::vec4& lpos)
{
	lightpos = lpos;
}

//Aqua set methods
void AquaSurface::setWaveActive(int wave, int isActive)
{
	SAFE_ARRAY_SETVALUE(waveActive, 4, wave, isActive);
}
void AquaSurface::setWaveFrequency(int wave, double f)
{
	SAFE_ARRAY_SETVALUE(waveFrequency, 4, wave, f);
}
void AquaSurface::setWaveAmplitude(int wave, double a)
{
	SAFE_ARRAY_SETVALUE(waveAmplitude, 4, wave, a);
}
void AquaSurface::setWaveAngularNumber(int wave, double an)
{
	SAFE_ARRAY_SETVALUE(waveAngularNumber, 4, wave, an);
}
void AquaSurface::setWavePhase(int wave, double ph)
{
	SAFE_ARRAY_SETVALUE(wavePhase, 4, wave, ph);
}
void AquaSurface::setWavePosX(int wave, double x)
{
	SAFE_ARRAY_SETVALUE(wavePosX, 4, wave, x);
}
void AquaSurface::setWavePosZ(int wave, double z)
{
	SAFE_ARRAY_SETVALUE(wavePosZ, 4, wave, z);
}

int AquaSurface::getWaveActive(int wave) const
{
	return waveActive[wave];
}
double AquaSurface::getWaveFrequency(int wave) const
{
	return waveFrequency[wave];
}
double AquaSurface::getWaveAmplitude(int wave) const
{
	return waveAmplitude[wave];
}
double AquaSurface::getWaveAngularNumber(int wave) const
{
	return waveAngularNumber[wave];
}
double AquaSurface::getWavePhase(int wave) const
{
	return wavePhase[wave];
}
double AquaSurface::getWavePosX(int wave) const
{
	return wavePosX[wave];
}
double AquaSurface::getWavePosZ(int wave) const
{
	return wavePosZ[wave];
}
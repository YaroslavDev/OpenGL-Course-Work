#include "cTexture.h"

cTexture::cTexture(void)
{
	texHandle=-1;
	texPath = "null";
}

cTexture::~cTexture(void)
{
	if(texHandle>=0)
	glDeleteTextures(1,&texHandle);
}
void cTexture::LoadFromFile(const std::string& filePathIn)
{
	texPath.assign(filePathIn);
	texHandle = SOIL_load_OGL_texture(filePathIn.c_str(),
										SOIL_LOAD_RGBA,
										SOIL_CREATE_NEW_ID,
										SOIL_FLAG_MIPMAPS|SOIL_FLAG_INVERT_Y);
}
GLuint cTexture::GetTextureHandle()
{
	return this->texHandle;	
}
const char * cTexture::GetTexturePath()
{
	return texPath.c_str();
}


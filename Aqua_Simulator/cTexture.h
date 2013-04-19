#pragma once
#include "glew.h"
#include "soil.h"
#include "string.h"
#include <iostream>

class cTexture
{
public:
	cTexture(void);
	virtual ~cTexture(void);
	void LoadFromFile(const std::string& filePath);
	GLuint GetTextureHandle();
	const char * GetTexturePath();
private:
	GLuint texHandle;
	std::string texPath;
	//char texPath[1024];
};

extern cTexture textures[100];

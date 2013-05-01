#ifndef SKYBOX_H
#define SKYBOX_H

#include "Util.h"

#include "drawable.h"

class SkyBox : public Drawable
{
private:
    unsigned int vaoHandle;

public:
    SkyBox();

	void loadCubeMap(const std::string& pos_x,
					 const std::string& neg_x,
					 const std::string& pos_y,
					 const std::string& neg_y,
					 const std::string& pos_z,
					 const std::string& neg_z);
	void buildEffect(const std::string& effectName);

	void setViewProj(const glm::mat4& view, const glm::mat4& proj);
    void render();

protected:
	//Cubemap texture(consists of 6 textures)
	GLuint cubeTex;

	//Shader program
	GLSLProgram prog;

	//View Proj data
	glm::mat4 view;
	glm::mat4 proj;
};


#endif // SKYBOX_H

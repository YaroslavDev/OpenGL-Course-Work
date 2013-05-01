#version 330

in vec3 ReflectDir;

uniform samplerCube CubeMapTex;

layout( location = 0 ) out vec4 FragColor;

void main() 
{
    // Access the cube map texture
    vec4 cubeMapColor = texture(CubeMapTex, ReflectDir);

    FragColor = cubeMapColor;
}

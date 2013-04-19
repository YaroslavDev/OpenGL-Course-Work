#version 330

layout(location = 0) in vec4 VertexPosition;
layout(location = 1) in vec4 colorIn;
uniform mat4 cameraToClipMatrix;
uniform mat4 worldToCameraMatrix;
uniform mat4 modelToWorldMatrix;
uniform vec4 fragModulationColor;

smooth out vec4 colorForFS;

void main()
{	
	vec4 temp = modelToWorldMatrix * VertexPosition;
    temp = worldToCameraMatrix * temp;
    gl_Position = cameraToClipMatrix * temp;
    //colorForFS=colorIn;
	colorForFS = fragModulationColor;
}


	
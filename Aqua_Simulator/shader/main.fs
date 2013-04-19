#version 330

smooth in vec4 colorForFS;
out vec4 fragColor;
uniform vec4 fragModulationColor;

void main()
{
	//fragColor=colorForFS*fragModulationColor;
	fragColor=colorForFS;
}

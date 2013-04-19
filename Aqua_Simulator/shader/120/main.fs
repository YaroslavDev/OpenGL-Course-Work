#version 120

smooth varying vec4 colorForFS;
uniform vec4 fragModulationColor;

void main()
{
	gl_FragColor=colorForFS*fragModulationColor;
}

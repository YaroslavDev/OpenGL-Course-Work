#version 330

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec2 VertexTexCoord;

out vec3 Position;
out vec2 TexCoord;
out vec3 Normal;

uniform float dt;
uniform mat4 MVP;

// Amplitudes
float a[2] = float[2](0.1f, 0.05f);
	
// Angular wave numbers.
float k[2] = float[2](1.0, 8.0f);
	
// Angular frequency.
float w[2] = float[2](4.0f, 8.0f);
	
// Phase shifts.
float p[2] = float[2](0.0f, 1.0f);

float SumOfRadialSineWaves(float x, float z)
{
	// Distance of vertex from source of waves (which we set
	// as the origin of the local space).
	float d = sqrt(x*x + z*z);
	
	// Sum the waves.
	float sum = 0.0f;
	for(int i = 0; i < 2; ++i)
		sum += a[i]*sin(k[i]*d - dt*w[i] + p[i]);
	return sum;
}

void Partials(float x, float z, out float dhOverdx, out float dhOverdz)
{
	float d=x*x+z*z;
	if(d<0.01f)
		dhOverdx=dhOverdz=0.0f;
	else
	{
		d=sqrt(d);
		dhOverdx=dhOverdz=0.0f;
		for(int i = 0; i < 2; i++)
		{
			dhOverdx += (a[i]*k[i]*x*cos(k[i]*d - dt*w[i] + p[i]))/d;
			dhOverdz += (a[i]*k[i]*z*cos(k[i]*d - dt*w[i] + p[i]))/d;
		}
	}
}

void main()
{
    TexCoord = VertexTexCoord;
	vec3 pos = VertexPosition;
	pos.y = SumOfRadialSineWaves(pos.x, pos.z);

	float dhOverDx = 0, dhOverDz = 0;
	Partials(pos.x, pos.z, dhOverDx, dhOverDz);
	vec3 u = vec3(1.0, dhOverDx, 0.0);
	vec3 v = vec3(0.0, dhOverDz, 1.0);
	Normal = normalize( cross(u,v) );

	Position = pos;
    gl_Position = MVP * vec4(pos, 1.0);
} 
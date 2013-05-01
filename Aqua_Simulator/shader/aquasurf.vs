#version 330

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec2 VertexTexCoord;

out vec3 Position;
out vec3 Normal;
out vec2 TexCoord;
out vec3 Tangent;
out vec3 Binormal;

uniform float dt;
uniform mat4 MVP;

#define NUM_WAVE_GENS 4

// On/off switched for wave generators
uniform int active[NUM_WAVE_GENS];// = int[NUM_WAVE_GENS](1, 1, 0, 0);

//Wave centers
uniform float c_x[NUM_WAVE_GENS];// = float[NUM_WAVE_GENS](0.0f, 1.5f, 0.0f, -2.5f);
uniform float c_z[NUM_WAVE_GENS];// = float[NUM_WAVE_GENS](0.0f, 0.0f, -2.5f, 0.0f);

// Amplitudes
uniform float a[NUM_WAVE_GENS];// = float[NUM_WAVE_GENS](0.04f, 0.02f, 0.03f, 0.02f);
	
// Angular wave numbers.
uniform float k[NUM_WAVE_GENS];// = float[NUM_WAVE_GENS](10.0, 7.0f, 10.0f, 10.0f);
	
// Angular frequency.
uniform float w[NUM_WAVE_GENS];// = float[NUM_WAVE_GENS](3.0f, 5.0f, 1.0f, 2.0f);
	
// Phase shifts.
uniform float p[NUM_WAVE_GENS];// = float[NUM_WAVE_GENS](0.0f, 0.2f, 0.3f, 0.4f);

float SumOfRadialSineWaves(float _x, float _z)
{
	float x, z, d;
	// Sum the waves.
	float sum = 0.0f;
	float num_waves = 0.0f;
	for(int j = 0; j < NUM_WAVE_GENS; ++j)
	{
		if( active[j]==1 )		//if this wave generator is active
		{
			// Distance of vertex from source of waves (which we set
			// as the origin of the local space).
			x = _x - c_x[j];
			z = _z - c_z[j];
			d = sqrt(x*x + z*z);
		
			sum += a[j]*sin(k[j]*d - dt*w[j] + p[j]);
			num_waves = num_waves + 1.0f;
		}
	}
	sum /= num_waves;
	return sum;
}

void Partials(float _x, float _z, out float dhOverdx, out float dhOverdz)
{
	float x, z, d;
	dhOverdx=dhOverdz=0.0f;
	float num_waves = 0.0f;
	for(int j = 0; j < NUM_WAVE_GENS; j++)
	{
		if( active[j]==1 )		//if this wave generator is active
		{
			x = _x - c_x[j];
			z = _z - c_z[j];
			d=x*x+z*z;
			d = sqrt(d);
		
			if( d<0.01f )
			{
				dhOverdx = dhOverdz = 0.0f;
			}

			dhOverdx += (a[j]*k[j]*x*cos(k[j]*d - dt*w[j] + p[j]))/d;
			dhOverdz += (a[j]*k[j]*z*cos(k[j]*d - dt*w[j] + p[j]))/d;
			num_waves = num_waves + 1.0f;
		}
	}
	dhOverdx /= num_waves;
	dhOverdz /= num_waves;
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
	Normal = normalize( cross(v,u) );

	Tangent = normalize( u );
	Binormal = normalize( v );

	Position = pos;
    gl_Position = MVP * vec4(pos, 1.0);
} 
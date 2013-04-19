//=============================================================================
// heightcolor.fx by Frank Luna (C) 2004 All Rights Reserved.
//
// Animates vertices in a wave motion and generates vertex colors 
// based on their height.
//=============================================================================

uniform extern float4x4 gWVP;
uniform extern float gTime;
uniform extern float4x4 gWorldInverseTranspose;
uniform extern float4x4 gWorld;

uniform extern float4 gAmbientMtrl;
uniform extern float4 gAmbientLight;
uniform extern float4 gDiffuseMtrl;
uniform extern float4 gDiffuseLight;
uniform extern float4 gSpecularMtrl;
uniform extern float4 gSpecularLight;
uniform extern float  gSpecularPower;
uniform extern float3 gLightVecW;
uniform extern float3 gEyePosW;

struct OutputVS
{
    float4 posH  : POSITION0;
    float4 color : COLOR0;
};
struct OutPhongVS
{
    float4 posH  : POSITION0;
   // float3 normalW : TEXCOORD0;
    float3 posW    : TEXCOORD1;
};
// Amplitudes
static float a[2] = {0.8f, 0.2f};
	
// Angular wave numbers.
static float k[2] = {1.0, 8.0f};
	
// Angular frequency.
static float w[2] = {1.0f, 8.0f};
	
// Phase shifts.
static float p[2] = {0.0f, 1.0f};

float SumOfRadialSineWaves(float x, float z)
{
	// Distance of vertex from source of waves (which we set
	// as the origin of the local space).
	float d = sqrt(x*x + z*z);
	
	// Sum the waves.
	float sum = 0.0f;
	for(int i = 0; i < 2; ++i)
		sum += a[i]*sin(k[i]*d - gTime*w[i] + p[i]);
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
			dhOverdx += (a[i]*k[i]*x*cos(k[i]*d - gTime*w[i] + p[i]))/d;
			dhOverdz += (a[i]*k[i]*z*cos(k[i]*d - gTime*w[i] + p[i]))/d;
		}
	}
}
float4 GetColorFromHeight(float y)
{
	if( abs(y) <= 0.2f ) // black
		return float4(0.0f, 0.0f, 0.0f, 1.0f);
	else if(abs(y) <= 0.5f ) // blue
		return float4(0.0f, 0.0f, 1.0f, 1.0f);
	else if(abs(y) <= 0.8f ) // green
		return float4(0.0f, 1.0f, 0.0f, 1.0f);
	else if(abs(y) <= 1.0f ) // red
		return float4(1.0f, 0.0f, 0.0f, 1.0f);
	else // yellow
		return float4(1.0f, 1.0f, 0.0f, 1.0f);
}

OutputVS ColorVS(float3 posL : POSITION0)
{
    // Zero out our output.
	OutputVS outVS = (OutputVS)0;
	
	// Get the height of the vertex--the height is given by
	// summing sine waves.
	posL.y = SumOfRadialSineWaves(posL.x, posL.z);
	
	// Generate the vertex color based on its height.
	outVS.color = GetColorFromHeight(posL.y);
	// Transform to homogeneous clip space.
	outVS.posH = mul(float4(posL, 1.0f), gWVP);
	 
	// Done--return the output.
    return outVS;
}

float4 ColorPS(float4 c : COLOR0 ) : COLOR
{
    return c;
}
OutPhongVS PhongVS(float3 posL : POSITION0)
{
	// Zero out our output.
	OutPhongVS outVS = (OutPhongVS)0;
	
	// Get the height of the vertex--the height is given by
	// summing sine waves.
	posL.y = SumOfRadialSineWaves(posL.x, posL.z);
	
	/*float dhOverDx,dhOverDz;
	Partials(posL.x, posL.z, dhOverDx, dhOverDz);
	float3 u = float3(1.0f, dhOverDx, 0.0f);
	float3 v = float3(0.0f, dhOverDz, 1.0f);
	outVS.normalW = normalize( cross(u,v) );*/

	outVS.posW = mul(float4(posL, 1.0f), gWorld).xyz;
	//outVS.posW=posL;
	// Transform to homogeneous clip space.
	outVS.posH = mul(float4(posL, 1.0f), gWVP);
	 
	// Done--return the output.
    return outVS;
}
float4 PhongPS(float3 normalW : TEXCOORD0,
				float3 posW : TEXCOORD1):COLOR
{
	float dhOverDx,dhOverDz;
	Partials(posW.x, posW.z, dhOverDx, dhOverDz);
	float3 u = float3(1.0f, dhOverDx, 0.0f);
	float3 v = float3(0.0f, dhOverDz, 1.0f);
	normalW = normalize( cross(u,v) );
	//normalW=normalize(normalW);
    // Compute the vector from the vertex to the eye position.
	float3 toEye = normalize(gEyePosW - posW);
	
	// Compute the reflection vector.
	float3 r = reflect(-gLightVecW, normalW);
	
	// Determine how much (if any) specular light makes it into the eye.
	float t  = pow(max(dot(r, toEye), 0.0f), gSpecularPower);
	
	// Determine the diffuse light intensity that strikes the vertex.
	float s = max(dot(gLightVecW, normalW), 0.0f);
	
	// Compute the ambient, diffuse and specular terms separatly. 
	float3 spec = t*(gSpecularMtrl*gSpecularLight).rgb;
	float3 diffuse = s*(gDiffuseMtrl*gDiffuseLight).rgb;
	float3 ambient = gAmbientMtrl*gAmbientLight;
	
    return float4(ambient + diffuse + spec, gDiffuseMtrl.a);
}

technique HeightColorTech
{
    pass P0
    {
        // Specify the vertex and pixel shader associated with this pass.
        vertexShader = compile vs_2_0 ColorVS();
        pixelShader  = compile ps_2_0 ColorPS();

		// Specify the render/device states associated with this pass.
		FillMode = Wireframe;
    }
	pass P1
	{
		VertexShader = compile vs_3_0 PhongVS();
		PixelShader  = compile ps_3_0 PhongPS();
	}
}

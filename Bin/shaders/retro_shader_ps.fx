#include "common.fx"

SamplerState SampleType;

#define DIFFUSE_MAP 0
#define NORMAL_MAP 1

Texture2D shaderTextures[2] : register( t1 );

float4 PShader(PixelInputType input) : SV_TARGET
{
	float4 Diffuse = shaderTextures[DIFFUSE_MAP].Sample(SampleType, input.tex) * input.color;
	
	#ifdef USE_NOISE
	float4 noise = myNoiseTexture.Sample(SampleType, input.tex); 
	#endif
	
	float3 AmbientColor = Diffuse.xyz * myAmbience;
	float3 DirectColor = float3(0, 0, 0);
	
	#ifdef USE_LIGHTS
	float3 Normal = normalize((shaderTextures[NORMAL_MAP].Sample(SampleType, input.tex).xyz * 2.0f) - 1.0f);
	float2 Resolution = myResolution.xy;
	for (unsigned int index = 0; index < myNumberOfLights; index++)
	{
		float Intensity = myLights[index].myPosition.z;
		float Falloff = myLights[index].myPosition.w;

		float2 difference = float2((myLights[index].myPosition.xy - input.position.xy) / Resolution.xy);
		difference.x *= (Resolution.x / Resolution.y);
		difference.y *= -1; 

		float distance = length(difference); 

		float linearAttenuation = saturate((Falloff - distance) / Falloff);
		float physicalAttenuation = 1.0f/(1.0f + distance);
		float totalAttenuation = linearAttenuation * physicalAttenuation;

		float3 direction = normalize(float3(difference.xy, (Falloff / 2)));

		float lambert = dot(direction, Normal); 

		DirectColor += Diffuse.xyz * Intensity * totalAttenuation * myLights[index].myLightColor.xyz * lambert;
		
	} 
	#endif
	
	float4 outcolor = float4(0, 0, 0, 1);
	float4 muls = float4(0, 0, 0, 1);
	
	float vertscolor1 = 0.75f; // 65
	float vertscolor2 = 0.65f; // 4
	float scanscolor = 0.75f;
	
	float contrast = -0.5f; // -3 <-> 20
	float br = -200.0f; // -200 <-> 200

	int pp = (unsigned int)input.position.x % 3;
	
	if (pp == 1)
	{
		muls.r = 1;
		muls.g = vertscolor1;
		muls.b = vertscolor2;
	}
	else if (pp == 2)
	{
		muls.r = vertscolor2;
		muls.g = 1;
		muls.b = vertscolor1;
	}
	else
	{
		muls.r = vertscolor1;
		muls.g = vertscolor2;
		muls.b = 1;
	}

	if ((unsigned int)input.position.y % 3 == 0) muls *= float4(scanscolor, scanscolor, scanscolor, 1);

	outcolor = input.color * muls;
	outcolor += (br / 255);
	outcolor = outcolor - contrast * (outcolor - 1.0) * outcolor * (outcolor - 0.5);
	
	AmbientColor.r = outcolor.r;
	AmbientColor.g = outcolor.g;
	AmbientColor.b = outcolor.b;
	return float4(AmbientColor, Diffuse.w);
}
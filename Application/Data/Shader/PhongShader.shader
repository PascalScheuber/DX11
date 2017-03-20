cbuffer S_VSConstantBuffer
{
	matrix World;
	matrix View;
	matrix Projection;
};

cbuffer S_PSConstantBuffer
{
	float3 ViewDirection;
	float  AmbientIntensity;
	float4 AmbientLightColor;
	float4 LightColor;
	float3 LightPosition;
	float  LightIntensity;
	float  LightRadius;
	float3 ByteFiller;
};

struct VS_INPUT
{
	float3 Position  : POSITION;
	float3 Normal    : NORMAL;
	float4 Color     : COLOR;
};

struct PS_INPUT
{
	float4 Position  : SV_POSITION;
	float3 Normal    : NORMAL;
	float4 Color     : COLOR;
	float3 WorldPosition  : TEXCOORD;
};

PS_INPUT VS_Main(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;

	output.Position = mul(float4(input.Position, 1), World);
	output.WorldPosition = output.Position.xyz;
	output.Position = mul(mul(output.Position, View), Projection);
	output.Normal = normalize(mul(input.Normal, (float3x3)World).xyz);

	output.Color = input.Color;

	return output;
}

float4 PS_Main(PS_INPUT input) : SV_TARGET
{
	//Calculate lightDirection
	float3 lightDirection = LightPosition - input.WorldPosition;

	//Calculate lightDistance
	float lightDistance = length(lightDirection);

	//Normalize lightDirection
	lightDirection = normalize(lightDirection);

	//Calculate lightReflection
	float3 lightReflection = reflect(lightDirection, input.Normal);

	//Calculate lightAmount
	float lightAmount = dot(lightDirection, input.Normal);

	//Calculate attenuation
	float attenuation = saturate(lightDistance / LightRadius);
	attenuation = 1 / (1 + attenuation) * saturate(LightIntensity * (1 - attenuation));

	//Add AmbientLight
	float4 result = float4(input.Color.rgb * AmbientLightColor.rgb * AmbientIntensity, input.Color.a);

	//Add Falloff
	result.xyz += lightAmount * (lerp(input.Color.rgb, LightColor.rgb, attenuation * 0.5)) * attenuation;

	//Add Specular Point
	result = float4(result.rgb + (LightColor.rgb * LightIntensity) * pow(saturate(dot(lightReflection, normalize(ViewDirection))), 15), result.a) * attenuation;
	
	return saturate(result);
}
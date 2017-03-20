// ----------------------------------------------------------------------------
// STRUCTURES
// ----------------------------------------------------------------------------
struct VS_DATA
{
	float3 Position  : POSITION;
	float3 Normal    : NORMAL;
	float4 Color	 : COLOR;
};

struct PS_DATA
{
	float4 Position  : SV_POSITION;
	float3 Normal    : NORMAL;
	float4 Color	 : COLOR;
};


// ----------------------------------------------------------------------------
// VERTEX SHADER
// ----------------------------------------------------------------------------
PS_DATA VS_Main(VS_DATA input)
{
	PS_DATA output = (PS_DATA)0;
	
	output.Position = float4(input.Position, 1.0f);
	output.Normal = input.Normal;
	output.Color = input.Color;

	return output;
}


// ----------------------------------------------------------------------------
// PIXEL SHADER
// ----------------------------------------------------------------------------
float4 PS_Main(PS_DATA input) : SV_TARGET
{
	return input.Color;
}

technique10 Main
{
	pass p0
	{
		SetRasterizerState(RasterSetting);
		SetVertexShader(CompileShader(vs_5_0, VS_Main()));
		SetGeometryShader(NULL);
		SetHullShader(NULL);
		SetDomainShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PS_Main()));
	}
}
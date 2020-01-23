#include "Common.hlsl"

Texture2D DepthTex : register(t0);
Texture2D GeoNormalTex : register(t1);
Texture2D InGIResultSHTex : register(t2);
Texture2D InGIResultColorTex : register(t3);



RWTexture2D<float4> OutGIResultSH : register(u0);
RWTexture2D<float4> OutGIResultColor: register(u1);



cbuffer SpatialFilterConstant : register(b0)
{
	float4 ProjectionParams;
    uint Iteration;
    uint GIBufferScale;
    float IndirectDiffuseWeightFactorDepth;
    float IndirectDiffuseWeightFactorNormal;
};

static const float wavelet_factor = 0.5;
static const float wavelet_kernel[2][2] = {
	{ 1.0, wavelet_factor  },
	{ wavelet_factor, wavelet_factor * wavelet_factor }
};

void DeFlicker(Texture2D GIResultSHTex, Texture2D GIResultColorTex, uint2 Pos, inout SH result )
{
	int StepSize =  int(1u << (Iteration - 1));

	float2 CenterPos = Pos;

	SH CenterSH = init_SH();
	CenterSH.shY = GIResultSHTex[CenterPos];
	CenterSH.CoCg = GIResultColorTex[CenterPos].xy;

	float3 SumColor = float3(0, 0, 0);
	float SumW = 0;

	SH SumSH = init_SH();

	
	const int r = 1;

	for(int yy = -r; yy <= r; yy++) 
	{
		for(int xx = -r; xx <= r; xx++) 
		{
			if(xx == 0 && yy == 0)
				continue;

			float2 SamplePos = CenterPos + float2(xx, yy) * StepSize;

			SumSH.shY += GIResultSHTex[SamplePos];
			SumSH.CoCg += GIResultColorTex[SamplePos].xy;
		}
	}

	const float num_pixels = pow(r * 2 + 1, 2) - 1;

	float max_lum = SumSH.shY.w * 1.0 / num_pixels;
	if(CenterSH.shY.w > max_lum)
	{
		float ratio = max_lum / CenterSH.shY.w;
		CenterSH.shY *= ratio;
		CenterSH.CoCg *= ratio;
	}

	result = CenterSH;

}

void Filter(Texture2D GIResultSHTex,Texture2D GIResultColorTex, uint2 Pos, inout SH result )
{
	int StepSize =  int(1u << (Iteration - 1));

	float2 CenterPos = Pos;

	float CenterDepth = DepthTex[CenterPos.xy];
	float CenterZ = GetLinearDepthOpenGL(CenterDepth, ProjectionParams.x, ProjectionParams.y) ;

	float3 CenterNormal = GeoNormalTex[CenterPos.xy];

	const int r = 1;
	float3 SumColor = float3(0, 0, 0);
	float SumW = 0;

	SH SumSH = init_SH();

	for(int yy = -r; yy <= r; yy++) 
	{
		for(int xx = -r; xx <= r; xx++) 
		{
			if(xx == 0 && yy == 0)
				continue;
			float2 SamplePos = CenterPos + float2(xx, yy) * StepSize;

			SH SampleSH;
			SampleSH.shY = GIResultSHTex[SamplePos];
			SampleSH.CoCg = GIResultColorTex[SamplePos].xy;

			float W = 1;

			float3 SampleDepth = DepthTex[SamplePos.xy];
			float SampleZ = GetLinearDepthOpenGL(SampleDepth, ProjectionParams.x, ProjectionParams.y) ;

			float DistZ = abs(CenterZ - SampleZ) * IndirectDiffuseWeightFactorDepth;
			W *= exp(-DistZ/StepSize) ;
			float3 Normal = GeoNormalTex[SamplePos.xy];
			W *= wavelet_kernel[abs(xx)][abs(yy)];

			float GNdotGN = max(0.0, dot(CenterNormal, Normal));
			W *= pow(GNdotGN, IndirectDiffuseWeightFactorNormal);

			SumW += W;
			accumulate_SH(SumSH, SampleSH, W);
		}
	}

    scale_SH(SumSH, 1.0/SumW);

    result = SumSH;
}

[numthreads(32, 32, 1)]
void SpatialFilter( uint3 DTid : SV_DispatchThreadID )
{
    SH ResultSH;
    if(Iteration == 0)
		DeFlicker(InGIResultSHTex, InGIResultColorTex, DTid.xy, ResultSH);
	else
		Filter(InGIResultSHTex, InGIResultColorTex, DTid.xy, ResultSH);


    OutGIResultSH[DTid.xy] = ResultSH.shY;
    OutGIResultColor[DTid.xy] = float4(ResultSH.CoCg, 0, 0);

    // OutGIResultSH[DTid.xy] = InGIResultSHTex[DTid.xy];
    // OutGIResultColor[DTid.xy] = InGIResultColorTex[DTid.xy];
}
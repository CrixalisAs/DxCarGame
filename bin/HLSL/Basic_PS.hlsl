#include "Basic.hlsli"

// ������ɫ��
float4 PS(VertexPosHWNormalTex pIn) : SV_Target
{
	// ��׼��������
	pIn.NormalW = normalize(pIn.NormalW);

	// ����ָ���۾�������
	float3 toEyeW = normalize(gEyePosW - pIn.PosW);

	// ��ʼ��Ϊ0 
	float4 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 spec = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 A = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 D = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 S = float4(0.0f, 0.0f, 0.0f, 0.0f);
	int i;

	[unroll]
	for (i = 0; i < 5; ++i)
	{
		ComputeDirectionalLight(gMaterial, gDirLight[i], pIn.NormalW, toEyeW, A, D, S);
		ambient += A;
		diffuse += D;
		spec += S;
	}
	
	[unroll]
	for (i = 0; i < 5; ++i)
	{
		ComputePointLight(gMaterial, gPointLight[i], pIn.PosW, pIn.NormalW, toEyeW, A, D, S);
		ambient += A;
		diffuse += D;
		spec += S;
	}
	
	[unroll]
	for (i = 0; i < 5; ++i)
	{
		ComputeSpotLight(gMaterial, gSpotLight[i], pIn.PosW, pIn.NormalW, toEyeW, A, D, S);
		ambient += A;
		diffuse += D;
		spec += S;
	}

	float4 texColor = gDiffuseMap.Sample(gSam, float3(pIn.Tex, gTexIndex));
	float4 litColor = texColor * (ambient + diffuse) + spec;
	litColor.a = texColor.a * gMaterial.Diffuse.a;

	return litColor;
}
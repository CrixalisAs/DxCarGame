#include "LightHelper.hlsli"

Texture2DArray gDiffuseMap : register(t0);
TextureCube gTexCube : register(t1);
SamplerState gSam : register(s0);

cbuffer CBChangesEveryInstanceDrawing : register(b0)
{
	matrix gWorld;
	matrix gWorldInvTranspose;
}

cbuffer CBChangesEveryObjectDrawing : register(b1)
{
	Material gMaterial;
}

cbuffer CBDrawingStates : register(b2)
{
	int gTextureUsed;
	int gReflectionEnabled;
	float2 gPad;
}

cbuffer CBChangesEveryFrame : register(b3)
{
	matrix gView;
	float3 gEyePosW;
	float gPad2;
}

cbuffer CBChangesOnResize : register(b4)
{
	matrix gProj;
}

cbuffer CBChangesRarely : register(b5)
{
	DirectionalLight gDirLight[5];
	PointLight gPointLight[5];
	SpotLight gSpotLight[5];
}

cbuffer CBChangesEveryDrawing : register(b6)
{
	int gTexIndex;
	float3 gPad3;
}

struct VertexPosNormalTex
{
	float3 PosL : POSITION;
	float3 NormalL : NORMAL;
	float2 Tex : TEXCOORD;
};

struct VertexPosHWNormalTex
{
	float4 PosH : SV_POSITION;
	float3 PosW : POSITION;     // �������е�λ��
	float3 NormalW : NORMAL;    // �������������еķ���
	float2 Tex : TEXCOORD;
};

struct InstancePosNormalTex
{
	float3 PosL : POSITION;
	float3 NormalL : NORMAL;
	float2 Tex : TEXCOORD;
	matrix World : World;
	matrix WorldInvTranspose : WorldInvTranspose;
};




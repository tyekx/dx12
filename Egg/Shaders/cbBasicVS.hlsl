#include "RootSignatures.hlsli"

struct IAOutput {
	float3 position : POSITION;
	float3 normal : NORMAL;
	float2 texCoord : TEXCOORD;
};

struct VSOutput {
	float4 position : SV_Position;
	float3 color : COLOR;
};

cbuffer PerObjectCb2 : register(b0) {
	float4x4 modelMat;
}

[RootSignature(RootSig1)]
VSOutput main(IAOutput iao) {
	VSOutput vso;
	vso.position = mul(modelMat, float4(iao.position, 1.0f));
	vso.color = float3(iao.texCoord, 0.0f);
	return vso;
}

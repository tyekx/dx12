#include "RootSignatures.hlsli"

struct VSOutput
{
    float4 position : SV_Position;
    float3 normal : NORMAL;
    float2 texCoord : TEXCOORD;
    float3 lightDirTS : TEXCOORD1;
    float3 viewDirTS : TEXCOORD2;
};

Texture2D diffuseTex : register(t0);
Texture2D normalTex : register(t1);
Texture2D bumpTex : register(t1);

SamplerState sampl : register(s0);

[RootSignature(RootSig3)]
float4 main(VSOutput vso) : SV_Target
{

    float3 n = normalTex.Sample(sampl, vso.texCoord).xyz - float3(0.5, 0.5, 0.5);
    float3 l = normalize(vso.lightDirTS);
    float3 v = normalize(vso.viewDirTS);
    float3 h = normalize(l + v);

    float dw = saturate(dot(n, l));
    dw = dw * 0.95 + 0.05;

    return diffuseTex.Sample(sampl, vso.texCoord) * dw;
}

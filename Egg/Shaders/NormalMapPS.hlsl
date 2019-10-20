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
Texture2D bumpTex : register(t2);

SamplerState sampl : register(s0);

cbuffer PerFrameCb : register(b1)
{
    float4x4 viewProj;
    float4 lightPos;
    float4 eyePos;
    float4 lightIntensity;
}

[RootSignature(NormalMapRS)]
float4 main(VSOutput vso) : SV_Target
{

    float3 n = normalize(normalTex.Sample(sampl, vso.texCoord).xyz - 0.5f);
    float3 l = normalize(vso.lightDirTS);
    float3 v = normalize(vso.viewDirTS);
    float3 h = normalize(l + v);

    float ndotl = saturate(dot(n, l));
    float ndoth = saturate(dot(n, h));
    ndoth = pow(ndoth, 80);

    float3 kd = diffuseTex.Sample(sampl, vso.texCoord).xyz;
    
    return float4(kd * ndotl + ndoth, 1);
}

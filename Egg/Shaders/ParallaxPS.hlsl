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

static const float HEIGHT_SCALE = 0.05f;
static const float HEIGHT_BIAS = 0.0f;

[RootSignature(RootSig3)]
float4 main(VSOutput vso) : SV_Target
{
    float3 l = normalize(vso.lightDirTS);
    float3 v = normalize(vso.viewDirTS);

    float height = bumpTex.Sample(sampl, vso.texCoord) * HEIGHT_SCALE + HEIGHT_BIAS;
    float2 tex = vso.texCoord + height * (v.xy / v.z);

    float3 n = normalTex.Sample(sampl, tex).xyz - float3(0.5, 0.5, 0.5);
    float3 h = normalize(l + v);

    float ndotl = saturate(dot(n, l));
    float ndoth = saturate(dot(n, h));
    ndoth = pow(ndoth, 3);

    float3 kd = diffuseTex.Sample(sampl, tex).xyz;
    
    return float4(kd * ndotl + ndoth, 1);
}

#include "RootSignatures.hlsli"

struct IAOutput
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    float2 texCoord : TEXCOORD;
    float3 tangent : TANGENT;
    float3 binormal : BINORMAL;
};

struct VSOutput
{
    float4 position : SV_Position;
    float3 normal : NORMAL;
    float2 texCoord : TEXCOORD;
    float3 lightDirTS : TEXCOORD1;
    float3 viewDirTS : TEXCOORD2;
};

cbuffer PerObjectCb : register(b0)
{
    float4x4 modelMat;
    float4x4 invModelMat;
}

cbuffer PerFrameCb : register(b1)
{
    float4x4 viewProj;
    float4 lightPos;
    float4 eyePos;
    float4 lightIntensity;
}

[RootSignature(RootSig3)]
VSOutput main(IAOutput iao)
{
    VSOutput vso;
    vso.position = mul(modelMat, float4(iao.position, 1.0f));

    vso.normal = normalize(mul(float4(iao.normal, 0.0f), invModelMat).xyz);
    vso.texCoord = iao.texCoord;

    float3 n = vso.normal;
    float3 t = normalize(mul(modelMat, float4(iao.tangent, 0)).xyz);
    float3 b = normalize(mul(modelMat, float4(iao.binormal, 0)).xyz);

    float3 pos = vso.position.xyz / vso.position.w;

    vso.lightDirTS = normalize(lightPos.xyz - pos * lightPos.w);
    vso.viewDirTS = normalize(eyePos.xyz - pos);

    float3x3 tbn = { t, b, n };
    vso.lightDirTS = mul(tbn, vso.lightDirTS);
    vso.viewDirTS = mul(tbn, vso.viewDirTS);

    vso.position = mul(viewProj, vso.position);

    return vso;
}

struct IAOutput {
	float3 position : POSITION;
	float3 color : COLOR;
};

struct VSOutput {
	float4 position : SV_Position;
	float3 color : COLOR;
};

VSOutput main(IAOutput iao) {
	VSOutput vso;
	vso.position = float4(iao.position, 1.0f);
	vso.color = iao.color;
	return vso;
}

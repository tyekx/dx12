#pragma once

#include <Egg/Common.h>
#include <Egg/Mesh/Shaded.h>
#include <Egg/Mesh/Prefabs.h>
#include <Egg/ConstantBuffer.hpp>
#include "ConstantBufferTypes.h"

class Box {
public:
	Egg::Mesh::Shaded::P shadedMesh;
	//PerObjectCb cb;
	//com_ptr<ID3D12Resource> constantBuffer;
	//UINT8 * mappedPtr;

	Egg::ConstantBuffer<PerObjectCb> cb;

	Float4x4 translation;
	Float4x4 rotation;
	Float4x4 scale;

	Float3 speed;
	Float3 gravity;
	Float3 position;

	bool leftGround;

	Box() {
		gravity = Float3{ 0.0f, -0.931f, 0.0f };
		speed = Float3::Random();
		speed.x = speed.z = 0.0f;
		leftGround = true;
	}

	void Update(double dt, double T) {
		speed -= gravity * (float)dt;
		position -= speed * (float)dt;
		if(position.y <= -1.0f && leftGround) {
			speed = -speed;
			leftGround = false;
		}

		if(position.y > -1.0f && !leftGround) {
			leftGround = true;
		}

		translation = Float4x4::Translation(position);

		cb->modelTransform = scale * rotation * translation;
		cb.Upload();
	}
	//memcpy(mappedPtr, &cb, sizeof(PerObjectCb));
	//commandList->SetGraphicsRootConstantBufferView(0, constantBuffer->GetGPUVirtualAddress());

	void Draw(ID3D12GraphicsCommandList * commandList) {
		shadedMesh->SetPipelineState(commandList);
		shadedMesh->BindConstantBuffer(commandList, cb);
		shadedMesh->Draw(commandList);
	}

	void CreateResources(ID3D12Device * device) {
		cb.CreateResources(device);/*

		DX_API("Failed to create constant buffer resource")
			device->CreateCommittedResource(
				&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
				D3D12_HEAP_FLAG_NONE,
				&CD3DX12_RESOURCE_DESC::Buffer(Egg::Utility::Align256(sizeof(PerObjectCb))),
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(constantBuffer.GetAddressOf())
			);

		CD3DX12_RANGE range{ 0,0 };
		DX_API("Failed to map constant buffer resource")
			constantBuffer->Map(0, &range, reinterpret_cast<void**>(&mappedPtr));*/
	}

};

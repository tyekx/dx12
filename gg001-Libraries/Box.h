#pragma once

#include <Egg/Common.h>
#include <Egg/Mesh/Shaded.h>
#include <Egg/Mesh/Prefabs.h>
#include <Egg/ConstantBuffer.hpp>
#include "ConstantBufferTypes.h"

class Box {
public:
	Egg::Mesh::Shaded::P shadedMesh;

	Egg::ConstantBuffer<PerObjectCb> cb;

	Float4x4 translation;
	Float4x4 rotation;
	Float4x4 scale;

	Float3 speed;
	Float3 gravity;
	Float3 position;

	Box() {
		gravity = Float3{ 0.0f, -0.931f, 0.0f };
		speed = Float3::Random();
		speed.xz = 0.0f;
	}

	void Update(float dt, float T) {
		speed -= gravity * dt;
		position -= speed * dt;
		if(position.y < -1.0f) {
			speed = -speed;
			position.y = -1.0f;
		}

		translation = Float4x4::Translation(position);

		cb->modelTransform = scale * rotation * translation;
		cb.Upload();
	}

	void Draw(ID3D12GraphicsCommandList * commandList) {
		shadedMesh->SetPipelineState(commandList);
		shadedMesh->BindConstantBuffer(commandList, cb);
		shadedMesh->Draw(commandList);
	}

	void CreateResources(ID3D12Device * device) {
		cb.CreateResources(device);
	}

};

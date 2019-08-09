#pragma once

#include <Egg/Common.h>
#include <Egg/Mesh/Shaded.h>
#include <Egg/Mesh/Prefabs.h>
#include <Egg/ConstantBuffer.hpp>
#include "ConstantBufferTypes.h"

GG_CLASS(Box) 
public:
	Egg::Mesh::Shaded::P shadedMesh;

	Box(Egg::Mesh::Shaded::P shadedm) : shadedMesh{ shadedm } {

	}

	void Update(float dt, float T) {
		// dt: delta Time, time since last frame, T: total time
	}

	void Draw(ID3D12GraphicsCommandList * commandList) {
		shadedMesh->SetPipelineState(commandList);
		// bind the constant buffer here
		shadedMesh->Draw(commandList);
	}

	void CreateResources(ID3D12Device * device) {
		// create cb resources here
	}

GG_ENDCLASS

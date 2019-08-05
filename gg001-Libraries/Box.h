#pragma once

#include <Egg/Common.h>
#include "ConstantBufferTypes.h"
#include <Egg/ConstantBuffer.hpp>
#include <Egg/Mesh/Shaded.h>
#include <Egg/Shader.h>
#include <Egg/Mesh/Prefabs.h>

class Box {
public:
	Egg::Mesh::Shaded::P shadedBox;
	ConstantBuffer<PerObjectCb> cb;
	Float4x4 translation;
	Float4x4 rotation;
	Float4x4 scale;
	float speed;


	void Update(double T) {
		rotation = Float4x4::Rotation(Float3{ 1.0f, 1.0f, 1.0f }, ((float)T) * speed);
		cb->modelTransform = scale * rotation * translation;
		cb.Upload();
	}

	void Draw(ID3D12GraphicsCommandList * commandList) {
		shadedBox->SetPipelineState(commandList);
		shadedBox->BindConstantBuffer(commandList, cb);
		shadedBox->Draw(commandList);
	}

	void CreateResources(ID3D12Device * device, Egg::PsoManager * psoManager) {
		cb.CreateResources(device);

		// Vertex / Pixel Shaders

		com_ptr<ID3DBlob> vertexShader = Egg::Shader::LoadCso("Shaders/cbBasicVS.cso");
		com_ptr<ID3DBlob> pixelShader = Egg::Shader::LoadCso("Shaders/DefaultPS.cso");
		com_ptr<ID3D12RootSignature> rootSig = Egg::Shader::LoadRootSignature(device, vertexShader.Get());


		Egg::Mesh::Material::P material = Egg::Mesh::Material::Create();
		material->SetRootSignature(rootSig);
		material->SetVertexShader(vertexShader);
		material->SetPixelShader(pixelShader);

		Egg::Mesh::Geometry::P geometry = Egg::Mesh::Prefabs::UnitBox(device);

		shadedBox = Egg::Mesh::Shaded::Create(psoManager, material, geometry);
	}

};

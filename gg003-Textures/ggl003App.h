#pragma once

#include <Egg/SimpleApp.h>
#include <Egg/Importer.h>
#include <Egg/Math/Math.h>
#include <Egg/ConstantBuffer.hpp>

#include "ConstantBufferTypes.h"

using namespace Egg::Math;

class ggl003App : public Egg::SimpleApp {
protected:
	Egg::Mesh::Shaded::P shadedMesh;
	Float4x4 rotation;
	Egg::ConstantBuffer<PerObjectCb> cb;
public:
	virtual void Update(float dt, float T) override {
		rotation *= Float4x4::Rotation(Float3::UnitY, dt);
		cb->modelTransform = Float4x4::Translation(Float3{ 0.0f, 0.0f, -0.5f }) * rotation * Float4x4::Translation(Float3{ 0.0f, 0.0f, 0.5f });
		cb.Upload();
	}

	virtual void PopulateCommandList() {
		commandAllocator->Reset();
		commandList->Reset(commandAllocator.Get(), nullptr);

		commandList->RSSetViewports(1, &viewPort);
		commandList->RSSetScissorRects(1, &scissorRect);

		commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(renderTargets[frameIndex].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

		CD3DX12_CPU_DESCRIPTOR_HANDLE rHandle(rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), frameIndex, rtvDescriptorHandleIncrementSize);
		CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHandle(dsvHeap->GetCPUDescriptorHandleForHeapStart());
		commandList->OMSetRenderTargets(1, &rHandle, FALSE, &dsvHandle);

		const float clearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
		commandList->ClearRenderTargetView(rHandle, clearColor, 0, nullptr);
		commandList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

		shadedMesh->SetPipelineState(commandList.Get());
		shadedMesh->BindConstantBuffer(commandList.Get(), cb);
		shadedMesh->Draw(commandList.Get());

		commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(renderTargets[frameIndex].Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

		DX_API("Failed to close command list")
			commandList->Close();
	}


	virtual void LoadAssets() override {
		cb.CreateResources(device.Get());

		com_ptr<ID3DBlob> vertexShader = Egg::Shader::LoadCso("Shaders/cbBasicVS.cso");
		com_ptr<ID3DBlob> pixelShader = Egg::Shader::LoadCso("Shaders/DefaultPS.cso");
		com_ptr<ID3D12RootSignature> rootSig = Egg::Shader::LoadRootSignature(device.Get(), vertexShader.Get());

		Egg::Mesh::Material::P material = Egg::Mesh::Material::Create();
		material->SetRootSignature(rootSig);
		material->SetVertexShader(vertexShader);
		material->SetPixelShader(pixelShader);
		material->SetDepthStencilState(CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT));
		material->SetDSVFormat(DXGI_FORMAT_D32_FLOAT);

		Egg::Mesh::Geometry::P geometry = Egg::Importer::ImportSimpleObj(device.Get(), "C:/work/dx12/Media/giraffe.obj");

		shadedMesh = Egg::Mesh::Shaded::Create(psoManager.get(), material, geometry);
	}

};



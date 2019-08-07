#pragma once

#include "Box.h"
#include <Egg/SimpleApp.h>


class ggl001App : public Egg::SimpleApp {
protected:
	Box boxes[8];
public:
	virtual void Update(double T, double dt) override {
		for(int i = 0; i < 8; ++i) {
			boxes[i].Update(dt, T);
			//boxes[i].cb->modelTransform *= Float4x4::Proj(1.5f, aspectRatio, 0.0f, 1.0f);
			//boxes[i].cb.Upload();
		}
	}

	virtual void PopulateCommandList() {
		commandAllocator->Reset();
		commandList->Reset(commandAllocator.Get(), nullptr);

		commandList->RSSetViewports(1, &viewPort);
		commandList->RSSetScissorRects(1, &scissorRect);

		commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(renderTargets[frameIndex].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

		CD3DX12_CPU_DESCRIPTOR_HANDLE rHandle(rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), frameIndex, rtvDescriptorHandleIncrementSize);
		commandList->OMSetRenderTargets(1, &rHandle, FALSE, nullptr);

		const float clearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
		commandList->ClearRenderTargetView(rHandle, clearColor, 0, nullptr);

		for(int i = 0; i < 8; ++i) {
			boxes[i].Draw(commandList.Get());
		}

		commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(renderTargets[frameIndex].Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

		DX_API("Failed to close command list")
			commandList->Close();
	}

	virtual void LoadAssets() override {
		com_ptr<ID3DBlob> vertexShader = Egg::Shader::LoadCso("Shaders/cbBasicVS.cso");
		com_ptr<ID3DBlob> pixelShader = Egg::Shader::LoadCso("Shaders/DefaultPS.cso");
		com_ptr<ID3D12RootSignature> rootSig = Egg::Shader::LoadRootSignature(device.Get(), vertexShader.Get());

		Egg::Mesh::Material::P material = Egg::Mesh::Material::Create();
		material->SetRootSignature(rootSig);
		material->SetVertexShader(vertexShader);
		material->SetPixelShader(pixelShader);

		Egg::Mesh::Geometry::P geometry = Egg::Mesh::Prefabs::UnitBox(device.Get());

		Egg::Mesh::Shaded::P shadedBox = Egg::Mesh::Shaded::Create(psoManager.get(), material, geometry);

		for(int i = 0; i < 8; ++i) {
			boxes[i].shadedMesh = shadedBox;
			boxes[i].CreateResources(device.Get());
			boxes[i].scale = Float4x4::Scaling(Float3{ 0.2f, 0.2f, 0.2f });
			boxes[i].position = Float3{ i * 0.3f - 0.85f, 0.85f, 0.5f };
		}
	}

};



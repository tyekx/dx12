#pragma once

#include <Egg/SimpleApp.h>
#include <Egg/Mesh/Importer.h>

class ggl002App : public Egg::SimpleApp {
protected:
	Egg::Mesh::Shaded::P shadedMesh;
public:
	virtual void Update(float dt, float T) override {

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

		shadedMesh->SetPipelineState(commandList.Get());
		shadedMesh->Draw(commandList.Get());

		commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(renderTargets[frameIndex].Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

		DX_API("Failed to close command list")
			commandList->Close();
	}

	virtual void LoadAssets() override {
		com_ptr<ID3DBlob> vertexShader = Egg::Shader::LoadCso("Shaders/DefaultVS.cso");
		com_ptr<ID3DBlob> pixelShader = Egg::Shader::LoadCso("Shaders/DefaultPS.cso");
		com_ptr<ID3D12RootSignature> rootSig = Egg::Shader::LoadRootSignature(device.Get(), vertexShader.Get());

		Egg::Mesh::Material::P material = Egg::Mesh::Material::Create();
		material->SetRootSignature(rootSig);
		material->SetVertexShader(vertexShader);
		material->SetPixelShader(pixelShader);

		Egg::Mesh::Geometry::P geometry = Egg::Mesh::Importer::ImportSimpleObj(device.Get(), "C:/work/dx12/Media/giraffe.obj");

		shadedMesh = Egg::Mesh::Shaded::Create(psoManager.get(), material, geometry);
	}

};



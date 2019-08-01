#pragma once

#include <Egg/App.h>
#include <Egg/Shader.h>
#include <Egg/PsoManager.h>
#include <memory>
#include <Egg/Mesh/Shaded.h>

using namespace Egg;

class HelloTriangleApp : public App {
protected:
	com_ptr<ID3D12CommandAllocator> commandAllocator;
	com_ptr<ID3D12GraphicsCommandList> commandList;

	Egg::Mesh::Shaded::P shadedTriangle;

	std::unique_ptr<PsoManager> psoManager;

	void PopulateCommandList() {
		commandAllocator->Reset();
		commandList->Reset(commandAllocator.Get(), nullptr);

		commandList->RSSetViewports(1, &viewPort);
		commandList->RSSetScissorRects(1, &scissorRect);

		commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(renderTargets[frameIndex].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

		CD3DX12_CPU_DESCRIPTOR_HANDLE rHandle(rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), frameIndex, rtvDescriptorHandleIncrementSize);
		commandList->OMSetRenderTargets(1, &rHandle, FALSE, nullptr);

		const float clearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
		commandList->ClearRenderTargetView(rHandle, clearColor, 0, nullptr);

		shadedTriangle->SetPipelineState(commandList.Get());
		shadedTriangle->Draw(commandList.Get());

		commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(renderTargets[frameIndex].Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

		DX_API("Failed to close command list")
			commandList->Close();
	}

	void WaitForPreviousFrame() {
		const UINT64 fv = fenceValue;
		DX_API("Failed to signal from command queue")
			commandQueue->Signal(fence.Get(), fv);

		fenceValue++;

		if(fence->GetCompletedValue() < fv) {
			DX_API("Failed to sign up for event completion")
				fence->SetEventOnCompletion(fv, fenceEvent);
			WaitForSingleObject(fenceEvent, INFINITE);
		}

		frameIndex = swapChain->GetCurrentBackBufferIndex();
	}


public:
	virtual void Update(double T, double dt) override {

	}

	virtual void Render() override {
		PopulateCommandList();

		// Execute
		ID3D12CommandList * cLists[] = { commandList.Get() };
		commandQueue->ExecuteCommandLists(_countof(cLists), cLists);

		DX_API("Failed to present swap chain")
			swapChain->Present(1, 0);

		// Sync
		WaitForPreviousFrame();
	}

	virtual void LoadAssets() override {
		App::LoadAssets();

		struct Vertex {
			float pos[3];
			float color[3];
		};

		Vertex triangleVertices[] = {
			{ {  0.0f   ,  1.0f   , 0.5f }, { 1.0f, 0.0f, 0.0f } },
			{ {  0.866025f , -0.5f , 0.5f }, { 0.0f, 1.0f, 0.0f } },
			{ { -0.866025f , -0.5f , 0.5f }, { 0.0f, 0.0f, 1.0f } }
		};

		com_ptr<ID3DBlob> vertexShader = Shader::LoadCso("Shaders/DefaultVS.cso");
		com_ptr<ID3DBlob> pixelShader = Shader::LoadCso("Shaders/DefaultPS.cso");
		com_ptr<ID3D12RootSignature> rootSignature = Shader::LoadRootSignature(device.Get(), vertexShader.Get());

		Egg::Mesh::Geometry::P geometry = Egg::Mesh::VertexStreamGeometry::Create(device.Get(), reinterpret_cast<void*>(triangleVertices), sizeof(triangleVertices), sizeof(Vertex));
		geometry->AddInputElement({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });
		geometry->AddInputElement({ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });
		
		Egg::Mesh::Material::P material = Egg::Mesh::Material::Create();
		material->SetRootSignature(rootSignature);
		material->SetVertexShader(vertexShader);
		material->SetPixelShader(pixelShader);

		shadedTriangle = Egg::Mesh::Shaded::Create(psoManager.get(), material, geometry);
	}

	virtual void CreateResources() override {
		App::CreateResources();
		psoManager.reset(new PsoManager{ device });

		// Create Command Allocator
		DX_API("Failed to create command allocator")
			device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(commandAllocator.GetAddressOf()));

		// Create Graphics Command List, set the newly created GPSO as its initial state
		DX_API("Failed to greate graphics command list")
			device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator.Get(), nullptr, IID_PPV_ARGS(commandList.GetAddressOf()));

		commandList->Close();

		WaitForPreviousFrame();
	}

	virtual void ReleaseAssets() override {
		App::ReleaseAssets();
	}

	virtual void ReleaseResources() override {
		psoManager.reset(nullptr);
		commandList.Reset();
		shadedTriangle.reset();
		fence.Reset();
		commandAllocator.Reset();
		App::ReleaseResources();
	}

	virtual void Resize(int width, int height) override {
		WaitForPreviousFrame();
		App::Resize(width, height);
	}


	virtual void Destroy() override {
		WaitForPreviousFrame();
		App::Destroy();
	}
};

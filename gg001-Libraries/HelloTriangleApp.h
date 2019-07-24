#pragma once

#include <Egg/App.h>
#include <Egg/Shader.h>
#include <Egg/PSOManager.h>
#include <memory>

using namespace Egg;

class HelloTriangleApp : public App {
protected:
	com_ptr<ID3D12RootSignature> rootSignature;
	com_ptr<ID3D12CommandAllocator> commandAllocator;

	// Graphics Pipeline State Object
	com_ptr<ID3D12PipelineState> gpso;
	com_ptr<ID3D12GraphicsCommandList> commandList;

	// Asset Data
	com_ptr<ID3D12Resource> vertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView;

	std::unique_ptr<PSOManager> psoManager;


	void PopulateCommandList() {
		commandAllocator->Reset();
		commandList->Reset(commandAllocator.Get(), gpso.Get());

		commandList->SetGraphicsRootSignature(rootSignature.Get());
		commandList->RSSetViewports(1, &viewPort);
		commandList->RSSetScissorRects(1, &scissorRect);

		commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(renderTargets[frameIndex].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

		CD3DX12_CPU_DESCRIPTOR_HANDLE rHandle(rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), frameIndex, rtvDescriptorHandleIncrementSize);
		commandList->OMSetRenderTargets(1, &rHandle, FALSE, nullptr);

		const float clearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
		commandList->ClearRenderTargetView(rHandle, clearColor, 0, nullptr);

		commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		commandList->IASetVertexBuffers(0, 1, &vertexBufferView);
		commandList->DrawInstanced(3, 1, 0, 0);

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
			{ {  0.0f   ,  0.85f  , 0.0f }, { 1.0f, 0.0f, 0.0f } },
			{ {  0.7071f, -0.8571f, 0.0f }, { 0.0f, 1.0f, 0.0f } },
			{ { -0.7071f, -0.8571f, 0.0f }, { 0.0f, 0.0f, 1.0f } }
		};

		unsigned int vertexBufferSize = sizeof(triangleVertices);

		DX_API("Failed to create commited resource")
			device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
											D3D12_HEAP_FLAG_NONE,
											&CD3DX12_RESOURCE_DESC::Buffer(vertexBufferSize),
											D3D12_RESOURCE_STATE_GENERIC_READ,
											nullptr,
											IID_PPV_ARGS(vertexBuffer.GetAddressOf()));

		vertexBuffer->SetName(L"Vertex Buffer");

		UINT8 * vertexDataBegin;
		CD3DX12_RANGE readRange(0, 0); // CPU read is not mapped
		vertexBuffer->Map(0, &readRange, reinterpret_cast<void**>(&vertexDataBegin));
		memcpy(vertexDataBegin, triangleVertices, vertexBufferSize);
		vertexBuffer->Unmap(0, nullptr);

		vertexBufferView.BufferLocation = vertexBuffer->GetGPUVirtualAddress();
		vertexBufferView.StrideInBytes = sizeof(Vertex);
		vertexBufferView.SizeInBytes = vertexBufferSize;
	}

	virtual void CreateResources() override {
		App::CreateResources();
		psoManager.reset(new PSOManager{ device });

		// Create Root Signature

		D3D12_ROOT_SIGNATURE_DESC rootDesc = { 0 };
		rootDesc.NumParameters = 0;
		rootDesc.NumStaticSamplers = 0;
		rootDesc.pStaticSamplers = nullptr;
		rootDesc.pParameters = nullptr;
		rootDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

		com_ptr<ID3DBlob> signature;
		com_ptr<ID3DBlob> error;

		DX_API("Failed to serialize root signature")
			D3D12SerializeRootSignature(&rootDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, signature.GetAddressOf(), error.GetAddressOf());

		DX_API("Failed to create root signature")
			device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(rootSignature.GetAddressOf()));

		// Input Layout

		D3D12_INPUT_ELEMENT_DESC inputDesc[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
		};

		D3D12_INPUT_LAYOUT_DESC inputLayout;
		inputLayout.NumElements = _countof(inputDesc);
		inputLayout.pInputElementDescs = inputDesc;

		// Vertex / Pixel Shaders

		Shader vertexShader = Shader::LoadCSO("Shaders/DefaultVS.cso");
		Shader pixelShader = Shader::LoadCSO("Shaders/DefaultPS.cso");

		gpso = psoManager->Add(rootSignature.Get(), inputLayout, vertexShader.GetByteCode(), pixelShader.GetByteCode());

		// Create Command Allocator
		DX_API("Failed to create command allocator")
			device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(commandAllocator.GetAddressOf()));

		// Create Graphics Command List, set the newly created GPSO as its initial state
		DX_API("Failed to greate graphics command list")
			device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator.Get(), gpso.Get(), IID_PPV_ARGS(commandList.GetAddressOf()));

		commandList->Close();

		WaitForPreviousFrame();
	}

	virtual void ReleaseAssets() override {
		vertexBuffer.Reset();
		App::ReleaseAssets();
	}

	virtual void ReleaseResources() override {
		psoManager.reset(nullptr);
		commandList.Reset();
		rootSignature.Reset();
		gpso.Reset();
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

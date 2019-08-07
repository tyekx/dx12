#pragma once

#include <Egg/SimpleApp.h>
#include <Egg/Mesh/Importer.h>

class ggl002App : public Egg::SimpleApp {
protected:
	Egg::Mesh::Shaded::P shadedMesh;
	com_ptr<ID3D12Resource> depthStencilBuffer;
	com_ptr<ID3D12DescriptorHeap> depthStencilDescriptorHeap;
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

		CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHandle(depthStencilDescriptorHeap->GetCPUDescriptorHandleForHeapStart());
		commandList->OMSetRenderTargets(1, &rHandle, FALSE, &dsvHandle);

		const float clearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
		commandList->ClearRenderTargetView(rHandle, clearColor, 0, nullptr);
		commandList->ClearDepthStencilView(depthStencilDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

		shadedMesh->SetPipelineState(commandList.Get());
		shadedMesh->Draw(commandList.Get());

		commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(renderTargets[frameIndex].Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

		DX_API("Failed to close command list")
			commandList->Close();
	}

	virtual void CreateSwapChainResources() override {
		Egg::SimpleApp::CreateSwapChainResources();

		D3D12_DESCRIPTOR_HEAP_DESC dsHeapDesc = {};
		dsHeapDesc.NumDescriptors = 1;
		dsHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
		dsHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		
		DX_API("Failed to create depth stencil descriptor heap")
			device->CreateDescriptorHeap(&dsHeapDesc, IID_PPV_ARGS(depthStencilDescriptorHeap.GetAddressOf()));

		D3D12_DEPTH_STENCIL_VIEW_DESC depthStencilDesc = {};
		depthStencilDesc.Format = DXGI_FORMAT_D32_FLOAT;
		depthStencilDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
		depthStencilDesc.Flags = D3D12_DSV_FLAG_NONE;

		D3D12_CLEAR_VALUE depthOptimizedClearValue = {};
		depthOptimizedClearValue.Format = DXGI_FORMAT_D32_FLOAT;
		depthOptimizedClearValue.DepthStencil.Depth = 1.0f;
		depthOptimizedClearValue.DepthStencil.Stencil = 0;

		DX_API("Failed to create Depth Stencil buffer")
			device->CreateCommittedResource(
				&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
				D3D12_HEAP_FLAG_NONE,
				&CD3DX12_RESOURCE_DESC::Tex2D(DXGI_FORMAT_D32_FLOAT, scissorRect.right, scissorRect.bottom, 1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL),
				D3D12_RESOURCE_STATE_DEPTH_WRITE,
				&depthOptimizedClearValue,
				IID_PPV_ARGS(&depthStencilBuffer)
			);

		depthStencilBuffer->SetName(L"Depth Stencil Buffer");

		device->CreateDepthStencilView(depthStencilBuffer.Get(), &depthStencilDesc, depthStencilDescriptorHeap->GetCPUDescriptorHandleForHeapStart());
	}

	virtual void ReleaseSwapChainResources() override {

		depthStencilBuffer.Reset();
		depthStencilDescriptorHeap.Reset();

		Egg::SimpleApp::ReleaseSwapChainResources();
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



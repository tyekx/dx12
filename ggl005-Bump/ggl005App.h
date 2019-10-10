#pragma once

#include <Egg/SimpleApp.h>
#include <Egg/Importer.h>
#include <Egg/Math/Math.h>
#include <Egg/ConstantBuffer.hpp>

#include "ConstantBufferTypes.h"

using namespace Egg::Math;

class ggl005App : public Egg::SimpleApp {
protected:
	Egg::Mesh::Shaded::P shadedMesh;
	Float4x4 rotation;
	Egg::ConstantBuffer<PerObjectCb> cb;
	Egg::ConstantBuffer<PerFrameCb> perFrameCb;
	com_ptr<ID3D12DescriptorHeap> srvHeap;

	Egg::Texture2D diffuseTex;
	Egg::Texture2D normalTex;
	Egg::Texture2D bumpTex;
public:
	virtual void Update(float dt, float T) override {
		rotation *= Float4x4::Rotation(Float3::UnitY, 0.5f * dt);
		cb->model = Float4x4::Scaling(Float3{ 0.02f, 0.02f, 0.02f }) * rotation * Float4x4::Translation(Float3{ 0.0f, 0.0f, 2.5f });
		cb->invModel = cb->model.Invert();
		cb.Upload();

		perFrameCb->viewProj = Float4x4::Proj(0.9f, aspectRatio, 0.001f, 5.0f);
		perFrameCb->eyePos = Float3::Zero;
		perFrameCb->lightPos = Float4{ -1, -1, -1, 0 };
		perFrameCb->lightIntensity = Float3::One;
		perFrameCb.Upload();
	}

	virtual void PopulateCommandList() override {
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

		ID3D12DescriptorHeap* descriptorHeaps[] = { srvHeap.Get() };
		commandList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);

		shadedMesh->SetPipelineState(commandList.Get());
		shadedMesh->BindConstantBuffer(commandList.Get(), cb);
		shadedMesh->BindConstantBuffer(commandList.Get(), perFrameCb);
		commandList->SetGraphicsRootDescriptorTable(2, srvHeap->GetGPUDescriptorHandleForHeapStart());
		shadedMesh->Draw(commandList.Get());

		commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(renderTargets[frameIndex].Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

		DX_API("Failed to close command list")
			commandList->Close();
	}

	/*
	Almost a render call
	*/
	void UploadResources() {
		DX_API("Failed to reset command allocator (UploadResources)")
			commandAllocator->Reset();
		DX_API("Failed to reset command list (UploadResources)")
			commandList->Reset(commandAllocator.Get(), nullptr);

		diffuseTex.UploadResource(commandList.Get());
		normalTex.UploadResource(commandList.Get());
		bumpTex.UploadResource(commandList.Get());

		DX_API("Failed to close command list (UploadResources)")
			commandList->Close();

		ID3D12CommandList * commandLists[] = { commandList.Get() };
		commandQueue->ExecuteCommandLists(_countof(commandLists), commandLists);

		WaitForPreviousFrame();

		diffuseTex.ReleaseUploadResources();
		normalTex.ReleaseUploadResources();
		bumpTex.ReleaseUploadResources();
	}

	virtual void CreateResources() override {
		Egg::SimpleApp::CreateResources();

		D3D12_DESCRIPTOR_HEAP_DESC dhd;
		dhd.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		dhd.NodeMask = 0;
		dhd.NumDescriptors = 3;
		dhd.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;

		DX_API("Failed to create descriptor heap for texture")
			device->CreateDescriptorHeap(&dhd, IID_PPV_ARGS(srvHeap.GetAddressOf()));
	}

	virtual void ReleaseResources() override {
		srvHeap.Reset();
		cb.ReleaseResources();
		perFrameCb.ReleaseResources();

		Egg::SimpleApp::ReleaseResources();
	}

	virtual void LoadAssets() override {
		cb.CreateResources(device.Get());
		perFrameCb.CreateResources(device.Get());

		com_ptr<ID3DBlob> vertexShader = Egg::Shader::LoadCso("Shaders/NormalMapVS.cso");
		com_ptr<ID3DBlob> pixelShader = Egg::Shader::LoadCso("Shaders/NormalMapPS.cso");
		com_ptr<ID3D12RootSignature> rootSig = Egg::Shader::LoadRootSignature(device.Get(), vertexShader.Get());

		Egg::Mesh::Material::P material = Egg::Mesh::Material::Create();
		material->SetRootSignature(rootSig);
		material->SetVertexShader(vertexShader);
		material->SetPixelShader(pixelShader);
		material->SetDepthStencilState(CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT));
		material->SetDSVFormat(DXGI_FORMAT_D32_FLOAT);

		Egg::Mesh::Geometry::P bumpGeom = Egg::Importer::ImportWithTangentSpace(device.Get(), "big.x");

		shadedMesh = Egg::Mesh::Shaded::Create(psoManager.get(), material, bumpGeom);

		diffuseTex = Egg::Importer::ImportTexture2D(device.Get(), "rkd.jpg");
		diffuseTex.CreateSRV(device.Get(), srvHeap.Get(), 0);
		
		normalTex = Egg::Importer::ImportTexture2D(device.Get(), "rnormal.jpg");
		normalTex.CreateSRV(device.Get(), srvHeap.Get(), 1);

		bumpTex = Egg::Importer::ImportTexture2D(device.Get(), "rbump.jpg");
		bumpTex.CreateSRV(device.Get(), srvHeap.Get(), 2);

		UploadResources();
	}

};



#pragma once

#include "Box.h"
#include <Egg/SimpleApp.h>


class ggl001App : public Egg::SimpleApp {
protected:
	Box boxes[8];
public:
	virtual void Update(double T, double dt) override {
		for(int i = 0; i < 8; ++i) {
			boxes[i].Update(T);
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
		for(int i = 0; i < 8; ++i) {
			boxes[i].CreateResources(device.Get(), psoManager.get());
			boxes[i].scale = Float4x4::Scaling(Float3{ 0.2f, 0.2f, 0.2f });
			boxes[i].translation = Float4x4::Translation(Float3{ i * 0.25f - 0.9f, 0.0f, 0.8f });
			boxes[i].speed = 0.5f + i * 0.2f;
		}
	}

};



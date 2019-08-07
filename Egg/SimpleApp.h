#pragma once

#include "Common.h"
#include "Mesh/Shaded.h"
#include "App.h"
#include "Shader.h"

namespace Egg {

	class SimpleApp : public App {
	protected:
		com_ptr<ID3D12CommandAllocator> commandAllocator;
		com_ptr<ID3D12GraphicsCommandList> commandList;

		std::unique_ptr<PsoManager> psoManager;

		virtual void PopulateCommandList() = 0;

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
				swapChain->Present(0, 0);

			// Sync
			WaitForPreviousFrame();
		}

		virtual void CreateResources() override {
			App::CreateResources();

			psoManager.reset(new PsoManager{ device });

			DX_API("Failed to create command allocator")
				device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(commandAllocator.GetAddressOf()));

			DX_API("Failed to greate graphics command list")
				device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator.Get(), nullptr, IID_PPV_ARGS(commandList.GetAddressOf()));

			commandList->Close();

			WaitForPreviousFrame();
		}

		virtual void ReleaseResources() override {
			psoManager.reset(nullptr);
			commandList.Reset();
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

}

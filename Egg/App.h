#pragma once

#include "Common.h"
#include <vector>

namespace Egg {

	class App {
	protected:
		com_ptr<ID3D12Device> device;
		com_ptr<IDXGISwapChain3> swapChain;
		com_ptr<ID3D12CommandQueue> commandQueue;

		// swap chain resources
		D3D12_VIEWPORT viewPort;
		D3D12_RECT scissorRect;
		unsigned int backBufferDepth;
		unsigned int rtvDescriptorHandleIncrementSize;
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;
		com_ptr<ID3D12DescriptorHeap> rtvDescriptorHeap;
		std::vector<com_ptr<ID3D12Resource>> renderTargets;
		float aspectRatio;

		// Sync objects
		com_ptr<ID3D12Fence> fence;
		HANDLE fenceEvent;
		unsigned long long fenceValue;
		unsigned int frameIndex;
	public:
		virtual ~App() = default;

		virtual void CreateSwapChainResources() {
			DXGI_SWAP_CHAIN_DESC scDesc;
			swapChain->GetDesc(&scDesc);

			backBufferDepth = scDesc.BufferCount;

			viewPort.TopLeftX = 0;
			viewPort.TopLeftY = 0;
			viewPort.Width = (float)scDesc.BufferDesc.Width;
			viewPort.Height = (float)scDesc.BufferDesc.Height;
			viewPort.MinDepth = 0.0f;
			viewPort.MaxDepth = 1.0f;

			aspectRatio = viewPort.Width / (float)viewPort.Height;

			scissorRect.left = 0;
			scissorRect.top = 0;
			scissorRect.right = scDesc.BufferDesc.Width;
			scissorRect.bottom = scDesc.BufferDesc.Height;

			// Create Render Target View Descriptor Heap, like a RenderTargetView** on the GPU. A set of pointers.

			D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc;
			rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
			rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
			rtvHeapDesc.NumDescriptors = backBufferDepth;
			rtvHeapDesc.NodeMask = 0;

			DX_API("Failed to create render target view descriptor heap")
				device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(rtvDescriptorHeap.GetAddressOf()));

			rtvHandle = rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
			rtvDescriptorHandleIncrementSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

			// Create Render Target Views

			renderTargets.resize(backBufferDepth);

			for(unsigned int i = 0; i < backBufferDepth; ++i) {
				DX_API("Failed to get swap chain buffer")
					swapChain->GetBuffer(i, IID_PPV_ARGS(renderTargets[i].GetAddressOf()));

				CD3DX12_CPU_DESCRIPTOR_HANDLE cpuHandle{ rtvHandle };
				cpuHandle.Offset(i * rtvDescriptorHandleIncrementSize);

				device->CreateRenderTargetView(renderTargets[i].Get(), nullptr, cpuHandle);
			}

			frameIndex = swapChain->GetCurrentBackBufferIndex();
		}

		virtual void ReleaseSwapChainResources() {
			for(com_ptr<ID3D12Resource> & i : renderTargets) {
				i.Reset();
			}
			renderTargets.clear();
			rtvDescriptorHeap.Reset();
		}

		virtual void Render() = 0;
		virtual void Update(float T, float dt) = 0;

		virtual void LoadAssets() { }

		virtual void ReleaseAssets() { }

		virtual void CreateResources() {
			DX_API("Failed to create fence")
				device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(fence.GetAddressOf()));
			fenceValue = 1;

			fenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
			if(fenceEvent == NULL) {
				DX_API("Failed to create windows event") HRESULT_FROM_WIN32(GetLastError());
			}
		}

		virtual void ReleaseResources() {
			commandQueue.Reset();
			swapChain.Reset();
			device.Reset();
		}

		virtual void Resize(int width, int height) {
			ReleaseSwapChainResources();
			DX_API("Failed to resize swap chain")
				swapChain->ResizeBuffers(backBufferDepth, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
			CreateSwapChainResources();
		}

		virtual void Destroy() {
			ReleaseSwapChainResources();
			ReleaseResources();
			ReleaseAssets();
		}

		void SetCommandQueue(com_ptr<ID3D12CommandQueue> cQueue) {
			commandQueue = cQueue;
		}

		void SetDevice(com_ptr<ID3D12Device> dev) {
			device = dev;
		}

		void SetSwapChain(com_ptr<IDXGISwapChain3> sChain) {
			swapChain = sChain;
		}
	};

}

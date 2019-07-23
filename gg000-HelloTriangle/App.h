#pragma once

#include "Common.h"

class App {
protected:
	com_ptr<IDXGISwapChain3> swapChain;
	com_ptr<ID3D12Device> device;
	com_ptr<ID3D12Fence> fence;

	virtual void PopulateCommandList() {

	}

	virtual void WaitForPreviousFrame() {

	}
public:
	virtual void Render() {

	}

	virtual void CreateResources() {

	}
	virtual void ReleaseResources() {

	}

	virtual void CreateSwapChainResources() {

	}
	virtual void ReleaseSwapChainResources() {

	}

	virtual void SetSwapChain(com_ptr<IDXGISwapChain3> sChain) {
		swapChain = sChain;
	}
};

#pragma once

#include "Common.h"

class App {
public:
	void CreateResources();
	void ReleaseResources();

	void CreateSwapChainResources();
	void ReleaseSwapChainResources();

	void SetSwapChain(com_ptr<IDXGISwapChain3>)
};

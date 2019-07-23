#include "Common.h"
#include <system_error>

template<typename T>
using com_ptr = Microsoft::WRL::ComPtr<T>;

// R"()" is the multiline string in C++
const char * vertexShaderCode = R"(
struct InputAssemblerOutputStructure {
	float3 position : POSITION;
	float3 color : COLOR;
};

struct VertexShaderOutputStructure {
	float4 position : SV_Position;
	float3 color : COLOR;
};

VertexShaderOutputStructure vs_main(InputAssemblerOutputStructure iaos) {
	VertexShaderOutputStructure vsos;
	vsos.position = float4(iaos.position.xy, 0.1f, 1.0f);
	vsos.color = iaos.color;
	return vsos;
}
)";

const char * pixelShaderCode = R"(
struct VertexShaderOutputStructure {
	float4 position : SV_Position;
	float3 color : COLOR;
};

float4 ps_main(VertexShaderOutputStructure vsos) : SV_Target {
	return float4(vsos.color, 1.0f);
}
)";

LRESULT CALLBACK WindowProcess(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam) {
	switch(message) {
	case WM_DESTROY:
		// adds a WM_QUIT message to the message queue
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(windowHandle, message, wParam, lParam);
}

HWND InitWindow(HINSTANCE hInstance) {
	const wchar_t * windowClassName = L"ClassName";

	WNDCLASSW windowClass;
	ZeroMemory(&windowClass, sizeof(WNDCLASSW));

	windowClass.lpfnWndProc = WindowProcess;
	windowClass.lpszClassName = windowClassName;
	windowClass.hInstance = hInstance;

	RegisterClassW(&windowClass);

	HWND wnd = CreateWindowExW(0,
							   windowClassName,
							   L"Hello Triangle",
							   WS_OVERLAPPEDWINDOW,
							   CW_USEDEFAULT,
							   CW_USEDEFAULT,
							   CW_USEDEFAULT,
							   CW_USEDEFAULT,
							   NULL,
							   NULL,
							   hInstance,
							   NULL);

	ASSERT(wnd != NULL, "Failed to create window");

	return wnd;
}

void GetAdapters(IDXGIFactory6 * dxgiFactory, std::vector<com_ptr<IDXGIAdapter1>> & adapters) {
	HRESULT adapterQueryResult;
	unsigned int adapterId = 0;
	OutputDebugStringW(L"Detected Video Adapters:\n");
	do {
		com_ptr<IDXGIAdapter1> tempAdapter{ nullptr };
		adapterQueryResult = dxgiFactory->EnumAdapters1(adapterId, tempAdapter.GetAddressOf());

		if(adapterQueryResult != S_OK && adapterQueryResult != DXGI_ERROR_NOT_FOUND) {
			ASSERT(false, "Failed to query DXGI adapter");
		}

		if(tempAdapter != nullptr) {
			DXGI_ADAPTER_DESC desc;
			tempAdapter->GetDesc(&desc);

			OutputDebugStringW(L"\t");
			OutputDebugStringW(desc.Description);
			OutputDebugStringW(L"\n");

			adapters.push_back(std::move(tempAdapter));
		}

		adapterId++;
	} while(adapterQueryResult != DXGI_ERROR_NOT_FOUND);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, LPWSTR command, INT nShowCmd) {
	HWND windowHandle = InitWindow(hInstance);

	ShowWindow(windowHandle, nShowCmd);
	MSG winMessage = { 0 };

	RECT r;
	GetWindowRect(windowHandle, &r);

	D3D12_VIEWPORT viewPort;
	D3D12_RECT scissorRect;

	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;
	viewPort.Width = r.right - r.left;
	viewPort.Height = r.bottom - r.top;

	scissorRect.left = 0;
	scissorRect.top = 0;
	scissorRect.right = r.right - r.left;
	scissorRect.bottom = r.bottom - r.top;

	// DirectX stuff
	com_ptr<ID3D12Debug> debugController{ nullptr };
	com_ptr<IDXGIFactory6> dxgiFactory{ nullptr };
	com_ptr<IDXGISwapChain3> swapChain{ nullptr };
	com_ptr<ID3D12Device> device{ nullptr };
	com_ptr<ID3D12CommandQueue> commandQueue{ nullptr };
	com_ptr<ID3D12RootSignature> rootSignature{ nullptr };

	// debug controller 
	DX_API("Failed to create debug layer")
		D3D12GetDebugInterface(IID_PPV_ARGS(debugController.GetAddressOf()));

	debugController->EnableDebugLayer();

	DX_API("Failed to create DXGI factory")
		CreateDXGIFactory1(IID_PPV_ARGS(dxgiFactory.GetAddressOf()));

	std::vector<com_ptr<IDXGIAdapter1>> adapters;
	GetAdapters(dxgiFactory.Get(), adapters);

	// select your adapter here, NULL = system default
	IUnknown * selectedAdapter = (adapters.size() > 0) ? adapters[0].Get() : NULL;

	DX_API("Failed to create D3D Device")
		D3D12CreateDevice(selectedAdapter, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(device.GetAddressOf()));

	D3D12_COMMAND_QUEUE_DESC commandQueueDesc;
	commandQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	commandQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	commandQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	commandQueueDesc.NodeMask = 0;

	DX_API("Failed to create command queue")
		device->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(commandQueue.GetAddressOf()));


	// swap chain creation
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
	// if you specify width/height as 0, the CreateSwapChainForHwnd will query it from the output window
	swapChainDesc.Width = 0;
	swapChainDesc.Height = 0;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.Stereo = false;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 2; // back buffer depth
	swapChainDesc.Scaling = DXGI_SCALING_NONE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
	swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
	swapChainDesc.Flags = 0;

	DXGI_SWAP_CHAIN_FULLSCREEN_DESC swapChainFullscreenDesc = { 0 };
	swapChainFullscreenDesc.RefreshRate = DXGI_RATIONAL{ 60, 1 };
	swapChainFullscreenDesc.Windowed = true;
	swapChainFullscreenDesc.Scaling = DXGI_MODE_SCALING_CENTERED;
	swapChainFullscreenDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST;

	com_ptr<IDXGISwapChain1> tempSwapChain;

	DX_API("Failed to create swap chain for HWND")
		dxgiFactory->CreateSwapChainForHwnd(commandQueue.Get(), windowHandle, &swapChainDesc, &swapChainFullscreenDesc, NULL, tempSwapChain.GetAddressOf());

	DX_API("Failed to cast swap chain")
		tempSwapChain.As(&swapChain);

	DX_API("Failed to make window association") // disable ALT+Enter shortcut to full screen mode
		dxgiFactory->MakeWindowAssociation(windowHandle, DXGI_MWA_NO_ALT_ENTER);

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

	com_ptr<ID3D12Resource> renderTargets[2];
	com_ptr<ID3D12DescriptorHeap> rtvDescriptorHeap{ nullptr };
	com_ptr<ID3D12CommandAllocator> commandAllocator{ nullptr };

	DX_API("Failed to create command allocators")
		device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(commandAllocator.GetAddressOf()));

	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc;
	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvHeapDesc.NumDescriptors = 2;
	rtvHeapDesc.NodeMask = 0;

	DX_API("Failed to create render target view descriptor heap")
		device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(rtvDescriptorHeap.GetAddressOf()));

	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
	int incrementSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	

	for(unsigned int i = 0; i < 2; ++i) {
		DX_API("Failed to get swap chain buffer")
			swapChain->GetBuffer(i, IID_PPV_ARGS(renderTargets[i].GetAddressOf()));

		device->CreateRenderTargetView(renderTargets[i].Get(), nullptr, rtvHandle);

		rtvHandle.ptr += incrementSize;

	}

	D3D12_INPUT_ELEMENT_DESC inputDesc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	};

	D3D12_INPUT_LAYOUT_DESC inputLayout;
	inputLayout.NumElements = _countof(inputDesc);
	inputLayout.pInputElementDescs = inputDesc;

	com_ptr<ID3DBlob> vsByteCode;
	com_ptr<ID3DBlob> vsError;
	HRESULT cRes = D3DCompile(vertexShaderCode, strlen(vertexShaderCode), "basic vertex shader", nullptr, nullptr, "vs_main", "vs_5_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, vsByteCode.GetAddressOf(), vsError.GetAddressOf());

	if(cRes != S_OK) {
		char * ptr = reinterpret_cast<char*>(vsError->GetBufferPointer());
		std::string err = "Failed to compile vertex shader: " + std::string{ ptr };
		DX_API(err.c_str()) cRes;
	}

	com_ptr<ID3DBlob> psByteCode;
	com_ptr<ID3DBlob> psError;

	cRes = D3DCompile(pixelShaderCode, strlen(pixelShaderCode), "basic pixel shader", nullptr, nullptr, "ps_main", "ps_5_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, psByteCode.GetAddressOf(), psError.GetAddressOf());

	if(cRes != S_OK) {
		char * ptr = reinterpret_cast<char*>(psError->GetBufferPointer());
		std::string err = "Failed to compile pixel shader: " + std::string{ ptr };
		DX_API(err.c_str()) cRes;
	}

	com_ptr<ID3D12PipelineState> graphicsPipelineStateObject;


	D3D12_GRAPHICS_PIPELINE_STATE_DESC gpsoDesc;
	ZeroMemory(&gpsoDesc, sizeof(gpsoDesc));
	gpsoDesc.pRootSignature = rootSignature.Get();
	gpsoDesc.InputLayout = inputLayout;

	gpsoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	gpsoDesc.NumRenderTargets = 1;
	gpsoDesc.DepthStencilState.StencilEnable = FALSE;
	gpsoDesc.DepthStencilState.DepthEnable = FALSE;
	gpsoDesc.SampleMask = UINT_MAX;
	gpsoDesc.SampleDesc.Count = 1;
	gpsoDesc.SampleDesc.Quality = 0;
	gpsoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;

	gpsoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	gpsoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);

	gpsoDesc.VS.pShaderBytecode = vsByteCode->GetBufferPointer();
	gpsoDesc.VS.BytecodeLength = vsByteCode->GetBufferSize();

	gpsoDesc.PS.pShaderBytecode = psByteCode->GetBufferPointer();
	gpsoDesc.PS.BytecodeLength = psByteCode->GetBufferSize();

	DX_API("Failed to initialize GPSO")
	device->CreateGraphicsPipelineState(&gpsoDesc, IID_PPV_ARGS(graphicsPipelineStateObject.GetAddressOf()));


	com_ptr<ID3D12GraphicsCommandList> commandList{ nullptr };

	DX_API("Failed to greate graphics command list")
		device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator.Get(), graphicsPipelineStateObject.Get(), IID_PPV_ARGS(commandList.GetAddressOf()));

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
	
	com_ptr<ID3D12Resource> vertexBuffer{ nullptr };

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

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
	vertexBufferView.BufferLocation = vertexBuffer->GetGPUVirtualAddress();
	vertexBufferView.StrideInBytes = sizeof(Vertex);
	vertexBufferView.SizeInBytes = vertexBufferSize;

	unsigned int frameIndex = swapChain->GetCurrentBackBufferIndex();

	com_ptr<ID3D12Fence> fence{ nullptr };
	HANDLE fenceEvent;
	UINT64 fenceValue = 0;

	DX_API("Failed to create fence")
		device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(fence.GetAddressOf()));
	fenceValue = 1;

	fenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if(fenceEvent == NULL) {
		DX_API("Failed to create windows event") HRESULT_FROM_WIN32(GetLastError());
	}

	commandList->Close();

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

	while(winMessage.message != WM_QUIT) {
		if(PeekMessage(&winMessage, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&winMessage);
			DispatchMessage(&winMessage);
		} else {
			commandAllocator->Reset();
			commandList->Reset(commandAllocator.Get(), graphicsPipelineStateObject.Get());
			
			commandList->SetGraphicsRootSignature(rootSignature.Get());
			commandList->RSSetViewports(1, &viewPort);
			commandList->RSSetScissorRects(1, &scissorRect);

			commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(renderTargets[frameIndex].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

			CD3DX12_CPU_DESCRIPTOR_HANDLE rHandle(rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), frameIndex, incrementSize);
			commandList->OMSetRenderTargets(1, &rHandle, FALSE, nullptr);

			const float clearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
			commandList->ClearRenderTargetView(rHandle, clearColor, 0, nullptr);

			commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			commandList->IASetVertexBuffers(0, 1, &vertexBufferView);
			commandList->DrawInstanced(3, 1, 0, 0);

			commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(renderTargets[frameIndex].Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

			DX_API("Failed to close command list")
				commandList->Close();

			ID3D12CommandList * ppCommandLists[] = { commandList.Get() };
			commandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

			DX_API("Failed to present swap chain")
				swapChain->Present(1, 0);

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
	}

	return 0;
}

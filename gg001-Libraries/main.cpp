#include "HelloTriangleApp.h"
#include <Egg/Utility.h>
#include <chrono>
#include <type_traits>
#include <Egg/Math/Math.h>
 
using namespace Egg::Math;

__declspec(align(16)) struct PerObjectCb {
	Float4x4 modelTransform;
};

struct PNT_Vertex {
	Float3 position;
	Float3 normal;
	Float2 tex;
};

template<typename T>
class ConstantBuffer {
	UINT8 * mappedPtr;
	com_ptr<ID3D12Resource> constantBuffer;
	T data;
public:
	using Type = T;

	ConstantBuffer() : mappedPtr{ nullptr }, constantBuffer{ nullptr } {
		static_assert(__alignof(T) % 16 == 0, "ConstantBuffer type must be aligned to 16 bytes, otherwise you'll get funny glitches, use __declspec(align(16)) before your class specification");
		static_assert(!std::is_polymorphic<T>::value, "Polymorphic classes are strongly discouraged as constant buffers (the Vtable will offset the layout, remove any virtual keywords)");
	}

	~ConstantBuffer() {
		ReleaseResources();
	}

	void CreateResources(ID3D12Device * device) {
		DX_API("Failed to create constant buffer resource")
			device->CreateCommittedResource(
				&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
				D3D12_HEAP_FLAG_NONE,
				&CD3DX12_RESOURCE_DESC::Buffer(Egg::Utility::Align256(sizeof(T))),
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(constantBuffer.GetAddressOf()));

		CD3DX12_RANGE rr(0, 0);
		DX_API("Failed to map constant buffer")
			constantBuffer->Map(0, &rr, reinterpret_cast<void**>(&mappedPtr));
	}

	D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress() const {
		return constantBuffer->GetGPUVirtualAddress();
	}

	void ReleaseResources() {
		if(constantBuffer != nullptr) {
			constantBuffer->Unmap(0, nullptr);
			constantBuffer.Reset();
		}
		mappedPtr = nullptr;
	}

	void Upload() {
		memcpy(mappedPtr, &data, sizeof(T));
	}

	void Bind(ID3D12GraphicsCommandList * commandList) {
		Upload();
		commandList->SetGraphicsRootConstantBufferView(0, constantBuffer->GetGPUVirtualAddress());
	}

	T & operator=(const T & rhs) {
		data = rhs;
		return data;
	}

	T * operator->() {
		return &data;
	}
};

class Box {
public:
	Egg::Mesh::Shaded::P shadedBox;
	ConstantBuffer<PerObjectCb> cb;
	Float4x4 translation;
	Float4x4 rotation;
	Float4x4 scale;
	float speed;


	void Update(double T) {
		rotation = Float4x4::rotation(Float3{1.0f, 1.0f, 1.0f}, ((float)T) * speed);
		cb->modelTransform = scale * rotation * translation;
	}

	void Draw(ID3D12GraphicsCommandList * commandList) {
		shadedBox->SetPipelineState(commandList);
		//cb.Bind(commandList);
		shadedBox->BindConstantBuffer(commandList, cb, "MiertNemJo");
		shadedBox->Draw(commandList);
	}

	void CreateResources(ID3D12Device * device, Egg::PsoManager * psoManager) {
		cb.CreateResources(device);

		PNT_Vertex vertices[] = {
			{ { -0.4f, -0.4f, -0.4f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f } },
			{ { -0.4f,  0.4f, -0.4f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f } },
			{ {  0.4f, -0.4f, -0.4f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f } },
			{ {  0.4f, -0.4f, -0.4f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f } },
			{ { -0.4f,  0.4f, -0.4f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f } },
			{ {  0.4f,  0.4f, -0.4f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f } },

			{ { -0.4f,  0.4f, -0.4f }, { 0.0f, 1.0f,  0.0f }, { 0.0f, 0.0f } },
			{ { -0.4f,  0.4f,  0.4f }, { 0.0f, 1.0f,  0.0f }, { 0.0f, 1.0f } },
			{ {  0.4f,  0.4f, -0.4f }, { 0.0f, 1.0f,  0.0f }, { 1.0f, 0.0f } },
			{ {  0.4f,  0.4f, -0.4f }, { 0.0f, 1.0f,  0.0f }, { 1.0f, 0.0f } },
			{ { -0.4f,  0.4f,  0.4f }, { 0.0f, 1.0f,  0.0f }, { 0.0f, 1.0f } },
			{ {  0.4f,  0.4f,  0.4f }, { 0.0f, 1.0f,  0.0f }, { 1.0f, 1.0f } },

			{ {  0.4f, -0.4f, -0.4f }, { 1.0f, 0.0f,  0.0f }, { 0.0f, 0.0f } },
			{ {  0.4f,  0.4f, -0.4f }, { 1.0f, 0.0f,  0.0f }, { 0.0f, 1.0f } },
			{ {  0.4f, -0.4f, 0.4f }, { 1.0f, 0.0f,  0.0f }, { 1.0f, 0.0f } },
			{ {  0.4f, -0.4f, 0.4f }, { 1.0f, 0.0f,  0.0f }, { 1.0f, 0.0f } },
			{ {  0.4f,  0.4f, -0.4f }, { 1.0f, 0.0f,  0.0f }, { 0.0f, 1.0f } },
			{ {  0.4f,  0.4f, 0.4f }, { 1.0f, 0.0f,  0.0f }, { 1.0f, 1.0f } },

			{ {  0.4f, -0.4f, 0.4f }, { 0.0f, 0.0f,  1.0f }, { 0.0f, 0.0f } },
			{ {  0.4f,  0.4f, 0.4f }, { 0.0f, 0.0f,  1.0f }, { 0.0f, 1.0f } },
			{ { -0.4f, -0.4f, 0.4f }, { 0.0f, 0.0f,  1.0f }, { 1.0f, 0.0f } },
			{ { -0.4f, -0.4f, 0.4f }, { 0.0f, 0.0f,  1.0f }, { 1.0f, 0.0f } },
			{ {  0.4f,  0.4f, 0.4f }, { 0.0f, 0.0f,  1.0f }, { 0.0f, 1.0f } },
			{ { -0.4f,  0.4f, 0.4f }, { 0.0f, 0.0f,  1.0f }, { 1.0f, 1.0f } },

			{ { -0.4f, -0.4f, 0.4f }, { 0.0f, -1.0f,  0.0f }, { 0.0f, 0.0f } },
			{ { -0.4f, -0.4f, -0.4f }, { 0.0f, -1.0f,  0.0f }, { 0.0f, 1.0f } },
			{ {  0.4f, -0.4f, 0.4f }, { 0.0f, -1.0f,  0.0f }, { 1.0f, 0.0f } },
			{ {  0.4f, -0.4f, 0.4f }, { 0.0f, -1.0f,  0.0f }, { 1.0f, 0.0f } },
			{ { -0.4f, -0.4f, -0.4f }, { 0.0f, -1.0f,  0.0f }, { 0.0f, 1.0f } },
			{ {  0.4f, -0.4f, -0.4f }, { 0.0f, -1.0f,  0.0f }, { 1.0f, 1.0f } },

			{ {  -0.4f, -0.4f, 0.4f }, { -1.0f, 0.0f,  0.0f }, { 0.0f, 0.0f } },
			{ {  -0.4f,  0.4f, 0.4f }, { -1.0f, 0.0f,  0.0f }, { 0.0f, 1.0f } },
			{ {  -0.4f, -0.4f, -0.4f }, { -1.0f, 0.0f,  0.0f }, { 1.0f, 0.0f } },
			{ {  -0.4f, -0.4f, -0.4f }, { -1.0f, 0.0f,  0.0f }, { 1.0f, 0.0f } },
			{ {  -0.4f,  0.4f, 0.4f }, { -1.0f, 0.0f,  0.0f }, { 0.0f, 1.0f } },
			{ {  -0.4f,  0.4f, -0.4f }, { -1.0f, 0.0f,  0.0f }, { 1.0f, 1.0f } }
		};

		unsigned int vertexBufferSize = sizeof(vertices);

		// Vertex / Pixel Shaders

		com_ptr<ID3DBlob> vertexShader = Shader::LoadCso("Shaders/cbBasicVS.cso");
		com_ptr<ID3DBlob> pixelShader = Shader::LoadCso("Shaders/DefaultPS.cso");
		com_ptr<ID3D12RootSignature> rootSig = Shader::LoadRootSignature(device, vertexShader.Get());

		Egg::Mesh::Geometry::P geometry = Egg::Mesh::VertexStreamGeometry::Create(device, reinterpret_cast<void*>(vertices), vertexBufferSize, sizeof(PNT_Vertex));
		geometry->AddInputElement({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });
		geometry->AddInputElement({ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });
		geometry->AddInputElement({ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });

		Egg::Mesh::Material::P material = Egg::Mesh::Material::Create();
		material->SetRootSignature(rootSig);
		material->SetVertexShader(vertexShader);
		material->SetPixelShader(pixelShader);

		shadedBox = Egg::Mesh::Shaded::Create(psoManager, material, geometry);
	}

};


class HelloConstantBufferApp : public HelloTriangleApp {
protected:
	Box boxes[8];
public:
	virtual void Update(double T, double dt) override {
		for(int i = 0; i < 8; ++i) {
			boxes[i].Update(T);
		}
	}

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

		for(int i = 0; i < 8; ++i) {
			boxes[i].Draw(commandList.Get());
		}

		commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(renderTargets[frameIndex].Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

		DX_API("Failed to close command list")
			commandList->Close();
	}

	virtual void Render() override {
		PopulateCommandList();

		// Execute
		ID3D12CommandList * cLists[] = { commandList.Get() };
		commandQueue->ExecuteCommandLists(_countof(cLists), cLists);

		DX_API("Failed to present swap chain")
			swapChain->Present(1, 0);

		WaitForPreviousFrame();
	}

	virtual void LoadAssets() override {
		for(int i = 0; i < 8; ++i) {
			boxes[i].CreateResources(device.Get(), psoManager.get());
			boxes[i].scale = Float4x4::scaling(Float3{ 0.2f, 0.2f, 0.2f });
			boxes[i].translation = Float4x4::translation(Float3{ i * 0.25f - 0.9f, 0.0f, 0.8f });
			boxes[i].speed = 0.5f + i * 0.2f;
		}
	}

};

Egg::App * app;

LRESULT CALLBACK WindowProcess(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam) {
	switch(message) {
	case WM_DESTROY:
		app->Destroy();
		PostQuitMessage(0);
		return 0;
	case WM_SIZE:
		int height = HIWORD(lParam);
		int width = LOWORD(lParam);
		if(app != nullptr) {
			app->Resize(width, height);
		}
		break;
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


int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, LPWSTR command, INT nShowCmd) {

	HWND windowHandle = InitWindow(hInstance);
	// DirectX stuff
	com_ptr<ID3D12Debug> debugController{ nullptr };
	com_ptr<IDXGIFactory6> dxgiFactory{ nullptr };
	com_ptr<IDXGISwapChain3> swapChain{ nullptr };
	com_ptr<ID3D12Device> device{ nullptr };
	com_ptr<ID3D12CommandQueue> commandQueue{ nullptr };

	// debug controller 
	DX_API("Failed to create debug layer")
		D3D12GetDebugInterface(IID_PPV_ARGS(debugController.GetAddressOf()));

	debugController->EnableDebugLayer();

	DX_API("Failed to create DXGI factory")
		CreateDXGIFactory1(IID_PPV_ARGS(dxgiFactory.GetAddressOf()));

	std::vector<com_ptr<IDXGIAdapter1>> adapters;
	Egg::Utility::GetAdapters(dxgiFactory.Get(), adapters);

	// select your adapter here, NULL = system default
	IUnknown * selectedAdapter = (adapters.size() > 0) ? adapters[0].Get() : NULL;

	DX_API("Failed to create D3D Device")
		D3D12CreateDevice(selectedAdapter, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(device.GetAddressOf()));


	// Create Command Queue

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

	app = new HelloConstantBufferApp{};
	app->SetDevice(device);
	app->SetCommandQueue(commandQueue);
	app->SetSwapChain(swapChain);
	
	app->CreateSwapChainResources();
	app->CreateResources();
	app->LoadAssets();

	ShowWindow(windowHandle, nShowCmd);
	MSG winMessage = { 0 };

	using clock_t = std::chrono::high_resolution_clock;

	std::chrono::time_point<clock_t> start = clock_t::now();
	std::chrono::time_point<clock_t> end;
	double T = 0.0;
	double dt = 0.0;
	while(winMessage.message != WM_QUIT) {
		if(PeekMessage(&winMessage, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&winMessage);
			DispatchMessage(&winMessage);
		} else {
			end = clock_t::now();
			dt = std::chrono::duration<double>(end - start).count();
			T += dt;
			start = end;
			
			app->Update(T, dt);
			app->Render();
		}
	}

	delete app;

	return 0;
}

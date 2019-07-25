#pragma once

#include "Common.h"

namespace Egg {

	namespace Utility {

		constexpr unsigned int Align256(unsigned int v) {
			return (v + 255U) & (~255U);
		}

		void DebugPrintBlob(com_ptr<ID3DBlob> blob) {
			if(blob != nullptr) {
				OutputDebugString(reinterpret_cast<const char*>(blob->GetBufferPointer()));
			} else {
				OutputDebugString("Blob was NULL");
			}
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

	}

}

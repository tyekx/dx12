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

		// prints a formatted wide string to the VS output window
		void WDebugf(const wchar_t * format, ...) {
			va_list va;
			va_start(va, format);

			std::wstring wstr;
			wstr.resize(1024);

			vswprintf_s(&(wstr.at(0)), 1024, format, va);

			OutputDebugStringW(wstr.c_str());

			va_end(va);
		}

		// prints a formatted string to the VS output window
		void Debugf(const char * format, ...) {
			va_list va;
			va_start(va, format);
			
			std::string str;
			str.resize(1024);

			vsprintf_s(&(str.at(0)), 1024, format, va);


			OutputDebugString(str.c_str());

			va_end(va);
		}

		void GetAdapters(IDXGIFactory6 * dxgiFactory, std::vector<com_ptr<IDXGIAdapter1>> & adapters) {
			com_ptr<IDXGIAdapter1> tempAdapter{ nullptr };
			OutputDebugStringW(L"Detected Video Adapters:\n");
			unsigned int adapterId = 0;
			
			for(HRESULT query = dxgiFactory->EnumAdapters1(adapterId, tempAdapter.GetAddressOf());
				query != DXGI_ERROR_NOT_FOUND;
				query = dxgiFactory->EnumAdapters1(++adapterId, tempAdapter.GetAddressOf())) {

				// check if not S_OK
				DX_API("Failed to query DXGI adapter") query;

				if(tempAdapter != nullptr) {
					DXGI_ADAPTER_DESC desc;
					tempAdapter->GetDesc(&desc);

					OutputDebugStringW(L"\t");
					OutputDebugStringW(desc.Description);
					OutputDebugStringW(L"\n");

					adapters.push_back(std::move(tempAdapter));
					tempAdapter.Reset();
				}
			}
		}

	}

}

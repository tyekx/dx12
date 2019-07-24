#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <d3d12.h>
#include <d3dcompiler.h>
#include <dxgi1_6.h>
#include "d3dx12.h"

template<typename T>
using com_ptr = Microsoft::WRL::ComPtr<T>;

namespace Egg {

	namespace Internal {

		void Assert(bool trueMeansOk, const char * msgOnFail);

		class HResultTester {
		public:
			const char * Message;
			const char * File;
			const int Line;

			HResultTester(const char * msg, const char * file, int line);

			void operator<<(HRESULT hr);
		};

	}

}

#define ASSERT(trueMeansOk, msgOnFail) Egg::Internal::Assert(trueMeansOk, msgOnFail)

#define DX_API(msg) Egg::Internal::HResultTester(msg, __FILE__, __LINE__) <<


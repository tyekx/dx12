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

	}

}

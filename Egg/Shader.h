#pragma once

#include "Common.h"
#include <fstream>

namespace Egg {
	
	class Shader {
		com_ptr<ID3DBlob> byteCode;

		Shader(com_ptr<ID3DBlob> && blobRvalue) : byteCode{ std::move(blobRvalue) } { }

	public:
		
		D3D12_SHADER_BYTECODE GetByteCode() const {
			D3D12_SHADER_BYTECODE bc;
			bc.BytecodeLength = byteCode->GetBufferSize();
			bc.pShaderBytecode = byteCode->GetBufferPointer();
			return bc;
		}

		static Shader LoadCSO(const std::string & filename) {
			std::ifstream file{ filename, std::ios::binary | std::ios::ate };
			std::streamsize size = file.tellg();

			file.seekg(0, std::ios::beg);

			com_ptr<ID3DBlob> shaderByteCode{ nullptr };
			
			DX_API("Failed to allocate memory for blob")
				D3DCreateBlob((size_t)size, shaderByteCode.GetAddressOf());

			if(file.read(reinterpret_cast<char*>(shaderByteCode->GetBufferPointer()), size)) {
				return Shader(std::move(shaderByteCode));
			} else {
				throw std::exception{ "Failed to load CSO file" };
			}
		}
	};

}

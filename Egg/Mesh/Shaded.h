#pragma once

#include "../Common.h"
#include "Material.h"
#include "Geometry.h"
#include "../PsoManager.h"
#include <typeinfo>

namespace Egg {
	namespace Mesh {

		GG_CLASS(Shaded)
			com_ptr<ID3D12PipelineState> pipelineState;
			D3D12_GRAPHICS_PIPELINE_STATE_DESC gpsoDesc;
			Material::P material;
			Geometry::P geometry;

			com_ptr<ID3D12RootSignatureDeserializer> rsDeserializer;
			com_ptr<ID3D12ShaderReflection> vsReflection;
			com_ptr<ID3D12ShaderReflection> psReflection;
		public:
			Shaded(PsoManager * psoMan, Material::P mat, Geometry::P geom) : pipelineState{ nullptr }, gpsoDesc{}, material{ mat }, geometry{ geom } {
				ZeroMemory(&gpsoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
				gpsoDesc.NumRenderTargets = 1;
				gpsoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
				gpsoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
				gpsoDesc.InputLayout = geom->GetInputLayout();
				mat->ApplyToDescriptor(gpsoDesc);
			
				DX_API("Failed to reflect vertex shader")
					D3DReflect(gpsoDesc.VS.pShaderBytecode, gpsoDesc.VS.BytecodeLength, IID_PPV_ARGS(vsReflection.GetAddressOf()));

				DX_API("Failed to reflect pixel shader")
					D3DReflect(gpsoDesc.PS.pShaderBytecode, gpsoDesc.PS.BytecodeLength, IID_PPV_ARGS(psReflection.GetAddressOf()));

				DX_API("Failed to deserialize root signature")
					D3D12CreateRootSignatureDeserializer(gpsoDesc.VS.pShaderBytecode, gpsoDesc.VS.BytecodeLength, IID_PPV_ARGS(rsDeserializer.GetAddressOf()));

				pipelineState = psoMan->Get(gpsoDesc);
			}

			template<typename T>
			void BindConstantBuffer(ID3D12GraphicsCommandList * commandList, const T & resource, const std::string & nameOverride = "") {
				std::string name = (nameOverride != "") ? nameOverride.c_str() : typeid(T::Type).name();

				size_t indexOf;
				if((indexOf = name.find(' ')) != std::string::npos) {
					name = name.substr(indexOf + 1);
				}

				D3D12_SHADER_INPUT_BIND_DESC bindDesc;

				DX_API("Failed to get resource binding")
					vsReflection->GetResourceBindingDescByName(name.c_str(), &bindDesc);

				const D3D12_ROOT_SIGNATURE_DESC & rootSignatureDesc = *(rsDeserializer->GetRootSignatureDesc());
				for(unsigned int i = 0; i < rootSignatureDesc.NumParameters; ++i) {
					const D3D12_ROOT_PARAMETER & param = rootSignatureDesc.pParameters[i];
					if(param.ParameterType == D3D12_ROOT_PARAMETER_TYPE_CBV &&
					   param.Descriptor.ShaderRegister == bindDesc.BindPoint &&
					   param.Descriptor.RegisterSpace == bindDesc.Space) {
						commandList->SetGraphicsRootConstantBufferView(i, resource.GetGPUVirtualAddress());
						return;
					}
				}
				OutputDebugString("Failed to bind constant buffer");
			}

			void SetPipelineState(ID3D12GraphicsCommandList * commandList) {
				commandList->SetPipelineState(pipelineState.Get());
				commandList->SetGraphicsRootSignature(gpsoDesc.pRootSignature);
			}

			void Draw(ID3D12GraphicsCommandList * commandList) {
				geometry->Draw(commandList);
			}

		GG_ENDCLASS


	}
}

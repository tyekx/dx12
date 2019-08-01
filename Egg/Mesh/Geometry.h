#pragma once

#include "../Common.h"

namespace Egg {
	namespace Mesh {

		GG_CLASS(Geometry)
		protected:
			std::vector<D3D12_INPUT_ELEMENT_DESC> inputElements;
			D3D12_INPUT_LAYOUT_DESC inputLayout;
			D3D12_PRIMITIVE_TOPOLOGY topology;
		public:
			Geometry() : inputElements{}, inputLayout{}, topology{ D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST } {}

			void SetTopology(D3D12_PRIMITIVE_TOPOLOGY top) {
				topology = top;
			}

			D3D12_PRIMITIVE_TOPOLOGY GetTopology() const {
				return topology;
			}

			void AddInputElement(const D3D12_INPUT_ELEMENT_DESC & ied) {
				inputElements.push_back(ied);
			}

			virtual void Draw(ID3D12GraphicsCommandList * commandList) = 0;
			
			const D3D12_INPUT_LAYOUT_DESC & GetInputLayout() {
				inputLayout.NumElements = (unsigned int)inputElements.size();
				inputLayout.pInputElementDescs = &(inputElements.at(0));
				return inputLayout;
			}

		GG_ENDCLASS

		GG_SUBCLASS(VertexStreamGeometry, Geometry)
		protected:
			com_ptr<ID3D12Resource> vertexBuffer;
			D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
			unsigned int vertexCount;
		public:

			VertexStreamGeometry(ID3D12Device * device, void * data, unsigned int sizeInBytes, unsigned int stride) : Geometry{}, vertexBuffer{ nullptr },
				vertexBufferView{}, vertexCount{ 0 } {

				ASSERT((sizeInBytes % stride) == 0, "VertexStreamGeometry: size and stride is inconsistent. Size % stride must be 0.");

				vertexCount = sizeInBytes / stride;

				DX_API("Failed to create committed resource (VertexStreamGeometry)")
					device->CreateCommittedResource(
						&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
						D3D12_HEAP_FLAG_NONE,
						&CD3DX12_RESOURCE_DESC::Buffer(sizeInBytes),
						D3D12_RESOURCE_STATE_GENERIC_READ,
						nullptr,
						IID_PPV_ARGS(vertexBuffer.GetAddressOf())
					);

				CD3DX12_RANGE readRange{ 0, 0 };
				void * mappedPtr = nullptr;
				vertexBuffer->Map(0, &readRange, &mappedPtr);
				memcpy(mappedPtr, data, sizeInBytes);
				vertexBuffer->Unmap(0, nullptr);

				vertexBufferView.BufferLocation = vertexBuffer->GetGPUVirtualAddress();
				vertexBufferView.SizeInBytes = sizeInBytes;
				vertexBufferView.StrideInBytes = stride;
			}
			
			virtual void Draw(ID3D12GraphicsCommandList * commandList) override {
				commandList->IASetPrimitiveTopology(topology);
				commandList->IASetVertexBuffers(0, 1, &vertexBufferView);
				commandList->DrawInstanced(vertexCount, 1, 0, 0);
			}
	
		GG_ENDCLASS

		GG_SUBCLASS(IndexedGeometry, Geometry)
		protected:
			com_ptr<ID3D12Resource> vertexBuffer;
			com_ptr<ID3D12Resource> indexBuffer;
			D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
			D3D12_INDEX_BUFFER_VIEW indexBufferView;
			unsigned int indexCount;
		public:

			IndexedGeometry() {
				ASSERT(false, "not implemented");
			}

			virtual void Draw(ID3D12GraphicsCommandList * commandList) override {
				commandList->IASetPrimitiveTopology(topology);
				commandList->IASetIndexBuffer(&indexBufferView);
				commandList->IASetVertexBuffers(0, 1, &vertexBufferView);
				commandList->DrawIndexedInstanced(indexCount, 1, 0, 0, 0);
			}

		GG_ENDCLASS

	}
}

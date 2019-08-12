#pragma once

#include "Common.h"

namespace Egg {

	class Texture {
	public:
		com_ptr<ID3D12Resource> resource;
		com_ptr<ID3D12Resource> uploadResource;
		Texture() : resource{ nullptr }, uploadResource{ nullptr } { }

		// copy-and-swap idiom (c++11)
		Texture & operator=(Texture t) {
			std::swap(resource, t.resource);
			std::swap(uploadResource, t.uploadResource);
			return *this;
		}

		Texture(com_ptr<ID3D12Resource> && resource, com_ptr<ID3D12Resource> && uploadResource) :
			resource{ std::move(resource) },
			uploadResource{ std::move(uploadResource) } {

		}

		void InitializeOnFirstFrame(ID3D12GraphicsCommandList * commandList) {
			CD3DX12_TEXTURE_COPY_LOCATION dst{ resource.Get(), 0 };
			D3D12_PLACED_SUBRESOURCE_FOOTPRINT psf;
			psf.Offset = 0;
			psf.Footprint.Depth = 1;
			psf.Footprint.Height = 512;
			psf.Footprint.Width = 512;
			psf.Footprint.RowPitch = 512 * 4;
			psf.Footprint.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			CD3DX12_TEXTURE_COPY_LOCATION src{ uploadResource.Get(), psf };
			commandList->CopyTextureRegion(&dst, 0, 0, 0, &src, nullptr);
			commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(resource.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ));
		}

		void AfterFirstFrame() {
			uploadResource.Reset();
		}


	};

}

#pragma once

#include "Common.h"

namespace Egg {

	class Texture {
		com_ptr<ID3D12Resource> resource;
		com_ptr<ID3D12Resource> uploadResource;
		D3D12_RESOURCE_DESC resourceDesc;
	public:
		Texture();

		// copy-and-swap idiom (c++11)
		Texture & operator=(Texture t);

		Texture(com_ptr<ID3D12Resource> && resource, com_ptr<ID3D12Resource> && uploadResource, D3D12_RESOURCE_DESC resourceDesc);

		void UploadResource(ID3D12GraphicsCommandList * commandList);

		void ReleaseUploadResources();

		ID3D12Resource * operator->() {
			return resource.Get();
		}
	};

}

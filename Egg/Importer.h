#pragma once

#include "Mesh/Geometry.h"
#include "Texture.h"

namespace Egg {
	namespace Importer {

		Egg::Mesh::Geometry::P ImportSimpleObj(ID3D12Device * device, const std::string & filePath);

		Texture ImportTexture(ID3D12Device * device, const std::string & filePath);

	};
}


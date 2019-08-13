#pragma once

#include "Mesh/Geometry.h"
#include "Texture2D.h"

namespace Egg {
	namespace Importer {

		Egg::Mesh::Geometry::P ImportSimpleObj(ID3D12Device * device, const std::string & filePath);

		Texture2D ImportTexture2D(ID3D12Device * device, const std::string & filePath);

	};
}


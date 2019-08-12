#pragma once

#include "Mesh/Geometry.h"

namespace Egg {
	namespace Importer {

		Egg::Mesh::Geometry::P ImportSimpleObj(ID3D12Device * device, const std::string & filePath);

	};
}


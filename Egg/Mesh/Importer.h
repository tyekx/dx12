#pragma once

#include "Geometry.h"

namespace Egg {
	namespace Mesh {
		class Importer {
			~Importer() = delete;
			Importer() = delete;
		public:

			static Egg::Mesh::Geometry::P ImportSimpleObj(ID3D12Device * device, const std::string & filePath);

		};
	}
}


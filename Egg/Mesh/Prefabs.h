#pragma once

#include "Geometry.h"
#include "../Vertex.h"

namespace Egg {
	namespace Mesh {

		class Prefabs {
			Prefabs() = delete;
			~Prefabs() = delete;
		public:

			static Egg::Mesh::Geometry::P FullScreenQuad(ID3D12Device * device) {
				PNT_Vertex vertices[] = {
					{ { -1.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f } },
					{ {  1.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f } },
					{ { -1.0f,-1.0f, 0.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f } },
					{ { -1.0f,-1.0f, 0.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f } },
					{ {  1.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f } },
					{ { 1.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, -1.0f}, { 1.0f, 0.0f } }
				}; 


				unsigned int vertexBufferSize = sizeof(vertices);
				Egg::Mesh::Geometry::P geometry = Egg::Mesh::VertexStreamGeometry::Create(device, reinterpret_cast<void*>(vertices), vertexBufferSize, sizeof(PNT_Vertex));

				geometry->AddInputElement({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });
				geometry->AddInputElement({ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });
				geometry->AddInputElement({ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });

				return geometry;
			}

			static Egg::Mesh::Geometry::P UnitBox(ID3D12Device * device) {
				PNT_Vertex vertices[] = {
					{ { -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f } },
					{ { -0.5f,  0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f } },
					{ {  0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f } },
					{ {  0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f } },
					{ { -0.5f,  0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f } },
					{ {  0.5f,  0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f } },

					{ { -0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f,  0.0f }, { 0.0f, 0.0f } },
					{ { -0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f,  0.0f }, { 0.0f, 1.0f } },
					{ {  0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f,  0.0f }, { 1.0f, 0.0f } },
					{ {  0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f,  0.0f }, { 1.0f, 0.0f } },
					{ { -0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f,  0.0f }, { 0.0f, 1.0f } },
					{ {  0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f,  0.0f }, { 1.0f, 1.0f } },

					{ {  0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f,  0.0f }, { 0.0f, 0.0f } },
					{ {  0.5f,  0.5f, -0.5f }, { 1.0f, 0.0f,  0.0f }, { 0.0f, 1.0f } },
					{ {  0.5f, -0.5f, 0.5f }, { 1.0f, 0.0f,  0.0f }, { 1.0f, 0.0f } },
					{ {  0.5f, -0.5f, 0.5f }, { 1.0f, 0.0f,  0.0f }, { 1.0f, 0.0f } },
					{ {  0.5f,  0.5f, -0.5f }, { 1.0f, 0.0f,  0.0f }, { 0.0f, 1.0f } },
					{ {  0.5f,  0.5f, 0.5f }, { 1.0f, 0.0f,  0.0f }, { 1.0f, 1.0f } },

					{ {  0.5f, -0.5f, 0.5f }, { 0.0f, 0.0f,  1.0f }, { 0.0f, 0.0f } },
					{ {  0.5f,  0.5f, 0.5f }, { 0.0f, 0.0f,  1.0f }, { 0.0f, 1.0f } },
					{ { -0.5f, -0.5f, 0.5f }, { 0.0f, 0.0f,  1.0f }, { 1.0f, 0.0f } },
					{ { -0.5f, -0.5f, 0.5f }, { 0.0f, 0.0f,  1.0f }, { 1.0f, 0.0f } },
					{ {  0.5f,  0.5f, 0.5f }, { 0.0f, 0.0f,  1.0f }, { 0.0f, 1.0f } },
					{ { -0.5f,  0.5f, 0.5f }, { 0.0f, 0.0f,  1.0f }, { 1.0f, 1.0f } },

					{ { -0.5f, -0.5f, 0.5f }, { 0.0f, -1.0f,  0.0f }, { 0.0f, 0.0f } },
					{ { -0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f,  0.0f }, { 0.0f, 1.0f } },
					{ {  0.5f, -0.5f, 0.5f }, { 0.0f, -1.0f,  0.0f }, { 1.0f, 0.0f } },
					{ {  0.5f, -0.5f, 0.5f }, { 0.0f, -1.0f,  0.0f }, { 1.0f, 0.0f } },
					{ { -0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f,  0.0f }, { 0.0f, 1.0f } },
					{ {  0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f,  0.0f }, { 1.0f, 1.0f } },

					{ {  -0.5f, -0.5f, 0.5f }, { -1.0f, 0.0f,  0.0f }, { 0.0f, 0.0f } },
					{ {  -0.5f,  0.5f, 0.5f }, { -1.0f, 0.0f,  0.0f }, { 0.0f, 1.0f } },
					{ {  -0.5f, -0.5f, -0.5f }, { -1.0f, 0.0f,  0.0f }, { 1.0f, 0.0f } },
					{ {  -0.5f, -0.5f, -0.5f }, { -1.0f, 0.0f,  0.0f }, { 1.0f, 0.0f } },
					{ {  -0.5f,  0.5f, 0.5f }, { -1.0f, 0.0f,  0.0f }, { 0.0f, 1.0f } },
					{ {  -0.5f,  0.5f, -0.5f }, { -1.0f, 0.0f,  0.0f }, { 1.0f, 1.0f } }
				};


				unsigned int vertexBufferSize = sizeof(vertices);
				Egg::Mesh::Geometry::P geometry = Egg::Mesh::VertexStreamGeometry::Create(device, reinterpret_cast<void*>(vertices), vertexBufferSize, sizeof(PNT_Vertex));

				geometry->AddInputElement({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });
				geometry->AddInputElement({ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });
				geometry->AddInputElement({ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });

				return geometry;
			}

		};

	}
}

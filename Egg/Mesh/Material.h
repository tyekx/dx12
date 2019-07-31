#pragma once

#include "../Common.h"

namespace Egg {
	namespace Mesh {

		GG_CLASS(Material)

			com_ptr<ID3D12PipelineState> pipelineState;

			void Apply(ID3D12GraphicsCommandList * commandList) {
				commandList->SetPipelineState(pipelineState.Get());
			}


		GG_ENDCLASS

	}
}

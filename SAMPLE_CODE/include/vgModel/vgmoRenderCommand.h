#pragma once

#include <vgKernel/vgkRenderCommand.h>
#include <vgModel/vgmoModelManager.h>

namespace vgModel
{
	class ModelRenderCommand : public vgKernel::RenderCommand
	{
	public:
		ModelRenderCommand() : vgKernel::RenderCommand(VG_RP_MODEL_RENDER) {}

		inline virtual bool render() 
		{
			vgModel::ModelManager::getSingleton().render();

			return true;
		}
	};
}
#pragma once

#include <vgkernel/vgkRenderCommand.h>
#include <vgKernel/vgkRendererManager.h>

namespace vgKernel
{
	class RenderMngBegin : public vgKernel::RenderCommand
	{
	public:
		RenderMngBegin() : RenderCommand(VG_RP_RENDERMNG_BEGIN) {}

		inline virtual bool render()
		{
			vgKernel::RendererManager::getSingleton().renderBegin();

			return true;
		}
	};

	class RenderMngEnd : public vgKernel::RenderCommand
	{
	public:
		RenderMngEnd () : RenderCommand(VG_RP_RENDERMNG_END) {}

		inline virtual bool render()
		{
			vgKernel::RendererManager::getSingleton().renderEnd();

			return true;
		}
	};
}
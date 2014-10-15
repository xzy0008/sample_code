#pragma once

#pragma once

#include <vgKernel/vgkRenderCommandPriority.h>
#include <vgKernel/vgkRenderCommand.h>
#include <vgKernel/vgkRenderCommandManager.h>
#include <vgAsyn/vgaMainThreadMessageManager.h>

namespace vgAsyn
{
	class AsynBeginCommand : public vgKernel::RenderCommand
	{
	public:
		AsynBeginCommand() : vgKernel::RenderCommand(VG_RP_ASYN_BEGIN){}

		inline virtual bool render()
		{
	 		vgAsyn::MainThreadMessageManager::getSingleton().renderBegin();
	 
	 		vgAsyn::MainThreadMessageManager::getSingleton().doRequests();
		
			return true;
		}
	};
}
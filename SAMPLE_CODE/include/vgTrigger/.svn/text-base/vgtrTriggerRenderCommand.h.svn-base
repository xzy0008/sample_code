#pragma once

#include <vgKernel/vgkRenderCommand.h>
#include <vgTrigger/vgtrTriggerManager.h>
#include <vgTrigger/vgtrDefinition.h>

namespace vgTrigger
{
	class TriggerRenderCommand : public vgKernel::RenderCommand
	{
	public:
		TriggerRenderCommand() : vgKernel::RenderCommand(VG_RP_TRIGGER) {}

		inline virtual bool render() 
		{
			vgTrigger::TriggerManager::getSingleton().checkOnEveryFrame();

			return true;
		}
	};
}
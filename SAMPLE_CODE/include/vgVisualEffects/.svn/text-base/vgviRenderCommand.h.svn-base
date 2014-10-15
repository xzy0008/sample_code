#pragma once

#include <vgKernel/vgkRenderCommandPriority.h>
#include <vgKernel/vgkRenderCommand.h>
#include <vgKernel/vgkRenderCommandManager.h>
#include <vgVisualEffects/vgviFogManager.h>
#include <vgVisualEffects/vgviBackgroundManager.h>

namespace vgVisualEffects
{
	class BackGroundRenderCommand : public vgKernel::RenderCommand
	{
	public:
		BackGroundRenderCommand() : vgKernel::RenderCommand(VG_RP_VISUALEFFECT_BK){}
		virtual ~BackGroundRenderCommand(){}

		inline virtual bool render()
		{
			vgVisualEffects::BackgroundManager::getSingleton().renderBegin();
			
			return true;
		}
	};

	class FogRenderCommand : public vgKernel::RenderCommand
	{
	public:
		FogRenderCommand() : vgKernel::RenderCommand(VG_RP_VISUALEFFECT_FOG) {}
		
		inline virtual bool render()
		{
			vgVisualEffects::FogManager::getSingleton().renderBegin();

			return true;
		}
	};

}
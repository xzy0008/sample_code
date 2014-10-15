#pragma once

#include <vgKernel/vgkRenderCommand.h>
#include <vgLogo/vgloLogoManager.h>
#include <vgKernel/vgkRenderCommandPriority.h>

namespace vgLogo
{
	class LogoRenderCommand : public vgKernel::RenderCommand
	{
	public:
		LogoRenderCommand() : vgKernel::RenderCommand(VG_RP_LOGO_RENDER){}

		inline virtual bool render()
		{
			LogoManager::getSingleton().renderAllLogo();

			return true;
		}
	};

}
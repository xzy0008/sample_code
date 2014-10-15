#pragma once

#include <vgkernel/vgkRenderCommand.h>
#include <vgKernel/vgkPluginManager.h>

namespace vgKernel
{
	class PluginRenderAll : public vgKernel::RenderCommand
	{
	public:
		PluginRenderAll() : RenderCommand(VG_RP_PLUGIN_RENDER) {}

		inline virtual bool render()
		{
			vgKernel::PluginManager::getSingleton().renderAllPlugins();

			return true;
		}
	};
}
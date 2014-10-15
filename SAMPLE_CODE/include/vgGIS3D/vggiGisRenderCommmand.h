#pragma once

#include <vgKernel/vgkRenderCommand.h>
#include <vgGIS/vgGisManager.h>

namespace vgGIS3D
{
	class ContourRenderCommand : public vgKernel::RenderCommand
	{
	public:
		ContourRenderCommand() : vgKernel::RenderCommand(VG_RP_GIS_CONTOUR){}

		inline virtual bool render()
		{
			ContourManager::getSingleton().render();

			return true;
		}
	};

	class GisRenderCommand : public vgKernel::RenderCommand
	{
	public:
		GisRenderCommand() : vgKernel::RenderCommand(VG_RP_GIS_RENDER) {}

		inline virtual bool render()
		{
			vgGIS3D::GisManager::getSingleton().renderGisElements();
		
			return true;
		}
	};
}
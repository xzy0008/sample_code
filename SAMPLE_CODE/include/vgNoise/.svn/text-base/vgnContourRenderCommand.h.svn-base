#pragma once

#include <vgKernel/vgkRenderCommand.h>
#include <vgNoise/vgnNoiseManager.h>


class ContourRenderCommand : public vgKernel::RenderCommand
{
public:
	ContourRenderCommand() : vgKernel::RenderCommand(VG_RP_CONTOUR_RENDER){}

	inline virtual bool render()
	{
		vgNoise::NoiseManager::getSingleton().RenderNoise();

		return true;
	}
};

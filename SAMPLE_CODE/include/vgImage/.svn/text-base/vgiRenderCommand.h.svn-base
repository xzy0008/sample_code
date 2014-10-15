#pragma once

#include <vgKernel/vgkRenderCommand.h>
#include <vgImage/vgiTextureIoRequestDispatcher.h>

namespace vgImage
{
	class TextureIoCommand : public vgKernel::RenderCommand
	{
	public:
		TextureIoCommand ()
			: vgKernel::RenderCommand(VG_RP_TEX_IODISPATCHER){}
		
		inline virtual bool render()
		{
			vgImage::TextureIoRequestDispatcher::getSingleton().dealWithUpdateInfoEveryFrame();
			
			return true;
		}
	};
}
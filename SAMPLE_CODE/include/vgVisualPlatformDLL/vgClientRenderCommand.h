#include <vgKernel/vgkRenderCommand.h>
#include <vgKernel/vgkRendererManager.h>
#include <vgMesh/vgmMesh.h>

class ClientRenderMngRender : public vgKernel::RenderCommand
{
public:
	ClientRenderMngRender() :  vgKernel::RenderCommand(VG_RP_CLIENT_RENDERMNG_RENDER) {}

	// 为提高效率写成inline，实现可放入CPP文件
	inline virtual bool render()
	{
		
		return true;
	}
};

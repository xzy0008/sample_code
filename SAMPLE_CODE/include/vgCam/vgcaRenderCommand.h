#include <vgCam/vgcaCamManager.h>
#include <vgKernel/vgkRenderCommand.h>
#include <vgKernel/vgkRenderCommandPriority.h>

namespace vgCam
{
	// 渲染至AVI 开始
	class RenderAviBegin : public vgKernel::RenderCommand
	{
	public:
		RenderAviBegin() : RenderCommand(VG_RP_CAM_AVI_BEGIN) {}

		inline virtual bool render()
		{
			vgCam::CamManager::getSingleton().recordAviBegin();
			
			return true;
		}
	};

	// 渲染至AVI 结束
	class RenderAviEnd : public vgKernel::RenderCommand
	{
	public:
		RenderAviEnd() : RenderCommand(VG_RP_CAM_AVI_END) {}

		inline virtual bool render()
		{
			vgCam::CamManager::getSingleton().recordAviEnd();
			
			return true;
		}
	};

	// 相机设置
	class RenderBegin : public vgKernel::RenderCommand
	{
	public:

		RenderBegin() : RenderCommand(VG_RP_CAM_BEGIN) {}

		inline virtual bool render()
		{
			/*第一：视景体 设定好投影矩阵和模型观察矩阵，为绘制作准备***/
			vgCam::CamManager::getSingleton().setupViewFrustum();

			/*第二：相机 ***********************************************/
			vgCam::CamManager::getSingleton().setupCamera();
			vgCam::CamManager::getSingleton().updateCurrentFrustum();
			vgCam::CamManager::getSingleton().renderVcr();

//			VGK_CHECK_OPENGL_ERROR();
			
			return true;
		}
	};
}
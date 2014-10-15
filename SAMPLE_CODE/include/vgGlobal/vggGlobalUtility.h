

#ifndef __VGGLOBALUTILITY_H__
#define __VGGLOBALUTILITY_H__

#include <vgGlobal/vgglDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkRenderer.h>

namespace vgGlobal{

	//using namespace vgXXX;
	
	
	class	VGGL_EXPORT GlobalUtility
	{
	public:
		GlobalUtility();
		~GlobalUtility();

	public:
		static void attachRendererToTerrain( vgKernel::Renderer* renderer , 
			const bool& update_selectmgr );

		static void attachRendererToTerrain( vgKernel::RendererQueue* renderers ,
			const bool& update_selectmgr  );
		
		static vgKernel::Renderer*	getSelectedRendererByType( vgKernel::RendererType type);


		//add by zzy 2009/10/23 供给View类中消息响应的接口
		static  bool  publishProject();     //生成EXE--VGMSGBOX2暂时未提取出来
		static  bool  reset();              //重置场景--有Bug暂时未提取
		static  bool  exitProgram();        //退出平台--无此相关函数（找不到ID）

		static  bool  renderEntityOrLine(); //实体或线框显示
		static  bool  updateRenderEntityOrLine();

  		static  bool  showAboutDlg();       //显示关于VR-GIS对话框

		//Keyboard input 
		static  bool responseLButtonDblClk(UINT nFlags, CPoint point, CWnd* pwnd );
		static  bool responseLButtonDown(UINT nFlags, CPoint point);
		static  bool responseLButtonUp(UINT nFlags, CPoint point);

		//原来GlobalFacade类中的两个接口转移至这里2009/10/29 8:52 zzy
		static  bool importVtrFile( const String& file_name);        //导入vtr文件
		static  bool importVmdFileOnly( const String& file_name);    //导入vmd文件

	private:
		static bool m_bIsWireLine;            //标志是否以线框方式渲染

	};
}//namespace vgGlobal

#endif//__VGGLOBALUTILITY_H__
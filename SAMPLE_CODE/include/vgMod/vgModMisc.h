

#ifndef __VGMODMISC_H__
#define __VGMODMISC_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSingleton.h>
#include <vgCore/vgPrerequisites.h>

#include <vgSmallMap.h>
#include <vgHawkeyePath.h>

#include <vgDlgTreeDis.h>
#include <vgDlgTreeSet.h>

#include <vgDlgDynamicBillboardNode.h>
#include <vgKernel/vgkRenderCommandManager.h>
#include <vgKernel/vgkInputSystem.h>

namespace vgMod{

	//using namespace vgXXX;
	
	//using namespace vgCore;


	class	VGDEP_EXPORT	ModMisc : 
		public vgKernel::Singleton<ModMisc>,
		public vgKernel::InputHandler
	{
		friend class vgKernel::Singleton<ModMisc>;

	public:
		ModMisc();
		~ModMisc();

	protected:
		virtual bool initialise();
		virtual bool shutdown();
		
		vgKernel::RenderCommand  *m_pMiscRenderCommand;

	public:
		vgCore::SmallMap*		getSmallMap();

		vgCore::HawkeyePath*	getHawkeyePath();

		void	setStatus(int status);

		int		getStatus();

		DlgTreeSet*	getDlgTreeSet();

		DlgTreeDis* getDlgTreeDis();

		int	getCurrentMode();
		void	setCurrentMode( int nMode);

		void reset();

		DlgDynamicBillboardNode* getDlgDynBillboard();

	public:
		void	renderMisc();

		void	renderLines();

		void	renderHawkeye();

		void	renderPath();

		void	addPlantPosition(CPoint &point);

		//add by ZhouZY 2009-11-5 22:13
		virtual void OnKeyDown(int keyCode);

		void  StopCreate();

		void	lButtonDown( UINT nFlags, CPoint point);
		void	lButtonDblClk(UINT nFlags, CPoint point, /*GLfloat gldaspect, */CWnd *pwnd);

		bool	initialize(HWND &hWnd);

		Vector3Vec* getPlantPosForDrawLine()
		{
			return &m_vPlantPosForDrawLine;
		}

		//ZhouZY add 2009-11-17 20:26 
		//清空TreeDis对话框类中的坐标点数据
		void clearTreeDisPosVec();

	private:
		int		m_nCurrentMode;
		
		// 鹰眼路线
		vgCore::SmallMap* m_pSmallMap;

		// 鹰眼图
		vgCore::HawkeyePath* m_pHawkeyePath;

		// Billboard植树
		DlgTreeSet*		m_dlgTreeSet;
		DlgTreeDis*		m_dlgTreeDis;
		Vector3Vec      m_vPlantPosForDrawLine; //ZhouZY add 2009-11-7  0:09

		// DymamicBillboard
		DlgDynamicBillboardNode*  m_dlgdynbillboard;


	};

	class ModMiscRenderCommand : public vgKernel::RenderCommand
	{
	public:
		ModMiscRenderCommand() : vgKernel::RenderCommand(VG_RP_MISC_RENDER) {}
	public:
		inline virtual bool render()
		{
			ModMisc::getSingleton().renderMisc();

			return true;
		}
	};
}//namespace vgMod

#endif//__VGMODMISC_H__

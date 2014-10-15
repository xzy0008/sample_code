
#ifndef __VGKINPUTSYSTEM_H__
#define __VGKINPUTSYSTEM_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSingleton.h>
#include <vgKernel/vgkSingletonLifeTimeDefine.h>
#include <vgKernel/vgkInputCodeDef.h>
#include <vgKernel/vgkTrace.h>
#include <vgKernel/vgkDirectInputDefinition.h>

#include <vgKernel/vgkRenderCommand.h>

namespace vgKernel {
	/**
		@date 	2008/08/20  11:09	
		@author  ZSC
	
		@brief 	
	
		@see    
	*/

	class  VGK_EXPORT InputHandler
	{
	public:
		InputHandler()
		{
			statusFlag = 0;
		}
		virtual ~InputHandler()
		{

		}

		void SetHandleStatus(DWORDLONG flag)
		{
			statusFlag = flag;
		}

		void AddHandleStatus(DWORDLONG flag)
		{
			statusFlag |= flag;
		}

		void RemoveHandleStatus(DWORDLONG flag)
		{
			statusFlag &= (~flag);
		}

		DWORDLONG GetHandleStatus()
		{
			return statusFlag;
		}

		virtual void OnKeyDown(int keyCode) {}
		virtual void OnChar(int keyCode) {}
		virtual void OnMouseMove(UINT nFlags, CPoint position) {}
		virtual void OnLButtonDown(UINT nFlags, CPoint position) {}
		virtual void OnLButtonUp(UINT nFlags, CPoint position) {}
		virtual void OnLButtonDbClick(UINT nFlags, CPoint position) {}
		virtual void OnMouseWheel(UINT nFlags, short zDelta, CPoint pt){}
		virtual void OnRBottonDown(UINT nFlags, CPoint position) {}
		virtual void OnRBottonUp(UINT nFlags, CPoint position) {}
	protected:

		DWORDLONG statusFlag;

	private:

	};


	class  VGK_EXPORT InputSystem : public Singleton<InputSystem>
	{
	friend class Singleton<InputSystem>;
	public:
		bool UpdateInput();

		bool initialise(const HINSTANCE& appInstance, const HWND& hwnd);

		//void SetClientHwnd(HWND hWnd) { m_clientHwnd = hWnd; };
	
		bool registerHandle(InputHandler *handle);

		bool removeHandle(InputHandler *handle);
		
		void SetEnable(bool enable) { m_enable = enable; }

		bool GetEnable() { return m_enable; }  //add by ZhouZY 2009-11-4 15:48

		void OnMouseMove(UINT nFlags, CPoint position);

		void OnLButtonDown(UINT nFlags, CPoint position);

		void OnLButtonUp(UINT nFlags, CPoint position);

		void OnLButtonDbClick(UINT nFlags, CPoint position);

		void OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

		void OnRButtonDown(UINT nFlags, CPoint position);

		void OnRButtonUp(UINT nFlags, CPoint position);

	private:
		InputSystem();

		virtual~InputSystem();
		
	public:

		void AddHandleStatus( DWORDLONG flag )
		{
			statusFlag |= flag;
		}
		void RemoveHandleStatus( DWORDLONG flag )
		{
			statusFlag &= ( ~flag );
		}
		DWORDLONG CheckStatusValid( DWORDLONG flag )
		{
			return ( statusFlag & flag );
		}
		void setCurrentStatus( const DWORDLONG& status )
		{
			statusFlag = status;
		}
		
		void setDefaultStatus()
		{
			statusFlag = 0;

			// 初始的输入状态：相机和点选
			statusFlag |= VG_INPUTMODE_CAMERA;
			statusFlag |= VG_INPUTMODE_SELECT;
			statusFlag |= VG_INPUTMODE_UI;
		}


		void reset() { setDefaultStatus();}

	protected:
		bool initialise() { return true; }

		bool shutdown();
		
		vgKernel::RenderCommand *m_pUpdateCmd;

	private:
		bool					m_enable;

		LPDIRECTINPUT8			m_lpDI;	

		LPDIRECTINPUTDEVICE8	m_keyboard; 
		LPDIRECTINPUTDEVICE8	m_mouse;

		unsigned char			m_KeyStateBuffer[256];
		unsigned char			m_KeyLastStateBuffer[256];

		HWND					m_clientHwnd;
		
		DWORDLONG				statusFlag;

		std::vector<InputHandler*>	eventHanleList;
	};

	class UpdateInputCmd : public vgKernel::RenderCommand
	{
	public:

		UpdateInputCmd() : RenderCommand(VG_RP_UPDATEINPUT) {}
		inline virtual bool render()
		{
			vgKernel::InputSystem::getSingleton().UpdateInput();

			return true;
		}

	};
	
}// end of namespace vgKernel
	


#endif // end of __VGKINPUTSYSTEM_H__

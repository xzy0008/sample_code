

#ifndef __VGKDISSOLVEOBJECT_H__
#define __VGKDISSOLVEOBJECT_H__

#include <vgKernel/vgkForward.h>
#include <afxtempl.h>

namespace vgKernel {

	/**
	@date 	2009/12/21  22:37	
	@author  YuXin

	@brief 	纹理淡入淡出效果

	@see    
	*/

	class DissolveObject;
	typedef CMap<UINT,UINT,DissolveObject*,DissolveObject*> CTimerMap;

	class VGK_EXPORT DissolveObject
	{
	public:
		DissolveObject();
		virtual ~DissolveObject();


	public:

		//dissolvetype 1为淡入 2为淡出
		virtual void setDissolveState(const bool& dissolveable, const int& dissolvetype, const float& time);

		virtual int  getDissolveType(){return m_dissolveType;}

		virtual float getDissolveAlpha(){return m_alpha;}

		virtual bool isDissolveable(){return m_dissolveable;}

	private:

		void setTimer(UINT nElapse);

		void killTimer();

		static void CALLBACK timerProc(HWND hwnd,UINT uMsg,UINT idEvent,DWORD dwTime);

		void fadeIn();

		void fadeOut();

	private:

		UINT m_nTimerID;
		static CTimerMap m_sTimeMap;

		bool    m_dissolveable;
		int     m_dissolveType;//1为淡入，2为淡出
		float   m_alpha;
		float   m_alphaStep;

	};


}// end of namespace vgKernel
	


#endif // end of __VGKDISSOLVEOBJECT_H__
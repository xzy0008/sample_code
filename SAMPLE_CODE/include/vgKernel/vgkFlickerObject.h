

#ifndef __VGKFLICKEROBJECT_H__
#define __VGKFLICKEROBJECT_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkRgbaQuad.h>
#include <vgKernel/vgkColorVal.h>
#include <afxtempl.h>

namespace vgKernel {

	/**
	@date 	2009/12/21  22:37	
	@author  YuXin

	@brief 	纹理闪烁效果

	@see    
	*/
#define  GRADIENTSTEP            20.0

	class FlickerObject;
	typedef CMap<UINT,UINT,FlickerObject*,FlickerObject*> CTimerMapFlicker;

	class VGK_EXPORT FlickerObject
	{
	public:
		FlickerObject();
		virtual ~FlickerObject();


	public:

		//设置此接口开启闪烁
		virtual void setFlickerState(const bool& flickerstate, const int& flickertype, const float & time);

		virtual bool isFlickered(){ return m_bFlickered; }

	public:

		void setCurrentColor( RgbaQuad color ){ m_currentColor = color; }

		RgbaQuad getCurrentColor(){ return m_currentColor; }

		void setForeColor( BYTE r,BYTE g,BYTE b, BYTE a );

		RgbaQuad getForeColor(){ return m_foreColor; }

		void setBackColor( BYTE r,BYTE g,BYTE b, BYTE a );

		RgbaQuad getBackColor(){ return m_backColor; }

		//简单模式下true为前景色，false为后景色；渐变模式下true为颜色递增，false为颜色递减
		void setColorState(bool state){ m_colorState = state; }

		bool getColorState(){ return m_colorState; }
		
		//1代表简单颜色交替，2代表渐变颜色交替
		void setFlickerType(int type){ m_nflickerType = type; }	

		int getFlickerType(){ return m_nflickerType; }

		void initializeState();

	private:

		void setTimer(UINT nElapse);

		void killTimer();

		static void CALLBACK timerProc(HWND hwnd,UINT uMsg,UINT idEvent,DWORD dwTime);

		//渐变效果
		RgbaQuad getGradientStep();

		void stepIt();

		//闪烁效果
		void flickerIt();

	private:

		UINT m_nTimerID;
		static CTimerMapFlicker m_sTimeMapFlicker;

		bool     m_bFlickered;
		int      m_nflickerType;

		RgbaQuad m_foreColor;
		RgbaQuad m_backColor;
		RgbaQuad m_currentColor;

		//标记渐变状态
		int      m_counter;
		bool     m_colorState;

		
	};


}// end of namespace vgKernel
	


#endif // end of __VGKFLICKEROBJECT_H__
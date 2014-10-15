
#include <vgStableHeaders.h>
#include <vgKernel/vgkFlickerObject.h>

namespace vgKernel {


	CTimerMapFlicker FlickerObject::m_sTimeMapFlicker;

	FlickerObject::FlickerObject()
		: m_foreColor(255,0,0,255),m_backColor(255,255,0,255)
	{
		m_bFlickered = false;
		m_nflickerType = 1;
		m_colorState = true;
		m_nTimerID = -1;

		initializeState();
	}

	FlickerObject::~FlickerObject()
	{
		killTimer();
	}

	void CALLBACK FlickerObject::timerProc(HWND hwnd,UINT uMsg,UINT idEvent,DWORD dwTime)
	{
		if (m_sTimeMapFlicker[idEvent]->isFlickered())
		{
			switch(m_sTimeMapFlicker[idEvent]->getFlickerType())
			{
			case 1:
				m_sTimeMapFlicker[idEvent]->flickerIt();
				break;

			case 2:
				m_sTimeMapFlicker[idEvent]->stepIt();
				break;

			default:
				break;
			}
		}
		else
		{
			m_sTimeMapFlicker[idEvent]->killTimer();
		}

	}

	void FlickerObject::setTimer(UINT nElapse)
	{
		//保证每个实例仅维护一个定时器
		if (m_nTimerID != -1)
		{
			killTimer();
		}

		m_nTimerID = ::SetTimer(NULL,NULL,nElapse,timerProc);

		m_sTimeMapFlicker[m_nTimerID] = this;
	}

	void FlickerObject::killTimer()
	{
		::KillTimer(NULL,m_nTimerID);

		m_sTimeMapFlicker.RemoveKey(m_nTimerID);

		m_nTimerID = -1;
	}

	void FlickerObject::setFlickerState(const bool& flickerstate,const int& flickertype,const float& time)
	{ 
		m_bFlickered = flickerstate;

		m_nflickerType = flickertype;

		switch(m_nflickerType)
		{
		case 1:
			{
				setTimer(time);
			}
			break;

		case 2:
			{
				setTimer(time/GRADIENTSTEP);
			}
			break;

		default:
			break;
		}
	}

	RgbaQuad FlickerObject::getGradientStep()
	{
		RgbaQuad _gradientStep;

		_gradientStep.red = (m_backColor.red - m_foreColor.red)/GRADIENTSTEP;
		_gradientStep.green = (m_backColor.green - m_foreColor.green)/GRADIENTSTEP;
		_gradientStep.blue = (m_backColor.blue - m_foreColor.blue)/GRADIENTSTEP;
		_gradientStep.alpha = (m_backColor.alpha - m_foreColor.alpha)/GRADIENTSTEP;
	
		return _gradientStep;
	}

	void FlickerObject::stepIt()
	{
		if (m_colorState)
		{
			m_currentColor = m_currentColor + getGradientStep();

			m_counter++;

			if (m_counter > GRADIENTSTEP)
			{
				m_colorState = !m_colorState;
			}
		}
		else
		{
			m_currentColor = m_currentColor - getGradientStep();

			m_counter--;

			if (m_counter <= 1)
			{
				m_colorState = !m_colorState;
			}
		}
	}

	void FlickerObject::flickerIt()
	{
		if (m_colorState)
		{
			m_currentColor = m_foreColor;
		}
		else
		{
			m_currentColor = m_backColor;
		}

		m_colorState = !m_colorState;

	}

	void FlickerObject::initializeState()
	{
		m_currentColor = m_foreColor;
		m_counter = 0;
	}

	void FlickerObject::setForeColor( BYTE r,BYTE g,BYTE b, BYTE a )
	{
		m_foreColor = RgbaQuad(r,g,b,a);
		initializeState();
	}

	void FlickerObject::setBackColor( BYTE r,BYTE g,BYTE b, BYTE a )
	{
		m_backColor = RgbaQuad(r,g,b,a);
		initializeState();
	}

}// end of namespace vgKernel

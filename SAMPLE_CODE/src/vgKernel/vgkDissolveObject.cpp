
#include <vgStableHeaders.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkDissolveObject.h>

namespace vgKernel {


	CTimerMap DissolveObject::m_sTimeMap;

	DissolveObject::DissolveObject()
	{
		m_dissolveable = false;
		m_dissolveType = 1;
		m_alpha = 1.0f;
		m_alphaStep = 0.025f;

		m_nTimerID = -1;
	}

	DissolveObject::~DissolveObject()
	{
		killTimer();
	}

	void CALLBACK DissolveObject::timerProc(HWND hwnd,UINT uMsg,UINT idEvent,DWORD dwTime)
	{
		if (m_sTimeMap[idEvent]->isDissolveable())
		{
			switch(m_sTimeMap[idEvent]->getDissolveType())
			{
			case 1:
				m_sTimeMap[idEvent]->fadeIn();
				break;

			case 2:
				m_sTimeMap[idEvent]->fadeOut();
				break;

			default:
				break;
			}
		}
		else
		{
			m_sTimeMap[idEvent]->killTimer();	
		}

	}

	void DissolveObject::setTimer(UINT nElapse)
	{
		//保证每个实例仅维护一个定时器
		if (m_nTimerID != -1)
		{
			killTimer();
		}
		m_nTimerID = ::SetTimer(NULL,NULL,nElapse,timerProc);
		m_sTimeMap[m_nTimerID] = this;
	}

	void DissolveObject::killTimer()
	{
		::KillTimer(NULL,m_nTimerID);
		m_sTimeMap.RemoveKey(m_nTimerID);
		m_nTimerID = -1;
	}

	void DissolveObject::setDissolveState( const bool& dissolveable, const int& dissolvetype, const float& time )
	{
		m_dissolveable = dissolveable;
		m_dissolveType = dissolvetype;

		switch(m_dissolveType)
		{
		case 1:
			{
				if (m_dissolveable)
				{
					m_alpha = 0.0f;
					m_alphaStep = 10.0f/time;
					setTimer(10);
				}
				else
				{
					m_alpha = 1.0f;
				}
			}
			break;

		case 2:
			{
				if (m_dissolveable)
				{
					m_alpha = 1.0f;
					m_alphaStep = 10.0f/time;
					setTimer(10);
				}
				else
				{
					m_alpha = 1.0f;
				}
			}
			break;

		default:
			break;
		}
	}

	void DissolveObject::fadeIn()
	{
		if(m_alpha < 1.0f)
		{
			m_alpha += m_alphaStep;
		}
		else
		{
			m_dissolveable = false;
			m_alpha = 1.0f;
			killTimer();
		}

	}

	void DissolveObject::fadeOut()
	{
		if (m_alpha > 0) 
		{
			m_alpha -= m_alphaStep;
		}
		else 
		{
			m_alpha = 0.0f;
		}

	}

}// end of namespace vgKernel

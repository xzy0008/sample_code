


#ifndef __VGMOTIMER_H__
#define __VGMOTIMER_H__

#include <vgKernel/vgkForward.h>

	
namespace vgModel {

	/**
		@date 	2009/06/01  15:05	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	//-------------------------------------------------------------
	//                        Timer                              -
	// author: Evan Pipho (evan@codershq.com)                     -
	// date  : Jul 09, 2002                                       -
	//-------------------------------------------------------------
	class Timer
	{
	public:

		//Initialize the timer
		void initialise();

		//Get the FPS of the program baed on elapsed frames
		//float GetFPS(unsigned int uiFrames = 1);

		//Get the number of ms since last call
		unsigned int getMS();

		////Get the number of seconds since the last call
		//float GetSeconds();

	private:

		//multipling by this gives you time in seconds	
		float m_fInvTicksPerSec;
		//multipling by this gives you time in milliseconds
		float m_fInvTicksPerMs;
		//start time
		__int64 m_i64StartTime;
		__int64 m_i64LastTime;
	};

	//-------------------------------------------------------------
	//                     FUNCTIONS                              -
	//-------------------------------------------------------------
	//-------------------------------------------------------------
	//- initialise
	//- Initialize the timer
	//-------------------------------------------------------------
	inline void Timer::initialise()
	{
		__int64 i64Freq = 0;
		QueryPerformanceFrequency((LARGE_INTEGER *)&i64Freq);
		QueryPerformanceCounter((LARGE_INTEGER *)&m_i64StartTime);
		m_fInvTicksPerSec = (float)1/i64Freq;
		m_fInvTicksPerMs = (float)1000/i64Freq;
		m_i64LastTime = 0;
		getMS();
	}

	////-------------------------------------------------------------
	////- GetFPS
	////- Calulate the Frames Per Second of the application
	////-------------------------------------------------------------
	//inline float Timer::GetFPS(unsigned int uiFrames)
	//{
	//	static __int64 sLastTime = m_i64StartTime;
	//	__int64 i64NewTime = 0;
	//	float fElapsedSecs = 0;
	//	QueryPerformanceCounter((LARGE_INTEGER *)&i64NewTime);
	//	fElapsedSecs = (i64NewTime - sLastTime) * m_fInvTicksPerSec;
	//	sLastTime = i64NewTime;

	//	return (uiFrames / fElapsedSecs); 
	//}

	//-------------------------------------------------------------
	//- getMS
	//- Get the number of milliseconds since the last call to getMS
	//- or since the start of the timer.
	//-------------------------------------------------------------
	inline unsigned int Timer::getMS()
	{
		__int64 i64NewTime = 0;
		unsigned int uiMs;

		QueryPerformanceCounter((LARGE_INTEGER *)&i64NewTime);
		uiMs = (unsigned int)((i64NewTime - m_i64LastTime) * m_fInvTicksPerMs);
		m_i64LastTime = i64NewTime;
		return uiMs;
	}

	////-------------------------------------------------------------
	////- GetSeconds
	////- Get the number of seconds since the last call to GetSeconds
	////-------------------------------------------------------------
	//inline float Timer::GetSeconds()
	//{
	//	return (float)(getMS() * 0.001f);
	//}
	
	
}// end of namespace vgModel
	


#endif // end of __VGMOTIMER_H__
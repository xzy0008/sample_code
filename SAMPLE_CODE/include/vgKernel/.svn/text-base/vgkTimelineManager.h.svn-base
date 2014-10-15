




#ifndef __VGKTIMELINEMANAGER_H__
#define __VGKTIMELINEMANAGER_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSingleton.h>

#include "vgKernel/vgkTimelineObserver.h"

namespace vgKernel {


	/**
		@date 	2010/05/04  14:27	
		@author  YUXIN
	
		@brief 	
	
		@see    
	*/
	class  VGK_EXPORT TimelineManager :
		public vgKernel::Singleton<TimelineManager>,
		public vgKernel::TimelineWatcher
	{
	private:
		friend class vgKernel::Singleton<TimelineManager>;

	private:
		TimelineManager()
			: Singleton<TimelineManager>( VGK_SINGLETON_LEFE_TIMELINEMANAGER ) 
		{
// 			VGK_TRACE(_T("TimelineManager created."));
			m_curTime = TIMELINE_CURRENT;
		}
	public:
		virtual ~TimelineManager()
		{
// 			VGK_TRACE(_T("TimelineManager destroyed."));
		}

	protected:
		virtual bool initialise();

		virtual bool shutdown(){ return true; }
	

	public:
		int getCurrentTime() {return m_curTime;}

		void setCurrentTime(int _curTime);


	protected:
		int  m_curTime;


	};
}// end of namespace vgKernel
	


#endif // end of TimelineManager
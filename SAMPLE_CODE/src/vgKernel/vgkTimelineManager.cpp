




#include <vgStableHeaders.h>
#include <vgKernel/vgkTimelineManager.h>


namespace vgKernel {
	
	
	bool TimelineManager::initialise()
	{
		TimelineWatcher::notifyTargetsOnEvent(m_curTime);
		return true;
	}
	
	void TimelineManager::setCurrentTime(int _curTime)
	{
		m_curTime = _curTime;

		TimelineWatcher::notifyTargetsOnEvent(m_curTime);
	}

}// end of namespace vgKernel

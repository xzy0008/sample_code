#pragma once

#include <vector>

using std::vector;

#define  TIMELINE_START         1900
#define  TIMELINE_END           2100
#define  TIMELINE_CURRENT       2010

namespace vgKernel
{

	class TimelineTarget
	{
	public:
		TimelineTarget()
		{
			m_bEvent = true;
			m_startTime = TIMELINE_START;
			m_endTime = TIMELINE_END;
		}

		virtual ~TimelineTarget()
		{

		}

		virtual void onEvent(int _curTime) 
		{
			//时间起至范围内显示，范围外不显示
			if ( (m_startTime <= _curTime) && (_curTime <= m_endTime) )
			{
				m_bEvent = true;
			}
			else 
			{
				m_bEvent = false;
			}
		}

		virtual bool getEventState() { return m_bEvent; }
		virtual void setEventState(bool& val) { m_bEvent = val; }

		virtual int  getStartTimeVal() { return m_startTime; }
		virtual void setStartTimeVal(int& val) { m_startTime = val; }
		
		virtual int  getEndTimeVal() { return m_endTime; }
		virtual void setEndTimeVal(int& val) { m_endTime = val; }

	protected:
		
		int  m_startTime;
		int  m_endTime;

		bool  m_bEvent;
	};



	class TimelineWatcher 
	{
	public:

		TimelineWatcher()
		{

		}

		virtual ~TimelineWatcher()
		{

		}

	public:

		virtual bool registerTarget(TimelineTarget *pTarget)
		{
			for (int i=0; i<m_timeTargets.size(); i++)
			{
				if (m_timeTargets[i] == pTarget)
				{
					return false;
				}
			}
			m_timeTargets.push_back(pTarget);

			return true;
		}

		virtual bool unregisterTarget(TimelineTarget *pTarget)
		{
			vector <TimelineTarget*>::iterator iter = m_timeTargets.begin();
			vector <TimelineTarget*>::iterator iter_end = m_timeTargets.end();

			while (iter != m_timeTargets.end())
			{
				if ((*iter) == pTarget)
				{
					iter = m_timeTargets.erase(iter);

					continue ;
				}

				iter ++;
			}

			return true;
		}

		virtual void notifyTargetsOnEvent(int _curTime)
		{
			for (int i=0; i<m_timeTargets.size(); i++)
			{
				if (m_timeTargets[i] != NULL)
				{
					m_timeTargets[i]->onEvent(_curTime);
				}
			}
		}

	protected:
		vector<TimelineTarget*> m_timeTargets;	

	};
}
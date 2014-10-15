#pragma once

#include <vector>

using std::vector;

namespace vgKernel
{
	class VGK_EXPORT Observer
	{
	public:
		virtual void onEvent(unsigned int eventId, void *param) {}
	};


	class VGK_EXPORT ObserverTarget
	{
	public:
		ObserverTarget() {}
		virtual ~ObserverTarget() {};

		virtual bool registerObserver(Observer *pObserver)
		{
			for (int i=0; i<m_observerVec.size(); i++)
			{
				if (m_observerVec[i] == pObserver)
				{
					return false;
				}
			}
			m_observerVec.push_back(pObserver);

			return true;
		}

		virtual bool removeObserver(Observer *pObserver)
		{
			for (int i=0; i<m_observerVec.size(); i++)
			{
				if (m_observerVec[i] == pObserver)
				{
					return false;
				}
			}
			m_observerVec.push_back(pObserver);

			return true;
		}

	protected:
		vector<Observer*> m_observerVec;	
	};

}




#ifndef __VGKRENDEREROBSERVER_H__
#define __VGKRENDEREROBSERVER_H__


#include <vgKernel/vgkForward.h>

namespace vgKernel {

	enum ObserverEvent
	{
		VG_OBS_PROPCHANGED,
		VG_OBS_NEWMESHITEM,
		VG_OBS_SELECTCHAGNED,
		VG_OBS_ADDSELECTION,
		VG_OBS_GROUPUPDATE,
		VG_OBS_INVALIDATE_PROPERTIES, // 用于刷新右侧属性窗口 

		VG_MOD_NODEEDIT,
		VG_OBS_SIZ
	};


	class RendererObserver
	{
	public:
		RendererObserver()
		{

		}
		virtual ~RendererObserver()
		{

		}

		virtual void onChanged(int eventId, void *param) = 0;

		virtual bool onDelete() = 0;
	};

	class ObserverContainer
	{
	public:
		ObserverContainer()
		{

		}
		virtual ~ObserverContainer()
		{

		}

		void notifyOberversOnDelete()
		{
				for (int i=0; i<m_observers.size(); i++)
				{
					if (m_observers[i] != NULL)
					{
						m_observers[i]->onDelete();
					}
				}
		}

		virtual void registerObserver(RendererObserver* observer)
		{
			for (int i=0; i<m_observers.size(); i++)
			{
				if (m_observers[i] == observer)
				{
					return ;
				}				
			}
			m_observers.push_back(observer);
			
		}

		virtual void notifyOberversOnEvent(int eventId, void *param)
		{
			for (int i=0; i<m_observers.size(); i++)
			{
				if (m_observers[i] != NULL)
				{
					m_observers[i]->onChanged(eventId, param);
				}
			}
		}
		
		virtual void unregisterObserver(RendererObserver* observer)
		{
 		//	for (int i=0; i<m_observers.size(); i++)
 		//	{
 		//		if (m_observers[i] == observer)
 		//		{
 		//			m_observers[i] = NULL;
 
 		//			return ;
 		//		}
			//}

			std::vector <RendererObserver*>::iterator iter = m_observers.begin();
			std::vector <RendererObserver*>::iterator iter_end = m_observers.end();

			while (iter != m_observers.end())
			{
				if ((*iter) == observer)
				{
					iter = m_observers.erase(iter);
					
					continue ;
				}

				iter ++;
			}

		}
	protected:
		std::vector <RendererObserver*> m_observers;
	};


}// end of namespace vgKernel




#endif // end of __VGKRENDEREROBSERVER_H__
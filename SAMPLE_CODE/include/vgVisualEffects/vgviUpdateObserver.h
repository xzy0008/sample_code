


#ifndef __VGVIUPDATEOBSERVER_H__
#define __VGVIUPDATEOBSERVER_H__


#include <vgVisualEffects/vgviDefinition.h>
#include <vgKernel/vgkForward.h>

	
namespace vgVisualEffects {

	/**
		@date 	2008/09/11  22:24	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class UpdateObserver
	{
	public:
		UpdateObserver()
		{
			
		}
		~UpdateObserver()
		{
			
		}
	
	
		virtual void onUpdate() = 0;
	
	
	};
	

	class Updater
	{
	public:
		Updater()
		{
			
		}
		~Updater()
		{
			
		}

		virtual void unregisterObs(UpdateObserver* observer)
		{
			for (int i=0; i<_observers.size(); i++)
			{
				if (_observers[i] == observer)
				{
					_observers[i] = NULL;
					return ;
				}
			}
		}	
		virtual void registerObs( UpdateObserver* obs )
		{
			_observers.push_back( obs );
		}

		virtual void clearObs()
		{
			_observers.clear();
		}

		void notfiyUpdate()
		{
			std::vector<UpdateObserver*>::iterator iter = _observers.begin();
			std::vector<UpdateObserver*>::iterator iter_end = _observers.end();

			for ( ; iter != iter_end ; ++ iter )
			{
				if ((*iter) != NULL)
				{
					(*iter)->onUpdate();
				}
			}
		}
	
	private:


		std::vector<UpdateObserver*> _observers;

	
	};
	
	
}// end of namespace vgVisualEffects
	


#endif // end of __VGVIUPDATEOBSERVER_H__
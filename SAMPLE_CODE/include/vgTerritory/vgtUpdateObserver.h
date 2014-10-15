


#ifndef __VGTERRITORY_TUPDATEOBSERVER_H__
#define __VGTERRITORY_TUPDATEOBSERVER_H__


#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkForward.h>

	
namespace vgTerritory {

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
				(*iter)->onUpdate();
			}
		}
	
	private:


		std::vector<UpdateObserver*> _observers;

	
	};
	
}// end of namespace vgTerritory
	


#endif // end of __VGTERRITORY_TUPDATEOBSERVER_H__




#ifndef __VGUSENTRYMANAGER_H__
#define __VGUSENTRYMANAGER_H__


#include <vgUserInterface/vgusDefinition.h>
#include <vgKernel/vgkForward.h>


	
namespace vgUserInterface {

	/**
		@date 	2009/06/25  9:16	
		@author  xy
	
		@brief 	
	
		@see    
	*/
	class  VGUS_EXPORT EntryManager : public vgKernel::Singleton<EntryManager>
	{
		friend class vgKernel::Singleton<EntryManager>;
	private:
		EntryManager()
			: vgKernel::Singleton<EntryManager>( VGK_SIGNLETON_LEFE_ENTRYMGR )
		{
			_absEntryFac = NULL;
			VGK_TRACE(_T("EntryManager created."));
		}

	public:
		virtual~EntryManager()
		{
			VGK_TRACE(_T("EntryManager destroyed."));
		}

	protected:

		virtual bool initialise()
		{
			return true;
		}
		virtual bool shutdown();

	protected:
	
		
		AbstractEntryFactory* getAbstractEntryFac()
		{
			return _absEntryFac;
		}
	
	private:
	
		AbstractEntryFactory* _absEntryFac;
	
	};
	
	
}// end of namespace vgUserInterface
	


#endif // end of __VGUSENTRYMANAGER_H__



#include <vgStableHeaders.h>
#include <vgCam/vgcaRecordAction.h>


namespace vgCam {
	
	
	
	
	//----------------------------------------------------------------
	void RecordAction::doAction()
	{
		if ( _func != NULL )
		{
			(*_func)();
		}

		//if ( _scriptRunner->isValid() )
		//{
			//_scriptRunner->run();
		//}
	}
	//----------------------------------------------------------------


}// end of namespace vgCam

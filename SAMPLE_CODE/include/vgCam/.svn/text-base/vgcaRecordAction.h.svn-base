


#ifndef __VGCARECORDACTION_H__
#define __VGCARECORDACTION_H__
#include <vgCam/vgcaDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgCam/vgcaAction.h>
//#include <vgScript/vgscScriptRunner.h>

	
namespace vgCam {


	typedef void (*RecordActionFunc)(void); 

	const ActionType RecordActionType_start = 1;
	const ActionType RecordActionType_finish = 2;

	/**
		@date 	2009/02/06  15:33	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGCA_EXPORT RecordAction : public Action
	{
	public:
		RecordAction( ActionType type )
			: Action( type )
		{
			_func = NULL;
		}
		virtual ~RecordAction()
		{
			
		}
	
	
	public:


		void setByFunc( RecordActionFunc pfunc )
		{
			_func = pfunc;
		}

		void setByScript( const String& script_content )
		{
			assert(0);
			//_scriptRunner.setNull();

			//_scriptRunner.bind( new vgScript::ScriptRunner( script_content ) );
		}

		void clear()
		{
			_func = NULL;
			//_scriptRunner.setNull();
		}

		virtual void doAction();



	private:
	
		RecordActionFunc _func;

		//vgScript::ScriptRunnerPtr _scriptRunner;

	};
	
	
}// end of namespace vgCam
	


#endif // end of __VGCARECORDACTION_H__
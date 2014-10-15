


#ifndef __VGSCSCRIPTRUNNER_H__
#define __VGSCSCRIPTRUNNER_H__

#include <vgScript/vgscDefinition.h>
#include <vgKernel/vgkForward.h>

#include <vgKernel/vgkSharePtr.h>
#include <vgScript/vgscDefinition.h>

#include <python.h>


namespace vgScript {

	class ScriptManager;

	/**
		@date 	2009/01/08  15:28	
		@author  leven
	
		@brief 	编译文本之后的二进制script存储类.
	
		@see    
	*/
	class  VGSC_EXPORT ScriptRunner
	{
	public:

		ScriptRunner( const String& script_content );
		virtual ~ScriptRunner();
	
	public:

		bool isValid();
		
		bool run();

		bool reBindToString( const String& script_content );

		String getScriptContent() const 
		{
			return _scriptContent;
		}
	private:

		PyObject* getDict();

		void destroy();

	private:
	
		String _scriptContent;

		bool _hasEvalled;

		PyCodeObject* _pyCodeObject;

		PyObject* _evalObject;

		PyObject* _mainDict;
	};
	
	
	typedef vgKernel::SharePtr<ScriptRunner> ScriptRunnerPtr;



}// end of namespace vgScript
	


#endif // end of __VGSCSCRIPTRUNNER_H__
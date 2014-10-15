


#include <vgStableHeaders.h>
#include <vgScript/vgscScriptRunner.h>
#include <vgScript/vgscScriptManager.h>

#include <Python.h>

namespace vgScript {
	


	
	//----------------------------------------------------------------
	ScriptRunner::ScriptRunner( const String& script_content )
	{
		_pyCodeObject = NULL;
		_evalObject = NULL;
		_hasEvalled = false;
		_mainDict = NULL;

		_pyCodeObject = (PyCodeObject*)Py_CompileString( script_content.c_str(),
			VGSC_COMPILE_NAME, Py_file_input );

		if ( _pyCodeObject != NULL )
		{
			_scriptContent = script_content;
		}
	}
	//----------------------------------------------------------------
	ScriptRunner::~ScriptRunner()
	{
		destroy();
	}
	//----------------------------------------------------------------
	bool ScriptRunner::isValid()
	{
		if( _pyCodeObject == NULL )
		{
			return false;
		}

		if ( _hasEvalled == true )
		{
			if ( _evalObject != NULL )
			{
				return true;
			}

			return false;
		}

		//------------------------------------------
		// begin to eval
		//------------------------------------------
		_evalObject = PyEval_EvalCode( _pyCodeObject , 
			getDict() , 
			getDict() );

		if ( _evalObject == NULL )
		{
			return false;
		}

		return true;
	}
	//----------------------------------------------------------------
	bool ScriptRunner::run()
	{
		if ( isValid() == false )
		{
			return false;
		}

		Py_CLEAR( _evalObject );

		_evalObject = PyEval_EvalCode( _pyCodeObject , 
			getDict() , 
			getDict() );

		assert( _evalObject != NULL );

		return true;
	}
	//----------------------------------------------------------------
	PyObject* ScriptRunner::getDict()
	{
		if ( _mainDict == NULL )
		{
			return ScriptManager::getSingleton().getMainDictPyObject();
		}

		return _mainDict;
	}
	//----------------------------------------------------------------
	void ScriptRunner::destroy()
	{
		if ( _evalObject != NULL )
		{
			Py_CLEAR( _evalObject );
			_evalObject = NULL;
		}

		if ( _pyCodeObject != NULL )
		{
			Py_CLEAR( _pyCodeObject );
			_pyCodeObject = NULL;
		}

		_hasEvalled = false;
		_scriptContent.clear();
	}
	//----------------------------------------------------------------
	bool ScriptRunner::reBindToString( const String& script_content )
	{
		PyCodeObject* strobj = (PyCodeObject*)Py_CompileString( script_content.c_str(),
			VGSC_COMPILE_NAME, Py_file_input );

		if ( strobj == NULL )
		{
			return false;
		}

		destroy();

		_pyCodeObject = strobj;

		return true;
	}
	//----------------------------------------------------------------


}// end of namespace vgScript

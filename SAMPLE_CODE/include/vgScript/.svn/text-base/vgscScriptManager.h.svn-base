




#ifndef __VGSCSCRIPTMANAGER_H__
#define __VGSCSCRIPTMANAGER_H__

#include <vgScript/vgscDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSingleton.h>
#include <vgScript/vgscScriptRunner.h>





class CScriptConsoleDlg;

namespace vgScript {


	

	typedef std::vector<ScriptInitializeFunc> ScriptInitializeFuncVec;

	/**
		@date 	2008/12/11  21:40	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGSC_EXPORT ScriptManager : public vgKernel::Singleton<ScriptManager>
	{
	private:
		friend class vgKernel::Singleton<ScriptManager>;
	private:
		ScriptManager();

	public:
		~ScriptManager();

	protected:

		virtual bool initialise();

		virtual bool shutdown();

	public:

		void reset();

		bool initAfterOpenGLSetup();

		
		bool uninitBeforeOpenGLDestroy();


		void renderBegin();

		void render();

		void renderEnd();


		bool runScriptFile( const String& script_file_path , 
			const bool& alert = true );
		bool runScriptString( const String& script_str );

		void createMultiSelectDailogAndRunScript();

		String getDefaultScript() const
		{
			return _defaultScript;
		}

		void runScriptConsole();
		

		void runUserScriptConfig();


		bool dumpToScriptConsole( const String& msg );

		void clearScriptConsoleContent();


		PyObject* getMainModulePyObject();

		PyObject* getMainDictPyObject();

		void readProjectEnd(  const String& projpath , const String& projname );

		void saveProject(  const String& projpath , const String& projname );


		String getUserSaveProjScript()
		{
			return _userSaveProj;
		}

		String getUserReadProjScript()
		{
			return _userReadProj;
		}

		String getSaveProjPath() const
		{ 
			return _saveProjPath; 
		}


		String getReadProjPath() const
		{ 
			return _readProjPath; 
		}

		String getReadProjName() const
		{ 
			return _readProjName; 
		}

		String getSaveProjName() const
		{ 
			return _saveProjName; 
		}



		//------------------------------------------
		// 返回用户定义script
		// 注意, 是unix回车风格
		//------------------------------------------
		vgKernel::StringVector getUserDefinedScripts();

		//------------------------------------------
		// 输入用户定义script
		// 注意,顺序要和
		// _userInitScript;
		// _userRenderScript;
		// _userRenderBeginScript;
		// _userRenderEndScript;
		// _userUninitScript;
		// 一致且size是5
		//------------------------------------------
		bool setUserDefinedScripts( const vgKernel::StringVector& userscripts );


		bool addUserScriptFunc( ScriptInitializeFunc user_func );

	private:

		static void dumpToOutputHook( const char* msg );

		void readFromXml();
		void writeToXml();
		void destroyUserScripts();

		bool initialiseDefaultModules();

		void generateDefaultScript();

		void uninitMainModule();

		String getStringFromProjConf( const String& section , 
			const String& keystr );

		void setStringToProjConf( const String& section , 
			const String& keystr , const String& valuestr );

		//void test();

	private:

		String _saveProjPath;
		String _saveProjName;
		String _readProjName;
		String _readProjPath;


		ScriptInitializeFuncVec _initFuncs;

		String _defaultScript;
		CScriptConsoleDlg* _scriptConsolePtr;

		CScriptConsoleDlg* _scriptConsoleDialog;


		String _userSaveProj;
		String _userReadProj;

		String _userInitScript;
		String _userRenderScript;
		String _userRenderBeginScript;
		String _userRenderEndScript;
		String _userUninitScript;

		PyObject* _mainModule;
		PyObject* _mainDict;

		ScriptRunnerPtr _runnerUserRender;
		ScriptRunnerPtr _runnerUserRenderBegin;
		ScriptRunnerPtr _runnerUserRenderEnd;
	};
	
	
}// end of namespace vgScript
	


#endif // end of __VGSCSCRIPTMANAGER_H__
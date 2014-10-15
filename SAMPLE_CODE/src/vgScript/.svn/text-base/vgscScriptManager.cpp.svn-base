


#include <vgStableHeaders.h>
#include <vgScript/vgscScriptManager.h>
#include <vgScript/vgscModuleCam.h>
#include <vgScript/vgscModuleKernel.h>
#include <vgScript/vgscModuleHello.h>
#include <vgScript/vgscModuleTerritory.h>
//#include <vgScript/vgscModuleSystem.h>
#include <vgScript/vgscModuleScript.h>
#include <vgScript/vgscModuleVisualEffects.h>
//#include <vgScript/vgscModuleVector.h>
#include <vgScript/vgscModuleConf.h>
//#include <vgScript/vgscModuleMusic.h>
//#include <vgScript/vgscModuleSprite.h>
#include <vgScript/vgscModuleShape.h>
#include <vgScript/vgscDefinition.h>
#include <vgScript/ScriptConsoleDlg.h>
#include <vgScript/vgscUserScriptConfig.h>
#include <vgScript/vgscModuleAsyn.h>

#include <vgConf/vgcoProjectConfigRegProxy.h>
#include <vgConf/vgcoProjectConfig.h>

#include <vgKernel/vgkStandardOutput.h>




namespace vgScript {
	

	vgConf::ProjectConfigRegProxy script_projectconf1( 
		VGSC_SECTION , VGSC_USER_INIT , "" );

	vgConf::ProjectConfigRegProxy script_projectconf2(
		VGSC_SECTION , VGSC_USER_UNINIT , "" );

	vgConf::ProjectConfigRegProxy script_projectconf3(
		VGSC_SECTION , VGSC_USER_RENDER , "" );

	vgConf::ProjectConfigRegProxy script_projectconf4(
		VGSC_SECTION , VGSC_USER_RENDER_BEGIN , "" );

	vgConf::ProjectConfigRegProxy script_projectconf5(
		VGSC_SECTION , VGSC_USER_RENDER_END , "" );

	vgConf::ProjectConfigRegProxy script_projectconf6(
		VGSC_SECTION , VGSC_USER_READ_PROJ , "" );
	
	vgConf::ProjectConfigRegProxy script_projectconf7(
		VGSC_SECTION , VGSC_USER_SAVE_PROJ , "" );


	//----------------------------------------------------------------
	bool ScriptManager::runScriptFile( const String& script_file_path ,
		const bool& alert /*= true*/)
	{
		if ( vgKernel::SystemUtility::checkFileExist( script_file_path ) == false )
		{
			if ( alert )
			{
				std::ostringstream o;
				o << "script文件:" << script_file_path << "不存在";
				//MessageBox( NULL , o.str().c_str() , "提示" , MB_OK );
				vgKernel::SystemUtility::showModelDialog(o.str());
			}
			return false;
		}

#if 0
		String command( "execfile('" );

		command += script_file_path;
		command += "'";

		PyRun_SimpleString( command.c_str() );
#endif
#if 1

		FILE* file = fopen( script_file_path.c_str() , "r");

		if ( file == NULL )
		{
			return false;
		}

		assert( file != NULL );

		PyRun_SimpleFile( file, 
			vgKernel::StringUtility::getFilenameFromAbsolutePath( script_file_path ).c_str() );

		fclose( file );

		file = NULL;

#endif

		// 下面这个用了直接崩溃
		//boost::python::exec_file( 
		//	boost::python::str( script_file_path ) );

		return true;
	}
	//----------------------------------------------------------------
	bool ScriptManager::initialise()
	{
		Py_Initialize();

		if ( !Py_IsInitialized() )
		{
			//MessageBox( NULL , "Script初始化失败.", "提示" , MB_OK );
			vgKernel::SystemUtility::showModelDialog("Script初始化失败.");
			return false;
		}

		initialiseDefaultModules();

		return true;
	}
	//----------------------------------------------------------------
	void ScriptManager::createMultiSelectDailogAndRunScript()
	{
		CString DefExt;

		DefExt.Format("%s","py(*.py)|*.py|(*.*)|*.*|");

		CFileDialog dlgmodelFile(true,"py",
			NULL,OFN_HIDEREADONLY|
			OFN_CREATEPROMPT|
			OFN_NONETWORKBUTTON|
			OFN_ALLOWMULTISELECT|   
			OFN_FILEMUSTEXIST,
			DefExt);

		DWORD   MAXFILE = 0xFFFF;   
		dlgmodelFile.m_ofn.nMaxFile=MAXFILE; 

		char*  pc = new char[MAXFILE];   


		dlgmodelFile.m_ofn.lpstrFile = pc;   
		dlgmodelFile.m_ofn.lpstrFile[0] = NULL;   
		dlgmodelFile.m_ofn.lpstrTitle="python script";

		if( dlgmodelFile.DoModal() == IDOK )
		{
			POSITION posi;   
			vgKernel::StringVector strVec;

			posi = dlgmodelFile.GetStartPosition();   

			while( posi != NULL )
			{   
				strVec.push_back( dlgmodelFile.GetNextPathName(posi).GetBuffer(0));
			} 

			//------------------------------------------
			// 开始运行各个script
			//------------------------------------------
			vgKernel::StringVector::iterator iter = strVec.begin();
			vgKernel::StringVector::iterator iter_end = strVec.end();

			for ( ; iter != iter_end ; ++ iter )
			{
				runScriptFile( *iter );
			}
		}

		return;
	}
	//----------------------------------------------------------------
	bool ScriptManager::shutdown()
	{
		uninitMainModule();

		assert( _scriptConsolePtr == NULL );

		//Py_Finalize();
		return true;
	}
	//----------------------------------------------------------------
	bool ScriptManager::initialiseDefaultModules()
	{
		const bool show_user_defined = true;
		const bool show_cpp_signatures = false;
		const bool show_py_signatures = true;

		boost::python::docstring_options doc_options(
			show_user_defined, 
			show_py_signatures ,
			show_cpp_signatures);


		//addUserScriptFunc( registerScriptModule_hello );
		addUserScriptFunc( registerScriptModule_vgVisualEffects );
		addUserScriptFunc( registerScriptModule_vgKernel );
		addUserScriptFunc( registerScriptModule_vgCam );
#ifdef	SCRIPT_VGT
		addUserScriptFunc( registerScriptModule_vgTerritory );
#endif
		//addUserScriptFunc( registerScriptModule_vgSystem );
		addUserScriptFunc( registerScriptModule_vgScript );
		addUserScriptFunc( registerScriptModule_vgConf );
		//addUserScriptFunc( registerScriptModule_vgVector );
		//addUserScriptFunc( registerScriptModule_vgMusic );
		//addUserScriptFunc( registerScriptModule_vgSprite );
		addUserScriptFunc( registerScriptModule_vgAsyn );
#ifdef	SCRIPT_VGSH
		addUserScriptFunc( registerScriptModule_vgShape );
#endif
		if ( _defaultScript.empty() )
		{
			generateDefaultScript();
		}

		VGK_TRACE( _defaultScript );

		if( runScriptString( _defaultScript ) == false )
		{
			std::ostringstream o; 
			o << "默认script 初始化失败:\n" << _defaultScript; 
			//MessageBox( NULL , o.str().c_str() , "提示" , MB_OK );
			vgKernel::SystemUtility::showModelDialog(o.str());
		}

		return true;
	}
	//----------------------------------------------------------------
	bool ScriptManager::runScriptString( const String& script_str )
	{
		if ( script_str.empty() == true )
		{
			return true;
		}

		int runret = PyRun_SimpleString( script_str.c_str() );

		if ( runret == -1 )
		{
			return false;
		}

		return true;
	}
	//----------------------------------------------------------------
	void ScriptManager::generateDefaultScript()
	{
		_defaultScript.clear();

		std::ostringstream o;

		o << "\n"
			<< "import vgCam"		<< "\n"
			//<< "import vgSystem"		<< "\n"
			<< "import vgKernel"		<< "\n"
			//<< "import vgVector"		<< "\n"
#ifdef	SCRIPT_VGT
			<< "import vgTerritory"		<< "\n"
#endif
			<< "import vgVisualEffects"		<< "\n"
			<< "import vgScript"		<< "\n"
			//<< "import vgSprite"		<< "\n"
			<< "import vgConf"		<< "\n"
			//<< "import vgMusic"		<< "\n"
			<< "import vgAsyn"		<< "\n"

			<< "import sys"				<< "\n"
			<< "import os"				<< "\n"

			<< "def  vgAddGdalPath():"	<< "\n"
			<< "    exepath = vgKernel.getCurrentProcessPath()"	<< "\n"
			<< "    exepath = vgKernel.StringUtility.getPathFromAbsoluteFilename( exepath )"	<< "\n"
			<< "    gdalbin = exepath + \"gdalwin32-1.6\\\\bin\""	<< "\n"
			<< "    gdaldata = exepath + \"gdalwin32-1.6\\\\data\""	<< "\n"
			<< "    pa = os.getenv( \'PATH\' )"	<< "\n"
			<< "    assert pa != None"	<< "\n"
			<< "    pa += \';\'"	<< "\n"
			<< "    pa += gdalbin"	<< "\n"
			<< "    os.putenv( \'PATH\' , pa )"	<< "\n"
			<< "    os.putenv( \'GDAL_DATA\'  ,gdaldata )"	<< "\n"

			<< "vgAddGdalPath()"	<< "\n"

			<< "class vgStdoutLogger:"	<< "\n"
			<< "    def write(self, s):"		<< "\n"
			<< "        if isinstance( s , unicode ):" << "\n"
			<< "            vgKernel.dumpToOutputW( s )" << "\n"
			<< "        else:" << "\n"
			<< "            vgKernel.dumpToOutput( s )" << "\n"
			<< "vglogger = vgStdoutLogger() "		<< "\n"
			<< "sys.stdout = vglogger "					<< "\n"
			<< "sys.stderr = vglogger "					<< "\n"

			<< "try:"					<< "\n"
			<< "  from OpenGL.GL import *"					<< "\n"
			<< "  from OpenGL.GLU import *"					<< "\n"
			<< "except:"					<< "\n"
			<< "  print( 'ERROR: PyOpenGL not installed properly.' )"					<< "\n"

			;


		_defaultScript = o.str();
	}
	//----------------------------------------------------------------
	void ScriptManager::runScriptConsole()
	{	
		vgKernel::StandardOutput::redirectOutput( 
			dumpToOutputHook );

		assert( _scriptConsoleDialog != NULL );
		assert( _scriptConsolePtr  == NULL );
		
		_scriptConsoleDialog = new CScriptConsoleDlg;	//@FengYK 2009/11/14
		_scriptConsolePtr = _scriptConsoleDialog;

		_scriptConsolePtr->DoModal();

		_scriptConsolePtr = NULL;

		assert( _scriptConsolePtr  == NULL );

		BCGCBProSetTopLevelFrame( NULL );

		//CScriptConsoleDlg* dlg = new CScriptConsoleDlg;

		//dlg->DoModal();

		//delete dlg;

		vgKernel::StandardOutput::restoreToDefaultOutput();
	}
	//----------------------------------------------------------------
	bool ScriptManager::dumpToScriptConsole( const String& msg )
	{
		if( _scriptConsolePtr != NULL )
		{
			_scriptConsolePtr->dumpToOutput( msg , false , false );
			return true;
		}

		return false;
	}
	//----------------------------------------------------------------
	bool ScriptManager::initAfterOpenGLSetup()
	{
		assert( _scriptConsoleDialog == NULL );
		_scriptConsoleDialog = new CScriptConsoleDlg;

		//test();

		readFromXml();

		return true;
	}
	//----------------------------------------------------------------
	bool ScriptManager::uninitBeforeOpenGLDestroy()
	{
		assert( _scriptConsoleDialog != NULL );
		delete _scriptConsoleDialog;
		_scriptConsoleDialog  = NULL;

		if ( runScriptString( _userUninitScript ) == false )
		{
			//MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd , 
			//	"应用user uninit script 失败." , "Error" , MB_OK );
			vgKernel::SystemUtility::showModelDialog(
				"应用user uninit script 失败.");

		}

		_runnerUserRender.setNull();
		_runnerUserRenderBegin.setNull();
		_runnerUserRenderEnd.setNull();
		
		//------------------------------------------
		// 在这里卸载.
		// 如果放在shutdown里面,会出现错误.
		//------------------------------------------
		Py_Finalize();

		return true;
	}
	//----------------------------------------------------------------
	void ScriptManager::clearScriptConsoleContent()
	{
		_scriptConsoleDialog->clearOutput();
	}

	//----------------------------------------------------------------
	PyObject* ScriptManager::getMainModulePyObject()
	{
		if ( _mainModule == NULL )
		{
			_mainModule = PyImport_AddModule("__main__");
			assert( _mainModule != NULL );
		}

		return _mainModule;
	}
	//----------------------------------------------------------------
	PyObject* ScriptManager::getMainDictPyObject()
	{
		if ( _mainDict == NULL )
		{
			_mainDict = PyModule_GetDict( getMainModulePyObject() );
			assert( _mainDict != NULL );
		}

		return _mainDict;
	}
	//----------------------------------------------------------------
	void ScriptManager::uninitMainModule()
	{
		//------------------------------------------
		// 注意,不能释放,应该由py_finalize()释放
		//------------------------------------------

		//if ( _mainDict != NULL )
		//{
		//	Py_XDECREF( _mainDict );
		//	_mainDict = NULL ;
		//}

		//if ( _mainModule != NULL )
		//{
		//	Py_XDECREF( _mainModule );
		//	_mainModule = NULL;
		//}
	}
	//----------------------------------------------------------------
	String ScriptManager::getStringFromProjConf( const String& section , const String& keystr )
	{
		String str = 
			VG_PROJCONF_GET_STRING( section , keystr );

		vgKernel::StringUtility::replace( str , "\r" , "" );

		return str;
	}
	//----------------------------------------------------------------
	void ScriptManager::renderBegin()
	{
		if ( _runnerUserRenderBegin.isNull() == false )
		{
			_runnerUserRenderBegin->run();
		}
	}
	//----------------------------------------------------------------
	void ScriptManager::renderEnd()
	{
		if ( _runnerUserRenderEnd.isNull() == false )
		{
			_runnerUserRenderEnd->run();
		}
	}
	//----------------------------------------------------------------
	void ScriptManager::render()
	{
		if ( _runnerUserRender.isNull() == false )
		{
			_runnerUserRender->run();
		}
	}
	//----------------------------------------------------------------
	void ScriptManager::readProjectEnd( const String& projpath , const String& projname )
	{
		_readProjName = projname;
		_readProjPath = projpath;


		readFromXml();
	}
	//----------------------------------------------------------------
	void ScriptManager::saveProject(  const String& projpath , const String& projname )
	{
		_saveProjPath = projpath;
		_saveProjName = projname;


		writeToXml();
	}
	//----------------------------------------------------------------
	void ScriptManager::readFromXml()
	{
		vgKernel::StringVector xmlvec;

		xmlvec.push_back( getStringFromProjConf( 
			VGSC_SECTION , VGSC_USER_INIT ) );

		xmlvec.push_back( getStringFromProjConf( 
			VGSC_SECTION , VGSC_USER_RENDER_BEGIN ) );

		xmlvec.push_back( getStringFromProjConf( 
			VGSC_SECTION , VGSC_USER_RENDER ) );

		xmlvec.push_back( getStringFromProjConf( 
			VGSC_SECTION , VGSC_USER_RENDER_END ) );

		xmlvec.push_back( getStringFromProjConf( 
			VGSC_SECTION , VGSC_USER_UNINIT ) );

		setUserDefinedScripts( xmlvec );
	}
	//----------------------------------------------------------------
	void ScriptManager::destroyUserScripts()
	{
		_userInitScript.clear();
		_userRenderScript.clear();
		_userRenderBeginScript.clear();
		_userRenderEndScript.clear();
		_userUninitScript.clear();

		_runnerUserRender.setNull();

		_runnerUserRenderBegin.setNull();

		_runnerUserRenderEnd.setNull();
	}
	//----------------------------------------------------------------
	void ScriptManager::writeToXml()
	{
		setStringToProjConf( VGSC_SECTION , VGSC_USER_INIT, _userInitScript );
		setStringToProjConf( VGSC_SECTION , VGSC_USER_UNINIT, _userUninitScript );
		setStringToProjConf( VGSC_SECTION , VGSC_USER_RENDER, _userRenderScript );
		setStringToProjConf( VGSC_SECTION , VGSC_USER_RENDER_BEGIN, _userRenderBeginScript );
		setStringToProjConf( VGSC_SECTION , VGSC_USER_RENDER_END, _userRenderEndScript );
	}
	//----------------------------------------------------------------
	void ScriptManager::setStringToProjConf( const String& section ,
		const String& keystr , const String& valuestr )
	{
		String tmp = valuestr;
		vgKernel::StringUtility::replace( tmp , "\n" , "\r\n" );

		//------------------------------------------
		// 处理转义字符
		//------------------------------------------
		vgKernel::StringUtility::replace( tmp , "&" , "&amp;" );
		vgKernel::StringUtility::replace( tmp , "\"" , "&quot;" );
		vgKernel::StringUtility::replace( tmp , "<" , "&lt;" );
		vgKernel::StringUtility::replace( tmp , ">" , "&gt;" );

		VG_PROJCONF_SET( section , keystr , tmp );
	}
	//----------------------------------------------------------------
//	void ScriptManager::test()
//	{
//		//////////////////////////////////////////////////////////////////////////
//
//#if 1
//		std::ostringstream o;
//
//		o << "\n"
//			<< "glDisable( GL_DEPTH_TEST )"		<< "\n"
//
//			<< "glMatrixMode( GL_PROJECTION )"		<< "\n"
//			<< "glPushMatrix()"		<< "\n"
//			<< "glLoadIdentity()"		<< "\n"
//
//			<< "glMatrixMode( GL_MODELVIEW )"		<< "\n"
//			<< "glPushMatrix()"		<< "\n"
//			<< "glLoadIdentity()"		<< "\n"
//
//			<< "glDisable( GL_TEXTURE_2D )"		<< "\n"
//			<< "glDisable( GL_DEPTH_TEST)"		<< "\n"
//			<< "glColor3f(1,0,0.5)"		<< "\n"
//
//			<< "glBegin(GL_LINE_LOOP)"		<< "\n"
//
//			<< "glVertex2f( -0.5, -0.5 )"		<< "\n"
//			<< "glVertex2f( -0.5, 0.5 )"		<< "\n"
//			<< "glVertex2f( 0.5, 0.5 )"		<< "\n"
//			<< "glVertex2f( 0.5, -0.5 )"		<< "\n"
//
//			<< "glEnd()"		<< "\n"
//
//			<< "glMatrixMode( GL_PROJECTION )"		<< "\n"
//			<< "glPopMatrix()"		<< "\n"
//
//			<< "glMatrixMode( GL_MODELVIEW )"		<< "\n"
//			<< "glPopMatrix()"		<< "\n";
//
//
//		VG_PROJCONF_SET( VGSC_SECTION , VGSC_USER_RENDER_END, o.str() );
//
//#endif
//
//		//vgConf::ProjectConfig::getSingleton().trace();
//		//////////////////////////////////////////////////////////////////////////
//	}
	//----------------------------------------------------------------
	void ScriptManager::runUserScriptConfig()
	{
		vgKernel::StringVector userstr = getUserDefinedScripts();

		vgKernel::StringVector::iterator iter = userstr.begin();
		vgKernel::StringVector::iterator iter_end = userstr.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			vgKernel::StringUtility::replace( *iter , "\n" , "\r\n" );
		}

		UserScriptConfig dlg( userstr , 
			AfxGetApp()->m_pMainWnd );

		dlg.DoModal();
	}
	//----------------------------------------------------------------
	vgKernel::StringVector ScriptManager::getUserDefinedScripts()
	{
		vgKernel::StringVector ret;
		ret.push_back( _userInitScript );
		ret.push_back( _userRenderScript );
		ret.push_back( _userRenderBeginScript );
		ret.push_back( _userRenderEndScript );
		ret.push_back( _userUninitScript );

		return ret;
	}
	//----------------------------------------------------------------
	bool ScriptManager::setUserDefinedScripts( 
		const vgKernel::StringVector& userscripts )
	{
		assert( userscripts.size() == 5 ||
			userscripts.size() == 7 );

		if ( userscripts.size() != 7 && userscripts.size() != 5 )
		{
			return false;
		}

		//------------------------------------------
		// 首先需要卸载
		//------------------------------------------
		destroyUserScripts();

		//------------------------------------------
		// 开始初始化user script
		//------------------------------------------
		_userInitScript = userscripts[0];
		_userRenderBeginScript = userscripts[1];
		_userRenderScript = userscripts[2];
		_userRenderEndScript = userscripts[3];
		_userUninitScript = userscripts[4];

		if ( userscripts.size() == 7 )
		{
			_userReadProj = userscripts[5];
			_userSaveProj = userscripts[6];
		}

		if ( runScriptString( _userInitScript ) == false )
		{
#if 0
			MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd , 
				"初始化user init script 失败." , "Error" , MB_OK );
#else
			vgKernel::SystemUtility::showModelDialog(
				"初始化user init script 失败.");
#endif
		}

		if ( _userRenderBeginScript.empty() == false )
		{
			assert( _runnerUserRenderBegin.isNull() == true );
			_runnerUserRenderBegin.bind( new ScriptRunner( _userRenderBeginScript ) );

			if ( _runnerUserRenderBegin->isValid() == false )
			{
#if 0
				MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd , 
					"初始化user rendering begin script 失败." , "Error" , MB_OK );
#else
				vgKernel::SystemUtility::showModelDialog(
					"初始化user rendering begin script 失败.");
#endif
			}
		}

		if ( _userRenderScript.empty() == false )
		{
			assert( _runnerUserRender.isNull() == true );
			_runnerUserRender.bind( new ScriptRunner( _userRenderScript ) );

			if ( _runnerUserRender->isValid() == false )
			{
#if 0
				MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd , 
					"初始化user rendering script 失败." , "Error" , MB_OK );
#else
				vgKernel::SystemUtility::showModelDialog(
					"初始化user rendering script 失败.");
#endif
			}
		}

		if ( _userRenderEndScript.empty() == false )
		{
			assert( _runnerUserRenderEnd.isNull() == true );
			_runnerUserRenderEnd.bind( new ScriptRunner( _userRenderEndScript ) );

			if ( _runnerUserRenderEnd->isValid() == false )
			{
#if 0
				MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd , 
					"初始化user rendering end script 失败." , "Error" , MB_OK );
#else
				vgKernel::SystemUtility::showModelDialog(
					"初始化user rendering script 失败.");
#endif
			}
		}


		return true;
	}
	//----------------------------------------------------------------
	bool ScriptManager::addUserScriptFunc( ScriptInitializeFunc user_func )
	{
		if ( find( _initFuncs.begin() , _initFuncs.end() , user_func ) != _initFuncs.end() )
		{
			return false;
		}
		 
		(*user_func)();

		_initFuncs.push_back( user_func );

		return true;
	}
	//----------------------------------------------------------------
	void ScriptManager::dumpToOutputHook( const char* msg )
	{
		if( getSingleton()._scriptConsolePtr != NULL )
		{
			getSingleton()._scriptConsolePtr->dumpToOutput( msg , false , false );
			return;
		}

		VGK_SHOW( msg );
	}

	ScriptManager::ScriptManager() : Singleton<ScriptManager>( VGK_SINGLETON_LEFE_SCRIPTMGR )
	{
		_scriptConsolePtr = NULL;
		_scriptConsoleDialog = NULL;
		_mainModule = NULL;
		_mainDict = NULL;

		VGK_TRACE(_T("ScriptManager created."));
	}

	ScriptManager::~ScriptManager()
	{
		VGK_TRACE(_T("ScriptManager destroyed."));
	}

	void ScriptManager::reset()
	{

// 		generateDefaultScript();
// 
// 		runScriptString( _defaultScript );
// 
// 		destroyUserScripts();

	}
	//----------------------------------------------------------------

}// end of namespace vgScript


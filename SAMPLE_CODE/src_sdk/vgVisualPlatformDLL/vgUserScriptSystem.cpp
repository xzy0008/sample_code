



#include <vgStableHeaders.h>
#include "vgUserScriptSystem.h"
#include <vgGlobal/vggEditUtility.h>
#include <vgGlobal/vggSceneFileUtility.h>
#include <vgUIController/vgUIController.h>
#include <vgKernel/vgkSystemUtility.h>
#include <vgScript/vgscScriptManager.h>
#include <vgKernel/vgkRendererManager.h>

#include <vgScript/vgscBoostPythonInclude.h>

#include "MainFrm.h"

namespace vgUser
{

	//----------------------------------------------------------------
	void setApplicationTitle( const String& str )
	{
		AfxGetApp()->m_pMainWnd->SetWindowText( str.c_str() );

		// Ë¢ÐÂ½çÃæ
		RECT rect;
		AfxGetApp()->m_pMainWnd->GetWindowRect( &rect );
		InvalidateRect( NULL , &rect , TRUE );
	}
	//----------------------------------------------------------------
	void resetMenu()
	{
		CMainFrame* mainfrm = (CMainFrame*)AfxGetMainWnd();
		assert( mainfrm != NULL );

		mainfrm->resetMenuItems();
	}
	//----------------------------------------------------------------
	bool loadScriptMenuFile( const String& filepath ,
		const String& menu_name = "UserMenu", const int& insert_pos = -1 )
	{
		CMainFrame* mainfrm = (CMainFrame*)AfxGetMainWnd();
		assert( mainfrm != NULL );

		return mainfrm->loadScriptMenu( filepath , menu_name , insert_pos );
	}
	//----------------------------------------------------------------
	bool loadScriptMenuString( const String& content ,
		const String& menu_name = "UserMenu", const int& insert_pos = -1 )
	{
		CMainFrame* mainfrm = (CMainFrame*)AfxGetMainWnd();
		assert( mainfrm != NULL );

		return mainfrm->loadScriptMenuFromString( content , menu_name , insert_pos );

	}
	//----------------------------------------------------------------
	void showMenuBar( const bool& showit )
	{

		CMainFrame* mainfrm = (CMainFrame*)AfxGetMainWnd();
		assert( mainfrm != NULL );

		if ( showit == true )
		{
			mainfrm->m_wndMenuBar.ShowControlBar(TRUE, TRUE, TRUE);
		}
		return mainfrm->m_wndMenuBar.ShowControlBar(FALSE, FALSE, FALSE);

	}
	bool getMenuBarVisible()
	{

		CMainFrame* mainfrm = (CMainFrame*)AfxGetMainWnd();
		assert( mainfrm != NULL );
		return mainfrm->m_wndMenuBar.IsVisible();

	}
	//----------------------------------------------------------------
	void showOutputBar( const bool& showit )
	{
		if ( showit == true )
		{
			vgUI::UIController::getSingleton().GetOutputBar()->ShowControlBar(TRUE, TRUE, TRUE);
			return;
		}

		vgUI::UIController::getSingleton().GetOutputBar()->ShowControlBar(FALSE, FALSE, FALSE);
	}
	bool getOutputBarVisible()
	{
		return vgUI::UIController::getSingleton().GetOutputBar()->IsVisible();
	}
	//----------------------------------------------------------------
	void showPropertiesViewBar( const bool& showit )
	{
		if ( showit == true )
		{
			vgUI::UIController::getSingleton().GetPropertiesViewBar()->ShowControlBar(TRUE, TRUE, TRUE);
			return;
		}

		vgUI::UIController::getSingleton().GetPropertiesViewBar()->ShowControlBar(FALSE, FALSE, FALSE);
	}
	bool getPropertiesViewBarVisible()
	{
		return vgUI::UIController::getSingleton().GetPropertiesViewBar()->IsVisible();
	}
	//----------------------------------------------------------------
	void showWorkSpaceBar( const bool& showit )
	{
		if ( showit == true )
		{
			vgUI::UIController::getSingleton().GetWorkSpaceBar()->ShowControlBar(TRUE, TRUE, TRUE);
			return;
		}

		vgUI::UIController::getSingleton().GetWorkSpaceBar()->ShowControlBar(FALSE, FALSE, FALSE);
	}
	bool getWorkSpaceBarVisible()
	{
		return vgUI::UIController::getSingleton().GetWorkSpaceBar()->IsVisible();
	}
	//----------------------------------------------------------------
	void showToolBar( const bool& showit )
	{
		CMainFrame* mainfrm = (CMainFrame*)AfxGetMainWnd();
		assert( mainfrm != NULL );

		BOOL b;
		if ( showit == true )
		{
			b = TRUE;
		}
		else
		{
			b = FALSE;
		}

		mainfrm->m_wndToolBar.ShowControlBar(b, b, b);
		mainfrm->m_wndToolBar2_edit.ShowControlBar(b, b, b);
		mainfrm->m_wndToolBar3_camera.ShowControlBar(b, b, b);

		return;
	}
	//----------------------------------------------------------------
	//----------------------------------------------------------------
	void removeMenuItem(const int& index )
	{
		CMainFrame* mainfrm = (CMainFrame*)AfxGetMainWnd();
		assert( mainfrm != NULL );

		mainfrm->removeMenuItem( index );
	}
	//----------------------------------------------------------------
	void clearOutput()
	{
		vgScript::ScriptManager::getSingleton().clearScriptConsoleContent();
		vgUI::UIController::getSingleton().GetOutputBar()->ClearContent();
	}
	//----------------------------------------------------------------
	//----------------------------------------------------------------
	void outputMessage( const String& str )
	{
		if ( vgScript::ScriptManager::getSingleton().dumpToScriptConsole( str ) )
		{
			return;
		}

		VGK_SHOW( str );
	}
	void outputMessageW( const std::wstring& wstr )
	{
		std::string str = vgKernel::StringUtility::convertWStringToString( wstr );

		outputMessage( str );
	}
	//----------------------------------------------------------------
	//----------------------------------------------------------------
	void messageBox1( const String& str , const String& caption )
	{
		MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd , 
			str.c_str() , caption.c_str() , MB_OK  );
	}
	//----------------------------------------------------------------
	void messageBox2( const String& str )
	{
		MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd , 
			str.c_str() , "VR-GIS Platform" , MB_OK  );
	}
	//----------------------------------------------------------------
	void switchObjectsVisible( const vgKernel::StringVector& obj_name_list )
	{
		for (int i=0; i< obj_name_list.size(); i++)
		{
			vgKernel::Renderer* pRenderer = 
				vgKernel::RendererManager::getSingleton().getRendererbyName(
				obj_name_list[i] );

			if (pRenderer != NULL)
			{
				pRenderer->setVisible(! pRenderer->getVisible());
			}
		}
	}
	bool switchObjectVisible( const String& objname )
	{
		vgKernel::Renderer* pRenderer = 
			vgKernel::RendererManager::getSingleton().getRendererbyName(
			objname );

		if (pRenderer != NULL)
		{
			pRenderer->setVisible(! pRenderer->getVisible());
			return true;
		}

		return false;
	}
	//----------------------------------------------------------------
	void setObjectsVisible( const vgKernel::StringVector& obj_name_list ,
		const bool& visible )
	{
		for (int i=0; i< obj_name_list.size(); i++)
		{
			vgKernel::Renderer* pRenderer = 
				vgKernel::RendererManager::getSingleton().getRendererbyName(
				obj_name_list[i] );

			if (pRenderer != NULL)
			{
				pRenderer->setVisible( visible );
			}
		}
	}
	bool setObjectVisible( const String& objname , const bool& visible )
	{
		vgKernel::Renderer* pRenderer = 
			vgKernel::RendererManager::getSingleton().getRendererbyName(
			objname );

		if (pRenderer != NULL)
		{
			pRenderer->setVisible( visible );
			return true;
		}

		return false;
	}

	//----------------------------------------------------------------
	void logMessage( const String& msg )
	{
		LogManager::getSingleton().logMessage( msg );
	}
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//----------------------------------------------------------------
	void exportSystem()
	{
		using namespace boost::python;


		//def( "testMsg" , testMsg );


		def( "removeMenuItem", removeMenuItem );

		def( "logMessage" , logMessage );
		def( "outputMessage" , outputMessage );
		//def( "outputMessage" , outputMessageW );
		def( "outputMessageW" , outputMessageW );
		def( "messageBox" , messageBox1 );
		def( "messageBox" , messageBox2 );

		def( "switchObjectsVisible" , switchObjectsVisible );
		def( "switchObjectVisible" , switchObjectVisible );
		def( "setObjectsVisible" , setObjectsVisible );
		def( "setObjectVisible" , setObjectVisible );

		def( "setApplicationTitle" , setApplicationTitle , ( VGARG("str") ) );
		def( "clearOutput" , clearOutput );

		def( "loadScriptMenuFile" , loadScriptMenuFile ,
			( VGARG("filepath"), VGARG("menu_name")="UserMenu", VGARG("insert_pos")=-1 ) );

		def( "loadScriptMenuString" , loadScriptMenuString ,
			( VGARG("content"), VGARG("menu_name")="UserMenu", VGARG("insert_pos")=-1 ) );

		def( "resetMenu" , resetMenu );

		def( "showMenuBar" , showMenuBar );
		def( "getMenuBarVisible" , getMenuBarVisible );
		def( "showOutputBar" , showOutputBar );
		def( "getOutputBarVisible" , getOutputBarVisible );
		def( "showPropertiesViewBar" , showPropertiesViewBar );
		def( "getPropertiesViewBarVisible" , getPropertiesViewBarVisible );
		def( "showWorkSpaceBar" , showWorkSpaceBar );
		def( "getWorkSpaceBarVisible" , getWorkSpaceBarVisible );

		def( "showToolBar",showToolBar );



	}
	//----------------------------------------------------------------

	void exportGlobal()
	{
		using namespace boost::python;
		using namespace vgGlobal;

		def( "getSceneOpenedFlag" , SceneFileUtility::getSceneOpenedFlag );
		def( "resetScene" , SceneFileUtility::resetScene );
		def( "openScene" , SceneFileUtility::openScene );
		//def( "importFiles" , SceneFileUtility::importFiles );
		//def( "importFile" , SceneFileUtility::importFile );
		//def( "exportModelFile" , SceneFileUtility::exportModelFile );
		def( "getCurrentScenePath" , SceneFileUtility::getCurrentScenePath );
		def( "translateRenderers" , EditUtility::translateRenderers );
	}

	//----------------------------------------------------------------
	BOOST_PYTHON_MODULE(vgSystem)
	{
		exportSystem();
		exportGlobal();
	}

	void exportSystemModule()
	{
		initvgSystem();
	}

}
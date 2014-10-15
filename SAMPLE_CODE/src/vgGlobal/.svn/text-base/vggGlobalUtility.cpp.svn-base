
#include <vgStableHeaders.h>
#include <vgGlobal/vggGlobalUtility.h>

#include <vgGlobal/vggVgmodUtility.h>
#include <vgGlobal/vggVgshpUtility.h>

#include <vgModel/vgmoModelManager.h>
#include <vgModel/vgmoFileHandleVmd.h>

#include <vgKernel/vgkSelectManager.h>
#include <vgKernel/vgkPluginManager.h>
#include <vgKernel/vgkInputSystem.h>
#include <vgTerritory/vgtDefinition.h>

#include <DlgAbout.h>


namespace vgGlobal{


	bool GlobalUtility::m_bIsWireLine = false;


	//----------------------------------------------------------------
	GlobalUtility::GlobalUtility()
	{
		
	}
	
	//----------------------------------------------------------------
	GlobalUtility::~GlobalUtility()
	{

	}

	
	//----------------------------------------------------------------
	void	GlobalUtility::attachRendererToTerrain( vgKernel::Renderer* renderer ,
		const bool& update_selectmgr )
	{
		assert( renderer != NULL );

		using namespace vgKernel;
		Plugin* plg = PluginManager::getSingleton().getPluginRef( VGT_DLL_NAME );

		if ( plg == NULL )
		{
			return;
		}


		VGK_DLL_DECLARE_CLASSFUNC( 
			plg , TerrainManager, getElevationByPosition, fun1 );

		if ( fun1 == NULL )
		{
			return;
		}


		// 普通三维renderer
		float elev = 0.0f;

		vgKernel::Vec3 rendererpos = renderer->getBoundingBox().getCenter();

		float maxheight = renderer->getBoundingBox()._maxVertex.y;
		float halfheight = maxheight - rendererpos.y;
		assert( halfheight >= 0.0f );


		bool getok = (*fun1)(
			rendererpos , elev , true );

		renderer->moveTo( rendererpos.x , elev + halfheight, rendererpos.z );


		if ( update_selectmgr )
		{
			vgKernel::SelectManager::getSingleton().updateBox();
		}
	}
	
	//----------------------------------------------------------------
	void	GlobalUtility::attachRendererToTerrain(
		vgKernel::RendererQueue* renderers ,
		const bool& update_selectmgr )
	{
		assert( renderers != NULL );

		if ( renderers->empty() == true )
		{
			return;
		}

		vgKernel::RendererQueue::iterator iter = renderers->begin();
		vgKernel::RendererQueue::iterator iter_end = renderers->end();

		for ( ; iter != iter_end ; ++ iter )
		{
			attachRendererToTerrain( *iter  , false );
		}

		if ( update_selectmgr )
		{
			vgKernel::SelectManager::getSingleton().updateBox();
		}
	}
	
	
	//----------------------------------------------------------------
	vgKernel::Renderer* GlobalUtility::getSelectedRendererByType( 
		vgKernel::RendererType type )
	{
		vgKernel::RendererQueue sel=vgKernel::SelectManager::getSingleton().
			getSelectedItems();
		
		if (sel.size()>0)
		{	
			vgKernel::Renderer* tmp=sel[0];

			if(tmp->getType()==type)
			{
				return tmp;
			}
			else
			{
				MessageBox(NULL, "类型不匹配，请重新选择！", "", MB_OK);
			}
		}
		else
		{
			MessageBox(NULL, "未选中任何节点，请选择！", "", MB_OK);
		}

		return NULL;
	}

	//----------------------------------------------------------------
	bool GlobalUtility::publishProject()
	{
		return true;
	}

	//----------------------------------------------------------------
	bool GlobalUtility::reset()
	{
		return true;
	}

	//----------------------------------------------------------------
	bool GlobalUtility::exitProgram()
	{
		return true;
	}

	//----------------------------------------------------------------
	bool GlobalUtility::renderEntityOrLine()
	{
		//static bool dd = false;

		//dd = !dd;

		m_bIsWireLine = !m_bIsWireLine; //初始化为实体渲染

		if ( m_bIsWireLine == true )
		{
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		}
		else
		{
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

		}

		return true;
	}

	//----------------------------------------------------------------
	bool GlobalUtility::updateRenderEntityOrLine()
	{
		return m_bIsWireLine;
	}

	//----------------------------------------------------------------
	bool GlobalUtility::showAboutDlg()
	{
		VGK_DLL_RES_SWITCH_NAME( VGDEP_DLL_NAME );

		CAboutDlg	dlgAbout;
		dlgAbout.DoModal();

		return true;
	}
	
	//----------------------------------------------------------------
	bool GlobalUtility::responseLButtonDblClk(UINT nFlags, CPoint point, CWnd* pwnd )
	{
		vgKernel::InputSystem::getSingleton().OnLButtonDbClick(nFlags,point);

		vgGlobal::ModUtility::responseLButtonDblClk(nFlags, point, pwnd);

		return true;
	}

	//----------------------------------------------------------------
	bool GlobalUtility::responseLButtonDown(UINT nFlags, CPoint point)
	{
		vgKernel::InputSystem::getSingleton().OnLButtonDown(nFlags, point);

		vgGlobal::ModUtility::responseLButtonDown(nFlags, point);

		return true;
	}

	//----------------------------------------------------------------
	bool GlobalUtility::responseLButtonUp(UINT nFlags, CPoint point)
	{
		vgKernel::InputSystem::getSingleton().OnLButtonUp(nFlags,point);

		return true;
	}

	//----------------------------------------------------------------
	bool GlobalUtility::importVtrFile( const String& file_name)
	{
		if ( !VGK_DLL_CHECK_LOAD( VGT_DLL_NAME ) )
		{
			return false;
		}

		VGK_DLL_RUN_CLASSFUNC( VGT_DLL_NAME ,
			TerrainManager, openVtrFile )( file_name );


		//bool has_create_node = 
		//	vgPlugin::TerritoryUtility::hasTerrainData();

		//bool openok = 
		//	vgPlugin::TerritoryUtility::openVtrFile( file_name );

		//if ( openok == true )
		//{
		//	if ( has_create_node == false )
		//	{
		//		// 添加地形节点
		//		vgUI::UIController::getSingleton().ClearSelection();
		//	}
		//}

		return true;
	}

	//----------------------------------------------------------------
	bool GlobalUtility::importVmdFileOnly( const String& file_name)
	{
		vgModel::FileHandleVmd* vgmhandle 
			= new vgModel::FileHandleVmd( file_name );

		bool opened = vgmhandle->open();

		if( opened == false )
		{
			delete vgmhandle;

			return false;
		}

		bool addres = 
			vgModel::ModelManager::getSingleton().addItemsAndRegisterFileHandlerVmd( vgmhandle );


		if ( addres == false)
		{
			delete vgmhandle;

			return false;
		}

		//------------------------------------------
		// 向UI中添加vgBaseEntry
		//------------------------------------------

		vgModel::ModelItemMap* items = vgmhandle->getModelItemsPtr();
		assert( items != NULL );

		vgModel::ModelItemMap::iterator iter = items->begin();
		vgModel::ModelItemMap::iterator iter_end = items->end();

		for ( ; iter != iter_end ; ++ iter )
		{
			//String shortname = vgKernel::StringUtility::getFilenameFromAbsolutePath(
			//	vgmhandle->getFilePath() );
			//vgBaseEntry* entry = vgEntryFactory::createEntryFromRenderer( iter->second );
			//vgUI::UIController::getSingleton().AddNode( shortname, entry, hRootVGM);
			//vgUI::UIController::getSingleton().OnChanged(VG_OBS_NEWMESHITEM, vgmhandle->getMeshItemsPtr());


			vgKernel::RendererQueue* queue = 
				vgKernel::RendererManager::getSingleton().addRenderer( iter->second );

			assert( queue != NULL );
		}

		return true;
	}

}//namespace vgXXX

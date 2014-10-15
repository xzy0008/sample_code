
#include <vgStableHeaders.h>

#include <vgMod/vgModMisc.h>

#include <vgMod/vgNodeManager.h>
#include <vgCam/vgcaCamManager.h>
#include <vgMovingManager.h>

#include <vgDlgTreeSet.h>
#include <vgDlgTreeDis.h>

#include <vgRoot.h>

#include <vgKernel/vgkSystemUtility.h>
#include <vgKernel/vgkStringUtility.h>

#include <vgTex/tvgArchiveManager.h>

#include <vgKernel/vgkInputCodeDef.h>
#include <vgGlobalDefinition.h>

#include <vgConf/vgcoExeConfig.h>

#define VGEXE_PATHCONF					"DataPathConfig"
#define VGEXE_PATHCONF_TEXTURE_PATH		"TexturePath"


namespace vgMod{

	
	//----------------------------------------------------------------
	ModMisc::ModMisc()
		: vgKernel::Singleton<ModMisc>( VGK_SINGLETON_LEFE_MODMISCMANAGER ) 
	{
		m_pSmallMap = new vgCore::SmallMap;
		m_pHawkeyePath = new vgCore::HawkeyePath;

		m_dlgTreeSet = new DlgTreeSet;
		m_dlgTreeDis = new DlgTreeDis;

		m_nCurrentMode = false;

		m_dlgdynbillboard = new DlgDynamicBillboardNode;

		SetHandleStatus( VG_INPUT_MODMISC );
		vgKernel::InputSystem::getSingleton().registerHandle( this );

		m_pMiscRenderCommand = new ModMiscRenderCommand;
		vgKernel::RenderCommandFacade::AddCommand(m_pMiscRenderCommand);
	}
	
	//----------------------------------------------------------------
	ModMisc::~ModMisc()
	{
		if (m_pSmallMap)
		{
			delete m_pSmallMap;

			m_pSmallMap = NULL;
		}

		if (m_pHawkeyePath)
		{
			delete m_pHawkeyePath;

			m_pHawkeyePath = NULL;
		}

		if (m_dlgTreeSet)
		{
			delete m_dlgTreeSet;

			m_dlgTreeSet = NULL;
		}

		if (m_dlgTreeDis)
		{
			delete m_dlgTreeDis;

			m_dlgTreeDis = NULL;
		}

		if (m_dlgdynbillboard)
		{
			delete m_dlgdynbillboard;

			m_dlgdynbillboard = NULL;
		}

		vgKernel::InputSystem::getSingleton().removeHandle( this );

		vgKernel::RenderCommandFacade::RemoveCommand(m_pMiscRenderCommand);
		m_pMiscRenderCommand = NULL;

		TRACE("Destory ModMisc Render Command.\n");
	}
	
	bool ModMisc::initialise()
	{

		return true;
	}

	bool ModMisc::shutdown()
	{
		return true;
	}
	//----------------------------------------------------------------
	void ModMisc::renderLines()
	{
		switch(m_nCurrentMode)
		{
		case VG_STATUS_PLANT_IN_LINE:
			{
				glDisable(GL_TEXTURE_2D);
				glPushMatrix();
				glPointSize(5.0);
				glPushAttrib(GL_CURRENT_BIT);
				glColor3f(1,0,0);

				/*Vector3Vec::iterator iter_begin = m_vPlantPos.begin();
				Vector3Vec::iterator iter_end = m_vPlantPos.end();*/
				
				Vector3Vec::iterator iter_begin = m_vPlantPosForDrawLine.begin();
				Vector3Vec::iterator iter_end = m_vPlantPosForDrawLine.end();

				Vector3Vec::iterator iter = iter_begin;

				glBegin(GL_POINTS);
				{
					for ( ; iter != iter_end ; ++ iter )
					{
						glVertex3fv( iter->v );
					}
				}
				glEnd();

				//int size = m_vPlantPos.size();
				int size = m_vPlantPosForDrawLine.size();
				if ( size > 1 )
				{
					glColor3f(0,1,0);
					glDisable(GL_DEPTH_TEST);
					glBegin(GL_LINES);
					{
						for ( iter = iter_begin ; iter != iter_end - 1 ; ++ iter )
						{
							glVertex3fv( iter->v );
							glVertex3fv( (iter+1)->v );
						}
					}
					glEnd();

					glEnable(GL_DEPTH_TEST);
				}

				glPopAttrib();
				glPopMatrix();
			}	
			break;

			
		case VG_STATUS_PATH:
			m_pHawkeyePath->Draw();
			break;
		}

	}
	
	//----------------------------------------------------------------
	void ModMisc::renderHawkeye()
	{
		//m_oCurrentScene.m_pSmallMap->DrawSmallmap(m_pCurrentCamera.g_eye[0],m_pCurrentCamera.g_eye[2]);
		m_pSmallMap->DrawSmallmap(
			vgCam::CamManager::getSingletonPtr()->getCurrentPositionPtr()->x, 
			vgCam::CamManager::getSingletonPtr()->getCurrentPositionPtr()->z );
	}

	
	//----------------------------------------------------------------
	void ModMisc::renderPath()
	{
		m_pHawkeyePath->DrawInScene();	
	}

	//----------------------------------------------------------------
	vgCore::SmallMap* ModMisc::getSmallMap()
	{
		return m_pSmallMap;
	}

	//----------------------------------------------------------------
	vgCore::HawkeyePath* ModMisc::getHawkeyePath()
	{
		return m_pHawkeyePath;
	}

	//----------------------------------------------------------------
	void ModMisc::setStatus( int status )
	{
		vgKernel::InputSystem::getSingleton().setCurrentStatus( VG_INPUT_MODMISC | 
			VG_INPUTMODE_CAMERA | VG_INPUTMODE_UI );
		
		m_nCurrentMode = status;
	}

	//----------------------------------------------------------------
	int ModMisc::getStatus()
	{
		return	m_nCurrentMode;
	}

	//----------------------------------------------------------------
	DlgTreeSet* ModMisc::getDlgTreeSet()
	{
		return m_dlgTreeSet;
	}	

	//----------------------------------------------------------------
	DlgTreeDis* ModMisc::getDlgTreeDis()
	{
		return m_dlgTreeDis;
	}

	//----------------------------------------------------------------
	DlgDynamicBillboardNode* ModMisc::getDlgDynBillboard()
	{
		return m_dlgdynbillboard;
	}
	//----------------------------------------------------------------
	void	ModMisc::addPlantPosition(CPoint &point)
	{
		vgKernel::Vec3 pt3D = vgKernel::Math::trans2DPointTo3DVec(point.x, point.y);
		
		m_vPlantPosForDrawLine.push_back( Vector3( pt3D ) );

		//此点数组实时改变植被距离时重新生成Billboard
		Vector3Vec* pVector3Vec = this->getDlgTreeDis()->getPlantPosVec();
		if ( pVector3Vec )
		{
			pVector3Vec->push_back( Vector3( pt3D ) );
		}
	}

	
	//----------------------------------------------------------------
	void ModMisc::OnKeyDown( int keyCode )
	{
		//Tab键取消生成喷泉，火，烟，种树等操作
		if ( keyCode == InputCode::TAB )
		{
			StopCreate();
			this->clearTreeDisPosVec();
		}
	}

	void ModMisc::StopCreate()
	{
		this->setStatus( VG_STATUS_NONE );
		vgKernel::InputSystem::getSingleton().reset();

		this->getPlantPosForDrawLine()->clear();
		//this->clearTreeDisPosVec();

	}

	//----------------------------------------------------------------
	void	ModMisc::lButtonDown( UINT nFlags, CPoint point)
	{
		switch (m_nCurrentMode)
		{
		case VG_STATUS_PLANT_TREE:
			{
				vgMod::NodeManager::getSingleton().addTree(point);
				break;
			}
		case VG_STATUS_PLANT_IN_LINE:
			{
				addPlantPosition(point);
				break;
			}

		case VG_STATUS_FOUNTAIN:
			{
				vgMod::NodeManager::getSingleton().addParticleToScene(point, PARTICLE_FOUNTAIN);
				break;
			}
		case VG_STATUS_FIRE:
			{
				vgMod::NodeManager::getSingleton().addParticleToScene(point, PARTICLE_FIRE);
				break;
			}
		case VG_STATUS_SMOKE:
			{
				vgMod::NodeManager::getSingleton().addParticleToScene(point, PARTICLE_SMOKE);
				break;
			}
		case VG_STATUS_FLAG:
			{
				vgMod::NodeManager::getSingleton().addParticleToScene(point, PARTICLE_FLAG);
				break;
			}

		case VG_STATUS_DYNBILLBOARD_GENERATE:
			{
				vgMod::NodeManager::getSingleton().addDyanamicBillboard(point);
				break;
			}
		default:
			break;

		}
	}
	
	//----------------------------------------------------------------
	void	ModMisc::lButtonDblClk(UINT nFlags, CPoint point, /*GLfloat gldaspect, */CWnd *pwnd)
	{

	}

	
	//----------------------------------------------------------------
	void	ModMisc::renderMisc()
	{
		renderPath();
		renderLines();
		renderHawkeye();
		MovingManager::getSingleton().renderMovingNode();
		MovingManager::getSingleton().getClimate()->render();
	}

	
	//----------------------------------------------------------------
	bool	ModMisc::initialize( HWND &hWnd )
	{
		// 初始化root
		vgCore::Root *root = vgCore::Root::getSingletonPtr();
		assert( root != NULL );
		root->initNecessity( );
		//root->initRequirement( NULL ,hWnd );		
		

		// 注册exe下的目录
		String path = vgKernel::SystemUtility::getCurrentProcessPath();

		path = vgKernel::StringUtility::getPathFromAbsoluteFilename(path);

		//path += "ProAttachdata";
		String texturePath =  VG_EXECONF_GET_STRING( 
			VGEXE_PATHCONF,  
			VGEXE_PATHCONF_TEXTURE_PATH);

		path += texturePath;

		vgCore::ArchivePtr parch( 
			new vgCore::FileSystemArchive( path ,"filesystem") );

		parch->load();

		vgCore::ArchiveManager::getSingleton().addArchive( 5142 , parch );


		// 其他
		vgCam::CamManager::getSingleton();

/*		vgSound::SoundManager::getSingleton().initialise( hWnd );*/

		vgCore::MovingManager::getSingleton().getClimate()->init(

			vgCam::CamManager::getSingletonPtr()
			);

		

		return	true;
	}

	
	//----------------------------------------------------------------
	int ModMisc::getCurrentMode()
	{
		return m_nCurrentMode;
	}

	//----------------------------------------------------------------
	void ModMisc::setCurrentMode( int nMode)
	{
		m_nCurrentMode = nMode;
	}

	void ModMisc::reset()
	{
		if (m_pSmallMap)
		{
			delete m_pSmallMap;

			m_pSmallMap = NULL;
		}

		if (m_pHawkeyePath)
		{
			delete m_pHawkeyePath;

			m_pHawkeyePath = NULL;
		}

		if (m_dlgTreeSet)
		{
			delete m_dlgTreeSet;

			m_dlgTreeSet = NULL;
		}

		if (m_dlgTreeDis)
		{
			delete m_dlgTreeDis;

			m_dlgTreeDis = NULL;
		}

		//m_vPlantPos.clear();
		m_vPlantPosForDrawLine.clear();

		m_nCurrentMode = -1;
		m_pSmallMap = new vgCore::SmallMap;
		m_pHawkeyePath = new vgCore::HawkeyePath;

		m_dlgTreeSet = new DlgTreeSet;
		m_dlgTreeDis = new DlgTreeDis;

	}

	//----------------------------------------------------------------
	void ModMisc::clearTreeDisPosVec()
	{
		Vector3Vec* pVector3Vec = this->getDlgTreeDis()->getPlantPosVec();
		if ( !pVector3Vec->empty() )
		{
			pVector3Vec->clear();
		}
	}
}//namespace vgMod

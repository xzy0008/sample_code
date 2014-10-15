
#include <vgStableHeaders.h>
#include <vgLogo/vgloLogoManager.h>

#include <vgKernel/vgkSystemUtility.h>
#include <vgKernel/vgkStringUtility.h>
#include <vgImage/vgiFreeImageWrapper.h>

#include <vgConf/vgcoExeConfig.h>

#include <vgLogo/vgloCompass.h>
#include <vgLogo/vgloRenderCommmand.h>
#include <vgKernel/vgkRenderCommandManager.h>


#define VGDATA_PATHCONF						"DataPathConfig"
#define VGDATA_PATHCONF_TEXTURE_PATH		"TexturePath"

#define VGDATA_FILECONF						"DataFileConfig"
#define VGDATA_FILECONF_TEXTURE_LOGO		"LogoName"


namespace vgLogo {  

	LogoManager::LogoManager() : Singleton<LogoManager>(VGK_SIGLETON_LEFE_LOGOMANAGER)
	{
		m_pCorpLogoRU = NULL;
		m_pMenuLogoLD = NULL;
		m_pMenuLogoRD = NULL;

		pcompassRU = NULL;
		psmallmapRU = NULL;

	}

	LogoManager::~LogoManager()
	{

	}

	//-----------------------------------------------------------------------
	void LogoManager::initInOpenGL()
	{
		pcompassRU = new CompassLogo();
		pcompassRU->initcompass();
		this->addLogoHandle( (CompassLogo*)pcompassRU );

 		psmallmapRU = new SmallMapLogo();
 		this->addLogoHandle( (SmallMapLogo*)psmallmapRU);

		m_pCorpLogoRU = new CorpLogo();
		m_pCorpLogoRU->initCorpLogoRU();
		this->addLogoHandle( (LogoHandle*)m_pCorpLogoRU );
#if 0
		//向LogoManager中注册MenuLogo
		m_pMenuLogoLD = new MenuLogo();
		m_pMenuLogoLD->initMenuLogoLD();
		this->addLogoHandle( (LogoHandle*)m_pMenuLogoLD );

		m_pMenuLogoRD = new MenuLogo();
		m_pMenuLogoRD->initMenuLogoRD();
		this->addLogoHandle( (LogoHandle*)m_pMenuLogoRD );
#endif
	}

	//-----------------------------------------------------------------------
	void LogoManager::uninitInOpenGL()
	{
		if ( m_pCorpLogoRU )
		{
			delete m_pCorpLogoRU;
			m_pCorpLogoRU = NULL;
		}

		//从LogoManager中移除MenuLogo,同时释放指针内存
		if ( m_pMenuLogoLD )
		{
			delete m_pMenuLogoLD;
			m_pMenuLogoLD = NULL;
		}

		if ( m_pMenuLogoRD )
		{
			delete m_pMenuLogoRD;
			m_pMenuLogoRD = NULL;
		}

		if ( pcompassRU )
		{
			delete pcompassRU;
			pcompassRU = NULL;
		}

		if ( psmallmapRU)
		{
			delete psmallmapRU;
			psmallmapRU = NULL;
		}

		//容器vector中存储由子类强制类型转换为父类的指针，当以上delete子类
		//指针后父类指针空间已释放不可在delete，但需指定其为NULL
		vector<LogoHandle*>::iterator itr = m_LogoHandleList.begin();
		vector<LogoHandle*>::iterator itr_end = m_LogoHandleList.end();

		for ( ; itr != itr_end; itr++ )
		{
			if( *itr )
			{
				//此处切不可delete
				*itr = NULL;
			} 
		}

		m_LogoHandleList.clear();

	}

	//-----------------------------------------------------------------------
	bool LogoManager::addLogoHandle( LogoHandle* handle )
	{
		vector<LogoHandle*>::iterator itr = m_LogoHandleList.begin();
		vector<LogoHandle*>::iterator itr_end = m_LogoHandleList.end();

		while( itr != itr_end )
		{
			if ( *itr == handle )
			{
				return false;
			}
			else
			{
				itr ++;
			}
		}

		m_LogoHandleList.push_back( handle );
		return true;
	}

	//-----------------------------------------------------------------------
	bool LogoManager::removeLogoHandle( LogoHandle* handle )
	{
		vector<LogoHandle*>::iterator itr = m_LogoHandleList.begin();
		vector<LogoHandle*>::iterator itr_end = m_LogoHandleList.end();

		while( itr != itr_end )
		{
			if ( *itr == handle )
			{
				m_LogoHandleList.erase( itr );
				return true;
			}
			else
			{
				itr++;
			}
		}

		return false;
	}

	//-----------------------------------------------------------------------
	void LogoManager::renderAllLogo()
	{
		vector<LogoHandle*>::iterator itr = m_LogoHandleList.begin();
		vector<LogoHandle*>::iterator itr_end = m_LogoHandleList.end();

		for ( ; itr != itr_end; itr++ )
		{
			(*itr)->render();
		}
	}

//-------------------------------------------------------------------------
	void LogoManager::reset()
	{

	}

//---------------------------------------------------------------------------
	void LogoManager::OutPutHawkeyeMapInSky(string _filename)
	{
		if ( psmallmapRU != NULL )
		{
			psmallmapRU->OutPutHawkeyeMapInSky(_filename);
		}
	}

	bool LogoManager::initialise()
	{
		m_pContourRenderCommand = new LogoRenderCommand;

		vgKernel::RenderCommandFacade::AddCommand( m_pContourRenderCommand );

		return true;
	}

	bool LogoManager::shutdown()
	{
		if (m_pContourRenderCommand != NULL)
		{
			vgKernel::RenderCommandFacade::RemoveCommand(m_pContourRenderCommand);
			m_pContourRenderCommand = NULL;
		}

		return true;
	}
}//namespace vgLogo




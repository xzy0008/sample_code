


#include <vgStableHeaders.h>
#include <vgVisualEffects/vgviBackgroundManager.h>
#include <vgVisualEffects/vgviDlgVgviBackground.h>

#include <vgConf/vgcoProjectConfig.h>
#include <vgConf/vgcoProjectConfigRegProxy.h>
#include <vgVisualEffects/vgviDefinition.h>
#include <vgKernel/vgkTrace.h>
#include <vgVisualEffects/vgviRenderCommand.h>


namespace vgVisualEffects {
	

	/**
		 在这里创建project config
	*/
	vgConf::ProjectConfigRegProxy bg_project_reg1( 
		VG_VISUALEFFECTS_STR , "background_R" , "0.5" );

	vgConf::ProjectConfigRegProxy bg_project_reg2( 
		VG_VISUALEFFECTS_STR , "background_G" , "0.6" );

	vgConf::ProjectConfigRegProxy bg_project_reg3( 
		VG_VISUALEFFECTS_STR , "background_B" , "0.8" );

	vgConf::ProjectConfigRegProxy bg_project_reg4( 
		VG_VISUALEFFECTS_STR , "background_A" , "1.0" );


	bool BackgroundManager::initialise()
	{
		getConfigColorFromXml();
		//setDefaultBackgroundColor();

		return true;
	}
	
	bool BackgroundManager::shutdown()
	{


		return true;
	}
	//----------------------------------------------------------------
	void BackgroundManager::configBackground()
	{
		DlgVgviBackground dlg;

		int ret= dlg.DoModal();

		if ( ret == IDOK )
		{
			setCurrentBackgroundColor(
				dlg.getBackgroundColor() );
		}
		
	}
	//----------------------------------------------------------------
	void BackgroundManager::renderBegin()
	{
		glClearColor(
			_backgroundColor.r,
			_backgroundColor.g,
			_backgroundColor.b,
			_backgroundColor.a );
	}
	//----------------------------------------------------------------
	void BackgroundManager::setDefaultBackgroundColor()
	{
		_backgroundColor = ColorValu::DEFAULT;
	}
	//----------------------------------------------------------------
	void BackgroundManager::getConfigColorFromXml()
	{
		_backgroundColor.r = VG_PROJCONF_GET_FLOAT( VG_VISUALEFFECTS_STR , "background_R" );
		_backgroundColor.g = VG_PROJCONF_GET_FLOAT( VG_VISUALEFFECTS_STR , "background_G" );
		_backgroundColor.b = VG_PROJCONF_GET_FLOAT( VG_VISUALEFFECTS_STR , "background_B" );
		_backgroundColor.a = VG_PROJCONF_GET_FLOAT( VG_VISUALEFFECTS_STR , "background_A" );
	}
	//----------------------------------------------------------------
	void BackgroundManager::setCurrentBackgroundColor( const ColorValu& new_bg_color )
	{
		_backgroundColor = new_bg_color;

		setColorToXml();

		notfiyUpdate();
	}
	//----------------------------------------------------------------
	void BackgroundManager::setColorToXml()
	{
		VG_PROJCONF_SET( VG_VISUALEFFECTS_STR , "background_R" , _backgroundColor.r );
		VG_PROJCONF_SET( VG_VISUALEFFECTS_STR , "background_G" , _backgroundColor.g );
		VG_PROJCONF_SET( VG_VISUALEFFECTS_STR , "background_B" , _backgroundColor.b );
		VG_PROJCONF_SET( VG_VISUALEFFECTS_STR , "background_A" , _backgroundColor.a );
	}
	//----------------------------------------------------------------
	void BackgroundManager::readProject()
	{
		getConfigColorFromXml();
	}

	BackgroundManager::BackgroundManager() : Singleton<BackgroundManager>( VGK_SINGLETON_LEFE_VI_BGMGR )
	{
		m_pRenderCommand = new BackGroundRenderCommand;

		vgKernel::RenderCommandFacade::AddCommand(m_pRenderCommand);

		VGK_TRACE(_T("BackgroundManager created."));
	}

	BackgroundManager::~BackgroundManager()
	{
		vgKernel::RenderCommandFacade::RemoveCommand(m_pRenderCommand);
		m_pRenderCommand = NULL;

		TRACE("Destory BackGround Render Command. \n");

		VGK_TRACE(_T("BackgroundManager destroyed."));
	}
	//----------------------------------------------------------------

}// end of namespace vgVisualEffects

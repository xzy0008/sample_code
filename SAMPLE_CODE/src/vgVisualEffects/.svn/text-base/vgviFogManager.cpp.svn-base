


#include <vgStableHeaders.h>
#include <vgVisualEffects/vgviFogManager.h>

#include <vgConf/vgcoProjectConfig.h>
#include <vgConf/vgcoProjectConfigRegProxy.h>
#include <vgKernel/vgkTrace.h>
#include <vgVisualEffects/vgviRenderCommand.h>

namespace vgVisualEffects {
	

	/**
		在这里创建project config
	*/
	vgConf::ProjectConfigRegProxy fog_project_reg1( VG_VISUALEFFECTS_STR ,
		VG_FOG_NAME_ENABLE , VG_FOG_DEFAULT_ENABLE_STR );
	
	vgConf::ProjectConfigRegProxy fog_project_reg2( VG_VISUALEFFECTS_STR ,
		VG_FOG_NAME_START , VG_FOG_DEFAULT_START_STR );

	vgConf::ProjectConfigRegProxy fog_project_reg3( VG_VISUALEFFECTS_STR ,
		VG_FOG_NAME_END , VG_FOG_DEFAULT_END_STR );

	vgConf::ProjectConfigRegProxy fog_project_reg4( VG_VISUALEFFECTS_STR ,
		VG_FOG_NAME_DENSITY , VG_FOG_DEFAULT_DENSITY_STR );

	vgConf::ProjectConfigRegProxy fog_project_reg5( VG_VISUALEFFECTS_STR ,
		VG_FOG_NAME_MODE , VG_FOG_DEFAULT_MODE_STR );

	vgConf::ProjectConfigRegProxy fog_project_reg6( VG_VISUALEFFECTS_STR ,
		VG_FOG_NAME_COLOR_R , VG_FOG_DEFAULT_COLOR_R_STR );

	vgConf::ProjectConfigRegProxy fog_project_reg7( VG_VISUALEFFECTS_STR ,
		VG_FOG_NAME_COLOR_G , VG_FOG_DEFAULT_COLOR_G_STR );
	
	vgConf::ProjectConfigRegProxy fog_project_reg8( VG_VISUALEFFECTS_STR ,
		VG_FOG_NAME_COLOR_B , VG_FOG_DEFAULT_COLOR_B_STR );

	vgConf::ProjectConfigRegProxy fog_project_reg9( VG_VISUALEFFECTS_STR ,
		VG_FOG_NAME_COLOR_A , VG_FOG_DEFAULT_COLOR_A_STR );


	//----------------------------------------------------------------
	FogManager::FogManager() 
		: Singleton<FogManager>( VGK_SINGLETON_LEFE_VI_FOGMGR )
	{
		//_fogStart = VG_FOG_DEFAULT_START;
		//_fogEnd = VG_FOG_DEFAULT_END;
		//_fogDensity = VG_FOG_DEFAULT_DENSITY;
		//_fogMod = VG_FOG_DEFAULT_MODE;
		//_enabled = VG_FOG_DEFAULT_ENABLE;

		//_fogColor.r = VG_FOG_DEFAULT_COLOR_R;
		//_fogColor.g = VG_FOG_DEFAULT_COLOR_G;
		//_fogColor.b = VG_FOG_DEFAULT_COLOR_B;
		//_fogColor.a = VG_FOG_DEFAULT_COLOR_A;


		m_pFogRenderCommad = new FogRenderCommand;
		vgKernel::RenderCommandFacade::AddCommand(m_pFogRenderCommad);

		VGK_TRACE(_T("FogManager created."));
	}
	//----------------------------------------------------------------
	FogManager::~FogManager()
	{
		vgKernel::RenderCommandFacade::RemoveCommand(m_pFogRenderCommad);

		m_pFogRenderCommad = NULL;

		TRACE("Destory Fog Render Command. \n");

		VGK_TRACE(_T("FogManager destroyed."));
	}
	//----------------------------------------------------------------
	GLint FogManager::getGlintFromMod( const FogMode& fogmod )
	{
		switch( fogmod )
		{
		case FOG_MOD_LINEAR:
			return GL_LINEAR;
		case FOG_MOD_EXP:
			return GL_EXP;
		case FOG_MOD_EXP2:
			return GL_EXP2;
		default:
			assert(0);
			return GL_LINEAR;
		}
	}
	//----------------------------------------------------------------
	void FogManager::renderBegin()
	{
		if ( !_enabled )
		{
			glDisable( GL_FOG );
			return;
		}

		glEnable( GL_FOG );
		glHint( GL_FOG_HINT, GL_NICEST );
		//glFogi( GL_FOG_COORD_SRC , GL_FRAGMENT_DEPTH );

		GLint mode = getGlintFromMod( _fogMod );

		glFogi( GL_FOG_MODE , mode );
		glFogf( GL_FOG_START , _fogStart );
		glFogf( GL_FOG_END , _fogEnd );
		glFogf( GL_FOG_DENSITY , _fogDensity );
		glFogfv( GL_FOG_COLOR, _fogColor.ptr() );
	}
	//----------------------------------------------------------------
	void FogManager::readProject()
	{
		readConfigFromXml();
	}
	//----------------------------------------------------------------
	void FogManager::saveProject()
	{
		saveConfigToXml();
	}
	//----------------------------------------------------------------
	void FogManager::readConfigFromXml()
	{
		_enabled = VG_PROJCONF_GET_BOOL( VG_VISUALEFFECTS_STR , 
			VG_FOG_NAME_ENABLE );

		_fogStart = VG_PROJCONF_GET_FLOAT( VG_VISUALEFFECTS_STR , 
			VG_FOG_NAME_START );

		_fogEnd = VG_PROJCONF_GET_FLOAT( VG_VISUALEFFECTS_STR , 
			VG_FOG_NAME_END );

		_fogDensity = VG_PROJCONF_GET_FLOAT( VG_VISUALEFFECTS_STR , 
			VG_FOG_NAME_DENSITY );

		_fogMod = (FogMode) VG_PROJCONF_GET_INT( VG_VISUALEFFECTS_STR , 
			VG_FOG_NAME_MODE ) ;


		_fogColor.r = VG_PROJCONF_GET_FLOAT( VG_VISUALEFFECTS_STR , 
			VG_FOG_NAME_COLOR_R );

		_fogColor.g = VG_PROJCONF_GET_FLOAT( VG_VISUALEFFECTS_STR , 
			VG_FOG_NAME_COLOR_G );

		_fogColor.b = VG_PROJCONF_GET_FLOAT( VG_VISUALEFFECTS_STR , 
			VG_FOG_NAME_COLOR_B );

		_fogColor.a = VG_PROJCONF_GET_FLOAT( VG_VISUALEFFECTS_STR , 
			VG_FOG_NAME_COLOR_A );
	}
	//----------------------------------------------------------------
	void FogManager::saveConfigToXml()
	{
		VG_PROJCONF_SET( VG_VISUALEFFECTS_STR , 
			VG_FOG_NAME_ENABLE , _enabled );

		VG_PROJCONF_SET( VG_VISUALEFFECTS_STR , 
			VG_FOG_NAME_START , _fogStart );

		VG_PROJCONF_SET( VG_VISUALEFFECTS_STR , 
			VG_FOG_NAME_END , _fogEnd );

		VG_PROJCONF_SET( VG_VISUALEFFECTS_STR , 
			VG_FOG_NAME_DENSITY , _fogDensity );

		VG_PROJCONF_SET( VG_VISUALEFFECTS_STR , 
			VG_FOG_NAME_MODE , (int)_fogMod );

		VG_PROJCONF_SET( VG_VISUALEFFECTS_STR , 
			VG_FOG_NAME_COLOR_R , _fogColor.r );

		VG_PROJCONF_SET( VG_VISUALEFFECTS_STR , 
			VG_FOG_NAME_COLOR_G , _fogColor.g );

		VG_PROJCONF_SET( VG_VISUALEFFECTS_STR , 
			VG_FOG_NAME_COLOR_B , _fogColor.b );

		VG_PROJCONF_SET( VG_VISUALEFFECTS_STR , 
			VG_FOG_NAME_COLOR_A , _fogColor.a );

	}
	//----------------------------------------------------------------
	bool FogManager::initialise()
	{
		readConfigFromXml();

		return true;
	}

	bool FogManager::shutdown()
	{
		return true;
	}
	//----------------------------------------------------------------
	void FogManager::getFogParams( float& fogstart , float& fogend , float& fogdensity , FogMode& fogmode , ColorValu& fogcolor )
	{
		fogstart = _fogStart;
		fogend = _fogEnd;
		fogdensity = _fogDensity;
		fogmode = _fogMod;
		fogcolor = _fogColor;
	}
	//----------------------------------------------------------------
	void FogManager::setFogParams( const float& fogstart , const float& fogend , const float& fogdensity , const FogMode& fogmode , const ColorValu& fogcolor )
	{
		_fogStart = fogstart  ;
		_fogEnd = fogend  ;
		_fogDensity = fogdensity  ;
		_fogMod = fogmode  ;
		_fogColor = fogcolor  ;
	}
	//----------------------------------------------------------------


}// end of namespace vgVisualEffects

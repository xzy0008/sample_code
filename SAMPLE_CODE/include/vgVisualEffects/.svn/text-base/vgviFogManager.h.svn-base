


#ifndef __VGVIFOGMANAGER_H__
#define __VGVIFOGMANAGER_H__


#include <vgVisualEffects/vgviDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSingleton.h>
#include <vgVisualEffects/vgviUpdateObserver.h>
#include <vgVisualEffects/vgviDefinition.h>
#include <vgVisualEffects/vgviColorValue.h>
#include <vgKernel/vgkRenderCommandManager.h>
	
namespace vgVisualEffects {


	/**
		@date 	2008/12/02  9:17	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGVI_EXPORT FogManager : 
		public vgKernel::Singleton<FogManager>,
		public Updater
	{
	public:
		enum FogMode
		{
			FOG_MOD_LINEAR = 0,
			FOG_MOD_EXP	=1,
			FOG_MOD_EXP2 = 2
		};

	private:
		friend class vgKernel::Singleton<FogManager>;
	private:
		FogManager();

	public:
		~FogManager();

	protected:
		virtual bool initialise();
		virtual bool shutdown();

	public:

		virtual void reset(){initialise();}

		void renderBegin();


		void readProject();

		void saveProject();

		bool getEnabledFlag() const
		{
			return _enabled;
		}

		void setEnabledFlag( const bool& enable_it )
		{
			_enabled = enable_it;
		}

		void getFogParams( float& fogstart , 
			float& fogend , float& fogdensity , FogMode& fogmode , 
			ColorValu& fogcolor );
		
		void setFogParams( const float& fogstart , 
			const float& fogend , const float& fogdensity , const FogMode& fogmode , 
			const ColorValu& fogcolor );

		/**
			直接访问内部数据的接口.用于GPU操作
		*/
		float* getFogColorValue()
		{
			return &_fogColor.r;
		}

		float getFogStart() const
		{
			return _fogStart;
		}

		float getFogEnd() const
		{
			return _fogEnd;
		}

	private:

		GLint getGlintFromMod( const FogMode& fogmod );

		void readConfigFromXml();
		void saveConfigToXml();

	private:

		bool _enabled;

		float _fogStart;
		float _fogEnd;
		float _fogDensity;

		FogMode _fogMod;

		ColorValu _fogColor;

		vgKernel::RenderCommand *m_pFogRenderCommad;
	};
	
	
}// end of namespace vgVisualEffects
	


#endif // end of __VGVIFOGMANAGER_H__
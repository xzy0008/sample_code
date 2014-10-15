
#pragma  once

#include <vgKernel/vgkForward.h>
#include <vgEntry/vgBaseEntryEx.h>
#include <vgVisualEffects/vgviUpdateObserver.h>
#include <vgVisualEffects/vgviFogManager.h>
#include <vgUIController/vgPropertyPage.h>
#include <vgKernel/vgkRendererObserver.h>


	/**
		@date 	2008/09/11  20:49	
		@author  leven

		@brief 	

		@see    
	*/
	class  VGUI_EXPORT vgFogEntry :	public vgBaseEntryEx ,
		public vgVisualEffects::UpdateObserver
	{
	public:

		vgFogEntry();

		virtual ~vgFogEntry(void);

		/**
			继承UpdateObserver的接口
		*/
		virtual void onUpdate();


		virtual String GetName()
		{
#if VGK_LANG_CHS
			return "雾效";
#else
			return "Fog";
#endif
		}

	protected:

		virtual PropertiesParamVector& pushPropertiesParam( 
			PropertiesParamVector& params );

		virtual void updateUIFromInternal();

		virtual void updateInternalFromUI(const String& changed_param_name );

		String getDescriptionFromFogMode( 
			const vgVisualEffects::FogManager::FogMode& mode );

		vgVisualEffects::FogManager::FogMode getFogModeFromDescription(
			const String& des );
		

	private:

		bool _turnedOn;

		COLORREF _fogColorRef;

		String _fogMod;

		float _fogStart;
		float _fogEnd;

		float _fogDensity;
	};




#pragma  once

#include <vgKernel/vgkForward.h>

#include <vgVisualEffects/vgviUpdateObserver.h>
#include <vgVisualEffects/vgviColorValue.h>
#include <vgEntry/vgBaseEntryEx.h>
#include <vgUIController/vgPropertyPage.h>
#include <vgKernel/vgkRendererObserver.h>

	/**
		@date 	2008/09/11  20:49	
		@author  leven

		@brief 	

		@see    
	*/
	class  VGUI_EXPORT vgBackgroundEntry :	public vgBaseEntryEx ,
		public vgVisualEffects::UpdateObserver
	{
	public:

		vgBackgroundEntry();

		virtual ~vgBackgroundEntry(void);

		/**
			继承UpdateObserver的接口
		*/
		virtual void onUpdate();


		virtual String GetName()
		{
#if VGK_LANG_CHS
			return "背景颜色";
#else
			return "Background Color";
#endif
		}

	protected:

		virtual PropertiesParamVector& pushPropertiesParam( 
			PropertiesParamVector& params );

		virtual void updateUIFromInternal();

		virtual void updateInternalFromUI(const String& changed_param_name );

	private:

		COLORREF _colorRef;
	};

	

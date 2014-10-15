


#ifndef __VGVIBACKGROUNDMANAGER_H__
#define __VGVIBACKGROUNDMANAGER_H__

#include <vgVisualEffects/vgviDefinition.h>

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSingleton.h>
#include <vgVisualEffects/vgviColorValue.h>
#include <vgVisualEffects/vgviUpdateObserver.h>
#include <vgKernel/vgkRenderCommandManager.h>

namespace vgVisualEffects {

	/**
		@date 	2008/12/02  9:18	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGVI_EXPORT BackgroundManager : 
		public vgKernel::Singleton<BackgroundManager>,
		public Updater
	{
		friend class vgKernel::Singleton<BackgroundManager>;
	private:
		BackgroundManager();

	public:

		~BackgroundManager();

	protected:

		virtual bool initialise();

		virtual bool shutdown();

	public:

		virtual void reset(){ initialise(); }

		ColorValu getCurrentBackgroundColor()
		{
			return _backgroundColor;
		}

		void setCurrentBackgroundColor( const ColorValu& new_bg_color );

		/**
			≈‰÷√±≥æ∞—’…´.
		*/
		void configBackground();

		void renderBegin();

		bool uninitBeforeOpenGLDestroy()
		{
			return true;
		}

		void setDefaultBackgroundColor();

		void readProject();
 
	private:

		void getConfigColorFromXml();

		void setColorToXml();

	private:

		ColorValu _backgroundColor;
		
		vgKernel::RenderCommand *m_pRenderCommand;

	};


	
}// end of namespace vgVisualEffects
	


#endif // end of __VGVIBACKGROUNDMANAGER_H__
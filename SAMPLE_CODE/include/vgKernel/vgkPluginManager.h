


#ifndef __VGKPLUGINMANAGER_H__
#define __VGKPLUGINMANAGER_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSingleton.h>
#include <vgKernel/vgkPlugin.h>
#include <vgKernel/vgkPluginLoader.h>

#include <vgKernel/vgkRenderCommand.h>

namespace vgKernel {

	/**
		@date 	2009/06/18  10:10	
		@author  xy
	
		@brief 	
	
		@see    
	*/
	class VGK_EXPORT PluginManager : 
		public Singleton<PluginManager>
	{
		friend class vgKernel::Singleton<PluginManager>;
		//成员函数
	public :
		PluginManager();
		virtual ~PluginManager();
	protected:

		virtual bool initialise();
		virtual bool shutdown();
		
		vgKernel::RenderCommand *m_pRenderPlugin;
	public:


		bool registerLoader( PluginLoader* loader );
		
		void resetAllPlugins();
	
		bool loadPlugin( const String& dll_name );

		bool unloadPlugin( const String& dll_name );

		//void loadRightMenuPlugin(const String& plugin_name, CMenu *RightMenu);
		
		bool registerPlugin( Plugin* plug );

		void renderAllPlugins();
		
		PluginPointerVec* getPluginVecRef() { return &_plugins; }

		PluginLoaderPointerVec* getPluginLoaderRef() {return &_loaders;}

		// 注意，只要名字一样，plugin被认为是相同的
		Plugin* checkExist( Plugin* plug );

		void uninitBeforeOpenGLDestroy();

		Plugin* getPluginRef( const String& dll_name );


		void readProjectUsingPlugins( const String& projpath , 
			const String& projname);

		void saveProjectUsingPlugins( const String& projpath , 
			const String& projname);

	private:

		PluginPointerVec _plugins;

		int 	m_FirstCmdWndId;

		PluginLoaderPointerVec _loaders;
	};
	
	
}// end of namespace vgKernel
	


#endif // end of __VGKPLUGINMANAGER_H__
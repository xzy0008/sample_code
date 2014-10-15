


#ifndef __VGKPLUGIN_H__
#define __VGKPLUGIN_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkAbstractEntry.h>

	
namespace vgKernel {

	class Renderer;

typedef void (*VGK_PLUGIN_FUNC)(void);

#define VGK_PLUGIN_DLL_START dllStartPlugin
#define VGK_PLUGIN_DLL_START_STR "dllStartPlugin"


#define VGK_PLUGIN_DLL_END dllEndPlugin
#define VGK_PLUGIN_DLL_END_STR "dllEndPlugin"


#define  PluginHandle HMODULE 

	/**
		@date 	2009/06/18  9:39	
		@author  xy
	
		@brief 	
	
		@see    
	*/
	class Plugin
	{
	public:
		Plugin()
		{
			_dllHandle  = NULL;
		}
		virtual~Plugin()
		{
			
		}
	
	public:

		virtual String getName() = 0;


		// ´ýÐ´
		virtual StringVector getDependences()
		{
			return StringVector();
		}


		// ×¢Òâ¼ÓÔØµÄË³Ðò
		virtual bool initInOpenGL()
		{
			return true;
		}

		virtual void renderBegin()
		{

		}
		virtual void renderFirst()
		{

		}
		virtual void renderSecond()
		{

		}
		virtual void render()
		{

		}
		virtual void renderLast()
		{

		}
		virtual void renderEnd()
		{

		}

		virtual bool uninitInOpenGLFirst()
		{
			return true;
		}

		virtual bool uninitInOpenGLSecond()
		{
			return true;
		}

		virtual bool uninitInOpenGL()
		{
			return true;
		}

		virtual bool uninitInOpenGLEnd()
		{
			return true;
		}

		virtual void resetBegin()
		{

		}
		virtual void reset()
		{

		}
		virtual void resetEnd()
		{

		}


		virtual void readProjectBegin( const String& projpath , 
			const String& projname)
		{

		}

		virtual void readProject( const String& projpath , 
			const String& projname)
		{

		}

		virtual void readProjectEnd( const String& projpath , 
			const String& projname)
		{

		}

		virtual void saveProjectBegin(  const String& projpath ,
			const String& projname )
		{

		}

		virtual void saveProject(  const String& projpath ,
			const String& projname )
		{

		}


		virtual void saveProjectEnd(  const String& projpath ,
			const String& projname )
		{

		}


		virtual vgKernel::AbstractEntry* rendererToEntry( vgKernel::Renderer* renderer )
		{
			return NULL;
		}

		PluginHandle getPluginHandle()
		{
			return _dllHandle;
		}

		void setPluginHandle( PluginHandle handle )
		{
			_dllHandle = handle;
		}

		void* getProcAddr(const char* func_name )
		{
			void* ret = (void*)GetProcAddress( _dllHandle , func_name );
			SetLastError( NO_ERROR );

			return ret;
		}

		int getCmdWndId() { return m_cmdWndId; }

		void setCmdWndId(int id) { m_cmdWndId = id; }

		//int getCmdWindowId() {return m_cmdWindowId;}

		//void setCmdWindowId(int id) {m_cmdWindowId = id;}

	private:

		PluginHandle _dllHandle;

		int m_cmdWndId;

		int m_cmdWindowId;

	};
	

	typedef std::vector<Plugin*> PluginPointerVec;
	
}// end of namespace vgKernel
	


#endif // end of __VGKPLUGIN_H__
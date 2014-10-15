



#include <vgStableHeaders.h>
#include <vgKernel/vgkPluginManager.h>
#include <vgKernel/vgkRenderCommandManager.h>
#include <vgKernel/vgkPluginRenderCmd.h>

namespace vgKernel {
	
	
	struct PluginVecRenderBegin
	{
		inline void operator() ( Plugin* item) 
		{
			item->renderBegin();
		}
	};

	struct PluginVecRenderFirst
	{
		inline void operator() ( Plugin* item) 
		{
			item->renderFirst();
		}
	};

	struct PluginVecRenderSecond
	{
		inline void operator() ( Plugin* item) 
		{
			item->renderSecond();
		}
	};

	struct PluginVecRender
	{
		inline void operator() ( Plugin* item) 
		{
			item->render();
		}
	};

	struct PluginVecRenderLast
	{
		inline void operator() ( Plugin* item) 
		{
			item->renderLast();
		}
	};

	struct PluginVecRenderEnd
	{
		inline void operator() ( Plugin* item) 
		{
			item->renderEnd();
		}
	};

	struct PluginVecUninitInOpenGLFirst
	{
		inline void operator() ( Plugin* item) 
		{
			item->uninitInOpenGLFirst();
		}
	};

	struct PluginVecUninitInOpenGLSecond
	{
		inline void operator() ( Plugin* item) 
		{
			item->uninitInOpenGLSecond();
		}
	};

	struct PluginVecUninitInOpenGLThird
	{
		inline void operator() ( Plugin* item) 
		{
			item->uninitInOpenGL();
		}
	};

	struct PluginVecUninitInOpenGLEnd
	{
		inline void operator() ( Plugin* item) 
		{
			item->uninitInOpenGLEnd();
		}
	};

	struct PluginVecResetBegin
	{
		inline void operator() ( Plugin* item) 
		{
			item->resetBegin();
		}
	};

	struct PluginVecReset
	{
		inline void operator() ( Plugin* item) 
		{
			item->reset();
		}
	};

	struct PluginVecResetEnd
	{
		inline void operator() ( Plugin* item) 
		{
			item->resetEnd();
		}
	};


	//----------------------------------------------------------------
	PluginManager::PluginManager()
		: Singleton<PluginManager>( VGK_SINGLETON_LEFE_PLUGINMGR )
	{
		m_FirstCmdWndId = 6000;
		//m_FirstCmdWindowId = 7000;

		m_pRenderPlugin = new PluginRenderAll;
		vgKernel::RenderCommandFacade::AddCommand(m_pRenderPlugin);
	}

	PluginManager::~PluginManager()
	{
		vgKernel::RenderCommandFacade::RemoveCommand(m_pRenderPlugin);
	
		assert( _plugins.empty() == true );
	}
	//----------------------------------------------------------------
	bool PluginManager::initialise()
	{	
		return true;
	}
	//----------------------------------------------------------------
	void PluginManager::renderAllPlugins()
	{
	 
		static PluginVecRenderBegin s_renderBegin;
		static PluginVecRenderFirst s_renderFirst;
		static PluginVecRenderSecond s_renderSecond;
		static PluginVecRender s_render;
		static PluginVecRenderLast s_renderLast;
		static PluginVecRenderEnd s_renderEnd;

		for_each( _plugins.begin() , _plugins.end() , s_renderBegin );
		for_each( _plugins.begin() , _plugins.end() , s_renderFirst );
		for_each( _plugins.begin() , _plugins.end() , s_renderSecond );
		for_each( _plugins.begin() , _plugins.end() , s_render );
		for_each( _plugins.begin() , _plugins.end() , s_renderLast );
		for_each( _plugins.begin() , _plugins.end() , s_renderEnd );

	}
	//----------------------------------------------------------------
	bool PluginManager::registerPlugin( Plugin* plug )
	{
		if ( checkExist( plug ) != NULL )
		{
			return false;
		}

		VGK_TRACE( "registerPlugin " + plug->getName() );

		plug->setPluginHandle( GetModuleHandle( plug->getName().c_str() ) );

		if ( plug->initInOpenGL() == true )
		{
			// 分配事件处理CommandWnd ID
			plug->setCmdWndId(m_FirstCmdWndId ++);
			//plug->setCmdWindowId(m_FirstCmdWindowId ++);

			_plugins.push_back( plug );
			return true;
		}
		else
		{
			return false;
		}
	}
	//----------------------------------------------------------------
	Plugin* PluginManager::checkExist( Plugin* plug )
	{
		PluginPointerVec::iterator iter = _plugins.begin();
		PluginPointerVec::iterator iter_end = _plugins.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			if ( *iter == plug ||
				(*iter)->getName() == plug->getName() )
			{
				return *iter;
			}
		}

		return NULL;
	}
	//----------------------------------------------------------------
	bool PluginManager::shutdown()
	{

		return true;
	}
	//----------------------------------------------------------------
	void PluginManager::uninitBeforeOpenGLDestroy()
	{
		static PluginVecUninitInOpenGLFirst s_UninitInOpenGLFirst;
		static PluginVecUninitInOpenGLSecond s_UninitInOpenGLSecond;
		static PluginVecUninitInOpenGLThird s_UninitInOpenGLThird;
		static PluginVecUninitInOpenGLEnd s_UninitInOpenGLEnd;

		for_each( _plugins.begin() , _plugins.end() , s_UninitInOpenGLFirst );
		for_each( _plugins.begin() , _plugins.end() , s_UninitInOpenGLSecond );
		for_each( _plugins.begin() , _plugins.end() , s_UninitInOpenGLThird );
		for_each( _plugins.begin() , _plugins.end() , s_UninitInOpenGLEnd );

		PluginPointerVec::iterator iter = _plugins.begin();
		PluginPointerVec::iterator iter_end = _plugins.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			VGK_PLUGIN_FUNC func = (VGK_PLUGIN_FUNC)
				GetProcAddress( (*iter)->getPluginHandle() ,
				VGK_PLUGIN_DLL_END_STR );

			assert( func != NULL );

			if ( func != NULL )
			{
				(*func)();
#if _DEBUG
				VGK_SHOW( (*iter)->getName() + "	unload ok.\n");
#endif
			}

			FreeLibrary( (*iter)->getPluginHandle() );
			//delete *iter;
		}

		_plugins.clear();
	}
	//----------------------------------------------------------------
	bool PluginManager::loadPlugin( const String& dll_name )
	{
		if ( getPluginRef( dll_name ) != NULL )
		{
			// 已经载入了
			VGK_SHOW("already loaded!");
			return true;
		}

		PluginHandle han = LoadLibraryEx(dll_name.c_str(), NULL, 
			 LOAD_WITH_ALTERED_SEARCH_PATH );

		if ( han == NULL )
		{
#if 0
			int nErrorCode = GetLastError();
			std::ostringstream os;
			os << "导入DLL:" 
				<< dll_name.c_str() << "出错，错误代号是:" << nErrorCode
				<< "\n出错原因:可能是因为该DLL所依赖的底层DLL无法找到，请核查！";
			//AfxMessageBox( os.str().c_str() );
			vgKernel::SystemUtility::showModelDialog( os.str() );
#endif
			VGK_TRACE( dll_name + "  " + "han == NULL");
			return false;
		}

		assert( GetModuleHandle( dll_name.c_str() ) == han );

		VGK_PLUGIN_FUNC func = (VGK_PLUGIN_FUNC)
			GetProcAddress( han , VGK_PLUGIN_DLL_START_STR );

		assert( func != NULL );

		if ( func != NULL )
		{
			(*func)();
		}
		else
		{
			VGK_TRACE( "func == NULL    !!");
		}


		PluginLoaderPointerVec::iterator iter = _loaders.begin();
		PluginLoaderPointerVec::iterator iter_end = _loaders.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			(*iter)->loadPlugin( dll_name );
		}
#if _DEBUG	
		VGK_SHOW( dll_name + "	load ok.\n");
#endif
		return true;
	}
	//----------------------------------------------------------------
	Plugin* PluginManager::getPluginRef( const String& dll_name )
	{
		String dllName = vgKernel::StringUtility::
			getFilenameFromAbsolutePath(dll_name);

		PluginPointerVec::iterator iter = _plugins.begin();
		PluginPointerVec::iterator iter_end = _plugins.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			if ( (*iter)->getName() == dllName )
			{
				return *iter;
			}
		}

		return NULL;
	}
	//----------------------------------------------------------------
	bool PluginManager::unloadPlugin( const String& dll_name )
	{


		{
			PluginLoaderPointerVec::iterator iter = _loaders.begin();
			PluginLoaderPointerVec::iterator iter_end = _loaders.end();

			for ( ; iter != iter_end ; ++ iter )
			{
				(*iter)->unloadPlugin( dll_name );
			}

		}


		PluginPointerVec::iterator iter = _plugins.begin();

		while ( iter != _plugins.end() )
		{
			if ( (*iter)->getName() == dll_name )
			{
				Plugin* plug = *iter;
				plug->uninitInOpenGLFirst();
				plug->uninitInOpenGLSecond();
				plug->uninitInOpenGL();
				plug->uninitInOpenGLEnd();

				VGK_PLUGIN_FUNC func = (VGK_PLUGIN_FUNC)
					GetProcAddress( (*iter)->getPluginHandle() ,
					VGK_PLUGIN_DLL_END_STR );

				assert( func != NULL );

				if ( func != NULL )
				{
					(*func)();
				}

				delete *iter;
				FreeLibrary( (*iter)->getPluginHandle() );

				iter = _plugins.erase( iter );
#if _DEBUG

				VGK_SHOW( dll_name + "	unload ok.\n");
#endif
			}
			else
			{
				++iter;
			}
		}

		return true;
	}
	//----------------------------------------------------------------
	void PluginManager::resetAllPlugins()
	{
		static PluginVecResetBegin s_1;
		static PluginVecReset s_2;
		static PluginVecResetEnd s_3;

		for_each( _plugins.begin() , _plugins.end() , s_1 );
		for_each( _plugins.begin() , _plugins.end() , s_2 );
		for_each( _plugins.begin() , _plugins.end() , s_3 );
	}
	//----------------------------------------------------------------
	void PluginManager::readProjectUsingPlugins( const String& projpath , 
		const String& projname )
	{
		PluginPointerVec::iterator iter;
		PluginPointerVec::iterator iter_end = _plugins.end();

		iter = _plugins.begin();
		for ( ; iter != iter_end ; ++ iter )
		{
			(*iter)->readProjectBegin( projpath , projname );
		}

		iter = _plugins.begin();
		for ( ; iter != iter_end ; ++ iter )
		{
			(*iter)->readProject( projpath , projname );
		}

		iter = _plugins.begin();
		for ( ; iter != iter_end ; ++ iter )
		{
			(*iter)->readProjectEnd( projpath , projname );
		}

		return;
	}
	//----------------------------------------------------------------
	void PluginManager::saveProjectUsingPlugins( const String& projpath ,
		const String& projname )
	{
		PluginPointerVec::iterator iter;
		PluginPointerVec::iterator iter_end = _plugins.end();

		iter = _plugins.begin();
		for ( ; iter != iter_end ; ++ iter )
		{
			(*iter)->saveProjectBegin( projpath , projname );
		}

		iter = _plugins.begin();
		for ( ; iter != iter_end ; ++ iter )
		{
			(*iter)->saveProject( projpath , projname );
		}

		iter = _plugins.begin();
		for ( ; iter != iter_end ; ++ iter )
		{
			(*iter)->saveProjectEnd( projpath , projname );
		}

		return;
	}

	bool PluginManager::registerLoader( PluginLoader* loader )
	{
		if ( loader == NULL )
		{
			return false;
		}

		PluginLoaderPointerVec::iterator iter = _loaders.begin();
		PluginLoaderPointerVec::iterator iter_end = _loaders.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			if ( *iter == loader )
			{
				return false;
			}
		}

		_loaders.push_back( loader );

		return true;
	}

	//---------------------------------------------------------------
	//----------------------------------------------------------------



}// end of namespace vgKernel

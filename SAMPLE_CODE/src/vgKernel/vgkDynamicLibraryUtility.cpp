


#include <vgStableHeaders.h>
#include <vgKernel/vgkDynamicLibraryUtility.h>
#include <vgKernel/vgkPluginManager.h>


namespace vgKernel {


	bool checkDLLisLoad( const char* dllname )
	{
		Plugin* pl = PluginManager::getSingleton().getPluginRef( dllname );

		return pl !=NULL;
		//DWORD err =  GetLastError();
		//assert( err == NO_ERROR );
		//HMODULE mod_ = GetModuleHandle( dllname );
		//SetLastError( NO_ERROR );

		//return mod_ == NULL ? FALSE : TRUE;
	}

	bool loadDLL( const char* dllname )
	{
		return PluginManager::getSingleton().loadPlugin( dllname );
	}

	bool unloadDLL( const char* dllname )
	{
		return PluginManager::getSingleton().unloadPlugin( dllname );
	}
}// end of namespace vgKernel

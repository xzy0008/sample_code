
#include <vgStableHeaders.h>

#include <vgSoundDLL/vgSoundPlugin.h>

#include <vgSound/vgSoundManager.h>
#include <vgEntry/vgSound3DEntry.h>
#include <vgEntry/vgSoundBackgroundEntry.h>


namespace	vgSound
{

	bool SoundPlugin::uninitInOpenGL()
	{
		vgSound::SoundManager::getSingleton().unloadData();

		return true;
	}

	vgKernel::AbstractEntry* SoundPlugin::rendererToEntry( vgKernel::Renderer* renderer )
	{
		vgKernel::RendererType type = 
			renderer->getType();

		vgBaseEntry* ret = NULL;

		switch( type )
		{
				// SoundManager
		case vgSound::RENDERER_TYPE_SOUND:
				ret = new vgSound3DEntry( (vgSound::Sound3D*)renderer );
				break;

		case vgSound::RENDERER_TYPE_SOUNDBACK:
			ret = new vgSoundBackgroundEntry( (vgSound::SoundBackground*)renderer );
			break;

		default:
			break;
		}

		return ret;
	}

	bool SoundPlugin::initInOpenGL()
	{

		//vgKernel::Plugin *plugin = vgKernel::PluginManager::getSingleton().getPluginRef( VGSOUND_DLL_NAME );

		HWND hWnd = AfxGetApp()->m_pMainWnd->GetSafeHwnd();

		//HWND hWnd = this->GetSafeHwnd();

		assert( hWnd != NULL);

		SoundManager::getSingleton().initialise( hWnd );



		return true ;
	}
}
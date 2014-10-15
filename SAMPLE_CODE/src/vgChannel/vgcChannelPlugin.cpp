


#include <vgStableHeaders.h>
#include <vgChannel/vgcChannelPlugin.h>
#include <vgChannel/vgcChannelManager.h>

namespace vgChannel {



	bool ChannelPlugin::initInOpenGL()
	{
		HWND hWND = AfxGetApp()->GetMainWnd()->GetActiveWindow()->GetSafeHwnd();
		HDC hDC = ::GetDC(hWND);

		//FontManager::getSingleton().initialiseFonts(hDC);
		return true;
	}

	void ChannelPlugin::render()
	{
	}

	bool ChannelPlugin::uninitInOpenGL()
	{
		//FontManager::getSingleton().uninitBeforeOpenGLDestroy();
		return true;
	}

	void ChannelPlugin::reset()
	{
		//FontManager::getSingleton().reset();
		return;
	}

	void ChannelPlugin::readProject( const String& projpath , const String& projname )
	{
	}

	void ChannelPlugin::saveProject( const String& projpath , const String& projname )
	{
	}

}// end of namespace vgChannel

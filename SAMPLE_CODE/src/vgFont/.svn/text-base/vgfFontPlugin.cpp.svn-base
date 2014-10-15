


#include <vgStableHeaders.h>
#include <vgFont/vgfFontPlugin.h>
#include <vgFont/vgfFontManager.h>

namespace vgFont {



	bool FontPlugin::initInOpenGL()
	{
		HWND hWND = AfxGetApp()->GetMainWnd()->GetActiveWindow()->GetSafeHwnd();
		HDC hDC = ::GetDC(hWND);

		FontManager::getSingleton().initialiseFonts(hDC);
		return true;
	}

	void FontPlugin::render()
	{
	}

	bool FontPlugin::uninitInOpenGL()
	{
		FontManager::getSingleton().uninitBeforeOpenGLDestroy();
		return true;
	}

	void FontPlugin::reset()
	{
		FontManager::getSingleton().reset();
		return;
	}

	void FontPlugin::readProject( const String& projpath , const String& projname )
	{
	}

	void FontPlugin::saveProject( const String& projpath , const String& projname )
	{
	}
}// end of namespace vgFont

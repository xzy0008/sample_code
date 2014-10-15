
#include <vgStableHeaders.h>
#include <vgFont/vgfFontManager.h>

using namespace vgFont;

void FontManager_reset()
{
	return FontManager::getSingleton().reset();
}

void FontManager_initialiseFonts(HDC hDC)
{
	return FontManager::getSingleton().initialiseFonts(hDC);
}

void FontManager_uninitBeforeOpenGLDestroy()
{
	return FontManager::getSingleton().uninitBeforeOpenGLDestroy();
}

float FontManager_getOriginX()
{
	return FontManager::getSingleton().getOriginX();
}

void FontManager_setOriginX(float x)
{
	return FontManager::getSingleton().setOriginX(x);
}

float FontManager_getOriginY()
{
	return FontManager::getSingleton().getOriginY();
}

void FontManager_setOriginY(float y)
{
	return FontManager::getSingleton().setOriginY(y);
}

float FontManager_getFontSize()
{
	return FontManager::getSingleton().getFontSize();
}

void FontManager_setFontSize(float fontSize)
{
	return FontManager::getSingleton().setFontSize(fontSize);
}

void FontManager_setDefaultDisplay( String& str )
{
	return FontManager::getSingleton().setDefaultDisplay(str);
}

void FontManager_rebuildFontSize(int fontSize)
{
	return FontManager::getSingleton().rebuildFontSize(fontSize);
}

void FontManager_drawNumber(float h)
{
	return FontManager::getSingleton().drawNumber(h);
}

void FontManager_drawString(const std::string& str)
{
	return FontManager::getSingleton().drawString(str);
}

vgKernel::StringVector* FontManager_splitToMultiLine(const std::string &str)
{
	return FontManager::getSingleton().splitToMultiLine(str);
}



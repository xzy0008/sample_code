
#include <vgStableHeaders.h>
#include <vgChannel/vgcChannelManager.h>

using namespace vgChannel;

bool renderBegin()
{
	return vgChannel::ChannelManager::getSingleton().renderBegin();
}

bool clientRenderBegin()
{
	return vgChannel::ChannelManager::getSingleton().clientRenderBegin();
}

bool serverRenderBegin()
{
	return vgChannel::ChannelManager::getSingleton().serverRenderBegin();
}

bool renderEnd()
{
	return vgChannel::ChannelManager::getSingleton().renderEnd();
}

void blendAndAdjust()
{
	return vgChannel::ChannelManager::getSingleton().blendAndAdjust();
}

void setScreenSize(int x, int y)
{
	//return vgChannel::ChannelManager::setScreenSize(x,y);
}

//void FontManager_setOriginY(float y)
//{
	//return FontManager::getSingleton().setOriginY(y);
//}

// float FontManager_getFontSize()
// {
// 	//return FontManager::getSingleton().getFontSize();
// }

//void FontManager_setFontSize(float fontSize)
//{
	//return FontManager::getSingleton().setFontSize(fontSize);
//}

//void FontManager_rebuildFontSize(int fontSize)
//{
	//return FontManager::getSingleton().rebuildFontSize(fontSize);
//}

//void FontManager_drawNumber(float h)
//{
	//return FontManager::getSingleton().drawNumber(h);
//}

//void FontManager_drawString(const std::string& str)
//{
	//return FontManager::getSingleton().drawString(str);
//}

// vgKernel::StringVector* FontManager_splitToMultiLine(const std::string &str)
// {
// 	//return FontManager::getSingleton().splitToMultiLine(str);
// }



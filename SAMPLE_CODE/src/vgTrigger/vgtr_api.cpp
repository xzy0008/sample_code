
#include <vgStableHeaders.h>
#include <vgTrigger/vgtrTriggerManager.h>

using namespace vgTrigger;
 
bool TriggerManager_readFromVgFile(string savePath)
{
	return vgTrigger::TriggerManager::getSingleton().readFromVgFile(savePath);
}

bool TriggerManager_writeToVgFile(string savePath)
{
	return vgTrigger::TriggerManager::getSingleton().writeToVgFile(savePath);
}


bool serverRenderBegin()
{
	//return vgTrigger::TriggerManager::getSingleton().serverRenderBegin();
	return true;
}

bool renderEnd()
{
	//return vgTrigger::TriggerManager::getSingleton().renderEnd();
	return true;
}

void blendAndAdjust()
{
	//return vgTrigger::TriggerManager::getSingleton().blendAndAdjust();
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



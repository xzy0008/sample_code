


#include <vgStableHeaders.h>
#include <vgChannel/vgcChannelManager.h>


using namespace vgChannel;

//-----------------------------------------------
bool ChannelManager_startChannel( 
	int channelNum )
{

	return ChannelManager::getSingleton().startChannel( channelNum );

}
//-----------------------------------------------
void ChannelManager_SetChannelFromFile()
{
	return ChannelManager::getSingleton().SetChannelFromFile();
}
//-----------------------------------------------
void ChannelManager_setBlendAndAdjustEnable( bool b_able )
{
	return ChannelManager::getSingleton().setBlendAndAdjustEnable( b_able );
}
//-----------------------------------------------
void ChannelManager_setEdgeBlendEnable( bool b_able )
{
	return ChannelManager::getSingleton().setEdgeBlendEnable( b_able );
}
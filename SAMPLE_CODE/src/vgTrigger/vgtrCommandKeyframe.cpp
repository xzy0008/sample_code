
#include <vgStableHeaders.h>

#include <vgTrigger/vgtrCommandKeyframe.h>

#include "vgMovingManager.h"


namespace vgTrigger
{
	//-------------------------------------------------------------------
	CommandKeyframe::CommandKeyframe(String str, void *param) 
		: CommandAbstract(str)
	{
		String *pString = (string*)param;

		_pKeyFrameNode = 
			vgCore::MovingManager::getSingleton().getKeyFrameByName( *pString );

	}    

	
	//-------------------------------------------------------------------
	void CommandKeyframe::doCommand(TriggerEventEnum eventId /* = TRIGGER_NONE */)
	{

		if ( !_pKeyFrameNode ) 
		{
			return;
		}

		switch (eventId)
		{
		case TRIGGER_EVENT_ENTRENCE:
			_pKeyFrameNode->setPlayState(true);
			break;

		case TRIGGER_EVENT_EXIT:
			_pKeyFrameNode->setPlayState(false);
			break;

		case TRIGGER_EVENT_CLICK:

			break;

		default:
			break;
		}

		return ;
	}
}
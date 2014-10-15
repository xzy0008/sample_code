
#include <vgStableHeaders.h>

#include <vgTrigger/vgtrCommandSound.h>

#include "vgSound/vgSoundManager.h"


namespace vgTrigger
{
	//-------------------------------------------------------------------
	CommandSound::CommandSound(String str, void *param) 
		: CommandAbstract(str)
	{
		String *pString = (string*)param;

		_pSoundNode = 
			vgSound::SoundManager::getSingleton().getSound3DPtr( *pString );
	}    

	
	//-------------------------------------------------------------------
	void CommandSound::doCommand(TriggerEventEnum eventId /* = TRIGGER_NONE */)
	{

		if ( !_pSoundNode ) 
		{
			return;
		}

		switch (eventId)
		{
		case TRIGGER_EVENT_ENTRENCE:
			_pSoundNode->setPlayState(true);
			_pSoundNode->startPlaying( true );
			break;

		case TRIGGER_EVENT_EXIT:
			_pSoundNode->setPlayState(false);
			_pSoundNode->stopPlaying();
			break;

		case TRIGGER_EVENT_CLICK:

			break;

		default:
			break;
		}

		return ;
	}
}
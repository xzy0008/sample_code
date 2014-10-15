
#ifndef _COMMANDSOUND_H_INCLUDED_
#define _COMMANDSOUND_H_INCLUDED_

#include <vgTrigger/vgtrCommandAbstract.h>
#include <vgTrigger/vgtrDefinition.h>

#include <vgSound/vgSound3D.h>


namespace vgTrigger
{

	class VGTRI_EXPORT CommandSound : public CommandAbstract
	{
	public:
		CommandSound(String str, void *param);
		CommandSound() {} 

	public:
		virtual void doCommand(TriggerEventEnum eventId = TRIGGER_NONE);

		virtual CommandID getType() 
		{ 
			return TRIGGER_COMMAND_SOUND3D; 
		}

		vgSound::Sound3D*	getNode()
		{
			return _pSoundNode;
		}


	protected:
		vgSound::Sound3D*	_pSoundNode;		

	};//class

}//namespace

#endif//_COMMANDSOUND_H_INCLUDED_
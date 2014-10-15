
#include <vgStableHeaders.h>

#include <vgTrigger/vgtrCommandFactory.h>
#include <vgTrigger/vgtrCommandMsg.h>

#include "vgTrigger/vgtrCommandAvi.h"
// #include "vgTrigger/vgtrCommandKeyframe.h"
// #include "vgTrigger/vgtrCommandSound.h"
// #include "vgTrigger/vgtrCommandText2D.h"
#include <vgTrigger/vgtrCommandScript.h>

namespace vgTrigger
{

	//-------------------------------------------------------------------
	CommandFactory::CommandFactory()
	{

	}


	
	//-------------------------------------------------------------------
	CommandFactory::~CommandFactory()
	{

	}


	//-------------------------------------------------------------------
	CommandPtr CommandFactory::generateCommand( CommandID id,
		string name, void* param)
	{
		CommandAbstract* pCommand = NULL;

		switch (id)
		{
		case TRIGGER_COMMAND_MSG:
			pCommand = new CommandMsg(name, param);
			break;

		case TRIGGER_COMMAND_TEXT2D:
			//pCommand = new CommandText2D(name, param);
			break;

		case TRIGGER_COMMAND_SOUND3D:
			//pCommand = new CommandSound(name, param);
			break;

		case TRIGGER_COMMAND_KEYFRAME:
			//pCommand = new CommandKeyframe(name, param);
			break;

		case TRIGGER_COMMAND_AVI:
			pCommand = new CommandAvi(name, param);
			break;

		case TRIGGER_COMMAND_SCRIPT:
			pCommand = new CommandScript(name, param);
			break;
		}

		assert(pCommand != NULL);
		
		CommandPtr ptr(pCommand);
		return ptr;
	}
	//-------------------------------------------------------------------
}//namespace

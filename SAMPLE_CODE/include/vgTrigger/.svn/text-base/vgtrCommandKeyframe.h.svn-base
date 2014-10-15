
#ifndef _COMMANDKEYFRAME_H_INCLUDED_
#define _COMMANDKEYFRAME_H_INCLUDED_

#include <vgTrigger/vgtrCommandAbstract.h>
#include <vgTrigger/vgtrDefinition.h>

#include <vgMod/vgObjframeNode.h>


namespace vgTrigger
{

	class VGTRI_EXPORT CommandKeyframe : public CommandAbstract
	{
	public:
		CommandKeyframe(String str, void *param);
		CommandKeyframe() {}

	public:
		virtual void doCommand(TriggerEventEnum eventId = TRIGGER_NONE);

		virtual CommandID getType() 
		{ 
			return TRIGGER_COMMAND_SOUND3D; 
		}

		vgMod::ObjFrameNode*	getNode()
		{
			return _pKeyFrameNode;
		}

	protected:
		vgMod::ObjFrameNode*	_pKeyFrameNode;

	};//class

}//namespace

#endif//_COMMANDKEYFRAME_H_INCLUDED_
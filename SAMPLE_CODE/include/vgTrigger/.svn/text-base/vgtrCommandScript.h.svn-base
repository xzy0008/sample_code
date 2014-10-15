#pragma once

#include <vgTrigger/vgtrCommandAbstract.h>
#include <vgTrigger/vgtrDefinition.h>

namespace vgTrigger
{
	class VGTRI_EXPORT CommandScript : public CommandAbstract
	{
	public:
		CommandScript(String str, void *param);

		CommandScript() {}

	public:
		virtual void doCommand(TriggerEventEnum eventId = TRIGGER_NONE);

		virtual CommandID getType() 
		{ 
			return TRIGGER_COMMAND_SCRIPT; 
		}
	
		virtual string getContectInfo(TriggerEventEnum eventId);
		
		virtual bool saveToFile(FILE *fp);

		virtual bool readFromFile(FILE *fp);

	protected:
		String	_strText;

		String m_entranceScript;
		String m_exitScript;
		String m_clickScript;

		String m_serchPath;

	};
}
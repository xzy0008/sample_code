#pragma once

#include <vgTrigger/vgtrCommandAbstract.h>
#include <vgTrigger/vgtrDefinition.h>

namespace vgTrigger
{
	class VGTRI_EXPORT CommandMsg : public CommandAbstract
	{
	public:
		CommandMsg(string str, void *param);
		CommandMsg() {}

		virtual void doCommand(TriggerEventEnum eventId = TRIGGER_NONE);
		
		virtual CommandID getType() { return TRIGGER_COMMAND_MSG; }
		
		virtual string getContectInfo(TriggerEventEnum eventId);
		
		virtual bool readFromFile(FILE *fp);
		
		virtual bool saveToFile(FILE *fp);

	private:

		string m_entrenceMsg;
		string m_exitMsg;
		string m_clickMsg;
	};
}
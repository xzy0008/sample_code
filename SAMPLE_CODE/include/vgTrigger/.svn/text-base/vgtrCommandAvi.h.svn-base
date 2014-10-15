
#ifndef _COMMANDAVI_H_INCLUDED_
#define _COMMANDAVI_H_INCLUDED_

#include <vgTrigger/vgtrCommandAbstract.h>



namespace vgTrigger
{

	class VGTRI_EXPORT CommandAvi : public CommandAbstract
	{
	public:
		CommandAvi(String str, void *param);
		CommandAvi() {}

	public:	
		virtual void doCommand(TriggerEventEnum eventId = TRIGGER_NONE);

		virtual CommandID getType() 
		{ 
			return TRIGGER_COMMAND_AVI; 
		}

		virtual string getContectInfo(TriggerEventEnum eventId);

		virtual bool saveToFile(FILE *fp);

		virtual bool readFromFile(FILE *fp);

	protected:
		String m_entranceScript;
		String m_exitScript;
		String m_clickScript;
	};//class

}//namespace

#endif//_COMMANDAVI_H_INCLUDED_
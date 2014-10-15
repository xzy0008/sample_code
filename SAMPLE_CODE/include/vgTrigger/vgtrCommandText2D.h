
#ifndef _COMMANDTEXT2D_H_INCLUDED_
#define _COMMANDTEXT2D_H_INCLUDED_

#include <vgTrigger/vgtrCommandAbstract.h>
#include <vgTrigger/vgtrDefinition.h>

#include <vgMod/vgObjframeNode.h>


namespace vgTrigger
{

	class VGTRI_EXPORT CommandText2D : public CommandAbstract
	{
	public:
		CommandText2D(String str, void *param);
		CommandText2D() {}

	public:
		virtual void doCommand(TriggerEventEnum eventId = TRIGGER_NONE);
		
		virtual CommandID getType() 
		{ 
			return TRIGGER_COMMAND_TEXT2D; 
		}
		
		virtual string getContectInfo(TriggerEventEnum eventId);

		virtual void setText(string str) { _strText = str; }
		
		virtual bool saveToFile(FILE *fp);

		virtual bool readFromFile(FILE *fp);

	protected:
		String	_strText;

	};

}//namespace

#endif//_COMMANDTEXT2D_H_INCLUDED_
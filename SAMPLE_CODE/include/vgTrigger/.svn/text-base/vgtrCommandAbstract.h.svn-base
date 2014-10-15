
#ifndef _COMMANDABSTRACT_H_INCLUDED_
#define _COMMANDABSTRACT_H_INCLUDED_

#include <vgTrigger/vgtrDefinition.h>

namespace vgTrigger
{
	enum TriggerEventEnum
	{
		TRIGGER_NONE,
		TRIGGER_EVENT_ENTRENCE,
		TRIGGER_EVENT_EXIT,
		TRIGGER_EVENT_CLICK,

		TRIGGER_EVENT_TOTAL_NUM
	};

	enum CommandID
	{
		TRIGGER_COMMADN_NONE,
		TRIGGER_COMMAND_MSG,
		TRIGGER_COMMAND_TEXT2D,
		TRIGGER_COMMAND_SOUND3D,
		TRIGGER_COMMAND_KEYFRAME,
		TRIGGER_COMMAND_AVI,
		TRIGGER_COMMAND_SCRIPT,

		TRIGGER_COMMAND_TOTAL_NUM
	};

	class VGTRI_EXPORT CommandAbstract
	{
	public:
		CommandAbstract(string str, void* param = NULL)
		{ 
			_strName = str; 
		}

		CommandAbstract() 
		{
			_strName = "NoName";
		}

		// ÐéÎö¹¹º¯Êý
		virtual ~CommandAbstract(){}

	public:
		virtual void doCommand(TriggerEventEnum eventId = TRIGGER_NONE) = 0;

		virtual CommandID getType() { return TRIGGER_COMMADN_NONE; }

		virtual string& getName()
		{
			return _strName;
		}

		virtual void setName(string& str)
		{
			_strName = str;
		}

		virtual string getContectInfo(TriggerEventEnum eventId) 
		{
			return "";
		}

		virtual bool saveToFile(FILE *fp)
		{
			int nameLen = _strName.length();

			fwrite(&nameLen, sizeof(nameLen), 1, fp);
			fwrite(_strName.c_str(), nameLen, 1, fp);

			return true;
		}

		virtual bool readFromFile(FILE *fp)
		{
			int nameLen;
			char buffer[256] = {'\0'};

			fread(&nameLen, sizeof(nameLen), 1, fp);
			fread(buffer, nameLen, 1, fp);

			_strName = buffer;

			return true;
		}

	protected:
		string _strName;

	};//class

	typedef vgKernel::SharePtr<CommandAbstract>		CommandPtr;

	typedef	std::vector< CommandPtr >					CommandPtrArray;
	
	typedef vgKernel::SharePtr<CommandPtrArray>		CommandPtrArrayPtr;

	typedef	std::vector< CommandPtr >::iterator			CommandPtrArrayItr;

}//namespace

#endif//_COMMANDABSTRACT_H_INCLUDED_
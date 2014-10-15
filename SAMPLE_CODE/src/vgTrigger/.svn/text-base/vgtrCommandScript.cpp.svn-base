#include <vgStableHeaders.h>

#include <vgKernel/vgkStringUtility.h>

#include <vgTrigger/vgtrTrigger.h>
#include <vgTrigger/vgtrCommandScript.h>

#include <vgScript/vgscScriptFacade.h>


namespace vgTrigger
{

	CommandScript::CommandScript(String str, void *param) 
		: CommandAbstract(str)
	{
		string *pString = (string*)param;

		if (pString != NULL)
		{
			m_entranceScript = pString[0];
			m_exitScript = pString[1];
			m_clickScript = pString[2];

			vgKernel::StringUtility::replace( m_entranceScript , "\r" , "" );
			vgKernel::StringUtility::replace( m_exitScript , "\r" , "" );
			vgKernel::StringUtility::replace( m_clickScript , "\r" , "" );
		}

	}    


	//-------------------------------------------------------------------
	void CommandScript::doCommand(TriggerEventEnum eventId /* = TRIGGER_NONE */)
	{

		switch (eventId)
		{
		case TRIGGER_EVENT_ENTRENCE:
			 //vgFont::FontManager::getSingleton().setDefaultDisplay(_strText);
			
			if (m_entranceScript.length() > 1)
			{
				vgScript::ScriptFacade::RunScriptSimpleString(m_entranceScript);
			}

			break;

		case TRIGGER_EVENT_EXIT:

			if (m_exitScript.length() > 1)
			{
				vgScript::ScriptFacade::RunScriptSimpleString(m_exitScript);
			}

			break;

		case TRIGGER_EVENT_CLICK:
			
			if (m_clickScript.length() > 1)
			{
				vgScript::ScriptFacade::RunScriptSimpleString(m_clickScript);
			}

			break;

		default:
			break;
		}

		return ;
	}

	string CommandScript::getContectInfo(TriggerEventEnum eventId)
	{
		string returnString;

		switch (eventId)
		{
		case TRIGGER_EVENT_ENTRENCE:
			returnString = m_entranceScript;
			vgKernel::StringUtility::replace(returnString, "\n", "\r\n");

			break;
		case TRIGGER_EVENT_EXIT:
			returnString = m_exitScript;
			vgKernel::StringUtility::replace(returnString, "\n", "\r\n");

			break;
		case TRIGGER_EVENT_CLICK:
			returnString = m_clickScript;
			vgKernel::StringUtility::replace(returnString, "\n", "\r\n");

			break;
		}

		return returnString;
	}

	bool CommandScript::saveToFile(FILE *fp)
	{
		CommandAbstract::saveToFile(fp);
		
		int writeLen = m_entranceScript.length();

		fwrite(&writeLen, sizeof(writeLen), 1, fp);
		fwrite(m_entranceScript.c_str(), writeLen, 1, fp);

		writeLen = m_exitScript.length();
		fwrite(&writeLen, sizeof(writeLen), 1, fp);
		fwrite(m_exitScript.c_str(), writeLen, 1, fp);
	
		writeLen = m_clickScript.length();
		fwrite(&writeLen, sizeof(writeLen), 1, fp);
		fwrite(m_clickScript.c_str(), writeLen, 1, fp);
	
		return true;
	}

	bool CommandScript::readFromFile(FILE *fp)
	{
		CommandAbstract::readFromFile(fp);

		int writeLen;
		char buffer[256];

		fread(&writeLen, sizeof(writeLen), 1, fp);
		assert(writeLen <= 256);

		fread(buffer, writeLen, 1, fp);
		buffer[writeLen] = '\0';
		m_entranceScript = buffer;

		fread(&writeLen, sizeof(writeLen), 1, fp);
		assert(writeLen <= 256);

		fread(buffer, writeLen, 1, fp);
		buffer[writeLen] = '\0';
		m_exitScript = buffer;

		fread(&writeLen, sizeof(writeLen), 1, fp);
		assert(writeLen <= 256);

		fread(buffer, writeLen, 1, fp);
		buffer[writeLen] = '\0';
		m_clickScript = buffer;

		return true;
	}
}
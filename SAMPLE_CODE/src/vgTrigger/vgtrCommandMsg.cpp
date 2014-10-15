#include <vgStableHeaders.h>
#include <vgTrigger/vgtrCommandMsg.h>
#include <vgKernel/vgkStringUtility.h>

namespace vgTrigger
{
	CommandMsg::CommandMsg(string str, void *param) : CommandAbstract(str)
	{
		string *pString = (string*)param;

		if (pString != NULL)
		{
			// split by ;
// 			vgKernel::StringVector re 
// 				= vgKernel::StringUtility::tokenize(*pString, ";");
// 			
// 			if (re.size() < 3)
// 			{
// 				return ;
// 			}

			m_entrenceMsg = pString[0];
			m_exitMsg = pString[1];
			m_clickMsg = pString[2];
		}
	}    

	void CommandMsg::doCommand(TriggerEventEnum eventId /* = TRIGGER_NONE */)
	{
		switch (eventId)
		{
		case TRIGGER_EVENT_ENTRENCE:
			if (m_entrenceMsg.length() != 0)
			{
				::MessageBox(NULL, m_entrenceMsg.c_str(), this->_strName.c_str(), MB_OK);
			}
			break;
		case TRIGGER_EVENT_EXIT:
			if (m_exitMsg.length() != 0)
			{
				::MessageBox(NULL, m_exitMsg.c_str(), this->_strName.c_str(), MB_OK);
			}
			break;
		case TRIGGER_EVENT_CLICK:
			if (m_clickMsg.length() != 0)
			{
				::MessageBox(NULL, m_clickMsg.c_str(), this->_strName.c_str(), MB_OK);
				break;
			}
		}

		return ;
	}

	string CommandMsg::getContectInfo(TriggerEventEnum eventId)
	{
		switch (eventId)
		{
		case TRIGGER_EVENT_ENTRENCE:
			return m_entrenceMsg;

			break;
		case TRIGGER_EVENT_EXIT:
			return m_exitMsg;

			break;
		case TRIGGER_EVENT_CLICK:
			return m_clickMsg;

			break;
		}

		return "";
	}

	bool CommandMsg::saveToFile(FILE *fp)
	{
		CommandAbstract::saveToFile(fp);

		int writeLen = m_entrenceMsg.length();

		fwrite(&writeLen, sizeof(writeLen), 1, fp);
		fwrite(m_entrenceMsg.c_str(), writeLen, 1, fp);

		writeLen = m_exitMsg.length();
		fwrite(&writeLen, sizeof(writeLen), 1, fp);
		fwrite(m_exitMsg.c_str(), writeLen, 1, fp);

		writeLen = m_clickMsg.length();
		fwrite(&writeLen, sizeof(writeLen), 1, fp);
		fwrite(m_clickMsg.c_str(), writeLen, 1, fp);


		return true;
	}

	bool CommandMsg::readFromFile(FILE *fp)
	{
		CommandAbstract::readFromFile(fp);
		
		int writeLen;
		char buffer[256];

		fread(&writeLen, sizeof(writeLen), 1, fp);
		assert(writeLen <= 256);

		fread(buffer, writeLen, 1, fp);
		buffer[writeLen] = '\0';
		m_entrenceMsg = buffer;

		fread(&writeLen, sizeof(writeLen), 1, fp);
		assert(writeLen <= 256);

		fread(buffer, writeLen, 1, fp);
		buffer[writeLen] = '\0';
		m_exitMsg = buffer;

		fread(&writeLen, sizeof(writeLen), 1, fp);
		assert(writeLen <= 256);

		fread(buffer, writeLen, 1, fp);
		buffer[writeLen] = '\0';
		m_clickMsg = buffer;

		return true;
	}
}

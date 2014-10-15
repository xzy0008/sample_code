
#include <vgStableHeaders.h>

#include <vgTrigger/vgtrCommandText2D.h>
#include <vgKernel/vgkPluginManager.h>

#include "vgKernel/vgkRendererManager.h"
//#include <vgFont/vgFont.h>

namespace vgTrigger
{
	//-------------------------------------------------------------------
	CommandText2D::CommandText2D(String str, void *param) 
		: CommandAbstract(str)
	{
		String *pString = (string*)param;

		_strText = *pString;

	}    


	
	//-------------------------------------------------------------------
	void CommandText2D::doCommand(TriggerEventEnum eventId /* = TRIGGER_NONE */)
	{

		if ( _strText.empty() ) 
		{
			return;
		}

		switch (eventId)
		{
		case TRIGGER_EVENT_ENTRENCE:
			//vgFont::FontManager::getSingleton().setDefaultDisplay(_strText);
			VGK_DLL_RUN_CLASSFUNC(VGF_DLL_NAME, FontManager, setDefaultDisplay)(_strText);
			break;

		case TRIGGER_EVENT_EXIT:
			//vgFont::FontManager::getSingleton().setDefaultDisplay(String());
			VGK_DLL_RUN_CLASSFUNC(VGF_DLL_NAME, FontManager, setDefaultDisplay)(String());
			break;

		case TRIGGER_EVENT_CLICK:

			break;

		default:
			break;
		}

		return ;
	}

	string CommandText2D::getContectInfo(TriggerEventEnum eventId)
	{
		string returnString;

		switch (eventId)
		{
		case TRIGGER_EVENT_ENTRENCE:
			return _strText;

			break;
		case TRIGGER_EVENT_EXIT:

			break;

		case TRIGGER_EVENT_CLICK:

			break;
		}

		return returnString;
	}

	bool CommandText2D::saveToFile(FILE *fp)
	{
		CommandAbstract::saveToFile(fp);

		int textLen = _strText.length();

		fwrite(&textLen, sizeof(textLen), 1, fp);

		fwrite(_strText.c_str(), textLen, 1, fp);

		return true;
	}

	bool CommandText2D::readFromFile(FILE *fp)
	{
		CommandAbstract::readFromFile(fp);
		
		int textLen;
		char buffer[256];

		fread(&textLen, sizeof(textLen), 1, fp);
		assert(textLen < 256);

		fread(buffer, textLen, 1, fp);
		buffer[textLen] = '\0';

		_strText = buffer;

		return true;
	}
}
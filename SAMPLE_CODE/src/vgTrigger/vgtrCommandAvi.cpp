
#include <vgStableHeaders.h>

#include <vgTrigger/vgtrCommandAvi.h>

#include <vgKernel/vgkRendererManager.h>
#include <vgKernel/vgkStringUtility.h>

#include "vgEffect/vgAviNode.h"

namespace vgTrigger
{
	//-------------------------------------------------------------------
	CommandAvi::CommandAvi(String str, void *param) 
		: CommandAbstract(str)
	{
		String *pString = (string*)param;

		if (pString != NULL)
		{
			m_entranceScript = pString[0];
			m_exitScript = pString[1];
			m_clickScript = pString[2];

			vgKernel::StringUtility::replace( m_entranceScript , "\r" , "" );
			vgKernel::StringUtility::replace( m_exitScript , "\r" , "" );
			vgKernel::StringUtility::replace( m_clickScript , "\r" , "" );
		}

#if 0
		vgKernel::Renderer*	pRender = vgKernel::RendererManager::
			getSingleton().getRendererbyName( *pString );

		_pAviNode = dynamic_cast<vgMod::AviNode*>( pRender );
#endif
	}    

	
	//-------------------------------------------------------------------
	void CommandAvi::doCommand(TriggerEventEnum eventId /* = TRIGGER_NONE */)
	{
		vgKernel::Renderer*	pRender = vgKernel::RendererManager::
			getSingleton().getRendererbyName( m_clickScript, true );

		vgMod::AviNode  *_pAviNode = dynamic_cast<vgMod::AviNode*>( pRender );

		if ( !_pAviNode ) 
		{
			return;
		}

		switch (eventId)
		{
		case TRIGGER_EVENT_ENTRENCE:
			_pAviNode->setPlayState(true);
			break;

		case TRIGGER_EVENT_EXIT:
			_pAviNode->setPlayState(false);
			break;

		case TRIGGER_EVENT_CLICK:

			break;

		default:
			break;
		}

		return ;
	}

	string CommandAvi::getContectInfo( TriggerEventEnum eventId )
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


	bool CommandAvi::saveToFile(FILE *fp)
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

	bool CommandAvi::readFromFile(FILE *fp)
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
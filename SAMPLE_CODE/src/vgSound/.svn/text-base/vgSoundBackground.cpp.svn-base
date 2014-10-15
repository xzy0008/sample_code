



#include <vgStableHeaders.h>
#include "vgSound/vgSoundBackground.h"
#include "vgSound/vgSoundManager.h"


namespace vgSound {


#define  FILENAME_LENGTH  255

	VGK_RENDERER_IMPLEMENT( SoundBackground ,RENDERER_TYPE_SOUNDBACK)

	SoundBackground::SoundBackground()
		:_uniqueID( vgKernel::UniqueIDFactory::getUniqueID())
		//:vgKernel::ObserverHandler()
	{
		filepath = "";

		b_play = true;

	}
	//----------------------------------------------------------------
	void SoundBackground::reset()
	{
		if (filepath != "")
		{
			m_name = filepath.substr( filepath.find_last_of("\\/")+1, String::npos );
		}
		else
		{
			return;
		}

		//String sndNodeName = filepath.substr( filepath.find_last_of("\\/")+1 , String::npos);
			//filepath.find_last_of(".") - filepath.find_last_of("\\/") - 1 );
		//setName( sndNodeName );

		if (!b_play)
		{
			stopPlaying();
		}
		else
		{
			startPlaying();
		}

		this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);
	}

	void SoundBackground::stopPlaying()
	{
		if (filepath.empty())
		{
			return;
		}

		mciSendCommand(wDeviceID, MCI_CLOSE, MCI_DGV_PLAY_REPEAT, (DWORD)&playParam);

		setPlayFlag(false);

	}

	void SoundBackground::startPlaying()
	{
		if (filepath.empty())
		{
			return;
		}

		mciOpen.lpstrElementName =(LPSTR)(LPCSTR)(filepath.c_str());//(char *)filename;
		MCIERROR   retu=   mciSendCommand(0,   MCI_OPEN,   
			MCI_OPEN_ELEMENT/*|MCI_OPEN_TYPE|MCI_OPEN_TYPE_ID|MCI_DGV_OPEN_PARENT|MCI_DGV_OPEN_WS*/,   
			(DWORD)(LPMCI_DGV_OPEN_PARMS)&mciOpen);   

		wDeviceID =mciOpen.wDeviceID;   

		mciSendCommand(wDeviceID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)&playParam);

		setPlayFlag(true);

	}

	void SoundBackground::writeToFile( CFile *file )
	{

		file->Write( &b_play , sizeof(bool) );

		file->Write( m_name.c_str(), 200 );

		//file->Write( m_nodeName.c_str(), 200 );
	}

	void SoundBackground::readFromFile( CFile *file )
	{
		file->Read( &b_play , sizeof(bool) );

		char aa[200];

		file->Read( aa, 200 );
		m_name = String(aa);

		//file->Read( aa, 200 );
		//m_nodeName = String(aa);

		this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);
	}

	void SoundBackground::writeToFile(vgKernel::StreamWriterPtr	file )
	{

		file->write( &b_play , sizeof(bool) );

		file->write( (void*)m_name.c_str(), 200 );

		//file->Write( m_nodeName.c_str(), 200 );
	}

	void SoundBackground::readFromFile( vgKernel::StreamReaderPtr	file )
	{
		file->read( &b_play , sizeof(bool) );

		char aa[200];

		file->read( aa, 200 );
		m_name = String(aa);

		//file->Read( aa, 200 );
		//m_nodeName = String(aa);

		this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);
	}
}
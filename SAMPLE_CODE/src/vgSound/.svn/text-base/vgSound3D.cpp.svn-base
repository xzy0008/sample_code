


#include <vgStableHeaders.h>
#include "vgSound/vgSound3D.h"


#include "vgSound/vgSoundManager.h"
#include <vgKernel/vgkSystemUtility.h>

namespace vgSound {


	VGK_RENDERER_IMPLEMENT( Sound3D , RENDERER_TYPE_SOUND )

		Sound3D::Sound3D():_uniqueID( vgKernel::UniqueIDFactory::getUniqueID())
	{
		m_pDirectSoundBuf= NULL;

		pDirectSound3DBuf8 = NULL;

		m_shuaijian = 0.001;

		b_play = true;

		m_wavepath= "";

		m_name = "";

		//		_uniqueID =vgKernel::UniqueIDFactory::getUniqueID();
	}

	Sound3D::~Sound3D()
	{
		if(m_pDirectSoundBuf!=NULL)
		{
			m_pDirectSoundBuf->Release();
			m_pDirectSoundBuf=NULL;
		}

		if( pDirectSound3DBuf8 != NULL)//chunyongma2008.9.8
		{
			pDirectSound3DBuf8->Release();
			pDirectSound3DBuf8 = NULL;
		}
	}

	bool Sound3D::setSoundPos(float x,float y,float z)
	{
		if (FAILED(pDirectSound3DBuf8->SetPosition(x,y,z,DS3D_IMMEDIATE)))
			return FALSE;

		return TRUE;
	}

	bool Sound3D::setAbsolutePos( float x, float y, float z )
	{
		m_AbsolutePosition.x = x;

		m_AbsolutePosition.y = y;

		m_AbsolutePosition.z = z;

		GenBoundaryBox( m_AbsolutePosition );

		return true;

	}

	bool Sound3D::loadWaveFile(String szWaveFile)
	{
		if ( !vgKernel::SystemUtility::checkFileExist( szWaveFile) )
		{
			String errorMsg(szWaveFile);
			errorMsg += "不存在或文件名无效！";
			vgKernel::SystemUtility::showModelDialog( errorMsg );
			return false;
		}

		FILE *fp;
		if((fp = fopen(szWaveFile.c_str(),"rb")) == NULL)
		{  
			MessageBox(NULL,"0","0",MB_OK);
			return FALSE;
		}
		if(!GetSecondaryBuffer(fp))
		{
			MessageBox(NULL,"创建SecondaryBuffer出错","DirectSound Error",MB_OK);//有错误
			fclose(fp);
			return FALSE;

		}
		if(!LoadDataInBuffer(fp))
		{
			MessageBox(NULL,"载入buffer出错","DirectSound Error",MB_OK);
			fclose(fp);
			return FALSE;
		}
		fclose(fp);
		return true;
	}

	bool Sound3D::GetSecondaryBuffer(FILE* fp)
	{
		sWaveHeader *pWaveHeader = new sWaveHeader();
		fseek(fp,0,SEEK_SET);
		fread(pWaveHeader,sizeof(sWaveHeader),1,fp);

		if(memcmp(pWaveHeader->RiffID,"RIFF",4)||
			memcmp(pWaveHeader->WaveID,"WAVE",4)||
			memcmp(pWaveHeader->FormatID,"fmt ",4)||
			memcmp(pWaveHeader->DataID,"data",4))
		{
			MessageBox(NULL,"非wav格式","DirectSound Error",MB_OK);
			return FALSE;
		}


		WAVEFORMATEX waveFormat;
		ZeroMemory(&waveFormat,sizeof(WAVEFORMATEX));
		waveFormat.wFormatTag = WAVE_FORMAT_PCM;
		waveFormat.nChannels = pWaveHeader->Channels;
		waveFormat.nSamplesPerSec = pWaveHeader->SampleRate;
		waveFormat.wBitsPerSample = pWaveHeader->BitsPerSample;
		waveFormat.nBlockAlign = (waveFormat.wBitsPerSample/8)*waveFormat.nChannels;
		waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec*waveFormat.nBlockAlign;

		DSBUFFERDESC bufferDesc;
		ZeroMemory(&bufferDesc,sizeof(DSBUFFERDESC));
		bufferDesc.dwSize = sizeof(DSBUFFERDESC);
		bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME|DSBCAPS_GLOBALFOCUS|DSBCAPS_STATIC|DSBCAPS_CTRL3D;
		bufferDesc.dwBufferBytes =pWaveHeader->DataSize;
		bufferDesc.lpwfxFormat =&waveFormat;

		IDirectSound *pDirectSound;

		pDirectSound = SoundManager::getSingleton().GetDirectSound();

		if(FAILED(pDirectSound->CreateSoundBuffer(&bufferDesc,&m_pDirectSoundBuf,NULL)))
		{
			MessageBox(NULL,"创建SoundBuffe出错","DirectSound Error",MB_OK);
			return FALSE;
		}
		if(FAILED(m_pDirectSoundBuf->QueryInterface(IID_IDirectSound3DBuffer8,
			(void**)&pDirectSound3DBuf8)))
		{
			MessageBox(NULL,"创建IDirectSound3DBuffer出错","DirectSound Error",MB_OK);
			return FALSE;
		}
		delete pWaveHeader;
		return true;
	}

	bool Sound3D::LoadDataInBuffer(FILE *fp)
	{
		sWaveHeader *pWaveHeader = new sWaveHeader();
		fseek(fp,0,SEEK_SET);
		fread(pWaveHeader,1,sizeof(sWaveHeader),fp);

		BYTE *pSoundPtr1 = NULL;
		BYTE *pSoundPtr2 = NULL;

		DWORD dwSoundSize1,dwSoundSize2;

		if(FAILED(m_pDirectSoundBuf->Lock(0,pWaveHeader->DataSize,
			(void**)&pSoundPtr1,&dwSoundSize1,
			(void**)&pSoundPtr2,&dwSoundSize2,0)))
		{
			MessageBox(NULL,"读取wav头文件时出错","DirectSound error",MB_OK);
			return false;
		}

		fread(pSoundPtr1,1,dwSoundSize1,fp);

		if(pSoundPtr2!=NULL)
		{
			fread(pSoundPtr2,1,dwSoundSize2,fp);
		}


		m_pDirectSoundBuf->Unlock(pSoundPtr1,dwSoundSize1,pSoundPtr2,dwSoundSize2);

		delete pWaveHeader;

		return true;
	}

	bool Sound3D::startPlaying(bool bLoop)
	{
		if(m_pDirectSoundBuf==NULL)
			return false;
		m_pDirectSoundBuf->SetCurrentPosition(0);
		if(FAILED(m_pDirectSoundBuf->Play(0,0,bLoop?true:false)))
			return false;
		return true;
	}

	bool Sound3D::setVolume(long lVolume)
	{
		if(FAILED(m_pDirectSoundBuf->SetVolume(lVolume)))
			return false;
		return true;
	}

	bool Sound3D::stopPlaying()
	{
		if(FAILED(m_pDirectSoundBuf->Stop()))
			return false;
		return true;
	}

	bool Sound3D::setSoundPram(float fMinDistance,float fMaxDistance)
	{

		dsBufferParams.flMinDistance = fMinDistance;
		dsBufferParams.flMaxDistance = fMaxDistance;

		pDirectSound3DBuf8->GetAllParameters(&dsBufferParams);
		if( pDirectSound3DBuf8)
			pDirectSound3DBuf8->SetAllParameters( &dsBufferParams, DS3D_IMMEDIATE );
		return TRUE;

	}

	//void Sound3D::Render()
	//{
	//	//if (m_isVisible)
	//	{

	//		glDisable(GL_TEXTURE_2D);
	//		glPushMatrix();
	//		glTranslatef(m_AbsolutePosition.x, m_AbsolutePosition.y, m_AbsolutePosition.z);
	//		glTranslatef(0.0,0.0,-3.0);
	//		glColor3f(0.0,0.9,0.9);
	//		auxSolidCone(2,3);
	//		glTranslatef(0.0,0.0,5.0);
	//		auxSolidBox(4,4,4);
	//		glPopMatrix();
	//		glEnable(GL_TEXTURE_2D);
	//	}


	//}
	void Sound3D::GenBoundaryBox( vgKernel::Vec3 &pp)
	{
		_dynamicBox._maxVertex.x = pp.x + 10.0;
		_dynamicBox._maxVertex.y = pp.y + 10.0;
		_dynamicBox._maxVertex.z = pp.z + 10.0;

		_dynamicBox._minVertex.x = pp.x - 10.0;
		_dynamicBox._minVertex.y = pp.y - 10.0;
		_dynamicBox._minVertex.z = pp.z - 10.0;
	}

	void Sound3D::writeToFile( CFile *file )
	{
		file->Write( &b_play, sizeof(bool) );

		file->Write( m_name.c_str(), 200 );

		file->Write( &m_AbsolutePosition, sizeof(vgKernel::Vec3) );
	}

	void Sound3D::readFromFile(CFile *file)
	{
		file->Read( &b_play, sizeof(bool) );

		char aa[200];

		file->Read( aa, 200 );

		m_name = String(aa);

		file->Read( &m_AbsolutePosition, sizeof(vgKernel::Vec3) );

		this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);
	}

	void Sound3D::writeToFile(vgKernel::StreamWriterPtr pfile)
	{
		pfile->write( &b_play, sizeof(bool) );

		pfile->write( (void*)m_name.c_str(), 200 );

		pfile->write( &m_AbsolutePosition, sizeof(vgKernel::Vec3) );
	}

	void Sound3D::readFromFile(vgKernel::StreamReaderPtr pfile)
	{
		pfile->read( &b_play, sizeof(bool) );

		char aa[200];

		pfile->read( aa, 200 );

		m_name = String(aa);

		pfile->read( &m_AbsolutePosition, sizeof(vgKernel::Vec3) );

		this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);
	}
}
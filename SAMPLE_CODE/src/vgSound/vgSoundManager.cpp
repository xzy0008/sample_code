


#include <vgStableHeaders.h>
#include "vgsound/vgSoundManager.h"
#include <vgKernel/vgkSystemUtility.h>

#include <vgKernel/vgkCamMgrHolder.h>

#include <vgKernel/vgkStringUtility.h>

#include <vgKernel/vgkRendererManager.h>

#include <vgUIController/vgUIController.h>
#include <vgEntry/vgEntryFactory.h>

#include <vgUIController/vgWorkSpaceBar.h>
//#include <vgEntryFactory.h>
//#include <vgUIController.h>
#include <vgEntry/vgSound3DEntry.h>		// Add By FengYK @2010-03-19 14:49
#include <vgEntry/vgSoundBackgroundEntry.h>

namespace  vgSound {


	SoundManager::SoundManager()
		:Singleton<SoundManager>(VGK_SIGLETON_LEFE_SOUNDMANAGER)
	{
		_initialised = false;

		_hwnd = 0;
		//m_pSoundManager = this;
		m_pDirectSound = NULL;
		pListener=NULL;
		//	pDirectSound3DBuf = NULL;

		_backgroundMusic = new SoundBackground();

#if 1
		vgKernel::CamMgrHolder::getSingleton().getCamManager()->registerObserver( this );
#endif
		//registerOperatorHandle( );
	}

	SoundManager::~SoundManager()
	{
		//Modify by ZhouZY 2010-3-29 22:16
		//CamManager此时已经析构故下行代码会导致程序崩溃
		// 见vgkSingletonLifeTimeDefine.h---CamManager的生命期比CamMgrHolder要短
#if 0		
		vgKernel::CamMgrHolder::getSingleton().getCamManager()->unregisterObserver( this );
#endif
		unloadData();
	}

	bool SoundManager::Init(HWND hWnd,
		DWORD dwCoopLevel /*=DSSCL_PRIORITY*/)
	{

#if 0
 		HTREEITEM h3DSound =
 			vgUI::UIController::getSingleton().getEntryRootItemByType(STATIC_ENTRY_SOUND);
 
 		//HTREEITEM	h3DSound = vgUI::UIController::getSingleton()->GetRoot3DSound();
 
 		//vgBaseEntry* entry = vgEntryFactory::createEntryFromRenderer( _backgroundMusic );
 		
 		//case vgSound::RENDERER_TYPE_SOUND:
 		//	ret = new vgSound3DEntry( (vgSound::Sound3D*)renderer );
 		//	break;
 
 		vgBaseEntry* entry = new vgSound3DEntry( (vgSound::Sound3D*)_backgroundMusic );
 
 
 		vgUI::UIController::getSingleton().AddNode( h3DSound, entry );
 
 		if (h3DSound != NULL)
 		{
 			vgUI::UIController::getSingleton().GetWorkSpaceBar()->Expand(h3DSound );
 			vgUI::UIController::getSingleton().GetWorkSpaceBar()->EnsureVisible(h3DSound);
 		}

#endif

		HRESULT hr = DirectSoundCreate8(NULL,&m_pDirectSound,NULL);
		if(FAILED(hr))
		{
			assert(0);
			return FALSE;
		}
		if(FAILED(m_pDirectSound->SetCooperativeLevel(hWnd,dwCoopLevel))) 
		{
			assert(0);
			return FALSE;
		}

		return true;
	}
	bool SoundManager::SetPrimaryBufferFormat(WORD wChannels,DWORD dwSamplesPreSec, WORD wBitsPerSample)
	{
		if(m_pDirectSound==NULL)
		{
			return FALSE;
		}
		DSBUFFERDESC bufferDesc;
		ZeroMemory(&bufferDesc,sizeof(DSBUFFERDESC));
		bufferDesc.dwSize = sizeof(DSBUFFERDESC);
		bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER|DSBCAPS_CTRL3D;
		bufferDesc.dwBufferBytes = 0;
		bufferDesc.lpwfxFormat = NULL;
		LPDIRECTSOUNDBUFFER pDirectSoundBuf=NULL;
		if(FAILED(m_pDirectSound->CreateSoundBuffer(&bufferDesc,&pDirectSoundBuf,NULL)))
			return FALSE;

		if (FAILED(pDirectSoundBuf->QueryInterface(IID_IDirectSound3DListener,(void**)&pListener)))
		{
			MessageBox(NULL,"创建IDirectSound3DListener出错","DirectSound Error",MB_OK);
			return FALSE;
		}

		WAVEFORMATEX waveFormat;
		ZeroMemory(&waveFormat,sizeof(WAVEFORMATEX));
		waveFormat.wFormatTag = (WORD)WAVE_FORMAT_PCM;
		waveFormat.nChannels = (WORD)wChannels;
		waveFormat.nSamplesPerSec = (DWORD)dwSamplesPreSec;
		waveFormat.wBitsPerSample = (WORD)wBitsPerSample;
		waveFormat.nBlockAlign= (WORD)(waveFormat.wBitsPerSample/8)*waveFormat.nChannels;
		waveFormat.nAvgBytesPerSec = (DWORD)waveFormat.nSamplesPerSec*waveFormat.nBlockAlign;

		HRESULT hr;

		if(hr = pDirectSoundBuf->SetFormat(&waveFormat)) 
		{
			MessageBox(NULL,"设置wav格式时出错","DirectSound Error",MB_OK);
			return FALSE;

		}


		pDirectSoundBuf->Release();
		return true;

	}

	bool SoundManager::SetListenerPos(float x,float y,float z)
	{
		if ( _initialised == false )
		{
			return false;
		}
		if (FAILED(pListener->SetPosition(x,y,z,DS3D_IMMEDIATE)))
			return false;
		return true;

	}

	void SoundManager::Set3DParameters( FLOAT fDopplerFactor, FLOAT fRolloffFactor)
	{
		dsListenerParams.flDopplerFactor = fDopplerFactor;
		dsListenerParams.flRolloffFactor = fRolloffFactor;
		pListener->GetAllParameters(&dsListenerParams);
		if( pListener )
			pListener->SetAllParameters( &dsListenerParams, DS3D_IMMEDIATE );

		/*		dsBufferParams.flMinDistance = fMinDistance;
		dsBufferParams.flMaxDistance = fMaxDistance;
		pDirectSound3DBuf->GetAllParameters(&dsBufferParams);
		if( pDirectSound3DBuf)
		pDirectSound3DBuf->SetAllParameters( &dsBufferParams, DS3D_IMMEDIATE );*/
	}
	//----------------------------------------------------------------
	bool SoundManager::initialise( HWND hWnd )
	{

		_hwnd = hWnd;

		assert( hWnd != NULL );

		CoInitialize(NULL);

		return true;


		//return initImplement();


	}
	//------------------------------------------------------------------

	void SoundManager::copySoundfile( const String& attachDataPath)
	{
		bool bPlay = _backgroundMusic->getPlayFlag();
		if (bPlay)
		{
			_backgroundMusic->stopPlaying();
		}

		//////////////////////////////////////////////////////////////////////////
		std::vector<Sound3DPtr>::iterator sound3ditr = _sound3Ds.begin();

		std::vector<Sound3DPtr>::iterator sound3ditrend = _sound3Ds.end();

		std::string desFilePath, srcFilePath;
		for( ; sound3ditr != sound3ditrend; ++sound3ditr )
		{
			srcFilePath = (*sound3ditr)->getWavePath();

			if ( srcFilePath != "" )
			{
				desFilePath = attachDataPath + (*sound3ditr)->getName();

				bool save_ret = vgKernel::SystemUtility::copyFile( srcFilePath , desFilePath );

				assert( save_ret == true );
			}


		}
		//////////////////////////////////////////////////////////////////////////

		srcFilePath = _backgroundMusic->getFilePath();

		if ( srcFilePath != "" )
		{
			desFilePath = attachDataPath + _backgroundMusic->getSoundName();

			bool save_ret = vgKernel::SystemUtility::copyFile( srcFilePath , desFilePath );

			assert( save_ret == true );
		}
		
		if (bPlay)
		{
			_backgroundMusic->startPlaying();
		}
		return;

	}
#if 0	
	//----------------------------------------------------------------
	void SoundManager::writeToFile( vgKernel::StreamWriterPtr  pCfile 
		, const String& attachDataPath)
	{
		checkForInitailised();

		/////////////////////////
		copySoundfile(attachDataPath);

		int kk = _sound3Ds.size();

		pCfile->write( &kk, sizeof(int) );

		Sound3DPtrVec::iterator sound3ditr = _sound3Ds.begin();

		Sound3DPtrVec::iterator sound3ditrend = _sound3Ds.end();

		for( ; sound3ditr != sound3ditrend; ++sound3ditr )
		{
			(*sound3ditr)->WriteToFile( pCfile );
		}
		
		_backgroundMusic->WriteToFile( pCfile );


		
	}
	//----------------------------------------------------------------
	bool SoundManager::readFromFile( vgKernel::StreamReaderPtr pCfile
		, const String& attachDataPath)
	{
		return true;
	}
	//------------------------------------------------------------------
	void SoundManager::writeToFile( CFile*  pCfile, const String& attachDataPath)
	{
		checkForInitailised();

		/////////////////////////
		copySoundfile(attachDataPath);

		int kk = _sound3Ds.size();

		pCfile->Write( &kk, sizeof(int) );

		std::vector<Sound3DPtr>::iterator sound3ditr = _sound3Ds.begin();

		std::vector<Sound3DPtr>::iterator sound3ditrend = _sound3Ds.end();

		for( ; sound3ditr != sound3ditrend; ++sound3ditr )
		{
			(*sound3ditr)->WriteToFile( pCfile );
		}

		_backgroundMusic->WriteToFile( pCfile );



	}

 
	//----------------------------------------------------------------
	bool SoundManager::readFromFile( CFile*  pCfile, const String& attachDataPath)
	{
		checkForInitailised();

		int k;
		String	soundFullName;
		

		pCfile->Read( &k, sizeof(int) );

		for (int i =0; i < k; i++)
		{
			Sound3DPtr aa( new Sound3D() );

			aa->ReadFromFile( pCfile );

			soundFullName = attachDataPath + aa->getName();

			if(!aa->loadWaveFile(soundFullName.c_str()))	
				continue;

			aa->setWavePath(soundFullName);

			aa->setVolume( DSBVOLUME_MAX );
			aa->setSoundPram(0.1, 100000);

			aa->setAbsolutePos( aa->getSoundPos().x,
				aa->getSoundPos().y,aa->getSoundPos().z);

			//aa->startPlaying( aa->getPlayFlag() );
			if (aa->getPlayFlag())
			{
				aa->startPlaying(true);
			}
			else
			{
				aa->stopPlaying();
			}

			onChanged(0,NULL);

			_sound3Ds.push_back( aa );
			//////////////////////////////////////////////////////////////////////////界面chunyongma
			HTREEITEM	h3DSound = vgUI::UIController::getSingleton().GetRoot3DSound();

			vgBaseEntry* entry = vgEntryFactory::createEntryFromRenderer( aa.getPointer() );
			vgUI::UIController::getSingleton().AddNode( h3DSound, entry );

			if (h3DSound != NULL)
			{
				vgUI::UIController::getSingleton().GetWorkSpaceBar()->Expand(h3DSound );
				vgUI::UIController::getSingleton().GetWorkSpaceBar()->EnsureVisible(h3DSound);
			}

		}//for

		_backgroundMusic->ReadFromFile(pCfile);

		String musicName( _backgroundMusic->getSoundName());
		if (!musicName.empty())
		{
			soundFullName	= attachDataPath + musicName;
			_backgroundMusic->setFilePath( soundFullName  );
		}

		_backgroundMusic->reset();

		return true;
	}

#endif
	//------------------------------------------------------------------

	Sound3D* SoundManager::create3DSoundFromCurrentPos(std::string wavpath)
	{

		checkForInitailised();
 		
		Sound3DPtr aa( new Sound3D() );
 
 		if(aa->loadWaveFile(wavpath.c_str()))		
		{
			aa->setVolume( DSBVOLUME_MAX );
			aa->setSoundPram(0.1, 100000);

			vgKernel::Vec3 apos = 
				vgKernel::CamMgrHolder::getSingleton().getCamManager()->getCurrentPosition();

			aa->setAbsolutePos(
				apos.x, apos.y , apos.z);
			
			aa->startPlaying( true );

			onChanged(0,NULL);

			//std::string sndNodeName = wavpath.substr( wavpath.find_last_of("\\/")+1 , 
			//	wavpath.find_last_of(".") - wavpath.find_last_of("\\/") - 1 );
			String sndNodeName = vgKernel::StringUtility::getFilenameFromAbsolutePath(wavpath);
			aa->setName( sndNodeName );

			aa->setWavePath( wavpath );

			_sound3Ds.push_back( aa );

			return aa.getPointer();
		}
		else
			return NULL;

	}

	//----------------------------------------------------------------
	bool SoundManager::initImplement()
	{
		const float MAP_SCALE	= 20.0f;	

		Init(_hwnd);

		//------------------------------------------
		// WORD wChannels=2,DWORD dwSamplesPreSec=44100,WORD wBitsPerSample=16
		//------------------------------------------
		bool initret = SetPrimaryBufferFormat( 2 , 44100 , 16 );

		assert( initret == true );

		Set3DParameters(0,0.01);
 		SetListenerPos(0,0,200/MAP_SCALE);


		_initialised = true;

		return true;
	}
	//----------------------------------------------------------------
	void SoundManager::checkForInitailised( bool bDirectly /*= false*/)
	{
		if ( _initialised == false && !bDirectly)
		{
			bool init_result =initImplement( );
			assert( init_result == true );
			if ( init_result == false )
			{
				MessageBox(NULL , "DirectSound致命错误" , "Error" , MB_OK );
			}
		}

	}
	//----------------------------------------------------------------

	void SoundManager::onChanged(int eventId, void *param)
	{
		std::vector<Sound3DPtr>::iterator aa = _sound3Ds.begin();

		std::vector<Sound3DPtr>::iterator aaend = _sound3Ds.end();

		for( ; aa != aaend; aa++ )
		{
			vgKernel::Vec3 pp = (*aa)->getSoundPos();

			vgKernel::Vec3 apos = 
				vgKernel::CamMgrHolder::getSingleton().getCamManager()->getCurrentPosition();


			vgKernel::Vec3 qq = (pp - apos) * ( (*aa)->getAttenuation() );
			
			(*aa)->setSoundPos( qq.x ,qq.y, qq.z );
		}
	}

	void SoundManager::createDlgToSetBackgroundMusic()
	{
		char strFilter[]=
			"MP3 Files (*.mp3)|*.mp3|" /*
			"WAV Files (*.wav)|*.wav|"
			"MID Files (*.mid)|*.mid|"
			"WMA Files (*.wma)|*.wma||"*/;
		CFileDialog  OpenDlg(TRUE,
			NULL,
			NULL,
			OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
			strFilter);
		int nFlags=OpenDlg.DoModal();
		if(nFlags==IDOK)
		{
			std::string m_strFileName=OpenDlg.GetPathName();

			_backgroundMusic->setFilePath( m_strFileName );
						
			_backgroundMusic->reset();
	 	}
		return;

	}

	//////////////////////////////////////////////////////////////////////////chunyongma2008.9.8
	bool SoundManager::onDeleteRenderer( vgKernel::Renderer *render )
	{
		if ( render->getType() != RENDERER_TYPE_SOUND )
		{
			return false;
		}

		std::vector<Sound3DPtr>::iterator iter_Sound = _sound3Ds.begin();
		std::vector<Sound3DPtr>::iterator iterEnd_Sound = _sound3Ds.end();
		switch (render->getType() )
		{
		case RENDERER_TYPE_SOUND:
			for( ; iter_Sound != iterEnd_Sound; iter_Sound++ )
			{
				if ((*iter_Sound).getPointer() == render)
				{
					_sound3Ds.erase( iter_Sound );
					break;
				}
			}
			break;

		default:
			break;
		}//switch

		return true;
	}

	Sound3D* SoundManager::getSound3DPtr( const String& sound3dName )
	{
		Sound3DPtrVec::iterator iter = _sound3Ds.begin();
		Sound3DPtrVec::iterator iter_end = _sound3Ds.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			Sound3D* psound = (*iter).getPointer();

			assert( psound != NULL );

			if ( psound->getName() == sound3dName )
			{
				return psound;
			}
		}

		return NULL;
	}

	void SoundManager::unloadData()
	{
		_sound3Ds.clear();

		if ( _backgroundMusic != NULL )
		{
			delete _backgroundMusic;

			_backgroundMusic = NULL;
		}

		if(pListener)
		{
			pListener->Release();
			pListener = NULL;
		}

		if(m_pDirectSound)
		{
			m_pDirectSound->Release();
			m_pDirectSound = NULL;
		}

	}

	void SoundManager::reset()
	{
		_sound3Ds.clear();

		_backgroundMusic->setFilePath(std::string(""));

		_backgroundMusic->setPlayFlag( true );

		checkForInitailised();
	}

	void	SoundManager::setBackgroundMusicFromCurrentPos( const String& file_name )
	{
		checkForInitailised();

		_backgroundMusic->setFilePath( file_name );

		_backgroundMusic->reset();
	}


	//-----------------------------------------------------------------------
	bool SoundManager::importFiles( const vgKernel::StringVector& strvec,
		bool bSpecial/* = false*/)
	{
		//------------------------------------------
		// 开始导入
		//------------------------------------------
		if( strvec.empty() )
			return false;

		String ext = vgKernel::StringUtility::getFileExtension( strvec[0] );

		std::ostringstream o;
		o	<< "-----------------------------------------------------------\n"; 
#if VGK_LANG_CHS
		o << "\t\t正在执行 导入" << ext << "操作:\n";
#else
		o << "\t\tImporting "<< ext << ":\n";
#endif
		o	<< "-----------------------------------------------------------\n" ;
		VGK_SHOW( o.str() );


		bool ret = true;

		vgKernel::StringVector::const_iterator iter = strvec.begin();
		vgKernel::StringVector::const_iterator iter_end = strvec.end();


		for ( ; iter != iter_end ; ++ iter )
		{
			if ( importFile( *iter , bSpecial) == false )
			{
				ret = false;
			}

		}// for

		// 重新构树
		vgKernel::RendererManager::getSingleton().invalidate();


		std::ostringstream oEnd;
		oEnd<< "-----------------------------------------------------------\n"; 
#if VGK_LANG_CHS
		oEnd<< "\t\t完成执行 导入"<< ext << "操作!\n";
#else
		oEnd<< "\t\tImport "<< ext << " Completed!\n";
#endif
		oEnd<< "-----------------------------------------------------------\n" ;
		VGK_SHOW( oEnd.str() );

		vgKernel::SystemUtility::setCurrentDirectory(strvec[0]);

		return ret;
	}

	//----------------------------------------------------------------
	bool SoundManager::importFile( const String& impFile,
		bool bSpecial/* = false*/ )
	{
		if ( importFileImpl( impFile , bSpecial) == true )
		{	
			std::ostringstream oEnd;
			oEnd << "\t成功导入文件:"<< impFile << " \n";
			VGK_SHOW( oEnd.str() );
			return true;
		}
		else
		{
			std::ostringstream oEnd;
			oEnd << "\t导入文件:"<< impFile << " 失败\n";
			VGK_SHOW( oEnd.str() );
			return false;
		}
	}	

	//----------------------------------------------------------------
	bool	SoundManager::importBackgroundMusicFile( const String& file_name)
	{
		vgSound::SoundManager::getSingleton().setBackgroundMusicFromCurrentPos( file_name );

		HTREEITEM h3DSound =
			vgUI::UIController::getSingleton().getEntryRootItemByType(STATIC_ENTRY_SOUND);
		
		// 添加到节点视图
		vgBaseEntry* entry = new vgSoundBackgroundEntry( (vgSound::SoundBackground*)_backgroundMusic );

		vgUI::UIController::getSingleton().AddNode( h3DSound, entry );

 		if (h3DSound != NULL)
 		{
			vgUI::UIController::getSingleton().GetWorkSpaceBar()->Expand(h3DSound );
			vgUI::UIController::getSingleton().GetWorkSpaceBar()->EnsureVisible(h3DSound);
 		}
		return true;
	}
	//----------------------------------------------------------------
	bool	SoundManager::import3DMusicFile( const String& file_name)
	{
		vgSound::Sound3D* _sound = 
			vgSound::SoundManager::getSingleton().create3DSoundFromCurrentPos( file_name );

		if ( _sound == NULL )
		{
			return false;
		}


		HTREEITEM h3DSound =
		vgUI::UIController::getSingleton().getEntryRootItemByType(STATIC_ENTRY_SOUND);

		//HTREEITEM	h3DSound = vgUI::UIController::getSingleton()->GetRoot3DSound();
 
 		//vgBaseEntry* entry = vgEntryFactory::createEntryFromRenderer( _sound );
		// 添加到节点视图
 		vgBaseEntry* entry = new vgSound3DEntry( (vgSound::Sound3D*)_sound );
		
		vgUI::UIController::getSingleton().AddNode( h3DSound, entry );
 
 		if (h3DSound != NULL)
 		{
 			vgUI::UIController::getSingleton().GetWorkSpaceBar()->Expand(h3DSound );
 			vgUI::UIController::getSingleton().GetWorkSpaceBar()->EnsureVisible(h3DSound);
 		}


		return true;
	}

	//----------------------------------------------------------------
	bool SoundManager::importFileImpl( const String& filename,
		bool bSpecial/* = false*/ )
	{
		String	fileExt = vgKernel::StringUtility::getFileExtension( filename );

		vgKernel::StringUtility::toLowerCase(fileExt);


		if ( fileExt == "wav" )
		{
			return import3DMusicFile( filename );
		}
		else if ( fileExt == "mp3" )
		{
			return importBackgroundMusicFile( filename );
		}
		else
			return false;
	}

	//------------------------------------------------------------------
	bool SoundManager::readSoundMgrFromFile( vgKernel::StreamReaderPtr preader , 
		const String& attachDataPath )
	{
		using namespace vgSound;

		SoundManager* mgr = 
			SoundManager::getSingletonPtr();

		mgr->checkForInitailised();

		int k;
		std::string	soundFullName;

		preader->read( &k, sizeof(int) );

		for (int i =0; i < k; i++)
		{
			Sound3DPtr aa( new Sound3D() );

			aa->readFromFile( preader );

			soundFullName = attachDataPath + aa->getName();

			if(!aa->loadWaveFile(soundFullName.c_str()))	
				continue;

			aa->setWavePath(soundFullName);

			aa->setVolume( DSBVOLUME_MAX );
			aa->setSoundPram(0.1, 100000);

			aa->setAbsolutePos( aa->getSoundPos().x,
				aa->getSoundPos().y,aa->getSoundPos().z);

			//aa->startPlaying( aa->getPlayFlag() );
			if (aa->getPlayFlag())
			{
				aa->startPlaying(true);
			}
			else
			{
				aa->stopPlaying();
			}

			mgr->onChanged(0,NULL);

			mgr->getSoundVec().push_back( aa );
 			
			//////////////////////////////////////////////////////////////////////////
			HTREEITEM	h3DSound = vgUI::UIController::getSingleton().getEntryRootItemByType(STATIC_ENTRY_SOUND);

			vgBaseEntry* entry = vgEntryFactory::createEntryFromRenderer( aa.getPointer() );
			vgUI::UIController::getSingleton().AddNode( h3DSound, entry );

			if (h3DSound != NULL)
			{
				vgUI::UIController::getSingleton().GetWorkSpaceBar()->Expand(h3DSound );
				vgUI::UIController::getSingleton().GetWorkSpaceBar()->EnsureVisible(h3DSound);
			}


		}//for

		mgr->getBackMusic()->readFromFile(preader);

		std::string musicName( mgr->getBackMusic()->getSoundName());
		if (!musicName.empty())
		{
			soundFullName	= attachDataPath + musicName;
			mgr->getBackMusic()->setFilePath( soundFullName  );
		}

		mgr->getBackMusic()->reset();

		return true;
	}


	//------------------------------------------------------------------
	bool SoundManager::writeSoundMgrToFile( vgKernel::StreamWriterPtr pwriter , 
		const String& attachDataPath )
	{
		using namespace vgSound;

		SoundManager* mgr = 
			SoundManager::getSingletonPtr();

		mgr->checkForInitailised();

		// Part 1: 拷贝文件
		mgr->copySoundfile(attachDataPath);


		Sound3DPtrVec& _vector = mgr->getSoundVec();

		// Part 2: 写入队列
		int kk = _vector.size();
		pwriter->write( &kk, sizeof(int) );
		Sound3DPtrVec::iterator itr = _vector.begin();
		Sound3DPtrVec::iterator itrEnd = _vector.end();
		for( ; itr != itrEnd; ++itr )
		{
			(*itr)->writeToFile( pwriter );
		}

		// Part 3: 
		SoundBackground *back = mgr->getBackMusic();

		back->writeToFile( pwriter );


		return true;
	}
	//------------------------------------------------------------------

}// end of namespace 

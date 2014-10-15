


#include <vgStableHeaders.h>

#include <vgSound/vggSoundManagerSaver.h>
#include <vgSound/vgSoundManager.h>

#include <vgKernel/vgkRendererManager.h>
#include <vgKernel/vgkStringUtility.h>
#include <vgKernel/vgkSystemUtility.h>

#include <vgUIController/vgUIController.h>
#include <vgUIController/vgWorkSpaceBar.h>
#include <vgEntry/vgEntryFactory.h>

#include <vgEntry/vgSound3DEntry.h>		// Add By FengYK @2010-03-19 14:49
#include <vgEntry/vgSoundBackgroundEntry.h>

#include <vgConf/vgcoExeConfig.h>

#define VGDATA_PATHCONF					"DataPathConfig"
#define VGDATA_PATHCONF_PATH_SOUND		"SoundPath"

namespace vgSound {
	
	
	//------------------------------------------------------------------
	bool SoundManagerSaver::readSoundMgrFromFile( vgKernel::StreamReaderPtr preader , 
		const String& attachDataPath,
		bool bReadDirectly/* = false*/)
	{
		using namespace vgSound;

		String abs_path = 
			vgKernel::StringUtility::getPathFromAbsoluteFilename(attachDataPath);

		String g_DataPath =  VG_EXECONF_GET_STRING( 
			VGDATA_PATHCONF,  
			VGDATA_PATHCONF_PATH_SOUND);

		abs_path += g_DataPath;

		SoundManager* mgr = 
			SoundManager::getSingletonPtr();

		mgr->checkForInitailised( bReadDirectly );

		int k = 0;
		String	soundFullName;
		String	errorFiles;

		preader->read( &k, sizeof(int) );

		for (int i =0; i < k; i++)
		{
			Sound3DPtr aa( new Sound3D() );

			aa->readFromFile( preader );

			soundFullName = abs_path + aa->getName();

			if(!aa->loadWaveFile(soundFullName.c_str()))	
			{
				errorFiles += soundFullName;
				errorFiles += '\n';
				continue;
			}

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

			if ( !bReadDirectly )
			{
				HTREEITEM	h3DSound = vgUI::UIController::getSingleton().getEntryRootItemByType(STATIC_ENTRY_SOUND);

				//vgBaseEntry* entry = vgEntryFactory::createEntryFromRenderer( aa.getPointer() );
				
				// Edit By FengYK @2010-03-19 16:29
				vgBaseEntry* entry = new vgSound3DEntry( (vgSound::Sound3D*)aa.getPointer() );

				vgUI::UIController::getSingleton().AddNode( h3DSound, entry );

				if (h3DSound != NULL)
				{
					vgUI::UIController::getSingleton().GetWorkSpaceBar()->Expand(h3DSound );
					vgUI::UIController::getSingleton().GetWorkSpaceBar()->EnsureVisible(h3DSound);
				}
			}



		}//for

		mgr->getBackMusic()->readFromFile(preader);

		std::string musicName( mgr->getBackMusic()->getSoundName());
		if (!musicName.empty())
		{
			soundFullName	= abs_path + musicName;

			if( !vgKernel::SystemUtility::checkFileExist(soundFullName) )
			{
				errorFiles += soundFullName;
				errorFiles += '\n';
			}
			else
			{
				mgr->getBackMusic()->setFilePath( soundFullName  );

				// 添加背景音乐节点到节点视图 Add By FengYK @2010-03-19 16:51
				HTREEITEM h3DSound =
					vgUI::UIController::getSingleton().getEntryRootItemByType(STATIC_ENTRY_SOUND);

				vgBaseEntry* entry = new vgSoundBackgroundEntry( (vgSound::SoundBackground*)(mgr->getBackMusic()) );

				vgUI::UIController::getSingleton().AddNode( h3DSound, entry );

				if (h3DSound != NULL)
				{
					vgUI::UIController::getSingleton().GetWorkSpaceBar()->Expand(h3DSound );
					vgUI::UIController::getSingleton().GetWorkSpaceBar()->EnsureVisible(h3DSound);
				}
			}
		}
		

		mgr->getBackMusic()->reset();

		if ( !errorFiles.empty())
		{
			errorFiles += "缺失！";
			//AfxMessageBox( errorFiles.c_str() );
			vgKernel::SystemUtility::showModelDialog(errorFiles);
		}

		return true;
	}

	bool SoundManagerSaver::readSoundMgrFromFile( const String& save_absolute_path , 
		const String& attachDataPath,
		bool bReadDirectly/* = false*/)
	{
		String filePath = vgKernel::StringUtility::
			getPathFromAbsoluteFilename(save_absolute_path);

		String fileName = vgKernel::StringUtility::
			getFilenameWithoutExtFromAbsPath(save_absolute_path);
		fileName += ".snd";

		filePath += fileName;

		bool isFileExist = vgKernel::SystemUtility::checkFileExist(filePath);

		if (!isFileExist)
		{
			std::ostringstream oStr;
#if VGK_LANG_CHS
			oStr << "\n\t声音模块文件:"<< filePath << "不存在！\n"
				<< "请用VG转换器转换场景文件。\n";
#else
			oStr << "\n\tFile: "<< filePath << "Does Not Exist! \n"
				<< "Please Update Scene File By VGUpdater.\n";
#endif
			VGK_SHOW( oStr.str() );
			return false;
		}

		vgKernel::StreamReaderPtr m_pfile = 
			vgKernel::StreamReaderFactory::createFromFile( filePath );

		return readSoundMgrFromFile( m_pfile, attachDataPath, bReadDirectly);
	}
	
	//------------------------------------------------------------------
	bool SoundManagerSaver::writeSoundMgrToFile( vgKernel::StreamWriterPtr pwriter , 
		const String& attachDataPath ,
		bool bReadDerectly)
	{
		using namespace vgSound;

		String abs_path = 
			vgKernel::StringUtility::getPathFromAbsoluteFilename(attachDataPath);

		String g_DataPath =  VG_EXECONF_GET_STRING( 
			VGDATA_PATHCONF,  
			VGDATA_PATHCONF_PATH_SOUND);

		abs_path += g_DataPath;

		SoundManager* mgr = 
			SoundManager::getSingletonPtr();

		mgr->checkForInitailised( bReadDerectly );

		// Part 1: 拷贝文件
		if ( !bReadDerectly )
		{
			mgr->copySoundfile(abs_path);
		}


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

	bool SoundManagerSaver::writeSoundMgrToFile( const String& save_absolute_path , 
		const String& attachDataPath ,
		bool bReadDerectly)
	{
		String filePath = vgKernel::StringUtility::
			getPathFromAbsoluteFilename(save_absolute_path);

		String fileName = vgKernel::StringUtility::
			getFilenameWithoutExtFromAbsPath(save_absolute_path);
		fileName += ".snd";

		filePath += fileName;

		vgKernel::StreamWriterPtr m_pfile = 
			vgKernel::StreamWriterFactory::createFromFile( filePath );

		return writeSoundMgrToFile( m_pfile, attachDataPath, bReadDerectly);
	}
	//------------------------------------------------------------------
}// end of namespace vgGlobal

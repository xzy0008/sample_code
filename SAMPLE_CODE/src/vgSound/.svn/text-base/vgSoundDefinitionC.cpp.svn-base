


#include <vgStableHeaders.h>

#include <vgSound/vgSoundManager.h>
#include <vgSound/vggSoundManagerSaver.h>

#include <vgKernel/vgkVec3.h>
#include <vgSound/vgSound3D.h>
#include <vgSound/vgSoundBackground.h>


#include <vgSound/vgSoundDefinition.h>


using namespace vgSound;


//----------------------------------------------------------------
SoundBackgroundH SoundManager_getCurrentBackgroundMusic()
{
	return (SoundBackgroundH)SoundManager::getSingleton().getCurrentBackgroundMusic();
}

//----------------------------------------------------------------
Sound3DH SoundManager_getSound3DPtr( const String& sound3dName )
{
	return (Sound3DH)SoundManager::getSingleton().getSound3DPtr( sound3dName );
}

//----------------------------------------------------------------
void SoundManager_setBackgroundMusicFromCurrentPos( const String& file_name)
{
	return SoundManager::getSingleton().setBackgroundMusicFromCurrentPos( file_name );
}

//----------------------------------------------------------------
void SoundManager_createDlgToSetBackgroundMusic()
{
	return SoundManager::getSingleton().createDlgToSetBackgroundMusic();
}


//----------------------------------------------------------------
bool SoundManager_importFiles(const vgKernel::StringVector& strvec,
							  bool bSpecial )
{
	return SoundManager::getSingleton().importFiles( strvec, bSpecial );
}

//----------------------------------------------------------------
bool SoundManager_readSoundMgrFromFile( vgKernel::StreamReaderPtr preader , 
									   const String& attachDataPath)
{
	return SoundManager::getSingleton().readSoundMgrFromFile(
		preader, attachDataPath );
}

//----------------------------------------------------------------
bool SoundManager_writeSoundMgrToFile( vgKernel::StreamWriterPtr pwriter ,  const String& attachDataPath )
{
	return SoundManager::getSingleton().writeSoundMgrToFile(  pwriter ,  attachDataPath );
}

//----------------------------------------------------------------
bool SoundManager_initialise(  HWND hWnd )
{
	return SoundManager::getSingleton().initialise( hWnd );
}


//----------------------------------------------------------------
bool SoundManagerSaver_readSoundMgrFromFile(
	const String& save_absolute_path ,  
	const String& attachDataPath ,
	bool bDirectly )
{
	return SoundManagerSaver::readSoundMgrFromFile(
		save_absolute_path, attachDataPath ,bDirectly);
}

//----------------------------------------------------------------
bool SoundManagerSaver_writeSoundMgrToFile(
	const String& save_absolute_path ,  const String& attachDataPath,
	bool bDirectly )
{
	return SoundManagerSaver::writeSoundMgrToFile( save_absolute_path, attachDataPath, bDirectly);
}


//----------------------------------------------------------------
bool SoundManagerSaver_readSoundMgrFromFile2(
	vgKernel::StreamReaderPtr preader ,  
	const String& attachDataPath ,
	bool bDirectly )
{
	return SoundManagerSaver::readSoundMgrFromFile(
		preader, attachDataPath  ,bDirectly);
}

//----------------------------------------------------------------
bool SoundManagerSaver_writeSoundMgrToFile2(
	vgKernel::StreamWriterPtr pwriter ,  const String& attachDataPath ,
	bool bDirectly )
{
	return SoundManagerSaver::writeSoundMgrToFile(
		pwriter, attachDataPath, bDirectly);
}


//----------------------------------------------------------------
void SoundManager_unloadData( )
{
	SoundManager::getSingleton().unloadData( );
}

//----------------------------------------------------------------
void SoundManager_reset( )
{
	SoundManager::getSingleton().reset( );
}
//----------------------------------------------------------------

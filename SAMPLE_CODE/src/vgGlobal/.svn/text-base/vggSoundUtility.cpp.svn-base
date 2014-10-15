


#include <vgStableHeaders.h>
#include <vgGlobal/vggSoundUtility.h>

//#include <vgsound/vgSoundManager.h>
#include <vgSound/vgSoundDefinition.h>
#include <vgKernel/vgkPluginManager.h>



namespace vgGlobal{

	//----------------------------------------------------------------
	bool SoundUtility::addBackgroundSound()
	{
		vgKernel::StringVector strExts;
		strExts.push_back("mp3");
		vgKernel::StringVector strVec = vgKernel::SystemUtility::getFilesOpenByDialog(strExts);

		//vgSound::SoundManager::getSingleton().importFiles( strVec );
		VGK_DLL_RUN_CLASSFUNC( VGSOUND_DLL_NAME , SoundManager, importFiles )(strVec, false);

		return true;
	}

	//----------------------------------------------------------------
	bool SoundUtility::addStereo()
	{
		vgKernel::StringVector strExts;
		strExts.push_back("wav");
		vgKernel::StringVector strVec = vgKernel::SystemUtility::getFilesOpenByDialog(strExts);

		//¶ÁÈ¡ÉùÒôÎÄ¼þ
		//vgSound::SoundManager::getSingleton().importFiles( strVec );
		VGK_DLL_RUN_CLASSFUNC( VGSOUND_DLL_NAME , SoundManager, importFiles )(strVec, false);

		return true;
	}
	

}//namespace vgXXX
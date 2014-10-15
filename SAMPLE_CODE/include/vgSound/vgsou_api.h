


#ifndef __VGSOUAPI_H__
#define __VGSOUAPI_H__

#include <vgKernel/vgkForward.h>

#ifdef __cplusplus
extern "C" {
#endif


	typedef void* SoundBackgroundH;

	typedef SoundBackgroundH (*pfnSoundManager_getCurrentBackgroundMusic)();
	extern VGSOUND_EXPORT  SoundBackgroundH SoundManager_getCurrentBackgroundMusic();

	typedef void* Sound3DH;

	typedef Sound3DH (*pfnSoundManager_getSound3DPtr )( const String& sound3dName );
	extern VGSOUND_EXPORT Sound3DH SoundManager_getSound3DPtr( const String& sound3dName );

	typedef void (*pfnSoundManager_createDlgToSetBackgroundMusic)();
	extern VGSOUND_EXPORT void SoundManager_createDlgToSetBackgroundMusic();

	typedef void (*pfnSoundManager_setBackgroundMusicFromCurrentPos)( const String& file_name);
	extern VGSOUND_EXPORT void SoundManager_setBackgroundMusicFromCurrentPos( const String& file_name);


	typedef bool (*pfnSoundManager_importFiles)(const vgKernel::StringVector& strvec,
		bool bSpecial);

	extern VGSOUND_EXPORT bool SoundManager_importFiles(const vgKernel::StringVector& strvec,
		bool bSpecial = false);


	typedef bool (*pfnSoundManager_readSoundMgrFromFile)( vgKernel::StreamReaderPtr preader , 
		const String& attachDataPath );

	extern VGSOUND_EXPORT bool SoundManager_readSoundMgrFromFile( vgKernel::StreamReaderPtr preader , 
		const String& attachDataPath );


	typedef bool (*pfnSoundManager_writeSoundMgrToFile)( vgKernel::StreamWriterPtr pwriter ,  const String& attachDataPath );

	extern VGSOUND_EXPORT bool SoundManager_writeSoundMgrToFile( vgKernel::StreamWriterPtr pwriter ,  const String& attachDataPath );


	typedef bool (*pfnSoundManager_initialise)( HWND hWnd );

	extern VGSOUND_EXPORT bool SoundManager_initialise(  HWND hWnd );


	typedef bool (*pfnSoundManagerSaver_readSoundMgrFromFile)( 
		const String& save_absolute_path , const String& attachDataPath ,
		bool bDirectly );
	extern VGSOUND_EXPORT bool SoundManagerSaver_readSoundMgrFromFile( 
		const String& save_absolute_path , const String& attachDataPath ,
		bool bDirectly );

	typedef bool (*pfnSoundManagerSaver_readSoundMgrFromFile2)( vgKernel::StreamReaderPtr preader , 
		const String& attachDataPath ,bool bReadDirectly );
	extern VGSOUND_EXPORT bool SoundManagerSaver_readSoundMgrFromFile2( vgKernel::StreamReaderPtr preader , 
		const String& attachDataPath ,bool bReadDirectly );


	typedef bool (*pfnSoundManagerSaver_writeSoundMgrToFile)( 
		const String& save_absolute_path ,  const String& attachDataPath, 
		bool bDirectly );
	extern VGSOUND_EXPORT bool SoundManagerSaver_writeSoundMgrToFile( 
		const String& save_absolute_path ,  const String& attachDataPath, 
		bool bDirectly );

	typedef bool (*pfnSoundManagerSaver_writeSoundMgrToFile2)( vgKernel::StreamWriterPtr pwriter ,  
		const String& attachDataPath ,
		bool bDirectly );
	extern VGSOUND_EXPORT bool SoundManagerSaver_writeSoundMgrToFile2( vgKernel::StreamWriterPtr pwriter ,  
		const String& attachDataPath ,
		bool bDirectly );

	typedef void (*pfnSoundManager_unloadData)();
	extern VGSOUND_EXPORT void SoundManager_unloadData();

	typedef void (*pfnSoundManager_reset)();
	extern VGSOUND_EXPORT void SoundManager_reset();

#ifdef __cplusplus
}
#endif



#endif // end of __VGSOUAPI_H__
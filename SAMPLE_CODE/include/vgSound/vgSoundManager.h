


#ifndef __VGSOUNDMANAGER_H__
#define __VGSOUNDMANAGER_H__


#include <vgSound/vgSoundDefinition.h>
#include <vgKernel/vgkSingleton.h>
#include <vgSound/vgSoundBackground.h>

#include <mmsystem.h>
#include <dsound.h>

#include <vgCam/vgcaCamManager.h>
#include<vgKernel/vgkRendererHolder.h>

namespace  vgSound {

	/**
	@date 	2008/05/21  20:23	
	@author  leven

	@brief 	

	@see    
	*/
	class  VGSOUND_EXPORT SoundManager  : 
		 public vgKernel::Singleton<SoundManager>, 
		public vgKernel::RendererObserver,
		public vgKernel::RendererHolder
	{
	public:
		SoundManager();
		~SoundManager();

		bool initialise()
		{
			return true;
		}

		bool shutdown()
		{		

			return true;
		}


		bool initialise( HWND hWnd );	


	   	void unloadData();

		void reset();



		IDirectSound8* GetDirectSound()
		{
			return m_pDirectSound;
		}
#if 0
		void writeToFile( CFile*  pCfile , const String& attachDataPath);
		void writeToFile( vgKernel::StreamWriterPtr  pCfile , const String& attachDataPath);

		bool readFromFile( CFile*  pCfile , const String& attachDataPath);

		bool readFromFile( vgKernel::StreamReaderPtr  pCfile , const String& attachDataPath);
#endif
		SoundBackground* getCurrentBackgroundMusic()
		{
			return _backgroundMusic;
		}

		virtual bool onDeleteRenderer( vgKernel::Renderer *render );//chunyongma2008.9.8

		void createDlgToSetBackgroundMusic();

		void	setBackgroundMusicFromCurrentPos( const String& file_name );


		Sound3D* create3DSoundFromCurrentPos( String wavpath);

		Sound3D* getSound3DPtr( const String& sound3dName );

		virtual void onChanged(int eventId, void *param);

		virtual bool onDelete()
		{
			return true;
		}

		


		//DirectSound Listener不好用，一直处于原点状态，如此只能设置声源位置
		//来影响音效

	public:

		void copySoundfile( const String& attachDataPath);

		void checkForInitailised( bool bDirectly = false );

		bool initImplement();

		Sound3DPtrVec &getSoundVec()
		{
			return _sound3Ds;
		}

		SoundBackground *getBackMusic()
		{
			return _backgroundMusic;
		}

	private:

		bool _initialised;

		HWND _hwnd;



		Sound3DPtrVec _sound3Ds;
		
		SoundBackground *_backgroundMusic;
		
	public:

		//////////////////////////////////////////////////////////////////////////

		bool SetPrimaryBufferFormat(WORD wChannels,DWORD dwSamplesPreSec, WORD wBitsPerSample);

		bool Init(HWND hWnd,
			DWORD dwCoopLevel=DSSCL_PRIORITY);

		bool SetListenerPos(float x,float y,float z);

		void Set3DParameters( FLOAT fDopplerFactor, FLOAT fRolloffFactor);
	
		bool importFiles( const vgKernel::StringVector& strvec, bool bSpecial = false);

		bool importFile( const String& impFile,bool bSpecial = false );
		
		bool import3DMusicFile( const String& file_name);
		
		bool importBackgroundMusicFile( const String& file_name);
	
		bool importFileImpl( const String& filename, bool bSpecial = false );


		bool readSoundMgrFromFile( vgKernel::StreamReaderPtr preader , 
			const String& attachDataPath );
	
		bool writeSoundMgrToFile( vgKernel::StreamWriterPtr pwriter ,  const String& attachDataPath );


		private:
	
		IDirectSound8 *m_pDirectSound;
		IDirectSound3DListener8 *pListener;

		DS3DLISTENER            dsListenerParams; 
//----------------------------------------------------------------------------------

	};




}// end of namespace 

#endif // end of __VGSOUNDMANAGER_H__


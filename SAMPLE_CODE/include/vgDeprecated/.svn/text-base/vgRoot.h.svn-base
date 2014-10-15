

#ifndef __VGROOT_H__
#define __VGROOT_H__

#include <vgCore/vgPrerequisites.h>
#include <vgCore/vgSingleton.h>


#include <vgTex/tvgTextureManager.h>
#include <vgTex/tvgGpuManager.h>
#include <vgTex/tvgArchiveManager.h>

//#include <vgPictureInPicture.h>



#include <vgMovingManager.h>


//#include <vgCoordinate.h>//2008.9.11

 


namespace vgCore {

 

//	class QuadtreeSceneManager;
//	class vgTextureLoadingQueue;
//	class LoadingModelQueue;

	class   VGDEP_EXPORT  Root : public ::Singleton<Root>
	{
	public:
		Root( const String& fileName = "win_log.log");
		~Root();


		/// 初始化必备的物件,包括LogManager和TextureManager以及ArchiveManger
		void initNecessity( );

		/// 初始化特别的物件,包括InputSystem.注意,本操作要在initNecessity完成之后.
		//bool initRequirement( const HINSTANCE& hinst , const HWND& hwnd );

		void uninitialise();

	private:

		void setDefaultParameters();

	private:


//		vgCoordinate *m_pcood;//2008.9.11

		MovingManager   *m_pMovingMgr;

 

//		SoundManager	*m_pSoundMgr;

//		LogManager		*m_pLogManager;

		TextureManager	*m_pTextureManager;
		
		vgCore::GpuManager		*m_pGpuManager;

		ArchiveManager *m_pArchiveManger;

		//QuadtreeSceneManager *m_pQtSceneManger;//add by ma

//		vgTextureLoadingQueue *m_TexLoadingQueue;

//		LoadingModelQueue *m_LoadingModelQueue;

//		PictureInPicture *m_PicInPic;


#if DIRECTINPUT_SUPPORT

		InputSystem		*m_pInputSystem;

#endif// end of DIRECTINPUT_SUPPORT


		String m_defaultLogName;

		HWND m_hWindow;

		HINSTANCE m_hInstance;


	public:
		static Root& getSingleton(void);
		static Root* getSingletonPtr(void);
	};



}// end of namespace vgCore
#endif // end of __VGROOT_H__
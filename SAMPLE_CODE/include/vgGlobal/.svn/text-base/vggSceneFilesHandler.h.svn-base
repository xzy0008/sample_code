


#ifndef __VGGSceneFilesHandler_H__
#define __VGGSceneFilesHandler_H__
#include <vgGlobal/vgglDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkRenderer.h>

#if 0
namespace vgGlobal {

	/**
		@date 	2009/09/08  10:43	
		@author  lss
	
		@brief 	
	
		@see    
	*/

	/*!
		本类中函数除exportModFile和exportVgFile外都已转移到SceneFileUtility类中
        exportModFile，exportVgFile目前只有声明和定义，没有用到。

		openSceneDirectly,saveSceneDirectly，目前未被SceneFileUtility中同名接口替换，
		当以下两接口替换后，本类可随时抛弃

		2009/10/21  9:53
	*/
	class  VGGL_EXPORT SceneFilesHandler
	{
	private:
		SceneFilesHandler()
		{
			
		}
	public:
		~SceneFilesHandler()
		{
			
		}
	
		// Part 1: File i/o
	public:

		static bool getSceneOpenedFlag();

		static bool resetScene();

		static bool saveScene( const String& save_vg_path );

		static bool saveSceneDirectly( const String& save_vg_path );

		static bool openScene( const String& vg_filepath );

		static bool openSceneDirectly( const String& vg_filepath );


		static bool importFiles( const vgKernel::StringVector& strvec , 
			bool bSpecial = false);

		static bool importFile( const String& impFile , 
			bool bSpecial = false );

		static bool exportFile( const String& impFile );

		static bool exportModelFile( const String& vgm_filepath );

		static String getCurrentScenePath()
		{
			return _currentScenePath;
		}
		
		static bool publishScene( const String& publish_vg_path );

		static unsigned int getUpdateTime();

		static void setUpdateTime(unsigned uiUpdateTime);
		
	private:
		static bool openSceneBegin( const String& vg_filepath );
		static bool openSceneImpl( const String& vg_filepath );
		static bool openSceneEnd( const String& vg_filepath );

		static bool saveSceneImpl( const String& save_vg_path );
		static bool saveSceneBegin( const String &save_vg_path );
		static void saveSceneEnd( const String& save_vg_path );

		static void setSceneOpenedFlag( const bool& opened )
		{
			_sceneOpened = opened;
		}

		static bool exportVgFileImpl( const String& save_vg_path );

		static bool importFileImpl( const String& filename , 
			bool bSpecial  );
	
		static bool exportFileImpl( const String& filename );

		static bool _sceneOpened;

		// 当前场景的路径,注意以/结尾.
		static String _currentScenePath;

		static	unsigned int _uiUpdateTime;
	};
	
	
}// end of namespace vgGlobal
	


#endif // end of __VGGSceneFilesHandler_H__
#endif
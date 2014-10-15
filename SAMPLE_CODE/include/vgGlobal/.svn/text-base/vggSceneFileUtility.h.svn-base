


#ifndef __VGSCENEFILEUTILITY_H__
#define __VGSCENEFILEUTILITY_H__

#include <vgGlobal/vgglDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgGlobal/vggVgmodUtility.h>

namespace vgGlobal{

	/**
		@date    2009/10/20  15:06
		@author  zzy

		@brief   整理了关于场景文件(打开，保存，导入，导出)相关操作的接口

		@see
	*/	

	class	VGGL_EXPORT SceneFileUtility
	{
	public:
		SceneFileUtility()	{}
		~SceneFileUtility()	{}

		// File Menu
	public:
		static bool openSceneFile();  //打开文件
		static bool saveSceneFile( bool bSaveMode = false );  //保存文件

		static bool importFiles();     //导入文件
		static bool exportFile();      //导出文件--目前只支持导出vgm文件

		//VgFileConverter的接口，将用它替换SceneFileHandle中同名接口（暂时未用）
		//zzy 2009/10/22  9:42
		static bool openSceneDirectly(); 
		static bool saveSceneDirectly();

		static unsigned int getUpdateTime();
		static void setUpdateTime( unsigned uiUpdateTime );
	
		static bool getSceneOpenedFlag();
		static void setSceneOpenedFlag( const bool& opened );

		static bool openScene( const String& vg_filepath );
		static bool saveScene( const String& save_vg_path );

	public:
		static bool openSceneBegin( const String& vg_filepath );
		static bool openSceneImpl( const String& vg_filepath );
		static bool openSceneEnd( const String& vg_filepath );

		static bool saveSceneImpl( const String& save_vg_path );
		static bool saveSceneBegin( const String &save_vg_path );
		static void saveSceneEnd( const String& save_vg_path );

		static bool importFiles( const vgKernel::StringVector& strvec, bool bSpecial = false);
		static bool importGivenFile( const String& impFile, bool bSpecial = false );
		static bool importFileImpl(  const String& impFile, bool bSpecial = false );

		static bool exportFile( const String& impFile );
		static bool exportFileImpl( const String& filename );

		static bool openSceneDirectly( const String& vg_filepath );
		static bool saveSceneDirectly( const String& save_vg_path );

		static String getCurrentScenePath()
		{
			return _currentScenePath;
		}

		static String getCurrentSceneVgPath()
		{
			return _currentVgPath;
		}

		static String getCurrentSceneVgimgPath()
		{
			return _currentVgimgPath;
		}

		static bool resetScene();
		static bool publishScene( const String& publish_vg_path, const String& publish_UI_path );
		static bool publishScene();

		
		static void saveProject( const String& projpath , 
			const String& projname);


		// 用于切块保存
		static void saveCutSceneFile();

		static void setCutSceneBeginState();

	private:
		static bool         _sceneOpened;
		static String       _currentScenePath;  // 当前场景的路径,注意以/结尾.
		static String		_currentVgPath;
		static String		_currentVgimgPath;

		static unsigned int _uiUpdateTime;
		
		static String apptitle;
		static String dllnames;
		static String dllpath;

		static bool   _isCutBlock;  // 是否开始了切块

		// Animation Menu
	public:
		static bool    importMs3dFile();       //骨骼动画
		
		//static bool	invalidatePluginConfig( const String& vg_filepath);
		//static bool	resetPluginConfig();
		static bool	invalidateUserConfig( const String& vg_filepath );
	};

}//namespace vgGlobal

#endif//__VGSCENEFILEUTILITY_H__
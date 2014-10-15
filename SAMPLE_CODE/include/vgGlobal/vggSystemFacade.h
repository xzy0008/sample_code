


#ifndef __VGGSYSTEMFACADE_H__
#define __VGGSYSTEMFACADE_H__
#include <vgGlobal/vgglDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkRenderer.h>

#if 0	
namespace vgGlobal {

	/**
		@date 	2009/01/03  20:04	
		@author  xy
	
		@brief 	
	
		@see    
	*/
	class  VGGL_EXPORT SystemFacade
	{
	private:
		SystemFacade()
		{
			
		}
	public:
		~SystemFacade()
		{
			
		}

		// Part 1: File i/o
	public:

		static bool getSceneOpenedFlag();

		static bool resetScene();

		static bool saveScene( const String& save_vg_path );

		static bool openSceneFile( const String& vg_filepath );

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


		// Part 2: Others  已转移到vgGlobal::EditUtility类中  2009/10/28  zzy
	public:
		static bool translateRenderers( vgKernel::RendererQueue* queue ,
			const vgKernel::Vec3& trans_vec );

		static bool setSelectNodesToTransparent(bool bSet);
	
		static void searchObject();

		// Part 3: Camera  已转移至vgGlobal::CamUtility类中 2009/10/28  zzy
	public:
		static bool	importVCRAnimation( const String& file_name);
		static bool exportVCRAnimation( const String& file_name);
		static bool runVcr();
		static bool continueRunVcr();
		static bool stopRunVcr();
		static bool beginRecordingVcr();

		static bool	createViewCam();
		static bool	switchViewCam();
		static bool	positionViewCamToRenderer();

		// Part 4: Keyboard input 已转移到vgGlobal::GlobalUtility类中 2009/10/28  zzy
	public:
		static bool responseLButtonDblClk(UINT nFlags, CPoint point, CWnd* pwnd );
		static bool responseLButtonDown(UINT nFlags, CPoint point);
		static bool responseLButtonUp(UINT nFlags, CPoint point);


		// Part 5: Shape Operation  已转移到vgGlobal::GlobalUtility类中 2009/10/28  zzy
	public:
		static bool convertShpToEditState();


		// Part 6: Gis Operation  已转移至vgGlobal::GisUtility类中 2009/10/28  zzy
	public:
		static bool renderGisElements();
		static bool	measureGisPoint();
		static bool	measureGisLength();
		static bool	measureGisArea();
		static bool	measureGisVolume();
		
		static bool	updateStateGisPoint();
		static bool	updateStateGisLength();
		static bool	updateStateGisArea();

		
		// Part 7: Mod 特效 已转移到vgGlobal::EffectUtility类中 2009/10/28  zzy
	public:
		static bool convertSelectedObjectToEffectNode(int nEffectType);


	private:

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

	};
	
	
}// end of namespace vgGlobal
	
#endif

#endif // end of __VGGSYSTEMFACADE_H__
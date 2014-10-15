


#ifndef __VGTERRITORY_TTERRAINMANAGER_H__
#define __VGTERRITORY_TTERRAINMANAGER_H__


#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSingleton.h>
#include <vgTerritory/vgTerrainRenderer.h>
#include <vgTerritory/vgtUpdateObserver.h>
#include <vgKernel/vgkClassIdentify.h>

#include <vgKernel/vgkPolygon2D.h>

#include <vgTerritory/vgtProcessingDlg.h>	
#include <vgKernel/vgkRenderCommand.h>

namespace vgTerritory {

	using namespace vgKernel;

	class 		CutSurfaceAnalysis;
	class 		CutSurfaceAnalysis2;
	class 		CutSurfaceVisibility;
	class 		CutSurfaceVisibility2;
	class 		CutSurfaceLevelling;
	class 		CutArea;
	class		SurfaceLengthSurvey;			// append by FengYK @ 2009-12-23
	class		SurfaceAreaSurvey;
	/**
		@date 	2008/08/19  9:01	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGT_EXPORT TerrainManager 
		: public vgKernel::Singleton<TerrainManager> ,
		public Updater 
	{
		//VGK_CLASS_IN_DECLARE( TerrainManager )
		friend class vgKernel::Singleton<TerrainManager>;
	private:
		TerrainManager();

	public:
		~TerrainManager();

	protected:

		virtual bool initialise();

		virtual bool shutdown();
	public:

		virtual void reset(){};

		/**
			通过当前的某一点得到高程.
			use_accurate 是否采用精度最高的采样方式.这样的方式可能比较慢.
		*/
		bool getElevationByPosition( const Vec3& pos , float& out_elevation , 
			const bool& use_accurate );

		/**
			输入路径来保存vtr文件和vgi文件
		*/
		bool saveData( const String& absolute_path );

		bool hasTerrainData()
		{
			return (_terrainRenderer.isNull() == false);
		}

		bool initAfterOpenGLSetup();	
		bool uninitBeforeOpenGLDestroy();

		bool dropTerrianData();

		void render();

		TerrainGpuProgram* getGpuProgramPtr()
		{
			return _terrainGpuProgramPtr;
		}

		bool openVtrFile( const String& abs_vtr_filename );


		void setRenderFlag( const bool& enable )
		{
			_renderFlag = enable;
		}
		
		bool getRenderFlag()
		{
			if ( hasTerrainData() == false )
			{
				return false;
			}

			return _renderFlag;
		}

		void setCollisionDetectedFlag( const bool& enable )
		{
			_collisionDetectedFlag = enable;
		}

		bool getCollisionDetectedFlag()
		{
			return _collisionDetectedFlag;
		}

		void setCutSurfaceAnalysisFlag( const bool& enable );
		bool getCutSurfaceAnalysisFlag() const;

		void setCutSurfaceAnalysisFlag2( const bool& enable );
		bool getCutSurfaceAnalysisFlag2() const;

		void setCutSurfaceVisibilityFlag( const bool& enable );
		bool getCutSurfaceVisibilityFlag() const;

		void setCutSurfaceVisibilityFlag2( const bool& enable );
		bool getCutSurfaceVisibilityFlag2() const;

		void setCutSurfaceLevellingFlag( const bool& enable );
		bool getCutSurfaceLevellingFlag() const;

		void setCutAreaFlag( const bool& enable );
		bool getCutAreaFlag() const;

		void setSurfaceLengthSurvey( const bool& enable );		//@ FengYK 2009-12-23
		bool getSurfaceLengthSurvey() const;

		void setSurfaceAreaSurvey( const bool& enable );		//地形表面积测量
		bool getSurfaceAreaSurvey() const;
		// 是否开启透明渲染
		void setBlendFlag( const bool& enable );
		bool getBlendFlag() const;

		//long	writeInfoToVg(CFile &pfile);

		//long 	readInfoFromVg(CFile &pfile);

		float* getUserClipPlaneParam();


		void readProject( const String& projpath , const String& projname );

		void saveProject(const String& projpath , const String& projname );

		bool saveSelectVtrAndVgi( const String& folderpath );  // 切块保存vtr及vgi

		void setSaveMode( bool bMode )
		{
			_bSelectMode = bMode;
		}
		
		// 是否有切块多边形区域
		bool hasCutArea();

		void setVerSectionAnaFlag( const bool& enable );
		bool getVerSectionAnaFlag() const;
		void setHorSectionAnaFlag( const bool& enable );
		bool getHorSectionAnaFlag() const;

	private:

		void safeDeleteAllCutSurfaces();

		void readConfigFromXml();

		void saveConfigToXml();

		vgKernel::RenderCommand *m_pRenderCommand;

	private:

		bool _blendRenderingFlag;

		bool _collisionDetectedFlag;

		TerrainGpuProgram* _terrainGpuProgramPtr;

		bool _gpuExtensionSupported;

		// 用这个标记位是不是null来表示是否载入了地形
		TerrainRendererPtr _terrainRenderer;

		bool _renderFlag;

		CutSurfaceAnalysis* _cutSurfaceAnalysis;
		CutSurfaceAnalysis2* _cutSurfaceAnalysis2;
		CutSurfaceVisibility* _cutSurfaceVisibility;
		CutSurfaceVisibility2* _cutSurfaceVisibility2;
		CutSurfaceLevelling* _cutSurfaceLevelling;

		SurfaceLengthSurvey* _surfaceLengthSurvey;
		SurfaceAreaSurvey* _surfaceAreaSurvey;

		CutArea* _cutArea;
		
		bool     _bSelectMode;

	public:
		Vec3 m_Position;
		CutSurfaceLevelling* getLevellingClassPtr()
		{
			return _cutSurfaceLevelling;
		}

		bool flagCutSurf;
		bool flagDlgCellSize;
		float posY;

	private:
		vgtProcessingDlg *m_processingDlg;

	public:
		void showProcessingDlg(bool show);
		void setProcessingInfo(std::string info);
		void setProcessingProgress(int pos);

	};



}// end of namespace vgTerritory
	


#endif // end of __VGTERRITORY_TTERRAINMANAGER_H__

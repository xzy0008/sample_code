#pragma once



#include <vgGis/vggisDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSingleton.h>
#include <vgGis3d/vggiDataSource.h>
#include <vgKernel/vgkRendererHolder.h>
#include <vgGis3d/vggiPipeLineSelector.h> 
#include <vgGis3d/vggiPipeAnalysisSelector.h>
#include <vgGis3d/vggiSelector.h> 
#include <vgGIS3D/vggiPrerequisite.h>
#include <vgGIS3D/vggiOGRPipeLineMap.h>

using namespace std;

class OGRGeometry;

	
namespace vgGIS3D {
 
	class  VGG_EXPORT GisDataManager : public vgKernel::Singleton<GisDataManager>,
		public vgKernel::RendererHolder
	{
	private:
		friend class vgKernel::Singleton<GisDataManager>;
	private:
		GisDataManager()
			: Singleton<GisDataManager>( VGK_SIGLETON_LEFE_GISDATAMGR ) 
		{
			_filter = NULL;
			_selector = NULL;
//			_querySurface = NULL;
			_pipeLineSelector = NULL;
			_pipeAnalysisSelector = NULL;

			VGK_TRACE(_T("GisDataManager created."));
		}

	public:
		~GisDataManager()
		{
			assert( _filter  == NULL );
//			assert( _querySurface == NULL );

			if (_selector != NULL)
			{
				delete _selector;
				_selector = NULL;
			}

			if (_pipeLineSelector != NULL)
			{
				delete _pipeLineSelector;
				_pipeLineSelector = NULL;
			}

			if (_pipeAnalysisSelector != NULL)
			{
				delete _pipeAnalysisSelector;
				_pipeAnalysisSelector = NULL;
			}

			VGK_TRACE(_T("GisDataManager destroyed."));
		}

	protected:

		virtual bool initialise();
		virtual bool shutdown();



	public:
		void reset();

		virtual bool onDeleteRenderer( vgKernel::Renderer *render);

		bool initAfterOpenGLSetup();

		bool uninitBeforeOpenGLDestroy();
	
		// readonly == false 时, shp可以修改并写入.
		DataSourcePtr openShapeFile( const String& filepath  );

		//DataSourcePtr openShapeFileWithUpdateUI( const String& filepath  );

		DataSourcePtr openShapeFileSpecially( const String& filepath );

		bool importDataFromOCI(string user, string passWord, string server, string sql);
		
		bool importDataFromDxfFile(string filePath);
		//DataSourcePtr openShapeFileSpeciallyWithUpdateUI( const String& filepath );

		bool checkOpened( const String& filepath );

		void renderShapes();
		
		void clearAllDataSources();

		bool clearDataSource( const String& datasource_filepath );
		bool clearDataSourcePtr( const DataSourcePtr& psource );

		//  对layer进行geometry选择模式
		// 注意,一次只能选择一个物体
		// 故只在这里留接口
		// layer中的setEditMode不对外开放
		bool setSelectMode( vgKernel::Renderer* selected_layer , const bool& enable );

		bool getSelectFlag() const
		{
			return _selector != NULL ;
		}

		bool getPipeLineSelectFlag() const
		{
			return _pipeLineSelector != NULL ;
		}

		bool getPipeLineAnalysisFlag() const
		{
			return _pipeAnalysisSelector != NULL ;
		}

		String readProject( const String& projpath );
		void readProjectExtra( const String& projpath );

		void saveProject(  const String& projpath );

		// 注意提供的是shp坐标. 而且,传入的geo生命期会被manager接管.
		void setShpLoadingFilterByOGRGeometry( OGRGeometry* geo )
		{
			_filter = geo;
		}

		// shrink_param是向内缩小的数值
		void setShpLoadingFilter( double  dfMinX,  
			double  dfMinY,  
			double  dfMaxX,  
			double  dfMaxY, 
			double shrink_param = 0.0 );


		// 通过路径名来得到datasource
		DataSourcePtr getDataSourceByPathName( const String& pathname );

		// 通过简短的名字来得到datasource
		DataSourcePtr getDataSourceByShortName( const String& shortname );

		Layer* getLayerByShortName( const String& shortname );

		DataSourcePtrMap* getDataSources()
		{
			return &_datasources;
		}
		
		Selector* getSelector()
		{
			return _selector;
		}

		bool constructTopMap();
	public:
		//add by KingHJ @2010.01.04
		//DataSourcePtr getShapeFileResource()
		//{
		//	return psource;
		//}


#if 1

		DataSource* openShapeFile2( const String& filepath  );

		DataSource* openShapeFileSpecially2( const String& filepath );

#endif

#if 1
		GeometryPointerVec* getSelectGeometriesFromLayer(Layer* layer);
		LayerPtrVector*		getLayersFromDataSource(DataSource* psource);
#endif

		DataSourcePtr&		getCurrentDataSource();
		bool setSelectPipeLineMode(vgKernel::Renderer* selected_pipeline, const bool& enable);
		bool setPipeLineAnalysisMode(vgKernel::Renderer* selected_pipeline, const bool& enable);		
	private:
		//DataSourcePtr psource;

		DataSourcePtrMap _datasources;

		LayerPtrVector* _queryLayers;

		Selector* _selector;		

		PipeLineSelector* _pipeLineSelector;
		PipeAnalysisSelector *_pipeAnalysisSelector;		

		//PipeLineSelector* m_pipeLineSelector;

		OGRGeometry* _filter;


	private://临时变量
		String	_keyFieldName;

		DataSourcePtr _currentDataSource;
	};
	
}// end of namespace  
	 
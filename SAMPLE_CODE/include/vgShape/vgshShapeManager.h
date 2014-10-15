




#ifndef __VGSHSHAPEMANAGER_H__
#define __VGSHSHAPEMANAGER_H__



#include <vgShape/vgshDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSingleton.h>
#include <vgShape/vgshDefinition.h>
#include <vgShape/vgshDataSource.h>
#include <vgKernel/vgkRendererHolder.h>
#include <vgShape/vgshSelector.h>
#include <vgShape/vgshQuerySurface.h>

class OGRGeometry;

	
namespace vgShape {

	/**
		@date 	2009/02/13  16:02	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGSH_EXPORT ShapeManager : public vgKernel::Singleton<ShapeManager>,
		public vgKernel::RendererHolder
	{
	private:
		friend class vgKernel::Singleton<ShapeManager>;
	private:
		ShapeManager()
			: Singleton<ShapeManager>( VGK_SINGLETON_LEFE_SHAPEMGR ) 
		{
			_filter = NULL;
			_selector = NULL;
			_querySurface = NULL;

			VGK_TRACE(_T("ShapeManager created."));
		}

	public:
		~ShapeManager()
		{
			assert( _filter  == NULL );
			assert( _querySurface == NULL );
			VGK_TRACE(_T("ShapeManager destroyed."));
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

#if 1
		/**
			@action		add
			@date 		2009/03/27  13:53	
			@author  	lss
		
			@brief 	
		
			@see    
			*/
		/*
			开始绿化率分析
		*/
		bool	setQueryRatioFlag( vgShape::QueryType qType);
		void	setQueryRatioKeyField(String fieldName);
		
		vgShape::vgshQuerySurface* getQuerySurface();
		vgShape::QueryType	getQueryType();

#endif

#if 1

		DataSource* openShapeFile2( const String& filepath  );

		DataSource* openShapeFileSpecially2( const String& filepath );

#endif

#if 1
		GeometryPointerVec* getSelectGeometriesFromLayer(Layer* layer);
		LayerPtrVector*		getLayersFromDataSource(vgShape::DataSource* psource);
#endif
		DataSourcePtr&		getCurrentDataSource();


	private:

		DataSourcePtrMap _datasources;

		Selector* _selector;
		vgShape::vgshQuerySurface* _querySurface;

		OGRGeometry* _filter;

	private://临时变量
		String	_keyFieldName;

		DataSourcePtr _currentDataSource;

	};
	
}// end of namespace vgShape
	


#endif // end of __VGSHSHAPEMANAGER_H__
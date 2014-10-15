#pragma once

#include <vgGis/vggisDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSharePtr.h>
#include <vgGis3d/vggiLayer.h>

	

class OGRDataSource;

namespace vgGIS3D {


	enum DataSourceType
	{
		DataSource_NONE,
		DataSource_SHP,
		DataSource_OCI,
		DataSource_DXF,

		DataSource_Type_Cnt
	};

	class  VGG_EXPORT DataSource
	{
	public:
		DataSource( String filepath , 
			OGRDataSource* source , LayerPtrVector* layers , DataSourceType tp, bool autoDel = false)
		{
			_sourcePath = filepath;
			_ogrDataSrouce = source;
			m_autoDelete = autoDel;

			if (tp == DataSource_SHP)
			{
				_queryLayers = NULL;
				_layers = layers;
			}

			if (tp == DataSource_OCI)
			{
				_layers = layers;
				_queryLayers = layers;
			}

			if (tp == DataSource_DXF)
			{
				_layers = layers;
				_queryLayers = layers;
			}

			_type = DataSource_NONE;

			assert( source != NULL);
		}

		~DataSource()
		{
			destroy();
		}

	public:

		String getSourcePath() const
		{
			return _sourcePath;
		}

		String getShortName() const;

		bool isValid() const
		{
			return (_ogrDataSrouce != NULL)&&( _layers != NULL ) && (
				_layers->empty() == false );
		}
	
		// 注意!并不对外开放的接口!
		// 因为renderermgr中含有对layer的拷贝
		// 所以直接这么删除会造成崩溃
		bool deleteLayer( Layer* layer );

		// 注意,通过renderermanager删除的接口
		bool deleteAllLayers();


		void renderLayers();


		LayerPtrVector* getLayerPtrVector()
		{
			return _layers;
		}

		bool dumpToShpByFilePath( const String& filepath );

		void setLayersRenderingPriority( const int& pri );

		DataSourceType getType()
		{
			return _type;
		}

		void setType(DataSourceType t)
		{
			_type = t;
		}

	private:

		void destroy();

	private:

		String _sourcePath;

		// Data Source直接可访问的Layer
		LayerPtrVector* _layers;

		// 通过Sql查询出的Layer
		LayerPtrVector* _queryLayers;

		OGRDataSource* _ogrDataSrouce;

		DataSourceType _type;

		bool m_autoDelete;
	};
	

	typedef vgKernel::SharePtr<DataSource> DataSourcePtr;
	typedef std::map<String , DataSourcePtr> DataSourcePtrMap;
	
}// end of namespace  
	

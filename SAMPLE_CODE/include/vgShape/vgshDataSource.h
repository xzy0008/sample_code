


#ifndef __VGSHDATASOURCE_H__
#define __VGSHDATASOURCE_H__



#include <vgShape/vgshDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSharePtr.h>
#include <vgShape/vgshLayer.h>

	

class OGRDataSource;

namespace vgShape {

	/**
		@date 	2009/02/16  15:54	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGSH_EXPORT DataSource
	{
	public:
		DataSource( String filepath , 
			OGRDataSource* source , LayerPtrVector* layers ,
			bool special )
		{
			_isSpecial = special;
			_filepath = filepath;
			_ogrDataSrouce = source;

			_layers = layers;

			assert( layers != NULL );
			assert( source != NULL);
		}
		~DataSource()
		{
			destroy();
		}

	public:


		bool isSpecial() const
		{
			return _isSpecial;
		}

		String getFilePath() const
		{
			return _filepath;
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

		bool saveToFilePath( const String& filepath );

		void setLayersRenderingPriority( const int& pri );

	private:

		void destroy();

	private:

		bool _isSpecial;
		String _filepath;
		LayerPtrVector* _layers;

		OGRDataSource* _ogrDataSrouce;
	};
	

	typedef vgKernel::SharePtr<DataSource> DataSourcePtr;
	typedef std::map<String , DataSourcePtr> DataSourcePtrMap;
	
}// end of namespace vgShape
	


#endif // end of __VGSHDATASOURCE_H__
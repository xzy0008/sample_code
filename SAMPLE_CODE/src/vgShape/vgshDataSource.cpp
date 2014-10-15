


#include <vgStableHeaders.h>
#include <vgShape/vgshDataSource.h>
#include <vgShape/vgshOgrUtility.h>
#include <vgKernel/vgkRendererManager.h>
#include <gdal/ogrsf_frmts.h>
#include <gdal/ogr_api.h>

#include <vgKernel/vgkStringUtility.h>

namespace vgShape {
	
	
	
	
	//----------------------------------------------------------------
	bool DataSource::deleteLayer( Layer* layer )
	{
		assert( isValid() );

#if 0
		LayerPtrVector::iterator iter = _layers->begin();
		LayerPtrVector::iterator iter_end = _layers->end();

		for ( ; iter != iter_end ; ++ iter )
		{
			LayerPtr pl = *iter;
			assert( pl.isNull() == false );

			if ( pl.getPointer() == layer )
			{
				_layers->erase( iter );
				return true;
			}
		}

		return false;
#else

		bool deleteok = false;
		LayerPtrVector::iterator iter = _layers->begin();

		while ( iter != _layers->end() )
		{
			if ( (*iter).getPointer() == layer )
			{
				iter = _layers->erase( iter );
				deleteok = true;
			}
			else
			{
				++iter;
			}
		}

		return deleteok;
#endif
	}
	//----------------------------------------------------------------
	void DataSource::renderLayers()
	{
		if ( isValid() == false )
		{
			return;
		}

		LayerPtrVector::iterator iter = _layers->begin();
		LayerPtrVector::iterator iter_end  = _layers->end();

		for ( ; iter != iter_end ; ++ iter )
		{
			(*iter)->render();
		}

		return;
	}
	//----------------------------------------------------------------
	bool DataSource::saveToFilePath( const String& filepath )
	{
		assert( _ogrDataSrouce != NULL );

		if ( _ogrDataSrouce == NULL )
		{
			return false;
		}

		//------------------------------------------
		// 开始复制
		//------------------------------------------
		const char *pszDriverName = "ESRI Shapefile";
		OGRSFDriver *poDriver = NULL;

		poDriver = OGRSFDriverRegistrar::GetRegistrar()->GetDriverByName(
			pszDriverName );

		if( poDriver == NULL )
		{
			assert(0);
			return false;
		}

		OGRDataSource *dstDatasource = NULL;

		dstDatasource = poDriver->CreateDataSource( 
			filepath.c_str(), NULL );
		if( dstDatasource == NULL )
		{
			std::ostringstream o ;
			o << "创建shp文件" << filepath << "时失败,文件已存在或者路径不正确!";

			MessageBox( NULL , o.str().c_str() , "提示" , MB_OK );
			return false;
		}

		bool saveasok = OgrUtility::copyDataSource( _ogrDataSrouce , dstDatasource );

		OGRDataSource::DestroyDataSource( dstDatasource );

		return saveasok;
	}
	//----------------------------------------------------------------
	bool DataSource::deleteAllLayers()
	{
#if 0
		if ( isValid() == false )
		{
			return false;
		}

		LayerPtrVector::iterator iter = _layers->begin();
		LayerPtrVector::iterator iter_end  = _layers->end();

		for ( ; iter != iter_end ; ++ iter )
		{
			vgKernel::RendererManager::getSingleton().deleteRenderer(
				(*iter).getPointer() );
		}

		return true;

#else
		
		if ( _layers != NULL )
		{
			while ( _layers->empty() == false )
			{
				vgKernel::RendererManager::getSingleton().deleteRenderer( 
					(*_layers->begin()).getPointer() );
			}
		}
		return true;
#endif
		
	}
	//----------------------------------------------------------------
	void DataSource::setLayersRenderingPriority( const int& pri )
	{
		if (_layers != NULL )
		{
			LayerPtrVector::iterator iter = _layers->begin();
			LayerPtrVector::iterator iter_end = _layers->end();

			for ( ; iter != iter_end ; ++ iter )
			{
				(*iter)->setRenderingPriority( pri );
			}
		}
	}
	//----------------------------------------------------------------
	String DataSource::getShortName() const
	{
		return vgKernel::StringUtility::getFilenameFromAbsolutePath( getFilePath() );
	}

	//----------------------------------------------------------------
	void DataSource::destroy()
	{
		//deleteAllLayers();
#if 0
		if ( _layers != NULL )
		{
			_layers->clear();
			delete _layers;
			_layers = NULL;
		}
#else
		if ( _layers!= NULL && _layers->empty() )
		{
			_layers->clear();
			delete _layers;
		}
#endif
		if ( _ogrDataSrouce != NULL )
		{
			OGRDataSource::DestroyDataSource( _ogrDataSrouce );
			_ogrDataSrouce = NULL;
		}
	}
	//----------------------------------------------------------------


}// end of namespace vgShape

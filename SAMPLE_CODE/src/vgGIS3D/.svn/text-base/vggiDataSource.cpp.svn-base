


#include <vgStableHeaders.h>
#include <vgGis3d/vggiDataSource.h>
#include <vgGis3d/vggiOgrUtility.h>
#include <vgKernel/vgkRendererManager.h>
#include <gdal/ogrsf_frmts.h>
#include <gdal/ogr_api.h>

#include <vgKernel/vgkStringUtility.h>

namespace vgGIS3D {
	
	
	
	
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
		
		if ( _queryLayers != NULL )
		{
			iter = _queryLayers->begin();

			while ( iter != _queryLayers->end() )
			{
				if ( (*iter).getPointer() == layer )
				{
					_ogrDataSrouce->ReleaseResultSet((*iter)->getOGRLayer());

					iter = _queryLayers->erase( iter );
					deleteok = true;
				}
				else
				{
					++iter;
				}
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
	bool DataSource::dumpToShpByFilePath( const String& filepath )
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
		return vgKernel::StringUtility::getFilenameFromAbsolutePath( getSourcePath() );
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
		if ( _layers->empty() )
		{
			_layers->clear();
			delete _layers;
		}
#endif

		// _queryLayers 要在之后删除，因为_layers里面有_queryLayers的副本
		if (_queryLayers != NULL)
		{
			for (int i=0; i<_queryLayers->size(); i++)
			{
				_ogrDataSrouce->ReleaseResultSet(_queryLayers->at(i)->getOGRLayer());
			}

			_queryLayers->clear();
			delete _queryLayers;
		}

		if ( _ogrDataSrouce != NULL && !m_autoDelete)
		{
			OGRDataSource::DestroyDataSource( _ogrDataSrouce );
			_ogrDataSrouce = NULL;
		}
	}
	//----------------------------------------------------------------


}// end of namespace  
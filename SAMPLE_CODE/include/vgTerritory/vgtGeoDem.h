


#ifndef __VGTGEODEM_H__
#define __VGTGEODEM_H__

#include <vgKernel/vgkForward.h>
#include <vgTerritory/vgtGeoDemOverview.h>
#include <vgTerritory/vgtGeoGlobalData.h>
#include <vgTerritory/vgTerrainHugeImageUtil.h>
#include <vgTerritory/vgtGdalDataSetGuide.h>
#include <gdal/gdal_priv.h>
#include <gdal/ogr_spatialref.h>

#include <vgTerritory/vgtHugeProcessHugeJobs.h>
	
namespace vgTerritory {

	class GeoDemManager;


	const float FOOT_TO_METRE = 0.3048006096012f;




	/**
		@date 	2008/09/19  14:18	
		@author  leven
	
		@brief 	注意,这里dem数据的坐标是在xy平面,高度值是z
	
		@see    
	*/
	class GeoDem
	{
		friend class GeoDemManager;
	public:
		GeoDem( String filepath , GeoGlobalData* global_data );
		~GeoDem();
	
	public:

		bool doOpen();
	
		String getFilePath() const;
	
		String getImageFilePath() const
		{
			return _imagePath;
		}

		String getDebugImageFilePath() const 
		{
			return _debugImgPath;
		}

		void clearOverview()
		{
			if ( _overview != NULL )
			{
				delete _overview;
				_overview = NULL;
			}
		}

		bool readGlobalInfo( const bool& unload_gdal_dataset );

		void updateGlobalInfo();

		bool isValid() const
		{
			return _isValid;
		}

	
		String getDetails();


		GeoDemOverview* getOverview()
		{
			assert( _hasReadOverview == true );
			assert( _overview != NULL );
			assert( _overview->isEmpty() == false );
			return _overview;
		}

		/**
			留给GeoDemManager使用.
		*/
		fileBlock* saveToImage();

		fileBlock* saveToDebugImage();

	private:

		void getGDALDataSet();
		//void safeDeleteGDALDataSet();


		bool readDemDataAndUpdate();

		bool readMinAndMaxElevation();
		bool readOverview();



		static int GDALInfoReportCorner( GDALDatasetH hDataset, 
			OGRCoordinateTransformationH hTransform,
			const char * corner_name,
			double x, double y , std::ostringstream& o );

		bool getStatistics( GDALRasterBand* poBand , 
			double *pdfMin, double *pdfMax );

		/**
			注意,这里产生的overview要在updateGlobalInfo之后,
			因为它的rect要在updateGlobalInfo之后更新才可以产生.
			要注意这一点!!
		*/
		GeoDemOverview* generateOverview();

	private:

		bool _hasReadMinAndMaxElevation;
		bool _hasReadOverview;

		/**
			绝对路径 
		*/
		String _filePath;
	
		bool _isValid;
	
		GDALDataset* _gdalDataSet;

		double _noDataValue;

		/**
			长宽,整形.
		*/
		long _sizeX;
		long _sizeY;

		/**
			原点坐标,以左上角为基准
		*/
		double _upperLeftX;
		double _upperLeftY;

		/**
			最大点的坐标, 和原点坐标对应
		*/
		double _lowerRightX;
		double _lowerRightY;

		/**
			Pixel Size
		*/
		double _pixelSizeX;
		double _pixelSizeY;

		/**
			最大最小高度值,注意,这里和GlobalData的值应该不一样.
		*/
		double _maxElevation;
		double _minElevation;



		/**
			连同feet到metre的系数也计算在内.
		*/
		float _zScale;
		float _zOffset;

		/**
			原始rect,左上角是原点位置
		*/
		vgKernel::ImageRect _rawRect;

		/**
			当前在世界中的位置.
			注意,需要GeoDemManager来设置GlobalData后updateGlobalInfo更新.
		*/
		vgKernel::ImageRect _worldRect;

		GeoGlobalData* _globalData;

		GeoDemOverview* _overview;

		/**
			存储为Image之后的信息,RGBA分别存储一个float高程数据
		*/

		String _imagePath;

		/**
			存储用于debug版本的image,这个可以肉眼看到的.
		*/
		String _debugImgPath;

	};
	
	class GeoDemSaveImgJob : public HugeProcess::PieceJob
	{
	public:
		GeoDemSaveImgJob( HugeProcess::HugeJobs* boss , 
			GeoDem* dem , CriticalSection* aimsect , ProcessNotifier* notifier ,
			fileBlockVector* aimsave )
			: PieceJob( boss )
		{
			_dem = dem;
			_fileBlockVec = aimsave;
			_notifier = notifier;
			_sect = aimsect;
		}
		~GeoDemSaveImgJob()
		{
			
		}


		virtual void doJob();

	private:

		fileBlockVector* _fileBlockVec;
		GeoDem* _dem;

		ProcessNotifier* _notifier;


		CriticalSection* _sect;
	
	};

	/**
		以文件名为索引
	*/
	typedef std::map<String, GeoDem* > GeoDemMap;

	typedef std::pair< GeoDemMap::iterator , bool > GeoDemMapInsertRes;
	
}// end of namespace vgTerritory
	


#endif // end of __VGTGEODEM_H__
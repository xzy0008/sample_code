


#ifndef __VGTGEOIMAGE_H__
#define __VGTGEOIMAGE_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkImageRect.h>
#include <vgTerritory/vgtGeoGlobalData.h>
#include <vgTerritory/vgtGeoImageOverview.h>
#include <vgTerritory/vgTerrainHugeImageProcessor.h>
#include <gdal/gdal_priv.h>
#include <gdal/ogr_spatialref.h>
#include <vgTerritory/vgtGeoDoubleRect.h>
#include <vgTerritory/vgtGeoImageFileBlock.h>

#include <vgTerritory/vgtHugeProcessHugeJobs.h>

	
namespace vgTerritory {




	/**
		@date 	2008/09/26  21:17	
		@author  leven
	
		@brief 	Tiff最原始图像的封装类
	
		@see    
	*/
	class GeoImage
	{
		friend class GeoDemManager;

	public:
		GeoImage( String filepath , GeoGlobalData* global_data  );
		~GeoImage();
	
	public:

		bool doOpen();

		String getFilePath() const;


		bool isValid() const
		{
			return _isValid;
		}

		String getDetails();


		GeoImageFileBlockVecPtr cutToFileBlocks( GeoDoubleRectVec* input_rects );

	private:

		void getGDALDataSet();

		bool testIntersect( const GeoDoubleRect& rect )
		{
			GeoDoubleRect tmp( _globalData );
			tmp.setRectData( _upperLeftX ,  _upperLeftY ,
				_lowerRightX , _lowerRightY );

			return tmp.testIntersect( rect );
		}


		bool readFileAndCheckValid();

		bool readDataAndUpdate();

		static int GDALInfoReportCorner( GDALDatasetH hDataset, 
			OGRCoordinateTransformationH hTransform,
			const char * corner_name,
			double x, double y , std::ostringstream& o );


		GeoImageFileBlock* rectResize( 
			const GeoDoubleRect& cut_rect );

	private:

		/**
			绝对路径 
		*/
		String _filePath;
	
		bool _isValid;
	
		GDALDataset* _gdalDataSet;
	
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
			原始rect,左上角是原点位置
		*/
		vgKernel::ImageRect _rawRect;


		GeoGlobalData* _globalData;


		//GeoImageOverview* _overview;
	};
	


	class GeoImageCutFileJob : public HugeProcess::PieceJob
	{
	public:
		GeoImageCutFileJob( HugeProcess::HugeJobs* boss , 
			GeoImage* geoimg , 
			std::vector<GeoDoubleRect>* doublerect ,
			GeoImageFileBlockVec* aimvec , 
			CriticalSection* aimsect , ProcessNotifier* notifier )
			: PieceJob( boss )
		{
			_geoImg = geoimg;
			_geoImgVec = aimvec;
			_notifier = notifier;
			_sect = aimsect;
			_doubleRect = doublerect;
		}
		virtual ~GeoImageCutFileJob()
		{
			
		}
	

		virtual void doJob();
		
	private:

		std::vector<GeoDoubleRect>* _doubleRect;
		GeoImage* _geoImg;
		ProcessNotifier* _notifier;
		GeoImageFileBlockVec* _geoImgVec;
		CriticalSection* _sect;


	};



	
	/**
		以文件名为索引
	*/
	typedef std::map<String, GeoImage* > GeoImageMap;

	typedef std::pair< GeoImageMap::iterator , bool > GeoImageMapInsertRes;



}// end of namespace vgTerritory
	


#endif // end of __VGTGEOIMAGE_H__
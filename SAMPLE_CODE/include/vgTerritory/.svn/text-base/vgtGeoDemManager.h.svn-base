


#ifndef __VGTGEODEMMANAGER_H__
#define __VGTGEODEMMANAGER_H__

#include <vgKernel/vgkForward.h>
#include <vgTerritory/vgtGeoDem.h>
#include <vgTerritory/vgtGeoGlobalData.h>
#include <vgKernel/vgkSingleton.h>
#include <vgKernel/vgkProcessObserver.h>
#include <vgTerritory/vgtGeoBlock.h>
#include <vgTerritory/vgtGeoImage.h>
#include <vgTerritory/vgtGeoImageBlock.h>


	
namespace vgTerritory {


	/**
		定义生命周期,因为不依赖于核心库,所以定义在这里.
	*/
	#define VGT_SINGLETON_LEFE_GEODEMMGR		-1624


	/**
		@date 	2008/09/19  14:18	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class GeoDemManager : public vgKernel::Singleton<GeoDemManager> ,
		public vgKernel::ProcessNotifier
	{
		friend class vgKernel::Singleton<GeoDemManager>;
	private:
		GeoDemManager();

		~GeoDemManager();

	protected:

		virtual bool initialise();

		virtual bool shutdown();

	public:


		bool clearTempData();

		void clearData();

		bool addGeoDemAndCheckValid( const vgKernel::StringVectorPtr pdems );

		bool addGeoImages( const vgKernel::StringVectorPtr pimgs );

		// 得到image的列表.用于UI界面overview
		// 当globaldata没有显示的时候,返回为空
		StringVector getOverviewGeoImageFileNames();

		void logGeoDemsDetails();

		GeoGlobalData* getGlobalDataPtr()
		{
			return &_globalData;
		}

		GeoDemMap* getGeoDemMap()
		{
			return &_dems;
		}

		void clearOverviews();

		void setOverviewFlag( const bool& gen_elevation ,
			const bool& gen_image )
		{
			_globalData._genElevationOverview = gen_elevation;
			_globalData._genImageOverview = gen_image;
		}


		void setGlobalData( const String& terrainname , 
			const String& temp_path , const String& output_path ,
			const long& n ,
			const float& cellsize ,
			const long& cellTexSize ,
			const bool& clearTempData , 
			const bool& genDebugImages ,
			unsigned char* filled_color );

		/**
			得到temp路径,然后把数据保存到bmp,方便切块处理.
		*/
		bool saveDemToImages();

		// 测试. 需要在saveToImages之后即更新了GlobalData之后
		bool saveToDebugImages();


		//////////////////////////////////////////////////////////////////////////
		// 将正摄影像分块保存
		bool saveOrthoToImages();
		//////////////////////////////////////////////////////////////////////////

		bool saveVgtrLayers();
		bool saveDebugLayers();
		bool saveImageLayers();

		void generateDemLayerImpl(  const long layernum, 
			const StringVectorPtr vgtrlist , const StringVectorPtr debugimagelist );

		void generateDebugLayerImpl(  const long layernum, 
			const StringVectorPtr vgtrlist );

		void generateImageLayerImpl(  const long layernum, 
			const StringVectorPtr vgtrlist );

		// 取得需要创建的layer总数.
		// 如果返回-1,表示出现严重错误
		long getLayerNum();

		/**
		更新_dems,包括最原始原点,GeoDem的absoluteRect 
		*/
		void updateGeoDemsFirst();

		// 更新dems，包括最低点最高点
		void updateGeoDemsSecond();


	private:

		void setDefault();

		/**
			一旦加入,Image的生命周期由GeoDemManager掌控 
		*/
		bool addGeoImageAndCheckValid( GeoImage* img )
		{
			GeoImageMapInsertRes result = _images.insert( 
				std::make_pair( img->getFilePath() , img ) ); 

			return result.second;
		}

		/**
		一旦加入,dem的生命周期由GeoDemManager掌控 
		*/
		bool addGeoDemAndCheckValid( GeoDem* dem )
		{
			GeoDemMapInsertRes result = _dems.insert( 
				std::make_pair( dem->getFilePath() , dem ) ); 

			return result.second;
		}



		/**
			检查dems的正确性,比如cellsize是否不一致等等.
		*/
		bool checkDemsValid();

		fileBlockVectorPtr getOriginFileBlocks();
		fileBlockVectorPtr getDebugOriginFileBlocks();
		fileBlockVectorPtr getGeoImageFileBlocks();


		bool resizeOriginImages();
		bool resizeDebugOriginImages();
		// 用于GeoImageBlock
		bool resizeOriginGeoImages();

		static void CPL_STDCALL gdalErrorHandler(CPLErr eErrClass, int err_no, const char *msg);

	private:


		GeoGlobalData _globalData;
		
		// 最最原始的dem数据
		GeoDemMap _dems;

		// 切块1024之后的dem数据
		GeoBlockPtrVec* _originGeoBlocks;

		GeoBlockPtrVec* _debugOrginGeoBlocks;

		// 最最原始的image数据
		GeoImageMap _images;

		// 切块1024之后的Image数据.
		GeoImageBlockPtrVec* _originalImageBlocks;

	};


	
	
}// end of namespace vgTerritory
	


#endif // end of __VGTGEODEMMANAGER_H__
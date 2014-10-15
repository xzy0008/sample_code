




#ifndef __VGTGEOGLOBALDATA_H__
#define __VGTGEOGLOBALDATA_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSystemUtility.h>
#include <vgKernel/vgkImageRect.h>
#include <vgTerritory/vgVgtrFile.h>
#include <vgTerritory/vgtDefinition.h>
#include <vgThreads/CriticalSection.h>
#include <vgThreads/ScopedLock.h>

	
namespace vgTerritory {


	using namespace vgKernel;
	using namespace vgThreads;



	/**
		@date 	2008/09/22  14:29	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class GeoGlobalData
	{
	public:
		GeoGlobalData();
		~GeoGlobalData()
		{
			
		}
	public:

		bool isValid() const;

		void setValid( const bool& isvalid )
		{
			_isUpdated = isvalid;
		}

		String getDetails();

		void pushNeedToCleanFile( const String& filename );
		void pushNeedToCleanFile( const vgKernel::StringVectorPtr namelist );

		void cleanTempFiles();

		VgtrHeaderPtr getVgtrHeaderPtr();


	public:

		// 注意,当生成完成后,这个标志置false
		bool _genDebugImages;

		bool _genElevationOverview;
		bool _genImageOverview;

		bool _clearTempData;

		/**
			坐标轴是否在左下角.
			若为true,表示在左下角.此时_globalUpperLeftY > _globalLowerRightY
			若为false,表示在左上角,此时_globalUpperLeftY < _globalLowerRightY
		*/
		bool _axisLeftDown;


		double _globalUpperLeftX;
		double _globalUpperLeftY;

		double _globalLowerRightX;
		double _globalLowerRightY;

		double _globalPixelSizeX;
		double _globalPixelSizeY;

		// 注意,最小的高度值最后会当成逻辑原点的高程offset
		double _globalMinElevation;
		double _globalMaxElevation;

		// 要送如GPU的scale值. 
		float	 _globalElevationScale;

		// minPos应该为(0,0)
		ImageRect _globalRect;

		// 经过2的n次方取整后的rect
		ImageRect _globalAdjustRect;

		// 全局保存tga时的临时目录
		String _globalTempPath;

		// 全局输出目录
		String _globalOutputPath;

		/**
			一般为N=8时,256
		*/
		long _globalChunkSize;
		long _globalN;
		
		// 当为经纬度坐标时,这个值需要手动设置
		float _globalAdjustCellsize;


		String _terrainName;

		// 纹理和网格的对应关系
		long _globalCellTexSize;

		// 这里都是计算好的绝对路径
		String _demDirectory;
		String _debugImageDirectory;
		String _imageDirectory;


		long _maxLayerNum;

		uchar _filledColor[4];

		uchar _filledBlackColor[4];

	private:

		CriticalSection _sect;

		vgKernel::StringVector _needToCleanFiles;

		bool _isUpdated;
	};
	
	
}// end of namespace vgTerritory
	


#endif // end of __VGTGEOGLOBALDATA_H__
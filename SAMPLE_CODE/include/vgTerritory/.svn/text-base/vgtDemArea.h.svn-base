



#ifndef __VGTERRITORY_TDEMAREA_H__
#define __VGTERRITORY_TDEMAREA_H__

#include <vgKernel/vgkForward.h>
#include <vgImage/vgiCximageWrapper.h>
#include <vgTerritory/vgtDemHeader.h>
#include <vgKernel/vgkImageRect.h>
#include <vgKernel/vgkStringVector.h>
	
namespace vgTerritory {

	using namespace vgKernel;
	using namespace vgImage;

	/**
		@date 	2008/08/26  19:24	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class DemArea
	{
	public:
		DemArea( String dempath , String imgpath );
		~DemArea();

		bool readFileAndCheckValid();

		void setAbsoluteRect( 
			const double& originx ,const double& originz );


		/**
			得到网格点和img的缩放比例.
			比如:500*500对应1000*1000的img,则缩放比例应该为10
		*/
		long getScaleOfDemToImage();


		bool resizeImg( const long& scale_dem_to_img , 
			const String& temp_folder );


		/**
			执行此函数一次,resize图像到1/4的大小,即长宽缩短一半.
		*/
		bool resizeImageForLod( const String& absolute_temp_folder );

		void clearTempFile();

	public:

		StringVector _tempFiles;

		String _demPath;
		String _imagePath;

		DemHeader* _demHeader;

		CximageWrapperPtr _img;


		// 通过设置最原始的坐标之后才计算出来
		ImageRect _absDemRect;

		ImageRect _absImgRect;

	};
	
	typedef vgKernel::SharePtr<DemArea> DemAreaPtr;

	typedef std::vector<DemAreaPtr> DemAreaPtrVec;
	
}// end of namespace vgTerritory
	


#endif // end of __VGTERRITORY_TDEMAREA_H__
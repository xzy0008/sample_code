


#ifndef __VGTERRITORY_TDEMAREABAG_H__
#define __VGTERRITORY_TDEMAREABAG_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSharePtr.h>
#include <vgTerritory/vgtDemArea.h>
#include <vgkernel/vgkStringPairVector.h>
#include <vgTerritory/vgTerrainHugeImageUtil.h>
#include <vgKernel/vgkProcessObserver.h>

	
namespace vgTerritory {


	using namespace vgKernel;


	

	/**
		@date 	2008/08/26  16:53	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class DemAreaBag : public vgKernel::ProcessNotifier
	{
	public:
		DemAreaBag();
		virtual ~DemAreaBag();
	

		bool readFromFilePairs( const StringPairVector& inputlist );
	

		/**
			layer参数指代层级.
			layer == 0 时,是返回最精细的一层
		*/
		fileBlockVectorPtr getFileBlockVec();

		bool isNeedToResizeImg();

		long getScaleOfDemToImg()
		{
			return _scaleOfDemToImg;
		}

		bool resizeImages( const long& new_scale , 
			const String& absolute_temp_folder );

		/**
			执行此函数一次,resize图像到1/4的大小,即长宽缩短一半.
		*/
		bool resizeImageForLod( const String& absolute_temp_folder );

		/**
			这里为什么导入ddsfilenames的列表?因为某些对应的区块没有数据
			从dds列表可以剔除这些区块
		*/
		bool saveToVtr( const vgKernel::StringVectorPtr ddsfilenames ,
			const String& terrain_name ,
			const String& absolute_output_filepath , const long& N );

		void clearTempFiles();

		/**
			 用来计算所需要的层级的函数.
			 返回的是所有dem rect的总和,并且满足2的n次方
			 此值和vgtr中的width一样.
		*/
		long getDemWidth();

	private:
	

		DemAreaPtrVec* _dems;

		double _absOriginX;
		double _absOriginZ;
		float _cellsize;
		long _scaleOfDemToImg;
		
		vgKernel::StringVectorPtr _needToClearList;
	};

	typedef vgKernel::SharePtr<DemAreaBag> DemAreaBagPtr;
	
	
}// end of namespace vgTerritory
	


#endif // end of __VGTERRITORY_TDEMAREABAG_H__
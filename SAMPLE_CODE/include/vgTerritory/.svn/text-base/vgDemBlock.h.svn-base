


#ifndef __VGTERRITORY_DEMBLOCK_H__
#define __VGTERRITORY_DEMBLOCK_H__


#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSharePtr.h>
#include <vgKernel/vgkImageRect.h>


namespace vgTerritory {


	/**
		@date 	2008/04/01  9:34	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGT_EXPORT DemBlock
	{
	public:
		DemBlock();
		~DemBlock();

		void destroy();

		void setData( const String& filename,  const uint& x_num , 
			const uint& y_num , const double& xllcorner , 
			const double& yllcorner, const double& origin_y,
			const double& top_y , const float& cell , float* data );

		String getDetails();

	public:

		uint _xNum;
		uint _zNum;

		float* _zData;

		double _originX;
		double _originZ;

		// _originY为所有高程值中最低点
		double _originY;
		
		// _topY为所有高程值中最高点
		double _topY;

		float _cellSize;

		String _demFilename;

		//------------------------------------------
		// 用于dem的处理,注意,为临时变量
		//------------------------------------------
		vgKernel::ImageRect _imgRect;

	};

	typedef vgKernel::SharePtr<DemBlock> DemBlockPtr;

	typedef std::vector<DemBlockPtr> DemBlockVector;
	typedef vgKernel::SharePtr<DemBlockVector> DemBlockVectorPtr;

	
	
	
}// end of namespace vgTerritory

#endif // end of __VGTERRITORY_DEMBLOCK_H__
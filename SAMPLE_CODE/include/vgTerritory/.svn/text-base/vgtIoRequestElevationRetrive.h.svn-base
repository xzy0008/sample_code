




#ifndef __VGTIOREQUESTELEVATIONRETRIVE_H__
#define __VGTIOREQUESTELEVATIONRETRIVE_H__


#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgAsyn/vgaIoRequest.h>
#include <vgTerritory/vgtElevationManager.h>

namespace vgTerritory {

	/**
		@date 	2008/09/08  9:24	
		@author  leven

		@brief 	通过某点查询当前的高程,同步模式
		注意,读取的是一次性的数据,四个高程,分别在起始端和末尾

		@see    
	*/
	class  VGT_EXPORT IoRequestElevationRetrive : public vgAsyn::IoRequest
	{
	public:
		IoRequestElevationRetrive( vgAsyn::FileInfo* fileinfo , 
			float scaleY );
		virtual ~IoRequestElevationRetrive()
		{

		}

		virtual bool anotherThreadHandler();

		virtual bool mainThreadHandler();


		/**
			得到的不是0-1的值, 是相乘过高层scale之后的实际值.
		*/
		float* getElevation()
		{
			return _elevation;
		}

	private:


		float _elevation[4];

		float _scaleY;

	};


}// end of namespace vgTerritory




#endif // end of __VGTIOREQUESTELEVATIONRETRIVE_H__
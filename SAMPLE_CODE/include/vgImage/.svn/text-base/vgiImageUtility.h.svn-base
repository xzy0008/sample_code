




#ifndef __VGIIMAGEUTILITY_H__
#define __VGIIMAGEUTILITY_H__
#include <vgImage/vgiDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkImagePos.h>
#include <vgKernel/vgkVec2.h>
	

namespace vgImage{

	/**
		@date 	2008/08/02  10:01	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGI_EXPORT ImageUtility
	{
	private:
		ImageUtility()
		{
			
		}
		~ImageUtility()
		{
			
		}
	
	public:

		/// 得到mipmap的最大可能值.
		static uint getMaxMipmapNum(const uint& width,const uint& height);

		static long getDdsImageStorageRequirements( const long& width ,
			const long& height , const GLenum& dds_format , 
			const bool& calculate_mipmap );

		// 计算了mipmap的dds整个文件的大小.
		static long getDdsFileStorage( const long& width , const long& height , 
			const GLenum& dds_format );


		static int getNearestPowerOfTwoNumber( const int& inputNum );

		static int getBiggerPowerOfTwoNumber( const int& inputNum );

		static int getSmallerPowerOfTwoNumber( const int& inputNum );


		// 检验高度和宽度是否是2的n次方.
		static bool checkImageSizeIsPowerOfTwo(const long& width,const long& height);

		static String findImageFileExtension( const String& filename );

		static String findFilenameFromAbsolutePath( const String& abs_path );


		static inline vgKernel::ImagePos getMaximalPos(
			const vgKernel::ImagePos& p1 , const vgKernel::ImagePos& p2 )
		{
			long m1 = p1.x > p2.x ? p1.x : p2.x ;
			long m2 = p1.y > p2.y ? p1.y : p2.y ;
			return vgKernel::ImagePos( m1 , m2 );
		}

		static inline vgKernel::ImagePos getMinimalPos(
			const vgKernel::ImagePos& p1 , const vgKernel::ImagePos& p2 )
		{
			long m1 = p1.x < p2.x ? p1.x : p2.x ;
			long m2 = p1.y < p2.y ? p1.y : p2.y ;
			return vgKernel::ImagePos( m1 , m2 );
		}

		static inline vgKernel::Vec2 getVector2FromImagePos( 
			const vgKernel::ImagePos& pos , const float& ratio )
		{
			return vgKernel::Vec2( (float)pos.x * ratio , (float)pos.y * ratio );
		}

		/**
			检查dds文件是否为空
			返回值表明了是否为空.
			真正的是否为空在out_isEmpty输出中.
		*/
		static bool checkDdsImageIsEmpty( const String& dds_abs_filepath,
			bool& out_isEmpty );
	
 

		static long getDdsImageStorage( const long& width ,
			const long& height , const GLenum& dds_format );

	};
	
	

}// end of namespace vgImage



#endif // end of __VGIIMAGEUTILITY_H__




#ifndef __VGIFREEIMAGEWRAPPER_H__
#define __VGIFREEIMAGEWRAPPER_H__


#include <vgImage/vgiDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSharePtr.h>
#include <vgKernel/vgkImageRect.h>


#include <FreeImage.h>
#include <FreeImagePlus.h>

	
namespace vgImage {

	/**
		@date 	2009/05/03  14:32	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class VGI_EXPORT FreeImageWrapper : public fipWinImage
	{
	public:

		enum  DdsFormat
		{
			DDS_FORMAT_DXT1		= 1,
			DDS_FORMAT_DXT3		= 2,
			DDS_FORMAT_DXT5		= 3,
		};

	public:
		FreeImageWrapper()
			: fipWinImage()
		{
			
		}
		~FreeImageWrapper()
		{
			
		}
	
	public:


		inline void release()
		{
			clear();
		}


		bool createFromSize( long dwWidth, long dwHeight , long dBpp = 32 );

		// 将图像全部重置为这种颜色.
		// 注意,包含alpha通道.
		void clearColor( const RGBQUAD& color );
		void clearColor( uchar color_r , uchar color_g , uchar color_b , uchar color_a );


		bool resize( const vgKernel::ImageSize& imgSize );

		/**
			返回重新设置图像大小后的拷贝.
		*/
		FreeImageWrapper*  resizeCopy( const vgKernel::ImageSize& imgSize ) const;

		// 与本身的load不同的是, 在这里可以做优化
		// 一般是将数据全部读入内存,在内存中解压
		bool loadFromFile( const String& filepath, int flag = 0 );

		// 同样,这个也有优化
		// 注意,这个是同步过程,若保存失败,将重试保存
		bool saveToFile( const String& save_path ,int flag = 0 );

		
		// 注意此时的坐标
		// axis_left_down为true时,第一行在下面
		// axis_left_down为false时,第一行在上面
		// 若需要flipY,使用flipVertical()
		// 若需要Red和Blue相转换, 请使用swapRedAndBlueChannel()
		bool createFromArray( void* buf, long dwWidth, 
			long dwHeight , long dBpp = 24 , bool axis_left_up = true );

		
		bool swapRedAndBlueChannel();

		/**
			dds文件存储
		*/
		bool	saveToDdsFile( const String& file_abs_path ,
			const DdsFormat& dformat , 
			const bool& auto_resize_to_two_power = false );

		bool	saveToDdsFile( const String& file_abs_path ,
			const GLenum& dds_format , 
			const bool& auto_resize_to_two_power = false );

		// 得到连续的RGBA或者RGB格式
		// 与accessAlignedPixels不同的是,一般返回的不是NULL
		BYTE* getAlignedPixelsCopy();

		// 直接访问连续的RGBA或者RGB格式，如果不是此格式或者没有对齐，返回NULL
		BYTE* accessAlignedPixels();


		/**
			切割图像.
				
			@note	一般执行的图像的缩小操作.当Rect的大小超出图像的大小时并不能保证正确.
				另外注意图像的坐标轴问题.
				
			@param	rect 切割图像的长方形表示.即在原图中所占的位置.
			@param	pDstImg 将图像存入的目的地.注意为空时,会将数据存入本身.
			@param	axisLeftTop 坐标轴是否在左上角.
		*/
		bool  crop( const vgKernel::ImageRect& rect , FreeImageWrapper* pDstImg , 
			bool axisLeftTop = true );


		/**
			将imgsrc2的图像内容叠在本图像之上.
				
			@note	本方法也有坐标轴之分.另外注意,本函数暂不支持超过图像大小的Rect.
				
			@param	imgsrc2 重叠在上层的图像.
			@param	rect 相对于底层的正方形区块.
			@param	axisLeftTop 坐标是否是左上角.
		*/
		bool overlap( FreeImageWrapper &imgsrc2, const vgKernel::ImageRect& rect ,
			bool axisLeftTop = true );

		// 以左上角为原点
		bool overlap2( FreeImageWrapper &overlapped, long left , long top);

	private:
	
		bool saveToFileImpl( const String& save_path, fipMemoryIO &alloc );
	
	};
	

	typedef vgKernel::SharePtr<FreeImageWrapper> FreeImageWrapperPtr;
	
}// end of namespace vgImage
	


#endif // end of __VGIFREEIMAGEWRAPPER_H__
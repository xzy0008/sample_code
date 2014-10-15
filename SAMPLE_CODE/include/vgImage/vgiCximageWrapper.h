


#ifndef __VGICXIMAGEWRAPPER_H__
#define __VGICXIMAGEWRAPPER_H__
#include <vgImage/vgiDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSharePtr.h>
#include <vgKernel/vgkStreamReader.h>
#include <vgKernel/vgkImageRect.h>




class CxImage;

namespace vgImage {

	using namespace vgKernel;


	class CxStreamReader;
	class CxStreamWriter;
	class CximageWrapper;

	typedef CxImage*  CximagePtr;
	typedef vgKernel::SharePtr<CximageWrapper> CximageWrapperPtr;

	/**
		@date 	2008/08/25  10:40	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class VGI_EXPORT CximageWrapper
	{
	public:

		enum  DdsFormat
		{
			DDS_FORMAT_DXT1		= 1,
			DDS_FORMAT_DXT3		= 2,
			DDS_FORMAT_DXT5		= 3,
		};

		

	private:




	public:
		
		CximageWrapper( CximagePtr cximg );
		CximageWrapper();

		~CximageWrapper();
	

	public:

		// 将图像全部重置为这种颜色.
		// 注意,包含alpha通道.
		void clearColor( const RGBQUAD& color );
		void clearColor( const uchar& color_r , 
			const uchar& color_g , 	const uchar& color_b , 	const uchar& color_a );

		bool createFromArray(  void* buf, const long& dwWidth, 
			const long& dwHeight , const long& dBpp = 24 ,bool  bFlipImage = false ,
			bool reverse_R_and_B = false );

		// 注意是大写
		bool cxCreateFromArray(BYTE* pArray,DWORD dwWidth,DWORD dwHeight,
			DWORD dwBitsperpixel, DWORD dwBytesperline, bool bFlipImage);

		bool createFromSize( const long& dwWidth, 
			const long& dwHeight , const long& dBpp = 32 );

		/**
			通过filename来判断文件格式
		*/
		bool loadHeaderFromFile( const String& file_abs_path );
		

		bool loadFromFile( const String& file_abs_path );
	
		/**
			非dds文件的存储
		*/
		bool	saveToFile( const String& output_filepath );

		/**
			dds文件存储
		*/
		bool	saveToDdsFile( const String& file_abs_path ,
			const DdsFormat& dformat , 
			const bool& auto_resize_to_two_power = false );

		// 检查是否有黑边,并且手动
		// 此函数暂时放弃不用
		bool	saveToDdsFileWithBorderCheck( const String& file_abs_path ,
			const DdsFormat& dformat , const bool& border_left_black , 
			const bool& border_up_black );

		bool	saveToDdsFile( const String& file_abs_path ,
			const GLenum& dds_format , 
			const bool& auto_resize_to_two_power = false );

		void release();

		CximagePtr getCximagePtr()
		{
			return mCximagePtr;
		}

		String getFilePath() const
		{
			return mFilePath;
		}

		long getWidth() const
		{
			return this->mWidth;
		}

		long getHeight() const
		{
			return this->mHeight;
		}

		ImageSize getImageSize() const
		{
			return ImageSize( mWidth , mHeight );
		}


		bool resize( const ImageSize& imgSize );

		/**
			返回重新设置图像大小后的拷贝.
		*/
		const CximageWrapperPtr  resizeCopy( const ImageSize& imgSize ) const;

		/**
			切割图像.
				
			@note	一般执行的图像的缩小操作.当Rect的大小超出图像的大小时并不能保证正确.
				另外注意图像的坐标轴问题.
				
			@param	rect 切割图像的长方形表示.即在原图中所占的位置.
			@param	pDstImg 将图像存入的目的地.注意为空时,会将数据存入本身.
			@param	axisLeftTop 坐标轴是否在左上角.
		*/
		bool  crop( const ImageRect& rect , CximageWrapperPtr pDstImg , 
			const bool& axisLeftTop = true );

		/**
			在图像上绘制文字信息.
				
			@note	注意,此时x偏移和y偏移都是对于坐标轴在左上角而言.
				
			@param	xoffset x偏移.
			@param	yoffset y偏移.
			@param	text 要写的文字.
			@param	font 文字的字体名称.
			@param	fontsize 文字的大小.
			@param	setAlpha 是否将其设置为透明.
		*/
		bool drawString( const long& xoffset ,
			const long& yoffset , const String& text , const String& font = "" , 
			const long& fontsize = 30 , const bool& setAlpha = false );


		/**
			将imgsrc2的图像内容叠在本图像之上.
				
			@note	本方法也有坐标轴之分.另外注意,本函数暂不支持超过图像大小的Rect.
				
			@param	imgsrc2 重叠在上层的图像.
			@param	rect 相对于底层的正方形区块.
			@param	axisLeftTop 坐标是否是左上角.
		*/
		void overlap( CximageWrapper &imgsrc2, const ImageRect& rect ,
			const bool& axisLeftTop = true );

		// 注意!!以左上角为原点!!
		void overlap2( CximageWrapper &imgsrc2, const long& xoffset , 
			const long& yoffset );


		


	private:
	

	
		void updateSelfInfoFromCximage();

		

	private:

		/// 图像的文件路径.
		String		mFilePath;

		/// 图像的长宽.
		long		mWidth;
		long		mHeight;

		/// 是否已经初始化的标志.
		bool		mInitialised;

		CximagePtr	mCximagePtr;

	};
	
	bool VGI_EXPORT getImageFormatInfo( const String& filename , 
		long& width, long& height);







}// end of namespace vgImage
	


#endif // end of __VGICXIMAGEWRAPPER_H__
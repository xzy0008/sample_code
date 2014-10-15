/*
-----------------------------------------------------------------------------
  VRES(Virtual Reality GIS Engine System)    
  -------------------------------------------------------------
  License details ... waiting to add...
  -------------------------------------------------------------
  Copyright  (C) 2007 , leven - All Rights Reserved
-----------------------------------------------------------------------------
*/

#ifndef __TVGIMAGEUTIL_H__
#define __TVGIMAGEUTIL_H__

#include <vgCore/vgPrerequisites.h>
#include <vgTex/tvgImagePos.h>
#include <vgTex/tvgImageRect.h>
#include <ximage.h>
#include <vgMath/vgfVector2.h>



namespace vgCore {


	using namespace vgMath;

	enum  ImageFormat 
	{
		IMAGE_FORMAT_UNKNOWN	= CXIMAGE_FORMAT_UNKNOWN ,
		IMAGE_FORMAT_BMP		= CXIMAGE_FORMAT_BMP ,
		IMAGE_FORMAT_JPG		= CXIMAGE_FORMAT_JPG ,
		//IMAGE_FORMAT_GIF		= CXIMAGE_FORMAT_GIF ,
		IMAGE_FORMAT_PNG		= CXIMAGE_FORMAT_PNG ,
		//IMAGE_FORMAT_ICO		= CXIMAGE_FORMAT_ICO ,
		IMAGE_FORMAT_TIF		= CXIMAGE_FORMAT_TIF ,
		IMAGE_FORMAT_TGA		= CXIMAGE_FORMAT_TGA ,
		//IMAGE_FORMAT_PCX		= CXIMAGE_FORMAT_PCX ,
		//IMAGE_FORMAT_WBMP		= CXIMAGE_FORMAT_WBMP ,
		//IMAGE_FORMAT_WMF		= CXIMAGE_FORMAT_WMF ,
		IMAGE_FORMAT_JP2		= CXIMAGE_FORMAT_JP2 ,
		//IMAGE_FORMAT_JPC		= CXIMAGE_FORMAT_JPC ,
		//IMAGE_FORMAT_PGX		= CXIMAGE_FORMAT_PGX ,
		//IMAGE_FORMAT_RAS		= CXIMAGE_FORMAT_RAS ,
		//IMAGE_FORMAT_PNM		= CXIMAGE_FORMAT_PNM ,
		IMAGE_FORMAT_DDS		= 188/// DDS 文件格式.
	};

	enum  DdsFormat
	{
		DDS_FORMAT_UNKNOWN	= 0,
		DDS_FORMAT_DXT1		= 1,
		DDS_FORMAT_DXT3		= 2,
		DDS_FORMAT_DXT5		= 3,
		DDS_FORMAT_A8R8G8B8	= 4,
		DDS_FORMAT_DEFAULT	= DDS_FORMAT_DXT3
	};

	/**
		@date 	2007/05/19  9:04	
		@author  Leven
			
		@brief 	
			 Utility for ImagePos.
			 This is just a package of static functions only.
			 目前的函数很少.以后可以扩展.比如,要对一个ImagePos做绕某点旋转操作.
			 再比如,随机产生某点等等.
		@see    
	*/
	class ImageUtility
	{
	public:

		static ImageSize getNearestPowerOfTwoNumber( const ImageSize& inputsize )
		{
			ImageSize ret;
			ret.setWidth( getNearestPowerOfTwoNumber( inputsize.getWidth() ) );
			ret.setHeight( getNearestPowerOfTwoNumber( inputsize.getHeight() ) );

			return ret;
		}

		static int getNearestPowerOfTwoNumber( const int& inputNum )
		{
			if ( inputNum == 0 || inputNum < 0 )
			{
				assert(0);
				return 0 ;
			}

			int left = inputNum;

			int aim = 1;

			do 
			{
				left /= 2;

				aim *= 2;

			} while( left != 0);


			int s = aim/2;

			int b = aim;

			return ( (b - inputNum) >= ( inputNum - s) ) ? s : b;
		}

		static int getBiggerPowerOfTwoNumber( const int& inputNum )
		{
			if ( inputNum == 0 || inputNum < 0 )
			{
				assert(0);
				return 0 ;
			}

			int left = inputNum;

			int aim = 1;

			do 
			{
				left /= 2;

				aim *= 2;

			} while( left != 0);

			return aim;
		}

		static inline ImagePos getMaximalPos( const ImagePos& p1 , const ImagePos& p2 )
		{
			Integer m1 = p1.x > p2.x ? p1.x : p2.x ;
			Integer m2 = p1.y > p2.y ? p1.y : p2.y ;
			return ImagePos( m1 , m2 );
		}

		static inline ImagePos getMinimalPos( const ImagePos& p1 , const ImagePos& p2 )
		{
			Integer m1 = p1.x < p2.x ? p1.x : p2.x ;
			Integer m2 = p1.y < p2.y ? p1.y : p2.y ;
			return ImagePos( m1 , m2 );
		}

		// 检验高度和宽度是否是2的n次方.
		static inline bool checkImageSizeIsPowerOfTwo(const uint& width,const uint& height)
		{
			unsigned int w = width;
			unsigned int h = height;
			while ( (w & 0x0001) == 0 && w != 0 )
			{
				w = w >> 1;
			}
			while ( (h & 0x0001) == 0 && h != 0 )
			{
				h = h >> 1;
			}
			if ( w == 1 && h == 1)
			{
				return true;
			}
			return false;
		}

		static inline bool checkImageSizeIsPowerOfTwo(const ImageSize& imgsize)
		{
			return checkImageSizeIsPowerOfTwo(imgsize.getWidth() ,imgsize.getHeight());
		}

		/// 得到mipmap的最大可能值.
		static inline uint getMaxMipmapNum(const uint& width,const uint& height)
		{
			assert( width != -1 && height != -1 );

			unsigned int w = width;
			unsigned int h = height;
			unsigned int result = 0;
			while ( w!=0 || h!=0 )
			{
				result++;
				w /=2;
				h /=2;
			}
			return result;
		}
		//----------------------------------------------------------------
		static inline string getStringPostfixFromNum( const Integer& num_x , const Integer& num_y ,
			const bool& reverseSequence = false )
		{
			std::ostringstream o;
			o << "_";
			if ( reverseSequence == false )
			{
				o <<  num_x << "_" << num_y << ".";
			}
			else
			{
				o <<  num_y << "_" << num_x << ".";
			}
			return o.str();
		}

		static inline Vector2 getVector2FromImagePos( const ImagePos& pos , const Real& ratio )
		{
			return Vector2( (Real)pos.x * ratio , (Real)pos.y * ratio );
		}

		//----------------------------------------------------------------
		static inline ImageFormat  findImageFormat( const String& filename )
		{
			const String& ext = findImageFileExtension( filename );
			return findImageFormatFromExt( ext );
		}
		

		/// !!!!!!!!!!!要添加caseSensity!~~!!!!!!!!!!!!!!!!!!!!!!
		static ImageFormat  findImageFormatFromExt( const String& ext );
		

		static inline String findImageFileNameWithoutExt( const String& filename )
		{
			std::string::size_type pos = filename.rfind('.');
			std::string ret = filename.substr( 0  , pos);

#if _DEBUG
			std::string::size_type ppp = ret.find_first_of("/\\");
			assert( ppp != std::string::npos );	
#endif

			return ret;	
		}

		static inline String findImageFileExtension( const String& filename )
		{
			std::string::size_type pos = filename.rfind('.');
			std::string ext = filename.substr(pos == std::string::npos ? filename.length() : pos + 1);
			transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

			ext.erase(ext.find_last_not_of(' ') + 1);
			return ext;
		}

		//----------------------------------------------------------------
		static bool getHeaderInfo(const string& filename , 
			Integer& width , Integer& height ,
			const ImageFormat& imgformat = IMAGE_FORMAT_UNKNOWN );

		//----------------------------------------------------------------
		static long getDdsImageStorageRequirements( const long& width ,
			const long& height , const DdsFormat& dds_format , 
			const bool& calculate_mipmap )
		{
			GLenum dformat = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;

			switch( dds_format )
			{
			case DDS_FORMAT_DXT1:
				{	
					dformat = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
					break;
				}
			case DDS_FORMAT_DXT3:
				{	
					dformat = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
					break;
				}
			case DDS_FORMAT_DXT5:
				{	
					dformat = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
					break;
				}
			case DDS_FORMAT_A8R8G8B8:
				{
					return 0;
					break;
				}
			default:
				{
					return 0;
				}
			}

			return getDdsImageStorageRequirements( width , height , dformat , 
				calculate_mipmap );

		}
		//----------------------------------------------------------------

		static long getDdsImageStorageRequirements( const long& width ,
			const long& height , const GLenum& dds_format , 
			const bool& calculate_mipmap );

		// 计算了mipmap的dds整个文件的大小.
		static long getDdsFileStorage( const long& width , const long& height , 
			const GLenum& dds_format );

			private:

				static long getDdsImageStorage( const long& width ,
					const long& height , const GLenum& dds_format );
	};

}

#endif // end of __TVGIMAGEUTIL_H__
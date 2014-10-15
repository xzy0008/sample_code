


#ifndef __VGIFILEWRITERVGI_H__
#define __VGIFILEWRITERVGI_H__
#include <vgImage/vgiDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkStringVector.h>
#include <vgKernel/vgkStringPairVector.h>
#include <vgTerritory/vgtFileWriterVtr.h>
	
namespace vgImage {


	/**
		@date 	2008/08/01  15:48	
		@author  leven
	
		@brief 	
	
		@see    
	*/

	/**
		注意：为了满足切块保存，选区之处的纹理像素置为背景色

		1. 根据vgtr的纹理名称生成纹理贴图,(dds-->minimap 最精细的一级)

		2. 然后从纹理中获取纹理数据(glGetTexImage),对获取的数据进行处理
		   (设置特定字节的数值)。

		3. 将处理过的纹理数据保存为dds文件

		4. 将dds 文件存储到vgi文件中 
	*/


	class  VGI_EXPORT FileWriterVgi
	{
	private:
		FileWriterVgi()
		{
			
		}
		~FileWriterVgi()
		{
			
		}
	
	public:


		/**
			用于从内部的texture name list保存到vgi文件, 注意,这里有切割
		*/
		static bool writeToVgiFileFromTextureNames(
			const vgKernel::StringVectorPtr input_texnames , 
			const String& output_filename );


		/**
			用于从内部的texture name list保存到vgi文件.此函数包含了
			纹理的rename. 注意,这里有切割.
		*/
		static bool writeToVgiFromTexNamesWithRename(
			const vgKernel::StringPairVectorPtr texnames , 
			const String& output_filename );


		/**
			add by ZhouZY 2009-1-12 19:34
			用于切块保存
		*/
		static bool writeToVgiFromTexNamesWithRename(
			const vgKernel::StringPairVectorPtr texnames , 
			const String& output_filename,
			vgTerritory::ptIndexMap* pixelIndexMap );

	private:

		/**
			用于从内部的texture name list保存到vgi文件
		*/
		static bool writeToVgiFile(
			const vgKernel::StringVectorPtr input_texnames , 
			const String& output_filename  , const long& nextfileid );

		static bool writeToVgiFileWithRename( 
			const vgKernel::StringPairVectorPtr texnames , 
			const String& output_filename  , const long& nextfileid  );


		//////////////////////////////////////////////////////////////////////////
		// 以下部分用于场景切块保存
		// add by ZhouZY 2009-1-12  19:51
		static bool dealTextureData(
			const vgKernel::StringPairVectorPtr texnames,
			vgKernel::StringVector& outVec );

		static void setBackgroundPicBuf( String ddsName );

		// glGetTexImage 从OPenGL纹理中读取数据
		static bool getTexDataFormTexture( GLuint texId, char* src_buf, int texWidth );
		
		static bool setPixelColor( char* src_buf, char* dst_buf, String ddsName, int texWidth );
		
		static String saveDataToDds( const char* dst_buf, String ddsFileName, int texWidth );


	private:
		
		// 用于索引需置为背景色的纹理像素
		static vgTerritory::ptIndexMap* s_pixelIndexMap;

		// 用于存储临时生成的dds文件目录
		static String s_tempPathDir;

	    // 如trerrain_level0_9_7.dds则terrain是其FirstName
		static String s_ddsFistName; 

		static char*  s_backgroundPicBuf;
	};
	
	
}// end of namespace vgImage
	


#endif // end of __VGIFILEWRITERVGI_H__
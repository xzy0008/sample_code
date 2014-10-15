



#ifndef __VGTGDALHELPER_H__
#define __VGTGDALHELPER_H__

#include <vgKernel/vgkForward.h>

	
namespace vgTerritory {

	/**
		@date 	2009/05/04  10:26	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class GdalHelper
	{
	public:
		GdalHelper()
		{
			
		}
		~GdalHelper()
		{
			
		}
	public:

		static String getMemName( const String& filename );

		// 创建GDAL内存文件,名字由getMemName获得
		static bool createMemFile( const String& abs_filepath );
	

		static bool createMemFileFromBuffer( 
			const String& filename , void* buffer, int buffer_size_in_bytes ,
			bool take_ownership );

		static bool deleteMemFile( const String& filename );


	};
	
	
}// end of namespace vgTerritory
	


#endif // end of __VGTGDALHELPER_H__
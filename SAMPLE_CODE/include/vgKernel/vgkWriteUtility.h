



#ifndef __VGKWRITEUTILITY_H__
#define __VGKWRITEUTILITY_H__

#include <vgKernel/vgkForward.h>

	
namespace vgKernel {

	/**
		@date 	2009/02/02  10:17	
		@author  xy
	
		@brief 	
	
		@see    
	*/
	class  VGK_EXPORT WriteUtility
	{
	private:
		WriteUtility()
		{
			
		}
	public:
		~WriteUtility()
		{
			
		}
	

	public:

		/**
			写入cfile一个字符串.
			str_length 是写入的长度,一定要大于str的长度
		*/
		static bool writeStringToCFile( CFile* cfile , const String& str , 
			const int& write_length , const bool& alert = false );
	

		/**
			
		*/
		static bool writeStringToStream( vgKernel::StreamWriterPtr pwriter , 
			const String& str, int write_length );

	};
	
	
}// end of namespace vgKernel
	

#define	VGK_CFILE_WRITESTR_ASSERT( cfile , write_string , write_length ) \
{ bool ret = vgKernel::WriteUtility::writeStringToCFile( cfile , write_string , write_length, true );\
	if( ret == false )\
	{ \
		std::ostringstream o; \
		o << "写入字符串失败: "<< write_string;\
		MessageBox( NULL , o.str().c_str() , "Write Error" , MB_OK );\
	}\
}

#define	VGK_STREAM_WRITESTR_ASSERT( stream , write_string , write_length ) \
{ bool ret = vgKernel::WriteUtility::writeStringToStream( stream , write_string , write_length );\
	if( ret == false )\
{ \
	std::ostringstream o; \
	o << "写入字符串失败: "<< write_string;\
	MessageBox( NULL , o.str().c_str() , "Write Error" , MB_OK );\
}\
}

#endif // end of __VGKWRITEUTILITY_H__
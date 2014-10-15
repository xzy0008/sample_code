


#ifndef __VGICOMPRESS_H__
#define __VGICOMPRESS_H__
#include <vgImage/vgiDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgImage/vgiImageUtility.h>
#include <nvtt/nvtt.h>
#include <vgKernel/vgkStreamWriter.h>


	
namespace vgImage {

	class NvOutputHandler;


	using namespace vgKernel;

	/**
		@date 	2008/10/10  8:24	
		@author  leven
	
		@brief 	DXT 压缩
	
		@see    
	*/
	class VGI_EXPORT Compress
	{
	private:
		Compress()
		{
			
		}
		~Compress()
		{
			
		}
	
	
	public:

		//------------------------------------------
		// 注意,下面的src格式都是BGRA格式
		//------------------------------------------

		// 压缩到dst缓冲区.没有mipmap
		static long processToBuffer( void* src , const long& width , 
			const long& height , void* dst , const GLenum& dds_format );
	
	
		static long processWholeFileToBuffer(  void* src , const long& width , 
			const long& height , void* dst , const GLenum& dds_format  );

		static long processWholeFileToStream( void* src , const long& width , 
			const long& height , StreamWriterPtr output, const GLenum& dds_format );

		static long processWholeFileToFile( void* src , const long& width , 
			const long& height , const String& outputfile , const GLenum& dds_format );
	private:

		static nvtt::Format getNvFormat( const GLenum& dds_format );

	};


	/**
		写入到内存.有自身的检查
	*/
	class NvOutputHandler : public nvtt::OutputHandler
	{
	public:
		// 通过buffer的大小构造.自身会申请内存.
		// 然后写入到这个buffer中.
		NvOutputHandler( long buffersize );

		// 通过buffer指针构造,自身不申请内存.
		// 只是检查
		NvOutputHandler( byte* buffer, long buffersize );
		~NvOutputHandler();

	public:

		/// Indicate the start of a new compressed image that's part of the final texture.
		virtual void beginImage(int size, int width, int height, int depth,
			int face, int miplevel);

		/// Output data. Compressed data is output as soon as it's generated to minimize memory allocations.
		virtual bool writeData(const void * data, int size);


		bool checkValidWhenDone()
		{
			return ( _curPointer == _buffer + _bufferSize );
		}

		byte* getBuffer()
		{
			return _buffer;
		}
		long getBufferSize() const
		{
			return _bufferSize;
		}
	private:

		void setDefault();

	private:

		bool _deleteBufFlag;

		byte* _buffer;
		long _bufferSize;

		byte* _curPointer;
	};
	
	
}// end of namespace vgImage
	


#endif // end of __VGICOMPRESS_H__
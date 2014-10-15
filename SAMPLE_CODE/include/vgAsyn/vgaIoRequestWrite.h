


#ifndef __VGAIOREQUESTWRITE_H__
#define __VGAIOREQUESTWRITE_H__
#include <vgAsyn/vgaDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgAsyn/vgaIoRequest.h>

	
namespace vgAsyn {

	/**
		@date 	2008/11/08  8:45	
		@author  leven
	
		@brief  写入文件的IoRequest.
		注意,暂时只实现了同步的版本.异步版本暂时不做考虑.
		输入的buffer会在析构的时候自动释放掉.
	
		@see    
	*/
	class VGA_EXPORT IoRequestWrite : public IoRequest
	{
	public:
		IoRequestWrite( FileInfo* fileinfo , void* buffer )
			: IoRequest( fileinfo )
		{
			_buffer = (char*)buffer;
			setAsynchronousMode( false );
		}

		virtual ~IoRequestWrite()
		{
			
		}
	
		
		void sendIoRequestWrite();

	
	private:
	
	
	};
	
	
}// end of namespace vgAsyn
	


#endif // end of __VGAIOREQUESTWRITE_H__
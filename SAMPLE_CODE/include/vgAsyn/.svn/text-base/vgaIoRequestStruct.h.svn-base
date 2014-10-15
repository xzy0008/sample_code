



#ifndef __VGAIOREQUESTSTRUCT_H__
#define __VGAIOREQUESTSTRUCT_H__
#include <vgAsyn/vgaDefinition.h>
#include <vgKernel/vgkForward.h>


namespace vgAsyn {

#pragma   warning(disable:4311)
#pragma   warning(disable:4312)


	class IoRequest;


	/**
		@date 	2008/06/21  9:40	
		@author  leven
	
		@brief 	OverLapped方式下的参数传递
			一般对外不可见
	
		@see    
	*/
	class IoRequestStruct : public OVERLAPPED
	{
	public:
		IoRequestStruct( IoRequest* request , 
			long offset , long readsize )
		{
			Internal = 0;
			InternalHigh = 0;

			Offset = offset;
			OffsetHigh = 0;

			hEvent = 0;

			_readSize = readsize;

			_request = request;
		}

		~IoRequestStruct()
		{
			if ( hEvent != 0 )
			{
				CloseHandle( hEvent );
				hEvent = 0;
			}
		}

		IoRequest* getIoRequest()
		{
			return (IoRequest*)_request;
		}

		// 查看是否是异步模式
		bool isAsynMode() const 
		{
			return hEvent == 0;
		}

		// used for IoRequest only
		void setAsynMode( const bool& asyn_mode )
		{
			if ( asyn_mode == false )
			{
				if ( hEvent == 0 )
				{
					hEvent = CreateEvent( NULL , TRUE , FALSE , NULL );
				}
				hEvent = (HANDLE)((DWORD) hEvent | 0x1 );
			}
			else
			{
				if ( hEvent != 0 )
				{
					CloseHandle( hEvent );
				}
				hEvent = 0;
			}
		}

	public:

		/**
			要读取的字节数.
			注意,这里也可用在Write File的过程中, 名称虽然不一样.
		*/
		long _readSize;

		volatile IoRequest* _request;
	};
	
	
#pragma   warning(default:4311)
#pragma   warning(default:4312)
	
}// end of namespace vgAsyn

#endif // end of __VGAIOREQUESTSTRUCT_H__
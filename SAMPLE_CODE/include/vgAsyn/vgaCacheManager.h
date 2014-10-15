



#ifndef __VGACACHEMANAGER_H__
#define __VGACACHEMANAGER_H__
#include <vgAsyn/vgaDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgAsyn/vgaCacheDefine.h>
#include <vgKernel/vgkSingleton.h>

	
namespace vgAsyn {

	class IoRequest;

	class CacheContent
	{
	public:
		CacheContent( int size , char* buf )
			: _size( size ) ,
			_content( buf )
		{
			
		}
		~CacheContent()
		{
			if ( _content != NULL )
			{
				delete[] _content;
				_content = NULL;
			}
		}

	public:

		int _size;
		char* _content;

	};

	/**
		@date 	2008/11/14  15:17	
		@author  leven
	
		@brief 	利用IoRequest获得数据，如果返回NULL，则使用默认的
		IO机制再载入。
	
		@see    
	*/
	class CacheManager : 
		public vgKernel::Singleton<CacheManager>
	{

		typedef stdext::hash_map<int, CacheContent> OffsetMap;
		typedef stdext::hash_map<int, OffsetMap> HandleCacheMap;

		friend class vgKernel::Singleton<CacheManager>;
	private:
		CacheManager();
		~CacheManager();

	protected:

		virtual bool initialise()
		{
			return true;
		}
		virtual bool shutdown()
		{
			return true;
		}

	public:
		
		// 如果不存在Cache，则返回NULL
		// 而且注意，客户端负责释放
		char* getCacheFromIoRequest( IoRequest* req );

	private:

		HandleCacheMap _handleCache;

		// 默认的缓冲区大小，这个要设置
		//int _defaultCacheSize;
	};
	
	
}// end of namespace vgAsyn
	


#endif // end of __VGACACHEMANAGER_H__
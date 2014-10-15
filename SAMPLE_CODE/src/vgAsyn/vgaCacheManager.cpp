


#include <vgStableHeaders.h>
#include <vgAsyn/vgaCacheManager.h>
#include <vgAsyn/vgaIoRequest.h>
#include <vgKernel/vgkTrace.h>


namespace vgAsyn {
	
	
	
	
	//----------------------------------------------------------------
	char* CacheManager::getCacheFromIoRequest( IoRequest* req )
	{
		assert( req != NULL );
		assert( req->getBuffer() != NULL );

		if ( req == NULL || req->getBuffer() != NULL ||
			req->getFileInfoRef()->_fileSize <= 0 )
		{
			return NULL;
		}

		FileInfo* info = req->getFileInfoRef();

		HandleCacheMap::iterator findres =
			_handleCache.find( (int)info->_fileHandle );
		
		if ( findres == _handleCache.end() )
		{
			// 按理说应该找得到
			assert( 0 );
			return NULL;
		}

		OffsetMap::iterator offfind = findres->second.find( info->_fileOffset );

		if ( offfind == findres->second.end() )
		{
			// 按理说应该找得到
			assert( 0 );
			return NULL;
		}

		assert( offfind->second._size == info->_fileSize );
		assert( offfind->second._content != NULL );

		char* ret = new char[ info->_fileSize ];
		memcpy( ret, offfind->second._content , info->_fileSize );

		return ret;
	}

	CacheManager::CacheManager() : Singleton<CacheManager>( VGK_SINGLETON_LEFE_CACHEMGR )
	{
		VGK_TRACE(_T("CacheManager created."));
	}

	CacheManager::~CacheManager()
	{
		VGK_TRACE(_T("CacheManager destroyed."));
	}
	//----------------------------------------------------------------


}// end of namespace vgAsyn

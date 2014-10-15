


#include <vgStableHeaders.h>
#include <vgImage/vgiIoRequestTextureLod.h>
#include <vgImage/vgiImageMiniature.h>
#include <vgImage/vgiTexture.h>


namespace vgImage {
	
	
	//----------------------------------------------------------------
	bool IoRequestTextureLod::anotherThreadHandler()
	{
		//Sleep(200);

		dispatchMainThreadFunc();

		return true;
	}
	//----------------------------------------------------------------
	bool IoRequestTextureLod::mainThreadHandler()
	{
		int ref = _texture->getReferenceCounter();

		if ( ( (ref > 0) && (_texture->isEmptyTextrue() == false) ) 
			|| ( ref == 0 ) )
		{
			//------------------------------------------
			// 如果此时引用计数大于0并且不是空纹理
			// 如果此时引用计数等于0
			// 此时直接清理并且返回即可.
			//------------------------------------------
			//assert(0);
			delete this;
			return true;
		}

#if _DEBUG
		if ( ref == 0 && _texture->isEmptyTextrue() == false )
		{
			assert(0);
		}
#endif

		bool ret = _texture->createTextureByBuffer( _buffer , _fileInfo->_fileSize );
		assert( ret == true );

		delete this;
		return true;
	}
	//----------------------------------------------------------------

}// end of namespace vgImage


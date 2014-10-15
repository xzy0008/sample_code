



#include <vgStableHeaders.h>
#include <vgImage/vgiTextureObserver.h>


namespace vgImage {
	
	
	
	
	//----------------------------------------------------------------
	TextureObserver::TextureObserver( TextureItem* ptexitem , int lod )
	{
		_pTexItem = ptexitem;
		_lod = lod;
		assert( _lod >= 0 && _lod < VGLOD_N );
	}
	//----------------------------------------------------------------
	TextureObserver::~TextureObserver()
	{

	}
	//----------------------------------------------------------------

}// end of namespace vgImage

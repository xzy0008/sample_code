



#include <vgStableHeaders.h>
#include <vgImage/vgiTextureItem.h>
#include <vgImage/vgiTextureObserver.h>


namespace vgImage {
	
	
	
	
	//----------------------------------------------------------------
	TextureItem::TextureItem( String texname , ImageMiniature* imgmini )
	{
		_textureName = texname;

		for ( int i = 0 ; i < VGLOD_N ; ++i )
		{
			_textureLodPyramid[i] = new Texture( texname , i , imgmini);
		}

		for ( int i = 0 ; i < VGLOD_N ; ++ i )
		{
			_texObservers[i] = new TextureObserver( this , i );
		}
	}
	//----------------------------------------------------------------
	TextureItem::~TextureItem()
	{
		for ( int i = 0 ; i < VGLOD_N ; ++i )
		{
			assert( _textureLodPyramid[i] != NULL );
			delete _textureLodPyramid[i];
			_textureLodPyramid[i] = NULL;
		}

		for ( int i = 0 ; i < VGLOD_N ; ++i )
		{
			assert( _texObservers[i] != NULL );
			delete _texObservers[i];
			_texObservers[i] = NULL;
		}
	}
	//----------------------------------------------------------------

}// end of namespace vgImage

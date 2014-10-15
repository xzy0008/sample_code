





#ifndef __VGITEXTUREOBSERVER_H__
#define __VGITEXTUREOBSERVER_H__

#include <vgImage/vgiDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgImage/vgiTextureItem.h>


namespace vgImage {

	class Texture;


	/**
		@date 	2008/06/18  19:13	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGI_EXPORT TextureObserver
	{
	public:
		TextureObserver(TextureItem* ptexitem , 
			int lod);

		~TextureObserver();

		void useBind()
		{
			assert( _pTexItem != NULL );
			_pTexItem->useBind( _lod , true );
		}

		GLuint getTextureID( const bool& useBestLayer = true ) const
		{
			assert( _pTexItem != NULL );
			return _pTexItem->getTextureID( _lod , useBestLayer );
		}

		void addRef()
		{
			assert( _pTexItem != NULL );
			_pTexItem->addRef( _lod );
		}

		void releaseRef()
		{
			assert( _pTexItem != NULL );
			_pTexItem->releaseRef( _lod );
		}

		bool isEmptyTexture()
		{
			assert( _pTexItem != NULL );
			return _pTexItem->containEmptyTexture();
		}
	private:
	
	
		TextureItem* _pTexItem;
		int		_lod;
	};
	
	
	typedef TextureObserver* TexObsPointer;

	
	
}// end of namespace vgImage

#endif // end of __VGITEXTUREOBSERVER_H__
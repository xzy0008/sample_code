



#include <vgStableHeaders.h>
#include <vgImage/vgiSmallTextureReferencer.h>
#include <vgImage/vgiImageMiniature.h>
#include <vgImage/vgiTextureItem.h>
#include <vgImage/vgiTextureObserver.h>


namespace vgImage {
	
	
	
	
	//----------------------------------------------------------------
	SmallTextureReferencer::SmallTextureReferencer()
	{
		_filterEnable = true;
		_loadFileSizeThreshold = VGI_LOADFILESIZETHRESHOLD;
	}
	//----------------------------------------------------------------
	SmallTextureReferencer::~SmallTextureReferencer()
	{

	}
	//----------------------------------------------------------------
	bool SmallTextureReferencer::filterSmallTextures( TextureItem* itm )
	{
		if ( _filterEnable == false )
		{
			return false;
		}

		assert( itm != NULL );
		if ( itm == NULL )
		{
			return false;
		}

		ImageMiniature* clearmini = 
			itm->getTexture( VGLOD_CLEAR )->getImageMiniature();

		if ( clearmini->getMetaFileSize() <= _loadFileSizeThreshold )
		{
			TextureObserver* obs = itm->getObserver( VGLOD_CLEAR );

			if ( checkExist( obs ) )
			{
				//如果存在了，直接返回
				return true;
			}

			obs->addRef();

			_smallTextures.push_back( obs );
		}

		return true;
	}
	//----------------------------------------------------------------
	bool SmallTextureReferencer::checkExist( TextureObserver* itm )
	{
		assert( itm != NULL );

		TextureObserverPtrVector::iterator result;

		result = std::find( _smallTextures.begin(),  _smallTextures.end() , itm );

		if ( result == _smallTextures.end() )
		{
			// nothing find
			return false;
		}

		return true;
	}
	//----------------------------------------------------------------
	void SmallTextureReferencer::unRefAllSmallTextures()
	{
		TextureObserverPtrVector::iterator iter  = _smallTextures.begin();
		TextureObserverPtrVector::iterator iter_end = _smallTextures.end();

		for (  ; iter != iter_end ; ++ iter )
		{
			TextureObserver* itm = *iter;
			
			itm->releaseRef();
		}

		_smallTextures.clear();
	}
	//----------------------------------------------------------------



}// end of namespace vgImage

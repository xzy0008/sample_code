
#include <vgStableHeaders.h>

#include <vgTex/tvgImageFactory.h>


namespace vgCore {
	
	
	
	
	//----------------------------------------------------------------
	ImagePtr ImageFactory::createFromFileFormat( const String& filename , 
		const ImageFormat& imgformat /*= IMAGE_FORMAT_UNKNOWN */ )
	{
		if ( imgformat == IMAGE_FORMAT_DDS )
		{
			return ImagePtr( new DdsImage );
		}

		if ( imgformat == IMAGE_FORMAT_UNKNOWN )
		{
			ImageFormat t = ImageUtility::findImageFormat( filename );

			if ( t == IMAGE_FORMAT_UNKNOWN )
			{
				return emptyImagePtrReturn( filename );
			}
			if ( t == IMAGE_FORMAT_DDS )
			{
				return ImagePtr( new DdsImage );
			}

			return ImagePtr( new NormalImage );
		}
		else
		{
			return ImagePtr( new NormalImage );
		}
	}
	//----------------------------------------------------------------
	ImagePtr ImageFactory::createFromLoadingHeader( const String& filename , 
		const ImageFormat& imgformat /*= IMAGE_FORMAT_UNKNOWN */ )
	{
		ImagePtr  pimg = createFromFileFormat( filename , imgformat );

		if ( pimg.isNull() )
		{
			return emptyImagePtrReturn( filename );
		}

		if( pimg->loadFromHeaderInfo( filename , imgformat ) )
		{
			return pimg;
		}

		return emptyImagePtrReturn( filename );
	}
	//----------------------------------------------------------------
	ImagePtr ImageFactory::createFromLoadingFile( const String& filename , 
		const ImageFormat& imgformat /*= IMAGE_FORMAT_UNKNOWN */ )
	{
		return createFromArchiveFile(filename , imgformat);

		/*
		if ( pimg.isNull() )
		{
			pimg = createFromFileFormat( filename , imgformat );

			if ( pimg.isNull() )
			{
				return emptyImagePtrReturn( filename );
			}

			if( pimg->loadFromFile( filename , imgformat ) )
			{
				return pimg;
			}
			else
			{
				return emptyImagePtrReturn( filename );
			}
		}
		*/

		//return pimg;
	}
	//----------------------------------------------------------------
	ImagePtr ImageFactory::createFromTexturePtr( const TexturePtr& ptex , 
		const bool& checkLoaded /*= true */ )
	{
		if ( ptex.isNull() )
		{
			VG_WARN(Warning::WARN_INTERNAL_WARNING ,
				Warning::BUTTON_NONE ,
				"TexturePtr is NULL !",
				"ImageFactory::createFromTexturePtr()");
			return emptyImagePtrReturn("");
		}

		if ( checkLoaded == true )
		{
			/// for the case loaded
			if ( ptex->getTextureState() == Texture::TEXTURE_STATE_LOADED )
			{
				VG_WARN(Warning::WARN_INTERNAL_WARNING ,
					Warning::BUTTON_NONE ,
					"TexturePtr has been loaded! It is loaded state",
					"ImageFactory::createFromTexturePtr()");
				return emptyImagePtrReturn("");
			}

			/// for the case empty
			if ( ptex->getTextureState() == Texture::TEXTURE_STATE_EMPTY )
			{
				VG_WARN(Warning::WARN_INTERNAL_WARNING ,
					Warning::BUTTON_NONE ,
					"TexturePtr is empty state!",
					"ImageFactory::createFromTexturePtr()");
				return emptyImagePtrReturn("");
			}

			/// for the case unbinded
			if ( ptex->getTextureState() == Texture::TEXTURE_STATE_UNBINDED )
			{
				VG_WARN(Warning::WARN_INTERNAL_WARNING ,
					Warning::BUTTON_NONE ,
					"TexturePtr is unbinded state!",
					"ImageFactory::createFromTexturePtr()");
				return emptyImagePtrReturn("");
			}

			/// for the case undefined
			if ( ptex->getTextureState() == Texture::TEXTURE_STATE_UNDEFINED )
			{
				VG_WARN(Warning::WARN_INTERNAL_WARNING ,
					Warning::BUTTON_NONE ,
					"TexturePtr is undefined state!",
					"ImageFactory::createFromTexturePtr()");
				return emptyImagePtrReturn("");
			}
		}// end of checkLoaded



		String filename = ptex->getFilePath();

		if ( filename.empty() )
		{
			VG_WARN(Warning::WARN_FILE_NOT_FOUND ,
				Warning::BUTTON_NONE ,
				"文件名为空,无法创建纹理.",
				"ImageFactory::createFromTexturePtr()");
			return emptyImagePtrReturn("");
		}

		return createFromLoadingFile( filename );
	}
	//----------------------------------------------------------------
	NormalImagePtr ImageFactory::createNormalImagePtr()
	{
		return NormalImagePtr( new NormalImage );
	}
	//----------------------------------------------------------------

}// end of namespace vgCore

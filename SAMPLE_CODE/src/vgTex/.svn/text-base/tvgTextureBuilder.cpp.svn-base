

#include <vgStableHeaders.h>

#include <vgTex/tvgTextureBuilder.h>

#include <vgTex/tvgImageFactory.h>

namespace vgCore {

	TexturePtr TextureBuilder::createUnbindedTexturePtr(
		const String& filename , const ImageFormat& format , 
		const TextureBuildOptionPtr& option /*= TextureBuildOptionPtr::DEFAULT_OPTION */ )
	{
		
		ImagePtr pimg = ImageFactory::createFromLoadingFile( filename , format );

		if ( pimg.isNull() )
		{
			// when failed.
			return emptyTextureReturn( filename );
		}

		return pimg->createUnbindedTexPtr( option );
	}
	//----------------------------------------------------------------
	TexturePtr TextureBuilder::createUnbindedTexturePtr(
		const String& filename , 
		const TextureBuildOptionPtr& option /*= TextureBuildOptionPtr::DEFAULT_OPTION */ )
	{
		return createUnbindedTexturePtr( filename , IMAGE_FORMAT_UNKNOWN , option );
	}
	//----------------------------------------------------------------
	vgCore::TexturePtr TextureBuilder::createFromHugeCuttedDdsImage( 
		const String& filename ,  
		const TextureBuildOptionPtr& option /*= TextureBuildOptionPtr::DEFAULT_HUGE_MAP_DXT_OPTION */ )
	{
		//return createTextureFromDds( filename , option );






		return emptyTextureReturn( filename );
	}
	//----------------------------------------------------------------
	bool TextureBuilder::setTexturePtrLoaded( TexturePtr& ptex ,  
		const bool& useSelfOption /*= true*/,
		const ImageFormat& format /*= IMAGE_FORMAT_UNKNOWN */, 
		const TextureBuildOptionPtr& option /*= TextureBuildOptionPtr::DEFAULT_OPTION */ )
	{
		if ( ptex->isEmptyTexture() == true )
		{
			return false;
		}

		const String& filename = ptex->getFilePath();
		
		if ( filename == "" )
		{
			return false;
		}

		uint texid;
		
		// the case loaded and unloaded state
		if ( ptex->isBinded() == false )
		{
			return false;
		}

		// when loaded ,return.
		if ( ptex->getTextureState() == Texture::TEXTURE_STATE_LOADED )
		{
			return true;
		}


		ImagePtr pimg = ImageFactory::createFromLoadingFile( filename , format );

		if ( pimg.isNull() )
		{
			return false;
		}


		if ( useSelfOption == true )
		{
			texid = pimg->createTextureID( ptex->mTexBuildOptionPtr );
		}
		else
		{
			texid = pimg->createTextureID( option );
		}


		if ( texid == -1 )
		{
			return false;
		}

		ptex->makeLoadedFromUnloaded( texid );

		return true;
	}
	//----------------------------------------------------------------
	TexturePtr TextureBuilder::createUnloadedTexturePtr( 
		const String& uniname , const String& filename , 
		const ImageFormat& format /*= IMAGE_FORMAT_UNKNOWN*/, 
		const TextureBuildOptionPtr& option /*= TextureBuildOptionPtr::DEFAULT_OPTION */ )
	{
		const ImagePtr& pimg = ImageFactory::createFromLoadingHeader( filename , format );

		if ( pimg.isNull() )
		{
			return emptyTextureReturn( filename );
		}

		StringPtr pname = StringUtil::createStringPtr( uniname );
		TexturePtr ptex( new Texture() );

		ptex->makeUnloadedFromUndefined( pname , filename , pimg->getWidth() ,
			pimg->getHeight() ,	pimg->getTexPixelFormat() , pimg->getTextureFlag() ,
			option );

		return ptex;
	}
	//----------------------------------------------------------------
	bool TextureBuilder::setTexturePtrLoadedFromImagePtr( TexturePtr& ptex , 
		ImagePtr& imgPtr , const bool& ifSetImgNull )
	{
		assert( ptex->getFilePath() != "" );

		assert( !ptex.isNull() );

		if ( ptex->isEmptyTexture() == true )
		{
			VG_WARN(Warning::WARN_INVALIDPARAMS ,
				Warning::BUTTON_NONE ,
				"TexturePtr is empty texture!",
				"TextureBuilder::setTexturePtrLoadedFromImagePtr()");

			return false;
		}

		// the case loaded and unloaded state
		if ( ptex->getTextureState() == Texture::TEXTURE_STATE_LOADED )
		{
			/// 注意，此时返回true，表示已经载入了。
			return true;
		}

		// the case undefined and unbinded state
		if ( ptex->getTextureState() == Texture::TEXTURE_STATE_UNBINDED
			|| ptex->getTextureState() == Texture::TEXTURE_STATE_UNDEFINED )
		{
			/// 注意，此时返回false,表示出错，虽然unbinded表示已经载入了。
			return false;
		}



		if ( imgPtr.isNull() )
		{
			VG_WARN(Warning::WARN_INVALIDPARAMS ,
				Warning::BUTTON_NONE ,
				"ImagePtr 为空！",
				"TextureBuilder::setTexturePtrLoadedFromImagePtr()");

			return false;
		}

		assert( imgPtr->isValid() );

		if ( imgPtr->isValid() == false )
		{
			VG_WARN(Warning::WARN_INVALIDPARAMS ,
				Warning::BUTTON_NONE ,
				"ImagePtr is not  Valid!",
				"TextureBuilder::setTexturePtrLoadedFromImagePtr()");

			return false;
		}

		uint texid = imgPtr->createTextureID( ptex->mTexBuildOptionPtr );

		if ( texid == -1 )
		{
			return false;
		}

		ptex->makeLoadedFromUnloaded( texid );

		if ( ifSetImgNull == true )
		{
			imgPtr->release();
			imgPtr.setNull();
		}
		return true;
	}
	//----------------------------------------------------------------


}// end of namespace vgCore

/*
-----------------------------------------------------------------------------
  VRES(Virtual Reality GIS Engine System)    
  -------------------------------------------------------------
  License details ... waiting to add...
  -------------------------------------------------------------
  Copyright  (C) 2007 , leven - All Rights Reserved
-----------------------------------------------------------------------------
*/

#include <vgStableHeaders.h>

#include <vgTex/tvgImage.h>



namespace vgCore {

	const Integer Image::DEFAULT_IMAGE_WIDTH ( 0 );
	const Integer Image::DEFAULT_IMAGE_HEIGHT ( 0 );



	//----------------------------------------------------------------
	const String Image::getDetails() const
	{
		std::ostringstream o;
		o << "Image Details: ( "
			<< "FilePath: " << this->mFilePath
			<< " , Width: " << this->mWidth
			<< " , Height: " << this->mHeight
			<< " , mInitialised: " << this->mInitialised
			<< " , mTexPixelFormat: " << 
			TextureUtility::getPixelFormatDescription( mTexPixelFormat )
			<< " , mTextureFlag: " << 
			TextureUtility::getTexFlagDescription( mTextureFlag ) << " ) ";

		return o.str();
	}
	//----------------------------------------------------------------
	const String Image::getFilePath() const
	{
		return this->mFilePath;
	}
	//----------------------------------------------------------------
}// end of namespace

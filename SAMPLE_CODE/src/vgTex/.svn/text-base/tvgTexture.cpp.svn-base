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

#include <vgTex/tvgTexture.h>
//#include <vgLoadingTextureQueue.h>


namespace vgCore {

//	vgThreads::CriticalSection* TexturePtr::mpCriticalSect = new vgThreads::CriticalSection;


	/// 将其放在这里,保证EmptyTexturePtr在其之后创建.
	const TextureBuildOptionPtr TextureBuildOptionPtr::DEFAULT_OPTION(
		new TextureBuildOption(	"" /*mUniqueName*/ ,
		TEXTURE_PIXFORMAT_RGBA /*pixelformat*/, 
		false /*ifHasBorder*/ , true /*ifGenMipmap*/ , true /*ifLoadMipmap*/) );

	const TextureBuildOptionPtr TextureBuildOptionPtr::DEFAULT_OPTION_RGB(
		new TextureBuildOption(	"" /*mUniqueName*/ ,
		TEXTURE_PIXFORMAT_RGB /*pixelformat*/, 
		false /*ifHasBorder*/ , true /*ifGenMipmap*/ , true /*ifLoadMipmap*/) );


	const TextureBuildOptionPtr TextureBuildOptionPtr::DEFAULT_DXT_OPTION(
		new TextureBuildOption( "" /*mUniqueName*/ ,
		TEXTURE_PIXFORMAT_DXT3 /*pixelformat*/, 
		false /*ifHasBorder*/ , true /*ifGenMipmap*/ , true /*ifLoadMipmap*/) );

	const TextureBuildOptionPtr TextureBuildOptionPtr::DEFAULT_HUGE_MAP_DXT_OPTION(
		new TextureBuildOption( "" /*mUniqueName*/ ,
		TEXTURE_PIXFORMAT_DXT1 /*pixelformat*/, 
		true /*ifHasBorder*/ , false /*ifGenMipmap*/ , true /*ifLoadMipmap*/) );



	const TextureBuildOptionPtr TextureBuildOptionPtr::DEFAULT_DXT_LEVEL0(
		new TextureBuildOption( "" /*mUniqueName*/ ,
		TEXTURE_PIXFORMAT_DXT3 /*pixelformat*/, 
		false /*ifHasBorder*/ , true /*ifGenMipmap*/ , true /*ifLoadMipmap*/ ,
		-1 /*miplevel*/ , true /*turnOnAnisotropic*/) );

	const TextureBuildOptionPtr TextureBuildOptionPtr::DEFAULT_DXT_LEVEL1(
		new TextureBuildOption( "" /*mUniqueName*/ ,
		TEXTURE_PIXFORMAT_DXT3 /*pixelformat*/, 
		false /*ifHasBorder*/ , true /*ifGenMipmap*/ , true /*ifLoadMipmap*/ ,
		1 /*miplevel*/ , true /*turnOnAnisotropic*/) );

	const TextureBuildOptionPtr TextureBuildOptionPtr::DEFAULT_DXT_LEVEL2(
		new TextureBuildOption( "" /*mUniqueName*/ ,
		TEXTURE_PIXFORMAT_DXT3 /*pixelformat*/, 
		false /*ifHasBorder*/ , true /*ifGenMipmap*/ , true /*ifLoadMipmap*/ ,
		2 /*miplevel*/ , true /*turnOnAnisotropic*/) );

	const TextureBuildOptionPtr TextureBuildOptionPtr::DEFAULT_DXT_LEVEL3(
		new TextureBuildOption( "" /*mUniqueName*/ ,
		TEXTURE_PIXFORMAT_DXT3 /*pixelformat*/, 
		false /*ifHasBorder*/ , true /*ifGenMipmap*/ , true /*ifLoadMipmap*/ ,
		3 /*miplevel*/ , true /*turnOnAnisotropic*/) );

	const TextureBuildOptionPtr TextureBuildOptionPtr::DEFAULT_DXT_LEVEL4(
		new TextureBuildOption( "" /*mUniqueName*/ ,
		TEXTURE_PIXFORMAT_DXT3 /*pixelformat*/, 
		false /*ifHasBorder*/ , true /*ifGenMipmap*/ , true /*ifLoadMipmap*/ ,
		4 /*miplevel*/ , true /*turnOnAnisotropic*/) );

	const TextureBuildOptionPtr TextureBuildOptionPtr::DEFAULT_DXT_LEVEL5(
		new TextureBuildOption( "" /*mUniqueName*/ ,
		TEXTURE_PIXFORMAT_DXT3 /*pixelformat*/, 
		false /*ifHasBorder*/ , true /*ifGenMipmap*/ , true /*ifLoadMipmap*/ ,
		5 /*miplevel*/ , true /*turnOnAnisotropic*/) );



	const uint Texture::DEFAULT_EMPTY_TEXTURE_ID = 0;
	const Integer Texture::DEFAULT_EMPTY_TEXTURE_WIDTH = 0;
	const Integer Texture::DEFAULT_EMPTY_TEXTURE_HEIGHT = 0;

	const uint Texture::DEFAULT_UNDEFINED_TEXTURE_ID = 0;
	const Integer Texture::DEFAULT_UNDEFINED_TEXTURE_WIDTH = -1;
	const Integer Texture::DEFAULT_UNDEFINED_TEXTURE_HEIGHT = -1;

	/// 创建空纹理
	const TexturePtr TexturePtr::EmptyTexturePtr( new Texture( Texture::TEXTURE_STATE_EMPTY ) );

	//----------------------------------------------------------------
	Texture::Texture()
	{
		this->setParametersDefault();
		/*LogManager *plog = LogManager::getSingletonPtr();
		if ( plog != NULL )
		{
			plog->logMessage("tex created");
		}*/
	}
	//----------------------------------------------------------------
	Texture::Texture( TextureState empty )
	{
		assert( empty == TEXTURE_STATE_EMPTY );
		this->setEmptyTextureParameters();

		this->mTexBuildOptionPtr = TextureBuildOptionPtr::DEFAULT_OPTION;
	}
	//----------------------------------------------------------------
	Texture::~Texture()
	{
		this->deleteTexture();

		/*LogManager *plog = LogManager::getSingletonPtr();
		if ( plog != NULL )
		{
			plog->logMessage("tex deleted");
		}*/
	}

	//----------------------------------------------------------------
	String Texture::getDetails() const
	{
		String name;
		if ( !mpUniqueName.isNull() )
		{
			name = *mpUniqueName;
		}
		String texBuild;
		if ( !mTexBuildOptionPtr.isNull() )
		{
			if ( mTexBuildOptionPtr == TextureBuildOptionPtr::DEFAULT_OPTION )
			{
				texBuild = "DEFAULT_OPTION";
			}
			else if ( mTexBuildOptionPtr == TextureBuildOptionPtr::DEFAULT_DXT_OPTION )
			{
				texBuild = "DEFAULT_DXT_OPTION";
			}
			else if ( mTexBuildOptionPtr == TextureBuildOptionPtr::DEFAULT_HUGE_MAP_DXT_OPTION )
			{
				texBuild == "DEFAULT_HUGE_MAP_DXT_OPTION ";
			}
			else
			{
				texBuild = mTexBuildOptionPtr->getDetails();
			}
		}
		else
		{
			texBuild = " NULL ";
		}
		std::stringstream result;
		result << "Texture Detail: ( " 
			<< "mpUniqueName = " <<  name
			<< " , State = " << getStateDescription( mTexState )
			<< " , mFilePath = " << mFilePath
			<< " , mWidth = " << mWidth
			<< " , mHeight = " << mHeight
			<< " , mTextureID = " << mTextureID
			<< " , mBuildType = " << 
			TextureUtility::getPixelFormatDescription( mTexPixelFormat )
			<< " , mTexFlag = " << 
			TextureUtility::getTexFlagDescription( mTexFlag ) 
			<< "      mTexBuildOption : " << texBuild <<  " )";

		return result.str();
	}
	//----------------------------------------------------------------
	void Texture::release()
	{
		if ( mTexState == TEXTURE_STATE_EMPTY 
			|| mTexState == TEXTURE_STATE_UNDEFINED )
		{
			assert( mTextureID == -1 || mTextureID == 0 );
			return;
		}
		if ( mTexState == TEXTURE_STATE_LOADED 
			|| mTexState == TEXTURE_STATE_UNLOADED )
		{
			this->deleteTexture();
			this->setParametersDefault();
			return;
		}

		if ( mTexState == TEXTURE_STATE_UNBINDED )
		{
			this->deleteTexture();
			this->setParametersDefault();
			return;
		}
		return;
	}
	//----------------------------------------------------------------
	void Texture::makeLoadedFromUnloaded( const uint& texid )
	{
		assert( this->mTexState != TEXTURE_STATE_UNDEFINED
			&&  this->mTexState != TEXTURE_STATE_UNBINDED );
		assert( texid != DEFAULT_EMPTY_TEXTURE_ID 
			&& texid != DEFAULT_UNDEFINED_TEXTURE_ID);
		if ( mTexState != TEXTURE_STATE_UNLOADED )
		{
			return ;
		}
		this->mTexState = TEXTURE_STATE_LOADED;
		this->mTextureID = texid;
	}
	//----------------------------------------------------------------
	void Texture::makeUnloadedFromLoaded()
	{
		if ( mTexState != TEXTURE_STATE_LOADED )
		{
			return;
		}

		this->deleteTexture();
		this->mTexState = TEXTURE_STATE_UNLOADED;
	}
	//----------------------------------------------------------------
	void Texture::makeUnbindedFromUndefined( const uint& texid ,
		const String& filePath ,  const Integer& width , 
		const Integer& height , const TexturePixelFormat& pixformat , 
		const TextureFlag& flag ,
		const TextureBuildOptionPtr& optionPtr )
	{
		assert( texid != DEFAULT_EMPTY_TEXTURE_ID
			|| texid != DEFAULT_UNDEFINED_TEXTURE_ID );

		assert( filePath != "" );
		assert( width >= 0 && height >= 0 );
		assert( pixformat != TEXTURE_PIXFORMAT_UNKOWN );
		assert( flag != TEXTURE_FLAG_UNINITIALISED );
		assert( mTexState == TEXTURE_STATE_UNDEFINED );

		// unbinded state
		this->mpUniqueName = StringPtr::UnbindedTexStringPtr;
		this->mTexState = TEXTURE_STATE_UNBINDED;

		this->mFilePath = filePath ;
		this->mWidth = width ;
		this->mHeight = height ;
		this->mTextureID = texid ;
		this->mTexPixelFormat =  pixformat  ;
		this->mTexFlag = flag;

		assert( !optionPtr.isNull() );
		this->mTexBuildOptionPtr = optionPtr;
	}
	//----------------------------------------------------------------
	void Texture::makeLoadedFromUnbinded( const StringPtr& uniName )
	{
		assert( mTexState == TEXTURE_STATE_UNBINDED );
		assert( *uniName != "" );

		// loaded state
		this->mpUniqueName = uniName;
		this->mTexState = TEXTURE_STATE_LOADED;
	}
	//----------------------------------------------------------------
	void Texture::makeUnloadedFromUndefined( const StringPtr& uniName ,  
		const String& filePath ,  const Integer& width , 
		const Integer& height , const TexturePixelFormat& pixformat , 
		const TextureFlag& flag ,
		const TextureBuildOptionPtr& optionPtr )
	{
		assert( filePath != "" );
		assert( width >= 0 && height >= 0 );
		assert( pixformat != TEXTURE_PIXFORMAT_UNKOWN );
		assert( flag != TEXTURE_FLAG_UNINITIALISED );
		assert( mTexState == TEXTURE_STATE_UNDEFINED );

		// unloaded state
		this->mpUniqueName = uniName;
		this->mTexState = TEXTURE_STATE_UNLOADED;

		this->mFilePath = filePath ;
		this->mWidth = width ;
		this->mHeight = height ;
		this->mTexPixelFormat =  pixformat  ;
		this->mTexFlag = flag;

		assert( !optionPtr.isNull() );
		this->mTexBuildOptionPtr = optionPtr;
	}
	//----------------------------------------------------------------
	void Texture::deleteTexture()
	{
		if( this->mTextureID == DEFAULT_EMPTY_TEXTURE_ID
			|| this->mTextureID == DEFAULT_UNDEFINED_TEXTURE_ID )
		{
			return;
		}

		// make sure there is no error msg
		OpenGLSupport::makeErrorStackEmpty();
		String errMessage;

		const uint tmp = getTextureID();
		glDeleteTextures( 1 , &tmp );

		if( OpenGLSupport::checkOpenGLErrorWithoutThrow( errMessage ) )
		{
			VG_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR ,
				"glDeleteTextures failed! Error Code: " + errMessage ,
				"Texture::deleteTexture()");

			return;
		}

		setTextureID(DEFAULT_EMPTY_TEXTURE_ID);
		// 		mTextureID = DEFAULT_EMPTY_TEXTURE_ID;

	}
	//----------------------------------------------------------------
	void Texture::setParametersDefault()
	{
		// undefined state
		this->mpUniqueName = StringPtr::UndefinedTexStringPtr;
		this->mFilePath = "" ;
		this->mWidth = DEFAULT_UNDEFINED_TEXTURE_WIDTH ;
		this->mHeight = DEFAULT_UNDEFINED_TEXTURE_HEIGHT ;
		this->mTextureID = DEFAULT_UNDEFINED_TEXTURE_ID ;
		this->mTexPixelFormat =  TEXTURE_PIXFORMAT_UNKOWN  ;
		this->mTexFlag = TEXTURE_FLAG_UNINITIALISED;

		this->mTexState = TEXTURE_STATE_UNDEFINED;

		this->mTexBuildOptionPtr = TextureBuildOptionPtr::DEFAULT_OPTION;
	}	
	//----------------------------------------------------------------
	String Texture::getStateDescription( volatile const TextureState& state )
	{
		switch( state )
		{
		case TEXTURE_STATE_UNDEFINED:
			return "Undefined";
		case TEXTURE_STATE_UNLOADED:
			return "Unloaded";
		case TEXTURE_STATE_UNBINDED:
			return "Unbinded";
		case TEXTURE_STATE_LOADED:
			return "Loaded";
		case TEXTURE_STATE_EMPTY:
			return "Empty";
		default:
			return "Unkown";
		}
	}
	//----------------------------------------------------------------
	void Texture::setEmptyTextureParameters()
	{
		/// empty state
		this->mpUniqueName = StringPtr::EmptyTexStringPtr;
		this->mFilePath = "" ;
		this->mWidth = DEFAULT_EMPTY_TEXTURE_WIDTH ;
		this->mHeight = DEFAULT_EMPTY_TEXTURE_HEIGHT ;
		this->mTextureID = DEFAULT_EMPTY_TEXTURE_ID ;
		this->mTexPixelFormat =  TEXTURE_PIXFORMAT_UNKOWN  ;
		this->mTexFlag = TEXTURE_FLAG_UNINITIALISED;

		this->mTexState = TEXTURE_STATE_EMPTY;

		this->mTexBuildOptionPtr = TextureBuildOptionPtr::DEFAULT_OPTION;
	}
	//----------------------------------------------------------------




	//----------------------------------------------------------------
	//----------------------------------------------------------------
	const String TextureBuildOption::getDetails() const
	{
		std::ostringstream o;
		o << "TextureBuildOption : ( " 
			<< "mTexPixelFormat : " << 
			TextureUtility::getPixelFormatDescription(mTexPixelFormat)
			<< " , mIfHasBorder : " << mIfHasBorder
			<< " , mIfGenMipmap : " << mIfGenMipmap
			<< " , mIfLoadMipmap : " << mIfLoadMipmap
			<< " , mIfTurnOnFilterAnisotropic : " << mIfTurnOnFilterAnisotropic
			<< " , mMiplevel : " << mMiplevel << " )";

		return o.str();
	}

	//----------------------------------------------------------------



	//----------------------------------------------------------------
	const String TextureUtility::getPixelFormatDescription( 
		const TexturePixelFormat& format )
	{
		switch( format )
		{
		case   TEXTURE_PIXFORMAT_UNKOWN :
			{
				return "UNKOWN";
			}
		case   TEXTURE_PIXFORMAT_RGB	:	
			{
				return "RGB";
			}
		case   TEXTURE_PIXFORMAT_RGBA	:	
			{
				return "RGBA";
			}
		case   TEXTURE_PIXFORMAT_DXT1	:
			{
				return "DXT1";
			}
		case   TEXTURE_PIXFORMAT_DXT3	:
			{
				return "DXT3";
			}
		case   TEXTURE_PIXFORMAT_DXT5	:
			{
				return "DXT5";
			}
		default:
			return "error";
		}
	}
	//----------------------------------------------------------------
	const String TextureUtility::getTexFlagDescription( const TextureFlag& flag )
	{
		switch( flag )
		{
		case TEXTURE_FLAG_UNINITIALISED :
			{
				return "UNINITIALISED";
			}
		case TEXTURE_FLAG_TEXTURE_2D :
			{
				return "TEXTURE_2D";
			}
		case TEXTURE_FLAG_COMPRESSED :
			{
				return "COMPRESSED";
			}
		default:
			return "error";
		}
	}
	//----------------------------------------------------------------
	bool TextureBuildOption::operator == ( const TextureBuildOption& op2 ) const
	{
		return (/*this->mUniqueName == op2.mUniqueName && */
			this->mTexPixelFormat == op2.mTexPixelFormat &&
			this->mIfHasBorder	== op2.mIfHasBorder &&
			this->mIfGenMipmap	== op2.mIfGenMipmap &&
			this->mIfLoadMipmap	== op2.mIfLoadMipmap && 
			this->mMiplevel		== op2.mMiplevel && 
			this->mIfTurnOnFilterAnisotropic == op2.mIfTurnOnFilterAnisotropic);
	}
	//----------------------------------------------------------------
	void TextureBuildOption::setParametersDefault()
	{
		//this->mUniqueName = "";
		this->mTexPixelFormat = TEXTURE_PIXFORMAT_RGBA;
		this->mIfHasBorder	= false;
		this->mIfGenMipmap	= true;
		this->mIfLoadMipmap	= true;
		this->mMiplevel		= -1;
		this->mIfTurnOnFilterAnisotropic = true;
	}
	//----------------------------------------------------------------
	//----------------------------------------------------------------
	//----------------------------------------------------------------



	//void TexturePtr::releaseInviewRef()
	//{
	//	vgThreads::ScopedLock locker(mpCriticalSect);

	//	if ( ImageUtility::findImageFileExtension(*pRep->mpUniqueName) != "dds" )
	//	{
	//		return;
	//	}

	//	assert(pInviewCount);

	//	if ( *pInviewCount == 0 )
	//	{
	//		// 			assert(0);
	//		if ( pRep->mTexState == Texture::TEXTURE_STATE_LOADED )
	//		{
	//			vgTextureLoadingQueue* pqueque = 
	//				vgTextureLoadingQueue::getSingletonPtr();

	//			//此时卸载!
	//			pqueque->insertElement( pRep , false );
	//		}

	//		return;
	//	}

	//	--(*pInviewCount);

	//	if ( *pInviewCount == 0 )
	//	{
	//		// 			assert(0);
	//		if ( pRep->mTexState == Texture::TEXTURE_STATE_LOADED )
	//		{
	//			if ( pRep->mTexState == Texture::TEXTURE_STATE_LOADED )
	//			{
	//				vgTextureLoadingQueue* pqueque = 
	//					vgTextureLoadingQueue::getSingletonPtr();

	//				//此时卸载!
	//				pqueque->insertElement( pRep ,false );
	//			}
	//		}
	//	}

	//	return;
	//}


}// end of namespace 

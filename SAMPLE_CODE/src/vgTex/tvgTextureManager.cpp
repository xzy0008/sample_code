

#include <vgStableHeaders.h>

#include <vgTex/tvgTextureManager.h>
//#include <vgLoadingTextureQueue.h>


template <> 
vgCore::TextureManager* ::Singleton<vgCore::TextureManager>::ms_pSingleton = 0;

namespace vgCore {

	//////////////////////////////////////////////////////////////////////////
	///Implement the Singleton pattern begin
	///attention:this must include 3 implements.
	///注意单件模式每次要重写下下面的3个初始化

	TextureManager* TextureManager::getSingletonPtr(void)
	{
		return ms_pSingleton;
	}
	TextureManager& TextureManager::getSingleton(void)
	{  
		assert( ms_pSingleton );  
		return ( *ms_pSingleton );  
	}
	//----------------------------------------------------------------

	///Implement the Singleton pattern end
	//////////////////////////////////////////////////////////////////////////
	//----------------------------------------------------------------
	const String TextureManager::getDetails() const
	{
		std::stringstream result;
		result << "------------------TextureManager begin size :" << this->getSize() 
			<< "--------------------\n";

		TexturePtrMap::const_iterator iter = this->mTexturePtrMap.begin();
		TexturePtrMap::const_iterator iter_end = this->mTexturePtrMap.end();

		for( ; iter != iter_end; ++ iter)
		{
			result << "TextureUniqueName : " << *iter->first << "  \n--"
				<< iter->second->getDetails() << "\n" ;
		}

		result << "------------------TextureManager details end --------------------\n";

		return result.str();
	}
	//----------------------------------------------------------------
	TexturePtr TextureManager::getUnloadedTexturePtr( 
		const String& uniName , const String& filename ,
		const bool& autoSearch /*= true */,  
		const bool& autoInsert /*= true */, 
		const bool& forceUnload /*= false*/,  
		const ImageFormat& format /*= IMAGE_FORMAT_UNKNOWN */,  
		const TextureBuildOptionPtr& option /*= TextureBuildOptionPtr::DEFAULT_OPTION */ )
	{
		if ( autoSearch == true )
		{
			TexturePtrMap::iterator iter = 
				findIteratorByString( uniName );

			// if found
			if ( iter != this->mTexturePtrMap.end() )
			{
				if ( forceUnload == true )
				{
					iter->second->makeUnloadedFromLoaded();
				}
				return iter->second;
			}
		}// end of autoSearch

		const TexturePtr& ptex =
			TextureBuilder::createUnloadedTexturePtr( uniName ,
			filename , format , option );

		if ( ptex->isEmptyTexture() )
		{
			if ( autoInsert == true )
			{
				insertEmptyTexturePtr( uniName );
			}
			return failedFindTexptrReturn();
		}

		insertBindedTexturePtr( ptex );
		return ptex;
	}
	//----------------------------------------------------------------
	TexturePtr TextureManager::getTexturePtr( 
		const String& uniqueName , const bool& autoLoad /*= true */, 
		const bool& emptyTexInsert /*= true */,  
		const TextureBuildOptionPtr& option /*= TextureBuildOptionPtr::DEFAULT_OPTION */ )
	{
		TexturePtrMap::iterator iter = 
			findIteratorByString( uniqueName );

		if ( autoLoad == false )
		{
			if ( iter == this->mTexturePtrMap.end() )
			{
				return failedFindTexptrReturn();
			}
			return iter->second;
		}

		/// auto load

		/// search found
		if ( iter != this->mTexturePtrMap.end() )
		{
			return iter->second;
		}

		/// not found ,so insert
		TextureInsertResult result = 
			this->addTexturePtr( uniqueName , false , emptyTexInsert , option );

		// failed insert
		if ( result.second == false )
		{
			return failedFindTexptrReturn();
		}
		else
		{
			// insert ok so return first
			return result.first->second;
		}
	}
	//----------------------------------------------------------------
	TextureManager::TextureInsertResult TextureManager::addTexturePtrByName(
		const String& uniqueName , const String& filename ,  
		const bool& autoSearch /*= true */, 
		const bool& emptyTexInsert /*= true */,  
		const TextureBuildOptionPtr& option /*= TextureBuildOptionPtr::DEFAULT_OPTION */ )
	{
		/// 不需要搜索,即已经知道这是第一次载入,所以这里直接插入即可.
		if ( autoSearch == false )
		{
			return loadImageAndInsert(
				uniqueName , filename , emptyTexInsert ,option );
		}

		TexturePtrMap::iterator iter = 
			findIteratorByString( uniqueName );

		// in case mMap already have the tex with the same name.
		if ( iter != this->mTexturePtrMap.end() )
		{
			return failedInsertResultReturn();
		}

		return loadImageAndInsert(
			uniqueName , filename , emptyTexInsert ,option );
	}
	//----------------------------------------------------------------
	bool TextureManager::unloadTexturePtr( const String& uniname )
	{
		TexturePtrMap::iterator iter = 
			findIteratorByString( uniname );

		if ( iter == this->mTexturePtrMap.end() )
		{
			return false;
		}
		unloadTexturePtr( iter->second );
		return true;
	}
	//----------------------------------------------------------------
	void TextureManager::unloadAll()
	{
		TexturePtrMap::iterator iter = mTexturePtrMap.begin() ;
		TexturePtrMap::iterator iter_end = mTexturePtrMap.end() ;
		for( ; iter != iter_end ; ++ iter )
		{
			iter->second->makeUnloadedFromLoaded();
		}
	}
	//----------------------------------------------------------------
	void TextureManager::reloadAll()
	{
		TexturePtrMap::iterator iter = mTexturePtrMap.begin() ;
		TexturePtrMap::iterator iter_end = mTexturePtrMap.end() ;

		for( ; iter != iter_end ; ++ iter )
		{
			TextureBuilder::setTexturePtrLoaded( iter->second );
		}
	}
	//----------------------------------------------------------------

//	TexturePtr TextureManager::getMultithreadTexturePtr( const String& uniqueName , 
//		const TextureBuildOptionPtr& option /*= TextureBuildOptionPtr::DEFAULT_OPTION */ )
//	{
//
//#if VG_SINGLE_THREAD
//		assert(0&&"不支持单线程!");
//#endif
//
//		TexturePtrMap::iterator iter = 
//			findIteratorByString( uniqueName );
//
//		if ( iter == this->mTexturePtrMap.end() )
//		{
//			return TexturePtr::EmptyTexturePtr;
//		}
//
//		///newadding...begin
//		iter->second.addInviewRef();
//
//		if ( iter->second->getTextureState() != Texture::TEXTURE_STATE_LOADED || 
//			ImageUtility::findImageFileExtension( uniqueName ) == "dds" )
//		{
//			vgTextureLoadingQueue& queque = 
//				vgTextureLoadingQueue::getSingleton();
//
//			queque.insertElement( iter->second.getPointer() , true );
//		}
//
//		///newadding...end
//		return iter->second;
//
//
//		assert(0);
//
//#if 0
//		/// auto load
//
//		/// search found
//		if ( iter != this->mTexturePtrMap.end() )
//		{
//			///newadding...begin
//			iter->second.addInviewRef();
//			///newadding...end
//
//			return iter->second;
//		}
//
//
//		/// not found ,so insert
//		TextureInsertResult result = 
//			this->addTexturePtr( uniqueName , false , emptyTexInsert , option );
//
//		// failed insert
//		if ( result.second == false )
//		{
//			return failedFindTexptrReturn();
//		}
//		else
//		{
//			// insert ok so return first
//
//			///newadding...begin
//			result.first->second.addInviewRef();
//			///newadding...end
//
//			return result.first->second;
//		}
//#endif
//	}
	//----------------------------------------------------------------
	const String TextureManager::getPtrDetails()
	{
		std::stringstream result;
		result << "------------------TextureManager Ptrs details begin size :" << this->getSize() 
			<< "--------------------\n";

		TexturePtrMap::iterator iter = this->mTexturePtrMap.begin();
		TexturePtrMap::iterator iter_end = this->mTexturePtrMap.end();

		///newadding...begin
		for( ; iter != iter_end; ++ iter)
		{
			result << iter->second.getPtrDetails() << "\n" ;
		}
		///newadding...end


		result << "------------------TextureManager Ptrs details end --------------------\n";
		return result.str();
	}
	//----------------------------------------------------------------
	
	
}// end of namespace vgCore

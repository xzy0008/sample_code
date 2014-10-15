
//----------------------------------------------------------------
inline TextureManager::TextureInsertResult  TextureManager::addTexturePtr( const StringPtr& uniqueName ,
			TexturePtr& texptr , const bool& emptyInsert /*= true*/ )
{
	assert( !texptr.isNull()  );

	// is not empty,so binded.
	/// if binded successful?
	if( bindUniqueNameToTexture( uniqueName , texptr ) )
	{
		return 	this->insertBindedTexturePtr( texptr );
	}
	else	
	{
		if ( emptyInsert == true )
		{
			/// is empty ,so insert empty and name.
			return	this->insertEmptyTexturePtr( uniqueName );
		}
		return failedInsertResultReturn();
	}
}
//----------------------------------------------------------------
TextureManager::TextureInsertResult TextureManager::loadImageAndInsert( 
	const String& uniqueName , const String& filename , 
	const bool& emptyTexInsert /*= true */,
	const TextureBuildOptionPtr& option /*= TextureBuildOptionPtr::DEFAULT_OPTION */ )
{
	TexturePtr ptex =
		TextureBuilder::createUnbindedTexturePtr( filename , option );

	StringPtr pname = StringUtil::createStringPtr( uniqueName );

	return this->addTexturePtr( pname , ptex , emptyTexInsert );
}
//----------------------------------------------------------------




//----------------------------------------------------------------
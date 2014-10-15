//----------------------------------------------------------------
inline void Texture::useBind()
{
	assert( getTextureState() != TEXTURE_STATE_UNDEFINED );

	if ( getTextureState() == TEXTURE_STATE_EMPTY )
	{
		glBindTexture( GL_TEXTURE_2D , DEFAULT_EMPTY_TEXTURE_ID );
	}
	else
	{
		glBindTexture( GL_TEXTURE_2D , getTextureID() );
	}
}
//----------------------------------------------------------------
inline bool Texture::isEmptyTexture() 
{
	assert( isInitialised() );

	if ( getTextureState() == TEXTURE_STATE_EMPTY )
	{
		return true;
	}
	return false;
}
//----------------------------------------------------------------
inline bool Texture::isBinded() 
{
	if ( getTextureState() == TEXTURE_STATE_LOADED 
		|| getTextureState() == TEXTURE_STATE_UNLOADED )
	{
		return true;
	}
	return false;
}
//----------------------------------------------------------------
inline bool Texture::isInitialised() 
{
	if ( getTextureState() == TEXTURE_STATE_UNDEFINED )
	{
		return false;
	}
	return true;
}
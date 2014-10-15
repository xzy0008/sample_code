

inline bool smallBlock::isInFileBlock(const fileBlock& fblock) const
{
	return absoluteRect.testIntersection( fblock.fileAbsoluteRect );
}
inline String smallBlock::getDetails() const 
{
	String result(_T( "smallBlock( " ));
	result += _T( "blockFileName: " ) + blockFileName + _T( " , absoluteRect = " ) + absoluteRect.getDetails();
	/// 这里主要是为了打印清晰
	/// 同时为smallBlockLayout服务.
	if ( relativeRect != ImageRect::ZERO )
	{
		result +=  _T( " ,relativeRect = " );
		result += relativeRect.getDetails();
	}
	if ( hasIntersect )
	{
		result += _T( " \n\t\t hasIntersect = true" );
		//result += IntersectRect.getDetails();
	}

	result += _T( " )" );
	return result;
}

//----------------------------------------------------------------

inline Integer ImagePos::operator [] ( const size_t i ) const
{
	assert( i < 2 );

	return *(&x+i);
}

inline Integer& ImagePos::operator [] ( const size_t i )
{
	assert( i < 2 );

	return *(&x+i);
}
//----------------------------------------------------------------
inline ImagePos& ImagePos::operator = ( const ImagePos& rkVector )
{
	x = rkVector.x;
	y = rkVector.y;

	return *this;
}

inline ImagePos& ImagePos::operator = ( const Integer fScalar)
{
	x = fScalar;
	y = fScalar;

	return *this;
}

inline bool ImagePos::operator == ( const ImagePos& rkVector ) const
{
	return ( x == rkVector.x && y == rkVector.y );
}

inline bool ImagePos::operator != ( const ImagePos& rkVector ) const
{
	return ( x != rkVector.x || y != rkVector.y  );
}
//----------------------------------------------------------------
inline ImagePos ImagePos::operator + ( const ImagePos& rkVector ) const
{
	return ImagePos(
		x + rkVector.x,
		y + rkVector.y);
}

inline ImagePos ImagePos::operator - ( const ImagePos& rkVector ) const
{
	return ImagePos(
		x - rkVector.x,
		y - rkVector.y);
}

inline ImagePos ImagePos::operator * ( const Integer fScalar ) const
{
	return ImagePos(
		x * fScalar,
		y * fScalar);
}

inline ImagePos ImagePos::operator * ( const ImagePos& rhs) const
{
	return ImagePos(
		x * rhs.x,
		y * rhs.y);
}

inline ImagePos ImagePos::operator / ( const Integer fScalar ) const
{
	assert( fScalar != 0 );

	return ImagePos(
		x / fScalar,
		y / fScalar);
}

inline ImagePos ImagePos::operator / ( const ImagePos& rhs) const
{
	return ImagePos(
		x / rhs.x,
		y / rhs.y);
}
inline const ImagePos& ImagePos::operator + () const
{
	return *this;
}

inline ImagePos ImagePos::operator - () const
{
	return ImagePos(-x, -y);
}

//----------------------------------------------------------------
// overloaded operators to help ImagePos
inline  ImagePos operator * ( const Integer fScalar, const ImagePos& rkVector )
{
	return ImagePos(
		fScalar * rkVector.x,
		fScalar * rkVector.y);
}

inline  ImagePos operator / ( const Integer fScalar, const ImagePos& rkVector )
{
	return ImagePos(
		fScalar / rkVector.x,
		fScalar / rkVector.y);
}

inline  ImagePos operator + (const ImagePos& lhs, const Integer rhs)
{
	return ImagePos(
		lhs.x + rhs,
		lhs.y + rhs);
}

inline  ImagePos operator + (const Integer lhs, const ImagePos& rhs)
{
	return ImagePos(
		lhs + rhs.x,
		lhs + rhs.y);
}

inline  ImagePos operator - (const ImagePos& lhs, const Integer rhs)
{
	return ImagePos(
		lhs.x - rhs,
		lhs.y - rhs);
}

inline  ImagePos operator - (const Integer lhs, const ImagePos& rhs)
{
	return ImagePos(
		lhs - rhs.x,
		lhs - rhs.y);
}
//----------------------------------------------------------------

// arithmetic updates
inline ImagePos& ImagePos::operator += ( const ImagePos& rkVector )
{
	x += rkVector.x;
	y += rkVector.y;

	return *this;
}

inline ImagePos& ImagePos::operator += ( const Integer fScaler )
{
	x += fScaler;
	y += fScaler;

	return *this;
}

inline ImagePos& ImagePos::operator -= ( const ImagePos& rkVector )
{
	x -= rkVector.x;
	y -= rkVector.y;

	return *this;
}

inline ImagePos& ImagePos::operator -= ( const Integer fScaler )
{
	x -= fScaler;
	y -= fScaler;

	return *this;
}

inline ImagePos& ImagePos::operator *= ( const Integer fScalar )
{
	x *= fScalar;
	y *= fScalar;

	return *this;
}

inline ImagePos& ImagePos::operator *= ( const ImagePos& rkVector )
{
	x *= rkVector.x;
	y *= rkVector.y;

	return *this;
}

inline ImagePos& ImagePos::operator /= ( const Integer fScalar )
{
	assert( fScalar != 0 );

	x /= fScalar;
	y /= fScalar;

	return *this;
}

inline ImagePos& ImagePos::operator /= ( const ImagePos& rkVector )
{
	x /= rkVector.x;
	y /= rkVector.y;

	return *this;
}
//----------------------------------------------------------------
inline bool ImagePos::operator > ( const ImagePos& rhs ) const
{
	if( x > rhs.x && y > rhs.y )
		return true;
	return false;
}
//----------------------------------------------------------------
inline bool ImagePos::operator < ( const ImagePos& rhs ) const
{
	if( x < rhs.x && y < rhs.y )
		return true;
	return false;
}
//----------------------------------------------------------------
inline bool ImagePos::operator >= ( const ImagePos& rhs ) const
{
	if( x >= rhs.x && y >= rhs.y )
		return true;
	return false;
}
//----------------------------------------------------------------
inline bool ImagePos::operator <= ( const ImagePos& rhs ) const
{
	if( x <= rhs.x && y <= rhs.y )
		return true;
	return false;
}

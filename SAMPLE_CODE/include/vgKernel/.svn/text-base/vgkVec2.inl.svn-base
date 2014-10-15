//----------------------------------------------------------------


inline void Vec2::makeFloor( const Vec2& cmp )
{
	if( cmp.x < x ) x = cmp.x;
	if( cmp.y < y ) y = cmp.y;
}

//----------------------------------------------------------------

inline float Vec2::operator [] ( const size_t i ) const
{
	assert( i < 2 );

	return *(&x+i);
}

inline float& Vec2::operator [] ( const size_t i )
{
	assert( i < 2 );

	return *(&x+i);
}
//----------------------------------------------------------------
inline Vec2& Vec2::operator = ( const Vec2& rkVector )
{
	x = rkVector.x;
	y = rkVector.y;

	return *this;
}

inline Vec2& Vec2::operator = ( const float fScalar)
{
	x = fScalar;
	y = fScalar;

	return *this;
}

inline bool Vec2::operator == ( const Vec2& rkVector ) const
{
	return ( x == rkVector.x && y == rkVector.y );
}

inline bool Vec2::operator != ( const Vec2& rkVector ) const
{
	return ( x != rkVector.x || y != rkVector.y  );
}

//----------------------------------------------------------------
inline Vec2 Vec2::operator + ( const Vec2& rkVector ) const
{
	return Vec2(
		x + rkVector.x,
		y + rkVector.y);
}

inline Vec2 Vec2::operator - ( const Vec2& rkVector ) const
{
	return Vec2(
		x - rkVector.x,
		y - rkVector.y);
}

inline Vec2 Vec2::operator * ( const float fScalar ) const
{
	return Vec2(
		x * fScalar,
		y * fScalar);
}

inline Vec2 Vec2::operator * ( const Vec2& rhs) const
{
	return Vec2(
		x * rhs.x,
		y * rhs.y);
}

inline Vec2 Vec2::operator / ( const float fScalar ) const
{
	assert( fScalar != 0.0 );

	float fInv = 1.0f / fScalar;

	return Vec2(
		x * fInv,
		y * fInv);
}

inline Vec2 Vec2::operator / ( const Vec2& rhs) const
{
	return Vec2(
		x / rhs.x,
		y / rhs.y);
}

inline const Vec2& Vec2::operator + () const
{
	return *this;
}

inline Vec2 Vec2::operator - () const
{
	return Vec2(-x, -y);
}

//----------------------------------------------------------------
// overloaded operators to help Vec2
inline  Vec2 operator * ( const float fScalar, const Vec2& rkVector )
{
	return Vec2(
		fScalar * rkVector.x,
		fScalar * rkVector.y);
}

inline  Vec2 operator / ( const float fScalar, const Vec2& rkVector )
{
	return Vec2(
		fScalar / rkVector.x,
		fScalar / rkVector.y);
}

inline  Vec2 operator + (const Vec2& lhs, const float rhs)
{
	return Vec2(
		lhs.x + rhs,
		lhs.y + rhs);
}

inline  Vec2 operator + (const float lhs, const Vec2& rhs)
{
	return Vec2(
		lhs + rhs.x,
		lhs + rhs.y);
}

inline  Vec2 operator - (const Vec2& lhs, const float rhs)
{
	return Vec2(
		lhs.x - rhs,
		lhs.y - rhs);
}

inline  Vec2 operator - (const float lhs, const Vec2& rhs)
{
	return Vec2(
		lhs - rhs.x,
		lhs - rhs.y);
}

//----------------------------------------------------------------

// arithmetic updates
inline Vec2& Vec2::operator += ( const Vec2& rkVector )
{
	x += rkVector.x;
	y += rkVector.y;

	return *this;
}

inline Vec2& Vec2::operator += ( const float fScaler )
{
	x += fScaler;
	y += fScaler;

	return *this;
}

inline Vec2& Vec2::operator -= ( const Vec2& rkVector )
{
	x -= rkVector.x;
	y -= rkVector.y;

	return *this;
}

inline Vec2& Vec2::operator -= ( const float fScaler )
{
	x -= fScaler;
	y -= fScaler;

	return *this;
}

inline Vec2& Vec2::operator *= ( const float fScalar )
{
	x *= fScalar;
	y *= fScalar;

	return *this;
}

inline Vec2& Vec2::operator *= ( const Vec2& rkVector )
{
	x *= rkVector.x;
	y *= rkVector.y;

	return *this;
}

inline Vec2& Vec2::operator /= ( const float fScalar )
{
	assert( fScalar != 0.0 );

	float fInv = 1.0f / fScalar;

	x *= fInv;
	y *= fInv;

	return *this;
}

inline Vec2& Vec2::operator /= ( const Vec2& rkVector )
{
	x /= rkVector.x;
	y /= rkVector.y;

	return *this;
}
//----------------------------------------------------------------
inline float Vec2::length () const
{
	return sqrt( x * x + y * y );
}

//----------------------------------------------------------------
inline float Vec2::squaredLength () const
{
	return x * x + y * y;
}

//----------------------------------------------------------------
inline float Vec2::dotProduct(const Vec2& vec) const
{
	return x * vec.x + y * vec.y;
}


//----------------------------------------------------------------

inline float Vec2::normalise()
{
	float fLength = sqrt( x * x + y * y);

	// Will also work for zero-sized vectors, but will change nothing
	if ( fLength > 1e-08 )
	{
		float fInvLength = 1.0f / fLength;
		x *= fInvLength;
		y *= fInvLength;
	}

	return fLength;
}
//----------------------------------------------------------------

inline Vec2& Vec2::normalisedRef()
{
	this->normalise();
	return *this;
}
//----------------------------------------------------------------
inline Vec2 Vec2::midPoint( const Vec2& vec ) const
{
	return Vec2(
		( x + vec.x ) * 0.5f,
		( y + vec.y ) * 0.5f );
}


//----------------------------------------------------------------
inline bool Vec2::operator < ( const Vec2& rhs ) const
{
	if( x < rhs.x && y < rhs.y )
		return true;
	return false;
}

//----------------------------------------------------------------
inline bool Vec2::operator > ( const Vec2& rhs ) const
{
	if( x > rhs.x && y > rhs.y )
		return true;
	return false;
}

//----------------------------------------------------------------
inline void Vec2::makeCeil( const Vec2& cmp )
{
	if( cmp.x > x ) x = cmp.x;
	if( cmp.y > y ) y = cmp.y;
}


//----------------------------------------------------------------
inline Vec2 Vec2::perpendicular(void) const
{
	return Vec2 (-y, x);
}

//----------------------------------------------------------------

inline float Vec2::crossProduct( const Vec2& rkVector ) const
{
	return x * rkVector.y - y * rkVector.x;
}

//----------------------------------------------------------------
inline bool Vec2::isZeroLength(void) const
{
	float sqlen = (x * x) + (y * y);
	return (sqlen < (1e-06 * 1e-06));

}

//----------------------------------------------------------------
inline Vec2 Vec2::normalisedCopy(void) const
{
	Vec2 ret = *this;
	ret.normalise();
	return ret;
}

//----------------------------------------------------------------
inline Vec2 Vec2::reflect(const Vec2& normal) const
{
	return Vec2( *this - ( 2 * this->dotProduct(normal) * normal ) );
}

//----------------------------------------------------------------

//----------------------------------------------------------------
//----------------------------------------------------------------

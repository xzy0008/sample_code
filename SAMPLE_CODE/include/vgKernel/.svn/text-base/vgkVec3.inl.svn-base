inline Vec3 Vec3::makeCeil( const Vec3& cmp )
{
	if( cmp.x > x ) x = cmp.x;
	if( cmp.y > y ) y = cmp.y;
	if( cmp.z > z ) z = cmp.z;
	return *this;
}
inline Vec3 Vec3::ceilProduct( const Vec3& c ) const
{
	Vec3 cmp = c;
	if( cmp.x < x ) cmp.x = x;
	if( cmp.y < y ) cmp.y = y;
	if( cmp.z < z ) cmp.z = z;
	return cmp;
}
inline Vec3 Vec3::floorProduct( const Vec3& c ) const
{
	Vec3 cmp = c;
	if( cmp.x > x ) cmp.x = x;
	if( cmp.y > y ) cmp.y = y;
	if( cmp.z > z ) cmp.z = z;
	return cmp;
}
//----------------------------------------------------------------
inline Vec3 Vec3::perpendicular(void) const
{
	static const float fSquareZero = 1e-06f * 1e-06f;

	Vec3 perp = this->crossProduct( Vec3::UNIT_X );

	// Check length
	if( perp.squaredLength() < fSquareZero )
	{
		/* This vector is the Y axis multiplied by a scalar, so we have
		to use another axis.
		*/
		perp = this->crossProduct( Vec3::UNIT_Y );
	}

	return perp;
}
//---------------------------------------------------------------
inline float Vec3::operator [] ( const size_t i ) const
{
	assert( i < 3 );

	return *(&x+i);
}

inline float& Vec3::operator [] ( const size_t i )
{
	assert( i < 3 );

	return *(&x+i);
}

//----------------------------------------------------------------
///operator操作函数重写
inline Vec3& Vec3::operator = ( const Vec3& rkVector )
{
	x = rkVector.x;
	y = rkVector.y;
	z = rkVector.z;

	return *this;
}

inline Vec3& Vec3::operator = ( const float fScaler )
{
	x = fScaler;
	y = fScaler;
	z = fScaler;

	return *this;
}
//----------------------------------------------------------------
inline bool Vec3::operator == ( const Vec3& rkVector ) const
{
	return ( abs(x - rkVector.x) < 1e-4 && 
		abs(y - rkVector.y) < 1e-4 && 
		abs(z - rkVector.z ) < 1e-4);
}

inline bool Vec3::operator != ( const Vec3& rkVector ) const
{
	return ( x != rkVector.x || y != rkVector.y || z != rkVector.z );
}
inline Vec3 Vec3::operator + ( const Vec3& rkVector ) const
{
	return Vec3(
		x + rkVector.x,
		y + rkVector.y,
		z + rkVector.z);
}

inline Vec3 Vec3::operator - ( const Vec3& rkVector ) const
{
	return Vec3(
		x - rkVector.x,
		y - rkVector.y,
		z - rkVector.z);
}
inline Vec3 Vec3::operator * ( const float fScalar ) const
{
	return Vec3(
		x * fScalar,
		y * fScalar,
		z * fScalar);
}
//----------------------------------------------------------------


inline Vec3 Vec3::operator / ( const float fScalar ) const
{
	assert( fScalar != 0.0 );

	float fInv = 1.0f / fScalar;

	return Vec3(
		x * fInv,
		y * fInv,
		z * fInv);
}
//----------------------------------------------------------------
inline const Vec3& Vec3::operator + () const
{
	return *this;
}

inline Vec3 Vec3::operator - () const
{
	return Vec3(-x, -y, -z);
}
//----------------------------------------------------------------
///当操作数为做操作数时
inline Vec3 operator * ( const float fScalar, const Vec3& rkVector )
{
	return Vec3(
		fScalar * rkVector.x,
		fScalar * rkVector.y,
		fScalar * rkVector.z);
}

inline Vec3 Vec3::operator * (const Vec3& rkVector) const
{
	return Vec3(
		x * rkVector.x,
		y * rkVector.y,
		z * rkVector.z);
}

inline Vec3 operator / ( const float fScalar, const Vec3& rkVector )
{
	return Vec3(
		fScalar / rkVector.x,
		fScalar / rkVector.y,
		fScalar / rkVector.z);
}

inline Vec3 Vec3::operator / ( const Vec3& rkVec) const
{
	return Vec3(x / rkVec.x, 
		y / rkVec.y,
		z / rkVec.z);
}

inline Vec3 operator + (const Vec3& lhs, const float rhs)
{
	return Vec3(
		lhs.x + rhs,
		lhs.y + rhs,
		lhs.z + rhs);
}

inline Vec3 operator + (const float lhs, const Vec3& rhs)
{
	return Vec3(
		lhs + rhs.x,
		lhs + rhs.y,
		lhs + rhs.z);
}

inline Vec3 operator - (const Vec3& lhs, const float rhs)
{
	return Vec3(
		lhs.x - rhs,
		lhs.y - rhs,
		lhs.z - rhs);
}

inline Vec3 operator - (const float lhs, const Vec3& rhs)
{
	return Vec3(
		lhs - rhs.x,
		lhs - rhs.y,
		lhs - rhs.z);
}
//----------------------------------------------------------------
inline Vec3& Vec3::operator += ( const Vec3& rkVector )
{
	x += rkVector.x;
	y += rkVector.y;
	z += rkVector.z;

	return *this;
}

inline Vec3& Vec3::operator += ( const float fScalar )
{
	x += fScalar;
	y += fScalar;
	z += fScalar;
	return *this;
}

inline Vec3& Vec3::operator -= ( const Vec3& rkVector )
{
	x -= rkVector.x;
	y -= rkVector.y;
	z -= rkVector.z;

	return *this;
}

inline Vec3& Vec3::operator -= ( const float fScalar )
{
	x -= fScalar;
	y -= fScalar;
	z -= fScalar;
	return *this;
}

inline Vec3& Vec3::operator *= ( const float fScalar )
{
	x *= fScalar;
	y *= fScalar;
	z *= fScalar;
	return *this;
}

inline Vec3& Vec3::operator *= ( const Vec3& rkVector )
{
	x *= rkVector.x;
	y *= rkVector.y;
	z *= rkVector.z;

	return *this;
}

inline Vec3& Vec3::operator /= ( const float fScalar )
{
	assert( fScalar != 0.0f );

	float fInv = 1.0f / fScalar;

	x *= fInv;
	y *= fInv;
	z *= fInv;

	return *this;
}

inline Vec3& Vec3::operator /= ( const Vec3& rkVector )
{
	x /= rkVector.x;
	y /= rkVector.y;
	z /= rkVector.z;

	return *this;
}
//----------------------------------------------------------------
inline float Vec3::normalise()
{
	float fLength = sqrt( x * x + y * y + z * z );

	// Will also work for zero-sized vectors, but will change nothing
	if ( fLength > 1e-08 )
	{
		float fInvLength = 1.0f / fLength;
		x *= fInvLength;
		y *= fInvLength;
		z *= fInvLength;
	}

	return fLength;
}
//----------------------------------------------------------------

inline Vec3& Vec3::normalisedRef()
{
	normalise();
	return *this;
}
//----------------------------------------------------------------

///计算叉乘
inline Vec3 Vec3::crossProduct( const Vec3& rkVector ) const
{
	return Vec3(
		y * rkVector.z - z * rkVector.y,
		z * rkVector.x - x * rkVector.z,
		x * rkVector.y - y * rkVector.x);
}
//----------------------------------------------------------------
inline Vec3 Vec3::midPoint( const Vec3& vec /*= Vec3()*/ ) const
{
	return Vec3(
		( x + vec.x ) * 0.5f,
		( y + vec.y ) * 0.5f,
		( z + vec.z ) * 0.5f );
}

//----------------------------------------------------------------


inline bool Vec3::operator < ( const Vec3& rhs ) const
{
	if( x < rhs.x && y < rhs.y && z < rhs.z )
		return true;
	return false;
}

inline bool Vec3::operator > ( const Vec3& rhs ) const
{
	if( x > rhs.x && y > rhs.y && z > rhs.z )
		return true;
	return false;
}
//----------------------------------------------------------------
inline bool Vec3::operator <= ( const Vec3& rhs ) const
{
	if( x <= rhs.x && y <= rhs.y && z <= rhs.z )
		return true;
	return false;
}

/** Returns true if the vector's scalar components are all smaller
that the ones of the vector it is compared against.
*/
inline bool Vec3::operator >= ( const Vec3& rhs ) const
{
	if( x >= rhs.x && y >= rhs.y && z >= rhs.z )
		return true;
	return false;
}

//----------------------------------------------------------------
/** As normalise, except that this vector is unaffected and the
normalised vector is returned as a copy. */
inline Vec3 Vec3::normalisedCopy(void) const
{
	Vec3 ret = *this;
	ret.normalise();
	return ret;
}

//----------------------------------------------------------------

inline Vec3 Vec3::reflect(const Vec3& normal) const
{
	return Vec3( *this - ( 2 * this->dotProduct(normal) * normal ) );
}
//----------------------------------------------------------------

/** Returns true if this vector is zero length. */
inline bool Vec3::isZeroLength(void) const
{
	float sqlen = (x * x) + (y * y) + (z * z);
	return (sqlen < (1e-06 * 1e-06));

}

//----------------------------------------------------------------
inline Vec3 Vec3::makeFloor( const Vec3& cmp )
{
	if( cmp.x < x ) x = cmp.x;
	if( cmp.y < y ) y = cmp.y;
	if( cmp.z < z ) z = cmp.z;
	return *this;
}

inline float Vec3::absDotProduct(const Vec3& vec) const
{
	return abs(x * vec.x) + abs(y * vec.y) + abs(z * vec.z);
}

inline float Vec3::dotProduct(const Vec3& vec) const
{
	return x * vec.x + y * vec.y + z * vec.z;
}

//----------------------------------------------------------------

inline float Vec3::length () const
{
	return sqrt( x * x + y * y + z * z );
}

//----------------------------------------------------------------

inline float Vec3::squaredLength () const
{
	return x * x + y * y + z * z;
}

//----------------------------------------------------------------

inline float Vec3::squaredDistance(const Vec3& rhs) const
{
	return (*this - rhs).squaredLength();
}

//----------------------------------------------------------------
inline float Vec3::distance(const Vec3& rhs) const
{
	return (*this - rhs).length();
}



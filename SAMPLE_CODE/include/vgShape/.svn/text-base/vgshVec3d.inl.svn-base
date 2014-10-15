inline Vec3d Vec3d::makeCeil( const Vec3d& cmp )
{
	if( cmp.x > x ) x = cmp.x;
	if( cmp.y > y ) y = cmp.y;
	if( cmp.z > z ) z = cmp.z;
	return *this;
}
inline Vec3d Vec3d::ceilProduct( const Vec3d& c ) const
{
	Vec3d cmp = c;
	if( cmp.x < x ) cmp.x = x;
	if( cmp.y < y ) cmp.y = y;
	if( cmp.z < z ) cmp.z = z;
	return cmp;
}
inline Vec3d Vec3d::floorProduct( const Vec3d& c ) const
{
	Vec3d cmp = c;
	if( cmp.x > x ) cmp.x = x;
	if( cmp.y > y ) cmp.y = y;
	if( cmp.z > z ) cmp.z = z;
	return cmp;
}
//----------------------------------------------------------------
inline Vec3d Vec3d::perpendicular(void) const
{
	static const double fSquareZero = 1e-06f * 1e-06f;

	Vec3d perp = this->crossProduct( Vec3d::UNIT_X );

	// Check length
	if( perp.squaredLength() < fSquareZero )
	{
		/* This vector is the Y axis multiplied by a scalar, so we have
		to use another axis.
		*/
		perp = this->crossProduct( Vec3d::UNIT_Y );
	}

	return perp;
}
//---------------------------------------------------------------
inline double Vec3d::operator [] ( const size_t i ) const
{
	assert( i < 3 );

	return *(&x+i);
}

inline double& Vec3d::operator [] ( const size_t i )
{
	assert( i < 3 );

	return *(&x+i);
}

//----------------------------------------------------------------
///operator操作函数重写
inline Vec3d& Vec3d::operator = ( const Vec3d& rkVector )
{
	x = rkVector.x;
	y = rkVector.y;
	z = rkVector.z;

	return *this;
}

inline Vec3d& Vec3d::operator = ( const double fScaler )
{
	x = fScaler;
	y = fScaler;
	z = fScaler;

	return *this;
}
//----------------------------------------------------------------
inline bool Vec3d::operator == ( const Vec3d& rkVector ) const
{
	return ( x == rkVector.x && y == rkVector.y && z == rkVector.z );
}

inline bool Vec3d::operator != ( const Vec3d& rkVector ) const
{
	return ( x != rkVector.x || y != rkVector.y || z != rkVector.z );
}
inline Vec3d Vec3d::operator + ( const Vec3d& rkVector ) const
{
	return Vec3d(
		x + rkVector.x,
		y + rkVector.y,
		z + rkVector.z);
}

inline Vec3d Vec3d::operator - ( const Vec3d& rkVector ) const
{
	return Vec3d(
		x - rkVector.x,
		y - rkVector.y,
		z - rkVector.z);
}
inline Vec3d Vec3d::operator * ( const double fScalar ) const
{
	return Vec3d(
		x * fScalar,
		y * fScalar,
		z * fScalar);
}
//----------------------------------------------------------------


inline Vec3d Vec3d::operator / ( const double fScalar ) const
{
	assert( fScalar != 0.0 );

	double fInv = 1.0f / fScalar;

	return Vec3d(
		x * fInv,
		y * fInv,
		z * fInv);
}
//----------------------------------------------------------------
inline const Vec3d& Vec3d::operator + () const
{
	return *this;
}

inline Vec3d Vec3d::operator - () const
{
	return Vec3d(-x, -y, -z);
}
//----------------------------------------------------------------
///当操作数为做操作数时
inline Vec3d operator * ( const double fScalar, const Vec3d& rkVector )
{
	return Vec3d(
		fScalar * rkVector.x,
		fScalar * rkVector.y,
		fScalar * rkVector.z);
}

inline Vec3d Vec3d::operator * (const Vec3d& rkVector) const
{
	return Vec3d(
		x * rkVector.x,
		y * rkVector.y,
		z * rkVector.z);
}

inline Vec3d operator / ( const double fScalar, const Vec3d& rkVector )
{
	return Vec3d(
		fScalar / rkVector.x,
		fScalar / rkVector.y,
		fScalar / rkVector.z);
}

inline Vec3d Vec3d::operator / ( const Vec3d& rkVec) const
{
	return Vec3d(x / rkVec.x, 
		y / rkVec.y,
		z / rkVec.z);
}

inline Vec3d operator + (const Vec3d& lhs, const double rhs)
{
	return Vec3d(
		lhs.x + rhs,
		lhs.y + rhs,
		lhs.z + rhs);
}

inline Vec3d operator + (const double lhs, const Vec3d& rhs)
{
	return Vec3d(
		lhs + rhs.x,
		lhs + rhs.y,
		lhs + rhs.z);
}

inline Vec3d operator - (const Vec3d& lhs, const double rhs)
{
	return Vec3d(
		lhs.x - rhs,
		lhs.y - rhs,
		lhs.z - rhs);
}

inline Vec3d operator - (const double lhs, const Vec3d& rhs)
{
	return Vec3d(
		lhs - rhs.x,
		lhs - rhs.y,
		lhs - rhs.z);
}
//----------------------------------------------------------------
inline Vec3d& Vec3d::operator += ( const Vec3d& rkVector )
{
	x += rkVector.x;
	y += rkVector.y;
	z += rkVector.z;

	return *this;
}

inline Vec3d& Vec3d::operator += ( const double fScalar )
{
	x += fScalar;
	y += fScalar;
	z += fScalar;
	return *this;
}

inline Vec3d& Vec3d::operator -= ( const Vec3d& rkVector )
{
	x -= rkVector.x;
	y -= rkVector.y;
	z -= rkVector.z;

	return *this;
}

inline Vec3d& Vec3d::operator -= ( const double fScalar )
{
	x -= fScalar;
	y -= fScalar;
	z -= fScalar;
	return *this;
}

inline Vec3d& Vec3d::operator *= ( const double fScalar )
{
	x *= fScalar;
	y *= fScalar;
	z *= fScalar;
	return *this;
}

inline Vec3d& Vec3d::operator *= ( const Vec3d& rkVector )
{
	x *= rkVector.x;
	y *= rkVector.y;
	z *= rkVector.z;

	return *this;
}

inline Vec3d& Vec3d::operator /= ( const double fScalar )
{
	assert( fScalar != 0.0f );

	double fInv = 1.0f / fScalar;

	x *= fInv;
	y *= fInv;
	z *= fInv;

	return *this;
}

inline Vec3d& Vec3d::operator /= ( const Vec3d& rkVector )
{
	x /= rkVector.x;
	y /= rkVector.y;
	z /= rkVector.z;

	return *this;
}
//----------------------------------------------------------------
inline double Vec3d::normalise()
{
	double fLength = sqrt( x * x + y * y + z * z );

	// Will also work for zero-sized vectors, but will change nothing
	if ( fLength > 1e-08 )
	{
		double fInvLength = 1.0f / fLength;
		x *= fInvLength;
		y *= fInvLength;
		z *= fInvLength;
	}

	return fLength;
}
//----------------------------------------------------------------

inline Vec3d& Vec3d::normalisedRef()
{
	normalise();
	return *this;
}
//----------------------------------------------------------------

///计算叉乘
inline Vec3d Vec3d::crossProduct( const Vec3d& rkVector ) const
{
	return Vec3d(
		y * rkVector.z - z * rkVector.y,
		z * rkVector.x - x * rkVector.z,
		x * rkVector.y - y * rkVector.x);
}
//----------------------------------------------------------------
inline Vec3d Vec3d::midPoint( const Vec3d& vec /*= Vec3d()*/ ) const
{
	return Vec3d(
		( x + vec.x ) * 0.5f,
		( y + vec.y ) * 0.5f,
		( z + vec.z ) * 0.5f );
}

//----------------------------------------------------------------


inline bool Vec3d::operator < ( const Vec3d& rhs ) const
{
	if( x < rhs.x && y < rhs.y && z < rhs.z )
		return true;
	return false;
}

inline bool Vec3d::operator > ( const Vec3d& rhs ) const
{
	if( x > rhs.x && y > rhs.y && z > rhs.z )
		return true;
	return false;
}
//----------------------------------------------------------------
inline bool Vec3d::operator <= ( const Vec3d& rhs ) const
{
	if( x <= rhs.x && y <= rhs.y && z <= rhs.z )
		return true;
	return false;
}

/** Returns true if the vector's scalar components are all smaller
that the ones of the vector it is compared against.
*/
inline bool Vec3d::operator >= ( const Vec3d& rhs ) const
{
	if( x >= rhs.x && y >= rhs.y && z >= rhs.z )
		return true;
	return false;
}

//----------------------------------------------------------------
/** As normalise, except that this vector is unaffected and the
normalised vector is returned as a copy. */
inline Vec3d Vec3d::normalisedCopy(void) const
{
	Vec3d ret = *this;
	ret.normalise();
	return ret;
}

//----------------------------------------------------------------

inline Vec3d Vec3d::reflect(const Vec3d& normal) const
{
	return Vec3d( *this - ( 2 * this->dotProduct(normal) * normal ) );
}
//----------------------------------------------------------------

/** Returns true if this vector is zero length. */
inline bool Vec3d::isZeroLength(void) const
{
	double sqlen = (x * x) + (y * y) + (z * z);
	return (sqlen < (1e-06 * 1e-06));

}

//----------------------------------------------------------------
inline Vec3d Vec3d::makeFloor( const Vec3d& cmp )
{
	if( cmp.x < x ) x = cmp.x;
	if( cmp.y < y ) y = cmp.y;
	if( cmp.z < z ) z = cmp.z;
	return *this;
}

inline double Vec3d::absDotProduct(const Vec3d& vec) const
{
	return abs(x * vec.x) + abs(y * vec.y) + abs(z * vec.z);
}

inline double Vec3d::dotProduct(const Vec3d& vec) const
{
	return x * vec.x + y * vec.y + z * vec.z;
}

//----------------------------------------------------------------

inline double Vec3d::length () const
{
	return sqrt( x * x + y * y + z * z );
}

//----------------------------------------------------------------

inline double Vec3d::squaredLength () const
{
	return x * x + y * y + z * z;
}

//----------------------------------------------------------------

inline double Vec3d::squaredDistance(const Vec3d& rhs) const
{
	return (*this - rhs).squaredLength();
}

//----------------------------------------------------------------
inline double Vec3d::distance(const Vec3d& rhs) const
{
	return (*this - rhs).length();
}



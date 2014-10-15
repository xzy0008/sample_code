inline Vector3 Vector3::makeCeil( const Vector3& cmp )
{
	if( cmp.x > x ) x = cmp.x;
	if( cmp.y > y ) y = cmp.y;
	if( cmp.z > z ) z = cmp.z;
	return *this;
}
inline Vector3 Vector3::ceilProduct( const Vector3& c ) const
{
	Vector3 cmp = c;
	if( cmp.x < x ) cmp.x = x;
	if( cmp.y < y ) cmp.y = y;
	if( cmp.z < z ) cmp.z = z;
	return cmp;
}
inline Vector3 Vector3::floorProduct( const Vector3& c ) const
{
	Vector3 cmp = c;
	if( cmp.x > x ) cmp.x = x;
	if( cmp.y > y ) cmp.y = y;
	if( cmp.z > z ) cmp.z = z;
	return cmp;
}
//----------------------------------------------------------------
inline Vector3 Vector3::perpendicular(void) const
{
	static const Real fSquareZero = 1e-06 * 1e-06;

	Vector3 perp = this->crossProduct( Vector3::UNIT_X );

	// Check length
	if( perp.squaredLength() < fSquareZero )
	{
		/* This vector is the Y axis multiplied by a scalar, so we have
		to use another axis.
		*/
		perp = this->crossProduct( Vector3::UNIT_Y );
	}

	return perp;
}
//---------------------------------------------------------------
inline Real Vector3::operator [] ( const size_t i ) const
{
	assert( i < 3 );

	return *(&x+i);
}

inline Real& Vector3::operator [] ( const size_t i )
{
	assert( i < 3 );

	return *(&x+i);
}

///求地址操作
inline Real* Vector3::ptr()
{
	return &x;
}
inline const Real* Vector3::ptr() const
{
	return &x;
}
//----------------------------------------------------------------
///operator操作函数重写
inline Vector3& Vector3::operator = ( const Vector3& rkVector )
{
	x = rkVector.x;
	y = rkVector.y;
	z = rkVector.z;

	return *this;
}

inline Vector3& Vector3::operator = ( const vgKernel::Vec3& rkVector )
{
	x = rkVector.x;
	y = rkVector.y;
	z = rkVector.z;

	return *this;
}

inline Vector3& Vector3::operator = ( const Real fScaler )
{
	x = fScaler;
	y = fScaler;
	z = fScaler;

	return *this;
}
//----------------------------------------------------------------
inline bool Vector3::operator == ( const Vector3& rkVector ) const
{
	return ( x == rkVector.x && y == rkVector.y && z == rkVector.z );
}

inline bool Vector3::operator != ( const Vector3& rkVector ) const
{
	return ( x != rkVector.x || y != rkVector.y || z != rkVector.z );
}
inline Vector3 Vector3::operator + ( const Vector3& rkVector ) const
{
	return Vector3(
		x + rkVector.x,
		y + rkVector.y,
		z + rkVector.z);
}

inline Vector3 Vector3::operator - ( const Vector3& rkVector ) const
{
	return Vector3(
		x - rkVector.x,
		y - rkVector.y,
		z - rkVector.z);
}
inline Vector3 Vector3::operator * ( const Real fScalar ) const
{
	return Vector3(
		x * fScalar,
		y * fScalar,
		z * fScalar);
}
//----------------------------------------------------------------
///一般用不到
inline Vector3 Vector3::operator * ( const Vector3& rhs) const
{
	return Vector3(
		x * rhs.x,
		y * rhs.y,
		z * rhs.z);
}

inline Vector3 Vector3::operator / ( const Real fScalar ) const
{
	assert( fScalar != 0.0 );

	Real fInv = 1.0 / fScalar;

	return Vector3(
		x * fInv,
		y * fInv,
		z * fInv);
}

inline Vector3 Vector3::operator / ( const Vector3& rhs) const
{
	return Vector3(
		x / rhs.x,
		y / rhs.y,
		z / rhs.z);
}

//----------------------------------------------------------------
inline const Vector3& Vector3::operator + () const
{
	return *this;
}

inline Vector3 Vector3::operator - () const
{
	return Vector3(-x, -y, -z);
}
//----------------------------------------------------------------
///当操作数为做操作数时
inline Vector3 operator * ( const Real fScalar, const Vector3& rkVector )
{
	return Vector3(
		fScalar * rkVector.x,
		fScalar * rkVector.y,
		fScalar * rkVector.z);
}

inline Vector3 operator / ( const Real fScalar, const Vector3& rkVector )
{
	return Vector3(
		fScalar / rkVector.x,
		fScalar / rkVector.y,
		fScalar / rkVector.z);
}

inline Vector3 operator + (const Vector3& lhs, const Real rhs)
{
	return Vector3(
		lhs.x + rhs,
		lhs.y + rhs,
		lhs.z + rhs);
}

inline Vector3 operator + (const Real lhs, const Vector3& rhs)
{
	return Vector3(
		lhs + rhs.x,
		lhs + rhs.y,
		lhs + rhs.z);
}

inline Vector3 operator - (const Vector3& lhs, const Real rhs)
{
	return Vector3(
		lhs.x - rhs,
		lhs.y - rhs,
		lhs.z - rhs);
}

inline Vector3 operator - (const Real lhs, const Vector3& rhs)
{
	return Vector3(
		lhs - rhs.x,
		lhs - rhs.y,
		lhs - rhs.z);
}
//----------------------------------------------------------------
inline Vector3& Vector3::operator += ( const Vector3& rkVector )
{
	x += rkVector.x;
	y += rkVector.y;
	z += rkVector.z;

	return *this;
}

inline Vector3& Vector3::operator += ( const Real fScalar )
{
	x += fScalar;
	y += fScalar;
	z += fScalar;
	return *this;
}

inline Vector3& Vector3::operator -= ( const Vector3& rkVector )
{
	x -= rkVector.x;
	y -= rkVector.y;
	z -= rkVector.z;

	return *this;
}

inline Vector3& Vector3::operator -= ( const Real fScalar )
{
	x -= fScalar;
	y -= fScalar;
	z -= fScalar;
	return *this;
}

inline Vector3& Vector3::operator *= ( const Real fScalar )
{
	x *= fScalar;
	y *= fScalar;
	z *= fScalar;
	return *this;
}

inline Vector3& Vector3::operator *= ( const Vector3& rkVector )
{
	x *= rkVector.x;
	y *= rkVector.y;
	z *= rkVector.z;

	return *this;
}

inline Vector3& Vector3::operator /= ( const Real fScalar )
{
	assert( fScalar != 0.0 );

	Real fInv = 1.0 / fScalar;

	x *= fInv;
	y *= fInv;
	z *= fInv;

	return *this;
}

inline Vector3& Vector3::operator /= ( const Vector3& rkVector )
{
	x /= rkVector.x;
	y /= rkVector.y;
	z /= rkVector.z;

	return *this;
}
//----------------------------------------------------------------
inline Real Vector3::normalise()
{
	Real fLength = Math::Sqrt( x * x + y * y + z * z );

	// Will also work for zero-sized vectors, but will change nothing
	if ( fLength > 1e-08 )
	{
		Real fInvLength = 1.0 / fLength;
		x *= fInvLength;
		y *= fInvLength;
		z *= fInvLength;
	}

	return fLength;
}
//----------------------------------------------------------------

inline Vector3& Vector3::normalisedRef()
{
	this->normalise();
	return *this;
}
//----------------------------------------------------------------

///计算叉乘
inline Vector3 Vector3::crossProduct( const Vector3& rkVector ) const
{
	return Vector3(
		y * rkVector.z - z * rkVector.y,
		z * rkVector.x - x * rkVector.z,
		x * rkVector.y - y * rkVector.x);
}
//----------------------------------------------------------------
inline Vector3 Vector3::midPoint( const Vector3& vec /*= Vector3()*/ ) const
{
	return Vector3(
		( x + vec.x ) * 0.5,
		( y + vec.y ) * 0.5,
		( z + vec.z ) * 0.5 );
}

//----------------------------------------------------------------

/** Returns true if the vector's scalar components are all greater
that the ones of the vector it is compared against.
*/
inline bool Vector3::operator < ( const Vector3& rhs ) const
{
	if( x < rhs.x && y < rhs.y && z < rhs.z )
		return true;
	return false;
}

/** Returns true if the vector's scalar components are all smaller
that the ones of the vector it is compared against.
*/
inline bool Vector3::operator > ( const Vector3& rhs ) const
{
	if( x > rhs.x && y > rhs.y && z > rhs.z )
		return true;
	return false;
}
//----------------------------------------------------------------
inline bool Vector3::operator <= ( const Vector3& rhs ) const
{
	if( x <= rhs.x && y <= rhs.y && z <= rhs.z )
		return true;
	return false;
}

/** Returns true if the vector's scalar components are all smaller
that the ones of the vector it is compared against.
*/
inline bool Vector3::operator >= ( const Vector3& rhs ) const
{
	if( x >= rhs.x && y >= rhs.y && z >= rhs.z )
		return true;
	return false;
}

//----------------------------------------------------------------
inline bool Vector3::positionEquals(const Vector3& rhs, Real tolerance /*= 1e-03*/) const
{
	return Math::RealEqual(x, rhs.x, tolerance) &&
		Math::RealEqual(y, rhs.y, tolerance) &&
		Math::RealEqual(z, rhs.z, tolerance);

}

//----------------------------------------------------------------
/** As normalise, except that this vector is unaffected and the
normalised vector is returned as a copy. */
inline Vector3 Vector3::normalisedCopy(void) const
{
	Vector3 ret = *this;
	ret.normalise();
	return ret;
}

//----------------------------------------------------------------

inline Vector3 Vector3::reflect(const Vector3& normal) const
{
	return Vector3( *this - ( 2 * this->dotProduct(normal) * normal ) );
}
//----------------------------------------------------------------

/** Returns true if this vector is zero length. */
inline bool Vector3::isZeroLength(void) const
{
	Real sqlen = (x * x) + (y * y) + (z * z);
	return (sqlen < (1e-06 * 1e-06));

}

//----------------------------------------------------------------
inline Vector3 Vector3::makeFloor( const Vector3& cmp )
{
	if( cmp.x < x ) x = cmp.x;
	if( cmp.y < y ) y = cmp.y;
	if( cmp.z < z ) z = cmp.z;
	return *this;
}


//----------------------------------------------------------------

/** Calculates the absolute dot (scalar) product of this vector with another.
@remarks
This function work similar dotProduct, except it use absolute value
of each component of the vector to computing.
@param
vec Vector with which to calculate the absolute dot product (together
with this one).
@returns
A Real representing the absolute dot product value.
*/
inline Real Vector3::absDotProduct(const Vector3& vec) const
{
	return Math::Abs(x * vec.x) + Math::Abs(y * vec.y) + Math::Abs(z * vec.z);
}


//----------------------------------------------------------------

/** Calculates the dot (scalar) product of this vector with another.
@remarks
The dot product can be used to calculate the angle between 2
vectors. If both are unit vectors, the dot product is the
cosine of the angle; otherwise the dot product must be
divided by the product of the lengths of both vectors to get
the cosine of the angle. This result can further be used to
calculate the distance of a point from a plane.
@param
vec Vector with which to calculate the dot product (together
with this one).
@returns
A float representing the dot product value.
*/
inline Real Vector3::dotProduct(const Vector3& vec) const
{
	return x * vec.x + y * vec.y + z * vec.z;
}

//----------------------------------------------------------------

inline Real Vector3::length () const
{
	return Math::Sqrt( x * x + y * y + z * z );
}

//----------------------------------------------------------------

inline Real Vector3::squaredLength () const
{
	return x * x + y * y + z * z;
}

//----------------------------------------------------------------

inline Real Vector3::squaredDistance(const Vector3& rhs) const
{
	return (*this - rhs).squaredLength();
}

//----------------------------------------------------------------
inline Real Vector3::distance(const Vector3& rhs) const
{
	return (*this - rhs).length();
}


//----------------------------------------------------------------

///计算叉乘的符号重载
inline Vector3 Vector3::operator ^ ( const Vector3 &rhs ) const
{
	return this->crossProduct( rhs );
}


//----------------------------------------------------------------

///输出函数,方便测试
inline /*VgfExport*/ StdOStream&  operator <<
( StdOStream& o, const Vector3& v )
{
	//std::cout.setf(std::ios::fixed);
	o << _T("Vector3( ") <<  v.x << _T(" , ") << v.y << _T(" , ") << v.z << _T(" )");
	return o;
}

//----------------------------------------------------------------


inline StdIStream& operator >> ( StdIStream& in , Vector3& v )
{
	float _X;
	float _Y;
	float _Z;

	TCHAR s1[] = _T("Vector3( ");
	String cs1(s1);

	TCHAR s2[] = _T(" , ");
	String cs2(s2);

	TCHAR s3[] = _T(" )");
	String cs3(s3);

	in.read( s1 , sizeof(s1)/sizeof(TCHAR) - 1 );
	assert( cs1 == s1 );

	in >> _X ;

	in.read( s2 , sizeof(s2)/sizeof(TCHAR) - 1 );
	assert( cs2 == s2 );

	in >> _Y ;

	in.read( s2 , sizeof(s2)/sizeof(TCHAR) - 1 );
	assert( cs2 == s2 );

	in >> _Z ;

	in.read( s3 , sizeof(s3)/sizeof(TCHAR) - 1 );
	assert( cs3 == s3 );

	v.x = _X;
	v.y = _Y;
	v.z = _Z;

	return in;
}


#ifdef UNICODE

///输出函数,方便测试
inline /*VgfExport*/ std::ostream&  operator <<
( std::ostream& o, const Vector3& v )
{
	//std::cout.setf(std::ios::fixed);
	o << "Vector3( " <<  v.x << " , " << v.y << " , " << v.z << " )";
	return o;
}

//----------------------------------------------------------------


inline std::istream& operator >> ( std::istream& in , Vector3& v )
{
	float _X;
	float _Y;
	float _Z;

	char s1[] = "Vector3( ";
	MbsString cs1(s1);

	char s2[] = " , ";
	MbsString cs2(s2);

	char s3[] = (" )");
	MbsString cs3(s3);

	in.read( s1 , sizeof(s1)/sizeof(char) - 1 );
	assert( cs1 == s1 );

	in >> _X ;

	in.read( s2 , sizeof(s2)/sizeof(char) - 1 );
	assert( cs2 == s2 );

	in >> _Y ;

	in.read( s2 , sizeof(s2)/sizeof(char) - 1 );
	assert( cs2 == s2 );

	in >> _Z ;

	in.read( s3 , sizeof(s3)/sizeof(char) - 1 );
	assert( cs3 == s3 );

	v.x = _X;
	v.y = _Y;
	v.z = _Z;

	return in;
}

#endif
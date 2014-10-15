//----------------------------------------------------------------


inline void Vector2::makeFloor( const Vector2& cmp )
{
	if( cmp.x < x ) x = cmp.x;
	if( cmp.y < y ) y = cmp.y;
}

//----------------------------------------------------------------

inline Real Vector2::operator [] ( const size_t i ) const
{
	assert( i < 2 );

	return *(&x+i);
}

inline Real& Vector2::operator [] ( const size_t i )
{
	assert( i < 2 );

	return *(&x+i);
}
//----------------------------------------------------------------
inline Vector2& Vector2::operator = ( const Vector2& rkVector )
{
	x = rkVector.x;
	y = rkVector.y;

	return *this;
}

inline Vector2& Vector2::operator = ( const Real fScalar)
{
	x = fScalar;
	y = fScalar;

	return *this;
}

inline bool Vector2::operator == ( const Vector2& rkVector ) const
{
	return ( x == rkVector.x && y == rkVector.y );
}

inline bool Vector2::operator != ( const Vector2& rkVector ) const
{
	return ( x != rkVector.x || y != rkVector.y  );
}

//----------------------------------------------------------------
inline Vector2 Vector2::operator + ( const Vector2& rkVector ) const
{
	return Vector2(
		x + rkVector.x,
		y + rkVector.y);
}

inline Vector2 Vector2::operator - ( const Vector2& rkVector ) const
{
	return Vector2(
		x - rkVector.x,
		y - rkVector.y);
}

inline Vector2 Vector2::operator * ( const Real fScalar ) const
{
	return Vector2(
		x * fScalar,
		y * fScalar);
}

inline Vector2 Vector2::operator * ( const Vector2& rhs) const
{
	return Vector2(
		x * rhs.x,
		y * rhs.y);
}

inline Vector2 Vector2::operator / ( const Real fScalar ) const
{
	assert( fScalar != 0.0 );

	Real fInv = 1.0 / fScalar;

	return Vector2(
		x * fInv,
		y * fInv);
}

inline Vector2 Vector2::operator / ( const Vector2& rhs) const
{
	return Vector2(
		x / rhs.x,
		y / rhs.y);
}

inline const Vector2& Vector2::operator + () const
{
	return *this;
}

inline Vector2 Vector2::operator - () const
{
	return Vector2(-x, -y);
}

//----------------------------------------------------------------
// overloaded operators to help Vector2
inline  Vector2 operator * ( const Real fScalar, const Vector2& rkVector )
{
	return Vector2(
		fScalar * rkVector.x,
		fScalar * rkVector.y);
}

inline  Vector2 operator / ( const Real fScalar, const Vector2& rkVector )
{
	return Vector2(
		fScalar / rkVector.x,
		fScalar / rkVector.y);
}

inline  Vector2 operator + (const Vector2& lhs, const Real rhs)
{
	return Vector2(
		lhs.x + rhs,
		lhs.y + rhs);
}

inline  Vector2 operator + (const Real lhs, const Vector2& rhs)
{
	return Vector2(
		lhs + rhs.x,
		lhs + rhs.y);
}

inline  Vector2 operator - (const Vector2& lhs, const Real rhs)
{
	return Vector2(
		lhs.x - rhs,
		lhs.y - rhs);
}

inline  Vector2 operator - (const Real lhs, const Vector2& rhs)
{
	return Vector2(
		lhs - rhs.x,
		lhs - rhs.y);
}

//----------------------------------------------------------------

// arithmetic updates
inline Vector2& Vector2::operator += ( const Vector2& rkVector )
{
	x += rkVector.x;
	y += rkVector.y;

	return *this;
}

inline Vector2& Vector2::operator += ( const Real fScaler )
{
	x += fScaler;
	y += fScaler;

	return *this;
}

inline Vector2& Vector2::operator -= ( const Vector2& rkVector )
{
	x -= rkVector.x;
	y -= rkVector.y;

	return *this;
}

inline Vector2& Vector2::operator -= ( const Real fScaler )
{
	x -= fScaler;
	y -= fScaler;

	return *this;
}

inline Vector2& Vector2::operator *= ( const Real fScalar )
{
	x *= fScalar;
	y *= fScalar;

	return *this;
}

inline Vector2& Vector2::operator *= ( const Vector2& rkVector )
{
	x *= rkVector.x;
	y *= rkVector.y;

	return *this;
}

inline Vector2& Vector2::operator /= ( const Real fScalar )
{
	assert( fScalar != 0.0 );

	Real fInv = 1.0 / fScalar;

	x *= fInv;
	y *= fInv;

	return *this;
}

inline Vector2& Vector2::operator /= ( const Vector2& rkVector )
{
	x /= rkVector.x;
	y /= rkVector.y;

	return *this;
}
//----------------------------------------------------------------
inline Real Vector2::length () const
{
	return Math::Sqrt( x * x + y * y );
}

//----------------------------------------------------------------
inline Real Vector2::squaredLength () const
{
	return x * x + y * y;
}

//----------------------------------------------------------------
inline Real Vector2::dotProduct(const Vector2& vec) const
{
	return x * vec.x + y * vec.y;
}


//----------------------------------------------------------------

inline Real Vector2::normalise()
{
	Real fLength = Math::Sqrt( x * x + y * y);

	// Will also work for zero-sized vectors, but will change nothing
	if ( fLength > 1e-08 )
	{
		Real fInvLength = 1.0 / fLength;
		x *= fInvLength;
		y *= fInvLength;
	}

	return fLength;
}
//----------------------------------------------------------------

inline Vector2& Vector2::normalisedRef()
{
	this->normalise();
	return *this;
}
//----------------------------------------------------------------
inline Vector2 Vector2::midPoint( const Vector2& vec ) const
{
	return Vector2(
		( x + vec.x ) * 0.5,
		( y + vec.y ) * 0.5 );
}


//----------------------------------------------------------------
inline bool Vector2::operator < ( const Vector2& rhs ) const
{
	if( x < rhs.x && y < rhs.y )
		return true;
	return false;
}

//----------------------------------------------------------------
inline bool Vector2::operator > ( const Vector2& rhs ) const
{
	if( x > rhs.x && y > rhs.y )
		return true;
	return false;
}

//----------------------------------------------------------------
inline void Vector2::makeCeil( const Vector2& cmp )
{
	if( cmp.x > x ) x = cmp.x;
	if( cmp.y > y ) y = cmp.y;
}


//----------------------------------------------------------------
inline Vector2 Vector2::perpendicular(void) const
{
	return Vector2 (-y, x);
}

//----------------------------------------------------------------

inline Real Vector2::crossProduct( const Vector2& rkVector ) const
{
	return x * rkVector.y - y * rkVector.x;
}
//----------------------------------------------------------------
inline Vector2 Vector2::randomDeviant(
							 Real angle) const
{

	angle *=  Math::UnitRandom() * Math::TWO_PI;
	Real cosa = cos(angle);
	Real sina = sin(angle);
	return  Vector2(cosa * x - sina * y,
		sina * x + cosa * y);
}

//----------------------------------------------------------------
inline bool Vector2::isZeroLength(void) const
{
	Real sqlen = (x * x) + (y * y);
	return (sqlen < (1e-06 * 1e-06));

}

//----------------------------------------------------------------
inline Vector2 Vector2::normalisedCopy(void) const
{
	Vector2 ret = *this;
	ret.normalise();
	return ret;
}

//----------------------------------------------------------------
inline Vector2 Vector2::reflect(const Vector2& normal) const
{
	return Vector2( *this - ( 2 * this->dotProduct(normal) * normal ) );
}

//----------------------------------------------------------------

inline VgfExport   StdOStream& operator <<
( StdOStream& o, const Vector2& v )
{
	o << _T("Vector2( ") << v.x << _T(" , ") << v.y <<  _T(" )");
	return o;
}
//----------------------------------------------------------------
/// Pointer accessor for direct copying
inline Real* Vector2::ptr()
{
	return &x;
}
/// Pointer accessor for direct copying
inline const Real* Vector2::ptr() const
{
	return &x;
}

//----------------------------------------------------------------

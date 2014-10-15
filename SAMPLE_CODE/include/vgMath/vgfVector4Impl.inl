// arithmetic updates
inline Vector4& Vector4::operator += ( const Vector4& rkVector )
{
	x += rkVector.x;
	y += rkVector.y;
	z += rkVector.z;
	w += rkVector.w;

	return *this;
}

inline Vector4& Vector4::operator -= ( const Vector4& rkVector )
{
	x -= rkVector.x;
	y -= rkVector.y;
	z -= rkVector.z;
	w -= rkVector.w;

	return *this;
}

inline Vector4& Vector4::operator *= ( const Real fScalar )
{
	x *= fScalar;
	y *= fScalar;
	z *= fScalar;
	w *= fScalar;
	return *this;
}

inline Vector4& Vector4::operator += ( const Real fScalar )
{
	x += fScalar;
	y += fScalar;
	z += fScalar;
	w += fScalar;
	return *this;
}

inline Vector4& Vector4::operator -= ( const Real fScalar )
{
	x -= fScalar;
	y -= fScalar;
	z -= fScalar;
	w -= fScalar;
	return *this;
}

inline Vector4& Vector4::operator *= ( const Vector4& rkVector )
{
	x *= rkVector.x;
	y *= rkVector.y;
	z *= rkVector.z;
	w *= rkVector.w;

	return *this;
}

inline Vector4& Vector4::operator /= ( const Real fScalar )
{
	assert( fScalar != 0.0 );

	Real fInv = 1.0 / fScalar;

	x *= fInv;
	y *= fInv;
	z *= fInv;
	w *= fInv;

	return *this;
}

inline Vector4& Vector4::operator /= ( const Vector4& rkVector )
{
	x /= rkVector.x;
	y /= rkVector.y;
	z /= rkVector.z;
	w /= rkVector.w;

	return *this;
}

//----------------------------------------------------------------
/** Assigns the value of the other vector.
@param
rkVector The other vector
*/
inline Vector4& Vector4::operator = ( const Vector4& rkVector )
{
	x = rkVector.x;
	y = rkVector.y;
	z = rkVector.z;
	w = rkVector.w;

	return *this;
}

inline Vector4& Vector4::operator = ( const Real fScalar)
{
	x = fScalar;
	y = fScalar;
	z = fScalar;
	w = fScalar;
	return *this;
}

inline bool Vector4::operator == ( const Vector4& rkVector ) const
{
	return ( x == rkVector.x &&
		y == rkVector.y &&
		z == rkVector.z &&
		w == rkVector.w );
}

inline bool Vector4::operator != ( const Vector4& rkVector ) const
{
	return ( x != rkVector.x ||
		y != rkVector.y ||
		z != rkVector.z ||
		w != rkVector.w );
}

inline Vector4& Vector4::operator = (const Vector3& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	w = 1.0f;
	return *this;
}
//----------------------------------------------------------------
inline  Vector4 operator * ( const Real fScalar, const Vector4& rkVector )
{
	return Vector4(
		fScalar * rkVector.x,
		fScalar * rkVector.y,
		fScalar * rkVector.z,
		fScalar * rkVector.w);
}

inline  Vector4 operator / ( const Real fScalar, const Vector4& rkVector )
{
	return Vector4(
		fScalar / rkVector.x,
		fScalar / rkVector.y,
		fScalar / rkVector.z,
		fScalar / rkVector.w);
}

inline  Vector4 operator + (const Vector4& lhs, const Real rhs)
{
	return Vector4(
		lhs.x + rhs,
		lhs.y + rhs,
		lhs.z + rhs,
		lhs.w + rhs);
}

inline  Vector4 operator + (const Real lhs, const Vector4& rhs)
{
	return Vector4(
		lhs + rhs.x,
		lhs + rhs.y,
		lhs + rhs.z,
		lhs + rhs.w);
}

inline  Vector4 operator - (const Vector4& lhs, Real rhs)
{
	return Vector4(
		lhs.x - rhs,
		lhs.y - rhs,
		lhs.z - rhs,
		lhs.w - rhs);
}

inline  Vector4 operator - (const Real lhs, const Vector4& rhs)
{
	return Vector4(
		lhs - rhs.x,
		lhs - rhs.y,
		lhs - rhs.z,
		lhs - rhs.w);
}
//----------------------------------------------------------------
inline Vector4 Vector4::operator - () const
{
	return Vector4(
		-v[0],
		-v[1],
		-v[2],
		-v[3]);
}


//----------------------------------------------------------------
inline const Vector4& Vector4::operator + () const
{
	return *this;
}


//----------------------------------------------------------------

/** Function for writing to a stream.
*/
inline VgfExport  StdOStream& operator <<
( StdOStream& o, const Vector4& v )
{
	o << _T("Vector4( ") << v.x
		<<_T(" , "  )<< v.y <<
		_T( " , " )<< v.z <<
		_T( " , " )<< v.w <<
		_T( " )" );
	return o;
}

//----------------------------------------------------------------

inline Real Vector4::dotProduct(const Vector4& vec) const
{
	return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
}

//----------------------------------------------------------------

/// Pointer accessor for direct copying
inline Real* Vector4::ptr()
{
	return &x;
}
/// Pointer accessor for direct copying
inline const Real* Vector4::ptr() const
{
	return &x;
}


//----------------------------------------------------------------
inline Real Vector4::operator [] ( const size_t i ) const
{
	assert( i < 4 );

	return *(&x+i);
}

inline Real& Vector4::operator [] ( const size_t i )
{
	assert( i < 4 );

	return *(&x+i);
}


//----------------------------------------------------------------



//----------------------------------------------------------------



//----------------------------------------------------------------



//----------------------------------------------------------------



//----------------------------------------------------------------



//----------------------------------------------------------------



//----------------------------------------------------------------



//----------------------------------------------------------------




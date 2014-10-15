inline Quaternion& Quaternion::operator= (const Quaternion& rkQ)
{
	w = rkQ.w;
	x = rkQ.x;
	y = rkQ.y;
	z = rkQ.z;
	return *this;
}
//----------------------------------------------------------------

//-----------------------------------------------------------------------
Quaternion Quaternion::operator+ (const Quaternion& rkQ) const
{
	return Quaternion(w+rkQ.w,x+rkQ.x,y+rkQ.y,z+rkQ.z);
}
//-----------------------------------------------------------------------
Quaternion Quaternion::operator- (const Quaternion& rkQ) const
{
	return Quaternion(w-rkQ.w,x-rkQ.x,y-rkQ.y,z-rkQ.z);
}
//-----------------------------------------------------------------------
Quaternion Quaternion::operator* (const Quaternion& rkQ) const
{
	// NOTE:  Multiplication is not generally commutative, so in most
	// cases p*q != q*p.

	return Quaternion
		(
		w * rkQ.w - x * rkQ.x - y * rkQ.y - z * rkQ.z,
		w * rkQ.x + x * rkQ.w + y * rkQ.z - z * rkQ.y,
		w * rkQ.y + y * rkQ.w + z * rkQ.x - x * rkQ.z,
		w * rkQ.z + z * rkQ.w + x * rkQ.y - y * rkQ.x
		);
}
//-----------------------------------------------------------------------
Quaternion Quaternion::operator* (Real fScalar) const
{
	return Quaternion(fScalar*w,fScalar*x,fScalar*y,fScalar*z);
}
//-----------------------------------------------------------------------
Quaternion operator* (Real fScalar, const Quaternion& rkQ)
{
	return Quaternion(fScalar*rkQ.w,fScalar*rkQ.x,fScalar*rkQ.y,
		fScalar*rkQ.z);
}
//-----------------------------------------------------------------------
Vector3 Quaternion::operator* (const Vector3& v) const
{
	// nVidia SDK implementation
	Vector3 uv, uuv;
	Vector3 qvec(x, y, z);
	uv = qvec.crossProduct(v);
	uuv = qvec.crossProduct(uv);
	uv *= (2.0f * w);
	uuv *= 2.0f;

	return v + uv + uuv;

}
//-----------------------------------------------------------------------
Quaternion Quaternion::operator- () const
{
	return Quaternion(-w,-x,-y,-z);
}


//----------------------------------------------------------------
/// Array accessor operator
inline Real Quaternion::operator [] ( const size_t i ) const
{
	assert( i < 4 );

	return *(&w+i);
}

/// Array accessor operator
inline Real& Quaternion::operator [] ( const size_t i )
{
	assert( i < 4 );

	return *(&w+i);
}

//----------------------------------------------------------------
/// Pointer accessor for direct copying
inline Real* Quaternion::ptr()
{
	return &w;
}

/// Pointer accessor for direct copying
inline const Real* Quaternion::ptr() const
{
	return &w;
}

//----------------------------------------------------------------
inline void Quaternion::ToAngleAxis (Degree& dAngle, Vector3& rkAxis) const
{
	Radian rAngle;
	ToAngleAxis ( rAngle, rkAxis );
	dAngle = rAngle;
}
inline Quaternion& Quaternion::FromAngleAxis (const Real& rfAngle, const Vector3& rkAxis) 
{
	 return FromAngleAxis ( Radian(rfAngle), rkAxis );
}
inline Quaternion& Quaternion::FromAngleAxis (const Degree& rfAngle, const Vector3& rkAxis) 
{
	return FromAngleAxis ( Radian(rfAngle), rkAxis );
}
inline void Quaternion::ToAngleAxis (Real& rfAngle, Vector3& rkAxis) const 
{
	Radian r;
	ToAngleAxis ( r, rkAxis );
	rfAngle = r.valueAngleUnits();
}
//-----------------------------------------------------------------------
inline Quaternion& Quaternion::FromAngleAxis (const Radian& rfAngle,
									   const Vector3& rkAxis)
{
	// assert:  axis[] is unit length
	//
	// The quaternion representing the rotation is
	//   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

	Radian fHalfAngle ( 0.5*rfAngle );
	Real fSin = Math::Sin(fHalfAngle);
	w = Math::Cos(fHalfAngle);
	x = fSin*rkAxis.x;
	y = fSin*rkAxis.y;
	z = fSin*rkAxis.z;

	return *this;
}
//----------------------------------------------------------------

//----------------------------------------------------------------------------
inline Quaternion Quaternion::operator/ (Real fScalar) const
{
	Quaternion kQuot;
	int i;

	if (fScalar != (Real)0.0)
	{
		Real fInvScalar = ((Real)1.0)/fScalar;
		for (i = 0; i < 4; i++)
		{
			kQuot.v[i] = fInvScalar*v[i];
		}
	}
	else
	{
		for (i = 0; i < 4; i++)
		{
			kQuot.v[i] = Math::MAX_REAL;
		}
	}

	return kQuot;
}
//----------------------------------------------------------------
//----------------------------------------------------------------------------

inline Quaternion& Quaternion::operator+= (const Quaternion& rkQ)
{
	for (int i = 0; i < 4; i++)
	{
		v[i] += rkQ.v[i];
	}
	return *this;
}
//----------------------------------------------------------------------------

inline Quaternion& Quaternion::operator-= (const Quaternion& rkQ)
{
	for (int i = 0; i < 4; i++)
	{
		v[i] -= rkQ.v[i];
	}
	return *this;
}
//----------------------------------------------------------------------------

inline Quaternion& Quaternion::operator*= (Real fScalar)
{
	for (int i = 0; i < 4; i++)
	{
		v[i] *= fScalar;
	}
	return *this;
}
//----------------------------------------------------------------------------

inline Quaternion& Quaternion::operator/= (Real fScalar)
{
	int i;

	if (fScalar != (Real)0.0)
	{
		Real fInvScalar = ((Real)1.0)/fScalar;
		for (i = 0; i < 4; i++)
		{
			v[i] *= fInvScalar;
		}
	}
	else
	{
		for (i = 0; i < 4; i++)
		{
			v[i] = Math::MAX_REAL;
		}
	}

	return *this;
}


//----------------------------------------------------------------
inline int Quaternion::compareArrays (const Quaternion& rkQ) const
{
	return memcmp(v,rkQ.v,4*sizeof(Real));
}

//----------------------------------------------------------------

//----------------------------------------------------------------------------

inline bool Quaternion::operator== (const Quaternion& rkQ) const
{
	return compareArrays(rkQ) == 0;
}
//----------------------------------------------------------------------------

inline bool Quaternion::operator!= (const Quaternion& rkQ) const
{
	return compareArrays(rkQ) != 0;
}
//----------------------------------------------------------------------------

inline bool Quaternion::operator< (const Quaternion& rkQ) const
{
	return compareArrays(rkQ) < 0;
}
//----------------------------------------------------------------------------

inline bool Quaternion::operator<= (const Quaternion& rkQ) const
{
	return compareArrays(rkQ) <= 0;
}
//----------------------------------------------------------------------------

inline bool Quaternion::operator> (const Quaternion& rkQ) const
{
	return compareArrays(rkQ) > 0;
}
//----------------------------------------------------------------------------

inline bool Quaternion::operator>= (const Quaternion& rkQ) const
{
	return compareArrays(rkQ) >= 0;
}

//----------------------------------------------------------------
//----------------------------------------------------------------------------
inline Real Quaternion::Length () const
{
	return Math::Sqrt(
		v[0]*v[0] +
		v[1]*v[1] +
		v[2]*v[2] +
		v[3]*v[3]);
}

//----------------------------------------------------------------
//----------------------------------------------------------------------------
Real Quaternion::SquaredLength () const
{
	return
		v[0]*v[0] +
		v[1]*v[1] +
		v[2]*v[2] +
		v[3]*v[3];
}

//----------------------------------------------------------------

//-----------------------------------------------------------------------
Radian Quaternion::getRoll(void) const
{
	return Radian(Math::ATan2(2*(x*y + w*z), w*w + x*x - y*y - z*z));
}
//-----------------------------------------------------------------------
Radian Quaternion::getPitch(void) const
{
	return Radian(Math::ATan2(2*(y*z + w*x), w*w - x*x - y*y + z*z));
}
//-----------------------------------------------------------------------
Radian Quaternion::getYaw(void) const
{
	return Radian(Math::ASin(-2*(x*z - w*y)));
}

//----------------------------------------------------------------
inline VgfExport StdOStream& operator <<
( StdOStream& o, const Quaternion& q )
{
	o << _T("Quaternion(") << q.w 
		<< _T(", ") << q.x 
		<< _T(", ") << q.y 
		<< _T(", ") << q.z << _T(")");
	return o;
}

//----------------------------------------------------------------


//----------------------------------------------------------------


//----------------------------------------------------------------


//----------------------------------------------------------------


//----------------------------------------------------------------


//----------------------------------------------------------------


//----------------------------------------------------------------


//----------------------------------------------------------------


//----------------------------------------------------------------


//----------------------------------------------------------------


//----------------------------------------------------------------


//----------------------------------------------------------------



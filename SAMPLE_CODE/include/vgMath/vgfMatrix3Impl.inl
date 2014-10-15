//----------------------------------------------------------------
inline   StdOStream& operator <<
( StdOStream& o, const Matrix3& v )
{
	const unsigned int w = 7;
	o << _T("\nMatrix3 { ") 
		<< std::setw(w) << v.m[0][0] << _T(" , ") << std::setw(w) << v.m[0][1] << _T(" , ") << std::setw(w) << v.m[0][2] << _T(" , ") << _T("\n          ") 
		<< std::setw(w) << v.m[1][0] << _T(" , ") << std::setw(w) << v.m[1][1] << _T(" , ") << std::setw(w) << v.m[1][2] << _T(" , ") << _T("\n          ")
		<< std::setw(w) << v.m[2][0] << _T(" , ") << std::setw(w) << v.m[2][1] << _T(" , ") << std::setw(w) << v.m[2][2] << _T(" }\n ");

	return o;
}

//----------------------------------------------------------------
inline Matrix3::Matrix3 (const Real arr[3][3])
{
	memcpy(m,arr,9*sizeof(Real));
}
inline Matrix3::Matrix3 (const Matrix3& rkMatrix)
{
	memcpy(m,rkMatrix.m,9*sizeof(Real));
}
//----------------------------------------------------------------

inline Real* Matrix3::operator[] (size_t iRow) const
{
	return (Real*)m[iRow];
}

//----------------------------------------------------------------

inline Matrix3& Matrix3::operator= (const Matrix3& rkMatrix)
{
	memcpy(m,rkMatrix.m,9*sizeof(Real));
	return *this;
}

//----------------------------------------------------------------

inline bool Matrix3::operator!= (const Matrix3& rkMatrix) const
{
	return compareArrays(rkMatrix) != 0;
}

//----------------------------------------------------------------

inline Matrix3& Matrix3::makeZero()
{
	m[0][0] = (Real)0.0;
	m[0][1] = (Real)0.0;
	m[0][2] = (Real)0.0;
	m[1][0] = (Real)0.0;
	m[1][1] = (Real)0.0;
	m[1][2] = (Real)0.0;
	m[2][0] = (Real)0.0;
	m[2][1] = (Real)0.0;
	m[2][2] = (Real)0.0;

	return *this;
}

//----------------------------------------------------------------
inline Matrix3& Matrix3::makeIdentity()
{
	m[0][0] = (Real)1.0;
	m[0][1] = (Real)0.0;
	m[0][2] = (Real)0.0;
	m[1][0] = (Real)0.0;
	m[1][1] = (Real)1.0;
	m[1][2] = (Real)0.0;
	m[2][0] = (Real)0.0;
	m[2][1] = (Real)0.0;
	m[2][2] = (Real)1.0;

	return *this;
}


//----------------------------------------------------------------

///设置对角线上的三个数,其他的为0.
inline Matrix3& Matrix3::makeDiagonal(Real fM00, Real fM11, Real fM22)
{
	v[0] = fM00;
	v[1] = (Real)0.0;
	v[2] = (Real)0.0;
	v[3] = (Real)0.0;
	v[4] = fM11;
	v[5] = (Real)0.0;
	v[6] = (Real)0.0;
	v[7] = (Real)0.0;
	v[8] = fM22;

	return *this;
}

//----------------------------------------------------------------
inline int Matrix3::compareArrays (const Matrix3& rkM) const
{
	return memcmp(v,rkM.v,9 * sizeof(Real));
}


//----------------------------------------------------------------

//-----------------------------------------------------------------------
inline bool Matrix3::operator == (const Matrix3& rkMatrix) const
{
	return compareArrays(rkMatrix) == 0;
}

//----------------------------------------------------------------

inline bool Matrix3::operator < (const Matrix3& rkM) const
{
	 return compareArrays(rkM) < 0;
}

//----------------------------------------------------------------

inline bool Matrix3::operator <= (const Matrix3& rkM) const
{
	return compareArrays(rkM) <= 0;
}

//----------------------------------------------------------------

inline bool Matrix3::operator > (const Matrix3& rkM) const
{
	return compareArrays(rkM) > 0;
}

//----------------------------------------------------------------

inline bool Matrix3::operator >= (const Matrix3& rkM) const
{
	return compareArrays(rkM) >= 0;
}

//----------------------------------------------------------------

inline Matrix3& Matrix3::makeTranspose()
{
	return  ( (*this) = transpose() );
}

//----------------------------------------------------------------

inline Matrix3& Matrix3::makeInverse()
{
	return  ( (*this) = inverse() );
}
//----------------------------------------------------------------
inline Matrix3& Matrix3::makeAdjoint()
{
	return  ( (*this) = adjoint() );
}
//----------------------------------------------------------------
inline void Matrix3::toAxisAngle (Vector3& rkAxis, Real& rfReal) const
{
	Radian r;
	toAxisAngle ( rkAxis, r );
	rfReal = r.valueRadians();
}

//----------------------------------------------------------------

inline void Matrix3::toAxisAngle (Vector3& rkAxis, Degree& rfAngle) const 
{
	Radian r;
	toAxisAngle ( rkAxis, r );
	rfAngle = r;
}
//----------------------------------------------------------------
inline bool Matrix3::toEulerAnglesXYZ (float& rfYAngle, float& rfPAngle,
							  float& rfRAngle) const 
{
	Radian y, p, r;
	bool b = toEulerAnglesXYZ(y,p,r);
	rfYAngle = y.valueRadians();
	rfPAngle = p.valueRadians();
	rfRAngle = r.valueRadians();
	return b;
}
inline bool Matrix3::toEulerAnglesXZY (float& rfYAngle, float& rfPAngle,
							  float& rfRAngle) const
{
	Radian y, p, r;
	bool b = toEulerAnglesXZY(y,p,r);
	rfYAngle = y.valueRadians();
	rfPAngle = p.valueRadians();
	rfRAngle = r.valueRadians();
	return b;
}
inline bool Matrix3::toEulerAnglesYXZ (float& rfYAngle, float& rfPAngle,
							  float& rfRAngle) const
{
	Radian y, p, r;
	bool b = toEulerAnglesYXZ(y,p,r);
	rfYAngle = y.valueRadians();
	rfPAngle = p.valueRadians();
	rfRAngle = r.valueRadians();
	return b;
}
inline bool Matrix3::toEulerAnglesYZX (float& rfYAngle, float& rfPAngle,
							  float& rfRAngle) const
{
	Radian y, p, r;
	bool b = toEulerAnglesYZX(y,p,r);
	rfYAngle = y.valueRadians();
	rfPAngle = p.valueRadians();
	rfRAngle = r.valueRadians();
	return b;
}
inline bool Matrix3::toEulerAnglesZXY (float& rfYAngle, float& rfPAngle,
							  float& rfRAngle) const 
{
	Radian y, p, r;
	bool b = toEulerAnglesZXY(y,p,r);
	rfYAngle = y.valueRadians();
	rfPAngle = p.valueRadians();
	rfRAngle = r.valueRadians();
	return b;
}
inline bool Matrix3::toEulerAnglesZYX (float& rfYAngle, float& rfPAngle,
							  float& rfRAngle) const
{
	Radian y, p, r;
	bool b = toEulerAnglesZYX(y,p,r);
	rfYAngle = y.valueRadians();
	rfPAngle = p.valueRadians();
	rfRAngle = r.valueRadians();
	return b;
}


//----------------------------------------------------------------
inline bool Matrix3::toEulerAnglesXYZ (Degree& rfYAngle, Degree& rfPAngle,
									   Degree& rfRAngle) const 
{
	Radian y, p, r;
	bool b = toEulerAnglesXYZ(y,p,r);
	rfYAngle = y.valueDegrees();
	rfPAngle = p.valueDegrees();
	rfRAngle = r.valueDegrees();
	return b;
}
inline bool Matrix3::toEulerAnglesXZY (Degree& rfYAngle, Degree& rfPAngle,
									   Degree& rfRAngle) const
{
	Radian y, p, r;
	bool b = toEulerAnglesXZY(y,p,r);
	rfYAngle = y.valueDegrees();
	rfPAngle = p.valueDegrees();
	rfRAngle = r.valueDegrees();
	return b;
}
inline bool Matrix3::toEulerAnglesYXZ (Degree& rfYAngle, Degree& rfPAngle,
									   Degree& rfRAngle) const
{
	Radian y, p, r;
	bool b = toEulerAnglesYXZ(y,p,r);
	rfYAngle = y.valueDegrees();
	rfPAngle = p.valueDegrees();
	rfRAngle = r.valueDegrees();
	return b;
}
inline bool Matrix3::toEulerAnglesYZX (Degree& rfYAngle, Degree& rfPAngle,
									   Degree& rfRAngle) const
{
	Radian y, p, r;
	bool b = toEulerAnglesYZX(y,p,r);
	rfYAngle = y.valueDegrees();
	rfPAngle = p.valueDegrees();
	rfRAngle = r.valueDegrees();
	return b;
}
inline bool Matrix3::toEulerAnglesZXY (Degree& rfYAngle, Degree& rfPAngle,
									   Degree& rfRAngle) const 
{
	Radian y, p, r;
	bool b = toEulerAnglesZXY(y,p,r);
	rfYAngle = y.valueDegrees();
	rfPAngle = p.valueDegrees();
	rfRAngle = r.valueDegrees();
	return b;
}
inline bool Matrix3::toEulerAnglesZYX (Degree& rfYAngle, Degree& rfPAngle,
									   Degree& rfRAngle) const
{
	Radian y, p, r;
	bool b = toEulerAnglesZYX(y,p,r);
	rfYAngle = y.valueDegrees();
	rfPAngle = p.valueDegrees();
	rfRAngle = r.valueDegrees();
	return b;
}

//----------------------------------------------------------------

inline void Matrix3::fromEulerAnglesXYZ (const float& fYAngle, const float& fPAngle, const float& fRAngle)
{
	fromEulerAnglesXYZ ( Radian(fYAngle), Radian(fPAngle), Radian(fRAngle) );
}
inline void Matrix3::fromEulerAnglesXZY (const float& fYAngle, const float& fPAngle, const float& fRAngle) 
{
	fromEulerAnglesXZY ( Radian(fYAngle), Radian(fPAngle), Radian(fRAngle) );
}
inline void Matrix3::fromEulerAnglesYXZ (const float& fYAngle, const float& fPAngle, const float& fRAngle) 
{
	fromEulerAnglesYXZ ( Radian(fYAngle), Radian(fPAngle), Radian(fRAngle) );
}
inline void Matrix3::fromEulerAnglesYZX (const float& fYAngle, const float& fPAngle, const float& fRAngle) 
{
	fromEulerAnglesYZX ( Radian(fYAngle), Radian(fPAngle), Radian(fRAngle) );
}
inline void Matrix3::fromEulerAnglesZXY (const float& fYAngle, const float& fPAngle, const float& fRAngle)
{
	fromEulerAnglesZXY ( Radian(fYAngle), Radian(fPAngle), Radian(fRAngle) );
}
inline void Matrix3::fromEulerAnglesZYX (const float& fYAngle, const float& fPAngle, const float& fRAngle)
{
	fromEulerAnglesZYX ( Radian(fYAngle), Radian(fPAngle), Radian(fRAngle) );
}
//----------------------------------------------------------------
inline void Matrix3::fromEulerAnglesXYZ (const Degree& fYAngle, const Degree& fPAngle, const Degree& fRAngle)
{
	fromEulerAnglesXYZ ( Radian(fYAngle), Radian(fPAngle), Radian(fRAngle) );
}
inline void Matrix3::fromEulerAnglesXZY (const Degree& fYAngle, const Degree& fPAngle, const Degree& fRAngle) 
{
	fromEulerAnglesXZY ( Radian(fYAngle), Radian(fPAngle), Radian(fRAngle) );
}
inline void Matrix3::fromEulerAnglesYXZ (const Degree& fYAngle, const Degree& fPAngle, const Degree& fRAngle) 
{
	fromEulerAnglesYXZ ( Radian(fYAngle), Radian(fPAngle), Radian(fRAngle) );
}
inline void Matrix3::fromEulerAnglesYZX (const Degree& fYAngle, const Degree& fPAngle, const Degree& fRAngle) 
{
	fromEulerAnglesYZX ( Radian(fYAngle), Radian(fPAngle), Radian(fRAngle) );
}
inline void Matrix3::fromEulerAnglesZXY (const Degree& fYAngle, const Degree& fPAngle, const Degree& fRAngle)
{
	fromEulerAnglesZXY ( Radian(fYAngle), Radian(fPAngle), Radian(fRAngle) );
}
inline void Matrix3::fromEulerAnglesZYX (const Degree& fYAngle, const Degree& fPAngle, const Degree& fRAngle)
{
	fromEulerAnglesZYX ( Radian(fYAngle), Radian(fPAngle), Radian(fRAngle) );
}

//----------------------------------------------------------------

inline bool  Matrix3::isSymmetric() const 
{
	if ( (v[1] == v[3]) &&
		(v[2] == v[6]) &&
		(v[5] == v[7]) )
	{
		return true;
	}
	else
	{
		return false;
	}
}
//----------------------------------------------------------------
inline Real Matrix3::getValueByPosition(const uint& row , const uint& col )
{
	assert( (row < 3) && 
		(col < 3)  );
	return m[row][col];
}

//----------------------------------------------------------------
inline void Matrix3::setValueByPosition(const uint& row , const uint& col , const Real& value)
{
	assert( (row < 3) && 
		(col < 3)  );
	m[row][col] = value;
}


//----------------------------------------------------------------

inline Matrix3& Matrix3::makeSymmetricFromUpperTriangularMatrix()
{
	v[3] = v[1];
	v[6] = v[2];
	v[7] = v[5];
	return *this;
}
//----------------------------------------------------------------

inline Matrix3& Matrix3::makeSymmetricFromLowerTriangularMatrix()
{
	v[1] = v[3];
	v[2] = v[6];
	v[5] = v[7];
	return *this;
}
//----------------------------------------------------------------
void Matrix3::singularValueComposition (const Matrix3& rkL, const Matrix3& rkS,
										const Matrix3& rkR)
{
	*this = rkL*(rkS*rkR);
}

//----------------------------------------------------------------


//----------------------------------------------------------------


//----------------------------------------------------------------






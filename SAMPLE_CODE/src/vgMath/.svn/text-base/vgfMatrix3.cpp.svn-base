/*
-----------------------------------------------------------------------------
  VRES(Virtual Reality GIS Engine System)    
  -------------------------------------------------------------
  License details ... waiting to add...
  -------------------------------------------------------------
  Copyright  (C) 2007 , leven - All Rights Reserved
-----------------------------------------------------------------------------
*/

#include <vgStableHeaders.h>
#include <vgMath/vgfMath.h>
#include <vgMath/vgfMatrix3.h>


#undef PI


namespace vgMath {
	
	
		
	const Real Matrix3::EPSILON = 1e-06;
	const Matrix3 Matrix3::ZERO(0,0,0,0,0,0,0,0,0);
	const Matrix3 Matrix3::IDENTITY(1,0,0,0,1,0,0,0,1);
	//const Real Matrix3::ms_fSvdEpsilon = 1e-04;		
	//const unsigned int Matrix3::ms_iSvdMaxIterations = 32;

	Matrix3::Matrix3 (Real fEntry00, Real fEntry01, Real fEntry02,
		Real fEntry10, Real fEntry11, Real fEntry12,
		Real fEntry20, Real fEntry21, Real fEntry22)
	{
		m[0][0] = fEntry00;
		m[0][1] = fEntry01;
		m[0][2] = fEntry02;
		m[1][0] = fEntry10;
		m[1][1] = fEntry11;
		m[1][2] = fEntry12;
		m[2][0] = fEntry20;
		m[2][1] = fEntry21;
		m[2][2] = fEntry22;
	}

	//-----------------------------------------------------------------------
	Vector3 Matrix3::getColumn (size_t iCol) const
	{
		assert( 0 <= iCol && iCol < 3 );
		return Vector3(m[0][iCol],m[1][iCol],
			m[2][iCol]);
	}
	//-----------------------------------------------------------------------
	Vector3 Matrix3::getRow (size_t iCol) const
	{
		assert( 0 <= iCol && iCol < 3 );
		return Vector3(m[iCol][0],m[iCol][1],
			m[iCol][2]);
	}
	//-----------------------------------------------------------------------
	void Matrix3::setColumn(size_t iCol, const Vector3& vec)
	{
		assert( 0 <= iCol && iCol < 3 );
		m[0][iCol] = vec.x;
		m[1][iCol] = vec.y;
		m[2][iCol] = vec.z;

	}
	void Matrix3::setRow(size_t iCol, const Vector3& vec)
	{
		assert( 0 <= iCol && iCol < 3 );
		m[iCol][0] = vec.x;
		m[iCol][1] = vec.y;
		m[iCol][2] = vec.z;

	}
	//-----------------------------------------------------------------------
	void Matrix3::fromAxes(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis)
	{
		setColumn(0,xAxis);
		setColumn(1,yAxis);
		setColumn(2,zAxis);

	}


	//-----------------------------------------------------------------------
	Matrix3 Matrix3::operator+ (const Matrix3& rkMatrix) const
	{
		Matrix3 kSum;
		for (size_t iRow = 0; iRow < 3; iRow++)
		{
			for (size_t iCol = 0; iCol < 3; iCol++)
			{
				kSum.m[iRow][iCol] = m[iRow][iCol] +
					rkMatrix.m[iRow][iCol];
			}
		}
		return kSum;
	}
	//-----------------------------------------------------------------------
	Matrix3 Matrix3::operator- (const Matrix3& rkMatrix) const
	{
		Matrix3 kDiff;
		for (size_t iRow = 0; iRow < 3; iRow++)
		{
			for (size_t iCol = 0; iCol < 3; iCol++)
			{
				kDiff.m[iRow][iCol] = m[iRow][iCol] -
					rkMatrix.m[iRow][iCol];
			}
		}
		return kDiff;
	}
	//-----------------------------------------------------------------------
	Matrix3 Matrix3::operator* (const Matrix3& rkM) const
	{
		return Matrix3(
			v[0]*rkM.v[0] +
			v[1]*rkM.v[3] +
			v[2]*rkM.v[6],

			v[0]*rkM.v[1] +
			v[1]*rkM.v[4] +
			v[2]*rkM.v[7],

			v[0]*rkM.v[2] +
			v[1]*rkM.v[5] +
			v[2]*rkM.v[8],

			v[3]*rkM.v[0] +
			v[4]*rkM.v[3] +
			v[5]*rkM.v[6],

			v[3]*rkM.v[1] +
			v[4]*rkM.v[4] +
			v[5]*rkM.v[7],

			v[3]*rkM.v[2] +
			v[4]*rkM.v[5] +
			v[5]*rkM.v[8],

			v[6]*rkM.v[0] +
			v[7]*rkM.v[3] +
			v[8]*rkM.v[6],

			v[6]*rkM.v[1] +
			v[7]*rkM.v[4] +
			v[8]*rkM.v[7],

			v[6]*rkM.v[2] +
			v[7]*rkM.v[5] +
			v[8]*rkM.v[8]);
	}
	//-----------------------------------------------------------------------
	Vector3 Matrix3::operator* (const Vector3& rkPoint) const
	{
		Vector3 kProd;
		for (size_t iRow = 0; iRow < 3; iRow++)
		{
			kProd[iRow] =
				m[iRow][0]*rkPoint[0] +
				m[iRow][1]*rkPoint[1] +
				m[iRow][2]*rkPoint[2];
		}
		return kProd;
	}
	//-----------------------------------------------------------------------
	Vector3 operator* (const Vector3& rkPoint, const Matrix3& rkMatrix)
	{
		Vector3 kProd;
		for (size_t iRow = 0; iRow < 3; iRow++)
		{
			kProd[iRow] =
				rkPoint[0]*rkMatrix.m[0][iRow] +
				rkPoint[1]*rkMatrix.m[1][iRow] +
				rkPoint[2]*rkMatrix.m[2][iRow];
		}
		return kProd;
	}
	//-----------------------------------------------------------------------
	Matrix3 Matrix3::operator- () const
	{
		return Matrix3(
			-v[0],
			-v[1],
			-v[2],
			-v[3],
			-v[4],
			-v[5],
			-v[6],
			-v[7],
			-v[8]);
	}
	//-----------------------------------------------------------------------
	Matrix3 Matrix3::operator* (Real fScalar) const
	{
		return Matrix3 (
			fScalar*v[0],
			fScalar*v[1],
			fScalar*v[2],
			fScalar*v[3],
			fScalar*v[4],
			fScalar*v[5],
			fScalar*v[6],
			fScalar*v[7],
			fScalar*v[8]);
	}
	Matrix3 Matrix3::operator/ (Real fScalar) const
	{
		if (fScalar != (Real)0.0)
		{
			Real fInvScalar = ((Real)1.0)/fScalar;
			return Matrix3 (
				fInvScalar* v[0],
				fInvScalar* v[1],
				fInvScalar* v[2],
				fInvScalar* v[3],
				fInvScalar* v[4],
				fInvScalar* v[5],
				fInvScalar* v[6],
				fInvScalar* v[7],
				fInvScalar* v[8]);
		}

		return Matrix3(
			Math::MAX_REAL,
			Math::MAX_REAL,
			Math::MAX_REAL,
			Math::MAX_REAL,
			Math::MAX_REAL,
			Math::MAX_REAL,
			Math::MAX_REAL,
			Math::MAX_REAL,
			Math::MAX_REAL);
	}
	//-----------------------------------------------------------------------
	Matrix3 operator* (Real fScalar, const Matrix3& rkMatrix)
	{
		Matrix3 kProd;
		for (size_t iRow = 0; iRow < 3; iRow++)
		{
			for (size_t iCol = 0; iCol < 3; iCol++)
				kProd[iRow][iCol] = fScalar*rkMatrix.m[iRow][iCol];
		}
		return kProd;
	}
	//-----------------------------------------------------------------------
	Matrix3 Matrix3::transpose () const
	{
		return Matrix3 (
			v[0],
			v[3],
			v[6],
			v[1],
			v[4],
			v[7],
			v[2],
			v[5],
			v[8]);
	}
	//-----------------------------------------------------------------------
	Matrix3 Matrix3::inverse () const
	{
		// Invert a 3x3 using cofactors.  This is about 8 times faster than
		// the Numerical Recipes code which uses Gaussian elimination.

		Matrix3 rkInverse;

		rkInverse[0][0] = m[1][1]*m[2][2] -
			m[1][2]*m[2][1];
		rkInverse[0][1] = m[0][2]*m[2][1] -
			m[0][1]*m[2][2];
		rkInverse[0][2] = m[0][1]*m[1][2] -
			m[0][2]*m[1][1];
		rkInverse[1][0] = m[1][2]*m[2][0] -
			m[1][0]*m[2][2];
		rkInverse[1][1] = m[0][0]*m[2][2] -
			m[0][2]*m[2][0];
		rkInverse[1][2] = m[0][2]*m[1][0] -
			m[0][0]*m[1][2];
		rkInverse[2][0] = m[1][0]*m[2][1] -
			m[1][1]*m[2][0];
		rkInverse[2][1] = m[0][1]*m[2][0] -
			m[0][0]*m[2][1];
		rkInverse[2][2] = m[0][0]*m[1][1] -
			m[0][1]*m[1][0];

		Real fDet =
			m[0][0]*rkInverse[0][0] +
			m[0][1]*rkInverse[1][0]+
			m[0][2]*rkInverse[2][0];

		if ( Math::Abs(fDet) <= Math::ZERO_TOLERANCE )
			return ZERO;

		Real fInvDet = ((Real)1.0)/fDet;
		rkInverse.v[0] *= fInvDet;
		rkInverse.v[1] *= fInvDet;
		rkInverse.v[2] *= fInvDet;
		rkInverse.v[3] *= fInvDet;
		rkInverse.v[4] *= fInvDet;
		rkInverse.v[5] *= fInvDet;
		rkInverse.v[6] *= fInvDet;
		rkInverse.v[7] *= fInvDet;
		rkInverse.v[8] *= fInvDet;

		return rkInverse;
	}
	//-----------------------------------------------------------------------
	Real Matrix3::determinant () const
	{
		Real fCofactor00 = m[1][1]*m[2][2] -
			m[1][2]*m[2][1];
		Real fCofactor10 = m[1][2]*m[2][0] -
			m[1][0]*m[2][2];
		Real fCofactor20 = m[1][0]*m[2][1] -
			m[1][1]*m[2][0];

		Real fDet =
			m[0][0]*fCofactor00 +
			m[0][1]*fCofactor10 +
			m[0][2]*fCofactor20;

		return fDet;
	}
	//-----------------------------------------------------------------------
	void Matrix3::Bidiagonalize (Matrix3& kA, Matrix3& kL,
		Matrix3& kR)
	{
		Real afV[3], afW[3];
		Real fLength, fSign, fT1, fInvT1, fT2;
		bool bIdentity;

		// map first column to (*,0,0)
		fLength = Math::Sqrt(kA[0][0]*kA[0][0] + kA[1][0]*kA[1][0] +
			kA[2][0]*kA[2][0]);
		if ( fLength > 0.0 )
		{
			fSign = (kA[0][0] > 0.0 ? 1.0 : -1.0);
			fT1 = kA[0][0] + fSign*fLength;
			fInvT1 = 1.0/fT1;
			afV[1] = kA[1][0]*fInvT1;
			afV[2] = kA[2][0]*fInvT1;

			fT2 = -2.0/(1.0+afV[1]*afV[1]+afV[2]*afV[2]);
			afW[0] = fT2*(kA[0][0]+kA[1][0]*afV[1]+kA[2][0]*afV[2]);
			afW[1] = fT2*(kA[0][1]+kA[1][1]*afV[1]+kA[2][1]*afV[2]);
			afW[2] = fT2*(kA[0][2]+kA[1][2]*afV[1]+kA[2][2]*afV[2]);
			kA[0][0] += afW[0];
			kA[0][1] += afW[1];
			kA[0][2] += afW[2];
			kA[1][1] += afV[1]*afW[1];
			kA[1][2] += afV[1]*afW[2];
			kA[2][1] += afV[2]*afW[1];
			kA[2][2] += afV[2]*afW[2];

			kL[0][0] = 1.0+fT2;
			kL[0][1] = kL[1][0] = fT2*afV[1];
			kL[0][2] = kL[2][0] = fT2*afV[2];
			kL[1][1] = 1.0+fT2*afV[1]*afV[1];
			kL[1][2] = kL[2][1] = fT2*afV[1]*afV[2];
			kL[2][2] = 1.0+fT2*afV[2]*afV[2];
			bIdentity = false;
		}
		else
		{
			kL = Matrix3::IDENTITY;
			bIdentity = true;
		}

		// map first row to (*,*,0)
		fLength = Math::Sqrt(kA[0][1]*kA[0][1]+kA[0][2]*kA[0][2]);
		if ( fLength > 0.0 )
		{
			fSign = (kA[0][1] > 0.0 ? 1.0 : -1.0);
			fT1 = kA[0][1] + fSign*fLength;
			afV[2] = kA[0][2]/fT1;

			fT2 = -2.0/(1.0+afV[2]*afV[2]);
			afW[0] = fT2*(kA[0][1]+kA[0][2]*afV[2]);
			afW[1] = fT2*(kA[1][1]+kA[1][2]*afV[2]);
			afW[2] = fT2*(kA[2][1]+kA[2][2]*afV[2]);
			kA[0][1] += afW[0];
			kA[1][1] += afW[1];
			kA[1][2] += afW[1]*afV[2];
			kA[2][1] += afW[2];
			kA[2][2] += afW[2]*afV[2];

			kR[0][0] = 1.0;
			kR[0][1] = kR[1][0] = 0.0;
			kR[0][2] = kR[2][0] = 0.0;
			kR[1][1] = 1.0+fT2;
			kR[1][2] = kR[2][1] = fT2*afV[2];
			kR[2][2] = 1.0+fT2*afV[2]*afV[2];
		}
		else
		{
			kR = Matrix3::IDENTITY;
		}

		// map second column to (*,*,0)
		fLength = Math::Sqrt(kA[1][1]*kA[1][1]+kA[2][1]*kA[2][1]);
		if ( fLength > 0.0 )
		{
			fSign = (kA[1][1] > 0.0 ? 1.0 : -1.0);
			fT1 = kA[1][1] + fSign*fLength;
			afV[2] = kA[2][1]/fT1;

			fT2 = -2.0/(1.0+afV[2]*afV[2]);
			afW[1] = fT2*(kA[1][1]+kA[2][1]*afV[2]);
			afW[2] = fT2*(kA[1][2]+kA[2][2]*afV[2]);
			kA[1][1] += afW[1];
			kA[1][2] += afW[2];
			kA[2][2] += afV[2]*afW[2];

			Real fA = 1.0+fT2;
			Real fB = fT2*afV[2];
			Real fC = 1.0+fB*afV[2];

			if ( bIdentity )
			{
				kL[0][0] = 1.0;
				kL[0][1] = kL[1][0] = 0.0;
				kL[0][2] = kL[2][0] = 0.0;
				kL[1][1] = fA;
				kL[1][2] = kL[2][1] = fB;
				kL[2][2] = fC;
			}
			else
			{
				for (int iRow = 0; iRow < 3; iRow++)
				{
					Real fTmp0 = kL[iRow][1];
					Real fTmp1 = kL[iRow][2];
					kL[iRow][1] = fA*fTmp0+fB*fTmp1;
					kL[iRow][2] = fB*fTmp0+fC*fTmp1;
				}
			}
		}
	}
	//-----------------------------------------------------------------------
	void Matrix3::GolubKahanStep (Matrix3& kA, Matrix3& kL,
		Matrix3& kR)
	{
		Real fT11 = kA[0][1]*kA[0][1]+kA[1][1]*kA[1][1];
		Real fT22 = kA[1][2]*kA[1][2]+kA[2][2]*kA[2][2];
		Real fT12 = kA[1][1]*kA[1][2];
		Real fTrace = fT11+fT22;
		Real fDiff = fT11-fT22;
		Real fDiscr = Math::Sqrt(fDiff*fDiff+4.0*fT12*fT12);
		Real fRoot1 = 0.5*(fTrace+fDiscr);
		Real fRoot2 = 0.5*(fTrace-fDiscr);

		// adjust right
		Real fY = kA[0][0] - (Math::Abs(fRoot1-fT22) <=
			Math::Abs(fRoot2-fT22) ? fRoot1 : fRoot2);
		Real fZ = kA[0][1];
		Real fInvLength = Math::InvSqrt(fY*fY+fZ*fZ);
		Real fSin = fZ*fInvLength;
		Real fCos = -fY*fInvLength;

		Real fTmp0 = kA[0][0];
		Real fTmp1 = kA[0][1];
		kA[0][0] = fCos*fTmp0-fSin*fTmp1;
		kA[0][1] = fSin*fTmp0+fCos*fTmp1;
		kA[1][0] = -fSin*kA[1][1];
		kA[1][1] *= fCos;

		size_t iRow;
		for (iRow = 0; iRow < 3; iRow++)
		{
			fTmp0 = kR[0][iRow];
			fTmp1 = kR[1][iRow];
			kR[0][iRow] = fCos*fTmp0-fSin*fTmp1;
			kR[1][iRow] = fSin*fTmp0+fCos*fTmp1;
		}

		// adjust left
		fY = kA[0][0];
		fZ = kA[1][0];
		fInvLength = Math::InvSqrt(fY*fY+fZ*fZ);
		fSin = fZ*fInvLength;
		fCos = -fY*fInvLength;

		kA[0][0] = fCos*kA[0][0]-fSin*kA[1][0];
		fTmp0 = kA[0][1];
		fTmp1 = kA[1][1];
		kA[0][1] = fCos*fTmp0-fSin*fTmp1;
		kA[1][1] = fSin*fTmp0+fCos*fTmp1;
		kA[0][2] = -fSin*kA[1][2];
		kA[1][2] *= fCos;

		size_t iCol;
		for (iCol = 0; iCol < 3; iCol++)
		{
			fTmp0 = kL[iCol][0];
			fTmp1 = kL[iCol][1];
			kL[iCol][0] = fCos*fTmp0-fSin*fTmp1;
			kL[iCol][1] = fSin*fTmp0+fCos*fTmp1;
		}

		// adjust right
		fY = kA[0][1];
		fZ = kA[0][2];
		fInvLength = Math::InvSqrt(fY*fY+fZ*fZ);
		fSin = fZ*fInvLength;
		fCos = -fY*fInvLength;

		kA[0][1] = fCos*kA[0][1]-fSin*kA[0][2];
		fTmp0 = kA[1][1];
		fTmp1 = kA[1][2];
		kA[1][1] = fCos*fTmp0-fSin*fTmp1;
		kA[1][2] = fSin*fTmp0+fCos*fTmp1;
		kA[2][1] = -fSin*kA[2][2];
		kA[2][2] *= fCos;

		for (iRow = 0; iRow < 3; iRow++)
		{
			fTmp0 = kR[1][iRow];
			fTmp1 = kR[2][iRow];
			kR[1][iRow] = fCos*fTmp0-fSin*fTmp1;
			kR[2][iRow] = fSin*fTmp0+fCos*fTmp1;
		}

		// adjust left
		fY = kA[1][1];
		fZ = kA[2][1];
		fInvLength = Math::InvSqrt(fY*fY+fZ*fZ);
		fSin = fZ*fInvLength;
		fCos = -fY*fInvLength;

		kA[1][1] = fCos*kA[1][1]-fSin*kA[2][1];
		fTmp0 = kA[1][2];
		fTmp1 = kA[2][2];
		kA[1][2] = fCos*fTmp0-fSin*fTmp1;
		kA[2][2] = fSin*fTmp0+fCos*fTmp1;

		for (iCol = 0; iCol < 3; iCol++)
		{
			fTmp0 = kL[iCol][1];
			fTmp1 = kL[iCol][2];
			kL[iCol][1] = fCos*fTmp0-fSin*fTmp1;
			kL[iCol][2] = fSin*fTmp0+fCos*fTmp1;
		}
	}
	//-----------------------------------------------------------------------
	void Matrix3::singularValueDecomposition (Matrix3& kL, Vector3& kS,
		Matrix3& kR) const
	{
		// temas: currently unused
		//const int iMax = 16;
		size_t iRow, iCol;

		Matrix3 kA = *this;
		Bidiagonalize(kA,kL,kR);

		const int iMax = 32;
		const Real fEpsilon = (Real)1e-04;

		for (unsigned int i = 0; i < iMax; i++)
		{
			Real fTmp, fTmp0, fTmp1;
			Real fSin0, fCos0, fTan0;
			Real fSin1, fCos1, fTan1;

			bool bTest1 = (Math::Abs(kA[0][1]) <=
				fEpsilon*(Math::Abs(kA[0][0])+Math::Abs(kA[1][1])));
			bool bTest2 = (Math::Abs(kA[1][2]) <=
				fEpsilon*(Math::Abs(kA[1][1])+Math::Abs(kA[2][2])));
			if ( bTest1 )
			{
				if ( bTest2 )
				{
					kS[0] = kA[0][0];
					kS[1] = kA[1][1];
					kS[2] = kA[2][2];
					break;
				}
				else
				{
					// 2x2 closed form factorization
					fTmp = (kA[1][1]*kA[1][1] - kA[2][2]*kA[2][2] +
						kA[1][2]*kA[1][2])/(kA[1][2]*kA[2][2]);
					fTan0 = 0.5*(fTmp+Math::Sqrt(fTmp*fTmp + 4.0));
					fCos0 = Math::InvSqrt(1.0+fTan0*fTan0);
					fSin0 = fTan0*fCos0;

					for (iCol = 0; iCol < 3; iCol++)
					{
						fTmp0 = kL[iCol][1];
						fTmp1 = kL[iCol][2];
						kL[iCol][1] = fCos0*fTmp0-fSin0*fTmp1;
						kL[iCol][2] = fSin0*fTmp0+fCos0*fTmp1;
					}

					fTan1 = (kA[1][2]-kA[2][2]*fTan0)/kA[1][1];
					fCos1 = Math::InvSqrt(1.0+fTan1*fTan1);
					fSin1 = -fTan1*fCos1;

					for (iRow = 0; iRow < 3; iRow++)
					{
						fTmp0 = kR[1][iRow];
						fTmp1 = kR[2][iRow];
						kR[1][iRow] = fCos1*fTmp0-fSin1*fTmp1;
						kR[2][iRow] = fSin1*fTmp0+fCos1*fTmp1;
					}

					kS[0] = kA[0][0];
					kS[1] = fCos0*fCos1*kA[1][1] -
						fSin1*(fCos0*kA[1][2]-fSin0*kA[2][2]);
					kS[2] = fSin0*fSin1*kA[1][1] +
						fCos1*(fSin0*kA[1][2]+fCos0*kA[2][2]);
					break;
				}
			}
			else
			{
				if ( bTest2 )
				{
					// 2x2 closed form factorization
					fTmp = (kA[0][0]*kA[0][0] + kA[1][1]*kA[1][1] -
						kA[0][1]*kA[0][1])/(kA[0][1]*kA[1][1]);
					fTan0 = 0.5*(-fTmp+Math::Sqrt(fTmp*fTmp + 4.0));
					fCos0 = Math::InvSqrt(1.0+fTan0*fTan0);
					fSin0 = fTan0*fCos0;

					for (iCol = 0; iCol < 3; iCol++)
					{
						fTmp0 = kL[iCol][0];
						fTmp1 = kL[iCol][1];
						kL[iCol][0] = fCos0*fTmp0-fSin0*fTmp1;
						kL[iCol][1] = fSin0*fTmp0+fCos0*fTmp1;
					}

					fTan1 = (kA[0][1]-kA[1][1]*fTan0)/kA[0][0];
					fCos1 = Math::InvSqrt(1.0+fTan1*fTan1);
					fSin1 = -fTan1*fCos1;

					for (iRow = 0; iRow < 3; iRow++)
					{
						fTmp0 = kR[0][iRow];
						fTmp1 = kR[1][iRow];
						kR[0][iRow] = fCos1*fTmp0-fSin1*fTmp1;
						kR[1][iRow] = fSin1*fTmp0+fCos1*fTmp1;
					}

					kS[0] = fCos0*fCos1*kA[0][0] -
						fSin1*(fCos0*kA[0][1]-fSin0*kA[1][1]);
					kS[1] = fSin0*fSin1*kA[0][0] +
						fCos1*(fSin0*kA[0][1]+fCos0*kA[1][1]);
					kS[2] = kA[2][2];
					break;
				}
				else
				{
					GolubKahanStep(kA,kL,kR);
				}
			}
		}

		// positize diagonal
		for (iRow = 0; iRow < 3; iRow++)
		{
			if ( kS[iRow] < 0.0 )
			{
				kS[iRow] = -kS[iRow];
				for (iCol = 0; iCol < 3; iCol++)
					kR[iRow][iCol] = -kR[iRow][iCol];
			}
		}
	}
	//-----------------------------------------------------------------------
	void Matrix3::singularValueComposition (const Matrix3& kL,
		const Vector3& kS, const Matrix3& kR)
	{
		size_t iRow, iCol;
		Matrix3 kTmp;

		// product S*R
		for (iRow = 0; iRow < 3; iRow++)
		{
			for (iCol = 0; iCol < 3; iCol++)
				kTmp[iRow][iCol] = kS[iRow]*kR[iRow][iCol];
		}

		// product L*S*R
		for (iRow = 0; iRow < 3; iRow++)
		{
			for (iCol = 0; iCol < 3; iCol++)
			{
				m[iRow][iCol] = 0.0;
				for (int iMid = 0; iMid < 3; iMid++)
					m[iRow][iCol] += kL[iRow][iMid]*kTmp[iMid][iCol];
			}
		}
	}
	//-----------------------------------------------------------------------
	void Matrix3::orthonormalize ()
	{
		// Algorithm uses Gram-Schmidt orthogonalization.  If 'this' matrix is
		// M = [m0|m1|m2], then orthonormal output matrix is Q = [q0|q1|q2],
		//
		//   q0 = m0/|m0|
		//   q1 = (m1-(q0*m1)q0)/|m1-(q0*m1)q0|
		//   q2 = (m2-(q0*m2)q0-(q1*m2)q1)/|m2-(q0*m2)q0-(q1*m2)q1|
		//
		// where |V| indicates length of vector V and A*B indicates dot
		// product of vectors A and B.

		// compute q0
		Real fInvLength = Math::InvSqrt(m[0][0]*m[0][0]
		+ m[1][0]*m[1][0] +
			m[2][0]*m[2][0]);

		m[0][0] *= fInvLength;
		m[1][0] *= fInvLength;
		m[2][0] *= fInvLength;

		// compute q1
		Real fDot0 =
			m[0][0]*m[0][1] +
			m[1][0]*m[1][1] +
			m[2][0]*m[2][1];

		m[0][1] -= fDot0*m[0][0];
		m[1][1] -= fDot0*m[1][0];
		m[2][1] -= fDot0*m[2][0];

		fInvLength = Math::InvSqrt(m[0][1]*m[0][1] +
			m[1][1]*m[1][1] +
			m[2][1]*m[2][1]);

		m[0][1] *= fInvLength;
		m[1][1] *= fInvLength;
		m[2][1] *= fInvLength;

		// compute q2
		Real fDot1 =
			m[0][1]*m[0][2] +
			m[1][1]*m[1][2] +
			m[2][1]*m[2][2];

		fDot0 =
			m[0][0]*m[0][2] +
			m[1][0]*m[1][2] +
			m[2][0]*m[2][2];

		m[0][2] -= fDot0*m[0][0] + fDot1*m[0][1];
		m[1][2] -= fDot0*m[1][0] + fDot1*m[1][1];
		m[2][2] -= fDot0*m[2][0] + fDot1*m[2][1];

		fInvLength = Math::InvSqrt(m[0][2]*m[0][2] +
			m[1][2]*m[1][2] +
			m[2][2]*m[2][2]);

		m[0][2] *= fInvLength;
		m[1][2] *= fInvLength;
		m[2][2] *= fInvLength;
	}
	//-----------------------------------------------------------------------
	void Matrix3::QDUDecomposition (Matrix3& kQ,
		Vector3& kD, Vector3& kU) const
	{
		// Factor M = QR = QDU where Q is orthogonal, D is diagonal,
		// and U is upper triangular with ones on its diagonal.  Algorithm uses
		// Gram-Schmidt orthogonalization (the QR algorithm).
		//
		// If M = [ m0 | m1 | m2 ] and Q = [ q0 | q1 | q2 ], then
		//
		//   q0 = m0/|m0|
		//   q1 = (m1-(q0*m1)q0)/|m1-(q0*m1)q0|
		//   q2 = (m2-(q0*m2)q0-(q1*m2)q1)/|m2-(q0*m2)q0-(q1*m2)q1|
		//
		// where |V| indicates length of vector V and A*B indicates dot
		// product of vectors A and B.  The matrix R has entries
		//
		//   r00 = q0*m0  r01 = q0*m1  r02 = q0*m2
		//   r10 = 0      r11 = q1*m1  r12 = q1*m2
		//   r20 = 0      r21 = 0      r22 = q2*m2
		//
		// so D = diag(r00,r11,r22) and U has entries u01 = r01/r00,
		// u02 = r02/r00, and u12 = r12/r11.

		// Q = rotation
		// D = scaling
		// U = shear

		// D stores the three diagonal entries r00, r11, r22
		// U stores the entries U[0] = u01, U[1] = u02, U[2] = u12

		// build orthogonal matrix Q
		Real fInvLength = Math::InvSqrt(m[0][0]*m[0][0]
		+ m[1][0]*m[1][0] +
			m[2][0]*m[2][0]);
		kQ[0][0] = m[0][0]*fInvLength;
		kQ[1][0] = m[1][0]*fInvLength;
		kQ[2][0] = m[2][0]*fInvLength;

		Real fDot = kQ[0][0]*m[0][1] + kQ[1][0]*m[1][1] +
			kQ[2][0]*m[2][1];
		kQ[0][1] = m[0][1]-fDot*kQ[0][0];
		kQ[1][1] = m[1][1]-fDot*kQ[1][0];
		kQ[2][1] = m[2][1]-fDot*kQ[2][0];
		fInvLength = Math::InvSqrt(kQ[0][1]*kQ[0][1] + kQ[1][1]*kQ[1][1] +
			kQ[2][1]*kQ[2][1]);
		kQ[0][1] *= fInvLength;
		kQ[1][1] *= fInvLength;
		kQ[2][1] *= fInvLength;

		fDot = kQ[0][0]*m[0][2] + kQ[1][0]*m[1][2] +
			kQ[2][0]*m[2][2];
		kQ[0][2] = m[0][2]-fDot*kQ[0][0];
		kQ[1][2] = m[1][2]-fDot*kQ[1][0];
		kQ[2][2] = m[2][2]-fDot*kQ[2][0];
		fDot = kQ[0][1]*m[0][2] + kQ[1][1]*m[1][2] +
			kQ[2][1]*m[2][2];
		kQ[0][2] -= fDot*kQ[0][1];
		kQ[1][2] -= fDot*kQ[1][1];
		kQ[2][2] -= fDot*kQ[2][1];
		fInvLength = Math::InvSqrt(kQ[0][2]*kQ[0][2] + kQ[1][2]*kQ[1][2] +
			kQ[2][2]*kQ[2][2]);
		kQ[0][2] *= fInvLength;
		kQ[1][2] *= fInvLength;
		kQ[2][2] *= fInvLength;

		// guarantee that orthogonal matrix has determinant 1 (no reflections)
		Real fDet = kQ[0][0]*kQ[1][1]*kQ[2][2] + kQ[0][1]*kQ[1][2]*kQ[2][0] +
			kQ[0][2]*kQ[1][0]*kQ[2][1] - kQ[0][2]*kQ[1][1]*kQ[2][0] -
			kQ[0][1]*kQ[1][0]*kQ[2][2] - kQ[0][0]*kQ[1][2]*kQ[2][1];

		if ( fDet < 0.0 )
		{
			for (size_t iRow = 0; iRow < 3; iRow++)
				for (size_t iCol = 0; iCol < 3; iCol++)
					kQ[iRow][iCol] = -kQ[iRow][iCol];
		}

		// build "right" matrix R
		Matrix3 kR;
		kR[0][0] = kQ[0][0]*m[0][0] + kQ[1][0]*m[1][0] +
			kQ[2][0]*m[2][0];
		kR[0][1] = kQ[0][0]*m[0][1] + kQ[1][0]*m[1][1] +
			kQ[2][0]*m[2][1];
		kR[1][1] = kQ[0][1]*m[0][1] + kQ[1][1]*m[1][1] +
			kQ[2][1]*m[2][1];
		kR[0][2] = kQ[0][0]*m[0][2] + kQ[1][0]*m[1][2] +
			kQ[2][0]*m[2][2];
		kR[1][2] = kQ[0][1]*m[0][2] + kQ[1][1]*m[1][2] +
			kQ[2][1]*m[2][2];
		kR[2][2] = kQ[0][2]*m[0][2] + kQ[1][2]*m[1][2] +
			kQ[2][2]*m[2][2];

		// the scaling component
		kD[0] = kR[0][0];
		kD[1] = kR[1][1];
		kD[2] = kR[2][2];

		// the shear component
		Real fInvD0 = 1.0/kD[0];
		kU[0] = kR[0][1]*fInvD0;
		kU[1] = kR[0][2]*fInvD0;
		kU[2] = kR[1][2]/kD[1];
	}
	//-----------------------------------------------------------------------
	Real Matrix3::MaxCubicRoot (Real afCoeff[3])
	{
		// Spectral norm is for A^T*A, so characteristic polynomial
		// P(x) = c[0]+c[1]*x+c[2]*x^2+x^3 has three positive real roots.
		// This yields the assertions c[0] < 0 and c[2]*c[2] >= 3*c[1].

		// quick out for uniform scale (triple root)
		const Real fOneThird = 1.0/3.0;
		const Real fEpsilon = 1e-06;
		Real fDiscr = afCoeff[2]*afCoeff[2] - 3.0*afCoeff[1];
		if ( fDiscr <= fEpsilon )
			return -fOneThird*afCoeff[2];

		// Compute an upper bound on roots of P(x).  This assumes that A^T*A
		// has been scaled by its largest entry.
		Real fX = 1.0;
		Real fPoly = afCoeff[0]+fX*(afCoeff[1]+fX*(afCoeff[2]+fX));
		if ( fPoly < 0.0 )
		{
			// uses a matrix norm to find an upper bound on maximum root
			fX = Math::Abs(afCoeff[0]);
			Real fTmp = 1.0+Math::Abs(afCoeff[1]);
			if ( fTmp > fX )
				fX = fTmp;
			fTmp = 1.0+Math::Abs(afCoeff[2]);
			if ( fTmp > fX )
				fX = fTmp;
		}

		// Newton's method to find root
		Real fTwoC2 = 2.0*afCoeff[2];
		for (int i = 0; i < 16; i++)
		{
			fPoly = afCoeff[0]+fX*(afCoeff[1]+fX*(afCoeff[2]+fX));
			if ( Math::Abs(fPoly) <= fEpsilon )
				return fX;

			Real fDeriv = afCoeff[1]+fX*(fTwoC2+3.0*fX);
			fX -= fPoly/fDeriv;
		}

		return fX;
	}
	//-----------------------------------------------------------------------
	Real Matrix3::SpectralNorm () const
	{
		Matrix3 kP;
		size_t iRow, iCol;
		Real fPmax = 0.0;
		for (iRow = 0; iRow < 3; iRow++)
		{
			for (iCol = 0; iCol < 3; iCol++)
			{
				kP[iRow][iCol] = 0.0;
				for (int iMid = 0; iMid < 3; iMid++)
				{
					kP[iRow][iCol] +=
						m[iMid][iRow]*m[iMid][iCol];
				}
				if ( kP[iRow][iCol] > fPmax )
					fPmax = kP[iRow][iCol];
			}
		}

		Real fInvPmax = 1.0/fPmax;
		for (iRow = 0; iRow < 3; iRow++)
		{
			for (iCol = 0; iCol < 3; iCol++)
				kP[iRow][iCol] *= fInvPmax;
		}

		Real afCoeff[3];
		afCoeff[0] = -(kP[0][0]*(kP[1][1]*kP[2][2]-kP[1][2]*kP[2][1]) +
			kP[0][1]*(kP[2][0]*kP[1][2]-kP[1][0]*kP[2][2]) +
			kP[0][2]*(kP[1][0]*kP[2][1]-kP[2][0]*kP[1][1]));
		afCoeff[1] = kP[0][0]*kP[1][1]-kP[0][1]*kP[1][0] +
			kP[0][0]*kP[2][2]-kP[0][2]*kP[2][0] +
			kP[1][1]*kP[2][2]-kP[1][2]*kP[2][1];
		afCoeff[2] = -(kP[0][0]+kP[1][1]+kP[2][2]);

		Real fRoot = MaxCubicRoot(afCoeff);
		Real fNorm = Math::Sqrt(fPmax*fRoot);
		return fNorm;
	}
	//-----------------------------------------------------------------------
	void Matrix3::toAxisAngle (Vector3& rkAxis, Radian& rfRadians) const
	{
		// Let (x,y,z) be the unit-length axis and let A be an angle of rotation.
		// The rotation matrix is R = I + sin(A)*P + (1-cos(A))*P^2 where
		// I is the identity and
		//
		//       +-        -+
		//   P = |  0 -z +y |
		//       | +z  0 -x |
		//       | -y +x  0 |
		//       +-        -+
		//
		// If A > 0, R represents a counterclockwise rotation about the axis in
		// the sense of looking from the tip of the axis vector towards the
		// origin.  Some algebra will show that
		//
		//   cos(A) = (trace(R)-1)/2  and  R - R^t = 2*sin(A)*P
		//
		// In the event that A = pi, R-R^t = 0 which prevents us from extracting
		// the axis through P.  Instead note that R = I+2*P^2 when A = pi, so
		// P^2 = (R-I)/2.  The diagonal entries of P^2 are x^2-1, y^2-1, and
		// z^2-1.  We can solve these for axis (x,y,z).  Because the angle is pi,
		// it does not matter which sign you choose on the square roots.

		Real fTrace = m[0][0] + m[1][1] + m[2][2];
		Real fCos = 0.5*(fTrace-1.0);
		rfRadians = Math::ACos(fCos);  // in [0,PI]

		if ( rfRadians > Radian(0.0) )
		{
			if ( rfRadians < Radian(Math::PI) )
			{
				rkAxis.x = m[2][1]-m[1][2];
				rkAxis.y = m[0][2]-m[2][0];
				rkAxis.z = m[1][0]-m[0][1];
				rkAxis.normalise();
			}
			else
			{
				// angle is PI
				float fHalfInverse;
				if ( m[0][0] >= m[1][1] )
				{
					// r00 >= r11
					if ( m[0][0] >= m[2][2] )
					{
						// r00 is maximum diagonal term
						rkAxis.x = 0.5*Math::Sqrt(m[0][0] -
							m[1][1] - m[2][2] + 1.0);
						fHalfInverse = 0.5/rkAxis.x;
						rkAxis.y = fHalfInverse*m[0][1];
						rkAxis.z = fHalfInverse*m[0][2];
					}
					else
					{
						// r22 is maximum diagonal term
						rkAxis.z = 0.5*Math::Sqrt(m[2][2] -
							m[0][0] - m[1][1] + 1.0);
						fHalfInverse = 0.5/rkAxis.z;
						rkAxis.x = fHalfInverse*m[0][2];
						rkAxis.y = fHalfInverse*m[1][2];
					}
				}
				else
				{
					// r11 > r00
					if ( m[1][1] >= m[2][2] )
					{
						// r11 is maximum diagonal term
						rkAxis.y = 0.5*Math::Sqrt(m[1][1] -
							m[0][0] - m[2][2] + 1.0);
						fHalfInverse  = 0.5/rkAxis.y;
						rkAxis.x = fHalfInverse*m[0][1];
						rkAxis.z = fHalfInverse*m[1][2];
					}
					else
					{
						// r22 is maximum diagonal term
						rkAxis.z = 0.5*Math::Sqrt(m[2][2] -
							m[0][0] - m[1][1] + 1.0);
						fHalfInverse = 0.5/rkAxis.z;
						rkAxis.x = fHalfInverse*m[0][2];
						rkAxis.y = fHalfInverse*m[1][2];
					}
				}
			}
		}
		else
		{
			// The angle is 0 and the matrix is the identity.  Any axis will
			// work, so just use the x-axis.
			rkAxis.x = 1.0;
			rkAxis.y = 0.0;
			rkAxis.z = 0.0;
		}
	}
	//-----------------------------------------------------------------------
	void Matrix3::fromAxisAngle (const Vector3& rkAxis, const Radian& fRadians)
	{
		Real fCos = Math::Cos(fRadians);
		Real fSin = Math::Sin(fRadians);
		Real fOneMinusCos = 1.0-fCos;
		Real fX2 = rkAxis.x*rkAxis.x;
		Real fY2 = rkAxis.y*rkAxis.y;
		Real fZ2 = rkAxis.z*rkAxis.z;
		Real fXYM = rkAxis.x*rkAxis.y*fOneMinusCos;
		Real fXZM = rkAxis.x*rkAxis.z*fOneMinusCos;
		Real fYZM = rkAxis.y*rkAxis.z*fOneMinusCos;
		Real fXSin = rkAxis.x*fSin;
		Real fYSin = rkAxis.y*fSin;
		Real fZSin = rkAxis.z*fSin;

		m[0][0] = fX2*fOneMinusCos+fCos;
		m[0][1] = fXYM-fZSin;
		m[0][2] = fXZM+fYSin;
		m[1][0] = fXYM+fZSin;
		m[1][1] = fY2*fOneMinusCos+fCos;
		m[1][2] = fYZM-fXSin;
		m[2][0] = fXZM-fYSin;
		m[2][1] = fYZM+fXSin;
		m[2][2] = fZ2*fOneMinusCos+fCos;
	}
	void Matrix3::fromAxisAngle (const Vector3& rkAxis, const Real& fReals)
	{
		Real fCos = Math::Cos(fReals);
		Real fSin = Math::Sin(fReals);
		Real fOneMinusCos = 1.0-fCos;
		Real fX2 = rkAxis.x*rkAxis.x;
		Real fY2 = rkAxis.y*rkAxis.y;
		Real fZ2 = rkAxis.z*rkAxis.z;
		Real fXYM = rkAxis.x*rkAxis.y*fOneMinusCos;
		Real fXZM = rkAxis.x*rkAxis.z*fOneMinusCos;
		Real fYZM = rkAxis.y*rkAxis.z*fOneMinusCos;
		Real fXSin = rkAxis.x*fSin;
		Real fYSin = rkAxis.y*fSin;
		Real fZSin = rkAxis.z*fSin;

		m[0][0] = fX2*fOneMinusCos+fCos;
		m[0][1] = fXYM-fZSin;
		m[0][2] = fXZM+fYSin;
		m[1][0] = fXYM+fZSin;
		m[1][1] = fY2*fOneMinusCos+fCos;
		m[1][2] = fYZM-fXSin;
		m[2][0] = fXZM-fYSin;
		m[2][1] = fYZM+fXSin;
		m[2][2] = fZ2*fOneMinusCos+fCos;
	}
	void Matrix3::fromAxisAngle (const Vector3& rkAxis, const Degree& fDegrees)
	{
		Real fCos = Math::Cos(fDegrees);
		Real fSin = Math::Sin(fDegrees);
		Real fOneMinusCos = 1.0-fCos;
		Real fX2 = rkAxis.x*rkAxis.x;
		Real fY2 = rkAxis.y*rkAxis.y;
		Real fZ2 = rkAxis.z*rkAxis.z;
		Real fXYM = rkAxis.x*rkAxis.y*fOneMinusCos;
		Real fXZM = rkAxis.x*rkAxis.z*fOneMinusCos;
		Real fYZM = rkAxis.y*rkAxis.z*fOneMinusCos;
		Real fXSin = rkAxis.x*fSin;
		Real fYSin = rkAxis.y*fSin;
		Real fZSin = rkAxis.z*fSin;

		m[0][0] = fX2*fOneMinusCos+fCos;
		m[0][1] = fXYM-fZSin;
		m[0][2] = fXZM+fYSin;
		m[1][0] = fXYM+fZSin;
		m[1][1] = fY2*fOneMinusCos+fCos;
		m[1][2] = fYZM-fXSin;
		m[2][0] = fXZM-fYSin;
		m[2][1] = fYZM+fXSin;
		m[2][2] = fZ2*fOneMinusCos+fCos;
	}
	//-----------------------------------------------------------------------
	bool Matrix3::toEulerAnglesXYZ (Radian& rfYAngle, Radian& rfPAngle,
		Radian& rfRAngle) const
	{
		// rot =  cy*cz          -cy*sz           sy
		//        cz*sx*sy+cx*sz  cx*cz-sx*sy*sz -cy*sx
		//       -cx*cz*sy+sx*sz  cz*sx+cx*sy*sz  cx*cy

		rfPAngle = Radian(Math::ASin(m[0][2]));
		if ( rfPAngle < Radian(Math::HALF_PI) )
		{
			if ( rfPAngle > Radian(-Math::HALF_PI) )
			{
				rfYAngle = Math::ATan2(-m[1][2],m[2][2]);
				rfRAngle = Math::ATan2(-m[0][1],m[0][0]);
				return true;
			}
			else
			{
				// WARNING.  Not a unique solution.
				Radian fRmY = Math::ATan2(m[1][0],m[1][1]);
				rfRAngle = Radian(0.0);  // any angle works
				rfYAngle = rfRAngle - fRmY;
				return false;
			}
		}
		else
		{
			// WARNING.  Not a unique solution.
			Radian fRpY = Math::ATan2(m[1][0],m[1][1]);
			rfRAngle = Radian(0.0);  // any angle works
			rfYAngle = fRpY - rfRAngle;
			return false;
		}
	}
	//-----------------------------------------------------------------------
	bool Matrix3::toEulerAnglesXZY (Radian& rfYAngle, Radian& rfPAngle,
		Radian& rfRAngle) const
	{
		// rot =  cy*cz          -sz              cz*sy
		//        sx*sy+cx*cy*sz  cx*cz          -cy*sx+cx*sy*sz
		//       -cx*sy+cy*sx*sz  cz*sx           cx*cy+sx*sy*sz

		rfPAngle = Math::ASin(-m[0][1]);
		if ( rfPAngle < Radian(Math::HALF_PI) )
		{
			if ( rfPAngle > Radian(-Math::HALF_PI) )
			{
				rfYAngle = Math::ATan2(m[2][1],m[1][1]);
				rfRAngle = Math::ATan2(m[0][2],m[0][0]);
				return true;
			}
			else
			{
				// WARNING.  Not a unique solution.
				Radian fRmY = Math::ATan2(-m[2][0],m[2][2]);
				rfRAngle = Radian(0.0);  // any angle works
				rfYAngle = rfRAngle - fRmY;
				return false;
			}
		}
		else
		{
			// WARNING.  Not a unique solution.
			Radian fRpY = Math::ATan2(-m[2][0],m[2][2]);
			rfRAngle = Radian(0.0);  // any angle works
			rfYAngle = fRpY - rfRAngle;
			return false;
		}
	}
	//-----------------------------------------------------------------------
	bool Matrix3::toEulerAnglesYXZ (Radian& rfYAngle, Radian& rfPAngle,
		Radian& rfRAngle) const
	{
		// rot =  cy*cz+sx*sy*sz  cz*sx*sy-cy*sz  cx*sy
		//        cx*sz           cx*cz          -sx
		//       -cz*sy+cy*sx*sz  cy*cz*sx+sy*sz  cx*cy

		rfPAngle = Math::ASin(-m[1][2]);
		if ( rfPAngle < Radian(Math::HALF_PI) )
		{
			if ( rfPAngle > Radian(-Math::HALF_PI) )
			{
				rfYAngle = Math::ATan2(m[0][2],m[2][2]);
				rfRAngle = Math::ATan2(m[1][0],m[1][1]);
				return true;
			}
			else
			{
				// WARNING.  Not a unique solution.
				Radian fRmY = Math::ATan2(-m[0][1],m[0][0]);
				rfRAngle = Radian(0.0);  // any angle works
				rfYAngle = rfRAngle - fRmY;
				return false;
			}
		}
		else
		{
			// WARNING.  Not a unique solution.
			Radian fRpY = Math::ATan2(-m[0][1],m[0][0]);
			rfRAngle = Radian(0.0);  // any angle works
			rfYAngle = fRpY - rfRAngle;
			return false;
		}
	}
	//-----------------------------------------------------------------------
	bool Matrix3::toEulerAnglesYZX (Radian& rfYAngle, Radian& rfPAngle,
		Radian& rfRAngle) const
	{
		// rot =  cy*cz           sx*sy-cx*cy*sz  cx*sy+cy*sx*sz
		//        sz              cx*cz          -cz*sx
		//       -cz*sy           cy*sx+cx*sy*sz  cx*cy-sx*sy*sz

		rfPAngle = Math::ASin(m[1][0]);
		if ( rfPAngle < Radian(Math::HALF_PI) )
		{
			if ( rfPAngle > Radian(-Math::HALF_PI) )
			{
				rfYAngle = Math::ATan2(-m[2][0],m[0][0]);
				rfRAngle = Math::ATan2(-m[1][2],m[1][1]);
				return true;
			}
			else
			{
				// WARNING.  Not a unique solution.
				Radian fRmY = Math::ATan2(m[2][1],m[2][2]);
				rfRAngle = Radian(0.0);  // any angle works
				rfYAngle = rfRAngle - fRmY;
				return false;
			}
		}
		else
		{
			// WARNING.  Not a unique solution.
			Radian fRpY = Math::ATan2(m[2][1],m[2][2]);
			rfRAngle = Radian(0.0);  // any angle works
			rfYAngle = fRpY - rfRAngle;
			return false;
		}
	}
	//-----------------------------------------------------------------------
	bool Matrix3::toEulerAnglesZXY (Radian& rfYAngle, Radian& rfPAngle,
		Radian& rfRAngle) const
	{
		// rot =  cy*cz-sx*sy*sz -cx*sz           cz*sy+cy*sx*sz
		//        cz*sx*sy+cy*sz  cx*cz          -cy*cz*sx+sy*sz
		//       -cx*sy           sx              cx*cy

		rfPAngle = Math::ASin(m[2][1]);
		if ( rfPAngle < Radian(Math::HALF_PI) )
		{
			if ( rfPAngle > Radian(-Math::HALF_PI) )
			{
				rfYAngle = Math::ATan2(-m[0][1],m[1][1]);
				rfRAngle = Math::ATan2(-m[2][0],m[2][2]);
				return true;
			}
			else
			{
				// WARNING.  Not a unique solution.
				Radian fRmY = Math::ATan2(m[0][2],m[0][0]);
				rfRAngle = Radian(0.0);  // any angle works
				rfYAngle = rfRAngle - fRmY;
				return false;
			}
		}
		else
		{
			// WARNING.  Not a unique solution.
			Radian fRpY = Math::ATan2(m[0][2],m[0][0]);
			rfRAngle = Radian(0.0);  // any angle works
			rfYAngle = fRpY - rfRAngle;
			return false;
		}
	}
	//-----------------------------------------------------------------------
	bool Matrix3::toEulerAnglesZYX (Radian& rfYAngle, Radian& rfPAngle,
		Radian& rfRAngle) const
	{
		// rot =  cy*cz           cz*sx*sy-cx*sz  cx*cz*sy+sx*sz
		//        cy*sz           cx*cz+sx*sy*sz -cz*sx+cx*sy*sz
		//       -sy              cy*sx           cx*cy

		rfPAngle = Math::ASin(-m[2][0]);
		if ( rfPAngle < Radian(Math::HALF_PI) )
		{
			if ( rfPAngle > Radian(-Math::HALF_PI) )
			{
				rfYAngle = Math::ATan2(m[1][0],m[0][0]);
				rfRAngle = Math::ATan2(m[2][1],m[2][2]);
				return true;
			}
			else
			{
				// WARNING.  Not a unique solution.
				Radian fRmY = Math::ATan2(-m[0][1],m[0][2]);
				rfRAngle = Radian(0.0);  // any angle works
				rfYAngle = rfRAngle - fRmY;
				return false;
			}
		}
		else
		{
			// WARNING.  Not a unique solution.
			Radian fRpY = Math::ATan2(-m[0][1],m[0][2]);
			rfRAngle = Radian(0.0);  // any angle works
			rfYAngle = fRpY - rfRAngle;
			return false;
		}
	}
	//-----------------------------------------------------------------------
	void Matrix3::fromEulerAnglesXYZ (const Radian& fYAngle, const Radian& fPAngle,
		const Radian& fRAngle)
	{
		Real fCos, fSin;

		fCos = Math::Cos(fYAngle);
		fSin = Math::Sin(fYAngle);
		Matrix3 kXMat(1.0,0.0,0.0,0.0,fCos,-fSin,0.0,fSin,fCos);

		fCos = Math::Cos(fPAngle);
		fSin = Math::Sin(fPAngle);
		Matrix3 kYMat(fCos,0.0,fSin,0.0,1.0,0.0,-fSin,0.0,fCos);

		fCos = Math::Cos(fRAngle);
		fSin = Math::Sin(fRAngle);
		Matrix3 kZMat(fCos,-fSin,0.0,fSin,fCos,0.0,0.0,0.0,1.0);

		*this = kXMat*(kYMat*kZMat);
	}
	//-----------------------------------------------------------------------
	void Matrix3::fromEulerAnglesXZY (const Radian& fYAngle, const Radian& fPAngle,
		const Radian& fRAngle)
	{
		Real fCos, fSin;

		fCos = Math::Cos(fYAngle);
		fSin = Math::Sin(fYAngle);
		Matrix3 kXMat(1.0,0.0,0.0,0.0,fCos,-fSin,0.0,fSin,fCos);

		fCos = Math::Cos(fPAngle);
		fSin = Math::Sin(fPAngle);
		Matrix3 kZMat(fCos,-fSin,0.0,fSin,fCos,0.0,0.0,0.0,1.0);

		fCos = Math::Cos(fRAngle);
		fSin = Math::Sin(fRAngle);
		Matrix3 kYMat(fCos,0.0,fSin,0.0,1.0,0.0,-fSin,0.0,fCos);

		*this = kXMat*(kZMat*kYMat);
	}
	//-----------------------------------------------------------------------
	void Matrix3::fromEulerAnglesYXZ (const Radian& fYAngle, const Radian& fPAngle,
		const Radian& fRAngle)
	{
		Real fCos, fSin;

		fCos = Math::Cos(fYAngle);
		fSin = Math::Sin(fYAngle);
		Matrix3 kYMat(fCos,0.0,fSin,0.0,1.0,0.0,-fSin,0.0,fCos);

		fCos = Math::Cos(fPAngle);
		fSin = Math::Sin(fPAngle);
		Matrix3 kXMat(1.0,0.0,0.0,0.0,fCos,-fSin,0.0,fSin,fCos);

		fCos = Math::Cos(fRAngle);
		fSin = Math::Sin(fRAngle);
		Matrix3 kZMat(fCos,-fSin,0.0,fSin,fCos,0.0,0.0,0.0,1.0);

		*this = kYMat*(kXMat*kZMat);
	}
	//-----------------------------------------------------------------------
	void Matrix3::fromEulerAnglesYZX (const Radian& fYAngle, const Radian& fPAngle,
		const Radian& fRAngle)
	{
		Real fCos, fSin;

		fCos = Math::Cos(fYAngle);
		fSin = Math::Sin(fYAngle);
		Matrix3 kYMat(fCos,0.0,fSin,0.0,1.0,0.0,-fSin,0.0,fCos);

		fCos = Math::Cos(fPAngle);
		fSin = Math::Sin(fPAngle);
		Matrix3 kZMat(fCos,-fSin,0.0,fSin,fCos,0.0,0.0,0.0,1.0);

		fCos = Math::Cos(fRAngle);
		fSin = Math::Sin(fRAngle);
		Matrix3 kXMat(1.0,0.0,0.0,0.0,fCos,-fSin,0.0,fSin,fCos);

		*this = kYMat*(kZMat*kXMat);
	}
	//-----------------------------------------------------------------------
	void Matrix3::fromEulerAnglesZXY (const Radian& fYAngle, const Radian& fPAngle,
		const Radian& fRAngle)
	{
		Real fCos, fSin;

		fCos = Math::Cos(fYAngle);
		fSin = Math::Sin(fYAngle);
		Matrix3 kZMat(fCos,-fSin,0.0,fSin,fCos,0.0,0.0,0.0,1.0);

		fCos = Math::Cos(fPAngle);
		fSin = Math::Sin(fPAngle);
		Matrix3 kXMat(1.0,0.0,0.0,0.0,fCos,-fSin,0.0,fSin,fCos);

		fCos = Math::Cos(fRAngle);
		fSin = Math::Sin(fRAngle);
		Matrix3 kYMat(fCos,0.0,fSin,0.0,1.0,0.0,-fSin,0.0,fCos);

		*this = kZMat*(kXMat*kYMat);
	}
	//-----------------------------------------------------------------------
	void Matrix3::fromEulerAnglesZYX (const Radian& fYAngle, const Radian& fPAngle,
		const Radian& fRAngle)
	{
		Real fCos, fSin;

		fCos = Math::Cos(fYAngle);
		fSin = Math::Sin(fYAngle);
		Matrix3 kZMat(fCos,-fSin,0.0,fSin,fCos,0.0,0.0,0.0,1.0);

		fCos = Math::Cos(fPAngle);
		fSin = Math::Sin(fPAngle);
		Matrix3 kYMat(fCos,0.0,fSin,0.0,1.0,0.0,-fSin,0.0,fCos);

		fCos = Math::Cos(fRAngle);
		fSin = Math::Sin(fRAngle);
		Matrix3 kXMat(1.0,0.0,0.0,0.0,fCos,-fSin,0.0,fSin,fCos);

		*this = kZMat*(kYMat*kXMat);
	}
	//-----------------------------------------------------------------------
	//void Matrix3::tridiagonal (Real afDiag[3], Real afSubDiag[3])
	//{
	//	// Householder reduction T = Q^t M Q
	//	//   Input:
	//	//     mat, symmetric 3x3 matrix M
	//	//   Output:
	//	//     mat, orthogonal matrix Q
	//	//     diag, diagonal entries of T
	//	//     subd, subdiagonal entries of T (T is symmetric)

	//	Real fA = m[0][0];
	//	Real fB = m[0][1];
	//	Real fC = m[0][2];
	//	Real fD = m[1][1];
	//	Real fE = m[1][2];
	//	Real fF = m[2][2];

	//	afDiag[0] = fA;
	//	afSubDiag[2] = 0.0;
	//	if ( Math::Abs(fC) >= EPSILON )
	//	{
	//		Real fLength = Math::Sqrt(fB*fB+fC*fC);
	//		Real fInvLength = 1.0/fLength;
	//		fB *= fInvLength;
	//		fC *= fInvLength;
	//		Real fQ = 2.0*fB*fE+fC*(fF-fD);
	//		afDiag[1] = fD+fC*fQ;
	//		afDiag[2] = fF-fC*fQ;
	//		afSubDiag[0] = fLength;
	//		afSubDiag[1] = fE-fB*fQ;
	//		m[0][0] = 1.0;
	//		m[0][1] = 0.0;
	//		m[0][2] = 0.0;
	//		m[1][0] = 0.0;
	//		m[1][1] = fB;
	//		m[1][2] = fC;
	//		m[2][0] = 0.0;
	//		m[2][1] = fC;
	//		m[2][2] = -fB;
	//	}
	//	else
	//	{
	//		afDiag[1] = fD;
	//		afDiag[2] = fF;
	//		afSubDiag[0] = fB;
	//		afSubDiag[1] = fE;
	//		m[0][0] = 1.0;
	//		m[0][1] = 0.0;
	//		m[0][2] = 0.0;
	//		m[1][0] = 0.0;
	//		m[1][1] = 1.0;
	//		m[1][2] = 0.0;
	//		m[2][0] = 0.0;
	//		m[2][1] = 0.0;
	//		m[2][2] = 1.0;
	//	}
	//}
	//-----------------------------------------------------------------------
	bool Matrix3::QLAlgorithm (Real afDiag[3], Real afSubDiag[3])
	{
		// This is an implementation of the symmetric QR algorithm from the book
		// "Matrix Computations" by Gene H. Golub and Charles F. Van Loan, second
		// edition.  The algorithm is 8.2.3.  The implementation has a slight
		// variation to actually make it a QL algorithm, and it traps the case
		// when either of the subdiagonal terms s0 or s1 is zero and reduces the
		// 2-by-2 subblock directly.

		const int iMax = 32;
		for (int i = 0; i < iMax; i++)
		{
			Real fSum, fDiff, fDiscr, fEValue0, fEValue1, fCos, fSin, fTmp;
			int iRow;

			fSum = Math::Abs(afDiag[0]) + Math::Abs(afDiag[1]);
			if (Math::Abs(afSubDiag[0]) + fSum == fSum)
			{
				// The matrix is effectively
				//       +-        -+
				//   M = | d0  0  0 |
				//       | 0  d1 s1 |
				//       | 0  s1 d2 |
				//       +-        -+

				// Compute the eigenvalues as roots of a quadratic equation.
				fSum = afDiag[1] + afDiag[2];
				fDiff = afDiag[1] - afDiag[2];
				fDiscr = Math::Sqrt(fDiff*fDiff +
					((Real)4.0)*afSubDiag[1]*afSubDiag[1]);
				fEValue0 = ((Real)0.5)*(fSum - fDiscr);
				fEValue1 = ((Real)0.5)*(fSum + fDiscr);

				// Compute the Givens rotation.
				if (fDiff >= (Real)0.0)
				{
					fCos = afSubDiag[1];
					fSin = afDiag[1] - fEValue0;
				}
				else
				{
					fCos = afDiag[2] - fEValue0;
					fSin = afSubDiag[1];
				}
				fTmp = Math::InvSqrt(fCos*fCos + fSin*fSin);
				fCos *= fTmp;
				fSin *= fTmp;

				// Postmultiply the current orthogonal matrix with the Givens
				// rotation.
				for (iRow = 0; iRow < 3; iRow++)
				{
					fTmp = v[2+3*iRow];
					v[2+3*iRow] = fSin*v[1+3*iRow] + fCos*fTmp;
					v[1+3*iRow] = fCos*v[1+3*iRow] - fSin*fTmp;
				}

				// Update the tridiagonal matrix.
				afDiag[1] = fEValue0;
				afDiag[2] = fEValue1;
				afSubDiag[0] = (Real)0.0;
				afSubDiag[1] = (Real)0.0;
				return true;
			}

			fSum = Math::Abs(afDiag[1]) + Math::Abs(afDiag[2]);
			if (Math::Abs(afSubDiag[1]) + fSum == fSum)
			{
				// The matrix is effectively
				//       +-         -+
				//   M = | d0  s0  0 |
				//       | s0  d1  0 |
				//       | 0   0  d2 |
				//       +-         -+

				// Compute the eigenvalues as roots of a quadratic equation.
				fSum = afDiag[0] + afDiag[1];
				fDiff = afDiag[0] - afDiag[1];
				fDiscr = Math::Sqrt(fDiff*fDiff +
					((Real)4.0)*afSubDiag[0]*afSubDiag[0]);
				fEValue0 = ((Real)0.5)*(fSum - fDiscr);
				fEValue1 = ((Real)0.5)*(fSum + fDiscr);

				// Compute the Givens rotation.
				if (fDiff >= (Real)0.0)
				{
					fCos = afSubDiag[0];
					fSin = afDiag[0] - fEValue0;
				}
				else
				{
					fCos = afDiag[1] - fEValue0;
					fSin = afSubDiag[0];
				}
				fTmp = Math::InvSqrt(fCos*fCos + fSin*fSin);
				fCos *= fTmp;
				fSin *= fTmp;

				// Postmultiply the current orthogonal matrix with the Givens
				// rotation.
				for (iRow = 0; iRow < 3; iRow++)
				{
					fTmp = v[1+3*iRow];
					v[1+3*iRow] = fSin*v[0+3*iRow] + fCos*fTmp;
					v[0+3*iRow] = fCos*v[0+3*iRow] - fSin*fTmp;
				}

				// Update the tridiagonal matrix.
				afDiag[0] = fEValue0;
				afDiag[1] = fEValue1;
				afSubDiag[0] = (Real)0.0;
				afSubDiag[1] = (Real)0.0;
				return true;
			}

			// The matrix is
			//       +-        -+
			//   M = | d0 s0  0 |
			//       | s0 d1 s1 |
			//       | 0  s1 d2 |
			//       +-        -+

			// Set up the parameters for the first pass of the QL step.  The
			// value for A is the difference between diagonal term D[2] and the
			// implicit shift suggested by Wilkinson.
			Real fRatio = (afDiag[1]-afDiag[0])/(((Real)2.0f)*afSubDiag[0]);
			Real fRoot = Math::Sqrt((Real)1.0 + fRatio*fRatio);
			Real fB = afSubDiag[1];
			Real fA = afDiag[2] - afDiag[0];
			if (fRatio >= (Real)0.0)
			{
				fA += afSubDiag[0]/(fRatio + fRoot);
			}
			else
			{
				fA += afSubDiag[0]/(fRatio - fRoot);
			}

			// Compute the Givens rotation for the first pass.
			if (Math::Abs(fB) >= Math::Abs(fA))
			{
				fRatio = fA/fB;
				fSin = Math::InvSqrt((Real)1.0 + fRatio*fRatio);
				fCos = fRatio*fSin;
			}
			else
			{
				fRatio = fB/fA;
				fCos = Math::InvSqrt((Real)1.0 + fRatio*fRatio);
				fSin = fRatio*fCos;
			}

			// Postmultiply the current orthogonal matrix with the Givens
			// rotation.
			for (iRow = 0; iRow < 3; iRow++)
			{
				fTmp = v[2+3*iRow];
				v[2+3*iRow] = fSin*v[1+3*iRow]+fCos*fTmp;
				v[1+3*iRow] = fCos*v[1+3*iRow]-fSin*fTmp;
			}

			// Set up the parameters for the second pass of the QL step.  The
			// values tmp0 and tmp1 are required to fully update the tridiagonal
			// matrix at the end of the second pass.
			Real fTmp0 = (afDiag[1] - afDiag[2])*fSin +
				((Real)2.0)*afSubDiag[1]*fCos;
			Real fTmp1 = fCos*afSubDiag[0];
			fB = fSin*afSubDiag[0];
			fA = fCos*fTmp0 - afSubDiag[1];
			fTmp0 *= fSin;

			// Compute the Givens rotation for the second pass.  The subdiagonal
			// term S[1] in the tridiagonal matrix is updated at this time.
			if (Math::Abs(fB) >= Math::Abs(fA))
			{
				fRatio = fA/fB;
				fRoot = Math::Sqrt((Real)1.0 + fRatio*fRatio);
				afSubDiag[1] = fB*fRoot;
				fSin = ((Real)1.0)/fRoot;
				fCos = fRatio*fSin;
			}
			else
			{
				fRatio = fB/fA;
				fRoot = Math::Sqrt((Real)1.0 + fRatio*fRatio);
				afSubDiag[1] = fA*fRoot;
				fCos = ((Real)1.0)/fRoot;
				fSin = fRatio*fCos;
			}

			// Postmultiply the current orthogonal matrix with the Givens
			// rotation.
			for (iRow = 0; iRow < 3; iRow++)
			{
				fTmp = v[1+3*iRow];
				v[1+3*iRow] = fSin*v[0+3*iRow]+fCos*fTmp;
				v[0+3*iRow] = fCos*v[0+3*iRow]-fSin*fTmp;
			}

			// Complete the update of the tridiagonal matrix.
			Real fTmp2 = afDiag[1] - fTmp0;
			afDiag[2] += fTmp0;
			fTmp0 = (afDiag[0] - fTmp2)*fSin + ((Real)2.0)*fTmp1*fCos;
			afSubDiag[0] = fCos*fTmp0 - fTmp1;
			fTmp0 *= fSin;
			afDiag[1] = fTmp2 + fTmp0;
			afDiag[0] -= fTmp0;
		}
		return false;
	}
	//-----------------------------------------------------------------------
	void Matrix3::EigenSolveSymmetric (Real afEigenvalue[3],
		Vector3 akEigenvector[3]) const
	{
		Matrix3 kMatrix = *this;
		Real afSubDiag[3];
		kMatrix.tridiagonalize(afEigenvalue,afSubDiag);
		kMatrix.QLAlgorithm(afEigenvalue,afSubDiag);

		for (size_t i = 0; i < 3; i++)
		{
			akEigenvector[i][0] = kMatrix[0][i];
			akEigenvector[i][1] = kMatrix[1][i];
			akEigenvector[i][2] = kMatrix[2][i];
		}

		// make eigenvectors form a right--handed system
		Vector3 kCross = akEigenvector[1].crossProduct(akEigenvector[2]);
		Real fDet = akEigenvector[0].dotProduct(kCross);
		if ( fDet < 0.0 )
		{
			akEigenvector[2][0] = - akEigenvector[2][0];
			akEigenvector[2][1] = - akEigenvector[2][1];
			akEigenvector[2][2] = - akEigenvector[2][2];
		}
	}
	//-----------------------------------------------------------------------
	void Matrix3::TensorProduct (const Vector3& rkU, const Vector3& rkV,
		Matrix3& rkProduct)
	{
		for (size_t iRow = 0; iRow < 3; iRow++)
		{
			for (size_t iCol = 0; iCol < 3; iCol++)
				rkProduct[iRow][iCol] = rkU[iRow]*rkV[iCol];
		}
	}
	//-----------------------------------------------------------------------


	Matrix3 Matrix3::crossProduct( const Matrix3& rkm ) const
	{
		return (*this) * rkm;
	}

	//----------------------------------------------------------------------------
	 
	Matrix3& Matrix3::operator+= (const Matrix3& rkM)
	{
		v[0] += rkM.v[0];
		v[1] += rkM.v[1];
		v[2] += rkM.v[2];
		v[3] += rkM.v[3];
		v[4] += rkM.v[4];
		v[5] += rkM.v[5];
		v[6] += rkM.v[6];
		v[7] += rkM.v[7];
		v[8] += rkM.v[8];
		return *this;
	}
	//----------------------------------------------------------------------------
	 
	Matrix3& Matrix3::operator-= (const Matrix3& rkM)
	{
		v[0] -= rkM.v[0];
		v[1] -= rkM.v[1];
		v[2] -= rkM.v[2];
		v[3] -= rkM.v[3];
		v[4] -= rkM.v[4];
		v[5] -= rkM.v[5];
		v[6] -= rkM.v[6];
		v[7] -= rkM.v[7];
		v[8] -= rkM.v[8];
		return *this;
	}
	//----------------------------------------------------------------------------
	 
	Matrix3& Matrix3::operator*= (Real fScalar)
	{
		v[0] *= fScalar;
		v[1] *= fScalar;
		v[2] *= fScalar;
		v[3] *= fScalar;
		v[4] *= fScalar;
		v[5] *= fScalar;
		v[6] *= fScalar;
		v[7] *= fScalar;
		v[8] *= fScalar;
		return *this;
	}
	//----------------------------------------------------------------------------
	 
	Matrix3& Matrix3::operator/= (Real fScalar)
	{
		if (fScalar != (Real)0.0)
		{
			Real fInvScalar = ((Real)1.0)/fScalar;
			v[0] *= fInvScalar;
			v[1] *= fInvScalar;
			v[2] *= fInvScalar;
			v[3] *= fInvScalar;
			v[4] *= fInvScalar;
			v[5] *= fInvScalar;
			v[6] *= fInvScalar;
			v[7] *= fInvScalar;
			v[8] *= fInvScalar;
		}
		else
		{
			v[0] = Math::MAX_REAL;
			v[1] = Math::MAX_REAL;
			v[2] = Math::MAX_REAL;
			v[3] = Math::MAX_REAL;
			v[4] = Math::MAX_REAL;
			v[5] = Math::MAX_REAL;
			v[6] = Math::MAX_REAL;
			v[7] = Math::MAX_REAL;
			v[8] = Math::MAX_REAL;
		}

		return *this;
	}

	//----------------------------------------------------------------
	Matrix3 Matrix3::transposeTimes (const Matrix3& rkM) const
	{
		// P = A^T*B
		return Matrix3(
			v[0]*rkM.v[0] +
			v[3]*rkM.v[3] +
			v[6]*rkM.v[6],

			v[0]*rkM.v[1] +
			v[3]*rkM.v[4] +
			v[6]*rkM.v[7],

			v[0]*rkM.v[2] +
			v[3]*rkM.v[5] +
			v[6]*rkM.v[8],

			v[1]*rkM.v[0] +
			v[4]*rkM.v[3] +
			v[7]*rkM.v[6],

			v[1]*rkM.v[1] +
			v[4]*rkM.v[4] +
			v[7]*rkM.v[7],

			v[1]*rkM.v[2] +
			v[4]*rkM.v[5] +
			v[7]*rkM.v[8],

			v[2]*rkM.v[0] +
			v[5]*rkM.v[3] +
			v[8]*rkM.v[6],

			v[2]*rkM.v[1] +
			v[5]*rkM.v[4] +
			v[8]*rkM.v[7],

			v[2]*rkM.v[2] +
			v[5]*rkM.v[5] +
			v[8]*rkM.v[8]);
	}
	//----------------------------------------------------------------------------
	Matrix3 Matrix3::timesTranspose (const Matrix3& rkM) const
	{
		// P = A*B^T
		return Matrix3(
			v[0]*rkM.v[0] +
			v[1]*rkM.v[1] +
			v[2]*rkM.v[2],

			v[0]*rkM.v[3] +
			v[1]*rkM.v[4] +
			v[2]*rkM.v[5],

			v[0]*rkM.v[6] +
			v[1]*rkM.v[7] +
			v[2]*rkM.v[8],

			v[3]*rkM.v[0] +
			v[4]*rkM.v[1] +
			v[5]*rkM.v[2],

			v[3]*rkM.v[3] +
			v[4]*rkM.v[4] +
			v[5]*rkM.v[5],

			v[3]*rkM.v[6] +
			v[4]*rkM.v[7] +
			v[5]*rkM.v[8],

			v[6]*rkM.v[0] +
			v[7]*rkM.v[1] +
			v[8]*rkM.v[2],

			v[6]*rkM.v[3] +
			v[7]*rkM.v[4] +
			v[8]*rkM.v[5],

			v[6]*rkM.v[6] +
			v[7]*rkM.v[7] +
			v[8]*rkM.v[8]);
	}
	//----------------------------------------------------------------
	Matrix3 Matrix3::adjoint () const
	{
		return Matrix3(
			v[4]*v[8] - v[5]*v[7],
			v[2]*v[7] - v[1]*v[8],
			v[1]*v[5] - v[2]*v[4],
			v[5]*v[6] - v[3]*v[8],
			v[0]*v[8] - v[2]*v[6],
			v[2]*v[3] - v[0]*v[5],
			v[3]*v[7] - v[4]*v[6],
			v[1]*v[6] - v[0]*v[7],
			v[0]*v[4] - v[1]*v[3]);
	}
	//----------------------------------------------------------------
	//----------------------------------------------------------------------------
	void Matrix3::eigenDecomposition (Matrix3& rkRot, Matrix3& rkDiag) const
	{
		// Factor M = R*D*R^T.  The columns of R are the eigenvectors.  The
		// diagonal entries of D are the corresponding eigenvalues.
		Real afDiag[3], afSubd[2];
		rkRot = *this;
		bool bReflection = rkRot.tridiagonalize(afDiag,afSubd);
		bool bConverged = rkRot.QLAlgorithm(afDiag,afSubd);

		assert(bConverged  && "求解特征向量时出现错误!");

		// (insertion) sort eigenvalues in increasing order, d0 <= d1 <= d2
		int i;
		Real fSave;

		if (afDiag[1] < afDiag[0])
		{
			// swap d0 and d1
			fSave = afDiag[0];
			afDiag[0] = afDiag[1];
			afDiag[1] = fSave;

			// swap V0 and V1
			for (i = 0; i < 3; i++)
			{
				fSave = rkRot[i][0];
				rkRot[i][0] = rkRot[i][1];
				rkRot[i][1] = fSave;
			}
			bReflection = !bReflection;
		}

		if (afDiag[2] < afDiag[1])
		{
			// swap d1 and d2
			fSave = afDiag[1];
			afDiag[1] = afDiag[2];
			afDiag[2] = fSave;

			// swap V1 and V2
			for (i = 0; i < 3; i++)
			{
				fSave = rkRot[i][1];
				rkRot[i][1] = rkRot[i][2];
				rkRot[i][2] = fSave;
			}
			bReflection = !bReflection;
		}

		if (afDiag[1] < afDiag[0])
		{
			// swap d0 and d1
			fSave = afDiag[0];
			afDiag[0] = afDiag[1];
			afDiag[1] = fSave;

			// swap V0 and V1
			for (i = 0; i < 3; i++)
			{
				fSave = rkRot[i][0];
				rkRot[i][0] = rkRot[i][1];
				rkRot[i][1] = fSave;
			}
			bReflection = !bReflection;
		}

		rkDiag.makeDiagonal(afDiag[0],afDiag[1],afDiag[2]);

		if (bReflection)
		{
			// The orthogonal transformation that diagonalizes M is a reflection.
			// Make the eigenvectors a right--handed system by changing sign on
			// the last column.
			rkRot[0][2] = -rkRot[0][2];
			rkRot[1][2] = -rkRot[1][2];
			rkRot[2][2] = -rkRot[2][2];
		}
	}

	void Matrix3::eigenDecomposition (Real afEigenvalue[3], Vector3 akEigenvector[3]) const
	{
		Matrix3 rkRot;
		Matrix3 rkDiag;

		this->eigenDecomposition(rkRot,rkDiag);
		afEigenvalue[0] = rkDiag.getValueByPosition( 0 , 0 );
		afEigenvalue[1] = rkDiag.getValueByPosition( 1 , 1 );	///未完成!
		afEigenvalue[2] = rkDiag.getValueByPosition( 2 , 2 );

		akEigenvector[0] = rkRot.getColumn(0);
		akEigenvector[1] = rkRot.getColumn(1);
		akEigenvector[2] = rkRot.getColumn(2);
	}
	//----------------------------------------------------------------
	//----------------------------------------------------------------------------
	bool Matrix3::tridiagonalize (Real afDiag[3], Real afSubd[2])
	{
		// Householder reduction T = Q^t M Q
		//   Input:   
		//     mat, symmetric 3x3 matrix M
		//   Output:  
		//     mat, orthogonal matrix Q (a reflection)
		//     diag, diagonal entries of T
		//     subd, subdiagonal entries of T (T is symmetric)

		Real fM00 = v[0];
		Real fM01 = v[1];
		Real fM02 = v[2];
		Real fM11 = v[4];
		Real fM12 = v[5];
		Real fM22 = v[8];

		afDiag[0] = fM00;
		if (Math::Abs(fM02) >= Math::ZERO_TOLERANCE)
		{
			afSubd[0] = Math::Sqrt(fM01*fM01+fM02*fM02);
			Real fInvLength = ((Real)1.0)/afSubd[0];
			fM01 *= fInvLength;
			fM02 *= fInvLength;
			Real fTmp = ((Real)2.0)*fM01*fM12+fM02*(fM22-fM11);
			afDiag[1] = fM11+fM02*fTmp;
			afDiag[2] = fM22-fM02*fTmp;
			afSubd[1] = fM12-fM01*fTmp;

			v[0] = (Real)1.0;
			v[1] = (Real)0.0;
			v[2] = (Real)0.0;
			v[3] = (Real)0.0;
			v[4] = fM01;
			v[5] = fM02;
			v[6] = (Real)0.0;
			v[7] = fM02;
			v[8] = -fM01;
			return true;
		}
		else
		{
			afDiag[1] = fM11;
			afDiag[2] = fM22;
			afSubd[0] = fM01;
			afSubd[1] = fM12;

			v[0] = (Real)1.0;
			v[1] = (Real)0.0;
			v[2] = (Real)0.0;
			v[3] = (Real)0.0;
			v[4] = (Real)1.0;
			v[5] = (Real)0.0;
			v[6] = (Real)0.0;
			v[7] = (Real)0.0;
			v[8] = (Real)1.0;
			return false;
		}
	}

	//----------------------------------------------------------------

	Matrix3 Matrix3::tensorProduct(const Matrix3& rkM ) const
	{
		Matrix3 tm;
		for ( int i = 0 ; i != 9 ; ++ i )
		{
			tm.v[i] = rkM.v[i] * this->v[i];
		}
		return tm;
	}
	//----------------------------------------------------------------
	//----------------------------------------------------------------------------
	void Matrix3::QDUDecomposition (Matrix3& rkQ, Matrix3& rkD,
		Matrix3& rkU) const
	{
		// Factor M = QR = QDU where Q is orthogonal (rotation), D is diagonal
		// (scaling),  and U is upper triangular with ones on its diagonal
		// (shear).  Algorithm uses Gram-Schmidt orthogonalization (the QR
		// algorithm).
		//
		// If M = [ m0 | m1 | m2 ] and Q = [ q0 | q1 | q2 ], then
		//
		//   q0 = m0/|m0|
		//   q1 = (m1-(q0*m1)q0)/|m1-(q0*m1)q0|
		//   q2 = (m2-(q0*m2)q0-(q1*m2)q1)/|m2-(q0*m2)q0-(q1*m2)q1|
		//
		// where |V| indicates length of vector V and A*B indicates dot
		// product of vectors A and B.  The matrix R has entries
		//
		//   r00 = q0*m0  r01 = q0*m1  r02 = q0*m2
		//   r10 = 0      r11 = q1*m1  r12 = q1*m2
		//   r20 = 0      r21 = 0      r22 = q2*m2
		//
		// so D = diag(r00,r11,r22) and U has entries u01 = r01/r00,
		// u02 = r02/r00, and u12 = r12/r11.

		// build orthogonal matrix Q
		Real fInvLength = Math::InvSqrt(v[0]*v[0] +
			v[3]*v[3] + v[6]*v[6]);
		rkQ[0][0] = v[0]*fInvLength;
		rkQ[1][0] = v[3]*fInvLength;
		rkQ[2][0] = v[6]*fInvLength;

		Real fDot = rkQ[0][0]*v[1] + rkQ[1][0]*v[4] +
			rkQ[2][0]*v[7];
		rkQ[0][1] = v[1]-fDot*rkQ[0][0];
		rkQ[1][1] = v[4]-fDot*rkQ[1][0];
		rkQ[2][1] = v[7]-fDot*rkQ[2][0];
		fInvLength = Math::InvSqrt(rkQ[0][1]*rkQ[0][1] +
			rkQ[1][1]*rkQ[1][1] + rkQ[2][1]*rkQ[2][1]);
		rkQ[0][1] *= fInvLength;
		rkQ[1][1] *= fInvLength;
		rkQ[2][1] *= fInvLength;

		fDot = rkQ[0][0]*v[2] + rkQ[1][0]*v[5] +
			rkQ[2][0]*v[8];
		rkQ[0][2] = v[2]-fDot*rkQ[0][0];
		rkQ[1][2] = v[5]-fDot*rkQ[1][0];
		rkQ[2][2] = v[8]-fDot*rkQ[2][0];
		fDot = rkQ[0][1]*v[2] + rkQ[1][1]*v[5] +
			rkQ[2][1]*v[8];
		rkQ[0][2] -= fDot*rkQ[0][1];
		rkQ[1][2] -= fDot*rkQ[1][1];
		rkQ[2][2] -= fDot*rkQ[2][1];
		fInvLength = Math::InvSqrt(rkQ[0][2]*rkQ[0][2] +
			rkQ[1][2]*rkQ[1][2] + rkQ[2][2]*rkQ[2][2]);
		rkQ[0][2] *= fInvLength;
		rkQ[1][2] *= fInvLength;
		rkQ[2][2] *= fInvLength;

		// guarantee that orthogonal matrix has determinant 1 (no reflections)
		Real fDet = rkQ[0][0]*rkQ[1][1]*rkQ[2][2] + rkQ[0][1]*rkQ[1][2]*rkQ[2][0]
		+  rkQ[0][2]*rkQ[1][0]*rkQ[2][1] - rkQ[0][2]*rkQ[1][1]*rkQ[2][0]
		-  rkQ[0][1]*rkQ[1][0]*rkQ[2][2] - rkQ[0][0]*rkQ[1][2]*rkQ[2][1];

		if (fDet < (Real)0.0)
		{
			for (int iRow = 0; iRow < 3; iRow++)
			{
				for (int iCol = 0; iCol < 3; iCol++)
				{
					rkQ[iRow][iCol] = -rkQ[iRow][iCol];
				}
			}
		}

		// build "right" matrix R
		Matrix3 kR;
		kR[0][0] = rkQ[0][0]*v[0] + rkQ[1][0]*v[3] +
			rkQ[2][0]*v[6];
		kR[0][1] = rkQ[0][0]*v[1] + rkQ[1][0]*v[4] +
			rkQ[2][0]*v[7];
		kR[1][1] = rkQ[0][1]*v[1] + rkQ[1][1]*v[4] +
			rkQ[2][1]*v[7];
		kR[0][2] = rkQ[0][0]*v[2] + rkQ[1][0]*v[5] +
			rkQ[2][0]*v[8];
		kR[1][2] = rkQ[0][1]*v[2] + rkQ[1][1]*v[5] +
			rkQ[2][1]*v[8];
		kR[2][2] = rkQ[0][2]*v[2] + rkQ[1][2]*v[5] +
			rkQ[2][2]*v[8];

		// the scaling component
		rkD.makeDiagonal(kR[0][0],kR[1][1],kR[2][2]);

		// the shear component
		Real fInvD0 = ((Real)1.0)/rkD[0][0];
		rkU[0][0] = (Real)1.0;
		rkU[0][1] = kR[0][1]*fInvD0;
		rkU[0][2] = kR[0][2]*fInvD0;
		rkU[1][0] = (Real)0.0;
		rkU[1][1] = (Real)1.0;
		rkU[1][2] = kR[1][2]/rkD[1][1];
		rkU[2][0] = (Real)0.0;
		rkU[2][1] = (Real)0.0;
		rkU[2][2] = (Real)1.0;
	}
	//----------------------------------------------------------------
	//----------------------------------------------------------------------------
	void Matrix3::singularValueDecomposition (Matrix3& rkL, Matrix3& rkS,
		Matrix3& rkR) const
	{
		int iRow, iCol;

		Matrix3 kA = *this;
		Bidiagonalize(kA,rkL,rkR);
		rkS.makeZero();

		const int iMax = 32;
		const Real fEpsilon = (Real)1e-04;
		for (int i = 0; i < iMax; i++)
		{
			Real fTmp, fTmp0, fTmp1;
			Real fSin0, fCos0, fTan0;
			Real fSin1, fCos1, fTan1;

			bool bTest1 = (Math::Abs(kA[0][1]) <=
				fEpsilon*(Math::Abs(kA[0][0]) +
				Math::Abs(kA[1][1])));
			bool bTest2 = (Math::Abs(kA[1][2]) <=
				fEpsilon*(Math::Abs(kA[1][1]) +
				Math::Abs(kA[2][2])));
			if (bTest1)
			{
				if (bTest2)
				{
					rkS[0][0] = kA[0][0];
					rkS[1][1] = kA[1][1];
					rkS[2][2] = kA[2][2];
					break;
				}
				else
				{
					// 2x2 closed form factorization
					fTmp = (kA[1][1]*kA[1][1] - kA[2][2]*kA[2][2] +
						kA[1][2]*kA[1][2])/(kA[1][2]*kA[2][2]);
					fTan0 = ((Real)0.5)*(fTmp + Math::Sqrt(fTmp*fTmp +
						((Real)4.0)));
					fCos0 = Math::InvSqrt(((Real)1.0)+fTan0*fTan0);
					fSin0 = fTan0*fCos0;

					for (iCol = 0; iCol < 3; iCol++)
					{
						fTmp0 = rkL[iCol][1];
						fTmp1 = rkL[iCol][2];
						rkL[iCol][1] = fCos0*fTmp0-fSin0*fTmp1;
						rkL[iCol][2] = fSin0*fTmp0+fCos0*fTmp1;
					}

					fTan1 = (kA[1][2]-kA[2][2]*fTan0)/kA[1][1];
					fCos1 = Math::InvSqrt(((Real)1.0)+fTan1*fTan1);
					fSin1 = -fTan1*fCos1;

					for (iRow = 0; iRow < 3; iRow++)
					{
						fTmp0 = rkR[1][iRow];
						fTmp1 = rkR[2][iRow];
						rkR[1][iRow] = fCos1*fTmp0-fSin1*fTmp1;
						rkR[2][iRow] = fSin1*fTmp0+fCos1*fTmp1;
					}

					rkS[0][0] = kA[0][0];
					rkS[1][1] = fCos0*fCos1*kA[1][1] -
						fSin1*(fCos0*kA[1][2]-fSin0*kA[2][2]);
					rkS[2][2] = fSin0*fSin1*kA[1][1] +
						fCos1*(fSin0*kA[1][2]+fCos0*kA[2][2]);
					break;
				}
			}
			else 
			{
				if (bTest2)
				{
					// 2x2 closed form factorization 
					fTmp = (kA[0][0]*kA[0][0] + kA[1][1]*kA[1][1] -
						kA[0][1]*kA[0][1])/(kA[0][1]*kA[1][1]);
					fTan0 = ((Real)0.5)*(-fTmp + Math::Sqrt(fTmp*fTmp +
						((Real)4.0)));
					fCos0 = Math::InvSqrt(((Real)1.0)+fTan0*fTan0);
					fSin0 = fTan0*fCos0;

					for (iCol = 0; iCol < 3; iCol++)
					{
						fTmp0 = rkL[iCol][0];
						fTmp1 = rkL[iCol][1];
						rkL[iCol][0] = fCos0*fTmp0-fSin0*fTmp1;
						rkL[iCol][1] = fSin0*fTmp0+fCos0*fTmp1;
					}

					fTan1 = (kA[0][1]-kA[1][1]*fTan0)/kA[0][0];
					fCos1 = Math::InvSqrt(((Real)1.0)+fTan1*fTan1);
					fSin1 = -fTan1*fCos1;

					for (iRow = 0; iRow < 3; iRow++)
					{
						fTmp0 = rkR[0][iRow];
						fTmp1 = rkR[1][iRow];
						rkR[0][iRow] = fCos1*fTmp0-fSin1*fTmp1;
						rkR[1][iRow] = fSin1*fTmp0+fCos1*fTmp1;
					}

					rkS[0][0] = fCos0*fCos1*kA[0][0] -
						fSin1*(fCos0*kA[0][1]-fSin0*kA[1][1]);
					rkS[1][1] = fSin0*fSin1*kA[0][0] +
						fCos1*(fSin0*kA[0][1]+fCos0*kA[1][1]);
					rkS[2][2] = kA[2][2];
					break;
				}
				else
				{
					GolubKahanStep(kA,rkL,rkR);
				}
			}
		}

		// positize diagonal
		for (iRow = 0; iRow < 3; iRow++)
		{
			if (rkS[iRow][iRow] < (Real)0.0)
			{
				rkS[iRow][iRow] = -rkS[iRow][iRow];
				for (iCol = 0; iCol < 3; iCol++)
					rkR[iRow][iCol] = -rkR[iRow][iCol];
			}
		}
	}

}

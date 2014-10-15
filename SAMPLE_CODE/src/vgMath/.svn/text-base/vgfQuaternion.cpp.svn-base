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
#include <vgMath/vgfQuaternion.h>
#include <vgMath/vgfVector3.h>
#include <vgMath/vgfMatrix3.h>


#undef PI


namespace vgMath {
	

	const Quaternion Quaternion::ZERO(0.0,0.0,0.0,0.0);
	const Quaternion Quaternion::IDENTITY(1.0,0.0,0.0,0.0);

	//-----------------------------------------------------------------------
	void Quaternion::FromRotationMatrix (const Matrix3& kRot)
	{
		// Algorithm in Ken Shoemake's article in 1987 SIGGRAPH course notes
		// article "Quaternion Calculus and Fast Animation".

		Real fTrace = kRot[0][0]+kRot[1][1]+kRot[2][2];
		Real fRoot;

		if ( fTrace > 0.0 )
		{
			// |w| > 1/2, may as well choose w > 1/2
			fRoot = Math::Sqrt(fTrace + 1.0);  // 2w
			w = 0.5*fRoot;
			fRoot = 0.5/fRoot;  // 1/(4w)
			x = (kRot[2][1]-kRot[1][2])*fRoot;
			y = (kRot[0][2]-kRot[2][0])*fRoot;
			z = (kRot[1][0]-kRot[0][1])*fRoot;
		}
		else
		{
			// |w| <= 1/2
			static size_t s_iNext[3] = { 1, 2, 0 };
			size_t i = 0;
			if ( kRot[1][1] > kRot[0][0] )
				i = 1;
			if ( kRot[2][2] > kRot[i][i] )
				i = 2;
			size_t j = s_iNext[i];
			size_t k = s_iNext[j];

			fRoot = Math::Sqrt(kRot[i][i]-kRot[j][j]-kRot[k][k] + 1.0);
			Real* apkQuat[3] = { &x, &y, &z };
			*apkQuat[i] = 0.5*fRoot;
			fRoot = 0.5/fRoot;
			w = (kRot[k][j]-kRot[j][k])*fRoot;
			*apkQuat[j] = (kRot[j][i]+kRot[i][j])*fRoot;
			*apkQuat[k] = (kRot[k][i]+kRot[i][k])*fRoot;
		}
	}
	//-----------------------------------------------------------------------
	void Quaternion::ToRotationMatrix (Matrix3& kRot) const
	{
		Real fTx  = 2.0*x;
		Real fTy  = 2.0*y;
		Real fTz  = 2.0*z;
		Real fTwx = fTx*w;
		Real fTwy = fTy*w;
		Real fTwz = fTz*w;
		Real fTxx = fTx*x;
		Real fTxy = fTy*x;
		Real fTxz = fTz*x;
		Real fTyy = fTy*y;
		Real fTyz = fTz*y;
		Real fTzz = fTz*z;

		kRot[0][0] = 1.0-(fTyy+fTzz);
		kRot[0][1] = fTxy-fTwz;
		kRot[0][2] = fTxz+fTwy;
		kRot[1][0] = fTxy+fTwz;
		kRot[1][1] = 1.0-(fTxx+fTzz);
		kRot[1][2] = fTyz-fTwx;
		kRot[2][0] = fTxz-fTwy;
		kRot[2][1] = fTyz+fTwx;
		kRot[2][2] = 1.0-(fTxx+fTyy);
	}

	//-----------------------------------------------------------------------
	void Quaternion::ToAngleAxis (Radian& rfAngle, Vector3& rkAxis) const
	{
		// The quaternion representing the rotation is
		//   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

		Real fSqrLength = x*x+y*y+z*z;
		if ( fSqrLength > 0.0 )
		{
			rfAngle = 2.0*Math::ACos(w);
			Real fInvLength = Math::InvSqrt(fSqrLength);
			rkAxis.x = x*fInvLength;
			rkAxis.y = y*fInvLength;
			rkAxis.z = z*fInvLength;
		}
		else
		{
			// angle is 0 (mod 2*pi), so any axis will do
			rfAngle = Radian(0.0);
			rkAxis.x = 1.0;
			rkAxis.y = 0.0;
			rkAxis.z = 0.0;
		}
	}
	//-----------------------------------------------------------------------
	void Quaternion::FromAxes (const Vector3* akAxis)
	{
		Matrix3 kRot;

		for (size_t iCol = 0; iCol < 3; iCol++)
		{
			kRot[0][iCol] = akAxis[iCol].x;
			kRot[1][iCol] = akAxis[iCol].y;
			kRot[2][iCol] = akAxis[iCol].z;
		}

		FromRotationMatrix(kRot);
	}
	//-----------------------------------------------------------------------
	void Quaternion::FromAxes (const Vector3& xaxis, const Vector3& yaxis, const Vector3& zaxis)
	{
		Matrix3 kRot;

		kRot[0][0] = xaxis.x;
		kRot[1][0] = xaxis.y;
		kRot[2][0] = xaxis.z;

		kRot[0][1] = yaxis.x;
		kRot[1][1] = yaxis.y;
		kRot[2][1] = yaxis.z;

		kRot[0][2] = zaxis.x;
		kRot[1][2] = zaxis.y;
		kRot[2][2] = zaxis.z;

		FromRotationMatrix(kRot);

	}
	//-----------------------------------------------------------------------
	void Quaternion::ToAxes (Vector3* akAxis) const
	{
		Matrix3 kRot;

		ToRotationMatrix(kRot);

		for (size_t iCol = 0; iCol < 3; iCol++)
		{
			akAxis[iCol].x = kRot[0][iCol];
			akAxis[iCol].y = kRot[1][iCol];
			akAxis[iCol].z = kRot[2][iCol];
		}
	}
	//-----------------------------------------------------------------------
	Vector3 Quaternion::xAxis(void) const
	{
		//Real fTx  = 2.0*x;
		Real fTy  = 2.0*y;
		Real fTz  = 2.0*z;
		Real fTwy = fTy*w;
		Real fTwz = fTz*w;
		Real fTxy = fTy*x;
		Real fTxz = fTz*x;
		Real fTyy = fTy*y;
		Real fTzz = fTz*z;

		return Vector3(1.0-(fTyy+fTzz), fTxy+fTwz, fTxz-fTwy);
	}
	//-----------------------------------------------------------------------
	Vector3 Quaternion::yAxis(void) const
	{
		Real fTx  = 2.0*x;
		Real fTy  = 2.0*y;
		Real fTz  = 2.0*z;
		Real fTwx = fTx*w;
		Real fTwz = fTz*w;
		Real fTxx = fTx*x;
		Real fTxy = fTy*x;
		Real fTyz = fTz*y;
		Real fTzz = fTz*z;

		return Vector3(fTxy-fTwz, 1.0-(fTxx+fTzz), fTyz+fTwx);
	}
	//-----------------------------------------------------------------------
	Vector3 Quaternion::zAxis(void) const
	{
		Real fTx  = 2.0*x;
		Real fTy  = 2.0*y;
		Real fTz  = 2.0*z;
		Real fTwx = fTx*w;
		Real fTwy = fTy*w;
		Real fTxx = fTx*x;
		Real fTxz = fTz*x;
		Real fTyy = fTy*y;
		Real fTyz = fTz*y;

		return Vector3(fTxz+fTwy, fTyz-fTwx, 1.0-(fTxx+fTyy));
	}
	//-----------------------------------------------------------------------
	void Quaternion::ToAxes (Vector3& xaxis, Vector3& yaxis, Vector3& zaxis) const
	{
		Matrix3 kRot;

		ToRotationMatrix(kRot);

		xaxis.x = kRot[0][0];
		xaxis.y = kRot[1][0];
		xaxis.z = kRot[2][0];

		yaxis.x = kRot[0][1];
		yaxis.y = kRot[1][1];
		yaxis.z = kRot[2][1];

		zaxis.x = kRot[0][2];
		zaxis.y = kRot[1][2];
		zaxis.z = kRot[2][2];
	}


	//-----------------------------------------------------------------------
	Real Quaternion::dotProduct (const Quaternion& rkQ) const
	{
		return w*rkQ.w+x*rkQ.x+y*rkQ.y+z*rkQ.z;
	}
	//-----------------------------------------------------------------------
	//Real Quaternion::Norm () const
	//{
	//	return w*w+x*x+y*y+z*z;
	//}
	//-----------------------------------------------------------------------
	Quaternion Quaternion::Inverse () const
	{
		Real fNorm = w*w+x*x+y*y+z*z;
		if ( fNorm > 0.0 )
		{
			Real fInvNorm = 1.0/fNorm;
			return Quaternion(w*fInvNorm,-x*fInvNorm,-y*fInvNorm,-z*fInvNorm);
		}
		else
		{
			// return an invalid result to flag the error
			return ZERO;
		}
	}
	//-----------------------------------------------------------------------
	Quaternion Quaternion::UnitInverse () const
	{
		// assert:  'this' is unit length
		return Quaternion(w,-x,-y,-z);
	}
	//-----------------------------------------------------------------------
	Quaternion Quaternion::Exp () const
	{
		// If q = A*(x*i+y*j+z*k) where (x,y,z) is unit length, then
		// exp(q) = cos(A)+sin(A)*(x*i+y*j+z*k).  If sin(A) is near zero,
		// use exp(q) = cos(A)+A*(x*i+y*j+z*k) since A/sin(A) has limit 1.

		Quaternion kResult;

		Real fAngle = Math::Sqrt(v[1]*v[1] +
			v[2]*v[2] + v[3]*v[3]);

		Real fSin = Math::Sin(fAngle);
		kResult.v[0] = Math::Cos(fAngle);

		int i;

		if (Math::Abs(fSin) >= Math::ZERO_TOLERANCE)
		{
			Real fCoeff = fSin/fAngle;
			for (i = 1; i <= 3; i++)
			{
				kResult.v[i] = fCoeff*v[i];
			}
		}
		else
		{
			for (i = 1; i <= 3; i++)
			{
				kResult.v[i] = v[i];
			}
		}

		return kResult;
	}
	//-----------------------------------------------------------------------
	Quaternion Quaternion::Log () const
	{
		// If q = cos(A)+sin(A)*(x*i+y*j+z*k) where (x,y,z) is unit length, then
		// log(q) = A*(x*i+y*j+z*k).  If sin(A) is near zero, use log(q) =
		// sin(A)*(x*i+y*j+z*k) since sin(A)/A has limit 1.

		Quaternion kResult;
		kResult.v[0] = (Real)0.0;

		int i;

		if (Math::Abs(v[0]) < (Real)1.0)
		{
			Real fAngle = Math::ACos(v[0]).valueRadians();
			Real fSin = Math::Sin(fAngle);
			if (Math::Abs(fSin) >= Math::ZERO_TOLERANCE)
			{
				Real fCoeff = fAngle/fSin;
				for (i = 1; i <= 3; i++)
				{
					kResult.v[i] = fCoeff*v[i];
				}
				return kResult;
			}
		}

		for (i = 1; i <= 3; i++)
		{
			kResult.v[i] = v[i];
		}
		return kResult;
	}

	//-----------------------------------------------------------------------
	bool Quaternion::equals(const Quaternion& rhs, const Radian& tolerance) const
	{
		Real fCos = dotProduct(rhs);
		Radian angle = Math::ACos(fCos);

		return (Math::Abs(angle.valueRadians()) <= tolerance.valueRadians())
			|| Math::RealEqual(angle.valueRadians(), Math::PI, tolerance.valueRadians());


	}
	//-----------------------------------------------------------------------
	/**
	Quaternion Quaternion::Slerp (Real fT, const Quaternion& rkP,
		const Quaternion& rkQ, bool shortestPath)
	{
		Real fCos = rkP.dotProduct(rkQ);
		Quaternion rkT;

		// Do we need to invert rotation?
		if (fCos < 0.0f && shortestPath)
		{
			fCos = -fCos;
			rkT = -rkQ;
		}
		else
		{
			rkT = rkQ;
		}

		if (Math::Abs(fCos) >= Math::ZERO_TOLERANCE)
		{
			// Standard case (slerp)
			Real fSin = Math::Sqrt(1 - Math::Sqr(fCos));
			Radian fAngle = Math::ATan2(fSin, fCos);
			Real fInvSin = 1.0f / fSin;
			Real fCoeff0 = Math::Sin((1.0f - fT) * fAngle) * fInvSin;
			Real fCoeff1 = Math::Sin(fT * fAngle) * fInvSin;
			return fCoeff0 * rkP + fCoeff1 * rkT;
		}
		else
		{
			// There are two situations:
			// 1. "rkP" and "rkQ" are very close (fCos ~= +1), so we can do a linear
			//    interpolation safely.
			// 2. "rkP" and "rkQ" are almost inverse of each other (fCos ~= -1), there
			//    are an infinite number of possibilities interpolation. but we haven't
			//    have method to fix this case, so just use linear interpolation here.
			Quaternion t = (1.0f - fT) * rkP + fT * rkT;
			// taking the complement requires renormalisation
			t.normalise();
			return t;
		}
	}
	*/

	//----------------------------------------------------------------------------

	Quaternion& Quaternion::Slerp (Real fT, const Quaternion& rkP,
		const Quaternion& rkQ)
	{
		Real fCos = rkP.dotProduct(rkQ);
		Real fAngle = Math::ACos(fCos).valueRadians();

		if (Math::Abs(fAngle) >= Math::ZERO_TOLERANCE)
		{
			Real fSin = Math::Sin(fAngle);
			Real fInvSin = ((Real)1.0)/fSin;
			Real fCoeff0 = Math::Sin(((Real)1.0-fT)*fAngle)*fInvSin;
			Real fCoeff1 = Math::Sin(fT*fAngle)*fInvSin;
			*this = fCoeff0*rkP + fCoeff1*rkQ;
		}
		else
		{
			*this = rkP;
		}

		return *this;
	}
	//-----------------------------------------------------------------------
	Quaternion& Quaternion::SlerpExtraSpins (Real fT, const Quaternion& rkP,
		const Quaternion& rkQ, int iExtraSpins)
	{
		Real fCos = rkP.dotProduct(rkQ);
		Real fAngle = Math::ACos(fCos).valueRadians();

		if (Math::Abs(fAngle) >= Math::ZERO_TOLERANCE)
		{
			Real fSin = Math::Sin(fAngle);
			Real fPhase = Math::PI*iExtraSpins*fT;
			Real fInvSin = ((Real)1.0)/fSin;
			Real fCoeff0 = Math::Sin(((Real)1.0-fT)*fAngle-fPhase)*fInvSin;
			Real fCoeff1 = Math::Sin(fT*fAngle + fPhase)*fInvSin;
			*this = fCoeff0*rkP + fCoeff1*rkQ;
		}
		else
		{
			*this = rkP;
		}

		return *this;
	}
	//-----------------------------------------------------------------------
	void Quaternion::Intermediate (const Quaternion& rkQ0,
		const Quaternion& rkQ1, const Quaternion& rkQ2,
		Quaternion& rkA, Quaternion& rkB)
	{
		// assert:  q0, q1, q2 are unit quaternions

		Quaternion kQ0inv = rkQ0.UnitInverse();
		Quaternion kQ1inv = rkQ1.UnitInverse();
		Quaternion rkP0 = kQ0inv*rkQ1;
		Quaternion rkP1 = kQ1inv*rkQ2;
		Quaternion kArg = 0.25*(rkP0.Log()-rkP1.Log());
		Quaternion kMinusArg = -kArg;

		rkA = rkQ1*kArg.Exp();
		rkB = rkQ1*kMinusArg.Exp();
	}
	//-----------------------------------------------------------------------
	Quaternion& Quaternion::Squad (Real fT, const Quaternion& rkQ0,
		const Quaternion& rkA0, const Quaternion& rkA1, const Quaternion& rkQ1)
	{
		Real fSlerpT = ((Real)2.0)*fT*((Real)1.0-fT);
		Quaternion kSlerpP = Slerp(fT,rkQ0,rkQ1);
		Quaternion kSlerpQ = Slerp(fT,rkA0,rkA1);
		return Slerp(fSlerpT,kSlerpP,kSlerpQ);
	}
	//----------------------------------------------------------------------------
	Real Quaternion::normalise(void)
	{
		Real fLength = Length();

		if (fLength > Math::ZERO_TOLERANCE)
		{
			Real fInvLength = ((Real)1.0)/fLength;
			v[0] *= fInvLength;
			v[1] *= fInvLength;
			v[2] *= fInvLength;
			v[3] *= fInvLength;
		}
		else
		{
			fLength = (Real)0.0;
			v[0] = (Real)0.0;
			v[1] = (Real)0.0;
			v[2] = (Real)0.0;
			v[3] = (Real)0.0;
		}

		return fLength;
	}

	//-----------------------------------------------------------------------
	Quaternion Quaternion::nlerp(Real fT, const Quaternion& rkP,
		const Quaternion& rkQ, bool shortestPath)
	{
		Quaternion result;
		Real fCos = rkP.dotProduct(rkQ);
		if (fCos < 0.0f && shortestPath)
		{
			result = rkP + fT * ((-rkQ) - rkP);
		}
		else
		{
			result = rkP + fT * (rkQ - rkP);
		}
		result.normalise();
		return result;
	}

	
}

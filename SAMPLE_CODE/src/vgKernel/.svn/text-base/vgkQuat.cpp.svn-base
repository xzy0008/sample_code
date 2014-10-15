

#include <vgStableHeaders.h>

#include <vgKernel/vgkQuat.h>


#undef PI


namespace vgKernel {
	
	
	
	Quat operator* (float fScalar, const Quat& rkQ)
	{
		return Quat(fScalar*rkQ.x,fScalar*rkQ.y,fScalar*rkQ.z,
			fScalar*rkQ.w);
	}

	float Quat::getPitchDegrees( const bool& reprojectAxis/* = true*/ ) const
	{
		if (reprojectAxis)
		{
			// pitch = atan2(localy.z, localy.y)
			// pick parts of yAxis() implementation that we need
			float fTx  = 2.0*x;
			float fTy  = 2.0*y;
			float fTz  = 2.0*z;
			float fTwx = fTx*w;
			float fTxx = fTx*x;
			float fTyz = fTz*y;
			float fTzz = fTz*z;

			// Vector3(fTxy-fTwz, 1.0-(fTxx+fTzz), fTyz+fTwx);
			return 180.0f/ vgKernel::Math::PI*(atan2(fTyz+fTwx, 1.0f-(fTxx+fTzz)));
		}
		else
		{

			double ret = 180.0f/ vgKernel::Math::PI*(atan2(2*(y*z + w*x), w*w - x*x - y*y + z*z));

			if ( ret <= 0.0 )
			{
				ret += 180.0;
			}

			if ( ret > 180.0 )
			{
				ret -= 180.0;
			}


			// internal version
			return ret;
		}

		//return (180.0f/PI*atan2(2*(m_y*m_z + m_w*m_x), m_w*m_w - m_x*m_x - m_y*m_y + m_z*m_z));
	}
	//----------------------------------------------------------------
	Quat Quat::slerp ( float fT, const Quat& rkP, const Quat& rkQ)
	{

		bool shortestPath = true;

		float fCos = rkP.dot(rkQ);
		Quat rkT;

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

		if ( abs(fCos) < 1 - 1e-03)
		{
			// Standard case (slerp)
			float fSin = sqrt( 1 - (fCos * fCos) );
			float fAngle = atan2(fSin, fCos);
			float fInvSin = 1.0f / fSin;
			float fCoeff0 = sin((1.0f - fT) * fAngle) * fInvSin;
			float fCoeff1 = sin(fT * fAngle) * fInvSin;
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
			Quat t = (1.0f - fT) * rkP + fT * rkT;
			// taking the complement requires renormalisation
			t.normalize();
			return t;
		}

#if 0
		Quat ret;

		float fCos = rkP.dot(rkQ);
		float fAngle = acos(fCos);

		if (fabs( fAngle ) >= 0.0001f )
		{
			float fSin = sin(fAngle);
			float fInvSin = ((float)1.0)/fSin;
			float fTAngle = fT*fAngle;
			float fCoeff0 = sin(fAngle - fTAngle)*fInvSin;
			float fCoeff1 = sin(fTAngle)*fInvSin;

			// Profiling showed that the old line of code,
			//   *this = fCoeff0*rkP + fCoeff1*rkQ;
			// was using a large number of cycles, more so than the sin and cos
			// function calls.  The following inlined code is much faster.
			ret.m_fQuat[0] = fCoeff0*rkP.m_fQuat[0] + fCoeff1*rkQ.m_fQuat[0];
			ret.m_fQuat[1] = fCoeff0*rkP.m_fQuat[1] + fCoeff1*rkQ.m_fQuat[1];
			ret.m_fQuat[2] = fCoeff0*rkP.m_fQuat[2] + fCoeff1*rkQ.m_fQuat[2];
			ret.m_fQuat[3] = fCoeff0*rkP.m_fQuat[3] + fCoeff1*rkQ.m_fQuat[3];
		}
		else
		{
			// Based on the problem with the code in the previous block, inlining
			// the old code
			//   *this = rkP;
			ret.m_fQuat[0] = rkP.m_fQuat[0];
			ret.m_fQuat[1] = rkP.m_fQuat[1];
			ret.m_fQuat[2] = rkP.m_fQuat[2];
			ret.m_fQuat[3] = rkP.m_fQuat[3];
		}

		return ret;

#endif

#if 0
		//Calculate the dot product
		float fDot = 0;
		for (int j=0;j<4;j++)
		{
			fDot+=rkP.m_fQuat[j]*rkQ.m_fQuat[j];
		}
		//rkP.m_w*rkQ.m_w+rkP.m_x*rkQ.m_x+rkP.m_y*rkQ.m_y+rkP.m_z*rkQ.m_z;

		if(fDot < 0.0f)
		{
			rkP = -rkQ;

			fDot = -fDot;
		}


		if(fDot < 1.00001f && fDot > 0.99999f)
		{
			return LERP(rkP, rkQ, fT);
		}

		if(rkP.m_fQuat[1]*rkQ.m_fQuat[1]<0)// 修正插值的bug [11/20/2008 zhu]
		{
			rkQ=-rkQ;
		}

		//calculate the angle between the quaternions 
		float fTheta = acosf(fDot);

		return (rkP * sinf(fTheta * (1 - fT)) + rkQ * sinf(fTheta * fT))/sinf(fTheta);
#endif
	}
	//-----------------------------------------------------------------------
	float Quat::getHeadDegrees(void) const
	{
		bool reprojectAxis = true;
		if (reprojectAxis)
		{
			// yaw = atan2(localz.x, localz.z)
			// pick parts of zAxis() implementation that we need
			float fTx  = 2.0*x;
			float fTy  = 2.0*y;
			float fTz  = 2.0*z;
			float fTwy = fTy*w;
			float fTxx = fTx*x;
			float fTxz = fTz*x;
			float fTyy = fTy*y;

			// Vector3(fTxz+fTwy, fTyz-fTwx, 1.0-(fTxx+fTyy));

			float ret =
				180.0/ vgKernel::Math::PI * (atan2((double)fTxz+fTwy, 1.0-(fTxx+fTyy)));

			//if ( ret <= 0.0f )
			//{
			//	ret += 90.0f;
			//}

			return ret;


		}
		else
		{
			// internal version
			return 180.0f/vgKernel::Math::PI *(asin(-2*(x*z - w*y)));
		}

		//return 180.0f/PI*(asin(-2*(m_x*m_z - m_w*m_y)));
	}
	//----------------------------------------------------------------
	void Quat::fromEulerAnglesDegree( const float& pitch , const float& head , const float& roll )
	{


		Quat tmp1;
		Quat tmp2;


		tmp1.createFromAxisAngle(1.0f, 0.0f, 0.0f,  pitch );
		tmp2.createFromAxisAngle(0.0f, 1.0f, 0.0f,  head );
		*this = tmp1 * tmp2;




		////------------------------------------------
		//// 首先转换成弧度
		////------------------------------------------
		//const double PIOVER180 = PI / 180.0;


		//const double fltPitch2 = (pitch) * PIOVER180 * 0.5f;
		//const double fltYaw2   =  head*PIOVER180 *  0.5f;
		//const double fltRoll2  = roll * PIOVER180 *  0.5f;

		//const double cosY2 = cos( fltYaw2 );
		//const double sinY2 = sin( fltYaw2 );
		//const double cosP2 = cos( fltPitch2 );
		//const double sinP2 = sin( fltPitch2 );
		//const double cosR2 = cos( fltRoll2 );
		//const double sinR2 = sin( fltRoll2 );

		//this->z = sinR2 * cosP2 * cosY2 - cosR2 * sinP2 * sinY2;
		//this->x = cosR2 * sinP2 * cosY2 + sinR2 * cosP2 * sinY2;
		//this->y = cosR2 * cosP2 * sinY2 - sinR2 * sinP2 * cosY2;


		////x = cosR2 * sinP2 * cosY2 + sinR2 * cosP2 * sinY2;
		////y = cosR2 * cosP2 * sinY2 - sinR2 * sinP2 * cosY2;
		////z = sinR2 * cosP2 * cosY2 - cosR2 * sinP2 * sinY2;
		//w = cosR2 * cosP2 * cosY2 + sinR2 * sinP2 * sinY2;

		//------------------------------------------
		// 在这里进行补偿!!!
		//------------------------------------------

		//float bbb = getPitchDegrees( false);
		float ddd = getHeadDegrees();


		//tmp1.createFromAxisAngle(1.0f, 0.0f, 0.0f,  pitch - bbb );
		//*this = *this * tmp1;
		tmp1.createFromAxisAngle(0.0f, 1.0f, 0.0f,   head - ddd);
		*this = *this * tmp1;


		//float bbddd = getPitchDegrees();

		return;
	}
	//----------------------------------------------------------------



}// end of namespace vgKernel


#include "vgStableHeaders.h"
#include "vgMath/vgVec3.h"


namespace vgMath {

	//----------------------------------------------------------------------------
	void	CVector3::narrow( CVector3& pointRef )
	{
		if( x > pointRef.x )
		{
			x = pointRef.x;
		}
		if( y > pointRef.y )
		{
			y = pointRef.y;
		}
		if( z > pointRef.z )
		{
			z = pointRef.z;
		}
	}

	//----------------------------------------------------------------------------
	void	CVector3::enlarge( CVector3& pointRef )
	{
		if( x < pointRef.x )
		{
			x = pointRef.x;
		}
		if( y < pointRef.y )
		{
			y = pointRef.y;
		}
		if( z < pointRef.z )
		{
			z = pointRef.z;
		}
	}

	//----------------------------------------------------------------------------
	CVector3	operator + (CVector3& point1, CVector3& point2)
	{
		CVector3	sum(point1);
		sum.x += point2.x;
		sum.y += point2.y;
		sum.z += point2.z;

		return sum;
	}

	//----------------------------------------------------------------------------
	CVector3	operator * (CVector3& point1, float scaleRef)
	{
		CVector3	sum(point1);
		sum.x *= scaleRef;
		sum.y *= scaleRef;
		sum.z *= scaleRef;

		return sum;
	}

	//----------------------------------------------------------------------------
	float CVector3::length()
	{
		return sqrtf( x*x + y*y + z*z );
	}

	//----------------------------------------------------------------------------
	CVector3 CVector3::normalize()
	{
		double Magnitude;							
		CVector3	vNormal;
		Magnitude = length();//Mag(vNormal);

		vNormal.x =	x/ (float)Magnitude;				
		vNormal.y = y/ (float)Magnitude;				
		vNormal.z = z/ (float)Magnitude;				

		return vNormal;		
	}

	//----------------------------------------------------------------------------
	CVector3 CVector3::formatAsVG()
	{
		CVector3 tmpVect;
		tmpVect.x =  this->x;
		tmpVect.y =  this->z;
		tmpVect.z = -this->y;

		return tmpVect;
	}
	//----------------------------------------------------------------------------
	CVector3	subVector( CVector3 vPoint1, CVector3 vPoint2 )
	{
		CVector3 vVector;

		vVector.x = vPoint1.x - vPoint2.x;
		vVector.y = vPoint1.y - vPoint2.y;
		vVector.z = vPoint1.z - vPoint2.z;
		return vVector;
	}

	//----------------------------------------------------------------------------
	float	dotProduct( CVector3 vVector1, CVector3 vVector2 )
	{
		float resultDot = 0.0f;
		for(int index =0; index<3; index++)
			resultDot += vVector1.vert[index] * vVector2.vert[index]  ;
		return resultDot;
	}

	//----------------------------------------------------------------------------
	CVector3	crossProduct( CVector3 vVector1, CVector3 vVector2 )
	{
		CVector3 vCross;
		vCross.x = ((vVector1.y * vVector2.z) - (vVector1.z * vVector2.y));
		vCross.y = ((vVector1.z * vVector2.x) - (vVector1.x * vVector2.z));
		vCross.z = ((vVector1.x * vVector2.y) - (vVector1.y * vVector2.x));
		return vCross;
	}

}// namespace vgMath
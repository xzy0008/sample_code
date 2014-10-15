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
#include <vgMath/vgfVector4.h>


namespace vgMath {
	
	const Vector4 Vector4::ZERO( 0, 0, 0, 0 );
	const Vector4 Vector4::ONE(1.0f,1.0f,1.0f,1.0f);
	
	//----------------------------------------------------------------------------
	Real Vector4::normalize ()
	{
		Real fLength = length();

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
	//----------------------------------------------------------------
	//----------------------------------------------------------------------------

	Real Vector4::length () const
	{
		return Math::Sqrt(
			v[0]*v[0] +
			v[1]*v[1] +
			v[2]*v[2] +
			v[3]*v[3]);
	}
	//----------------------------------------------------------------------------
	Real Vector4::squaredLength () const
	{
		return
			v[0]*v[0] +
			v[1]*v[1] +
			v[2]*v[2] +
			v[3]*v[3];
	}
}

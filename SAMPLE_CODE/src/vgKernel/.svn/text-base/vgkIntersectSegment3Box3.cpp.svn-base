


#include <vgStableHeaders.h>
#include <vgKernel/vgkMath.h>
#include <vgKernel/vgkIntersectSegment3Box3.h>


namespace vgKernel {
	
	
	
	//----------------------------------------------------------------------------
	
	IntrSegment3Box3::IntrSegment3Box3 (const Segment3& rkSegment,
		const Box3& rkBox/*, bool bSolid*/)
		:
	m_pkSegment(&rkSegment),
		m_pkBox(&rkBox)
	{
		m_iQuantity = 0;
		//m_bSolid = bSolid;
	}
	//----------------------------------------------------------------------------
	
	const Segment3& IntrSegment3Box3::GetSegment () const
	{
		return *m_pkSegment;
	}
	//----------------------------------------------------------------------------
	
	const Box3& IntrSegment3Box3::GetBox () const
	{
		return *m_pkBox;
	}
	//----------------------------------------------------------------------------
	
	bool IntrSegment3Box3::Test ()
	{
		float afAWdU[3], afADdU[3], afAWxDdU[3], fRhs;

		Vec3 kDiff = m_pkSegment->Origin - m_pkBox->Center;

		afAWdU[0] = Math::Abs(m_pkSegment->Direction.dotProduct(m_pkBox->Axis[0]));
		afADdU[0] = Math::Abs(kDiff.dotProduct(m_pkBox->Axis[0]));
		fRhs = m_pkBox->Extent[0] + m_pkSegment->Extent*afAWdU[0];
		if (afADdU[0] > fRhs)
		{
			return false;
		}

		afAWdU[1] = Math::Abs(m_pkSegment->Direction.dotProduct(m_pkBox->Axis[1]));
		afADdU[1] = Math::Abs(kDiff.dotProduct(m_pkBox->Axis[1]));
		fRhs = m_pkBox->Extent[1] + m_pkSegment->Extent*afAWdU[1];
		if (afADdU[1] > fRhs)
		{
			return false;
		}

		afAWdU[2] = Math::Abs(m_pkSegment->Direction.dotProduct(m_pkBox->Axis[2]));
		afADdU[2] = Math::Abs(kDiff.dotProduct(m_pkBox->Axis[2]));
		fRhs = m_pkBox->Extent[2] + m_pkSegment->Extent*afAWdU[2];
		if (afADdU[2] > fRhs)
		{
			return false;
		}

		Vec3 kWxD = m_pkSegment->Direction.crossProduct(kDiff);

		afAWxDdU[0] = Math::Abs(kWxD.dotProduct(m_pkBox->Axis[0]));
		fRhs = m_pkBox->Extent[1]*afAWdU[2] + m_pkBox->Extent[2]*afAWdU[1];
		if (afAWxDdU[0] > fRhs)
		{
			return false;
		}

		afAWxDdU[1] = Math::Abs(kWxD.dotProduct(m_pkBox->Axis[1]));
		fRhs = m_pkBox->Extent[0]*afAWdU[2] + m_pkBox->Extent[2]*afAWdU[0];
		if (afAWxDdU[1] > fRhs)
		{
			return false;
		}

		afAWxDdU[2] = Math::Abs(kWxD.dotProduct(m_pkBox->Axis[2]));
		fRhs = m_pkBox->Extent[0]*afAWdU[1] + m_pkBox->Extent[1]*afAWdU[0];
		if (afAWxDdU[2] > fRhs)
		{
			return false;
		}

		return true;
	}
	//----------------------------------------------------------------------------
#if 0
	bool IntrSegment3Box3::Find ()
	{
		float fT0 = -m_pkSegment->Extent, fT1 = m_pkSegment->Extent;
		return IntrLine3Box3::DoClipping(fT0,fT1,m_pkSegment->Origin,
			m_pkSegment->Direction,*m_pkBox,m_bSolid,m_iQuantity,m_akPoint,
			m_iIntersectionType);
	}

	//----------------------------------------------------------------------------
	
	bool IntrSegment3Box3::Test (float fTMax,
		const Vec3& rkVelocity0, const Vec3& rkVelocity1)
	{
		m_iQuantity = 0;

		// Get the endpoints of the segment.
		Vec3 akSegment[2] =
		{
			m_pkSegment->GetNegEnd(),
			m_pkSegment->GetPosEnd()
		};

		// Get the box velocity relative to the segment.
		Vec3 kVelocity = rkVelocity1 - rkVelocity0;

		m_fContactTime = (float)0;
		float fTLast = Math::MAX_REAL;

		int i;
		Vec3 kAxis;

		// test box normals
		for (i = 0; i < 3; i++)
		{
			kAxis = m_pkBox->Axis[i];
			if (!IntrAxis::Test(kAxis,akSegment,*m_pkBox,kVelocity,fTMax,
				m_fContactTime,fTLast))
			{
				return false;
			}
		}

		// test seg-direction cross box-edges
		for (i = 0; i < 3; i++)
		{
			kAxis = m_pkBox->Axis[i].Cross(m_pkSegment->Direction);
			if (!IntrAxis::Test(kAxis,akSegment,*m_pkBox,kVelocity,fTMax,
				m_fContactTime,fTLast))
			{
				return false;
			}
		}

		// test velocity cross box-faces
		for (i = 0; i < 3; i++)
		{
			kAxis = kVelocity.Cross(m_pkBox->Axis[i]);
			if (!IntrAxis::Test(kAxis,akSegment,*m_pkBox,kVelocity,fTMax,
				m_fContactTime,fTLast))
			{
				return false;
			}
		}

		return true;
	}
	//----------------------------------------------------------------------------
	
	bool IntrSegment3Box3::Find (float fTMax,
		const Vec3& rkVelocity0, const Vec3& rkVelocity1)
	{
		m_iQuantity = 0;
		m_iIntersectionType = IT_EMPTY;

		// Get the endpoints of the segment.
		Vec3 akSegment[2] =
		{
			m_pkSegment->GetNegEnd(),
			m_pkSegment->GetPosEnd()
		};

		// Get the box velocity relative to the segment.
		Vec3 kVelocity = rkVelocity1 - rkVelocity0;

		m_fContactTime = (float)0;
		float fTLast = Math::MAX_REAL;

		int i;
		Vec3 kAxis;
		int eSide = IntrConfiguration::NONE;
		IntrConfiguration kSegContact, kBoxContact;

		// test box normals
		for (i = 0; i < 3; i++)
		{
			kAxis = m_pkBox->Axis[i];
			if (!IntrAxis::Find(kAxis,akSegment,*m_pkBox,kVelocity,fTMax,
				m_fContactTime,fTLast,eSide,kSegContact,kBoxContact))
			{
				return false;
			}
		}

		// test seg-direction cross box-edges
		for (i = 0; i < 3; i++)
		{
			kAxis = m_pkBox->Axis[i].Cross(m_pkSegment->Direction);
			if (!IntrAxis::Find(kAxis,akSegment,*m_pkBox,kVelocity,fTMax,
				m_fContactTime,fTLast,eSide,kSegContact,kBoxContact))
			{
				return false;
			}
		}

		// test velocity cross box-faces
		for (i = 0; i < 3; i++)
		{
			kAxis = kVelocity.Cross(m_pkBox->Axis[i]);
			if (!IntrAxis::Find(kAxis,akSegment,*m_pkBox,kVelocity,fTMax,
				m_fContactTime,fTLast,eSide,kSegContact,kBoxContact))
			{
				return false;
			}
		}

		if (m_fContactTime < (float)0 || eSide == IntrConfiguration::NONE)
		{
			// intersecting now
			return false;
		}

		FindContactSet(akSegment,*m_pkBox,eSide,kSegContact,kBoxContact,
			rkVelocity0,rkVelocity1,m_fContactTime,m_iQuantity,m_akPoint);

		if (m_iQuantity == 1)
		{
			m_iIntersectionType = IT_POINT;
		}
		else
		{
			m_iIntersectionType = IT_SEGMENT;
		}

		return true;
	}
#endif
	//----------------------------------------------------------------------------
	
	int IntrSegment3Box3::GetQuantity () const
	{
		return m_iQuantity;
	}
	//----------------------------------------------------------------------------
	
	const Vec3& IntrSegment3Box3::GetPoint (int i) const
	{
		assert(0 <= i && i < m_iQuantity);
		return m_akPoint[i];
	}
	//----------------------------------------------------------------------------

}// end of namespace vgKernel




#include <vgStableHeaders.h>
#include <vgKernel/vgkIntersectSegment3Triangle3.h>


namespace vgKernel {
	
	
	
	//----------------------------------------------------------------------------
	
	IntrSegment3Triangle3::IntrSegment3Triangle3 (
		const Segment3& rkSegment, const Triangle3& rkTriangle)
		:
	m_pkSegment(&rkSegment),
		m_pkTriangle(&rkTriangle)
	{
		m_iQuantity = 0;
	}
	//----------------------------------------------------------------------------
	
	const Segment3& IntrSegment3Triangle3::GetSegment () const
	{
		return *m_pkSegment;
	}
	//----------------------------------------------------------------------------
	
	const Triangle3& IntrSegment3Triangle3::GetTriangle () const
	{
		return *m_pkTriangle;
	}
	//----------------------------------------------------------------------------
	
	bool IntrSegment3Triangle3::Test ()
	{
		// compute the offset origin, edges, and normal
		Vec3 kDiff = m_pkSegment->Origin - m_pkTriangle->V[0];
		Vec3 kEdge1 = m_pkTriangle->V[1] - m_pkTriangle->V[0];
		Vec3 kEdge2 = m_pkTriangle->V[2] - m_pkTriangle->V[0];
		Vec3 kNormal = kEdge1.crossProduct(kEdge2);

		// Solve Q + t*D = b1*E1 + b2*E2 (Q = kDiff, D = segment direction,
		// E1 = kEdge1, E2 = kEdge2, N = Cross(E1,E2)) by
		//   |Dot(D,N)|*b1 = sign(Dot(D,N))*Dot(D,Cross(Q,E2))
		//   |Dot(D,N)|*b2 = sign(Dot(D,N))*Dot(D,Cross(E1,Q))
		//   |Dot(D,N)|*t = -sign(Dot(D,N))*Dot(Q,N)
		float fDdN = m_pkSegment->Direction.dotProduct(kNormal);
		float fSign;
		if (fDdN > Math::ZERO_TOLERANCE)
		{
			fSign = (float)1.0;
		}
		else if (fDdN < -Math::ZERO_TOLERANCE)
		{
			fSign = (float)-1.0;
			fDdN = -fDdN;
		}
		else
		{
			// Segment and triangle are parallel, call it a "no intersection"
			// even if the segment does intersect.
			return false;
		}

		float fDdQxE2 = fSign*m_pkSegment->Direction.dotProduct(kDiff.crossProduct(kEdge2));
		if (fDdQxE2 >= (float)0.0)
		{
			float fDdE1xQ = fSign*m_pkSegment->Direction.dotProduct(kEdge1.crossProduct(kDiff));
			if (fDdE1xQ >= (float)0.0)
			{
				if (fDdQxE2 + fDdE1xQ <= fDdN)
				{
					// line intersects triangle, check if segment does
					float fQdN = -fSign*kDiff.dotProduct(kNormal);
					float fExtDdN = m_pkSegment->Extent*fDdN;
					if (-fExtDdN <= fQdN && fQdN <= fExtDdN)
					{
						// segment intersects triangle
						return true;
					}
					// else: |t| > extent, no intersection
				}
				// else: b1+b2 > 1, no intersection
			}
			// else: b2 < 0, no intersection
		}
		// else: b1 < 0, no intersection

		return false;
	}
	//----------------------------------------------------------------------------
	
	bool IntrSegment3Triangle3::Find ()
	{
		// compute the offset origin, edges, and normal
		Vec3 kDiff = m_pkSegment->Origin - m_pkTriangle->V[0];
		Vec3 kEdge1 = m_pkTriangle->V[1] - m_pkTriangle->V[0];
		Vec3 kEdge2 = m_pkTriangle->V[2] - m_pkTriangle->V[0];
		Vec3 kNormal = kEdge1.crossProduct(kEdge2);

		// Solve Q + t*D = b1*E1 + b2*E2 (Q = kDiff, D = segment direction,
		// E1 = kEdge1, E2 = kEdge2, N = Cross(E1,E2)) by
		//   |Dot(D,N)|*b1 = sign(Dot(D,N))*Dot(D,Cross(Q,E2))
		//   |Dot(D,N)|*b2 = sign(Dot(D,N))*Dot(D,Cross(E1,Q))
		//   |Dot(D,N)|*t = -sign(Dot(D,N))*Dot(Q,N)
		float fDdN = m_pkSegment->Direction.dotProduct(kNormal);
		float fSign;
		if (fDdN > Math::ZERO_TOLERANCE)
		{
			fSign = (float)1.0;
		}
		else if (fDdN < -Math::ZERO_TOLERANCE)
		{
			fSign = (float)-1.0;
			fDdN = -fDdN;
		}
		else
		{
			// Segment and triangle are parallel, call it a "no intersection"
			// even if the segment does intersect.
			return false;
		}

		float fDdQxE2 = fSign*m_pkSegment->Direction.dotProduct(kDiff.crossProduct(kEdge2));
		if (fDdQxE2 >= (float)0.0)
		{
			float fDdE1xQ = fSign*m_pkSegment->Direction.dotProduct(kEdge1.crossProduct(kDiff));
			if (fDdE1xQ >= (float)0.0)
			{
				if (fDdQxE2 + fDdE1xQ <= fDdN)
				{
					// line intersects triangle, check if segment does
					float fQdN = -fSign*kDiff.dotProduct(kNormal);
					float fExtDdN = m_pkSegment->Extent*fDdN;
					if (-fExtDdN <= fQdN && fQdN <= fExtDdN)
					{
						// segment intersects triangle
						float fInv = ((float)1.0)/fDdN;
						m_fSegmentT = fQdN*fInv;
						m_fTriB1 = fDdQxE2*fInv;
						m_fTriB2 = fDdE1xQ*fInv;
						m_fTriB0 = (float)1.0 - m_fTriB1 - m_fTriB2;
						return true;
					}
					// else: |t| > extent, no intersection
				}
				// else: b1+b2 > 1, no intersection
			}
			// else: b2 < 0, no intersection
		}
		// else: b1 < 0, no intersection

		return false;
	}
	//----------------------------------------------------------------------------
	
	float IntrSegment3Triangle3::GetSegmentT () const
	{
		return m_fSegmentT;
	}
	//----------------------------------------------------------------------------
	
	float IntrSegment3Triangle3::GetTriB0 () const
	{
		return m_fTriB0;
	}
	//----------------------------------------------------------------------------
	
	float IntrSegment3Triangle3::GetTriB1 () const
	{
		return m_fTriB1;
	}
	//----------------------------------------------------------------------------
	
	float IntrSegment3Triangle3::GetTriB2 () const
	{
		return m_fTriB2;
	}
	//----------------------------------------------------------------------------
#if 0
	bool IntrSegment3Triangle3::Test (float fTMax,
		const Vec3& rkVelocity0, const Vec3& rkVelocity1)
	{
		m_iQuantity = 0;

		// Get the endpoints of the segment.
		Vec3 akSegment[2] =
		{
			m_pkSegment->GetNegEnd(),
			m_pkSegment->GetPosEnd()
		};

		// Get the triangle edges.
		Vec3 kEdge0 = m_pkTriangle->V[1] - m_pkTriangle->V[0];
		Vec3 kEdge1 = m_pkTriangle->V[2] - m_pkTriangle->V[0];

		// Get the triangle velocity relative to the segment.
		Vec3 kVelocity = rkVelocity1 - rkVelocity0;

		m_fContactTime = (float)0;
		float fTLast = Math::MAX_REAL;

		// Test tri-normal.
		Vec3 kNormV = kEdge0.crossProduct(kEdge1);
		if (!IntrAxis::Test(kNormV,akSegment,*m_pkTriangle,kVelocity,
			fTMax,m_fContactTime,fTLast))
		{
			return false;
		}

		// Test whether the segment is parallel to the triangle, effectively the
		// test:  sin(Angle(NormV,DirU)) > 1-epsilon
		Vec3 kDirU = akSegment[1] - akSegment[0];
		Vec3 kNormU = kNormV.crossProduct(kDirU);
		float fDirUSqrLen = kDirU.squaredLength();
		float fNorUSqrLen = kNormU.squaredLength();
		float fNorVSqrLen = kNormV.squaredLength();
		float fOmEpsilon = (float)1 - Math::ZERO_TOLERANCE;

		int i0, i1;
		Vec3 kAxis;

		if (fNorUSqrLen > fOmEpsilon*fNorVSqrLen*fDirUSqrLen)  // parallel
		{
			// Test tri-normal cross seg-direction.
			if (!IntrAxis::Test(kNormU,akSegment,*m_pkTriangle,kVelocity,
				fTMax,m_fContactTime,fTLast))
			{
				return false;
			}

			// Test tri-normal cross tri-edges.
			for (i0 = 2, i1 = 0; i1 < 3; i0 = i1++)
			{
				kAxis = kNormV.Cross(m_pkTriangle->V[i1] - m_pkTriangle->V[i0]);
				if (!IntrAxis::Test(kAxis,akSegment,*m_pkTriangle,
					kVelocity,fTMax,m_fContactTime,fTLast))
				{
					return false;
				}
			}
		}
		else  // not parallel
		{
			// Test seg-direction cross tri-edges.
			for (i0 = 2, i1 = 0; i1 < 3; i0 = i1++)
			{
				kAxis = kDirU.Cross(m_pkTriangle->V[i1] - m_pkTriangle->V[i0]);
				if (!IntrAxis::Test(kAxis,akSegment,*m_pkTriangle,
					kVelocity,fTMax,m_fContactTime,fTLast))
				{
					return false;
				}
			}
		}

		return true;
	}

	//----------------------------------------------------------------------------
	
	bool IntrSegment3Triangle3::Find (float fTMax,
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

		// Get the triangle edges.
		Vec3 kEdge0 = m_pkTriangle->V[1] - m_pkTriangle->V[0];
		Vec3 kEdge1 = m_pkTriangle->V[2] - m_pkTriangle->V[0];

		// Get the triangle velocity relative to the segment.
		Vec3 kVelocity = rkVelocity1 - rkVelocity0;

		m_fContactTime = (float)0;
		float fTLast = Math::MAX_REAL;

		// Test tri-normal.
		Vec3 kNormV = kEdge0.Cross(kEdge1);
		IntrConfiguration kSegContact, kTriContact;
		int eSide;
		if (!IntrAxis::Find(kNormV,akSegment,*m_pkTriangle,kVelocity,
			fTMax,m_fContactTime,fTLast,eSide,kSegContact,kTriContact))
		{
			return false;
		}

		// Test whether the segment is parallel to the triangle, effectively the
		// test:  sin(Angle(NormV,DirU)) > 1-epsilon
		Vec3 kDirU = akSegment[1] - akSegment[0];
		Vec3 kNormU = kNormV.Cross(kDirU);
		float fDirUSqrLen = kDirU.SquaredLength();
		float fNorUSqrLen = kNormU.SquaredLength();
		float fNorVSqrLen = kNormV.SquaredLength();
		float fOmEpsilon = (float)1 - Math::ZERO_TOLERANCE;

		int i0, i1;
		Vec3 kAxis;

		if (fNorUSqrLen > fOmEpsilon*fNorVSqrLen*fDirUSqrLen)  // parallel
		{
			// Find tri-normal cross seg-direction.
			if (!IntrAxis::Find(kNormU,akSegment,*m_pkTriangle,kVelocity,
				fTMax,m_fContactTime,fTLast,eSide,kSegContact,kTriContact))
			{
				return false;
			}

			// Find tri-normal cross tri-edges.
			for (i0 = 2, i1 = 0; i1 < 3; i0 = i1++)
			{
				kAxis = kNormV.Cross(m_pkTriangle->V[i1] - m_pkTriangle->V[i0]);
				if (!IntrAxis::Find(kAxis,akSegment,*m_pkTriangle,
					kVelocity,fTMax,m_fContactTime,fTLast,eSide,kSegContact,
					kTriContact))
				{
					return false;
				}
			}
		} 
		else 
		{
			// test seg-direction cross tri-edges
			for (i0 = 2, i1 = 0; i1 < 3; i0 = i1++)
			{
				kDirU.Cross(m_pkTriangle->V[i1] - m_pkTriangle->V[i0]);
				if (!IntrAxis::Find(kAxis,akSegment,*m_pkTriangle,
					kVelocity,fTMax,m_fContactTime,fTLast,eSide,kSegContact,
					kTriContact))
				{
					return false;
				}
			}
		}

		if (m_fContactTime < (float)0)
		{
			return false;
		}

		FindContactSet(akSegment,*m_pkTriangle,eSide,kSegContact,
			kTriContact,rkVelocity0,rkVelocity1,m_fContactTime,m_iQuantity,
			m_akPoint);

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
	
	int IntrSegment3Triangle3::GetQuantity () const
	{
		return m_iQuantity;
	}
	//----------------------------------------------------------------------------
	
	const Vec3& IntrSegment3Triangle3::GetPoint (int i) const
	{
		assert(0 <= i && i < m_iQuantity);
		return m_akPoint[i];
	}
	//----------------------------------------------------------------------------

}// end of namespace vgKernel

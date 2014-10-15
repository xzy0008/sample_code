


#include <vgStableHeaders.h>
#include <vgKernel/vgkPointInPolygon.h>


namespace vgKernel {
	


	//----------------------------------------------------------------
	PointInPolygon::PointInPolygon( int iQuantity, const Vec2* akVertex )
	{
		m_iQuantity = iQuantity;
		m_akVertex = akVertex;
	}
	//----------------------------------------------------------------
	bool PointInPolygon::contains (const Vec2& rkP) const
	{
		bool bInside = false;
		for (int i = 0, j = m_iQuantity-1; i < m_iQuantity; j = i++)
		{
			const Vec2& rkU0 = m_akVertex[i];
			const Vec2& rkU1 = m_akVertex[j];
			float fRHS, fLHS;

			if (rkP[1] < rkU1[1])  // U1 above ray
			{
				if (rkU0[1] <= rkP[1])  // U0 on or below ray
				{
					fLHS = (rkP[1]-rkU0[1])*(rkU1[0]-rkU0[0]);
					fRHS = (rkP[0]-rkU0[0])*(rkU1[1]-rkU0[1]);
					if (fLHS > fRHS)
					{
						bInside = !bInside;
					}
				}
			}
			else if (rkP[1] < rkU0[1])  // U1 on or below ray, U0 above ray
			{
				fLHS = (rkP[1]-rkU0[1])*(rkU1[0]-rkU0[0]);
				fRHS = (rkP[0]-rkU0[0])*(rkU1[1]-rkU0[1]);
				if (fLHS < fRHS)
				{
					bInside = !bInside;
				}
			}
		}
		return bInside;
	}

	//----------------------------------------------------------------
	
	
}// end of namespace vgKernel

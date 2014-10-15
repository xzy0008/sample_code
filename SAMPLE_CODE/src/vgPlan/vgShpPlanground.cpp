#include <vgStableHeaders.h>
#include <vgPlan/vgShpPlanground.h>

namespace vgPlan
{
	bool vgShpPlanground::diffGemotry(OGRGeometry *pGemo)
	{
		OGRGeometry* pNewGemotry = this->m_pGeometry->Difference(pGemo);
	
		if (pNewGemotry != NULL)
		{
			delete m_pGeometry;
			m_pGeometry = pNewGemotry;
			assert (m_pGeometry->getGeometryType() == wkbPolygon25D ||
				    m_pGeometry->getGeometryType() == wkbPolygon ||
					m_pGeometry->getGeometryType() == wkbMultiPolygon ||
					m_pGeometry->getGeometryType() == wkbMultiPolygon25D);	
		}
		else
		{
			return false;
		}
		
		return true;
	}
// 
// 	bool vgShpPlanground::setGeometry(OGRGeometry *pGemo, const vgKernel::Mat4& mat)
// 	{
// 		if (m_pGeometry != NULL)
// 		{
// 			delete m_pGeometry;
// 			m_pGeometry = NULL;
// 		}
// 
// 		m_pGeometry = pGemo;
// 	
// 		int dimension = m_pGeometry->getDimension();
// 		if ( dimension != 3 )
// 		{
// 			m_pGeometry->setCoordinateDimension( 3 );
// 		}
// 
// 		int bufferSize = m_pGeometry->WkbSize();
// 		unsigned char *wkbBuffer = new unsigned char[bufferSize];
// 
// 		OGRErr err = m_pGeometry->exportToWkb(wkbNDR, wkbBuffer);
// 
// 		if (err != OGRERR_NONE)
// 		{
// 			delete [] wkbBuffer;
// 			return false;
// 		}
// 
// 		unsigned char *bufferStart = wkbBuffer;
// 
// 		byte byteorder = *wkbBuffer;
// 		assert( byteorder == wkbNDR );
// 		wkbBuffer += sizeof( byte );
// 
// 		// ¼ì²étype
// 		int geotype = *(int*)wkbBuffer;
// 		assert( geotype == wkbPolygon25D );
// 		wkbBuffer += sizeof( int );
// 
// 		// numRings
// 		int numRings = *(int*)wkbBuffer;
// 		wkbBuffer += sizeof( int );
// 
// 
// 		assert( numRings >= 0);
// 		if ( numRings <= 0 )
// 		{
// 			return false;
// 		}
// 
// 		for ( int i = 0 ; i < numRings ; ++ i )
// 		{
// 			int numPoints = *(int*)wkbBuffer;
// 			assert( numPoints >= 0 );
// 			wkbBuffer += sizeof( int );
// 
// 			for (int j=0; j<numPoints; j++)
// 			{
// 				double *px = (double*)(wkbBuffer);
// 				double *py = (double*)(wkbBuffer + sizeof(double));
// 				double *pz = (double*)(wkbBuffer + sizeof(double)*2);
// 
// 				vgKernel::Vec3 point(*px, (*pz), -(*py));
// 
// 				vgKernel::Vec3 newPoint = vgKernel::Math::translateVec3(mat, point);
// 
// // 				double *pCoord = (double*)wkbBuffer;
// // 				*pCoord = newPoint.x;
// // 				pCoord = (double*)(wkbBuffer+sizeof(double));
// // 				*pCoord = newPoint.z;
// // 				pCoord = (double*)(wkbBuffer+sizeof(double)*2);
// // 				*pCoord = -newPoint.y;
// 				*px = newPoint.x;
// 				*py = -newPoint.z;
// 				*pz = newPoint.y;
// 
// 				wkbBuffer += sizeof( double ) * 3;
// 			}
// 		}
// 
// 		assert( (wkbBuffer - bufferStart) == bufferSize );
// 
// 
// 		m_pGeometry->importFromWkb(bufferStart);
// 
// 		delete []bufferStart;
// 
// 		return true;
// 	}


}
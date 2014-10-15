#include <vgStableHeaders.h>
#include <vgPlan/vgpExcludeArea.h>

namespace vgPlan
{
	vgExcludeArea::vgExcludeArea() // : m_pGeometry(NULL)
	{
		// __super::setGeometry()
	}

	vgExcludeArea::~vgExcludeArea()
	{
// 		if (m_pGeometry != NULL)
// 		{
// 			delete m_pGeometry;
// 		}
	}
// 
// 	bool vgExcludeArea::setGeometry(OGRGeometry *pGeom, const vgKernel::Mat4& mat)
// 	{
// 		OGRGeometry* geometryPtr = pGeom->clone();
// 
// 		int dimension = geometryPtr->getDimension();
// 		if ( dimension != 3 )
// 		{
// 			geometryPtr->setCoordinateDimension( 3 );
// 		}
// 
// 		int bufferSize = geometryPtr->WkbSize();
// 		unsigned char *wkbBuffer = new unsigned char[bufferSize];
// 
// 		OGRErr err = geometryPtr->exportToWkb(wkbNDR, wkbBuffer);
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
// // 				double *px = (double*)(wkbBuffer);
// // 				double *py = (double*)(wkbBuffer + sizeof(double)*2);
// // 				double *pz = (double*)(wkbBuffer + sizeof(double));
// // 
// // 				vgKernel::Vec3 point(*px, - (*py), *pz);
// // 		
// // 				vgKernel::Vec3 newPoint = vgKernel::Math::translateVec3(mat, point);
// // 	
// // 				double *pCoord = (double*)wkbBuffer;
// // 				*pCoord = newPoint.x;
// // 				pCoord = (double*)(wkbBuffer+sizeof(double));
// // 				*pCoord = newPoint.z;
// // 				pCoord = (double*)(wkbBuffer+sizeof(double)*2);
// // 				*pCoord = -newPoint.y;
// 
// 				double *px = (double*)(wkbBuffer);
// 				double *py = (double*)(wkbBuffer + sizeof(double));
// 				double *pz = (double*)(wkbBuffer + sizeof(double)*2);
// 
// 				vgKernel::Vec3 point(*px, (*pz), -(*py));
// 
// 				vgKernel::Vec3 newPoint = vgKernel::Math::translateVec3(mat, point);
// 
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
// 		geometryPtr->importFromWkb(bufferStart);
// 		m_pGeometry = geometryPtr;
// 
// 		delete bufferStart;
// 
// 		return true;
// 	}
}
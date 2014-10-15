#include "vgStableHeaders.h"
#include <vgPlan/vgpShpArea.h>
 
 namespace vgPlan
 {
  	vgShpArea::vgShpArea()
  	{
  		m_pGeometry = NULL;

		m_renderFlag = false;
  	}
 
 	vgShpArea::~vgShpArea()
 	{
 		if (m_pGeometry != NULL)
 		{
 			delete m_pGeometry;
 		}
 	}
 
 	bool vgShpArea::setGeometry(OGRGeometry *pGeom, const vgKernel::Mat4 &mat)
 	{
 		OGRGeometry* geometryPtr = pGeom->clone();
 
 		int dimension = geometryPtr->getDimension();
 		if ( dimension != 3 )
 		{
 			geometryPtr->setCoordinateDimension( 3 );
 		}
 
 		int bufferSize = geometryPtr->WkbSize();
 		unsigned char *wkbBuffer = new unsigned char[bufferSize];
 
 		OGRErr err = geometryPtr->exportToWkb(wkbNDR, wkbBuffer);
 
 		if (err != OGRERR_NONE)
 		{
 			delete [] wkbBuffer;
 			return false;
 		}
 
 		unsigned char *bufferStart = wkbBuffer;
 
 		byte byteorder = *wkbBuffer;
 		assert( byteorder == wkbNDR );
 		wkbBuffer += sizeof( byte );
 
 		// ¼ì²étype
 		int geotype = *(int*)wkbBuffer;
 		assert( geotype == wkbPolygon25D );
 		wkbBuffer += sizeof( int );
 
 		// numRings
 		int numRings = *(int*)wkbBuffer;
 		wkbBuffer += sizeof( int );
 
 
 		assert( numRings >= 0);
 		if ( numRings <= 0 )
 		{
 			return false;
 		}
 
 		for ( int i = 0 ; i < numRings ; ++ i )
 		{
 			int numPoints = *(int*)wkbBuffer;
 			assert( numPoints >= 0 );
 			wkbBuffer += sizeof( int );
 
 			for (int j=0; j<numPoints; j++)
 			{
 				double *px = (double*)(wkbBuffer);
 				double *py = (double*)(wkbBuffer + sizeof(double));
 				double *pz = (double*)(wkbBuffer + sizeof(double)*2);
 
 				vgKernel::Vec3 point(*px, (*pz), -(*py));
 
 				vgKernel::Vec3 newPoint = vgKernel::Math::translateVec3(mat, point);
 
 				*px = newPoint.x;
 				*py = -newPoint.z;
 				*pz = newPoint.y;
				
				m_pointVec.push_back(newPoint);

 				wkbBuffer += sizeof( double ) * 3;
 			}
 		}
 
 		assert( (wkbBuffer - bufferStart) == bufferSize );
 
 
 		geometryPtr->importFromWkb(bufferStart);
 		
 		if (m_pGeometry != NULL)
 		{
 			delete m_pGeometry;
 			m_pGeometry = NULL;
 		}
 
 		// m_pGeometry = geometryPtr;
 
		if (m_pGeometry != NULL)
		{
			delete m_pGeometry;
		}

		m_pGeometry = geometryPtr;

 		delete bufferStart;
 
 		return true;
 	}

	void vgShpArea::render()
	{
		if (! m_renderFlag)
		{
			return ;
		}


		glDisable(GL_DEPTH_TEST);
		glDisable( GL_TEXTURE_2D );
		glLineWidth(2.0f);
		glColor3f( 0.f, 0.f , 1.f );

		glBegin(GL_LINE_LOOP);

		for ( int i = 0 ; i < m_pointVec.size() ; ++ i )
		{
			glVertex3d(m_pointVec[i].x, m_pointVec[i].y, m_pointVec[i].z);
		}

		glEnd();
		glEnable(GL_DEPTH_TEST);

	}
 }
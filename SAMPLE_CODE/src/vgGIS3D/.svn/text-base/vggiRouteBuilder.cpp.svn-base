#include <vgStableheaders.h>

#include <vgGIS3D/vggiRouteBuilder.h>
#include <gdal/ogr_api.h>
#include <gdal/ogr_feature.h>
#include <gdal/ogrsf_frmts.h>

namespace vgGIS3D
{

	void RouteBuilder::render()
	{
		glPushAttrib(GL_CURRENT_BIT);
		glDisable(GL_TEXTURE_2D);
		glColor3f(0.f, 1.f, 1.f);
 
		for (int i=0; i<m_rings.size(); i++)
		{
			glBegin(GL_LINE_STRIP);
			RingStruct &ring = m_rings.at(i);

			for (int j=0; j<ring._numPoints; j++)
			{
				glVertex3dv(ring._pointsBeginAddr + j*3);
			}
			glEnd();	
		}
		glPopAttrib();
	}

	void RouteBuilder::reset()
	{
		for (int i=0; i<m_rings.size(); i++)
		{
			delete [](m_rings[i]._pointsBeginAddr);
		}

		m_rings.clear();
	}

	bool RouteBuilder::addRoute(const vector<vgKernel::Vec3>& pointVec)
	{
		RingStruct ring;

		ring._numPoints = pointVec.size();

		ring._pointsBeginAddr = new double[3*ring._numPoints];

		for (int i=0; i<pointVec.size(); i++)
		{
			ring._pointsBeginAddr[i*3] = pointVec[i].x;
			ring._pointsBeginAddr[i*3 + 1] = pointVec[i].y+1;
			ring._pointsBeginAddr[i*3 + 2] = pointVec[i].z;
		}
		
		m_rings.push_back(ring);

		return true;
	}

	bool RouteBuilder::saveToFile(string path, string layername)
	{
		const char *pszDriverName = "AutoCAD DXF";
		OGRSFDriver *poDriver;
		OGRRegisterAll();

		poDriver = OGRSFDriverRegistrar::GetRegistrar()->GetDriverByName(
			pszDriverName );

		if( poDriver == NULL )
		{
			AfxMessageBox("driver not available.");
			return false;
		}

		OGRDataSource *poDS;
		poDS = poDriver->CreateDataSource( path.c_str(), NULL );
		if ( poDS == NULL )
		{
			// poDS = poDriver->CreateDataSource( "f:\\point_out.shp", NULL );

			AfxMessageBox( "Creation of output file failed.");
			return false;
		}

		OGRLayer *poLayer;

		poLayer = poDS->CreateLayer(layername.c_str(), NULL, wkbLineString25D, NULL );
		if( poLayer == NULL )
		{
			AfxMessageBox( "Layer creation failed." );
			return false;
		}
		
		OGRFeatureDefn* def = poLayer->GetLayerDefn();

		for (int i=0; i<m_rings.size(); i++)
		{
			OGRLineString *pGeometry = new OGRLineString;
			pGeometry->setCoordinateDimension(3);

			RingStruct &ring = m_rings[i];

			for (int j=0; j<ring._numPoints; j++)
			{
				pGeometry->addPoint(ring._pointsBeginAddr[j*3], 
					-ring._pointsBeginAddr[j*3 + 2],
					ring._pointsBeginAddr[j*3 + 1]
					);
			}
			//  = pVec->at(j)->getboxgeo();

			if (pGeometry == NULL)
			{
				continue;
			}

			OGRFeature *poFeature;
			poFeature = new OGRFeature( poLayer->GetLayerDefn() );

			if (poFeature->SetGeometry( pGeometry) != OGRERR_NONE)
			{
				AfxMessageBox( "Failed to set feature in shapefile.\n" );
			}

			int returnValue = poLayer->CreateFeature( poFeature );

			if( returnValue != OGRERR_NONE )
			{
				OGRwkbGeometryType gtype = pGeometry->getGeometryType();
				AfxMessageBox( "Failed to create feature in shapefile.\n" );
				return false;
			}

			// OGRFeature::DestroyFeature(pFeature);
			OGRFeature::DestroyFeature(poFeature);
		}

		OGRDataSource::DestroyDataSource( poDS );

		reset();

		::MessageBox(NULL, "导出路网文件成功." ,"提示", MB_OK);

		return true;
	}
}
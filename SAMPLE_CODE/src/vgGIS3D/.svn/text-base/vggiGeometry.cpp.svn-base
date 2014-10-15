



#include <vgStableHeaders.h>
#include <vgGis3D/vggiGeometry.h>
#include <vgGis3D/vggiLayer.h>
#include <gdal/ogrsf_frmts.h>
#include <gdal/ogr_api.h>




namespace vgGIS3D {
	
 

	//----------------------------------------------------------------
	Geometry::Geometry( OGRFeature* feature, Layer* father_layer )
		: _drawing( this )
	{
		assert( feature != NULL );
		_ogrFeatureFID = feature->GetFID();
		_fatherLayer = father_layer;

		m_pFeature = feature;

		assert( _fatherLayer != NULL );
	}
	//----------------------------------------------------------------
	OGRFeature* Geometry::getOGRFeature()
	{
		//return m_pFeature;
		return _fatherLayer->getOGRFeatureByFID( _ogrFeatureFID );
	}
	//----------------------------------------------------------------
	void Geometry::setFeature( OGRFeature* feature )
	{
		m_pFeature = feature;

		return _fatherLayer->setOGRFeature( feature );
	}
	//----------------------------------------------------------------
	OGRFeaturePtr Geometry::getOGRFeaturePtr()
	{
		OGRFeature* ret = getOGRFeature();
		
		if ( ret != NULL )
		{
			return OGRFeaturePtr( ret );
		}

		return OGRFeaturePtr();
	}

	//----------------------------------------------------------------


	// ÍØÆË¹ØÏµ¼ÆËã 
	 OGRBoolean Geometry::Intersects (Geometry *geom)
	{
		OGRFeaturePtr orgPtr1 = getOGRFeaturePtr();
		OGRFeaturePtr ogrPtr2 = geom->getOGRFeaturePtr();

		OGRGeometry *pGeom = orgPtr1->GetGeometryRef();
		OGRGeometry *pGeom2 = ogrPtr2->GetGeometryRef();

		OGRBoolean re = pGeom->Intersects(pGeom2);

		return re;
	}

	OGRBoolean Geometry::Equals (Geometry *geom)
	{
		OGRFeaturePtr orgPtr1 = getOGRFeaturePtr();
		OGRFeaturePtr ogrPtr2 = geom->getOGRFeaturePtr();

		OGRGeometry *pGeom = orgPtr1->GetGeometryRef();
		OGRGeometry *pGeom2 = ogrPtr2->GetGeometryRef();

		OGRBoolean re = pGeom->Equals(pGeom2);

		return re;
	}

	OGRBoolean Geometry::Disjoint (Geometry *geom)
	{
		OGRFeaturePtr orgPtr1 = getOGRFeaturePtr();
		OGRFeaturePtr ogrPtr2 = geom->getOGRFeaturePtr();

		OGRGeometry *pGeom = orgPtr1->GetGeometryRef();
		OGRGeometry *pGeom2 = ogrPtr2->GetGeometryRef();

		OGRBoolean re = pGeom->Disjoint(pGeom2);

		return re;
	}

	OGRBoolean Geometry::Touches (Geometry *geom)
	{		
		OGRFeaturePtr orgPtr1 = getOGRFeaturePtr();
		OGRFeaturePtr ogrPtr2 = geom->getOGRFeaturePtr();

		OGRGeometry *pGeom = orgPtr1->GetGeometryRef();
		OGRGeometry *pGeom2 = ogrPtr2->GetGeometryRef();

		OGRBoolean re = pGeom->Crosses(pGeom2);

		return re;
	}

	OGRBoolean Geometry::Crosses (Geometry *geom)
	{
		OGRFeaturePtr orgPtr1 = getOGRFeaturePtr();
		OGRFeaturePtr ogrPtr2 = geom->getOGRFeaturePtr();

		OGRGeometry *pGeom = orgPtr1->GetGeometryRef();
		OGRGeometry *pGeom2 = ogrPtr2->GetGeometryRef();

		OGRBoolean re = pGeom->Crosses(pGeom2);

		return re;
	}

	OGRBoolean Geometry::Within (Geometry *geom)
	{
		OGRFeaturePtr orgPtr1 = getOGRFeaturePtr();
		OGRFeaturePtr ogrPtr2 = geom->getOGRFeaturePtr();

		OGRGeometry *pGeom = orgPtr1->GetGeometryRef();
		OGRGeometry *pGeom2 = ogrPtr2->GetGeometryRef();

		OGRBoolean re = pGeom->Within(pGeom2);

		return re;
	}

	OGRBoolean Geometry::Contains (Geometry *geom)
	{
		OGRFeaturePtr orgPtr1 = getOGRFeaturePtr();
		OGRFeaturePtr ogrPtr2 = geom->getOGRFeaturePtr();

		OGRGeometry *pGeom = orgPtr1->GetGeometryRef();
		OGRGeometry *pGeom2 = ogrPtr2->GetGeometryRef();

		OGRBoolean re = pGeom->Contains(pGeom2);

		return re;
	}

	OGRBoolean Geometry::Overlaps (Geometry *geom)
	{
		OGRFeaturePtr orgPtr1 = getOGRFeaturePtr();
		OGRFeaturePtr ogrPtr2 = geom->getOGRFeaturePtr();

		OGRGeometry *pGeom = orgPtr1->GetGeometryRef();
		OGRGeometry *pGeom2 = ogrPtr2->GetGeometryRef();

		OGRBoolean re = pGeom->Overlaps(pGeom2);

		return re;
	}

	OGRGeometry* Geometry::getBoundary ()
	{
		OGRFeaturePtr orgPtr = getOGRFeaturePtr();

		OGRGeometry *pGeom = orgPtr->GetGeometryRef();

		OGRGeometry *re = pGeom->ConvexHull();

		return re;
	}

	double Geometry::Distance (Geometry *geom)
	{
		OGRFeaturePtr orgPtr1 = getOGRFeaturePtr();
		OGRFeaturePtr ogrPtr2 = geom->getOGRFeaturePtr();

		OGRGeometry *pGeom = orgPtr1->GetGeometryRef();
		OGRGeometry *pGeom2 = ogrPtr2->GetGeometryRef();

		double re = pGeom->Distance(pGeom2);

		return re;
	}

	OGRGeometry * Geometry::ConvexHull () 
	{
		OGRFeaturePtr orgPtr = getOGRFeaturePtr();

		OGRGeometry *pGeom = orgPtr->GetGeometryRef();

		OGRGeometry *re = pGeom->ConvexHull();

		return re;
	}

	OGRGeometry * Geometry::Buffer (double dfDist, int nQuadSegs) 
	{
		OGRFeaturePtr orgPtr = getOGRFeaturePtr();

		OGRGeometry *pGeom = orgPtr->GetGeometryRef();

		OGRGeometry *re = pGeom->Buffer(dfDist, nQuadSegs);

		return re;
	}

	OGRGeometry * Geometry::Intersection ( Geometry *geom) 
	{
		OGRFeaturePtr orgPtr1 = getOGRFeaturePtr();
		OGRFeaturePtr ogrPtr2 = geom->getOGRFeaturePtr();

		OGRGeometry *pGeom = orgPtr1->GetGeometryRef();
		OGRGeometry *pGeom2 = ogrPtr2->GetGeometryRef();

		OGRGeometry *re = pGeom->Intersection(pGeom2);

		return re;
	}

	OGRGeometry * Geometry::Union (Geometry *geom) 
	{
		OGRFeaturePtr orgPtr1 = getOGRFeaturePtr();
		OGRFeaturePtr ogrPtr2 = geom->getOGRFeaturePtr();

		OGRGeometry *pGeom = orgPtr1->GetGeometryRef();
		OGRGeometry *pGeom2 = ogrPtr2->GetGeometryRef();

		OGRGeometry *re = pGeom->Union(pGeom2);

		return re;
	}

	OGRGeometry * Geometry::Difference (Geometry *geom) 
	{
		OGRFeaturePtr orgPtr1 = getOGRFeaturePtr();
		OGRFeaturePtr ogrPtr2 = geom->getOGRFeaturePtr();

		OGRGeometry *pGeom = orgPtr1->GetGeometryRef();
		OGRGeometry *pGeom2 = ogrPtr2->GetGeometryRef();

		OGRGeometry *re = pGeom->Difference(pGeom2);

		return re;
	}

	OGRGeometry * Geometry::SymmetricDifference (Geometry *geom) 
	{
		OGRFeaturePtr orgPtr1 = getOGRFeaturePtr();
		OGRFeaturePtr ogrPtr2 = geom->getOGRFeaturePtr();

		OGRGeometry *pGeom = orgPtr1->GetGeometryRef();
		OGRGeometry *pGeom2 = ogrPtr2->GetGeometryRef();

		OGRGeometry *re = pGeom->SymmetricDifference(pGeom2);

		return re;
	}

}// end of namespace vgShape

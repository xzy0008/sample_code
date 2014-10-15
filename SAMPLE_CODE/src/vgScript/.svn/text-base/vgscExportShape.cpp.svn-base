



#include <vgStableHeaders.h>
#ifdef	SCRIPT_VGSH

#include <vgScript/vgscExportShape.h>
#include <vgShape/vgshShapeManager.h>
#include <vgScript/vgscSharePtrWrapper.h>
#include <vgScript/vgscBoostPythonInclude.h>




namespace vgScript {
	
	

	//----------------------------------------------------------------
	void exportShape()
	{
		using namespace boost::python;
		using namespace vgShape;



		class_<Geometry, boost::noncopyable >("Geometry", no_init )
			.def("renderUsingDisplayList", pure_virtual(&Geometry::renderUsingDisplayList) )
			.def("getNumOfPoints", pure_virtual(&Geometry::getNumOfPoints) )
			.def("getEnvelope3f", pure_virtual(&Geometry::getEnvelope3f) )
			.def("renderOnceForDisplayList", pure_virtual(&Geometry::renderOnceForDisplayList) )
			.def("getPointAttri", pure_virtual(&Geometry::getPointAttri) )
			.def("readDataFromOGRFeature", pure_virtual(&Geometry::readDataFromOGRFeature) )
			.def("clearRecoverableData", pure_virtual(&Geometry::clearRecoverableData) )
			.def("renderInSelectedMode", pure_virtual(&Geometry::renderInSelectedMode) )
			.def("attachToTerrain", pure_virtual(&Geometry::attachToTerrain) )
			.def("invalidateRendering", pure_virtual(&Geometry::invalidateRendering) )
			.def("getFatherLayer", pure_virtual(&Geometry::getFatherLayer) ,
			return_value_policy<reference_existing_object>() )

			;


		class_< GeometryPointerVec > ("GeometryPointerVec")
			.def (indexing::container_suite< GeometryPointerVec >
			::with_policies (return_value_policy<reference_existing_object>()) )
			;

		class_<Layer, vgKernel::SharePtr<Layer>, 
			bases<vgKernel::Renderer> >("Layer", no_init )
			.def( "getMatrix" , &Layer::getMatrix )
			.def( "setSelectedGeometry" , &Layer::setSelectedGeometry )
			.def( "addSelectedGeometry" , &Layer::addSelectedGeometry )
			.def( "delSelectedGeometry" , &Layer::delSelectedGeometry )
			.def( "clearSelectedGeometry" , &Layer::clearSelectedGeometry )

			.def( "getSelectedGeometry" , &Layer::getSelectedGeometry,
			return_value_policy<reference_existing_object>() )
			.def( "getGeometries" , &Layer::getGeometries ,
			return_value_policy<reference_existing_object>())

			.def( "transStaticCoordToOpenGLCoord" , &Layer::transStaticCoordToOpenGLCoord )
			.def( "getHeightInOpenGL" , &Layer::getHeightInOpenGL )
			.def( "invalidateRendering" , &Layer::invalidateRendering )
			.def( "attachGeometriesToTerrain" , &Layer::attachGeometriesToTerrain )
			.def( "setEditMode" , &Layer::setEditMode )
			.def( "isInEditMode" , &Layer::isInEditMode )

			.def( "selectByFieldString" , &Layer::selectByFieldString )

			
			;


		class_< LayerPtrVector > ("LayerPtrVector")
			.def (indexing::container_suite< LayerPtrVector , true> ())
			;

		class_<DataSource, 
			vgKernel::SharePtr<DataSource> , 
			boost::noncopyable >("DataSource" , no_init )

			.def( "getFilePath", &DataSource::getFilePath )
			.def( "isValid", &DataSource::isValid )
			.def( "deleteLayer", &DataSource::deleteLayer )
			.def( "deleteAllLayers", &DataSource::deleteAllLayers )
			.def( "renderLayers", &DataSource::renderLayers )

			.def( "getLayerPtrVector", &DataSource::getLayerPtrVector ,
			return_value_policy<reference_existing_object>() )

			.def( "renderLayers", &DataSource::renderLayers )
			.def( "saveToFilePath", &DataSource::saveToFilePath )
			.def( "setLayersRenderingPriority", &DataSource::setLayersRenderingPriority )

			;

		class_<ShapeManager ,bases<vgKernel::RendererHolder> ,
		boost::noncopyable >( "ShapeManager" , no_init )
			.def( "openShapeFile", &ShapeManager::openShapeFile )
			.def( "openShapeFileSpecially", &ShapeManager::openShapeFileSpecially )
			.def( "checkOpened", &ShapeManager::checkOpened )

			.def( "renderShapes", &ShapeManager::renderShapes )
			.def( "clearAllDataSources", &ShapeManager::clearAllDataSources )
			.def( "clearDataSource", &ShapeManager::clearDataSource )
			.def( "clearDataSourcePtr", &ShapeManager::clearDataSourcePtr )

			.def( "getLayerByShortName", &ShapeManager::getLayerByShortName ,
			return_value_policy<reference_existing_object>() )

			.def( "setSelectMode", &ShapeManager::setSelectMode )
			.def( "getSelectFlag", &ShapeManager::getSelectFlag )
			.def( "setShpLoadingFilter", &ShapeManager::setShpLoadingFilter )
			.def( "getDataSourceByPathName", &ShapeManager::getDataSourceByPathName )
			.def( "getDataSourceByShortName", &ShapeManager::getDataSourceByShortName )

			.def( "getSingleton", &ShapeManager::getSingleton ,
			return_value_policy<reference_existing_object>() )
			.staticmethod( "getSingleton" )
			;



	}
	//----------------------------------------------------------------



}// end of namespace vgScript

#endif



#include <vgStableHeaders.h>
#include <vgScript/vgscExportCam.h>
#include <vgCam/vgcaCamFacade.h>
#include <vgCam/vgcaCamManager.h>
#include <vgScript/vgscDefinition.h>
#include <vgScript/vgscBoostPythonInclude.h>

#include <vgScript/vgscSharePtrWrapper.h>


namespace vgScript {
	
	using namespace vgKernel;
	using namespace vgCam;


	bool (ViewFrustum::*testBoxInFrustum1)(const Box& ) = 
		&ViewFrustum::testBoxInFrustum;

	bool (ViewFrustum::*testBoxInFrustum2)(const float& , const float& , const float& , const  float& ) = 
		&ViewFrustum::testBoxInFrustum;

	void (CameraRecord::*switchCamera1)(ViewCam *, ViewCam *) = 
		&CameraRecord::switchCamera;
	
	void (CameraRecord::*switchCamera2)(ViewCam *, ViewCam *, float , int ) = 
		&CameraRecord::switchCamera;

	//----------------------------------------------------------------
	void exportCam()
	{
		using namespace boost::python;
		using namespace vgCam;

		class_<ViewFrustum>("ViewFrustum")
			.def( "calculateInEveryFrame" , &ViewFrustum::calculateInEveryFrame )
			.def( "validateUpdate" , &ViewFrustum::validateUpdate )

			.def( "testBoxInFrustum" , testBoxInFrustum1 )
			.def( "testBoxInFrustum" , testBoxInFrustum2 )

			.def( "testBoxIncludedInFrustum" , &ViewFrustum::testBoxIncludedInFrustum )

			.def( "getCameraBox" , &ViewFrustum::getCameraBox )
			.def( "updateCameraBox" , &ViewFrustum::updateCameraBox )
			;

		class_<ViewCam, vgKernel::SharePtr<ViewCam>,
			bases<vgKernel::Renderer> >("ViewCam")
			.def( "getPosition" , &ViewCam::getPosition )
			.def( "setPosition" , &ViewCam::setPosition )
			.def( "setCamData" , &ViewCam::setCamData )

			.def( "getPitchDegrees" , &ViewCam::getPitchDegrees )
			.def( "getHeadingDegrees" , &ViewCam::getHeadingDegrees )
			.def( "setPitchDegrees" , &ViewCam::setPitchDegrees )
			.def( "setHeadingDegrees" , &ViewCam::setHeadingDegrees )
			.def( "getForwardVelocity" , &ViewCam::getForwardVelocity )
			.def( "setForwardVelocity" , &ViewCam::setForwardVelocity )


			.def( "setFov" , &ViewCam::setFov )
			.def( "setAspectRatio" , &ViewCam::setAspectRatio )
			.def( "setNear" , &ViewCam::setNear )
			.def( "setFar" , &ViewCam::setFar )
			.def( "setViewport" , &ViewCam::setViewport )
			.def( "setToVisible" , &ViewCam::setToVisible )
			.def( "setToUnvisible" , &ViewCam::setToUnvisible )
			.def( "flushData" , &ViewCam::flushData )
			.def( "renderViewCamEntity" , &ViewCam::renderViewCamEntity )
			.def( "cloneCurrentCameraView" , &ViewCam::cloneCurrentCameraView )
			;

		class_<CameraRecord, vgKernel::SharePtr<CameraRecord>, 
			bases<vgKernel::Renderer> >("CameraRecord")
			.def( "init" , &CameraRecord::init )
			.def( "loadVCR" , &CameraRecord::loadVCR )
			.def( "saveVCR" , &CameraRecord::saveVCR )

			.def( "startPlaying" , &CameraRecord::startPlaying )
			.def( "stopPlaying" , &CameraRecord::stopPlaying )
			.def( "continuePlaying" , &CameraRecord::continuePlaying )

			.def( "switchVisible" , &CameraRecord::switchVisible )
			.def( "beginRecording" , &CameraRecord::beginRecording )
			.def( "pauseRecording" , &CameraRecord::pauseRecording )
			.def( "finishRecording" , &CameraRecord::finishRecording )

			.def( "switchCamera" , switchCamera1 )
			.def( "switchCamera" , switchCamera2 )

			.def( "getPlayingFlag" , &CameraRecord::getPlayingFlag )

			.def( "getVcrFileName" , &CameraRecord::getVcrFileName )
			.def( "getVcrFilePath" , &CameraRecord::getVcrFilePath )
			.def( "setVcrFilePath" , &CameraRecord::setVcrFilePath )

			.def( "reset" , &CameraRecord::reset )

			.def( "startPlayingByTime" , &CameraRecord::startPlayingByTime )
			.def( "startPlayingByFrame" , &CameraRecord::startPlayingByFrame )
			;

		//------------------------------------------
		// 注意,static成员不能封装成class类.
		//------------------------------------------
		def( "gotoCameraByName", &CamFacade::gotoCameraByName ,
			( VGARG("cam_name") ) );
		def( "gotoObject", &CamFacade::gotoObject ,
			( VGARG("obj_name") ));
		def( "gotoCamera", &CamFacade::gotoCamera );
		def( "gotoSelectedObject", &CamFacade::gotoSelectedObject );
		def( "gotoSelectedCamera", &CamFacade::gotoSelectedCamera );

		def( "playVCR", &CamFacade::playVCR ,
			( VGARG("vcrname") ));

		def( "stopVCR", &CamFacade::stopVCR ,
			( VGARG("vcrname") ));

		def( "continueVCR", &CamFacade::continueVCR ,
			( VGARG("vcrname") ));

		def( "stopVCRSeries", &CamFacade::stopVCRSeries );

		def( "continueVCRSeries", &CamFacade::continueVCRSeries );

		class_<CamManager,bases<vgKernel::RendererHolder>, 
			boost::noncopyable>("CamManager" , no_init )
			.def("setMovingEnable", &CamManager::setMovingEnable )
			.def("getMovingEnable", &CamManager::getMovingEnable )

			.def("setDefaultParameters", &CamManager::setDefaultParameters )
			.def("changeVelocity", &CamManager::changeVelocity )
			.def("getForwardVelocity", &CamManager::getForwardVelocity )

			.def("getCurrentPosition", &CamManager::getCurrentPosition )
			.def("getCurrentPositionPtr", &CamManager::getCurrentPositionPtr ,
				return_value_policy<reference_existing_object>() )
			.def("setCurrentPosition", &CamManager::setCurrentPosition )

			.def("getPitchDegrees", &CamManager::getPitchDegrees )
			.def("getHeadingDegrees", &CamManager::getHeadingDegrees )
			.def("setPitchDegrees", &CamManager::setPitchDegrees )
			.def("setHeadingDegrees", &CamManager::setHeadingDegrees )
			.def("getForwardVelocity", &CamManager::getForwardVelocity )
			.def("setForwardVelocity", &CamManager::setForwardVelocity )
			.def("getTurningVelocity", &CamManager::getTurningVelocity )
			.def("setTurningVelocity", &CamManager::setTurningVelocity )
			.def("getPitchDegrees", &CamManager::getPitchDegrees )
			.def("getPitchVelocity", &CamManager::getPitchVelocity )
			.def("setPitchVelocity", &CamManager::setPitchVelocity )
			.def("getUpAndDownMultiply", &CamManager::getUpAndDownMultiply )
			.def("setUpAndDownMultiply", &CamManager::setUpAndDownMultiply )

			.def("renderVcr", &CamManager::renderVcr )
			.def("renderViewCams", &CamManager::renderViewCams )
			.def("getCurrentCameraRecord", &CamManager::getCurrentCameraRecord ,
			return_value_policy<reference_existing_object>() )
			.def("setCurrentCameraRecord", &CamManager::setCurrentCameraRecord )
			.def("setDefaultCamRecordPtr", &CamManager::setDefaultCamRecordPtr )
			.def("getCameraRecordNum", &CamManager::getCameraRecordNum )


			.def("addCameraRecord", &CamManager::addCameraRecord )


			.def("getCameraRecordByName", &CamManager::getCameraRecordByName,
			return_value_policy<reference_existing_object>() )

			.def("getViewCamByName", &CamManager::getViewCamByName,
			return_value_policy<reference_existing_object>() )


			.def("setFov", &CamManager::setFov )
			.def("getFov", &CamManager::getFov )
			.def("setNear", &CamManager::setNear )
			.def("getNear", &CamManager::getNear )
			.def("setFar", &CamManager::setFar )
			.def("getFar", &CamManager::getFar )


			.def("setViewport", &CamManager::setViewport )
			.def("setupViewFrustum", &CamManager::setupViewFrustum )
			.def("getAspectRatio", &CamManager::getAspectRatio )
			.def("setChannelNum", &CamManager::setChannelNum )
			.def("setViewFrustumParam", &CamManager::setViewFrustumParam)	//@FengYK 2009/10/28	20:22

			.def("getCurrentFrustum", &CamManager::getCurrentFrustum ,
			return_value_policy<reference_existing_object>() )
			.def("updateCurrentFrustum", &CamManager::updateCurrentFrustum )

			.def("saveCurrentCameraView", &CamManager::saveCurrentCameraView ,
			return_value_policy<manage_new_object>() )
			.def("immediateToViewCam", &CamManager::immediateToViewCam )

			.def("copyRecordfile", &CamManager::copyRecordfile )
			.def("setPosByCurVcrSpecificFrame", &CamManager::setPosByCurVcrSpecificFrame )

			.def("setCollisionOnOff", &CamManager::setCollisionOnOff )
			.def("getCollisionOnOff", &CamManager::getCollisionOnOff )
			.def("setEillipseVec", &CamManager::setEillipseVec )
			.def("getEillipseVec", &CamManager::getEillipseVec )



			.def("playContinuousRecords", &CamManager::playContinuousRecords )
.def("playContinuousRecords2", &CamManager::playContinuousRecords2 )
			.def( "getSingleton", &CamManager::getSingleton ,
			return_value_policy<reference_existing_object>() )
			.staticmethod( "getSingleton" )
			;

	}
	//----------------------------------------------------------------



}// end of namespace vgScript





#include <vgStableHeaders.h>
#include "vgUserScriptOtherModules.h"

#include <vgScript/vgscDefinition.h>
#include <vgScript/vgscBoostPythonInclude.h>
#include <vgSprite/vgspAnimatedObjectManager.h>

#include <vgScript/vgscExportKernel.h>
#include <vgScript/vgscExportKernelObjects.h>
#include <vgSound/vgSoundManager.h>
namespace vgUser {
	
	

	//void FFF()
	//{
	//	assert(0);
	//}

#if 1
	//----------------------------------------------------------------
 	void exportMusic()
 	{
 		using namespace boost::python;
 		// using namespace vgMusic;

		using namespace vgSound;
 

		//def( "FFF" , &FFF );

 
 		class_<SoundBackground/*, bases<vgKernel::Renderer>*/ >("SoundBackground")
 			.def( "getFilePath" , &SoundBackground::getFilePath )
 			.def( "reset" , &SoundBackground::reset )
 			.def( "startPlaying" , &SoundBackground::startPlaying )
 			.def( "stopPlaying" , &SoundBackground::stopPlaying )
 			.def( "getPlayFlag" , &SoundBackground::getPlayFlag )
 			.def( "setPlayFlag" , &SoundBackground::setPlayFlag )
 			.def( "getSoundName" , &SoundBackground::getSoundName )
 			;
 
 		class_<Sound3D/*, bases<vgKernel::Renderer>*/ >("Sound3D")
 			.def( "loadWaveFile" , &Sound3D::loadWaveFile )
 			.def( "startPlaying" , &Sound3D::startPlaying , VGARG("loop") )
 			.def( "setVolume" , &Sound3D::setVolume )
 			.def( "setSoundPos" , &Sound3D::setSoundPos )
 			.def( "setSoundPram" , &Sound3D::setSoundPram , 
 			VGARG("fMinDistance"), VGARG("fMaxDistance") )
 
 			.def( "stopPlaying" , &Sound3D::stopPlaying )
 			.def( "setAbsolutePos" , &Sound3D::setAbsolutePos )
 			.def( "setPlayFlag" , &Sound3D::setPlayFlag )
 			.def( "getPlayFlag" , &Sound3D::getPlayFlag )
 
 			.def( "getSoundPos" , &Sound3D::getSoundPos )
 			.def( "getAttenuation" , &Sound3D::getAttenuation )
 			.def( "setAttenuation" , &Sound3D::setAttenuation )
 			.def( "getWavePath" , &Sound3D::getWavePath )
 			;
 
 
 		class_<SoundManager , 
 			/*bases<vgKernel::RendererHolder>,*/
 			boost::noncopyable>( "SoundManager" , no_init )
 			.def("createDlgToSetBackgroundMusic", &SoundManager::createDlgToSetBackgroundMusic )
 			.def("create3DSoundFromCurrentPos", &SoundManager::create3DSoundFromCurrentPos ,
			return_value_policy<reference_existing_object>() )

 			.def("getSound3DPtr", &SoundManager::getSound3DPtr ,
 			return_value_policy<reference_existing_object>() )
 
 			.def("getCurrentBackgroundMusic", &SoundManager::getCurrentBackgroundMusic ,
 			return_value_policy<reference_existing_object>() )
 
 			.def( "getSingleton", &SoundManager::getSingleton ,
 			return_value_policy<reference_existing_object>() )
 			.staticmethod( "getSingleton" )
 			;
 	}
	//----------------------------------------------------------------
#endif// comment by lss when 2009-11-9 18:28:24

	//----------------------------------------------------------------
	void exportSprite()
	{
		using namespace boost::python;
		using namespace vgSprite;

		class_<KeyFrameObject, bases<vgKernel::Renderer ,
			vgKernel::TransparentObject, vgKernel::DissolveObject>,
			boost::noncopyable>( "KeyFrameObject" )
			.def("getKeyFrameCount", &KeyFrameObject::getKeyFrameCount )
			.def("getPlayingState", &KeyFrameObject::getPlayingState )
			.def("getStartFrame", &KeyFrameObject::getStartFrame )
			.def("getEndFrame", &KeyFrameObject::getEndFrame )
			.def("getLoopState", &KeyFrameObject::getLoopState )
			.def("getSpeed", &KeyFrameObject::getSpeed )

			.def("setPlayState", &KeyFrameObject::setPlayState )
			.def("setStartFrame", &KeyFrameObject::setStartFrame )
			.def("setEndFrame", &KeyFrameObject::setEndFrame )
			.def("setSpeed", &KeyFrameObject::setSpeed )

			.def("reset", &KeyFrameObject::reset )

			.def("startPlayingByTime", &KeyFrameObject::startPlayingByTime )
			.def("startPlayingByFrame", &KeyFrameObject::startPlayingByFrame )
			.def("getTimeWithFrame", &KeyFrameObject::getTimeWithFrame )
			.def("pausePlaying", &KeyFrameObject::pausePlaying)
			.def("continuePlaying", &KeyFrameObject::continuePlaying)
			;


#if 0
		class_<AnimatedObjectManager, bases<vgKernel::RendererHolder>,
			boost::noncopyable>( 
			"AnimatedObjectManager" , 
			"控制所有动画的类,包括关键帧动画和ms3d的动画.", no_init )
			.def("addKeyFrameNodePtr", &AnimatedObjectManager::addKeyFrameNodePtr,  
			"添加关键帧动画.")

			.def("renderMovingNode", &AnimatedObjectManager::renderMovingNode,
			"渲染动画实体.")

			.def("startAllKeyFramePlaying", &AnimatedObjectManager::startAllKeyFramePlaying )

			.def("getKeyFrameByName", &AnimatedObjectManager::getKeyFrameByName ,
			return_value_policy<reference_existing_object>() )

			.def( "getSingleton", &AnimatedObjectManager::getSingleton ,
			return_value_policy<reference_existing_object>() )
			.staticmethod( "getSingleton" )
			;
#endif
	}
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	BOOST_PYTHON_MODULE(vgMusic)
	{
		exportMusic();
	}
	//----------------------------------------------------------------
	void registerScriptModule_vgMusic()
	{
		initvgMusic();
	}
	//----------------------------------------------------------------



	//----------------------------------------------------------------
	BOOST_PYTHON_MODULE(vgSprite)
	{

		exportSprite();
	}
	//----------------------------------------------------------------
	void registerScriptModule_vgSprite()
	{
		initvgSprite();
	}
	//----------------------------------------------------------------


	//----------------------------------------------------------------
	void exportVector()
	{

		return;
#if 0
		using namespace boost::python;
		using namespace vgVector;


		enum_<RenderType>("RenderType")
			.value("vgRenderNormal", vgRenderNormal)
			.value("vgRenderDisplay", vgRenderDisplay)
			.value("vgRenderVBO", vgRenderVBO)
			;

		class_<VectorManager >( "VectorManager" , no_init )
			.def("count", &VectorManager::count )
			.def("open", &VectorManager::open )
			.def("isOpened", &VectorManager::isOpened )


			.def("translateAllLayers", &VectorManager::translateAllLayers )
			.def("translateUpdateSceneCenter", &VectorManager::translateUpdateSceneCenter )


			.def("setVisibleLayers", &VectorManager::setVisibleLayers )
			.def("getVisibleSelectLayers", &VectorManager::getVisibleSelectLayers )
			.def("switchLayersModeRenderWay", &VectorManager::switchLayersModeRenderWay )
			.def("attachShapeLayerToTerrain", &VectorManager::attachShapeLayerToTerrain )

			.def("switchRenderType", &VectorManager::switchRenderType )
			.def("setRenderType", &VectorManager::setRenderType )
			.def("getRenderType", &VectorManager::getRenderType )


			.def("getVersionFileWriteVSG", &VectorManager::getVersionFileWriteVSG )
			.def("getVersionFileReadVSG", &VectorManager::getVersionFileReadVSG )

			.def("writeLayersToVSGFile", &VectorManager::writeLayersToVSGFile )
			.def("readLayersFromVSGFile", &VectorManager::readLayersFromVSGFile )


			.def( "getSingleton", &VectorManager::getSingleton ,
			return_value_policy<reference_existing_object>() )
			.staticmethod( "getSingleton" )
			;



#endif

	}
	//----------------------------------------------------------------


	////----------------------------------------------------------------
	//BOOST_PYTHON_MODULE(vgKernel)
	//{
	//	using namespace vgScript;
	//	exportKernel();
	//	exportKernelObjects();
	//}


	//----------------------------------------------------------------
	BOOST_PYTHON_MODULE(vgVector)
	{
		exportVector();
	}
	//----------------------------------------------------------------
	void registerScriptModule_vgVector()
	{
		initvgVector();
	}
	//----------------------------------------------------------------
	void exportOtherModules()
	{

		//initvgKernel();


		registerScriptModule_vgMusic();
		registerScriptModule_vgSprite();
		registerScriptModule_vgVector();
	}
}// end of namespace 

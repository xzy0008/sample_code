


#include <vgStableHeaders.h>
#include <vgScript/vgscExportVisualEffects.h>
#include <vgVisualEffects/vgviBackgroundManager.h>
#include <vgVisualEffects/vgviFogManager.h>
#include <vgScript/vgscDefinition.h>


namespace vgScript {
	

	using namespace vgVisualEffects;


	VGSC_STATIC_FUNC_DECLARE( ColorValu , ZERO )
	VGSC_STATIC_FUNC_DECLARE( ColorValu , Black )
	VGSC_STATIC_FUNC_DECLARE( ColorValu , White )
	VGSC_STATIC_FUNC_DECLARE( ColorValu , Red )
	VGSC_STATIC_FUNC_DECLARE( ColorValu , Green )
	VGSC_STATIC_FUNC_DECLARE( ColorValu , Blue )
	VGSC_STATIC_FUNC_DECLARE( ColorValu , Yellow )

	//----------------------------------------------------------------
	void exportVisualEffects()
	{
		using namespace boost::python;
		using namespace vgVisualEffects;

		//class_<ColorValu>("ColorValu")
		//	.def( init<float, float,float,float>() )
		//	.def( "saturate", &ColorValu::saturate )
		//	.def( "saturateCopy", &ColorValu::saturateCopy )
		//	.def( "getDetails", &ColorValu::getDetails )

		//	.def(self += self)
		//	.def(self + self)
		//	.def(self -= self)
		//	.def(self - self)
		//	.def(self *= float() )
		//	.def(self * float() )
		//	.def(self /= float() )
		//	.def(self / float() )
		//	.def(self == self)
		//	.def(self != self)

		//	.def("__str__", &ColorValu::getDetails )

		//	.def_readwrite( "r" , &ColorValu::r )
		//	.def_readwrite( "g" , &ColorValu::g )
		//	.def_readwrite( "b" , &ColorValu::b )
		//	.def_readwrite( "a" , &ColorValu::a )

		//	.add_static_property( "ZERO" , 
		//	&VGSC_STATIC_FUNC_PTR( ColorValu , ZERO ) )
		//	.add_static_property( "Black" , 
		//	&VGSC_STATIC_FUNC_PTR( ColorValu , Black ) )
		//	.add_static_property( "White" , 
		//	&VGSC_STATIC_FUNC_PTR( ColorValu , White ) )
		//	.add_static_property( "Red" , 
		//	&VGSC_STATIC_FUNC_PTR( ColorValu , Red ) )
		//	.add_static_property( "Green" , 
		//	&VGSC_STATIC_FUNC_PTR( ColorValu , Green ) )
		//	.add_static_property( "Blue" , 
		//	&VGSC_STATIC_FUNC_PTR( ColorValu , Blue ) )
		//	.add_static_property( "Yellow" , 
		//	&VGSC_STATIC_FUNC_PTR( ColorValu , Yellow ) )
		//;


		class_<BackgroundManager >( "BackgroundManager" , no_init )
			.def("setDefaultBackgroundColor", &BackgroundManager::setDefaultBackgroundColor )
			.def("configBackground", &BackgroundManager::configBackground )

			.def( "getSingleton", &BackgroundManager::getSingleton ,
				return_value_policy<reference_existing_object>() )
			.staticmethod( "getSingleton" )
			;

		class_<FogManager >( "FogManager" , no_init )
			.def("getEnabledFlag", &FogManager::getEnabledFlag )
			.def("setEnabledFlag", &FogManager::setEnabledFlag )
			.def("getFogParams", &FogManager::getFogParams )
			.def("setFogParams", &FogManager::setFogParams )

			.def("getFogStart", &FogManager::getFogStart )
			.def("getFogEnd", &FogManager::getFogEnd )
			.def("setFogParams", &FogManager::setFogParams )
			.def("setFogParams", &FogManager::setFogParams )

			.def( "getSingleton", &FogManager::getSingleton ,
			return_value_policy<reference_existing_object>() )
			.staticmethod( "getSingleton" )
			;
	}
	//----------------------------------------------------------------
}// end of namespace vgScript

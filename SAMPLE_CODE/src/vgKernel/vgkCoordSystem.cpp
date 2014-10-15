


#include <vgStableHeaders.h>
#include <vgKernel/vgkCoordSystem.h>

#include <vgConf/vgcoProjectConfig.h>
#include <vgConf/vgcoProjectConfigRegProxy.h>


namespace vgKernel {
	
	
#define VGK_COORDSYS_NAME "CoordSystem"

#define VGK_COORDSYS_ORIGIN_X		"OriginX"
#define VGK_COORDSYS_ORIGIN_X_DEFAULT		0.0
#define VGK_COORDSYS_ORIGIN_X_DEFAULT_STR		"0.0"

#define VGK_COORDSYS_ORIGIN_Y		"OriginY"
#define VGK_COORDSYS_ORIGIN_Y_DEFAULT		0.0
#define VGK_COORDSYS_ORIGIN_Y_DEFAULT_STR		"0.0"

#define VGK_COORDSYS_ORIGIN_Z		"OriginZ"
#define VGK_COORDSYS_ORIGIN_Z_DEFAULT		0.0
#define VGK_COORDSYS_ORIGIN_Z_DEFAULT_STR		"0.0"


	/**
		在这里创建project config
	*/
	vgConf::ProjectConfigRegProxy vgk_coord_system ( 
		VGK_COORDSYS_NAME , VGK_COORDSYS_ORIGIN_X , 
		VGK_COORDSYS_ORIGIN_X_DEFAULT_STR );
	
	vgConf::ProjectConfigRegProxy vgk_coord_system1 ( 
		VGK_COORDSYS_NAME , VGK_COORDSYS_ORIGIN_Y , 
		VGK_COORDSYS_ORIGIN_Y_DEFAULT_STR );

	vgConf::ProjectConfigRegProxy vgk_coord_system2 ( 
		VGK_COORDSYS_NAME , VGK_COORDSYS_ORIGIN_Z , 
		VGK_COORDSYS_ORIGIN_Z_DEFAULT_STR );

	//----------------------------------------------------------------
	void CoordSystem::readProject( const String& projpath , const String& projname )
	{
		float ox = VG_PROJCONF_GET_FLOAT( 
			VGK_COORDSYS_NAME,
			VGK_COORDSYS_ORIGIN_X );

		float oy = VG_PROJCONF_GET_FLOAT( 
			VGK_COORDSYS_NAME,
			VGK_COORDSYS_ORIGIN_Y );

		float oz = VG_PROJCONF_GET_FLOAT( 
			VGK_COORDSYS_NAME,
			VGK_COORDSYS_ORIGIN_Z );


		setProjectionCoord( vgKernel::Vec3(ox , oy ,oz) );
	}
	//----------------------------------------------------------------
	void CoordSystem::saveProject()
	{
		VG_PROJCONF_SET( VGK_COORDSYS_NAME , 
			VGK_COORDSYS_ORIGIN_X , 
			_coord.x );

		VG_PROJCONF_SET( VGK_COORDSYS_NAME , 
			VGK_COORDSYS_ORIGIN_Y , 
			_coord.y );

		VG_PROJCONF_SET( VGK_COORDSYS_NAME , 
			VGK_COORDSYS_ORIGIN_Z , 
			_coord.z );
	}
	//----------------------------------------------------------------
	void CoordSystem::setProjectionCoord( const vgKernel::Vec3& new_coord )
	{
		_coord = new_coord;

		notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);
	}
	//----------------------------------------------------------------


}// end of namespace vgKernel

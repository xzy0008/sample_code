



#include <vgStableHeaders.h>
#include <vgKernel/vgkSerializerManager.h>
#include <vgConf/vgcoProjectConfig.h>
#include <vgConf/vgcoProjectConfigRegProxy.h>


namespace vgKernel {
	
	
#define VGK_SERIALMGR_NAME "Serialize"

#define VGK_SERIALMGR_VERSION		"version"
#define VGK_SERIALMGR_VERSION_DEFAULT		0
#define VGK_SERIALMGR_VERSION_DEFAULT_STR		"0"


	///**
	//	在这里创建project config
	//*/
	//vgConf::ProjectConfigRegProxy vgk_coord_system ( 
	//	VGK_COORDSYS_NAME , VGK_COORDSYS_ORIGIN_X , 
	//	VGK_COORDSYS_ORIGIN_X_DEFAULT_STR );



	
	//----------------------------------------------------------------
	//bool SerializerManager::pushSerializer( Serializer* serial )
	//{
	//	return true;
	//}
	//----------------------------------------------------------------
	bool SerializerManager::readProject( const String& projpath , const String& projname )
	{
		return true;

	}
	//----------------------------------------------------------------
	bool SerializerManager::saveProject( const String& projpath , const String& projname )
	{

		return true;
	}
	//----------------------------------------------------------------
	void SerializerManager::clearSerializers()
	{
		//_serializers.clear();
	}
	//----------------------------------------------------------------



}// end of namespace vgKernel

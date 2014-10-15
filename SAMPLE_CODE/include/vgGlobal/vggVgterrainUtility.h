

#ifndef __VGTERRAINUTILITY_H__
#define __VGTERRAINUTILITY_H__

#include <vgGlobal/vgglDefinition.h>

namespace vgGlobal{

	//using namespace vgXXX;
	
	
	class	VGGL_EXPORT TerrainUtility
	{
	public:
		TerrainUtility();
		~TerrainUtility();

	public:

		static bool saveVtrAndVgi( String folderpath );
		
		static void setSaveMode( bool bMode );
	};
}//namespace vgGlobal

#endif//__VGTERRAINUTILITY_H__



#ifndef __VGTERRITORY_TERRAINLEVELLING_H__
#define __VGTERRITORY_TERRAINLEVELLING_H__


#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgTerritory/vgVgtrFile.h>


namespace vgTerritory {


	/**
		@date 	2008/05/06  16:22	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGT_EXPORT TerrainLevelling
	{
	public:
		TerrainLevelling()
		{
			
		}
		~TerrainLevelling()
		{
			
		}
	
	
		//static bool doLevelling( const GLuint& heightmapid , const int& xnum , 
		//	const int& znum ,
		//	vgKernel::Vec3* vec3 , const float& lastheight );
	
		static bool doLevelling( const VgtrFilePtr vgtrfile , const GLuint& heightmapid ,
			vgKernel::Vec3* vec3list, const int& vec3listnum , 
			const float& lastheight );
	
		static bool saveVgtrFile( const String& outputfilename ,
			const VgtrFilePtr vgtrfile , 
			const GLuint& heightmapid );

	private:

		static bool dumpDataToTexture( const VgtrFilePtr vgtrfile , 
			const GLuint& heightmapid );

		static bool dumpTextureToData( const GLuint& heightmapid , 
			const VgtrFilePtr vgtrfile );
	};
	
	
	
}// end of namespace vgTerritory

#endif // end of __VGTERRITORY_TERRAINLEVELLING_H__
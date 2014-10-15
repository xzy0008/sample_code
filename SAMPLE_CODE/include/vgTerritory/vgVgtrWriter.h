


#ifndef __VGTERRITORY_VGTRWRITER_H__
#define __VGTERRITORY_VGTRWRITER_H__


#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgTerritory/vgDemBlock.h>
#include <vgTerritory/vgVgtrFile.h>


namespace vgTerritory {

	/**
		@date 	2008/04/02  9:51	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGT_EXPORT VgtrWriter
	{
	public:
		VgtrWriter()
		{
			
		}
		~VgtrWriter()
		{
			
		}

		static bool writeVgtrToFile( const VgtrFilePtr vgtr , const String& outputfilename );
	
		static VgtrFilePtr convertDemBlocksToVgtr( const String& vgtrname , 
			const DemBlockVectorPtr pdemblocks,
			const int& cell_tex_size , const long& N );
	
	private:
		static void errorMsgOutput( const String& errMsg = "" );

		static bool setVgtrData( float* data , const int& data_width ,
			const DemBlockPtr pdem );
	};
	
	
	
}// end of namespace vgTerrrain

#endif // end of __VGTERRITORY_VGTRWRITER_H__
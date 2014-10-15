


#ifndef __VGTERRITORY_TDEMHEADER_H__
#define __VGTERRITORY_TDEMHEADER_H__

#include <vgKernel/vgkForward.h>

	
namespace vgTerritory {

	/**
		@date 	2008/08/26  19:09	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class DemHeader
	{
	public:
		DemHeader();
		~DemHeader();

		bool readFromFile( const String& demfilename );
	
	
	private:

		static void errorMsgOutput( const String& errMsg = "" );

	public:

		uint _xNum;
		uint _zNum;

		double _originX;
		double _originZ;

		float _cellSize;

		String _demFilename;


	};
	
	
}// end of namespace vgTerritory
	


#endif // end of __VGTERRITORY_TDEMHEADER_H__
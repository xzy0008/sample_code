



#include <vgStableHeaders.h>
#include <vgTerritory/vgtHugeProcessGlobal.h>


namespace vgTerritory {
	
	
	
	
	//----------------------------------------------------------------
	HugeProcess::Global::Global()
	{
		_smallBlockWidth = 0;
		_isValid = false;
		_widthAndHeightAddition = 0;

		_removeTempFiles = true;
		_removeInputFiles = false;

		memset( _filledColor , 0 , 4 );
	}
	//----------------------------------------------------------------
	HugeProcess::Global::~Global()
	{

	}
	//----------------------------------------------------------------



}// end of namespace vgTerritory

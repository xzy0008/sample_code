


#ifndef __VGAXISALIGNEDBOX2_H__
#define __VGAXISALIGNEDBOX2_H__

#include <vgPrerequisites.h>


namespace vgMath {

	/**
		@date 	2008/02/23  11:02	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class AxisAlignedBox2
	{
	public:
		// construction
		AxisAlignedBox2 (); 
		{
			// uninitialized
		}

		AxisAlignedBox2 (Real fXMin, Real fXMax, Real fYMin, Real fYMax)
		{
			Min[0] = fXMin;
			Max[0] = fXMax;
			Min[1] = fYMin;
			Max[1] = fYMax;
		}

		Vector2 _min , _max;
	};
	
	
}// end of namespace vgMath

#endif // end of __VGAXISALIGNEDBOX2_H__
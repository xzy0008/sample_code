// vgstruct1.cpp: implementation of the vgstruct class.
//
//////////////////////////////////////////////////////////////////////
#include <vgStableHeaders.h>
#include <vgMath/vgfBoundingBox.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace vgMath{
	



	//----------------------------------------------------------------

	void BoundingBox::merge( BoundingBox box )
	{
		minPoint.makeFloor(box.minPoint);
		minPoint.makeFloor(box.maxPoint);
		maxPoint.makeCeil(box.maxPoint);
		maxPoint.makeCeil(box.minPoint);
	}

	void BoundingBox::merge(const vgKernel::Box& rhs)
	{
		minPoint.makeFloor(rhs._minVertex);
		minPoint.makeFloor(rhs._maxVertex);
		maxPoint.makeCeil(rhs._maxVertex);
		maxPoint.makeCeil(rhs._minVertex);
	}


}
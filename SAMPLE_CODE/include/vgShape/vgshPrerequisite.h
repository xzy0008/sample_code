


#ifndef __VGSHPREREQUISITE_H__
#define __VGSHPREREQUISITE_H__



#include <vgShape/vgshDefinition.h>
#include <vgKernel/vgkForward.h>

#include <vgKernel/vgkSharePtr.h>
#include <vgShape/vgshBox3d.h>
#include <vgShape/vgshRay3d.h>
#include <vgShape/vgshRayLine3d.h>
#include <vgShape/vgshDrawingDescriptor.h>

#include <vgShape/vgshCheckOgrError.h>



namespace vgShape {

	struct RingStruct
	{
		RingStruct( int points = 0, double* addr = NULL)
		{
			_numPoints = points;
			_pointsBeginAddr = addr;
		}
		int _numPoints;
		double* _pointsBeginAddr; //x y z
	};


	typedef vgKernel::SharePtr<OGRFeature> OGRFeaturePtr;

	const int RENDERER_TYPE_SHAPE_LAYER	= 16151;




	//enum QueryType
	enum	QueryType
	{
		QUERY_NONE,
		GREEN_RATIO,
		PLOT_RATIO,
		TYPE_COUNT
	};
}// end of namespace vgShape




#endif // end of __VGSHPREREQUISITE_H__
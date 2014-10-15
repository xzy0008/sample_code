
#include <vgStableHeaders.h>
#include <vgplan/vgPlanBoxAB.h>

#define INFINITEPLAN 999999

namespace vgPlan
{

	PlanBoundboxAB::PlanBoundboxAB()
	{
		minvertex = vgKernel::Vec2( INFINITEPLAN, INFINITEPLAN );
		maxvertex = vgKernel::Vec2( -INFINITEPLAN, -INFINITEPLAN );
	}
	void PlanBoundboxAB::merge( vgKernel::Vec2 _vertex )
	{
		maxvertex.makeCeil(_vertex);
		minvertex.makeFloor(_vertex);
	}


	void PlanBoundboxAB::setminvertex( vgKernel::Vec2 _vertex )
	{
		minvertex = _vertex;
	}

	void PlanBoundboxAB::setmaxvertex( vgKernel::Vec2 _vertex )
	{
		maxvertex = _vertex;
	}
}
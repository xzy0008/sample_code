
#include<vgStableHeaders.h>

#include <vgPlan/vgPlanstreet.h>

//#include <vgPlan/vgPlanpolygon.h>


namespace vgPlan
{
	void vgPlanstreet::setdefault()
	{
		return;
	}

	void vgPlanstreet::render()
	{
		vector< vgPlanstreetLine * >::iterator _itr1 = streetpolys.begin();
		vector< vgPlanstreetLine *>::iterator _end1 = streetpolys.end();

		for (; _itr1 != _end1; _itr1++ )
		{
			(*_itr1)->render();
		}
	}

	void vgPlanstreet::addstreetLine( vgPlanstreetLine *pp )
	{
		streetpolys.push_back( pp );

	}

	void vgPlanstreet::genuniongeometry()
	{
		vector< vgPlanstreetLine * >::iterator _itr1 = streetpolys.begin();
		vector< vgPlanstreetLine *>::iterator _end1 = streetpolys.end();

		for (; _itr1 != _end1; _itr1++ )
		{
			geo->Union((*_itr1)->getGeometry());
		}

	}
}
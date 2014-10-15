#pragma once

#include <vgKernel/vgkVec3.h>
#include <vgKernel/vgkUniqueID.h>

namespace vgGIS3D
{
	class RouteMap
	{
	public:

		virtual void render() {}

		virtual void findRoute(vgKernel::Vec3 startPoint, vgKernel::Vec3 endPoint, vector<int>& route) {}
		
		virtual bool getRouteInfo(vgKernel::Vec3 pointInRoad) { return false; }
		
		virtual bool getRouteInfo(string routeName) { return false; }

		virtual bool isRouteConnected(string routeName1, string routeName2) { return false; }

		virtual bool isRouteConnected(vgKernel::Vec3 pointInRoad1, vgKernel::Vec3 pointInRoad2) { return false;}
	};
}
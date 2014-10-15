#ifndef __VGPLANGROUND__
#define __VGPLANGROUND__


#include <gdal/ogrsf_frmts.h>
#include <gdal/ogr_api.h>

//分析地块每次限定只分析一块

namespace vgPlan{

	class vgPlanground
	{
	public:

		// 此接口提供底图的Gemoetry.
		virtual OGRGeometry *getOgrGeometry() = 0;
// 
// 		virtual void setdefault() = 0;
//		纯数据类，暂时不考虑渲染.
// 		virtual void render() = 0;
	};


}

#endif
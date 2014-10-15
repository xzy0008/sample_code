


#ifndef __VGKPOINTINPOLYGON_H__
#define __VGKPOINTINPOLYGON_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkVec2.h>
	
namespace vgKernel {


	class  VGK_EXPORT PointInPolygon
	{
	public:

		// init it.
		// iQuantity -- means NUMBER
		// akVertex -- means VECTOR ARRAY
		PointInPolygon (int iQuantity, const Vec2* akVertex);

		// simple polygons (ray-intersection counting)
		bool contains (const Vec2& rkP) const;

	private:

		int m_iQuantity;
		const Vec2* m_akVertex;
	};
	
	
}// end of namespace vgKernel
	


#endif // end of __VGKPOINTINPOLYGON_H__
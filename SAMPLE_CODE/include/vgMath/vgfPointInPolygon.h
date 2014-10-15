


#ifndef __VGFPOINTINPOLYGON_H__
#define __VGFPOINTINPOLYGON_H__

#include <vgCore/vgPrerequisites.h>
#include <vgMath/vgfVector2.h>


namespace vgMath {

	/**
		@date 	2007/12/29  15:30	
		@author  Leven
	
		@brief 	
	
		@see    
	*/

	class PointInPolygon
	{
	public:
		
		// init it.
		// iQuantity -- means NUMBER
		// akVertex -- means VECTOR ARRAY
		PointInPolygon (int iQuantity, const Vector2* akVertex);

		// simple polygons (ray-intersection counting)
		bool contains (const Vector2& rkP) const;

	private:

		int m_iQuantity;
		const Vector2* m_akVertex;
	};
	
	
	
}// end of namespace vgMath

#endif // end of __VGFPOINTINPOLYGON_H__
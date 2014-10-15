


#ifndef __VGKTRIANGLE3_H__
#define __VGKTRIANGLE3_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkMath.h>
	
namespace vgKernel {

	/**
		@date 	2008/11/13  14:46	
		@author  xy
	
		@brief 	
	
		@see    
	*/
	class  VGK_EXPORT Triangle3
	{
	public:
		// The triangle is represented as an array of three vertices, V0, V1,
		// and V2.

		// construction
		Triangle3 (const Vec3& rkV0, const Vec3& rkV1,
			const Vec3& rkV2);
		Triangle3 (const Vec3 akV[3]);

		// distance from the point Q to the triangle
		float DistanceTo (const Vec3& rkQ) const;

		Vec3 V[3];
	};


	
	
}// end of namespace vgKernel
	


#endif // end of __VGKTRIANGLE3_H__
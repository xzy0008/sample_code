



#ifndef __VGKSEGMENT3_H__
#define __VGKSEGMENT3_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkVec3.h>



namespace vgKernel {

	/**
		@date 	2008/11/13  14:24	
		@author  xy

		@brief 	定义线段.注意,和Ray不同,这个是有长度限定的.

		@see    
	*/
	class  VGK_EXPORT Segment3
	{
	public:
		// The segment is represented as P+t*D, where P is the segment origin,
		// D is a unit-length direction vector and |t| <= e.  The value e is
		// referred to as the extent of the segment.  The end points of the
		// segment are P-e*D and P+e*D.  The user must ensure that the direction
		// vector is unit-length.  The representation for a segment is analogous
		// to that for an oriented bounding box.  P is the center, D is the
		// axis direction, and e is the extent.

		// Construction.
		Segment3 (const Vec3& rkOrigin, const Vec3& rkDirection,
			float fExtent);

		// The segment is:
		//   origin = (end0+end1)/2
		//   direction = (end1-end0)/Length(end1-end0)
		//   extent = 0.5*Length(end1-end0)
		Segment3 (const Vec3& rkEnd0, const Vec3& rkEnd1);

		// end points
		Vec3 getPosEnd () const;  // P+e*D
		Vec3 getNegEnd () const;  // P-e*D

		Vec3 Origin, Direction;
		float Extent;
	};


}// end of namespace vgKernel


#endif // end of __VGKSEGMENT3_H__
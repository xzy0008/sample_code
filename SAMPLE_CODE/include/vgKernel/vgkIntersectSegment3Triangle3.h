


#ifndef __VGKINTERSECTSEGMENT3TRIANGLE3_H__
#define __VGKINTERSECTSEGMENT3TRIANGLE3_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkIntersector.h>
#include <vgKernel/vgkTriangle3.h>
#include <vgKernel/vgkSegment3.h>

	
namespace vgKernel {

	/**
		@date 	2008/11/13  14:52	
		@author  xy
	
		@brief 	
	
		@see    
	*/
	class  VGK_EXPORT IntrSegment3Triangle3
		: public Intersector
	{
	public:
		IntrSegment3Triangle3 (const Segment3& rkSegment,
			const Triangle3& rkTriangle);

		// Object access.
		const Segment3& GetSegment () const;
		const Triangle3& GetTriangle () const;

		// Test-intersection query.
		virtual bool Test ();

		// Find-intersection query.  The point of intersection is
		//   P = origin + t*direction = b0*V0 + b1*V1 + b2*V2
		virtual bool Find ();
		float GetSegmentT () const;
		float GetTriB0 () const;
		float GetTriB1 () const;
		float GetTriB2 () const;

		//// Dynamic test-intersection query.
		//virtual bool Test (float fTMax, const Vec3& rkVelocity0,
		//	const Vec3& rkVelocity1);

		// Dynamic find-intersection query.  The first point of contact is
		// accessed by GetPoint(0), when there is a single contact, or by
		// GetPoint(0) and GetPoint(1), when the contact is a segment, in which
		// case the fetched points are the segment endpoints.  The first time of
		// contact is accessed by GetContactTime().
		//virtual bool Find (float fTMax, const Vec3& rkVelocity0,
		//	const Vec3& rkVelocity1);

		int GetQuantity () const;
		const Vec3& GetPoint (int i) const;

	private:

		using Intersector::IT_EMPTY;
		using Intersector::IT_POINT;
		using Intersector::IT_SEGMENT;
		using Intersector::m_fContactTime;
		using Intersector::m_iIntersectionType;

		// The objects to intersect.
		const Segment3* m_pkSegment;
		const Triangle3* m_pkTriangle;

		// Information about the stationary intersection set.
		float m_fSegmentT, m_fTriB0, m_fTriB1, m_fTriB2;

		// Information about the dynamic intersection set.
		int m_iQuantity;
		Vec3 m_akPoint[2];
	};

	
	
}// end of namespace vgKernel
	


#endif // end of __VGKINTERSECTSEGMENT3TRIANGLE3_H__
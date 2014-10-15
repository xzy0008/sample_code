


#ifndef __VGKINTERSECTOR_H__
#define __VGKINTERSECTOR_H__

#include <vgKernel/vgkForward.h>

	
namespace vgKernel {

	/**
		@date 	2008/11/13  14:56	
		@author  xy
	
		@brief 	
	
		@see    
	*/
	class  VGK_EXPORT Intersector
	{
	public:
		// abstract base class
		virtual ~Intersector ();

		// Static intersection queries.  The default implementations return
		// 'false'.  The Find query produces a set of intersection.  The derived
		// class is responsible for providing access to that set, since the nature
		// of the set is dependent on the object types.
		virtual bool Test ();
		virtual bool Find ();

		// Dynamic intersection queries.  The default implementations return
		// 'false'.  The Find query produces a set of first contact.  The derived
		// class is responsible for providing access to that set, since the nature
		// of the set is dependent on the object types.
		virtual bool Test (float fTMax, const Vec3& rkVelocity0,
			const Vec3& rkVelocity1);
		virtual bool Find (float fTMax, const Vec3& rkVelocity0,
			const Vec3& rkVelocity1);

		// The time at which two objects are in first contact for the dynamic
		// intersection queries.
		float GetContactTime () const;

		// information about the intersection set
		enum
		{
			IT_EMPTY,
			IT_POINT,
			IT_SEGMENT,
			IT_RAY,
			IT_LINE,
			IT_POLYGON,
			IT_PLANE,
			IT_POLYHEDRON,
			IT_OTHER
		};
		int GetIntersectionType () const;

	protected:
		Intersector ();

		float m_fContactTime;
		int m_iIntersectionType;
	};

	
	
}// end of namespace vgKernel
	


#endif // end of __VGKINTERSECTOR_H__
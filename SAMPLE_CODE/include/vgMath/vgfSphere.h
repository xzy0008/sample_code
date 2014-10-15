/*
-----------------------------------------------------------------------------
  VRES(Virtual Reality GIS Engine System)    
  -------------------------------------------------------------
  License details ... waiting to add...
  -------------------------------------------------------------
  Copyright  (C) 2007 , leven - All Rights Reserved
-----------------------------------------------------------------------------
*/

#ifndef __VGFSPHERE_H__
#define __VGFSPHERE_H__

#include <vgMath/vgfPrerequisites.h>
#include <vgMath/vgfVector3.h>

namespace vgMath {

	/**
		@date 	2007/02/22  17:58	
		@author  leven
	
		@brief 	球体类.比较简单的实现.
	
		A sphere primitive, mostly used for bounds checking. 

		A sphere in math texts is normally represented by the function
		x^2 + y^2 + z^2 = r^2 (for sphere's centered on the origin).  stores spheres
		simply as a center point and a radius.

		@see    
	*/

	class VgfExport Sphere
	{
	protected:

		Real mRadius;
		Vector3 mCenter;

	public:
		/** Standard constructor - creates a unit sphere around the origin.*/
		Sphere() : mRadius(1.0), mCenter(Vector3::ZERO) {}

		Sphere(const Vector3& center, Real radius)
			: mRadius(radius), mCenter(center) {}

		/// 得到半径值.
		inline Real getRadius(void) const { return mRadius; }

		/// 设置半径值.
		inline void setRadius(Real radius) { mRadius = radius; }

		/// 得到中心点
		inline const Vector3& getCenter(void) const { return mCenter; }

		/// 设置中心点.
		inline void setCenter(const Vector3& center) { mCenter = center; }

		///2个球体的相交测试
		inline bool intersects(const Sphere& s) const
		{
			return (s.mCenter - mCenter).squaredLength() <=
				Math::Sqr(s.mRadius + mRadius);
		}

		///球体与box的相交测试.注意职责的转移:涉及2个以上不同种类的数学运算理应
		///都放入Math类中.
		inline bool intersects(const AxisAlignedBox& box) const
		{
			return Math::intersects(*this, box);
		}

		///球体与平面的相交测试.
		/** Returns whether or not this sphere interects a plane. */
		inline bool intersects(const Plane& plane) const
		{
			return Math::intersects(*this, plane);
		}

		///球体与点的相交测试.
		/** Returns whether or not this sphere interects a point. */
		inline bool intersects(const Vector3& v) const
		{
			return ((v - mCenter).squaredLength() <= Math::Sqr(mRadius));
		}

		inline friend StdOStream& operator << ( StdOStream& o , const Sphere& s )
		{
			o << _T("Sphere( Center = ") << s.mCenter << _T(" , Radius = ") <<  s.mRadius << _T(" )");
			return o;
		}

		inline String getDetails() const
		{
			StdOStringStream o;
			//o << "Sphere( Center = " << mCenter << " , Radius = " <<  mRadius << " )";
			o << (*this);
			return o.str();
		}

	};

	
	
	
}

#endif // end of __VGFSPHERE_H__
/*
-----------------------------------------------------------------------------
  VRES(Virtual Reality GIS Engine System)    
  -------------------------------------------------------------
  License details ... waiting to add...
  -------------------------------------------------------------
  Copyright  (C) 2007 , leven - All Rights Reserved
-----------------------------------------------------------------------------
*/

#ifndef __VGFPLANE_H__
#define __VGFPLANE_H__

#include <vgMath/vgfPrerequisites.h>


namespace vgMath {

	/**
		@date 	2007/02/20  10:50	
		@author  leven
	
		@brief 	

			平面类.通过方程Ax + By + Cz + D = 0 表征一个平面.其中,
			A , B , C 的物理意义是平面上的法线向量.而D值表示平面和原点的距离.
		
			A plane is defined in 3D space by the equation
			Ax + By + Cz + D = 0
	
			This equates to a vector (the normal of the plane, whose x, y
		and z components equate to the coefficients A, B and C
		respectively), and a constant (D) which is the distance along
		the normal you have to go to move the plane back to the origin.

		@see    
	*/
	class VgfExport Plane
	{
	public:

		Plane ();
		Plane (const Plane& rhs);

		///构造函数,参数为normal和以normal为方向移动的距离,注意正负.
		/** Construct a plane through a normal, and a distance to move the plane along the normal.*/
		Plane (const Vector3& rkNormal, Real fConstant);
		Plane (const Vector3& rkNormal, const Vector3& rkPoint);
		Plane (const Vector3& rkPoint0, const Vector3& rkPoint1,
			const Vector3& rkPoint2);

		/** The "positive side" of the plane is the half space to which the
		plane normal points. The "negative side" is the other half
		space. The flag "no side" indicates the plane itself.
		*/
		enum Side
		{
			NO_SIDE,		///表示在平面上,另一个当AABB为NULL时表示不在任何一边上.
			POSITIVE_SIDE,	///表示在正面
			NEGATIVE_SIDE,	///表示在负面
			BOTH_SIDE		///表示在正负2面,用于AABB检测.
		};

	public:	

		///平面的法向量.
		Vector3 normal;
		///平面和原点的距离,联合normal可以确定唯一个Plane
		Real d;

	public:

		/// 得到一个点相对于平面的位置.返回为Side
		Side getSide (const Vector3& rkPoint) const;

		/// 得到一个包围盒相对于平面的位置.返回为Side
		Side getSide (const AxisAlignedBox& rkBox) const;

		/** Returns which side of the plane that the given box lies on.
		The box is defined as centre/half-size pairs for effectively.
		@param centre The centre of the box.
		@param halfSize The half-size of the box.
		@returns
		POSITIVE_SIDE if the box complete lies on the "positive side" of the plane,
		NEGATIVE_SIDE if the box complete lies on the "negative side" of the plane,
		and BOTH_SIDE if the box intersects the plane.
		*/
		Side getSide (const Vector3& centre, const Vector3& halfSize) const;

		///返回伪距离,此值可正可负.负值表示在negative side.
		Real getDistance (const Vector3& rkPoint) const;

		///通过3个点重定义.
		/** Redefine this plane based on 3 points. */
		void redefine(const Vector3& rkPoint0, const Vector3& rkPoint1,
			const Vector3& rkPoint2);

		///通过normal和一个点重定义
		/** Redefine this plane based on a normal and a point. */
		void redefine(const Vector3& rkNormal, const Vector3& rkPoint);

		///向量在plane上的投影.
		/** Project a vector onto the plane. 
		@remarks This gives you the element of the input vector that is perpendicular 
		to the normal of the plane. You can get the element which is parallel
		to the normal of the plane by subtracting the result of this method
		from the original vector, since parallel + perpendicular = original.
		@param v The input vector
		*/
		Vector3 projectVector(const Vector3& v);

		/// 单位化平面.
		/** Normalises the plane.
		@remarks
		This method normalises the plane's normal and the length scale of d
		is as well.
		@note
		This function will not crash for zero-sized vectors, but there
		will be no changes made to their components.
		@returns The previous length of the plane's normal.
		*/
		Real normalise(void);



		/// Comparison operator
		bool operator == (const Plane& rhs) const
		{
			return (rhs.d == d && rhs.normal == normal);
		}
		bool operator != (const Plane& rhs) const
		{
			return (rhs.d != d && rhs.normal != normal);
		}

		inline VgfExport friend StdOStream& operator<< (StdOStream& o, const Plane& p)
		{
			o << _T("Plane(normal=") << p.normal << _T(", d=") << p.d << _T(")");
			return o;
		}

		inline String getDetails() const
		{
			StdOStringStream o;
			o << (*this);
			return o.str();
		}
	};

	typedef std::vector<Plane> PlaneList;

	//inline StdOStream& operator<< (StdOStream& o, const Plane& p)
	//{

	//}
	
}

#endif // end of __VGFPLANE_H__
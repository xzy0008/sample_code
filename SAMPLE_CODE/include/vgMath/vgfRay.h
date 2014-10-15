/*
-----------------------------------------------------------------------------
  VRES(Virtual Reality GIS Engine System)    
  -------------------------------------------------------------
  License details ... waiting to add...
  -------------------------------------------------------------
  Copyright  (C) 2007 , leven - All Rights Reserved
-----------------------------------------------------------------------------
*/

#ifndef __VGFRAY_H__
#define __VGFRAY_H__

#include <vgMath/vgfPrerequisites.h>


namespace vgMath {

	/**
		@date 	2007/02/22  18:02	
		@author  leven
	
		@brief 	光线类.实现比较简单.其中相交测试好像在包含的情况下得出的数据不是很准.
	
		Representation of a ray in space, ie a line with an origin and direction.

		@see    
	*/
	class VgfExport Ray
	{
	protected:

		///光线的起始点.
		Vector3 mOrigin;		

		///光线指示的方向.
		Vector3 mDirection;
	public:

		///默认生成:
		///Ray(Origin = Vector3( 0 , 0 , 0 ) , Direction = Vector3( 0 , 1 , 0 ))
		Ray()
			:mOrigin(Vector3::ZERO), mDirection(Vector3::UNIT_Y) {}

		Ray(const Vector3& origin, const Vector3& direction)
			:mOrigin(origin), mDirection(direction) {}

		/// 设置原点.
		void setOrigin(const Vector3& origin) {mOrigin = origin;} 

		/// 得到原点值.
		const Vector3& getOrigin(void) const {return mOrigin;} 

		/// 设置方向
		void setDirection(const Vector3& dir) {mDirection = dir;} 

		/// 得到方向向量.
		const Vector3& getDirection(void) const {return mDirection;} 

		///得到光线上的一点.mOrigin为getPoint(0),指向的末端为getPoint(1).
		///光线上的范围[0-1].
		///注意,利用intersects测试的返回值再得到点的过程中,参数可能越界.
		///需要越界检查时,取消注释.
		Vector3 getPoint(Real t) const 
		{ 
			//assert( (t <= 1) && (t >= 0) && "访问光线上的点越界" );
			return Vector3(mOrigin + (mDirection * t));
		}
		
		/** Gets the position of a point t units along the ray. */
		Vector3 operator*(Real t) const 
		{ 
			return getPoint(t);
		};

		/// 与平面的相交测试.
		/** Tests whether this ray intersects the given plane. 
		@returns A pair structure where the first element indicates whether
			an intersection occurs, and if true, the second element will
			indicate the distance along the ray at which it intersects. 
			This can be converted to a point in space by calling getPoint().
		*/
		std::pair<bool, Real> intersects(const Plane& p) const
		{
			return Math::intersects(*this, p);
		}

		/** Tests whether this ray intersects the given plane bounded volume. 
		@returns A pair structure where the first element indicates whether
		an intersection occurs, and if true, the second element will
		indicate the distance along the ray at which it intersects. 
		This can be converted to a point in space by calling getPoint().
		*/
		//std::pair<bool, Real> intersects(const PlaneBoundedVolume& p) const
		//{
		//	return Math::intersects(*this, p.planes, p.outside == Plane::POSITIVE_SIDE);
		//}


		///与球的相交测试.返回的pair的第二个值用于getPoint(),可以得到相交点
		/** Tests whether this ray intersects the given sphere. 
		@returns A pair structure where the first element indicates whether
			an intersection occurs, and if true, the second element will
			indicate the distance along the ray at which it intersects. 
			This can be converted to a point in space by calling getPoint().
		*/
		std::pair<bool, Real> intersects(const Sphere& s) const
		{
			return Math::intersects(*this, s);
		}


		/// 与包围盒的相交测试.
		/** Tests whether this ray intersects the given box. 
		@returns A pair structure where the first element indicates whether
			an intersection occurs, and if true, the second element will
			indicate the distance along the ray at which it intersects. 
			This can be converted to a point in space by calling getPoint().
		*/
		std::pair<bool, Real> intersects(const AxisAlignedBox& box) const
		{
			return Math::intersects(*this, box);
		}

		inline friend StdOStream& operator << ( StdOStream& o , const Ray& s )
		{
			o << _T("Ray(Origin = ") << s.mOrigin << _T(" , Direction = ") <<  s.mDirection << _T(")");
			return o;
		}

		inline String getDetails() const
		{
			StdOStringStream o;
			o << (*this);
			return o.str();
		}

		// 得到某一点在这条ray上的垂线相交点
		inline Vector3 getPerpendicularVertex( const Vector3& point )
		{
			Vector3 normalize_dir = mDirection.normalisedCopy();

			float len = normalize_dir.dotProduct( point - mOrigin );

			return  mOrigin + len * normalize_dir;
		}


		inline void getPerspNearAndFarFromBox(  AxisAlignedBox& int_box , 
			float& out_near , float& out_far )
		{
			Vector3 normalize_dir = mDirection.normalisedCopy();

			const Vector3 point = int_box.getCorner( 0 );
			Real len = normalize_dir.dotProduct( point - mOrigin );

			float max_len = len;
			float min_len = len;

			for ( int i = 1 ; i < 8 ; ++i )
			{
				const Vector3 point = int_box.getCorner( i );

				Real len = normalize_dir.dotProduct( point - mOrigin );

				if ( len <= 0.0f )
				{
					continue;
				}

				max_len = Math::Max( len , max_len );
				min_len = Math::Min( len , min_len );
			}

			out_near = min_len;
			out_far = max_len;

			return;
		}

	};

	
	
	
}

#endif // end of __VGFRAY_H__
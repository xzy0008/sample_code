



#ifndef __VGSHRAY3D_H__
#define __VGSHRAY3D_H__



#include <vgShape/vgshDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkRay.h>

	
namespace vgShape {

	/**
		@date 	2009/02/20  20:03	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	/** 
	*/
	class Ray3d
	{
	public:

		///光线的起始点.
		Vec3d mOrigin;		

		///光线指示的方向.
		Vec3d mDirection;
	public:

		///默认生成:
		///Ray3d(Origin = Vector3( 0 , 0 , 0 ) , Direction = Vector3( 0 , 1 , 0 ))
		Ray3d()
			:mOrigin(Vec3d::ZERO), mDirection(Vec3d::UNIT_Y) {}

		Ray3d(const Vec3d& origin, const Vec3d& direction)
			:mOrigin(origin), mDirection(direction) {}

		/// 设置原点.
		void setOrigin(const Vec3d& origin) {mOrigin = origin;} 

		/// 得到原点值.
		Vec3d getOrigin(void) const {return mOrigin;} 

		/// 设置方向
		void setDirection(const Vec3d& dir) {mDirection = dir;} 

		/// 得到方向向量.
		Vec3d getDirection(void) const {return mDirection;} 

		///得到光线上的一点.mOrigin为getPoint(0),指向的末端为getPoint(1).
		///光线上的范围[0-1].
		///注意,利用intersects测试的返回值再得到点的过程中,参数可能越界.
		///需要越界检查时,取消注释.
		Vec3d getPoint(float t) const 
		{ 
			//assert( (t <= 1) && (t >= 0) && "访问光线上的点越界" );
			return Vec3d(mOrigin + (mDirection * t));
		}

		/** Gets the position of a point t units along the ray. */
		Vec3d operator*(float t) const 
		{ 
			return getPoint(t);
		};

		inline String getDetails() const
		{
			std::ostringstream o;
			o << _T("Ray3d(Origin = ") << mOrigin.getDetails() <<
				_T(" , Direction = ") << 
				mDirection.getDetails() << _T(")");
			return o.str();
		}

		// 得到某一点在这条ray上的垂线相交点
		Vec3d getPerpendicularVertex( const Vec3d& point )
		{
			Vec3d normalize_dir = mDirection.normalisedCopy();

			float len = (float)normalize_dir.dotProduct( point - mOrigin );

			return  mOrigin + len * normalize_dir;
		}

		vgKernel::Ray getRayFloat() const
		{
			return vgKernel::Ray( mOrigin.getVec3Float() , mDirection.getVec3Float() );
		}
	};
	
	
}// end of namespace vgShape
	


#endif // end of __VGSHRAY3D_H__
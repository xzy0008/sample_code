


#ifndef __VGKPLANE_H__
#define __VGKPLANE_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkBox.h>


	
namespace vgKernel {


	/**
		@date 	2007/02/20  10:50	
		@author  xy
	
		@brief 	

			ƽ����.ͨ������Ax + By + Cz + D = 0 ����һ��ƽ��.����,
			A , B , C ������������ƽ���ϵķ�������.��Dֵ��ʾƽ���ԭ��ľ���.
		
			A plane is defined in 3D space by the equation
			Ax + By + Cz + D = 0
	

		@see    
	*/
	class  VGK_EXPORT Plane
	{
	public:

		Plane ();
		Plane (const Plane& rhs);

		///���캯��,����Ϊnormal����normalΪ�����ƶ��ľ���,ע������.
		Plane (const Vec3& rkNormal, float fConstant);
		Plane (const Vec3& rkNormal, const Vec3& rkPoint);
		Plane (const Vec3& rkPoint0, const Vec3& rkPoint1,
			const Vec3& rkPoint2);

		enum Side
		{
			NO_SIDE,		///��ʾ��ƽ����,��һ����AABBΪNULLʱ��ʾ�����κ�һ����.
			POSITIVE_SIDE,	///��ʾ������
			NEGATIVE_SIDE,	///��ʾ�ڸ���
			BOTH_SIDE		///��ʾ������2��,����AABB���.
		};

	public:	

		///ƽ��ķ�����.
		Vec3 _normal;
		///ƽ���ԭ��ľ���,����normal����ȷ��Ψһ��Plane
		float _distance;

	public:

		/// �õ�һ���������ƽ���λ��.����ΪSide
		Side getSide (const Vec3& rkPoint) const;

		/// �õ�һ����Χ�������ƽ���λ��.����ΪSide
		Side getSide (const Box& rkBox) const;

		/** Returns which side of the plane that the given box lies on.
		The box is defined as centre/half-size pairs for effectively.
		@param centre The centre of the box.
		@param halfSize The half-size of the box.
		@returns
		POSITIVE_SIDE if the box complete lies on the "positive side" of the plane,
		NEGATIVE_SIDE if the box complete lies on the "negative side" of the plane,
		and BOTH_SIDE if the box intersects the plane.
		*/
		Side getSide (const Vec3& centre, const Vec3& halfSize) const;

		///����α����,��ֵ�����ɸ�.��ֵ��ʾ��negative side.
		float getDistance (const Vec3& rkPoint) const;

		///ͨ��3�����ض���.
		/** Redefine this plane based on 3 points. */
		void redefine(const Vec3& rkPoint0, const Vec3& rkPoint1,
			const Vec3& rkPoint2);

		///ͨ��normal��һ�����ض���
		/** Redefine this plane based on a _normal and a point. */
		void redefine(const Vec3& rkNormal, const Vec3& rkPoint);

		///������plane�ϵ�ͶӰ.
		/** Project a vector onto the plane. 
		@remarks This gives you the element of the input vector that is perpendicular 
		to the _normal of the plane. You can get the element which is parallel
		to the _normal of the plane by subtracting the result of this method
		from the original vector, since parallel + perpendicular = original.
		@param v The input vector
		*/
		//Vec3 projectVector(const Vec3& v);

		float normalise(void);

		bool isFrontFacingTo(const Vec3& direction) const {
			double dot = _normal.dotProduct(direction);

			return (dot <= 0);
		}

		/// Comparison operator
		bool operator == (const Plane& rhs) const
		{
			return (rhs._distance == _distance && rhs._normal == _normal);
		}
		bool operator != (const Plane& rhs) const
		{
			return (rhs._distance != _distance && rhs._normal != _normal);
		}

		String getDetails()
		{
			std::ostringstream o;
			o << " Plane:( _normal: " <<  _normal.getDetails() << " , distance: " << _distance << " )";
			return o.str();
		}
	};
	
}// end of namespace vgKernel
	


#endif // end of __VGKPLANE_H__
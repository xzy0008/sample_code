#pragma once

#include <vgPhys/vgphDefinition.h>

#include <vgPhys/vgphRealityObject.h>
#include <vgKernel/vgkVec3.h>

#include <vgKernel/vgkBox.h>

namespace vgPhys
{
	class VGPH_EXPORT CollisionPacket {
	public:
		vgKernel::Vec3 eRadius; // ellipsoid radius

		// Information about the move being requested: (in R3)
		vgKernel::Vec3 R3Velocity;
		vgKernel::Vec3 R3Position;

		// Information about the move being requested: (in eSpace)
		vgKernel::Vec3 velocity;
		vgKernel::Vec3 normalizedVelocity;
		vgKernel::Vec3 basePoint;

		// Hit information
		bool foundCollision;
		double nearestDistance;
		vgKernel::Vec3 intersectionPoint;

		float  aheadRatio;  //add by ZhouZY

		// For slide plane
		vgKernel::Vec3 continueVelocity;
		vgKernel::Vec3 newPositon;
		
		vgKernel::Box  boundingBox;

	public:
		static float s_veryCloseDistance;
	}; 

	class VGPH_EXPORT CollisionObject : public vgPhys::RealityObject
	{
	public:
		static void CollisionObject::checkTriangle(CollisionPacket* colPackage,
										const vgKernel::Vec3& p1,const vgKernel::Vec3& p2,const vgKernel::Vec3& p3, 
										const vgKernel::Vec3& normal);

	public:
		CollisionObject() : RealityObject(VGPH_REALITY_TYPE_COLLISION)
		{
			m_enableCollision = true;
		}  

		~CollisionObject() {}

		// 实现碰撞检测，根据数据组织取出三角面片和法线，传给checkTriangle进行操作
		inline virtual void collisionDetection(CollisionPacket& collistionPacket) = 0;
	
		inline bool getCollisionEnable()
		{
			return m_enableCollision;
		}

		inline void setCollisionEnable(bool enable)
		{
			m_enableCollision = enable;
		}

	protected:

		bool m_enableCollision;

	};
}

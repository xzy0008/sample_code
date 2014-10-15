#pragma once

#include <vgPhys/vgphDefinition.h>


#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSingleton.h>
#include <vgPhys/vgphCollisionObject.h>

namespace vgPhys		
{
	class VGPH_EXPORT PhysMananger : public vgKernel::Singleton<PhysMananger>
	{
		friend class vgKernel::Singleton<PhysMananger>;
	private:
		PhysMananger()
			: Singleton<PhysMananger>( VGK_SIGNLETON_LEFE_PYHSMANAGER ) 
		{
			m_collisionDectectionOn = false;

			//edit by KingHJ @2010.2.27 参数修改，因为观察者模型的参数偏大
			m_eillipseVec.x = .20f;
			m_eillipseVec.y = 0.60f;
			m_eillipseVec.z = .20f;

			m_aheadRatio = 0.2f;
		} 

	public:
		~PhysMananger(){}

	public:

		virtual void reset(){};

		// 碰撞检测相关
		void setCollisionEnable(bool isEnable)
		{
			m_collisionDectectionOn = isEnable;
		}

		bool getCollisionEnable()
		{
			return m_collisionDectectionOn;	
		}

		void setEillipseVec(vgKernel::Vec3 newVec) { m_eillipseVec = newVec; }

		vgKernel::Vec3 getEillipseVec() { return m_eillipseVec; }

		void setAheadRatio( float ratio ) { m_aheadRatio = ratio; }

		float getAheadRatio() { return m_aheadRatio; }

		// 碰撞检测，输入参数为物体原点，物体运动方向，返回为检测后物体位置.
		vgKernel::Vec3 collisionWithCamera(vgKernel::Vec3 position, vgKernel::Vec3 direction, const vgKernel::Box& cameraBox);

		// 可扩展加入物体间的碰撞检测 collisionWithWorld

		// Renderer如果是一个CollisionObject，在初始化时加入
		void addCollisionObject(CollisionObject* pObject);

		// 删除物体时从Manager中去除
		void removeCollisionObject(CollisionObject *pObject);

	protected:

		virtual bool initialise()
		{
			return true;
		}

		virtual bool shutdown()
		{
			return true;
		}
		
	private:
		vgKernel::Vec3 PhysMananger::collideWithWorld(CollisionPacket& colPacket, const vgKernel::Vec3& pos,
			const vgKernel::Vec3& vel);

	private:
		std::vector<CollisionObject*> m_collisionObejctVec;
		
		vgKernel::Vec3 m_eillipseVec;

		// 用来设置碰撞检测交点提前量, 取值范围为[0.0,1.0] 
		// add by ZhouZY  2010-3-26  15:29
		float   m_aheadRatio;

		bool	m_collisionDectectionOn;
		int		m_collisionRecursionDepth;
	};
}

#include <vgStableHeaders.h>
#include <vgPhys/vgphPhysManager.h>
#include <vgKernel/vgkVec3.h>
#include <vgKernel/vgkPlane.h>
#include <vgKernel/vgkMath.h>
#include <vector>

namespace vgPhys
{ 

	using namespace vgKernel;
	void PhysMananger::addCollisionObject(CollisionObject* pObject)
	{
		if (find(m_collisionObejctVec.begin(), m_collisionObejctVec.end(), pObject) == m_collisionObejctVec.end())
		{
			m_collisionObejctVec.push_back(pObject);
		}
	}

	void PhysMananger::removeCollisionObject(CollisionObject *pObject)
	{
		std::vector<CollisionObject*>::iterator iter = find(m_collisionObejctVec.begin(), m_collisionObejctVec.end(), pObject) ;

		if (iter != m_collisionObejctVec.end())
		{
			// m_collisionObejctVec.erase(iter);
			*iter = NULL;
		}
	}

	vgKernel::Vec3 PhysMananger::collisionWithCamera(vgKernel::Vec3 position, vgKernel::Vec3 direction, const vgKernel::Box& cameraBox)
	{
		if (! m_collisionDectectionOn)
		{
			position += direction;

			return position;
		}

		CollisionPacket colPacket;

		colPacket.boundingBox = cameraBox;

		colPacket.eRadius = m_eillipseVec;

		colPacket.continueVelocity = Vec3(0,0,0);

		colPacket.foundCollision = false;

		colPacket.aheadRatio = m_aheadRatio;

		// Do collision detection:
		colPacket.R3Position = position;
		colPacket.R3Velocity = direction;
		// calculate position and velocity in eSpace
		Vec3 eSpacePosition = colPacket.R3Position/
			colPacket.eRadius;
		Vec3 eSpaceVelocity = colPacket.R3Velocity/
			colPacket.eRadius;

		// Iterate until we have our final position.
		m_collisionRecursionDepth = 0;

		Vec3 finalPosition = collideWithWorld(colPacket, eSpacePosition,
			eSpaceVelocity);

		// Convert final result back to R3:
		finalPosition = finalPosition*colPacket.eRadius;
		// 
		// 		// Move the entity (application specific function)
		// 		MoveTo(finalPosition);

		colPacket.newPositon = finalPosition;

		return colPacket.newPositon;
	}

	vgKernel::Vec3 PhysMananger::collideWithWorld(CollisionPacket& colPacket, const Vec3& pos,
		const Vec3& vel)
	{
		// TRACE(" %d recursion \n", m_collisionRecursionDepth);

		// All hard-coded distances in this function is
		// scaled to fit the setting above..
		float unitScale = 1;
		float veryCloseDistance = 0.005f * unitScale;
		// do we need to worry?
		if (m_collisionRecursionDepth>3)
			return pos;
		// Ok, we need to worry:
		colPacket.velocity = vel;
		colPacket.normalizedVelocity = vel;
		colPacket.normalizedVelocity.normalise();
		colPacket.basePoint = pos;
		colPacket.foundCollision = false;
		colPacket.continueVelocity = Vec3(0,0,0);

		// Check for collision (calls the collision routines)
		// Application specific!!
		// collisionDetection(colPacket);
		
		std::vector<CollisionObject*>::iterator iter = m_collisionObejctVec.begin();
		std::vector<CollisionObject*>::iterator end_iter = m_collisionObejctVec.end();

		colPacket.nearestDistance = FLT_MAX;

		while ( iter != end_iter )
		{
			if ( (*iter) != NULL )
			{
				(*iter)->collisionDetection(colPacket);
			}

			iter ++;
		}
		
		// If no collision we just move along the velocity
		if (colPacket.foundCollision == false) {
			return pos + vel;
		}

		vgKernel::Vec3 destinationPoint = colPacket.basePoint + colPacket.velocity;
		vgKernel::Vec3 newBasePoint = colPacket.basePoint;

		if (colPacket.nearestDistance>=CollisionPacket::s_veryCloseDistance + 1)
		{
			Vec3 V = vel;
			V.setLength(colPacket.nearestDistance-CollisionPacket::s_veryCloseDistance-1);
			newBasePoint = colPacket.basePoint + V;
			// Adjust polygon intersection point (so sliding
			// plane will be unaffected by the fact that we
			// move slightly less than collision tells us)
			V.normalise();
			colPacket.intersectionPoint -= (CollisionPacket::s_veryCloseDistance) * V;
		}

		// Determine the sliding plane
		Vec3 slidePlaneOrigin = colPacket.intersectionPoint;
		Vec3 slidePlaneNormal = newBasePoint-colPacket.intersectionPoint;
		slidePlaneNormal.normalise();
		vgKernel::Plane slidingPlane(slidePlaneNormal, slidePlaneOrigin);
		// Again, sorry about formatting.. but look carefully ;)
		Vec3 newDestinationPoint = destinationPoint - slidingPlane.getDistance(destinationPoint) * slidePlaneNormal;
		// Generate the slide vector, which will become our new
		// velocity vector for the next iteration
		Vec3 newVelocityVector = newDestinationPoint - colPacket.intersectionPoint;
		// Recurse:
		// dont recurse if the new velocity is very small
		if (newVelocityVector.length() < CollisionPacket::s_veryCloseDistance) {
			TRACE(" Len < closeDistance return \n ");
			return newBasePoint;
		}
		m_collisionRecursionDepth++;

		// m_colPacket.continueVelocity = newVelocityVector * m_colPacket.eRadius;

		return collideWithWorld(colPacket, newBasePoint,newVelocityVector);
	}
}
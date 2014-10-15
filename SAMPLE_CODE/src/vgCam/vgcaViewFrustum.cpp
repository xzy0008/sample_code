


#include <vgStableHeaders.h>
#include <vgCam/vgcaViewFrustum.h>

#include <vgCam/vgcaCamManager.h>


#undef PI
namespace vgCam {
	

	//----------------------------------------------------------------
	void ViewFrustum::calculateInEveryFrame()
	{
		if ( _needUpdate == false )
		{
			return;
		}

// 		glGetFloatv( GL_PROJECTION_MATRIX, proj );
// 		glGetFloatv( GL_MODELVIEW_MATRIX, modl );

		glGetFloatv(GL_PROJECTION_MATRIX, proj);
		glGetFloatv(GL_MODELVIEW_MATRIX, m_preModl._m);

		// 根据视点和观察方向向后拉视景体，将视点包围盒包进视锥裁剪
		vgKernel::Vec3 dir = vgCam::CamManager::getSingleton().getCurrentDirection();

		dir.normalise();

		float dis = m_collisionBox.getSize().length();


		if (vgCam::CamManager::getSingleton().getAspectRatio() < 1)
		{
			dis = dis / vgCam::CamManager::getSingleton().getAspectRatio();
		}

		float fov = vgCam::CamManager::getSingleton().getFov();

		dis = dis / tan(fov / 2 / 180 * vgKernel::Math::PI);
		dis += m_collisionBox.getSize().length();

		vgKernel::Math::createTranslationMatrix(dir.x*dis, dir.y*dis, dir.z*dis, m_transMat);
		vgKernel::Math::multiplyMatrix(m_preModl, m_transMat, m_modl);

		for (int i=0; i<16; i++)
		{
			modl[i] = m_modl._m[i];
		}

		clip[ 0] = modl[ 0] * proj[ 0] + modl[ 1] * proj[ 4] + modl[ 2] * proj[ 8] + modl[ 3] * proj[12];
		clip[ 1] = modl[ 0] * proj[ 1] + modl[ 1] * proj[ 5] + modl[ 2] * proj[ 9] + modl[ 3] * proj[13];
		clip[ 2] = modl[ 0] * proj[ 2] + modl[ 1] * proj[ 6] + modl[ 2] * proj[10] + modl[ 3] * proj[14];
		clip[ 3] = modl[ 0] * proj[ 3] + modl[ 1] * proj[ 7] + modl[ 2] * proj[11] + modl[ 3] * proj[15];

		clip[ 4] = modl[ 4] * proj[ 0] + modl[ 5] * proj[ 4] + modl[ 6] * proj[ 8] + modl[ 7] * proj[12];
		clip[ 5] = modl[ 4] * proj[ 1] + modl[ 5] * proj[ 5] + modl[ 6] * proj[ 9] + modl[ 7] * proj[13];
		clip[ 6] = modl[ 4] * proj[ 2] + modl[ 5] * proj[ 6] + modl[ 6] * proj[10] + modl[ 7] * proj[14];
		clip[ 7] = modl[ 4] * proj[ 3] + modl[ 5] * proj[ 7] + modl[ 6] * proj[11] + modl[ 7] * proj[15];

		clip[ 8] = modl[ 8] * proj[ 0] + modl[ 9] * proj[ 4] + modl[10] * proj[ 8] + modl[11] * proj[12];
		clip[ 9] = modl[ 8] * proj[ 1] + modl[ 9] * proj[ 5] + modl[10] * proj[ 9] + modl[11] * proj[13];
		clip[10] = modl[ 8] * proj[ 2] + modl[ 9] * proj[ 6] + modl[10] * proj[10] + modl[11] * proj[14];
		clip[11] = modl[ 8] * proj[ 3] + modl[ 9] * proj[ 7] + modl[10] * proj[11] + modl[11] * proj[15];

		clip[12] = modl[12] * proj[ 0] + modl[13] * proj[ 4] + modl[14] * proj[ 8] + modl[15] * proj[12];
		clip[13] = modl[12] * proj[ 1] + modl[13] * proj[ 5] + modl[14] * proj[ 9] + modl[15] * proj[13];
		clip[14] = modl[12] * proj[ 2] + modl[13] * proj[ 6] + modl[14] * proj[10] + modl[15] * proj[14];
		clip[15] = modl[12] * proj[ 3] + modl[13] * proj[ 7] + modl[14] * proj[11] + modl[15] * proj[15];

		// This will extract the RIGHT side of the frustum
		m_Frustum[RIGHT][A] = clip[ 3] - clip[ 0];
		m_Frustum[RIGHT][B] = clip[ 7] - clip[ 4];
		m_Frustum[RIGHT][C] = clip[11] - clip[ 8];
		m_Frustum[RIGHT][D] = clip[15] - clip[12];

		// Now that we have a normal (A,B,C) and a distance (D) to the plane,
		// we want to normalize that normal and distance.

		// Normalize the RIGHT side
		normalizePlane(m_Frustum, RIGHT);

		// This will extract the LEFT side of the frustum
		m_Frustum[LEFT][A] = clip[ 3] + clip[ 0];
		m_Frustum[LEFT][B] = clip[ 7] + clip[ 4];
		m_Frustum[LEFT][C] = clip[11] + clip[ 8];
		m_Frustum[LEFT][D] = clip[15] + clip[12];

		// Normalize the LEFT side
		normalizePlane(m_Frustum, LEFT);

		// This will extract the BOTTOM side of the frustum
		m_Frustum[BOTTOM][A] = clip[ 3] + clip[ 1];
		m_Frustum[BOTTOM][B] = clip[ 7] + clip[ 5];
		m_Frustum[BOTTOM][C] = clip[11] + clip[ 9];
		m_Frustum[BOTTOM][D] = clip[15] + clip[13];

		// Normalize the BOTTOM side
		normalizePlane(m_Frustum, BOTTOM);

		// This will extract the TOP side of the frustum
		m_Frustum[TOP][A] = clip[ 3] - clip[ 1];
		m_Frustum[TOP][B] = clip[ 7] - clip[ 5];
		m_Frustum[TOP][C] = clip[11] - clip[ 9];
		m_Frustum[TOP][D] = clip[15] - clip[13];

		// Normalize the TOP side
		normalizePlane(m_Frustum, TOP);

		// This will extract the BACK side of the frustum
		m_Frustum[BACK][A] = clip[ 3] - clip[ 2];
		m_Frustum[BACK][B] = clip[ 7] - clip[ 6];
		m_Frustum[BACK][C] = clip[11] - clip[10];
		m_Frustum[BACK][D] = clip[15] - clip[14];

		// Normalize the BACK side
		normalizePlane(m_Frustum, BACK);

		// This will extract the FRONT side of the frustum
		m_Frustum[FRONT][A] = clip[ 3] + clip[ 2];
		m_Frustum[FRONT][B] = clip[ 7] + clip[ 6];
		m_Frustum[FRONT][C] = clip[11] + clip[10];
		m_Frustum[FRONT][D] = clip[15] + clip[14];

		// Normalize the FRONT side
		normalizePlane(m_Frustum, FRONT);

		_needUpdate = false;
	}
	//----------------------------------------------------------------
	void ViewFrustum::normalizePlane( float frustum[6][4], int side )
	{
		// Here we calculate the magnitude of the normal to the plane (point A B C)
		// Remember that (A, B, C) is that same thing as the normal's (X, Y, Z).
		// To calculate magnitude you use the equation:  magnitude = sqrt( x^2 + y^2 + z^2)
		float magnitude = (float)sqrt( frustum[side][A] * frustum[side][A] + 
			frustum[side][B] * frustum[side][B] + 
			frustum[side][C] * frustum[side][C] );

		// Then we divide the plane's values by it's magnitude.
		// This makes it easier to work with.
		frustum[side][A] /= magnitude;
		frustum[side][B] /= magnitude;
		frustum[side][C] /= magnitude;
		frustum[side][D] /= magnitude;
	}
	//----------------------------------------------------------------
	bool ViewFrustum::testBoxInFrustum( const Box& boundary )
	{
		const Vec3& midvec = boundary.getCenter();

		const float &x = midvec.x;
		const float &y = midvec.y;
		const float &z = midvec.z;

		//float y = (boundary.getMaximum().y+boundary.getMinimum().y)/2.0;
		//float z = (boundary.getMaximum().z+boundary.getMinimum().z)/2.0;

		const Vec3& sizevec = boundary.getSize();

		const float &sizeX = sizevec.x;
		const float &sizeY = sizevec.y;
		const float &sizeZ = sizevec.z;

		for(int i = 0; i < 6; i++ )
		{
			if(m_Frustum[i][A] * (x - sizeX) + m_Frustum[i][B] * (y - sizeY) + m_Frustum[i][C] * (z - sizeZ) + m_Frustum[i][D] > 0)
				continue;
			if(m_Frustum[i][A] * (x + sizeX) + m_Frustum[i][B] * (y - sizeY) + m_Frustum[i][C] * (z - sizeZ) + m_Frustum[i][D] > 0)
				continue;
			if(m_Frustum[i][A] * (x - sizeX) + m_Frustum[i][B] * (y + sizeY) + m_Frustum[i][C] * (z - sizeZ) + m_Frustum[i][D] > 0)
				continue;
			if(m_Frustum[i][A] * (x + sizeX) + m_Frustum[i][B] * (y + sizeY) + m_Frustum[i][C] * (z - sizeZ) + m_Frustum[i][D] > 0)
				continue;
			if(m_Frustum[i][A] * (x - sizeX) + m_Frustum[i][B] * (y - sizeY) + m_Frustum[i][C] * (z + sizeZ) + m_Frustum[i][D] > 0)
				continue;
			if(m_Frustum[i][A] * (x + sizeX) + m_Frustum[i][B] * (y - sizeY) + m_Frustum[i][C] * (z + sizeZ) + m_Frustum[i][D] > 0)
				continue;
			if(m_Frustum[i][A] * (x - sizeX) + m_Frustum[i][B] * (y + sizeY) + m_Frustum[i][C] * (z + sizeZ) + m_Frustum[i][D] > 0)
				continue;
			if(m_Frustum[i][A] * (x + sizeX) + m_Frustum[i][B] * (y + sizeY) + m_Frustum[i][C] * (z + sizeZ) + m_Frustum[i][D] > 0)
				continue;

			// If we get here, it isn't in the frustum
			return false;
		}

		return true;
	}

	bool ViewFrustum::testBoxInFrustum( const float& x, const float& y, const float& z, const float& size )
	{
		for(int i = 0; i < 4; i++ )
		{

			if(m_Frustum[i][A] * (x - size) + m_Frustum[i][B] * (y) + m_Frustum[i][C] * (z - size) + m_Frustum[i][D] > 0)
				continue;
			if(m_Frustum[i][A] * (x + size) + m_Frustum[i][B] * (y) + m_Frustum[i][C] * (z - size) + m_Frustum[i][D] > 0)
				continue;
			if(m_Frustum[i][A] * (x - size) + m_Frustum[i][B] * (y) + m_Frustum[i][C] * (z + size) + m_Frustum[i][D] > 0)
				continue;
			if(m_Frustum[i][A] * (x + size) + m_Frustum[i][B] * (y) + m_Frustum[i][C] * (z + size) + m_Frustum[i][D] > 0)
				continue;
			// If we get here, it isn't in the frustum
			return false;
		}

		return true;
	}
	//----------------------------------------------------------------
	//bool ViewFrustum::testBoxInFrustum(  vgMath::BoundingBox& boundary )
	//{
	//	vgMath::Vector3& midvec = boundary.getCenter();

	//	const float &x = midvec.x;
	//	const float &y = midvec.y;
	//	const float &z = midvec.z;

	//	//float y = (boundary.getMaximum().y+boundary.getMinimum().y)/2.0;
	//	//float z = (boundary.getMaximum().z+boundary.getMinimum().z)/2.0;

	//	vgMath::Vector3& sizevec = boundary.getSize();

	//	const float &sizeX = sizevec.x;
	//	const float &sizeY = sizevec.y;
	//	const float &sizeZ = sizevec.z;

	//	for(int i = 0; i < 6; i++ )
	//	{
	//		if(m_Frustum[i][A] * (x - sizeX) + m_Frustum[i][B] * (y - sizeY) + m_Frustum[i][C] * (z - sizeZ) + m_Frustum[i][D] > 0)
	//			continue;
	//		if(m_Frustum[i][A] * (x + sizeX) + m_Frustum[i][B] * (y - sizeY) + m_Frustum[i][C] * (z - sizeZ) + m_Frustum[i][D] > 0)
	//			continue;
	//		if(m_Frustum[i][A] * (x - sizeX) + m_Frustum[i][B] * (y + sizeY) + m_Frustum[i][C] * (z - sizeZ) + m_Frustum[i][D] > 0)
	//			continue;
	//		if(m_Frustum[i][A] * (x + sizeX) + m_Frustum[i][B] * (y + sizeY) + m_Frustum[i][C] * (z - sizeZ) + m_Frustum[i][D] > 0)
	//			continue;
	//		if(m_Frustum[i][A] * (x - sizeX) + m_Frustum[i][B] * (y - sizeY) + m_Frustum[i][C] * (z + sizeZ) + m_Frustum[i][D] > 0)
	//			continue;
	//		if(m_Frustum[i][A] * (x + sizeX) + m_Frustum[i][B] * (y - sizeY) + m_Frustum[i][C] * (z + sizeZ) + m_Frustum[i][D] > 0)
	//			continue;
	//		if(m_Frustum[i][A] * (x - sizeX) + m_Frustum[i][B] * (y + sizeY) + m_Frustum[i][C] * (z + sizeZ) + m_Frustum[i][D] > 0)
	//			continue;
	//		if(m_Frustum[i][A] * (x + sizeX) + m_Frustum[i][B] * (y + sizeY) + m_Frustum[i][C] * (z + sizeZ) + m_Frustum[i][D] > 0)
	//			continue;

	//		// If we get here, it isn't in the frustum
	//		return false;
	//	}

	//	return true;
	//}
	bool ViewFrustum::testBoxIncludedInFrustum( const Box& boundary )
	{
		const Vec3& midvec = boundary.getCenter();

		const float &x = midvec.x;
		const float &y = midvec.y;
		const float &z = midvec.z;

		//float y = (boundary.getMaximum().y+boundary.getMinimum().y)/2.0;
		//float z = (boundary.getMaximum().z+boundary.getMinimum().z)/2.0;

		const Vec3& sizevec = boundary.getSize();

		const float &sizeX = sizevec.x;
		const float &sizeY = sizevec.y;
		const float &sizeZ = sizevec.z;

		for(int i = 0; i < 6; i++ )
		{
			if(
				(m_Frustum[i][A] * (x - sizeX) + m_Frustum[i][B] * (y - sizeY) + m_Frustum[i][C] * (z - sizeZ) + m_Frustum[i][D] < 0)
				||(m_Frustum[i][A] * (x + sizeX) + m_Frustum[i][B] * (y - sizeY) + m_Frustum[i][C] * (z - sizeZ) + m_Frustum[i][D] < 0)
				||(m_Frustum[i][A] * (x - sizeX) + m_Frustum[i][B] * (y + sizeY) + m_Frustum[i][C] * (z - sizeZ) + m_Frustum[i][D] < 0)
				||(m_Frustum[i][A] * (x + sizeX) + m_Frustum[i][B] * (y + sizeY) + m_Frustum[i][C] * (z - sizeZ) + m_Frustum[i][D] < 0)
				||(m_Frustum[i][A] * (x - sizeX) + m_Frustum[i][B] * (y - sizeY) + m_Frustum[i][C] * (z + sizeZ) + m_Frustum[i][D] < 0)
				||(m_Frustum[i][A] * (x + sizeX) + m_Frustum[i][B] * (y - sizeY) + m_Frustum[i][C] * (z + sizeZ) + m_Frustum[i][D] < 0)
				||(m_Frustum[i][A] * (x - sizeX) + m_Frustum[i][B] * (y + sizeY) + m_Frustum[i][C] * (z + sizeZ) + m_Frustum[i][D] < 0)
				||(m_Frustum[i][A] * (x + sizeX) + m_Frustum[i][B] * (y + sizeY) + m_Frustum[i][C] * (z + sizeZ) + m_Frustum[i][D] < 0)
				)// 如果包围盒八个点中的任意一个点 在 视景体六个面中的任意一个面 之外，判定包围盒没有完全位于视景体

				// If we get here, it isn't included in the frustum
				return false;
		}

		return true;
	}
	//bool ViewFrustum::testBoxIncludedInFrustum(  vgMath::BoundingBox& boundary )
	//{
	//	vgMath::Vector3& midvec = boundary.getCenter();

	//	const float &x = midvec.x;
	//	const float &y = midvec.y;
	//	const float &z = midvec.z;

	//	//float y = (boundary.getMaximum().y+boundary.getMinimum().y)/2.0;
	//	//float z = (boundary.getMaximum().z+boundary.getMinimum().z)/2.0;

	//	vgMath::Vector3& sizevec = boundary.getSize();

	//	const float &sizeX = sizevec.x;
	//	const float &sizeY = sizevec.y;
	//	const float &sizeZ = sizevec.z;

	//	for(int i = 0; i < 6; i++ )
	//	{
	//		if(
	//			(m_Frustum[i][A] * (x - sizeX) + m_Frustum[i][B] * (y - sizeY) + m_Frustum[i][C] * (z - sizeZ) + m_Frustum[i][D] < 0)
	//			||(m_Frustum[i][A] * (x + sizeX) + m_Frustum[i][B] * (y - sizeY) + m_Frustum[i][C] * (z - sizeZ) + m_Frustum[i][D] < 0)
	//			||(m_Frustum[i][A] * (x - sizeX) + m_Frustum[i][B] * (y + sizeY) + m_Frustum[i][C] * (z - sizeZ) + m_Frustum[i][D] < 0)
	//			||(m_Frustum[i][A] * (x + sizeX) + m_Frustum[i][B] * (y + sizeY) + m_Frustum[i][C] * (z - sizeZ) + m_Frustum[i][D] < 0)
	//			||(m_Frustum[i][A] * (x - sizeX) + m_Frustum[i][B] * (y - sizeY) + m_Frustum[i][C] * (z + sizeZ) + m_Frustum[i][D] < 0)
	//			||(m_Frustum[i][A] * (x + sizeX) + m_Frustum[i][B] * (y - sizeY) + m_Frustum[i][C] * (z + sizeZ) + m_Frustum[i][D] < 0)
	//			||(m_Frustum[i][A] * (x - sizeX) + m_Frustum[i][B] * (y + sizeY) + m_Frustum[i][C] * (z + sizeZ) + m_Frustum[i][D] < 0)
	//			||(m_Frustum[i][A] * (x + sizeX) + m_Frustum[i][B] * (y + sizeY) + m_Frustum[i][C] * (z + sizeZ) + m_Frustum[i][D] < 0)
	//			)// 如果包围盒八个点中的任意一个点 在 视景体六个面中的任意一个面 之外，判定包围盒没有完全位于视景体

	//			// If we get here, it isn't included in the frustum
	//			return false;
	//	}

	//	return true;
	//}
	//----------------------------------------------------------------

	// 给相机创建一个包围盒
	void ViewFrustum::updateCameraBox()
	{
		vgKernel::Vec3 center = vgCam::CamManager::getSingleton().getCurrentPosition();

		float v = vgCam::CamManager::getSingleton().getForwardVelocity();

		// 防止一步进入物体内卡死，多设置一个增量
		float dist = 10.f;

		m_collisionBoxLen = v + dist;
		m_collisionBoxWidth = v + dist;
		m_collisionBoxHeight = v + dist;

		m_collisionBox._maxVertex = center + vgKernel::Vec3(m_collisionBoxLen, m_collisionBoxHeight, m_collisionBoxWidth);
		m_collisionBox._minVertex = center - vgKernel::Vec3(m_collisionBoxLen, m_collisionBoxHeight, m_collisionBoxWidth);

	}

}// end of namespace vgCam

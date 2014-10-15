//----------------------------------------------------------------
inline void Frustum::updateFrustumPlanesImpl()
{
	/// 从MVP矩阵中得到6个面的值,具体参见Game Programming Gems 4,128页.
	// -------------------------
	// Update the frustum planes
	// -------------------------

	Matrix4 combo;
	if ( mUseCustomMatrix )
	{
		combo = mProjectMatrix * mCustomModelMatrix;
	}
	else
	{
		combo = mProjectMatrix * mModelViewMatrix;
	}
	

	mFrustumPlanes[FRUSTUM_PLANE_LEFT].normal.x = combo[3][0] + combo[0][0];
	mFrustumPlanes[FRUSTUM_PLANE_LEFT].normal.y = combo[3][1] + combo[0][1];
	mFrustumPlanes[FRUSTUM_PLANE_LEFT].normal.z = combo[3][2] + combo[0][2];
	mFrustumPlanes[FRUSTUM_PLANE_LEFT].d = combo[3][3] + combo[0][3];

	mFrustumPlanes[FRUSTUM_PLANE_RIGHT].normal.x = combo[3][0] - combo[0][0];
	mFrustumPlanes[FRUSTUM_PLANE_RIGHT].normal.y = combo[3][1] - combo[0][1];
	mFrustumPlanes[FRUSTUM_PLANE_RIGHT].normal.z = combo[3][2] - combo[0][2];
	mFrustumPlanes[FRUSTUM_PLANE_RIGHT].d = combo[3][3] - combo[0][3];

	mFrustumPlanes[FRUSTUM_PLANE_TOP].normal.x = combo[3][0] - combo[1][0];
	mFrustumPlanes[FRUSTUM_PLANE_TOP].normal.y = combo[3][1] - combo[1][1];
	mFrustumPlanes[FRUSTUM_PLANE_TOP].normal.z = combo[3][2] - combo[1][2];
	mFrustumPlanes[FRUSTUM_PLANE_TOP].d = combo[3][3] - combo[1][3];

	mFrustumPlanes[FRUSTUM_PLANE_BOTTOM].normal.x = combo[3][0] + combo[1][0];
	mFrustumPlanes[FRUSTUM_PLANE_BOTTOM].normal.y = combo[3][1] + combo[1][1];
	mFrustumPlanes[FRUSTUM_PLANE_BOTTOM].normal.z = combo[3][2] + combo[1][2];
	mFrustumPlanes[FRUSTUM_PLANE_BOTTOM].d = combo[3][3] + combo[1][3];

	mFrustumPlanes[FRUSTUM_PLANE_NEAR].normal.x = combo[3][0] + combo[2][0];
	mFrustumPlanes[FRUSTUM_PLANE_NEAR].normal.y = combo[3][1] + combo[2][1];
	mFrustumPlanes[FRUSTUM_PLANE_NEAR].normal.z = combo[3][2] + combo[2][2];
	mFrustumPlanes[FRUSTUM_PLANE_NEAR].d = combo[3][3] + combo[2][3];

	mFrustumPlanes[FRUSTUM_PLANE_FAR].normal.x = combo[3][0] - combo[2][0];
	mFrustumPlanes[FRUSTUM_PLANE_FAR].normal.y = combo[3][1] - combo[2][1];
	mFrustumPlanes[FRUSTUM_PLANE_FAR].normal.z = combo[3][2] - combo[2][2];
	mFrustumPlanes[FRUSTUM_PLANE_FAR].d = combo[3][3] - combo[2][3];

	// Renormalise any normals which were not unit length
	for(int i=0; i<6; i++ ) 
	{
		float length = mFrustumPlanes[i].normal.normalise();
		mFrustumPlanes[i].d /= length;
	}

	//////////////////////////////////////////////////////////////////////////

	//mExtendPlanes[0].normal = mFrustumPlanes[FRUSTUM_PLANE_LEFT].normal;

	//Vector3 eyePos = Math::intersect( mFrustumPlanes[FRUSTUM_PLANE_LEFT] ,
	//	mFrustumPlanes[FRUSTUM_PLANE_RIGHT] ,
	//	mFrustumPlanes[FRUSTUM_PLANE_TOP] );

	//Quaternion  q( 3.1415f/8 , Vector3::UNIT_Y );

	//mExtendPlanes[0].normal = q * ( mFrustumPlanes[FRUSTUM_PLANE_LEFT].normal ;

	//mExtendPlanes[0].d = mFrustumPlanes[FRUSTUM_PLANE_LEFT].d ;
	//

	//q.w = - q.w;

	//mExtendPlanes[1].normal = q * mFrustumPlanes[FRUSTUM_PLANE_RIGHT].normal ;

	//mExtendPlanes[1].d = mFrustumPlanes[FRUSTUM_PLANE_RIGHT].d ;

	if ( mUseCustomMatrix )
	{
		mFrustumPlanes[FRUSTUM_PLANE_FAR].d = -mFrustumPlanes[FRUSTUM_PLANE_NEAR].d + mFarDist;
	}
	
	//////////////////////////////////////////////////////////////////////////


	mRecalcFrustumPlanes = false;

}

//----------------------------------------------------------------
inline void Frustum::calcProjectionParameters( Real& left, Real& right, 
									   Real& bottom, Real& top ) const
{
	// Calculate general projection parameters

	Radian thetaY (mFOVy * 0.5f);
	Real tanThetaY = Math::Tan(thetaY);
	Real tanThetaX = tanThetaY * mAspect;

	// Unknow how to apply frustum offset to orthographic camera, just ignore here
	Real nearFocal = (mProjType == PT_PERSPECTIVE) ? mNearDist / mFocalLength : 0;
	Real nearOffsetX = 0;
	Real nearOffsetY = 0;
	Real half_w = tanThetaX * mNearDist;
	Real half_h = tanThetaY * mNearDist;

	left   = - half_w + nearOffsetX;
	right  = + half_w + nearOffsetX;
	bottom = - half_h + nearOffsetY;
	top    = + half_h + nearOffsetY;

}
//----------------------------------------------------------------
inline void Frustum::updateWorldSpaceCornersImpl()
{

	Matrix4 eyeToWorld;
	if ( mUseCustomMatrix )
	{
		eyeToWorld = mCustomModelMatrix.inverseAffine();
	}
	else
	{
		eyeToWorld = this->mModelViewMatrix.inverseAffine();
	}


	//Matrix4 eyeToWorld = this->mModelViewMatrix.inverseAffine();

	// Note: Even though we can dealing with general projection matrix here,
	//       but because it's incompatibly with infinite far plane, thus, we
	//       still need to working with projection parameters.

	// Calc near plane corners
	Real nearLeft, nearRight, nearBottom, nearTop;
	calcProjectionParameters(nearLeft, nearRight, nearBottom, nearTop);

	// Treat infinite fardist as some arbitrary far value
	Real farDist = (mFarDist == 0) ? 100000 : mFarDist;

	// Calc far palne corners
	Real radio = mProjType == PT_PERSPECTIVE ? farDist / mNearDist : 1;
	Real farLeft = nearLeft * radio;
	Real farRight = nearRight * radio;
	Real farBottom = nearBottom * radio;
	Real farTop = nearTop * radio;

	// near
	mWorldSpaceCorners[0] = eyeToWorld.transformAffine(Vector3(nearRight, nearTop,    -mNearDist));
	mWorldSpaceCorners[1] = eyeToWorld.transformAffine(Vector3(nearLeft,  nearTop,    -mNearDist));
	mWorldSpaceCorners[2] = eyeToWorld.transformAffine(Vector3(nearLeft,  nearBottom, -mNearDist));
	mWorldSpaceCorners[3] = eyeToWorld.transformAffine(Vector3(nearRight, nearBottom, -mNearDist));
	// far
	mWorldSpaceCorners[4] = eyeToWorld.transformAffine(Vector3(farRight,  farTop,     -farDist));
	mWorldSpaceCorners[5] = eyeToWorld.transformAffine(Vector3(farLeft,   farTop,     -farDist));
	mWorldSpaceCorners[6] = eyeToWorld.transformAffine(Vector3(farLeft,   farBottom,  -farDist));
	mWorldSpaceCorners[7] = eyeToWorld.transformAffine(Vector3(farRight,  farBottom,  -farDist));

	const Plane& p0 = mFrustumPlanes[0];
	const Plane& p1 = mFrustumPlanes[1];
	const Plane& p2 = mFrustumPlanes[2];
	const Plane& p3 = mFrustumPlanes[3];
	const Plane& p4 = mFrustumPlanes[4];
	const Plane& p5 = mFrustumPlanes[5];

	const Plane& e0 = mExtendPlanes[0];
	const Plane& e1 = mExtendPlanes[1];

	// near
	mWorldSpaceCorners2[0] =  Math::intersect( p0 , p2 , p4 );
	mWorldSpaceCorners2[1] =  Math::intersect( p0 , p2 , p5 );
	mWorldSpaceCorners2[2] =  Math::intersect( p0 , p3 , p4 );
	mWorldSpaceCorners2[3] =  Math::intersect( p0 , p3 , p5 );
	mWorldSpaceCorners2[4] =  Math::intersect( p1 , p2 , p4 );
	mWorldSpaceCorners2[5] =  Math::intersect( p1 , p2 , p5 );
	mWorldSpaceCorners2[6] =  Math::intersect( p1 , p3 , p4 );
	mWorldSpaceCorners2[7] =  Math::intersect( p1 , p3 , p5 );
	

	mWorldSpaceCorners2[8] =  Math::intersect( p1 , p4 , e0 );
	mWorldSpaceCorners2[9] =  Math::intersect( p1 , p4 , e1 );
	mWorldSpaceCorners2[10] =  Math::intersect( p1 , p5 , e0 );
	mWorldSpaceCorners2[11] =  Math::intersect( p1 , p5 , e1 );


	mRecalcWorldSpaceCorners = false;
}

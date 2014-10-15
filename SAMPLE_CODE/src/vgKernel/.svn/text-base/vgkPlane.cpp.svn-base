


#include <vgStableHeaders.h>
#include <vgKernel/vgkPlane.h>


namespace vgKernel {
	

	//-----------------------------------------------------------------------
	Plane::Plane ()
	{
		_normal = Vec3::ZERO;
		_distance = 0.0;
	}
	//-----------------------------------------------------------------------
	Plane::Plane (const Plane& rhs)
	{
		_normal = rhs._normal;
		_distance = rhs._distance;
	}
	//-----------------------------------------------------------------------
	Plane::Plane (const Vec3& rkNormal, float fConstant)
	{
		_normal = rkNormal;
		_distance = -fConstant;
	}
	//-----------------------------------------------------------------------
	Plane::Plane (const Vec3& rkNormal, const Vec3& rkPoint)
	{
		redefine(rkNormal, rkPoint);
	}
	//-----------------------------------------------------------------------
	Plane::Plane (const Vec3& rkPoint0, const Vec3& rkPoint1,
		const Vec3& rkPoint2)
	{
		redefine(rkPoint0, rkPoint1, rkPoint2);
	}
	//-----------------------------------------------------------------------
	float Plane::getDistance (const Vec3& rkPoint) const
	{
		return _normal.dotProduct(rkPoint) + _distance;
	}
	//-----------------------------------------------------------------------
	Plane::Side Plane::getSide (const Vec3& rkPoint) const
	{
		float fDistance = getDistance(rkPoint);

		if ( fDistance < 0.0 )
			return Plane::NEGATIVE_SIDE;

		if ( fDistance > 0.0 )
			return Plane::POSITIVE_SIDE;

		return Plane::NO_SIDE;
	}


	//-----------------------------------------------------------------------
	Plane::Side Plane::getSide (const Box& box) const
	{
		return getSide(box.getCenter(), box.getHalfSize());
	}
	//-----------------------------------------------------------------------
	Plane::Side Plane::getSide (const Vec3& centre, const Vec3& halfSize) const
	{
		// Calculate the distance between box centre and the plane
		float dist = getDistance(centre);

		// Calculate the maximise allows absolute distance for
		// the distance between box centre and plane
		float maxAbsDist = _normal.absDotProduct(halfSize);

		if (dist < -maxAbsDist)
			return Plane::NEGATIVE_SIDE;

		if (dist > +maxAbsDist)
			return Plane::POSITIVE_SIDE;

		return Plane::BOTH_SIDE;
	}
	//-----------------------------------------------------------------------
	void Plane::redefine(const Vec3& rkPoint0, const Vec3& rkPoint1,
		const Vec3& rkPoint2)
	{
		Vec3 kEdge1 = rkPoint1 - rkPoint0;
		Vec3 kEdge2 = rkPoint2 - rkPoint0;
		_normal = kEdge1.crossProduct(kEdge2);
		_normal.normalise();
		_distance = -_normal.dotProduct(rkPoint0);	///点乘,得到在法线上的投影,即为距离
	}
	//-----------------------------------------------------------------------
	void Plane::redefine(const Vec3& rkNormal, const Vec3& rkPoint)
	{
		_normal = rkNormal;
		_distance = -rkNormal.dotProduct(rkPoint);
	}
	//-----------------------------------------------------------------------
	//Vec3 Plane::projectVector(const Vec3& p)
	//{
	//	// We know plane _normal is unit length, so use simple method
	//	Mat4 xform;
	//	xform[0][0] = _normal.x * _normal.x - 1.0f;
	//	xform[0][1] = _normal.x * _normal.y;
	//	xform[0][2] = _normal.x * _normal.z;
	//	xform[1][0] = _normal.y * _normal.x;
	//	xform[1][1] = _normal.y * _normal.y - 1.0f;
	//	xform[1][2] = _normal.y * _normal.z;
	//	xform[2][0] = _normal.z * _normal.x;
	//	xform[2][1] = _normal.z * _normal.y;
	//	xform[2][2] = _normal.z * _normal.z - 1.0f;
	//	return xform * p;

	//}
	//-----------------------------------------------------------------------
	float Plane::normalise(void)
	{
		float fLength = _normal.length();

		// Will also work for zero-sized vectors, but will change nothing
		if (fLength > 1e-08f)
		{
			float fInvLength = 1.0f / fLength;
			_normal *= fInvLength;
			_distance *= fInvLength;
		}

		return fLength;
	}
	//-----------------------------------------------------------------------


	
	
}// end of namespace vgKernel





#include <vgStableHeaders.h>
#include <vgKernel/vgkBox3.h>


namespace vgKernel {
	
	
	//----------------------------------------------------------------------------
	
	Box3::Box3 ()
	{
		// uninitialized
	}
	//----------------------------------------------------------------------------
	
	Box3::Box3 (const Vec3& rkCenter, const Vec3* akAxis,
		const float* afExtent)
		:
	Center(rkCenter)
	{
		for (int i = 0; i < 3; i++)
		{
			Axis[i] = akAxis[i];
			Extent[i] = afExtent[i];
		}
	}
	//----------------------------------------------------------------------------
	
	Box3::Box3 (const Vec3& rkCenter, const Vec3& rkAxis0,
		const Vec3& rkAxis1, const Vec3& rkAxis2, float fExtent0,
		float fExtent1, float fExtent2)
		:
	Center(rkCenter)
	{
		Axis[0] = rkAxis0;
		Axis[1] = rkAxis1;
		Axis[2] = rkAxis2;
		Extent[0] = fExtent0;
		Extent[1] = fExtent1;
		Extent[2] = fExtent2;
	}
	//----------------------------------------------------------------------------
	
	void Box3::ComputeVertices (Vec3 akVertex[8]) const
	{
		Vec3 akEAxis[3] =
		{
			Extent[0]*Axis[0],
			Extent[1]*Axis[1],
			Extent[2]*Axis[2]
		};

		akVertex[0] = Center - akEAxis[0] - akEAxis[1] - akEAxis[2];
		akVertex[1] = Center + akEAxis[0] - akEAxis[1] - akEAxis[2];
		akVertex[2] = Center + akEAxis[0] + akEAxis[1] - akEAxis[2];
		akVertex[3] = Center - akEAxis[0] + akEAxis[1] - akEAxis[2];
		akVertex[4] = Center - akEAxis[0] - akEAxis[1] + akEAxis[2];
		akVertex[5] = Center + akEAxis[0] - akEAxis[1] + akEAxis[2];
		akVertex[6] = Center + akEAxis[0] + akEAxis[1] + akEAxis[2];
		akVertex[7] = Center - akEAxis[0] + akEAxis[1] + akEAxis[2];
	}
	//----------------------------------------------------------------------------

	
}// end of namespace vgKernel

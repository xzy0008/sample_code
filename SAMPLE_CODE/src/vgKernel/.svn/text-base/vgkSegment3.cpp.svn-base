



#include <vgStableHeaders.h>
#include <vgKernel/vgkSegment3.h>


namespace vgKernel {
	
	
	
	



	//----------------------------------------------------------------------------

	Segment3::Segment3 (const Vec3& rkOrigin,
		const Vec3& rkDirection, float fExtent)
		:
	Origin(rkOrigin),
		Direction(rkDirection),
		Extent(fExtent)
	{
	}
	//----------------------------------------------------------------------------

	Segment3::Segment3 (const Vec3& rkEnd0,
		const Vec3& rkEnd1)
	{
		Origin = ((float)0.5)*(rkEnd0 + rkEnd1);
		Direction = rkEnd1 - rkEnd0;
		Extent = ((float)0.5)*Direction.normalise();
	}
	//----------------------------------------------------------------------------

	Vec3 Segment3::getPosEnd () const
	{
		return Origin + Extent*Direction;
	}
	//----------------------------------------------------------------------------

	Vec3 Segment3::getNegEnd () const
	{
		return Origin - Extent*Direction;
	}
	//----------------------------------------------------------------------------

}// end of namespace vgKernel

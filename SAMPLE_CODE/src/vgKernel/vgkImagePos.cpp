


#include <vgStableHeaders.h>
#include <vgKernel/vgkImagePos.h>


namespace vgKernel {
	
	
	// 在mfc中可能会有默认的max定义宏.
#undef MAX
#undef MIN
#undef  max
#undef  min


	const ImagePos ImagePos::ZERO (0);

	const ImagePos ImagePos::MAX (
		std::numeric_limits<long>::max() ,
		std::numeric_limits<long>::max() );

	const ImagePos ImagePos::MIN (
		std::numeric_limits<long>::min() ,
		std::numeric_limits<long>::min() );


	//----------------------------------------------------------------
	String ImagePos::getDetails() const
	{
		std::ostringstream o;
		o << "ImagePos( " << x <<  " , " << y << " )";

		return o.str();
	}
	//----------------------------------------------------------------

	
}// end of namespace vgKernel

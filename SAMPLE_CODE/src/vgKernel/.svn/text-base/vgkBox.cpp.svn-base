


#include <vgStableHeaders.h>
#include <vgKernel/vgkBox.h>


namespace vgKernel {
	

	const Box Box::NULL_BOX( 
		-std::numeric_limits<float>::infinity(), 
		-std::numeric_limits<float>::infinity(), 
		-std::numeric_limits<float>::infinity(), 
		std::numeric_limits<float>::infinity(), 
		std::numeric_limits<float>::infinity(), 
		std::numeric_limits<float>::infinity() );
	
	
	//----------------------------------------------------------------
	String Box::getDetails()
	{
		std::ostringstream o;
		o << "Box: {" 
			<< "minVertex: " << _minVertex.getDetails() 
			<< " , maxVertex: " << _maxVertex.getDetails() << " }";

		return o.str();
	}
	//----------------------------------------------------------------


}// end of namespace vgKernel

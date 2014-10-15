

#ifndef __VGKSTRINGPAIRVECTOR_H__
#define __VGKSTRINGPAIRVECTOR_H__



#include <vgKernel/vgkSharePtr.h>

	
namespace vgKernel {


	typedef std::pair<String,String> StringPair;

	typedef std::vector< StringPair > StringPairVector;
	

	typedef SharePtr< StringPairVector > StringPairVectorPtr;
	
}// end of namespace vgKernel
	


#endif // end of __VGKSTRINGPAIRVECTOR_H__
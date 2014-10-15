


#ifndef __VGKSTRINGVECTOR_H__
#define __VGKSTRINGVECTOR_H__


#include <vgKernel/vgkSharePtr.h>
	
namespace vgKernel {


	typedef std::vector<std::string> StringVector;
	typedef std::vector< std::pair<String,StringVector> > StringVectorArr;


	typedef SharePtr<StringVector> StringVectorPtr;
	
	
	
}// end of namespace vgKernel
	


#endif // end of __VGKSTRINGVECTOR_H__
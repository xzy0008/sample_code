


#ifndef __VGSCSHAREPTRWRAPPER_H__
#define __VGSCSHAREPTRWRAPPER_H__

#include <vgKernel/vgkSharePtr.h>
#include <boost/python.hpp>


	
namespace vgKernel {
	template<class T>
	inline T * get_pointer( vgKernel::SharePtr<T> const& p ){
		return p.getPointer();
	}
}

namespace boost{ namespace python{
	template <class T>
	struct pointee< vgKernel::SharePtr<T> >{
		typedef T type;
	};

} }
	


#endif // end of __VGSCSHAREPTRWRAPPER_H__
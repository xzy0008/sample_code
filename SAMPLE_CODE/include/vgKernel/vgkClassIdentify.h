


#ifndef __VGKCLASSIDENTIFICATION_H__
#define __VGKCLASSIDENTIFICATION_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkClassFactory.h>

	
namespace vgKernel {

	/**
		@date 	2009/05/27  9:16	
		@author  xy
	
		@brief 	
	
		@see    
	*/
	class ClassIdentify
	{
	public:
		ClassIdentify()
		{
			
		}
		virtual ~ClassIdentify()
		{
			
		}
	
	public:

		virtual String getClassName() = 0;

		virtual String getClassShortName() = 0;
	
	};
	


	
#define VGK_CLASS_IN_DECLARE( classname ) \
	public:\
	virtual String getClassName()\
	{ \
		return typeid( classname ).name();\
	}\
	virtual String getClassShortName()\
	{\
		return #classname;\
	}

#define VGK_CLASS_OUT_DECLARE( classname ) \
	class ClassFactory##classname \
	: public vgKernel::TClassFactory<classname> \
	{\
	public:\
		ClassFactory##classname()\
		{\
			\
		}\
		virtual ~ClassFactory##classname()\
		{\
			\
		}\
	};


#define VGK_CLASS_IMPLEMENT( classname ) \
	vgKernel::ClassFacRegProxy _class_fac_reg_proxy_##classname(\
		new ClassFactory##classname );
	
}// end of namespace vgKernel
	


#endif // end of __VGKCLASSIDENTIFICATION_H__
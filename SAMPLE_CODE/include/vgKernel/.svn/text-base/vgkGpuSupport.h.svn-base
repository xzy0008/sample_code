


#ifndef __VGKGPUSUPPORT_H__
#define __VGKGPUSUPPORT_H__

#include <vgKernel/vgkForward.h>
#include <Cg/cg.h>
#include <Cg/cgGL.h>

	
namespace vgKernel {


	class  VGK_EXPORT GpuContext
	{
	public:
		// 创建在构造函数中  
		GpuContext();
		~GpuContext();

		CGcontext getContext()
		{
			assert( _CgContext != NULL );
			return _CgContext;
		}

	private:

		// CGcontext本身就是一个指针
		CGcontext   _CgContext;
	};



	/**
		注意,这个类需要实例化,具体在GpuManager中.
		和以前不同的是:很多static成员已经不再支持.
		需要从GpuMananger::getSingleton().getGpuSupport()之后再使用
	*/
	class  VGK_EXPORT GpuSupport
	{
	public:
		GpuSupport();
		~GpuSupport();

		CGprofile getVertexProfile() 
		{
			assert( isValid() );
			return _vertexProfile;
		}

		CGprofile getPixelProfile() 
		{
			assert( isValid() );
			return _pixelProfile;
		}


		GpuContext* getGpuContextPointer()
		{
			assert(isValid());
			return _gpuContext;
		}

		bool isValid() 
		{
			return _vertexProfile != CG_PROFILE_UNKNOWN &&
				_pixelProfile != CG_PROFILE_UNKNOWN;
		}

	private:

		bool setupValidCgProfile( CGprofile& vertex_profile ,
			CGprofile& pixel_profile );

		static void checkCgErrorStack();

	private:

		GpuContext* _gpuContext;

		bool _cubeMapSupported;
		bool _vertexTextureFetchSupported;

		CGprofile   _vertexProfile;
		CGprofile   _pixelProfile;

	};


	
}// end of namespace vgKernel



#endif // end of __VGKGPUSUPPORT_H__
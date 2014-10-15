


#ifndef __VGIIOREQUESTDUMPIMAGE_H__
#define __VGIIOREQUESTDUMPIMAGE_H__
#include <vgImage/vgiDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgAsyn/vgaIoRequest.h>
#include <vgImage/vgiFileDefinitionVgi.h>
#include <vgImage/vgiImageMiniature.h>

	
namespace vgImage {

	/**
		同步IO请求,用于保存vgi文件
		注意,删除操作由外部完成
	*/
	class  VGI_EXPORT IoRequestDumpImage : public vgAsyn::IoRequest
	{
	public:
		IoRequestDumpImage( ImageMiniature* imgmini );
		virtual ~IoRequestDumpImage();

		// no dispatch to main thread
		virtual bool anotherThreadHandler();

		virtual bool mainThreadHandler();

		VgiBrief* getBriefFromBuffer();

	private:

		ImageMiniature* _img;

	};
	
	
	
}// end of namespace vgImage
	


#endif // end of __VGIIOREQUESTDUMPIMAGE_H__
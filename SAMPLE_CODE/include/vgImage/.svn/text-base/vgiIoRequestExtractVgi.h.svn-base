




#ifndef __VGIIOREQUESTEXTRACTVGI_H__
#define __VGIIOREQUESTEXTRACTVGI_H__
#include <vgImage/vgiDefinition.h>

#include <vgKernel/vgkForward.h>
#include <vgAsyn/vgaIoRequest.h>

namespace vgImage {

	/**
		@date 	2008/06/24  9:04	
		@author  leven
	
		@brief 	test IoRequest
	
		@see    
	*/
	class  VGI_EXPORT IoRequestExtractVgi : public vgAsyn::IoRequest
	{
	public:
		IoRequestExtractVgi( String vgipath ,  vgAsyn::FileInfo* fileinfo );

		virtual ~IoRequestExtractVgi()
		{
			
		}
	
		virtual bool anotherThreadHandler();

		virtual bool mainThreadHandler();

	
	private:

		String _vgiPath;
	};
	
	
	
	
}// end of namespace vgImage

#endif // end of __VGIIOREQUESTEXTRACTVGI_H__
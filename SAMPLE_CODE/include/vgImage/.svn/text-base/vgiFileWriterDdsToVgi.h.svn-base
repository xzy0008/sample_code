


#ifndef __VGIFILEWRITERDDSTOVGI_H__
#define __VGIFILEWRITERDDSTOVGI_H__
#include <vgImage/vgiDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkStringVector.h>
#include <vgKernel/vgkProcessObserver.h>
#include <vgImage/vgiImageUtility.h>

	
namespace vgImage {

	/**
		@date 	2008/08/06  16:01	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGI_EXPORT FileWriterDdsToVgi : public vgKernel::ProcessNotifier
	{
	public:
		FileWriterDdsToVgi()
		{
			
		}
		virtual ~FileWriterDdsToVgi()
		{
			
		}
	
	public:

		/**
			用于从外部的dds文件保存到vgi文件
		*/
		bool writeToVgiFileFromDdsNames(
			const vgKernel::StringVectorPtr input_dds , 
			const String& output_filename , 
			const bool& empty_not_insert = false );

	private:

		bool writeToVgiFile(
			const vgKernel::StringVectorPtr input_dds , 
			const String& output_filename , const long& nextfileid ,
			const bool& empty_not_insert = false );
	
	};
	
	
}// end of namespace vgImage
	


#endif // end of __VGIFILEWRITERDDSTOVGI_H__
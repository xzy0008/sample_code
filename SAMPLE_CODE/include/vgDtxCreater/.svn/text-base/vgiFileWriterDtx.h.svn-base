


#ifndef __VGIFILEWRITERDTX_H__
#define __VGIFILEWRITERDTX_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkStringVector.h>
#include <vgKernel/vgkProcessObserver.h>
#include <vgImage/vgiImageUtility.h>
#include <vgTex/vgDtxDeclaration.h>	

	/**
		@date 	2009/05/14  16:01	
		@author  yuxin
	
		@brief 	
	
		@see    
	*/


	class   FileWriterDtx : public vgKernel::ProcessNotifier
	{
	public:
		FileWriterDtx()
		{
			
		}
		virtual ~FileWriterDtx()
		{
			
		}
	
	public:

		/**
			用于从外部的图片文件保存到DTX文件
		*/

	public:

		bool writeToDtxFile(
			const vgKernel::StringVectorPtr input_image,
			const FrameVectorPtr input_frame , 
			const String& output_filename ,
			const int& ratio ,
			const bool& empty_not_insert = false);
	
	};
	
	


#endif // end of __VGIFILEWRITERDTX_H__
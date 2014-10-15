


#ifndef __VGMO_FILEWRITERVMD_H__
#define __VGMO_FILEWRITERVMD_H__
#include <vgModel/vgmoDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgModel/vgmoModelItem.h>

	
namespace vgModel {

	/**
		@date 	2008/07/02  11:01	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGMO_EXPORT FileWriterVmd
	{
	public:
		FileWriterVmd()
		{
			
		}
		~FileWriterVmd()
		{
			
		}
	
	

	public:


		/**
			得到的是纹理的列表.如果失败,返回的StringVectorPtr为空
			注意,始终用最新的version id进行写入
		*/
		static vgKernel::StringVectorPtr writeToVmdFileFromModelItemMap(
			 ModelItemMap* items , const String& save_absolute_path );
	




	private:
	
	
	};
	
	
}// end of namespace vgModel
	


#endif // end of __VGMO_FILEWRITERVMD_H__
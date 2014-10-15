


#ifndef __VGMFILEWRITERVGM_H__
#define __VGMFILEWRITERVGM_H__


#include <vgMesh/vgmDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgMesh/vgmMeshItem.h>

	
namespace vgMesh {

	/**
		@date 	2008/07/02  11:01	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGM_EXPORT FileWriterVgm
	{
	public:
		FileWriterVgm()
		{
			
		}
		~FileWriterVgm()
		{
			
		}
	
	

	public:


		/**
			得到的是纹理的列表.如果失败,返回的StringVectorPtr为空
		*/
		static vgKernel::StringVectorPtr writeToVgmFileFromMeshItemMap(
			 MeshItemMap* items , const String& save_absolute_path );
	




	private:
	
	
	};
	
	
}// end of namespace vgMesh
	


#endif // end of __VGMFILEWRITERVGM_H__
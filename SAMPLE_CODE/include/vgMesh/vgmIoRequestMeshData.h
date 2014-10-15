


#ifndef __VGMIOREQUESTMESHDATA_H__
#define __VGMIOREQUESTMESHDATA_H__


#include <vgMesh/vgmDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgAsyn/vgaIoRequest.h>
#include <vgKernel/vgkUniqueID.h>
	
namespace vgMesh {

	using namespace vgKernel;
	class MeshData;
	class MeshDataPlus;
	class MeshItem;

	/**
		@date 	2008/07/10  13:56	
		@author  leven
	
		@brief 	1.利用vgAsyn::FileInfo把数据载入;
					2.利用UniqueID查找到MeshItem,
						然后用lod参数找到相应的Mesh做赋值操作.
	
		@see    
	*/
	class  VGM_EXPORT IoRequestMeshData : public vgAsyn::IoRequest
	{
	public:
		IoRequestMeshData( UniqueID unique_id , int lod ,
			vgAsyn::FileInfo* fileinfo , bool load_shadow_data );
		virtual ~IoRequestMeshData()
		{

		}



		virtual bool anotherThreadHandler();

		virtual bool mainThreadHandler();

		virtual bool isReallyNeedToSend();

	private:

		bool _loadShadowData;

		MeshDataPlus* _meshDataPlus;

		MeshData* _meshData;

		UniqueID _meshID;

		int _lod;
	};

	
	
}// end of namespace vgMesh
	


#endif // end of __VGMIOREQUESTMESHDATA_H__
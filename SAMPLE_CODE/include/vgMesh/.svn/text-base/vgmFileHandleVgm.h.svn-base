



#ifndef __VGMFILEHANDLEVGM_H__
#define __VGMFILEHANDLEVGM_H__




#include <vgMesh/vgmDefinition.h>

#include <vgKernel/vgkForward.h>
#include <vgAsyn/vgaFileHandle.h>
#include <vgMesh/vgmFileReaderVgm.h>
#include <vgKernel/vgkStringVector.h>

	
namespace vgMesh {



	/**
		@date 	2008/07/04  10:40	
		@author  leven
	
		@brief 	注意这里的逻辑.
		MeshItem实体的管理(负责删除)都是在MeshManager中
	
		@see    
	*/
	class  VGM_EXPORT FileHandleVgm : public vgAsyn::FileHandle
	{	
	public:
		FileHandleVgm( String filepath )
			: FileHandle( filepath )
		{
			_type = FILEHANDLE_TYPE_VGM;
			_isLinkedWithMeshMgr = false;
		}

		virtual ~FileHandleVgm()
		{

		}

		virtual bool exist( const String& metafilename );

		virtual vgKernel::StringVector* listMetaFileNames();

		virtual bool open();

		virtual void close();

		virtual bool extractToMultipleFiles( const String& save_multiple_file_path );

		//virtual IoRequestVector* listIoRequests();

		MeshItemMap* getMeshItemsPtr()
		{
			return &_itemPtrs;
		}

		void setLinkedFlag( const bool& flag )
		{
			_isLinkedWithMeshMgr = flag;
		}

		bool getLinkedFlag() const
		{
			return _isLinkedWithMeshMgr;
		}

	private:

		bool addMeshItem( MeshItem* item );

	private:

		bool _isLinkedWithMeshMgr;

		MeshItemMap _itemPtrs;
	};
	
	

	

	
}// end of namespace vgMesh
	



#endif // end of __VGMFILEHANDLEVGM_H__
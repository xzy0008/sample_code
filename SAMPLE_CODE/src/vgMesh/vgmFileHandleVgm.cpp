

#include <vgStableHeaders.h>
#include <vgMesh/vgmFileHandleVgm.h>
#include <vgAsyn/vgaMemoryFileManager.h>
#include <vgKernel/vgkRgbaQuad.h>


namespace vgMesh {
	
	
	
	
	//----------------------------------------------------------------
	bool FileHandleVgm::extractToMultipleFiles( 
		const String& save_multiple_file_path )
	{
		assert(0);

		return false;
	}
	//----------------------------------------------------------------
	bool FileHandleVgm::exist( const String& metafilename )
	{
		
		assert(0);
		return false;
	}
	//----------------------------------------------------------------
	vgKernel::StringVector* FileHandleVgm::listMetaFileNames()
	{
		assert(0);

		return NULL;
	}
	//----------------------------------------------------------------
	bool FileHandleVgm::open()
	{
		bool openres = FileHandle::open();

		if ( openres == false )
		{
			return false;
		}

		//------------------------------------------
		// 1.开始读取
		//------------------------------------------
		VgmBriefPtrVec* briefs = FileReaderVgm::getVgmBriefFromFile( 
			_filePath );

		if ( briefs == NULL )
		{
			return false;
		}
		
		assert( _itemPtrs.empty() == true );
		VgmBriefPtrVec::iterator iter = briefs->begin();
		VgmBriefPtrVec::iterator iter_end = briefs->end();

		for ( ; iter != iter_end ; ++iter )
		{
			MeshItem* item = 
				new MeshItem( );

			item->initialise( (*iter).getPointer() , this  );

			bool addres = addMeshItem( item );

			assert( addres == true );
		}

		delete briefs;

		//------------------------------------------
		// 加入进memoryfile
		//------------------------------------------
		//vgAsyn::MemoryFileManager::getSingleton().addMemoryFile( this );

		return true;
	}
	//----------------------------------------------------------------
	void FileHandleVgm::close()
	{
		FileHandle::close();

		//------------------------------------------
		// 判断是否删除
		//------------------------------------------
		if ( _isLinkedWithMeshMgr == false )
		{
			MeshItemMap::iterator iter = _itemPtrs.begin();
			MeshItemMap::iterator iter_end = _itemPtrs.end();

			for ( ; iter != iter_end ; ++iter )
			{
				delete iter->second;
			}

			_itemPtrs.clear();
		}
	}
	//----------------------------------------------------------------
	bool FileHandleVgm::addMeshItem( MeshItem* item )
	{
		MeshItemInsertRes res = _itemPtrs.insert(
			std::make_pair( item->getUniqueID() , item ) );

		return res.second;
	}
	//----------------------------------------------------------------
	//IoRequestVector* FileHandleVgm::listIoRequests()
	//{
	//	//assert( isOpened() );
	//	//assert( _itemPtrs.empty() == false );

	//	//MeshItemMap::iterator iter = _itemPtrs.begin();
	//	//MeshItemMap::iterator iter_end = _itemPtrs.end();

	//	//for ( ; iter != iter_end ; ++iter )
	//	//{
	//	//	MeshItem* itm = iter->second;

	//	//	itm->getMeshByLod()
	//	//}
	//	
	//	return NULL;
	//}
	//----------------------------------------------------------------


}// end of namespace vgMesh



#include <vgStableHeaders.h>
#include <vgModel/vgmoFileHandleVmd.h>

#include <vgKernel/vgkClassFactoryManager.h>




namespace vgModel {
	
	
	
	
	//----------------------------------------------------------------
	bool FileHandleVmd::extractToMultipleFiles( 
		const String& save_multiple_file_path )
	{
		assert(0);

		return false;
	}
	//----------------------------------------------------------------
	bool FileHandleVmd::exist( const String& metafilename )
	{
		
		assert(0);
		return false;
	}
	//----------------------------------------------------------------
	vgKernel::StringVector* FileHandleVmd::listMetaFileNames()
	{
		assert(0);

		return NULL;
	}
	//----------------------------------------------------------------
	bool FileHandleVmd::open()
	{
		bool openres = FileHandle::open();

		if ( openres == false )
		{
			return false;
		}

		//------------------------------------------
		// 1.开始读取
		//------------------------------------------
		VmdBriefPtrVec* briefs = FileReaderVmd::getVmdBriefFromFile( 
			_filePath , _header );

		if ( briefs == NULL )
		{
			return false;
		}
		
		assert( _itemPtrs.empty() == true );
		VmdBriefPtrVec::iterator iter = briefs->begin();
		VmdBriefPtrVec::iterator iter_end = briefs->end();

		for ( ; iter != iter_end ; ++iter )
		{

			String classname = (*iter)->_className;

			using namespace vgKernel;

			ClassFactory* fac = 
				ClassFactoryManager::getSingleton().getFactoryByClassName( 
				classname );

			if ( fac == NULL )
			{
				std::ostringstream o; 
				o << "不可识别的Class:" << classname << ", 跳过读取.";
				VGK_SHOW( o.str() );
				continue;
			}

			ClassIdentify* ren = fac->create();
			ModelItem* item = dynamic_cast< ModelItem*>( ren );

			if ( item == NULL )
			{
				delete ren;
				std::ostringstream o; 
				o << "不可识别的Class:" << classname << ", 跳过读取.";
				VGK_SHOW( o.str() );
				continue;
			}

			bool loadok = item->load( (*iter).getPointer() , this ,
				_header._version );

			if ( loadok == false )
			{
				assert( 0 );
				delete item;
				continue;
			}
			else
			{
				bool addres = addModelItem( item );
				assert( addres == true );
			}
		}

		delete briefs;

		//------------------------------------------
		// 加入进memoryfile
		//------------------------------------------
		//vgAsyn::MemoryFileManager::getSingleton().addMemoryFile( this );

		return true;
	}
	//----------------------------------------------------------------
	void FileHandleVmd::close()
	{
		FileHandle::close();

		//------------------------------------------
		// 判断是否删除
		//------------------------------------------
		if ( _isLinkedWithModelMgr == false )
		{
			ModelItemMap::iterator iter = _itemPtrs.begin();
			ModelItemMap::iterator iter_end = _itemPtrs.end();

			for ( ; iter != iter_end ; ++iter )
			{
				delete iter->second;
			}

			_itemPtrs.clear();
		}
	}
	//----------------------------------------------------------------
	bool FileHandleVmd::addModelItem( ModelItem* item )
	{
		ModelItemInsertRes res = _itemPtrs.insert(
			std::make_pair( item->getUniqueID() , item ) );

		return res.second;
	}
	//----------------------------------------------------------------
	//IoRequestVector* FileHandleVmd::listIoRequests()
	//{
	//	//assert( isOpened() );
	//	//assert( _itemPtrs.empty() == false );

	//	//ModelItemMap::iterator iter = _itemPtrs.begin();
	//	//ModelItemMap::iterator iter_end = _itemPtrs.end();

	//	//for ( ; iter != iter_end ; ++iter )
	//	//{
	//	//	ModelItem* itm = iter->second;

	//	//	itm->getModelByLod()
	//	//}
	//	
	//	return NULL;
	//}
	//----------------------------------------------------------------


}// end of namespace vgModel





#include <vgStableHeaders.h>
#include <vgKernel/vgkTrace.h>
#include <vgAsyn/vgaMemoryFileManager.h>


namespace vgAsyn {
	
	
	
	
	//----------------------------------------------------------------
	bool MemoryFileManager::checkExist( FileHandle* handle )
	{
		MemoryFilePtrVec::iterator iter = _memoryFiles.begin();
		MemoryFilePtrVec::iterator iter_end = _memoryFiles.end();

		for ( ; iter != iter_end
			; ++iter )
		{
			MemoryFile* file = *iter;
			if ( handle == file->getFilehandle() )
			{
				return true;
			}
		}

		return false;
	}
	//----------------------------------------------------------------
	bool MemoryFileManager::addMemoryFile( FileHandle* handle )
	{
		if ( checkExist( handle ))
		{
			return true;
		}

		MemoryFile* mem = new MemoryFile;

		bool importok = mem->importFromFileHandle( handle );

		if ( importok == false )
		{
			delete mem;
			return false;
		}

		_memoryFiles.push_back( mem );
		return true;
	}
	//----------------------------------------------------------------
	void MemoryFileManager::destroyAllMemoryFiles()
	{
		MemoryFilePtrVec::iterator iter = _memoryFiles.begin();
		MemoryFilePtrVec::iterator iter_end = _memoryFiles.end();

		for ( ; iter != iter_end
			; ++iter )
		{
			MemoryFile* file = *iter;
			delete file;
		}

		_memoryFiles.clear();
	}
	//----------------------------------------------------------------
	char* MemoryFileManager::readFromMemory( FileInfo* fileinfo )
	{
		assert( fileinfo != NULL );

		MemoryFilePtrVec::iterator iter = _memoryFiles.begin();
		MemoryFilePtrVec::iterator iter_end = _memoryFiles.end();

		MemoryFile* curfile = NULL;
		char* buffer = NULL;

		for ( ; iter != iter_end ; ++iter )
		{
			curfile = *iter;
			buffer = curfile->readMemory( fileinfo );

			if ( buffer != NULL )
			{
				return buffer;
			}
		}

		return NULL;
	}

	MemoryFileManager::MemoryFileManager() : Singleton<MemoryFileManager>( VGK_SINGLETON_LEFE_MEMORYFILEMGR )
	{
		VGK_TRACE(_T("MemoryFileManager created."));
	}

	MemoryFileManager::~MemoryFileManager()
	{
		VGK_TRACE(_T("MemoryFileManager destroyed."));
	}
	//----------------------------------------------------------------



}// end of namespace vgAsyn

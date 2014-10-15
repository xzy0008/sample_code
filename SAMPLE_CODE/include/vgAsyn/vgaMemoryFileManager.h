




#ifndef __VGAMEMORYFILEMANAGER_H__
#define __VGAMEMORYFILEMANAGER_H__

#include <vgAsyn/vgaDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSingleton.h>
#include <vgAsyn/vgaMemoryFile.h>

	
namespace vgAsyn {

	/**
		@date 	2009/04/29  10:21	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGA_EXPORT MemoryFileManager : 
		public vgKernel::Singleton<MemoryFileManager>
	{
		typedef std::vector<MemoryFile*> MemoryFilePtrVec;

		friend class vgKernel::Singleton<MemoryFileManager>;
	private:
		MemoryFileManager();
	public:
		~MemoryFileManager();

	protected:

		virtual bool initialise()
		{
			return true;
		}
		virtual bool shutdown()
		{
			destroyAllMemoryFiles();
			return true;
		}

	public:

		virtual void reset(){};//need to write

		void destroyAllMemoryFiles();

		bool addMemoryFile( FileHandle* handle );

		char* readFromMemory( FileInfo* fileinfo );

	private:

		bool checkExist( FileHandle* handle );

	private:

		MemoryFilePtrVec _memoryFiles;
	};
	
}// end of namespace vgAsyn
	


#endif // end of __VGAMEMORYFILEMANAGER_H__
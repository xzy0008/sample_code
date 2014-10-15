


#ifndef __VGACACHEITEM_H__
#define __VGACACHEITEM_H__
#include <vgAsyn/vgaDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgAsyn/vgaCacheDefine.h>


	
namespace vgAsyn {

	class FileHandle;

	class CacheItemKey
	{
	public:
		CacheItemKey( FileHandle* handle , 
			long fileoffset , long filesize )
		{
			_fileHandleAddress = handle;
			_fileOffset = fileoffset;
			_fileSize = filesize;
		}
		~CacheItemKey()
		{
			
		}
 
	public:

		FileHandle* _fileHandleAddress;
		long _fileOffset;
		long _fileSize;

	};


	//typedef std::hash_map


	/**
		@date 	2008/11/14  15:49	
		@author  leven
	
		@brief 	用来存储每个io的包
	
		@see    
	*/
	class CacheItem
	{
	public:
		CacheItem()
		{
			
		}
		~CacheItem()
		{
			
		}
	
	
	protected:
	
		
	
	private:
	
	
	};
	
	
}// end of namespace vgAsyn
	


#endif // end of __VGACACHEITEM_H__
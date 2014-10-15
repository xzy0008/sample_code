
#include <vgStableHeaders.h>
#include <vgTex/tvgArchiveManager.h>


#include <vgKernel/vgkLogManager.h>
#include <vgKernel/vgkTrace.h>
#include <vgKernel/vgkSystemUtility.h>


template <> 
vgCore::ArchiveManager* ::Singleton<vgCore::ArchiveManager>::ms_pSingleton = 0;


namespace vgCore {
	
	//----------------------------------------------------------------
	ArchiveManager* ArchiveManager::getSingletonPtr(void)
	{
		return ms_pSingleton;
	}
	ArchiveManager& ArchiveManager::getSingleton(void)
	{  
		assert( ms_pSingleton );  
		return ( *ms_pSingleton );  
	}

	ArchiveManager::ArchiveManager( bool createCurrentFileSys /*= true */,
		bool createSystemTempPath/* = true*/)
	{
		if ( createCurrentFileSys )
		{
			char buf[1024];
			GetCurrentDirectory( 1024 , buf );

			String currentDir(buf);

			vgKernel::LogManager::getSingleton().logMessage( 
				"Current Directory is : "  + currentDir + "\n now creating default FileSystem Archive...");

			// 考虑这里是否加入容错机制。
			FileSystemArchive* pCurrentFileSys = 
				new FileSystemArchive( currentDir ,"FileSystem" );

			this->addArchive( DEFAULT_FILESYSTEM_WEIGHT , ArchivePtr( pCurrentFileSys ) );

			vgKernel::LogManager::getSingleton().logMessage( 
				"Current Directory added.");
		}

		if ( createSystemTempPath )
		{
			//String temp_path = SystemUtil::getSystemTempPath();
			String temp_path = vgKernel::SystemUtility::getSystemTempPath();

			assert( temp_path.empty() == false );

			vgKernel::LogManager::getSingleton().logMessage( 
				"System Temp Directory is : "  + temp_path + "\n now creating default FileSystem Archive...");

			// 考虑这里是否加入容错机制。
			FileSystemArchive* pTempArchive = 
				new FileSystemArchive( temp_path ,"FileSystem" );

			this->addArchive( DEFAULT_SYSTEM_TEMP_WEIGHT , ArchivePtr( pTempArchive ) );

			vgKernel::LogManager::getSingleton().logMessage( 
				"System Temp Directory added.");

		}

		VGK_TRACE("ArchiveManager created.");
	}
	//----------------------------------------------------------------
	
}// end of namespace vgCore

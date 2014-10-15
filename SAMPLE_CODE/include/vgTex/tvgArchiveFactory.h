

#ifndef __TVGARCHIVEFACTORY_H__
#define __TVGARCHIVEFACTORY_H__

#include <vgCore/vgPrerequisites.h>
#include <vgTex/tvgArchive.h>
#include <vgTex/tvgZipArchive.h>

namespace vgCore {

	/**
		@date 	2007/07/10  13:46	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGDEP_EXPORT ArchiveFactory
	{
	public:
		ArchiveFactory()
		{
			
		}
		~ArchiveFactory()
		{
			
		}
	
	
	public:
		static ArchivePtr createFromName( const String& name )
		{
			std::string::size_type pos1 = name.rfind('.');
			std::string::size_type pos2 = name.rfind("\\/");

			//assert( pos1 != pos2 );

			if ( pos1 == std::string::npos )
			{
				return createFromFileSystem( name );
			}

			if ( ( pos1 > pos2 )
				|| ( pos2 == std::string::npos ) )
			{
				// 查找扩展名
				std::string ext = 
					name.substr(pos1 == std::string::npos ? name.length() : pos1 + 1);

				transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
				ext.erase(ext.find_last_not_of(' ') + 1);

				if ( ext == "zip" )
				{
					assert(0);
				}
				if ( ext == "vgimg" )
				{
					return createFromVgimg( name );
				}
				return ArchivePtr();
			}

			// 此时从FileSystem创建
			return createFromFileSystem( name );
		}

#if 0
		static inline ArchivePtr createFromZip( const String& zipname )
		{
			return ArchivePtr( new ZipArchive( zipname , "zip" ) );
		}
#endif

		static inline ArchivePtr createFromVgimg( const String& vgimg_name )
		{
			return ArchivePtr( new VgimgArchive( vgimg_name , "vgimg") );
		}

		static inline ArchivePtr createFromFileSystem( const String& foldername )
		{
			return ArchivePtr( new FileSystemArchive( foldername , "filesystem") );
		}

	};
	
	
	
}// end of namespace vgCore

#endif // end of __TVGARCHIVEFACTORY_H__
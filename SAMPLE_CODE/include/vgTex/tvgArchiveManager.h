


#ifndef __TVGARCHIVEMANAGER_H__
#define __TVGARCHIVEMANAGER_H__

#include <vgCore/vgPrerequisites.h>
#include <vgCore/vgSingleton.h>
#include <vgTex/tvgArchiveFactory.h>

#include <vgKernel/vgkTrace.h>


namespace vgCore {

	/**
		@date 	2007/06/11  8:46	
		@author  Leven
	
		@brief 	
	
		@see    
	*/
	class  VGDEP_EXPORT ArchiveManager : public ::Singleton<ArchiveManager>
	{
	public:

#define  DEFAULT_FILESYSTEM_WEIGHT  100
#define  DEFAULT_SYSTEM_TEMP_WEIGHT	-500

		//typedef std::vector<ArchivePtr>  ArchivePtrList;
		typedef std::map< int  , ArchivePtr > ArchivePtrMap;

		typedef std::pair< ArchivePtrMap::iterator , bool > ArchivePtrMapInsertResult;

		typedef std::map< String , StringVectorPtr > ArchiveListResult;

	public:

		ArchiveManager( bool createCurrentFileSys = true ,
			bool createSystemTempPath = true );

		~ArchiveManager()
		{
			VGK_TRACE("ArchiveManager deleted.");
		}
		//----------------------------------------------------------------
		bool addArchive( const int& search_weight , const ArchivePtr& pArchive )
		{
			if ( pArchive.isNull() )
			{
				return false;
			}

			ArchivePtrMapInsertResult res = 
				this->mArchivePtrMap.insert( std::make_pair( search_weight , pArchive ) );

			return res.second;
		}
		//----------------------------------------------------------------
		bool addArchive( const int& search_weight , const String& archive_name )
		{
			ArchivePtr parchive = ArchiveFactory::createFromName( archive_name );
			if ( parchive.isNull() )
			{
				return false;
			}

			ArchivePtrMapInsertResult res = 
				this->mArchivePtrMap.insert( std::make_pair( search_weight , parchive ) );

			return res.second;
		}
		//----------------------------------------------------------------
		void clear()
		{
			this->mArchivePtrMap.clear();
		}
		//----------------------------------------------------------------
		FileInfoPtr getFileInfo(const String& filename) const
		{
			ArchivePtrMap::const_reverse_iterator iter = mArchivePtrMap.rbegin();
			ArchivePtrMap::const_reverse_iterator iter_end = mArchivePtrMap.rend();

			FileInfoPtr search_result;
			for ( ; iter != iter_end ; ++ iter )
			{
				assert( !iter->second.isNull() );
				search_result = iter->second->getFileInfo( filename );

				// when searched the file
				if ( search_result.isNull() == false )
				{
					break;
				}
			}

			return search_result;
		}
		//----------------------------------------------------------------
		ArchiveListResult listAll(bool recursive = true, bool dirs = false)
		{
			ArchivePtrMap::reverse_iterator iter = mArchivePtrMap.rbegin();
			ArchivePtrMap::reverse_iterator iter_end = mArchivePtrMap.rend();

			ArchiveListResult result;

			for ( ; iter != iter_end ; ++ iter )
			{
				assert( !iter->second.isNull() );
				StringVectorPtr tmp = iter->second->list( recursive , dirs );

				result.insert( std::make_pair( iter->second->getName() , tmp ) );
			}

			return result;
		}
		//----------------------------------------------------------------
		void loadAll()
		{
			ArchivePtrMap::reverse_iterator iter = mArchivePtrMap.rbegin();
			ArchivePtrMap::reverse_iterator iter_end = mArchivePtrMap.rend();

			for ( ; iter != iter_end ; ++ iter )
			{
				assert( !iter->second.isNull() );
				iter->second->load();
			}
			return;
		}
		//----------------------------------------------------------------
		void reset()
		{
			unloadAll();
			mArchivePtrMap.clear();
		}
		//----------------------------------------------------------------
		void unloadAll()
		{
			ArchivePtrMap::reverse_iterator iter = mArchivePtrMap.rbegin();
			ArchivePtrMap::reverse_iterator iter_end = mArchivePtrMap.rend();

			for ( ; iter != iter_end ; ++ iter )
			{
				assert( !iter->second.isNull() );
				iter->second->unload();
			}
			return;
		}
		//----------------------------------------------------------------
		bool exists(const String& filename)
		{
			ArchivePtrMap::reverse_iterator iter = mArchivePtrMap.rbegin();
			ArchivePtrMap::reverse_iterator iter_end = mArchivePtrMap.rend();

			for ( ; iter != iter_end ; ++ iter )
			{
				assert( !iter->second.isNull() );
				if ( iter->second->exists( filename ) )
				{
					return true;
				}
			}
			return false;
		}
		//----------------------------------------------------------------
		StreamReaderPtr open(const String& filename) const
		{
			ArchivePtrMap::const_reverse_iterator iter = mArchivePtrMap.rbegin();
			ArchivePtrMap::const_reverse_iterator iter_end = mArchivePtrMap.rend();

			StreamReaderPtr result;
			for ( ; iter != iter_end ; ++ iter )
			{
				assert( !iter->second.isNull() );
				result = iter->second->open( filename );

				if ( !result.isNull() )
				{
					break;
				}
			}
			return result;
		}
		//----------------------------------------------------------------
		ArchivePtr getArchive( const String& filepath )
		{
			ArchivePtrMap::reverse_iterator iter = mArchivePtrMap.rbegin();
			ArchivePtrMap::reverse_iterator iter_end = mArchivePtrMap.rend();

			for ( ; iter != iter_end ; ++ iter )
			{
				assert( !iter->second.isNull() );
				if ( iter->second->getName() == filepath )
				{
					return iter->second;
				}
			}
			return ArchivePtr();
		}
		//----------------------------------------------------------------
		String getDetails()
		{
			std::ostringstream o;
			o << "===================== ArchiveManager Details begin =========================\n";

			if ( mArchivePtrMap.empty() )
			{
				o << "\t\tcontains nothing!!!\n";
			}

			ArchivePtrMap::reverse_iterator iter = mArchivePtrMap.rbegin();
			ArchivePtrMap::reverse_iterator iter_end = mArchivePtrMap.rend();

			for ( ; iter != iter_end ; ++ iter )
			{
				assert( !iter->second.isNull() );
				o << "### Archive Weight: " << iter->first << "\n" 
					<< iter->second->getDetails() << "\n";
			}

			o << "===================== ArchiveManager Details end =========================\n";
			return o.str();
		}

		/// static functions which can make singleton pattern.
		static ArchiveManager& getSingleton(void);
		static ArchiveManager* getSingletonPtr(void);
	
	
	private:
	
		ArchivePtrMap mArchivePtrMap;
	};
	
	
	
}// end of namespace vgCore

#endif // end of __TVGARCHIVEMANAGER_H__


#ifndef __TVGARCHIVE_H__
#define __TVGARCHIVE_H__

#include <vgCore/vgPrerequisites.h>
#include <vgTex/tvgStreamFactory.h>
#include <vgTex/tvgArchiveDeclaration.h>


namespace vgCore {




	/**
		@date 	2007/06/08  15:12	
		@author  Leven
	
		@brief 	
	
		@see    
	*/
    /** Archive-handling class.
    @remarks
        An archive is a generic term for a container of files. This may be a
        filesystem folder, it may be a compressed archive, it may even be 
        a remote location shared on the web. This class is designed to be 
        subclassed to provide access to a range of file locations. 
    @par
        Instances of this class are never constructed or even handled by end-user
        applications. They are constructed by custom ArchiveFactory classes, 
        which plugins can register new instances of using ArchiveManager. 
        End-user applications will typically use ResourceManager or 
        ResourceGroupManager to manage resources at a higher level, rather than 
        reading files directly through this class. Doing it this way allows you
        to benefit from OGRE's automatic searching of multiple file locations 
        for the resources you are looking for.
    */
    class VgesExport Archive  
    {
    protected:
        /// Archive name
        String mName; 
        /// Archive type code
        String mType;

    public:

        /** Constructor - don't call direct, used by ArchiveFactory.
        */
        Archive( const String& name, const String& archType )
            : mName(name), mType(archType) {}

        /** Default destructor.
        */
        virtual ~Archive() {}

		/// Get the name of this archive
		const String& getName(void) const { return mName; }

        /// Returns whether this archive is case sensitive in the way it matches files
        //virtual bool isCaseSensitive(void) const = 0;

        /** Loads the archive.
        @remarks
            This initializes all the internal data of the class.
        @warning
            Do not call this function directly, it is ment to be used
            only by the ArchiveManager class.
        */
        virtual void load() = 0;

        /** Unloads the archive.
        @warning
            Do not call this function directly, it is ment to be used
            only by the ArchiveManager class.
        */
        virtual void unload() = 0;

        /** Open a stream on a given file. 
        @note
            There is no equivalent 'close' method; the returned stream
            controls the lifecycle of this file operation.
        @param filename The fully qualified name of the file
        @returns A shared pointer to a DataStream which can be used to 
            read / write the file. If the file is not present, returns a null
			shared pointer.
        */
        virtual StreamReaderPtr open(const String& filename) const = 0;

		//////////////////////////////////////////////////////////////////////////
		// 李文加

		virtual FileInfoPtr getFileInfo(const String& filename) = 0;

		//////////////////////////////////////////////////////////////////////////

        /** List all file names in the archive.
        @note
            This method only returns filenames, you can also retrieve other
            information using listFileInfo.
        @param recursive Whether all paths of the archive are searched (if the 
            archive has a concept of that)
        @param dirs Set to true if you want the directories to be listed
            instead of files
        @returns A list of filenames matching the criteria, all are fully qualified
        */
        virtual StringVectorPtr list(bool recursive = true, bool dirs = false) = 0;
        
        /** List all files in the archive with accompanying information.
        @param recursive Whether all paths of the archive are searched (if the 
            archive has a concept of that)
        @param dirs Set to true if you want the directories to be listed
            instead of files
        @returns A list of structures detailing quite a lot of information about
            all the files in the archive.
        */
        virtual FileInfoListPtr listFileInfo(bool recursive = true, bool dirs = false) = 0;

        /** Find all file or directory names matching a given pattern
            in this archive.
        @note
            This method only returns filenames, you can also retrieve other
            information using findFileInfo.
        @param pattern The pattern to search for; wildcards (*) are allowed
        @param recursive Whether all paths of the archive are searched (if the 
            archive has a concept of that)
        @param dirs Set to true if you want the directories to be listed
            instead of files
        @returns A list of filenames matching the criteria, all are fully qualified
        */
        virtual StringVectorPtr find(const String& pattern, bool recursive = true,
            bool dirs = false) = 0;

        /** Find out if the named file exists (note: fully qualified filename required) */
        virtual bool exists(const String& filename) = 0; 

        /** Find all files or directories matching a given pattern in this
            archive and get some detailed information about them.
        @param pattern The pattern to search for; wildcards (*) are allowed
        @param recursive Whether all paths of the archive are searched (if the 
        archive has a concept of that)
        @param dirs Set to true if you want the directories to be listed
            instead of files
        @returns A list of file information structures for all files matching 
            the criteria.
        */
        virtual FileInfoListPtr findFileInfo(const String& pattern, 
            bool recursive = true, bool dirs = false) = 0;

        /// Return the type code of this Archive
        const String& getType(void) const { return mType; }

		virtual String getDetails();
        
    };

	typedef SharedPtr<Archive> ArchivePtr;
	
	


	/** Specialisation of the Archive class to allow reading of files from 
	filesystem folders / directories.
	*/
	class FileSystemArchive : public Archive 
	{
	protected:
		/** Utility method to retrieve all files in a directory matching pattern.
		@param pattern File pattern
		@param recursive Whether to cascade down directories
		@param dirs Set to true if you want the directories to be listed
		instead of files
		@param simpleList Populated if retrieving a simple list
		@param detailList Populated if retrieving a detailed list
		@param currentDir The current directory relative to the base of the 
		archive, for file naming
		*/
		void findFiles(const String& pattern, bool recursive, bool dirs,
			StringVector* simpleList, FileInfoList* detailList);

	public:
		FileSystemArchive(const String& name, const String& archType );
		~FileSystemArchive();

		/// @copydoc Archive::isCaseSensitive
		bool isCaseSensitive(void) const;

		/// @copydoc Archive::load
		void load();
		/// @copydoc Archive::unload
		void unload();

		/// @copydoc Archive::open
		StreamReaderPtr open(const String& filename) const;

		/// @copydoc Archive::list
		StringVectorPtr list(bool recursive = true, bool dirs = false);

		/// @copydoc Archive::listFileInfo
		FileInfoListPtr listFileInfo(bool recursive = true, bool dirs = false);

		/// @copydoc Archive::find
		StringVectorPtr find(const String& pattern, bool recursive = true,
			bool dirs = false);

		/// @copydoc Archive::findFileInfo
		FileInfoListPtr findFileInfo(const String& pattern, bool recursive = true,
			bool dirs = false);

		/// @copydoc Archive::exists
		bool exists(const String& filename);



		//////////////////////////////////////////////////////////////////////////
		// 李文加

		virtual FileInfoPtr getFileInfo(const String& filename)
		{
			FileInfoListPtr searchresult = findFileInfo( filename , false );
			if ( searchresult.isNull() )
			{
				return FileInfoPtr();
			}

			assert( searchresult->size() >= 0 );

			if ( searchresult->empty() )
			{
				return FileInfoPtr();
			}

			if ( searchresult->size() != 1 )
			{
				VG_WARN(Warning::WARN_INVALID_STATE ,
					Warning::BUTTON_NONE,
					"多个同名文件被查找到",
					"FileSystemArchive::getFileInfo");
			}

			FileInfoPtr ret( new FileInfo() );

			(*ret) = (*searchresult)[0];

			//assert( !this->open( ret->filename ).isNull() );

			ret->streamReaderPtr = this->open( ret->filename );

			//assert( !ret->streamReaderPtr.isNull() );

			return ret;
		}


		//////////////////////////////////////////////////////////////////////////

	};




	class VgimgArchive : public Archive
	{

		typedef std::map<String , VgimgMetaFile*> VgimgMetaFileMap;
	private:
		bool isValid() const
		{
			return mpIndexField != NULL;
		}

	private:
		StreamPos  mArchiveBegPos;
		StreamReaderPtr mArchiveStreamReader;

		VgimgHeader mHeader;

		long		mMetaFileNum;

		VgimgMetaFile*  mpIndexField;
		VgimgMetaFileMap mMetaFileMap;

	public:

		VgimgArchive( const String& name , const StreamReaderPtr& pstream ,
			const String& archType )
			: Archive(name, archType) , mArchiveStreamReader( pstream )
		{

			if ( pstream.isNull() )
			{
				assert( 0 && "pstream is null!");
			}

			assert( pstream->isValid() == true );

			mArchiveBegPos = mArchiveStreamReader->tell();

			mpIndexField = NULL;
		}

		VgimgArchive( const String& name , const String& archType )
			: Archive(name, archType) 
		{
			mArchiveStreamReader = StreamFactory::createReaderFromFile( name );

			if ( mArchiveStreamReader.isNull() )
			{
				assert( 0 && "mArchiveStreamReader is null!");
			}

			mArchiveBegPos = mArchiveStreamReader->tell();

			mpIndexField = NULL;
		}

		~VgimgArchive()
		{
			mArchiveStreamReader->close();
			if ( mpIndexField != NULL )
			{
				delete mpIndexField;
				mpIndexField = NULL;
			}
		}
	
		/// @copydoc Archive::isCaseSensitive
		virtual bool isCaseSensitive(void) const
		{
			return true;
		}

		/// @copydoc Archive::load
		virtual void load();
		/// @copydoc Archive::unload
		virtual void unload()
		{
			if ( mpIndexField != NULL )
			{
				delete mpIndexField;
				mpIndexField = NULL;
			}
		}

		/// @copydoc Archive::open
		virtual StreamReaderPtr open(const String& filename) const
		{
			assert( isValid() );

			VgimgMetaFileMap::const_iterator result = mMetaFileMap.find( filename );
			if ( result == mMetaFileMap.end() )
			{
				return StreamReaderPtr();
			}
			
			this->mArchiveStreamReader->seek( result->second->mStoragePos );

			return this->mArchiveStreamReader;
		}

		/// @copydoc Archive::list
		virtual StringVectorPtr list(bool recursive = true, bool dirs = false)
		{
			StringVectorPtr ret( new StringVector() );

			VgimgMetaFileMap::iterator iter = mMetaFileMap.begin();
			VgimgMetaFileMap::iterator iter_end = mMetaFileMap.end();

			for ( ; iter != iter_end ; ++ iter )
			{
				ret->push_back( iter->first );
			}

			return ret;
		}

		/// @copydoc Archive::listFileInfo
		virtual FileInfoListPtr listFileInfo(bool recursive = true, bool dirs = false)
		{
			assert( isValid() );

			if ( mMetaFileMap.empty() )
			{
				// return empty.
				return FileInfoListPtr();
			}

			FileInfoListPtr ret( new FileInfoList() );

			VgimgMetaFileMap::iterator iter = mMetaFileMap.begin();
			VgimgMetaFileMap::iterator iter_end = mMetaFileMap.end();

			for ( ; iter != iter_end ; ++ iter )
			{
				VgimgMetaFile& metafile = *iter->second;

				FileInfo finfo;

				finfo.archive			= this;
				//finfo.streamReaderPtr	= this->mArchiveStreamReader;
				finfo.filename			= metafile.mFilename;
				finfo.path				= "";
				finfo.basename			= metafile.mFilename;
				finfo.compressedSize	= metafile.mFileSize;
				finfo.uncompressedSize	= metafile.mFileSize;

				ret->push_back( finfo );
			}

			return ret;
		}

		/// @copydoc Archive::find
		virtual StringVectorPtr find(const String& pattern, bool recursive = true,
			bool dirs = false)
		{
			assert(0);
			return StringVectorPtr();
		}

		/// @copydoc Archive::findFileInfo
		virtual FileInfoListPtr findFileInfo(const String& pattern, bool recursive = true,
			bool dirs = false)
		{
			assert(0);
			return FileInfoListPtr();
		}

		/// @copydoc Archive::exists
		virtual bool exists(const String& filename)
		{
			assert( isValid() );

			VgimgMetaFileMap::iterator result = mMetaFileMap.find( filename );
			if ( result == mMetaFileMap.end() )
			{
				return false;
			}
			return true;
		}

		virtual FileInfoPtr getFileInfo(const String& filename)
		{
			assert( isValid() );

			VgimgMetaFileMap::iterator result = mMetaFileMap.find( filename );
			if ( result == mMetaFileMap.end() )
			{
				// search failed, return empty.
				return FileInfoPtr();
			}

			VgimgMetaFile& metafile = *result->second;

			FileInfoPtr ret( new FileInfo() );
			FileInfo& finfo = *ret;

			this->mArchiveStreamReader->seek( metafile.mStoragePos );
		
			finfo.archive			= this;
			finfo.streamReaderPtr	= this->mArchiveStreamReader;
			finfo.filename			= metafile.mFilename;
			finfo.path				= "";
			finfo.basename			= metafile.mFilename;
			finfo.compressedSize	= metafile.mFileSize;
			finfo.uncompressedSize	= metafile.mFileSize;

			return ret;
		}


	};







}// end of namespace vgCore

#endif // end of __TVGARCHIVE_H__
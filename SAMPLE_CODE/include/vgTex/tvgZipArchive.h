

#ifndef __TVGZIPARCHIVE_H__
#define __TVGZIPARCHIVE_H__


#if 0

#include <vgCore/vgPrerequisites.h>
#include <vgTex/tvgArchive.h>

#include <zzip/zzip.h>

// Forward declaration for zziplib to avoid header file dependency.
typedef struct zzip_dir		ZZIP_DIR;
typedef struct zzip_file	ZZIP_FILE;


namespace vgCore {




	/**
		@date 	2007/06/08  15:41	
		@author  Leven
	
		@brief 	
	
		@see    
	*/
	/** Specialisation of the Archive class to allow reading of files from a zip
	format source archive.
	@remarks
	This archive format supports all archives compressed in the standard
	zip format, including iD pk3 files.
	*/
	class ZipArchive : public Archive 
	{
	protected:
		/// Handle to root zip file
		ZZIP_DIR* mZzipDir;
		/// Handle any errors from zzip
		void checkZzipError(int zzipError, const String& operation) const;
		/// File list (since zziplib seems to only allow scanning of dir tree once)
		FileInfoList mFileList;
	public:
		ZipArchive(const String& name, const String& archType );
		~ZipArchive();
		/// @copydoc Archive::isCaseSensitive
		bool isCaseSensitive(void) const { return false; }

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
		// ÀîÎÄ¼Ó

		virtual FileInfoPtr getFileInfo(const String& filename) 
		{
			StreamReaderPtr preader = this->open( filename );
			if ( preader.isNull() )
			{
				// return null sharedPtr
				return FileInfoPtr();
			}

			FileInfoList::const_iterator i, iend;
			iend = mFileList.end();
			for (i = mFileList.begin(); i != iend; ++i)
			{
				if ( i->filename == filename )
					//ret->push_back(*i);
				{
					FileInfoPtr ret( new FileInfo(*i) );

					ret->streamReaderPtr = preader;

					return ret;
				}
			}

			// return null sharedPtr
			return FileInfoPtr();
		}

		//////////////////////////////////////////////////////////////////////////


	};

	/** Specialisation of DataStream to handle streaming data from zip archives. */
	class ZipStreamReader : public StreamReader
	{
	protected:
		ZZIP_FILE* mZzipFile;

		bool mClosed;

	private:

		bool isValid() const
		{
			return (this->mClosed == false) && (mZzipFile != NULL);
		};

	public:
		/// Unnamed constructor
		ZipStreamReader(ZZIP_FILE* zzipFile, size_t uncompressedSize);
		/// Constructor for creating named streams
		ZipStreamReader(const String& name, ZZIP_FILE* zzipFile, size_t uncompressedSize);
		~ZipStreamReader();
		/// @copydoc DataStream::read
		size_t read(void* buf, size_t count);
		/// @copydoc DataStream::skip
		void skip(long count);
		/// @copydoc DataStream::seek
		void seek( size_t pos );
		/// @copydoc DataStream::seek
		size_t tell(void) const;
		/// @copydoc DataStream::eof
		bool eof(void) const;
		/// @copydoc DataStream::close
		void close(void);

	};

	
	
}// end of namespace vgCore

#endif

#endif // end of __TVGZIPARCHIVE_H__
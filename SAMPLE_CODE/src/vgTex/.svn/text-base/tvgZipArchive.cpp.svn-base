
#include <vgStableHeaders.h>

#if 0

#include <vgTex/tvgZipArchive.h>

#include <zzip/lib.h>


#pragma message("  now input zziplib...")
#pragma   comment(lib,"zziplib.lib")



namespace vgCore {
	

    /// Utility method to format out zzip errors
    String getZzipErrorDescription(zzip_error_t zzipError) 
    {
        String errorMsg;
        switch (zzipError)
        {
        case ZZIP_NO_ERROR:
            break;
        case ZZIP_OUTOFMEM:
            errorMsg = "Out of memory.";
            break;            
        case ZZIP_DIR_OPEN:
        case ZZIP_DIR_STAT: 
        case ZZIP_DIR_SEEK:
        case ZZIP_DIR_READ:
            errorMsg = "Unable to read zip file.";
            break;            
        case ZZIP_UNSUPP_COMPR:
            errorMsg = "Unsupported compression format.";
            break;            
        case ZZIP_CORRUPTED:
            errorMsg = "Corrupted archive.";
            break;            
        default:
            errorMsg = "Unknown error.";
            break;            
        };

        return errorMsg;
    }
    //-----------------------------------------------------------------------
    ZipArchive::ZipArchive(const String& name, const String& archType )
        : Archive(name, archType), mZzipDir(0)
    {
    }
    //-----------------------------------------------------------------------
    ZipArchive::~ZipArchive()
    {
        unload();
    }
    //-----------------------------------------------------------------------
    void ZipArchive::load()
    {
        if (!mZzipDir)
        {
            zzip_error_t zzipError;
            mZzipDir = zzip_dir_open(mName.c_str(), &zzipError);
            checkZzipError(zzipError, "opening archive");

            // Cache names
            ZZIP_DIRENT zzipEntry;
            while (zzip_dir_read(mZzipDir, &zzipEntry))
            {
                FileInfo info;
				info.archive = this;
                // Get basename / path
                StringUtil::splitFilename(zzipEntry.d_name, info.basename, info.path);
                info.filename = zzipEntry.d_name;
                // Get sizes
                info.compressedSize = static_cast<size_t>(zzipEntry.d_csize);
                info.uncompressedSize = static_cast<size_t>(zzipEntry.st_size);
                // folder entries
                if (info.basename.empty())
                {
                    info.filename = info.filename.substr (0, info.filename.length () - 1);
                    StringUtil::splitFilename(info.filename, info.basename, info.path);
                    // Set compressed size to -1 for folders; anyway nobody will check
                    // the compressed size of a folder, and if he does, its useless anyway
                    info.compressedSize = size_t (-1);
                }

                mFileList.push_back(info);

            }

        }
    }
    //-----------------------------------------------------------------------
    void ZipArchive::unload()
    {
        if (mZzipDir)
        {
            zzip_dir_close(mZzipDir);
            mZzipDir = 0;
            mFileList.clear();
        }
    
    }
    //-----------------------------------------------------------------------
	StreamReaderPtr ZipArchive::open(const String& filename) const
    {

        // Format not used here (always binary)
        ZZIP_FILE* zzipFile = 
            zzip_file_open(mZzipDir, filename.c_str(), ZZIP_ONLYZIP | ZZIP_CASELESS);
        if (!zzipFile)
		{
            int zerr = zzip_error(mZzipDir);
            String zzDesc = getZzipErrorDescription((zzip_error_t)zerr);
            LogManager::getSingleton().logMessage(
                mName + " - Unable to open file " + filename + ", error was '" + zzDesc + "'");
                
			// return null pointer
			return StreamReaderPtr();
		}

		// Get uncompressed size too
		ZZIP_STAT zstat;
		zzip_dir_stat(mZzipDir, filename.c_str(), &zstat, ZZIP_CASEINSENSITIVE);

        // Construct & return stream
        return StreamReaderPtr(new ZipStreamReader(filename, zzipFile, static_cast<size_t>(zstat.st_size)));

    }
    //-----------------------------------------------------------------------
    StringVectorPtr ZipArchive::list(bool recursive, bool dirs)
    {
        StringVectorPtr ret = StringVectorPtr(new StringVector());

        FileInfoList::iterator i, iend;
        iend = mFileList.end();
        for (i = mFileList.begin(); i != iend; ++i)
            if ((dirs == (i->compressedSize == size_t (-1))) &&
                (recursive || i->path.empty()))
                ret->push_back(i->filename);

        return ret;
    }
    //-----------------------------------------------------------------------
    FileInfoListPtr ZipArchive::listFileInfo(bool recursive, bool dirs)
    {
        FileInfoList* fil = new FileInfoList();
        FileInfoList::const_iterator i, iend;
        iend = mFileList.end();
        for (i = mFileList.begin(); i != iend; ++i)
            if ((dirs == (i->compressedSize == size_t (-1))) &&
                (recursive || i->path.empty()))
                fil->push_back(*i);

        return FileInfoListPtr(fil);
    }
    //-----------------------------------------------------------------------
    StringVectorPtr ZipArchive::find(const String& pattern, bool recursive, bool dirs)
    {
        StringVectorPtr ret = StringVectorPtr(new StringVector());
        // If pattern contains a directory name, do a full match
        bool full_match = (pattern.find ('/') != String::npos) ||
                          (pattern.find ('\\') != String::npos);

        FileInfoList::iterator i, iend;
        iend = mFileList.end();
        for (i = mFileList.begin(); i != iend; ++i)
            if ((dirs == (i->compressedSize == size_t (-1))) &&
                (recursive || full_match || i->path.empty()))
                // Check basename matches pattern (zip is case insensitive)
                if (StringUtil::match(full_match ? i->filename : i->basename, pattern, false))
                    ret->push_back(i->filename);

        return ret;
    }
    //-----------------------------------------------------------------------
	FileInfoListPtr ZipArchive::findFileInfo(const String& pattern, 
        bool recursive, bool dirs)
    {
        FileInfoListPtr ret = FileInfoListPtr(new FileInfoList());
        // If pattern contains a directory name, do a full match
        bool full_match = (pattern.find ('/') != String::npos) ||
                          (pattern.find ('\\') != String::npos);

        FileInfoList::iterator i, iend;
        iend = mFileList.end();
        for (i = mFileList.begin(); i != iend; ++i)
            if ((dirs == (i->compressedSize == size_t (-1))) &&
                (recursive || full_match || i->path.empty()))
                // Check name matches pattern (zip is case insensitive)
                if (StringUtil::match(full_match ? i->filename : i->basename, pattern, false))
                    ret->push_back(*i);

        return ret;
    }
    //-----------------------------------------------------------------------
	bool ZipArchive::exists(const String& filename)
	{
		ZZIP_STAT zstat;
		int res = zzip_dir_stat(mZzipDir, filename.c_str(), &zstat, ZZIP_CASEINSENSITIVE);

		return (res == ZZIP_NO_ERROR);

	}
	//-----------------------------------------------------------------------
    void ZipArchive::checkZzipError(int zzipError, const String& operation) const
    {
        if (zzipError != ZZIP_NO_ERROR)
        {
            String errorMsg = getZzipErrorDescription(static_cast<zzip_error_t>(zzipError));

            VG_EXCEPT(Exception::ERR_INTERNAL_ERROR, 
                mName + " - error whilst " + operation + ": " + errorMsg,
                "ZipArchive::checkZzipError");
        }
    }
    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    ZipStreamReader::ZipStreamReader(ZZIP_FILE* zzipFile, size_t uncompressedSize)
        : mZzipFile(zzipFile)
    {
		mSize = uncompressedSize;

		//added by leven
		if ( mZzipFile == NULL )
		{
			this->mClosed = true;
		}
		else
		{
			this->mClosed = false;
		}
    }
    //-----------------------------------------------------------------------
    ZipStreamReader::ZipStreamReader(const String& name, ZZIP_FILE* zzipFile, 
		size_t uncompressedSize)
        :StreamReader(name), mZzipFile(zzipFile)
    {
		mSize = uncompressedSize;

		//added by leven
		if ( mZzipFile == NULL )
		{
			this->mClosed = true;
		}
		else
		{
			this->mClosed = false;
		}
    }
    //-----------------------------------------------------------------------
	ZipStreamReader::~ZipStreamReader()
	{
		close();
	}
    //-----------------------------------------------------------------------
    size_t ZipStreamReader::read(void* buf, size_t count)
    {
        return zzip_file_read(mZzipFile, (char*)buf, count);
    }
    //-----------------------------------------------------------------------
    void ZipStreamReader::skip(long count)
    {
        zzip_seek(mZzipFile, static_cast<zzip_off_t>(count), SEEK_CUR);
    }
    //-----------------------------------------------------------------------
    void ZipStreamReader::seek( size_t pos )
    {
		zzip_seek(mZzipFile, static_cast<zzip_off_t>(pos), SEEK_SET);
    }
    //-----------------------------------------------------------------------
    size_t ZipStreamReader::tell(void) const
    {
		return zzip_tell(mZzipFile);
    }
    //-----------------------------------------------------------------------
    bool ZipStreamReader::eof(void) const
    {
        return (zzip_tell(mZzipFile) >= static_cast<zzip_off_t>(mSize));
    }
    //-----------------------------------------------------------------------
    void ZipStreamReader::close(void)
    {
		//added by leven
		if ( mClosed == true )
		{
			return;
		}

        zzip_file_close(mZzipFile);

		//added by leven
		this->mClosed = true;
    }
    //-----------------------------------------------------------------------
    //const String& ZipArchiveFactory::getType(void) const
    //{
    //    static String name = "Zip";
    //    return name;
    //}

	
	
}// end of namespace vgCore

#endif
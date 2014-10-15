

#ifndef __TVGARCHIVESAVER_H__
#define __TVGARCHIVESAVER_H__

#include <vgCore/vgPrerequisites.h>
#include <vgTex/tvgArchive.h>
#include <vgTex/tvgStreamFactory.h>
#include <vgTex/tvgArchiveDeclaration.h>
//#include <../vgTrace.h>
#include <vgTex/tvgImage.h>

#include <vgKernel/vgkTrace.h>

namespace vgCore {


	/**
		@date 	2007/06/12  15:00	
		@author  Leven
	
		@brief 	
	
		@see    
	*/
	class  VGDEP_EXPORT ArchiveSaver
	{

	public:

		ArchiveSaver( StreamWriterPtr& pwriter , const StringPairListPtr& pstrpairlist)
		{
			assert( !pwriter.isNull() );

			// 先这样写
			assert( !pstrpairlist.isNull() );
			this->mInputListPtr = pstrpairlist;

			this->mOutputStreamPtr = pwriter;

			this->mMetaFileListPtr.bind( new MetaFileList() );

			VGK_TRACE( "ArchiveSaver created!");
		}
		~ArchiveSaver()
		{
			VGK_TRACE( "ArchiveSaver deleted!");
		}
	

		bool beginToWrite()
		{
			assert( !mInputListPtr.isNull() );
			assert( !mOutputStreamPtr.isNull() );

			assert( !this->mMetaFileListPtr.isNull() );
			assert( this->mMetaFileListPtr->empty() );
			
			long whole_data_len = 0;
			StreamPos whole_data_beg = 0;

			// 存储写入头文件时的位置。
			this->mHeaderBeginPos = this->mOutputStreamPtr->tell();

			// 写入文件头内容。
			this->mOutputStreamPtr->write( (const char*)&mHeader , sizeof( Header ) );
			VGK_TRACE( sizeof(Header) );

			// 存储图像数据的写入起始点。
			whole_data_beg = this->mOutputStreamPtr->tell();

			// 开始写入图像数据
			StringPairList::iterator input_iter = mInputListPtr->begin();
			StringPairList::iterator input_iter_end = mInputListPtr->end();

			for ( ; input_iter != input_iter_end ; ++ input_iter )
			{
				const String& filename = input_iter->first;
				FileInfoPtr pfileinfo = ArchiveManager::getSingleton().getFileInfo( filename );

				if ( pfileinfo.isNull() )
				{
					continue;
				}

				WriterInfoPtr pwriter( new WriterInfo() );
				pwriter->aimFilename = input_iter->second;

				const StreamPos beg_pos = pwriter->absoluteBeginPos = mOutputStreamPtr->tell();
				pwriter->streamWriterPtr = this->mOutputStreamPtr;

				/// 还有DDS format

				if ( saveToStream( make_pair( pfileinfo , pwriter ) ) == false )
				{
					assert( 0 && "写入失败！！");
					mOutputStreamPtr->seek( beg_pos );
					continue;
				}
				
				// 存储MetaFile信息
				MetaFile tmpmeta;
				assert( input_iter->second.size() <= 256 );

				strcpy( tmpmeta.mFilename , input_iter->second.c_str() );
				tmpmeta.mFileSize = pwriter->fileLength;
				tmpmeta.mStoragePos = beg_pos;

				whole_data_len += tmpmeta.mFileSize;

				this->mMetaFileListPtr->push_back( tmpmeta );
			}

			// 写完数据后，写索引区域，放在末尾。
			const StreamPos index_beg = mOutputStreamPtr->tell();
			const long index_num = this->mMetaFileListPtr->size();
			const long index_filelen = index_num * sizeof( MetaFile );

			// 写入索引信息
			
			//char* index_buf = new char[index_num * sizeof( MetaFile )];
			//assert( index_buf!= NULL );

			if ( index_filelen != 0 )
			{
				const char* index_mem_beg = reinterpret_cast<const char*>( &(*mMetaFileListPtr)[0] );
				mOutputStreamPtr->write( index_mem_beg , index_filelen );
			}

			const StreamPos whole_file_end = mOutputStreamPtr->tell();

			// 更新文件头

			this->mHeader.mMetaFieldBegin	= index_beg;
			this->mHeader.mFilesNum			= index_num;
			this->mHeader.mMetaFieldLength	= index_filelen;
			this->mHeader.mWholeDataLength	= whole_data_len;
			this->mHeader.mDataBegin		= whole_data_beg;

			mOutputStreamPtr->seek( mHeaderBeginPos );
			const char* header_mem_beg = reinterpret_cast<const char*>(&mHeader);
			mOutputStreamPtr->write( header_mem_beg , sizeof( Header ) );

			mOutputStreamPtr->seek( whole_file_end );
			return true;
		}


		bool saveToStream( pair<FileInfoPtr, WriterInfoPtr>& input_param );

		bool saveToStream( const MetaSaverListPtr& saver_list );

		//----------------------------------------------------------------


		bool saveHeader( const StreamWriterPtr& pwriterstream ,
			const StringPairListPtr& pstrpairlist );

		long calculateHeaderLength( const StringPairListPtr& pstrpairlist )
		{
			if ( pstrpairlist.isNull() )
			{
				return 0;
			}
			
			long size1 = 3 * sizeof(long) + 2 * sizeof( StreamPos );
			long size2 = pstrpairlist->size() * sizeof( MetaFile );

			return size1 + size2;
		}


	public:

		//PreHeader	mPreHeader;

		StreamPos   mHeaderBeginPos;
		Header		mHeader;

		MetaFileListPtr mMetaFileListPtr;

		StringPairListPtr mInputListPtr;

		StreamWriterPtr mOutputStreamPtr;
	
	
	};

	typedef SharedPtr<ArchiveSaver> ArchiveSaverPtr;

	typedef ArchiveSaver VgimgArchiveSaver;

	
	
	
}// end of namespace vgCore

#endif // end of __TVGARCHIVESAVER_H__
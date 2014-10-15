


#include <vgStableHeaders.h>
#include <vgImage/vgiFileWriterDdsToVgi.h>
#include <vgImage/vgiFileWriterVgi.h>
#include <vgImage/vgiImageUtility.h>
#include <vgImage/vgiFileDefinitionVgi.h>
#include <vgKernel/vgkStreamWriter.h>
#include <vgKernel/vgkStreamReader.h>
#include <vgKernel/vgkCrcUtility.h>
#include <vgKernel/vgkStringUtility.h>

namespace vgImage {
	
	
	//----------------------------------------------------------------
	bool FileWriterDdsToVgi::writeToVgiFile( 
		const vgKernel::StringVectorPtr input_dds ,
		const String& output_filename , const long& nextfileid ,
		const bool& empty_not_insert /*= false */)
	{
		if ( input_dds.isNull() == true )
		{
			MessageBox( NULL , "输入dds序列为空" , "Error" , MB_OK );
			return false;
		}

		if ( input_dds->empty() == true )
		{
			MessageBox( NULL , "输入dds序列为空" , "Error" , MB_OK );
			return false;
		}


		//------------------------------------------
		// 确定process的进度条
		// 最后加2分别是文件开始的工作和文件收尾的工作
		//------------------------------------------
		int processCounter = 0;
		this->notifyProcessObserversStart( "开始生成vgi文件..." ,0,
			input_dds->size() - 1 + 2);

		//------------------------------------------
		// 首先检查文件是否是dds,是否有重名
		//------------------------------------------
		{
			std::set<String> names;
			std::pair<std::set<String>::iterator , bool > result;
			vgKernel::StringVector::iterator iter = input_dds->begin();
			vgKernel::StringVector::iterator iter_end  =input_dds->end();

			for (  ;iter != iter_end ; ++ iter )
			{
				String ext = ImageUtility::findImageFileExtension( *iter );

				if ( ext != "dds" )
				{
					MessageBox( NULL , "含有非DDS文件" , "Error" , MB_OK );
					return false;
				}

				String filename =
					ImageUtility::findFilenameFromAbsolutePath( *iter );
				StringUtility::toLowerCase( filename );

				if ( filename.size() >= VGI_NAME_LENGTH )
				{
					std::ostringstream o;
					o << "含有文件名过长的dds文件:" << filename ;
					MessageBox( NULL , o.str().c_str() , "Error" , MB_OK );
					return false;
				}

				result = names.insert( filename );

				if ( result.second == false )
				{
					std::ostringstream o;
					o << "含有重名dds文件(注意,vgi文件区分大小写): " <<  filename;
					MessageBox( NULL , o.str().c_str() , "Error" , MB_OK );
					return false;
				}
			}
		}

		//------------------------------------------
		// 如果需要把空的dds删除,则在这里操作
		//------------------------------------------
		vgKernel::StringVectorPtr input_names( new vgKernel::StringVector );
		{
			vgKernel::StringVector::iterator iter = input_dds->begin();
			vgKernel::StringVector::iterator iter_end = input_dds->end();

			for ( ; iter != iter_end ; ++ iter )
			{
				if ( empty_not_insert  == false )
				{
					// 直接插入即可.
					input_names->push_back( *iter );
				}
				else
				{
					bool isempty = true;
					bool readok = true;

					readok = ImageUtility::checkDdsImageIsEmpty( *iter , isempty );

					if ( isempty == false )
					{
						input_names->push_back( *iter );
					}
				}
			}
		}




		//------------------------------------------
		// 然后检查是否覆盖文件
		//------------------------------------------
		StreamWriterPtr pwriter = 
			StreamWriterFactory::createFromFile( output_filename ,true);

		if ( pwriter.isNull() == true )
		{
			return false;
		}

		if ( pwriter->isValid() == false )
		{
			return false;
		}

		this->notifyProcessObserversPos( "开始写vgi文件" , processCounter ++ );

		//------------------------------------------
		// 其次开始写文件,并且读dds,写入vgi
		//------------------------------------------
		std::vector<String> validList;
		VgiHeader header;
		std::vector<VgiBrief*> briefs;
		vgKernel::StringVector errList;

		//------------------------------------------
		// 1.先预写一边header
		// brief写在最后即可.
		//------------------------------------------
		long filebegin = pwriter->tell();
		assert( filebegin == 0 );
		pwriter->write( &header , sizeof( header ) );

		// 写data数据区
		{
			vgKernel::StringVector::iterator iter = input_names->begin();
			vgKernel::StringVector::iterator iter_end  =input_names->end();

			for (  ;iter != iter_end ; ++ iter )
			{

				this->notifyProcessObserversPos( "正在处理" + *iter  , processCounter ++ );

				StreamReaderPtr preader = 
					StreamReaderFactory::createFromFile( *iter );

				if ( preader.isNull() == true )
				{
					errList.push_back( *iter );
					continue;
				}

				long filesize = preader->size();
				assert( filesize >= 0 );

				if ( filesize == 0 )
				{
					errList.push_back( *iter );
					continue;
				}

				char* buffer = new char[filesize];
				memset( buffer , 0 , filesize );

				long readnum = preader->read( buffer , filesize );
				assert( readnum == filesize );

				if ( readnum != filesize )
				{
					errList.push_back( *iter );
					continue;
				}

				String metafilename = 
					ImageUtility::findFilenameFromAbsolutePath( *iter );

				// 创建brief
				VgiBrief* brief = new VgiBrief;
				bool getinfores = 
					brief->getInfoFromBuffer( metafilename , buffer , filesize );

				if ( getinfores == false )
				{
					delete brief;
					errList.push_back( *iter );
					continue;
				}

				// 写入文件
				long metafilebegin = pwriter->tell();
				brief->_metaFileOffset = metafilebegin;

				long writenum = pwriter->write( buffer , filesize );
				assert( writenum == filesize );

				if ( writenum != filesize )
				{
					MessageBox( NULL , "致命错误" , "Error" , MB_OK );
					return false;
				}

				// 插入队列
				briefs.push_back( brief );
				validList.push_back( *iter );

				// 清理
				delete[] buffer;
				buffer = NULL;
				filesize = 0;
			}
		}

		assert( validList.size() == briefs.size() );
		if ( validList.empty() == true )
		{
			MessageBox( NULL , "无有效的dds文件输入." , "Error" , MB_OK );
			return false;
		}

		//更新header
		header._positionOfBriefs = pwriter->tell();
		header._numberOfBriefs = briefs.size();
		// 最后的4字节是校验码
		header._sizeOfWholeFile = header._positionOfBriefs +
			header._numberOfBriefs * header._lengthOfOneBrief + sizeof( DWORD );

		header._nextFileID = nextfileid;

		assert( sizeof( DWORD ) == 4 );

		//------------------------------------------
		// 重写header
		//------------------------------------------
		pwriter->seek( filebegin );
		pwriter->write( &header , sizeof( header ) );

		// 跳转到写brief区域
		pwriter->seek( header._positionOfBriefs );

		//------------------------------------------
		// 写入brief
		//------------------------------------------
		{
			std::vector<VgiBrief*>::iterator iter = briefs.begin();
			std::vector<VgiBrief*>::iterator iter_end = briefs.end();

			for ( ; iter != iter_end ; ++iter )
			{
				long writenum =pwriter->write( *iter , sizeof( VgiBrief ));
				assert( writenum == sizeof( VgiBrief ) );
			}
		}

		//------------------------------------------
		// 开始计算校验码
		//------------------------------------------
		this->notifyProcessObserversPos( "计算校验码"  , processCounter ++ );


		DWORD crcCode;

		CrcUtility::initCrc32Code( crcCode );

		// 校验header
		for ( int i = 0 ; i < sizeof( header ) ; ++ i )
		{
			CrcUtility::calculateCrc32Code( (char*)&header + i , crcCode );
		}

		// 校验数据区
		{
			vgKernel::StringVector::iterator iter = validList.begin();
			vgKernel::StringVector::iterator iter_end  =validList.end();

			for (  ;iter != iter_end ; ++ iter )
			{
				StreamReaderPtr preader = 
					StreamReaderFactory::createFromFile( *iter );

				assert( preader.isNull() == false );

				long filesize = preader->size();
				assert( filesize > 0 );
				char* buffer = new char[filesize];
				memset( buffer , 0 , filesize );

				long readnum = preader->read( buffer , filesize );
				assert( readnum == filesize );

				for ( int  i = 0 ; i < filesize ; ++ i )
				{
					CrcUtility::calculateCrc32Code( buffer + i , crcCode );
				}
				// 清理
				delete[] buffer;
			}
		}

		// 校验brief
		{
			std::vector<VgiBrief*>::iterator iter = briefs.begin();
			std::vector<VgiBrief*>::iterator iter_end = briefs.end();

			for ( ; iter != iter_end ; ++iter )
			{
				for ( int i = 0 ; i < sizeof( VgiBrief ) ; ++ i )
				{
					CrcUtility::calculateCrc32Code( (char*)(*iter) + i , crcCode );
				}
			}
		}

		// 写入校验码
		long writenum =pwriter->write( &crcCode , sizeof( DWORD ) );
		assert( writenum == sizeof( DWORD ) );

		pwriter.setNull();

		//------------------------------------------
		// 开始检查文件正确性
		//------------------------------------------
#if 1
		DWORD checkcode;
		bool getres = CrcUtility::getFileCrc32Code( output_filename , checkcode );
		assert( getres == true );

		if ( checkcode != 0xFFFFFFFF )
		{
			MessageBox( NULL , "文件校验失败,请重新保存." , "保存失败" , 
				MB_OK | MB_ICONINFORMATION );

			// 清理brief
			std::vector<VgiBrief*>::iterator iter = briefs.begin();
			std::vector<VgiBrief*>::iterator iter_end = briefs.end();

			for ( ; iter != iter_end ; ++iter )
			{
				delete *iter;
			}

			briefs.clear();
			return false;
		}
#endif

		//------------------------------------------
		// 清理工作并生成report
		//------------------------------------------
		String outputmsg;

		if ( errList.empty() == false )
		{
			std::ostringstream o;

			o << "保存失败的列表:\n";

			vgKernel::StringVector::iterator iter = errList.begin();
			vgKernel::StringVector::iterator iter_end  = errList.end();

			for (  ;iter != iter_end ; ++ iter )
			{
				o << *iter << "\n";
			}

			outputmsg	+= o.str();
			outputmsg	+= "\n\n";
		}

		{
			std::ostringstream o;

			o << "成功保存的文件列表:\n";

			int count = 0;

			std::vector<VgiBrief*>::iterator iter = briefs.begin();
			std::vector<VgiBrief*>::iterator iter_end = briefs.end();

			for ( ; iter != iter_end ; ++iter )
			{
				o << (*iter)->_fileName;

				if ( count == 5 )
				{
					o << "\n";
					count = 0;
				}
				else
				{
					o << "\t";
					++count;
				}

				delete *iter;
			}

			briefs.clear();
			outputmsg += o.str();
		}

		// 生成报告
		std::ostringstream o;
		o << "处理完成,成功" << briefs.size() <<
			"个文件,失败:" << errList.size() << "个文件.";
		this->notfiyProcessObserversFinish( o.str() );


		return true;
	}
	//----------------------------------------------------------------
	bool FileWriterDdsToVgi::writeToVgiFileFromDdsNames(
		const vgKernel::StringVectorPtr input_dds , 
		const String& output_filename , 
		const bool& empty_not_insert /*= false */ )
	{
		using namespace vgKernel;

		// 出错的文件队列
		StringVectorPtr err_files( new StringVector );

		//------------------------------------------
		// 做必要的检查
		//------------------------------------------
		if ( StringUtility::getFileExtension( output_filename ) != "vgi" )
		{
			return false;
		}
		if ( input_dds.isNull() == true )
		{
			return false;
		}
		if ( input_dds->empty() == true )
		{
			return false;
		}

		//------------------------------------------
		// 读取每个dds文件,判断存在的同时,读入
		// 文件的大小,然后可以判断如何切割vgi文件.
		//------------------------------------------
		uint64 wholesize = 0;		// 总共的文件大小.
		unsigned int one_vgi_size = 0;
		int cur_list_num = 0;

		typedef std::vector<StringVectorPtr> StringVecPtrVec;
		StringVecPtrVec split_list;

		int dds_size = input_dds->size();
		StringVector& ddsvec = *input_dds.getPointer();

		for ( int i = 0 ; i < dds_size ; ++ i )
		{
			StreamReaderPtr preader = 
				StreamReaderFactory::createFromFile( ddsvec[i] );

			if ( preader.isNull() )
			{
				err_files->push_back( ddsvec[i] );
				continue;
			}

			int filesize = preader->size();

			if ( filesize == 0 )
			{
				err_files->push_back( ddsvec[i] );
				continue;
			}

			wholesize += filesize;
			one_vgi_size += filesize;

			if ( one_vgi_size >= VGI_MAX_SINGLE_FILE_SIZE )
			{
				one_vgi_size = filesize;	// 注意这里不是0
				cur_list_num ++;
			}

			if ( cur_list_num == split_list.size() )
			{
				split_list.push_back( StringVectorPtr( new StringVector() ) );
			}

			assert( cur_list_num < split_list.size() );

			// 最后插入
			split_list[ cur_list_num ]->push_back( ddsvec[i] );
		}

		//------------------------------------------
		// 开始保存
		//------------------------------------------
		String metaname =
			StringUtility::getFilenameWithoutExtFromAbsPath( output_filename );
		String path = StringUtility::getPathFromAbsoluteFilename( output_filename );

		for ( int i = 0 ; i < split_list.size() ; ++ i )
		{
			String curoutname;

			if ( i == 0 )
			{
				curoutname = output_filename;
			}
			else
			{
				std::ostringstream o;
				o << path << metaname << ".part" << i << ".vgi";
				curoutname = o.str();
			}

			bool writeok = writeToVgiFile( split_list[i] , 
				curoutname , 
				( i == split_list.size() - 1 ) ? 0 : i + 1 , 
				empty_not_insert );

			if ( writeok == false )
			{
				return false;
			}
		}

		return true;

#if 0
		//------------------------------------------
		// 下面是按文件数目存取的版本
		//------------------------------------------

		//------------------------------------------
		// 做必要的检查
		//------------------------------------------
		if ( StringUtility::getFileExtension( output_filename ) != "vgi" )
		{
			return false;
		}
		if ( input_dds.isNull() == true )
		{
			return false;
		}
		if ( input_dds->empty() == true )
		{
			return false;
		}

		// 存储需要保存的列表文件.
		// VtrPair中的int表示是下一个nextfileid.
		typedef std::pair<int,StringVectorPtr> VtrPair;
		typedef std::vector< VtrPair > VtrPairVec;
		//------------------------------------------
		// 首先检查输入的队列,如有必要,进行切块处理
		//------------------------------------------
		VtrPairVec fileVec;

		StringVector& in_names = *input_dds.getPointer();

		int vtrnum = ( in_names.size() + VGI_MAX_FILENUM - 1 ) / VGI_MAX_FILENUM;


		for ( int i = 0 ; i < vtrnum ; ++ i )
		{
			StringVectorPtr strvec( new StringVector );
			for ( int j = 0 ; j < VGI_MAX_FILENUM ; ++ j )
			{
				if ( (VGI_MAX_FILENUM * i + j) < in_names.size() )
				{
					strvec->push_back( in_names[ VGI_MAX_FILENUM * i + j ] );
				}
			}

			int nextfileid = 0;

			if ( i == vtrnum - 1 )
			{
				nextfileid = 0;
			}
			else
			{
				nextfileid = i + 1;
			}

			fileVec.push_back( std::make_pair( nextfileid , strvec ) );
		}


		//------------------------------------------
		// 处理已经构造好的map
		//------------------------------------------
		String out_terrainname = StringUtility::getFilenameWithoutExtFromAbsPath( output_filename );
		String path = StringUtility::getPathFromAbsoluteFilename( output_filename );

		for ( int i = 0 ; i < fileVec.size() ; ++ i )
		{
			String curoutname;

			if ( i == 0 )
			{
				curoutname = output_filename;
			}
			else
			{
				std::ostringstream o;
				o << path << "\\" << out_terrainname << ".part" << i << ".vgi";
				curoutname = o.str();
			}

			bool writeok = writeToVgiFile( fileVec[i].second , 
				curoutname , fileVec[i].first , empty_not_insert );

			if ( writeok == false )
			{
				return false;
			}
		}

		return true;
#endif

	}
	//----------------------------------------------------------------
}// end of namespace vgImage

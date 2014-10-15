




#include <vgStableHeaders.h>
#include <vgTerritory/vgtFileWriterVgtrToVtr.h>
#include <vgKernel/vgkStringUtility.h>
#include <vgImage/vgiImageUtility.h>
#include <vgKernel/vgkCrcUtility.h>
#include <vgTerritory/vgtDefinition.h>


namespace vgTerritory {
	
	
	
	
	//----------------------------------------------------------------
	bool FileWriterVgtrToVtr::writeToVtrFile( 
		const VgtrHeaderPtr vgtrheader,
		const vgKernel::StringVectorPtr input_vgtrs , 
		const String& output_filename , const long& nextFileID , 
		uchar* filledColor )
	{
		if ( vgtrheader.isNull() == true )
		{
			MessageBox( NULL , "输入参数为空" , "Error" , MB_OK );
			return false;
		}

		if ( input_vgtrs.isNull() == true )
		{
			MessageBox( NULL , "输入vgtr序列为空" , "Error" , MB_OK );
			return false;
		}

		if ( input_vgtrs->empty() == true )
		{
			MessageBox( NULL , "输入vgtr序列为空" , "Error" , MB_OK );
			return false;
		}


		//------------------------------------------
		// 确定process的进度条
		// 最后加2分别是文件开始的工作和文件收尾的工作
		//------------------------------------------
		int processCounter = 0;
		this->notifyProcessObserversStart( "开始生成vtr文件..." ,0,
			input_vgtrs->size() - 1 + 2);

		//------------------------------------------
		// 首先检查文件是否是vgtr,是否有重名
		//------------------------------------------
		{
			std::set<String> names;
			std::pair<std::set<String>::iterator , bool > result;
			vgKernel::StringVector::iterator iter = input_vgtrs->begin();
			vgKernel::StringVector::iterator iter_end  =input_vgtrs->end();

			for (  ;iter != iter_end ; ++ iter )
			{
				String ext = vgImage::ImageUtility::findImageFileExtension( *iter );

				if ( ext != "vgtr" )
				{
					MessageBox( NULL , "含有非vgtr文件" , "Error" , MB_OK );
					return false;
				}

				String filename =
					vgImage::ImageUtility::findFilenameFromAbsolutePath( *iter );
				vgKernel::StringUtility::toLowerCase( filename );

				if ( filename.size() >= VTR_NAME_LENGTH )
				{
					std::ostringstream o;
					o << "含有文件名过长的vgtr文件:" << filename ;
					MessageBox( NULL , o.str().c_str() , "Error" , MB_OK );
					return false;
				}

				result = names.insert( filename );

				if ( result.second == false )
				{
					std::ostringstream o;
					o << "含有重名vgtr文件(注意,vgtr文件不区分大小写): " <<  filename;
					MessageBox( NULL , o.str().c_str() , "Error" , MB_OK );
					return false;
				}
			}
		}


		//------------------------------------------
		// 然后检查是否覆盖文件
		//------------------------------------------
		vgKernel::StreamWriterPtr pwriter = 
			vgKernel::StreamWriterFactory::createFromFile( output_filename ,true);

		if ( pwriter.isNull() == true )
		{
			return false;
		}

		if ( pwriter->isValid() == false )
		{
			return false;
		}

		this->notifyProcessObserversPos( "开始写vtr文件" , processCounter ++ );

		//------------------------------------------
		// 其次开始写文件,并且读vgtr,写入vtr
		//------------------------------------------
		std::vector<String> validList;
		VtrHeader header;
		std::vector<VtrBrief*> briefs;
		vgKernel::StringVector errList;

		//------------------------------------------
		// 最开始对header进行赋值
		//------------------------------------------
		header._nextVtrFileID = nextFileID;
		header.cellsize = vgtrheader->cellsize;
		header.cellTexSize = vgtrheader->cellTexSize;
		strcpy( header.name , vgtrheader->name );
		if ( String(header.name).empty() == true )
		{
			MessageBox( NULL , "输入文件名为空" , "Error" , MB_OK );
			return false;
		}

		String imgname = header.name;
		imgname += ".vgi";
		assert( imgname.size() < VTR_NAME_LENGTH - 1 );
		strcpy( header.imageFilename , imgname.c_str() );

		header.originX = vgtrheader->originX;
		header.originY = vgtrheader->originY;
		header.originZ = vgtrheader->originZ;

		header.N = vgtrheader->N;
		header.xTotalNum = vgtrheader->xNum;
		header.zTotalNum = vgtrheader->zNum;

		memcpy( header._filledColor , filledColor , 4 );

		assert( header.xTotalNum == header.zTotalNum );

		int tmp = 
			log( header.xTotalNum / pow(2.0f, (float)header.N) ) / log(2.0f);

		header.numOfCenterLayers = tmp;
		


		//------------------------------------------
		// 1.先预写一边header
		// brief写在最后即可.
		//------------------------------------------
		long filebegin = pwriter->tell();
		assert( filebegin == 0 );
		pwriter->write( &header , sizeof( header ) );

		// 写data数据区
		{
			vgKernel::StringVector::iterator iter = input_vgtrs->begin();
			vgKernel::StringVector::iterator iter_end  =input_vgtrs->end();

			for (  ;iter != iter_end ; ++ iter )
			{

				this->notifyProcessObserversPos( "正在处理:" + *iter  , processCounter ++ );

				vgKernel::StreamReaderPtr preader = 
					vgKernel::StreamReaderFactory::createFromFile( *iter );

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
					vgImage::ImageUtility::findFilenameFromAbsolutePath( *iter );

				// 创建brief
				VtrBrief* brief = new VtrBrief;
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
			MessageBox( NULL , "无有效的vgtr文件输入." , "Error" , MB_OK );
			return false;
		}

		//更新header
		header._positionOfBriefs = pwriter->tell();
		header._numberOfBriefs = briefs.size();
		// 最后的4字节是校验码
		header._sizeOfWholeFile = header._positionOfBriefs +
			header._numberOfBriefs * header._lengthOfOneBrief + sizeof( DWORD );

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
			std::vector<VtrBrief*>::iterator iter = briefs.begin();
			std::vector<VtrBrief*>::iterator iter_end = briefs.end();

			for ( ; iter != iter_end ; ++iter )
			{
				long writenum =pwriter->write( *iter , sizeof( VtrBrief ));
				assert( writenum == sizeof( VtrBrief ) );
			}
		}

		//------------------------------------------
		// 开始计算校验码
		//------------------------------------------
		this->notifyProcessObserversPos( "计算校验码"  , processCounter ++ );


		DWORD crcCode;

		vgKernel::CrcUtility::initCrc32Code( crcCode );

		// 校验header
		for ( int i = 0 ; i < sizeof( header ) ; ++ i )
		{
			vgKernel::CrcUtility::calculateCrc32Code( (char*)&header + i , crcCode );
		}

		// 校验数据区
		{
			vgKernel::StringVector::iterator iter = validList.begin();
			vgKernel::StringVector::iterator iter_end  =validList.end();

			for (  ;iter != iter_end ; ++ iter )
			{
				vgKernel::StreamReaderPtr preader = 
					vgKernel::StreamReaderFactory::createFromFile( *iter );

				assert( preader.isNull() == false );

				long filesize = preader->size();
				assert( filesize > 0 );
				char* buffer = new char[filesize];
				memset( buffer , 0 , filesize );

				long readnum = preader->read( buffer , filesize );
				assert( readnum == filesize );

				for ( int  i = 0 ; i < filesize ; ++ i )
				{
					vgKernel::CrcUtility::calculateCrc32Code( buffer + i , crcCode );
				}
				// 清理
				delete[] buffer;
			}
		}

		// 校验brief
		{
			std::vector<VtrBrief*>::iterator iter = briefs.begin();
			std::vector<VtrBrief*>::iterator iter_end = briefs.end();

			for ( ; iter != iter_end ; ++iter )
			{
				for ( int i = 0 ; i < sizeof( VtrBrief ) ; ++ i )
				{
					vgKernel::CrcUtility::calculateCrc32Code( (char*)(*iter) + i , crcCode );
				}
			}
		}

		// 写入校验码
		long writenum =pwriter->write( &crcCode , sizeof( DWORD ) );
		assert( writenum == sizeof( DWORD ) );

		pwriter.setNull();

		//------------------------------------------
		// 开始检查文件正确性
		// 这一步应该由外部的应用程序完成
		// 比如提示:已完成, 正在校验中....
		//------------------------------------------
#if 0
		DWORD checkcode;
		bool getres = vgKernel::CrcUtility::getFileCrc32Code( output_filename , checkcode );
		assert( getres == true );

		if ( checkcode != 0xFFFFFFFF )
		{
			MessageBox( NULL , "文件校验失败,请重新保存." , "保存失败" , 
				MB_OK | MB_ICONINFORMATION );

			// 清理brief
			std::vector<VtrBrief*>::iterator iter = briefs.begin();
			std::vector<VtrBrief*>::iterator iter_end = briefs.end();

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

			std::vector<VtrBrief*>::iterator iter = briefs.begin();
			std::vector<VtrBrief*>::iterator iter_end = briefs.end();

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
	bool FileWriterVgtrToVtr::writeToVtrFileFromVgtrNames( 
		const VgtrHeaderPtr vgtrheader, const vgKernel::StringVectorPtr input_vgtrs , 
		const String& output_filename, uchar* filledColor  )
	{
		using namespace vgKernel;

		//------------------------------------------
		// 做必要的检查
		//------------------------------------------
		if ( StringUtility::getFileExtension( output_filename ) != "vtr" )
		{
			return false;
		}
		if ( input_vgtrs.isNull() == true )
		{
			return false;
		}
		if ( input_vgtrs->empty() == true )
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

		StringVector& in_names = *input_vgtrs.getPointer();

		int vtrnum = ( in_names.size() + VGT_VTR_MAX_FILENUM - 1 ) / VGT_VTR_MAX_FILENUM;


		for ( int i = 0 ; i < vtrnum ; ++ i )
		{
			StringVectorPtr strvec( new StringVector );
			for ( int j = 0 ; j < VGT_VTR_MAX_FILENUM ; ++ j )
			{
				if ( (VGT_VTR_MAX_FILENUM * i + j) < in_names.size() )
				{
					strvec->push_back( in_names[ VGT_VTR_MAX_FILENUM * i + j ] );
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
				o << path << "\\" << out_terrainname << ".part" << i << ".vtr";
				curoutname = o.str();
			}

			bool writeok = writeToVtrFile( vgtrheader , fileVec[i].second , 
				curoutname , fileVec[i].first ,filledColor);

			if ( writeok == false )
			{
				return false;
			}
		}

		return true;
	}
	//----------------------------------------------------------------


}// end of namespace vgTerritory

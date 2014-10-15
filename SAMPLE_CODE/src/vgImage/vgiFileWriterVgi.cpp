

#include <vgStableHeaders.h>
#include <vgImage/vgiFileWriterVgi.h>
#include <vgImage/vgiImageUtility.h>
#include <vgImage/vgiFileDefinitionVgi.h>
#include <vgImage/vgiIoRequestDumpImage.h>
#include <vgImage/vgiImageManager.h>
#include <vgKernel/vgkStreamWriter.h>
#include <vgKernel/vgkStreamReader.h>
#include <vgKernel/vgkCrcUtility.h>
#include <vgKernel/vgkStringUtility.h>
#include <vgKernel/vgkSystemUtility.h>
#include <vgImage/vgiCximageWrapper.h>
#include <vgImage/vgiFileWriterDdsToVgi.h>
#include <vgImage/vgiFreeImageWrapper.h>




namespace vgImage {
	
	
	using namespace vgKernel;
	
	vgTerritory::ptIndexMap* FileWriterVgi::s_pixelIndexMap = NULL;
	String FileWriterVgi::s_tempPathDir = "";
	String FileWriterVgi::s_ddsFistName = "";
	char* FileWriterVgi::s_backgroundPicBuf = NULL;


	//----------------------------------------------------------------
	bool FileWriterVgi::writeToVgiFile( 
		const vgKernel::StringVectorPtr input_texnames , 
		const String& output_filename  , const long& nextfileid )
	{

		//------------------------------------------
		// 1.首先创建StringPairVector
		//------------------------------------------
		vgKernel::StringPairVectorPtr pairlist( 
			new vgKernel::StringPairVector );

		StringVector::iterator iter = input_texnames->begin();
		StringVector::iterator iter_end = input_texnames->end();

		for ( ; iter != iter_end ; ++iter )
		{
			pairlist->push_back( std::make_pair( *iter , *iter ) );
		}


		return writeToVgiFileWithRename( pairlist , output_filename , nextfileid );


#if 0

		if ( input_texnames.isNull() == true )
		{
			MessageBox( NULL , "输入纹理序列为空" , "Error" , MB_OK );
			return false;
		}

		if ( input_texnames->empty() == true )
		{
			return false;
		}

		//------------------------------------------
		// 1.首先对输入的序列做如下处理:
		//	-删除非dds文件
		//	-删除同名文件
		//------------------------------------------
		std::set<String> nameSet;

		{
			vgKernel::StringVector::iterator iter = input_texnames->begin();
			vgKernel::StringVector::iterator iter_end = input_texnames->end();

			for ( ; iter != iter_end ; ++iter )
			{
				if ( ImageUtility::findImageFileExtension( *iter ) == "dds" &&
					iter->empty() == false )
				{
					nameSet.insert( *iter );
				}
			}
		}
		

		//------------------------------------------
		// 2.创建写入文件Stream
		//------------------------------------------
		vgKernel::StreamWriterPtr pwriter = 
			vgKernel::StreamWriterFactory::createFromFile( output_filename , true );

		if ( pwriter.isNull() == true )
		{
			return false;
		}

		if ( pwriter->isValid() == false )
		{
			return false;
		}

		//------------------------------------------
		// 3.写头文件
		//------------------------------------------
		VgiHeader header;
		long filebegin = pwriter->tell();

		pwriter->write( &header , sizeof( header ) );

		vgImage::ImageManager& imgmgr = 
			vgImage::ImageManager::getSingleton();

		//------------------------------------------
		// 4.开始得到文件数据,并从文件数据得到briefs
		//------------------------------------------
		VgiBriefPtrVec briefs;
		vgKernel::StringVector validLIst;

		{
			std::set<String>::iterator iter = nameSet.begin();
			std::set<String>::iterator iter_end = nameSet.end();

			for ( ; iter != iter_end ; ++iter )
			{
				long writebegpos = pwriter->tell();

				ImageMiniature* img = imgmgr.getImageMiniature( *iter );

				if ( img == NULL )
				{
					continue;
				}

				IoRequestDumpImage request( img );
				request.sendRequestAndDoAsynHandlerFunc( true );

				VgiBrief* brief = request.getBriefFromBuffer();
				assert( brief != NULL );

				// 写入buf
				char* buf = request.getBuffer();
				long buf_len = request.getBufferSize();

				long writenum = pwriter->write( buf , buf_len );
				assert( writenum == buf_len );

				// 更新brief
				brief->_metaFileOffset = writebegpos;

				briefs.push_back( VgiBriefPtr( brief ) );
				validLIst.push_back( *iter );

				delete[] buf;
			}
		}

		assert( briefs.size() == validLIst.size() );
		//------------------------------------------
		// 5.写入briefs,并更新header
		//------------------------------------------
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
			VgiBriefPtrVec::iterator iter = briefs.begin();
			VgiBriefPtrVec::iterator iter_end = briefs.end();

			for ( ; iter != iter_end ; ++iter )
			{
				VgiBrief* curbrief = (*iter).getPointer();
				long writenum =pwriter->write( curbrief, sizeof( VgiBrief ));
				assert( writenum == sizeof( VgiBrief ) );
			}
		}


		//------------------------------------------
		// 6.开始计算校验码
		//------------------------------------------
		DWORD crcCode;

		CrcUtility::initCrc32Code( crcCode );

		// 校验header
		for ( int i = 0 ; i < sizeof( header ) ; ++ i )
		{
			CrcUtility::calculateCrc32Code( (char*)&header + i , crcCode );
		}

		// 校验数据区
		{
			StringVector::iterator iter = validLIst.begin();
			StringVector::iterator iter_end = validLIst.end();

			for ( ; iter != iter_end ; ++iter )
			{
				ImageMiniature* img = imgmgr.getImageMiniature( *iter );
				assert( img != NULL );

				IoRequestDumpImage request( img );
				request.sendRequestAndDoAsynHandlerFunc( true );

				char* buf = request.getBuffer();
				long buf_len = request.getBufferSize();

				for ( int  i = 0 ; i < buf_len ; ++ i )
				{
					CrcUtility::calculateCrc32Code( buf + i , crcCode );
				}

				delete[] buf;
			}
		}

		// 校验brief
		{
			VgiBriefPtrVec::iterator iter = briefs.begin();
			VgiBriefPtrVec::iterator iter_end = briefs.end();

			for ( ; iter != iter_end ; ++iter )
			{
				for ( int i = 0 ; i < sizeof( VgiBrief ) ; ++ i )
				{
					CrcUtility::calculateCrc32Code( (char*)(*iter).getPointer() + i , crcCode );
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
#if 0
		DWORD checkcode;
		bool getres = CrcUtility::getFileCrc32Code( output_filename , checkcode );
		assert( getres == true );

		if ( checkcode != 0xFFFFFFFF )
		{
			MessageBox( NULL , "文件校验失败,请重新保存." , "保存失败" , 
				MB_OK | MB_ICONINFORMATION );

			return false;
		}

#endif

		//------------------------------------------
		// 清理工作并生成report
		//------------------------------------------


		return true;

#endif

	}
	//----------------------------------------------------------------
	bool FileWriterVgi::writeToVgiFileFromTextureNames( 
		const vgKernel::StringVectorPtr input_texnames , 
		const String& output_filename )
	{
		//------------------------------------------
		// 1.首先创建StringPairVector
		//------------------------------------------
		vgKernel::StringPairVectorPtr pairlist( 
			new vgKernel::StringPairVector );

		StringVector::iterator iter = input_texnames->begin();
		StringVector::iterator iter_end = input_texnames->end();

		for ( ; iter != iter_end ; ++iter )
		{
			pairlist->push_back( std::make_pair( *iter , *iter ) );
		}


		return writeToVgiFromTexNamesWithRename( pairlist , output_filename );

#if 0
		//////////////////////////////////////////////////////////////////////////
		using namespace vgKernel;

		ImageManager& imgmgr = ImageManager::getSingleton();

		// 出错的文件队列
		StringVectorPtr err_files( new StringVector );

		//------------------------------------------
		// 做必要的检查
		//------------------------------------------
		if ( StringUtility::getFileExtension( output_filename ) != "vgi" )
		{
			return false;
		}
		if ( input_texnames.isNull() == true )
		{
			return false;
		}
		if ( input_texnames->empty() == true )
		{
			return false;
		}

		//------------------------------------------
		// 首先对输入的序列做如下处理:
		//	-删除非dds文件
		//	-删除同名文件
		//------------------------------------------
		StringVectorPtr input_dds( new StringVector );
		{
			std::set<String>* nameSet = new std::set<String>;

			vgKernel::StringVector::iterator iter = input_texnames->begin();
			vgKernel::StringVector::iterator iter_end = input_texnames->end();

			for ( ; iter != iter_end ; ++iter )
			{
				if ( ImageUtility::findImageFileExtension( *iter ) == "dds" &&
					iter->empty() == false )
				{
					nameSet->insert( *iter );
				}
			}

			input_dds->assign( nameSet->begin() , nameSet->end() );
			delete nameSet;
		}

		//------------------------------------------
		// 读取每个纹理文件,判断存在的同时,读入
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
			ImageMiniature* img = imgmgr.getImageMiniature( ddsvec[i] );

			if ( img == NULL )
			{
				err_files->push_back( ddsvec[i] );
				continue;
			}

			int filesize = img->getMetaFileSize();

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
				( i == split_list.size() - 1 ) ? 0 : i + 1 );

			if ( writeok == false )
			{
				return false;
			}
		}

		return true;


#if 0
		//------------------------------------------
		// 按文件数目存取的版本.
		//------------------------------------------
		using namespace vgKernel;

		//------------------------------------------
		// 做必要的检查
		//------------------------------------------
		if ( StringUtility::getFileExtension( output_filename ) != "vgi" )
		{
			return false;
		}

		if ( input_texnames->empty() == true )
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

		StringVector& in_names = *input_texnames.getPointer();

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
				curoutname , fileVec[i].first );

			if ( writeok == false )
			{
				return false;
			}
		}

		return true;
#endif


#endif

	}
	//----------------------------------------------------------------
	bool FileWriterVgi::writeToVgiFromTexNamesWithRename( 
		const vgKernel::StringPairVectorPtr texnames ,
		const String& output_filename )
	{
		using namespace vgKernel;

		ImageManager& imgmgr = ImageManager::getSingleton();

		// 出错的文件队列
		StringVectorPtr err_files( new StringVector );

		//------------------------------------------
		// 做必要的检查
		//------------------------------------------
		if ( StringUtility::getFileExtension( output_filename ) != "vgi" )
		{
			return false;
		}
		if ( texnames.isNull() == true )
		{
			return false;
		}
		if ( texnames->empty() == true )
		{
			return false;
		}

		//------------------------------------------
		// 首先对输入的序列做如下处理:
		//	-删除非dds文件
		//	-删除同名文件
		//------------------------------------------
		typedef std::map<String,String> StringMap;

		StringPairVectorPtr input_dds( new StringPairVector );
		{
			StringMap* nameSet = new StringMap;

			StringPairVector::iterator iter = texnames->begin();
			StringPairVector::iterator iter_end = texnames->end();

			for ( ; iter != iter_end ; ++iter )
			{
				if ( ImageUtility::findImageFileExtension( iter->first ) == "dds" &&
					iter->first.empty() == false )
				{
					nameSet->insert( std::make_pair( iter->first , iter->second ) );
				}
			}

			input_dds->assign( nameSet->begin() , nameSet->end() );
			delete nameSet;
		}

		//------------------------------------------
		// 读取每个纹理文件,判断存在的同时,读入
		// 文件的大小,然后可以判断如何切割vgi文件.
		//------------------------------------------
		uint64 wholesize = 0;		// 总共的文件大小.
		unsigned int one_vgi_size = 0;
		int cur_list_num = 0;

		typedef std::vector<StringPairVectorPtr> StringPairVecPtrVec;
		StringPairVecPtrVec split_list;

		int dds_size = input_dds->size();
		StringPairVector& ddsvec = *input_dds.getPointer();

		for ( int i = 0 ; i < dds_size ; ++ i )
		{
			ImageMiniature* img = imgmgr.getImageMiniature( ddsvec[i].first );

			if ( img == NULL )
			{
				err_files->push_back( ddsvec[i].first );
				continue;
			}

			int filesize = img->getMetaFileSize();

			if ( filesize == 0 )
			{
				err_files->push_back( ddsvec[i].first );
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
				split_list.push_back( StringPairVectorPtr( new StringPairVector() ) );
			}

			assert( cur_list_num < split_list.size() );

			// 最后插入
			split_list[ cur_list_num ]->push_back(
				std::make_pair( ddsvec[i].first , ddsvec[i].second ) );
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

			bool writeok = writeToVgiFileWithRename( split_list[i] , 
				curoutname , 
				( i == split_list.size() - 1 ) ? 0 : i + 1 );

			if ( writeok == false )
			{
				return false;
			}
		}

		return true;
	}

	//----------------------------------------------------------------
	bool FileWriterVgi::writeToVgiFromTexNamesWithRename( 
		const vgKernel::StringPairVectorPtr texnames , 
		const String& output_filename, 
		vgTerritory::ptIndexMap* pixelIndexMap )
	{
		using namespace vgKernel;
		
		assert( pixelIndexMap != NULL );
		s_pixelIndexMap = pixelIndexMap;

		s_ddsFistName = 
			StringUtility::getFilenameWithoutExtFromAbsPath( output_filename );
		assert( s_ddsFistName != "" );

		ImageManager& imgmgr = ImageManager::getSingleton();


		// 出错的文件队列
		StringVectorPtr err_files( new StringVector );

		//------------------------------------------
		// 做必要的检查
		//------------------------------------------
		if ( StringUtility::getFileExtension( output_filename ) != "vgi" )
		{
			return false;
		}
		if ( texnames.isNull() == true )
		{
			return false;
		}
		if ( texnames->empty() == true )
		{
			return false;
		}

		//------------------------------------------
		// 首先对输入的序列做如下处理:
		//	-删除非dds文件
		//	-删除同名文件
		//------------------------------------------
		typedef std::map<String,String> StringMap;

		StringPairVectorPtr input_dds( new StringPairVector );
		{
			StringMap* nameSet = new StringMap;

			StringPairVector::iterator iter = texnames->begin();
			StringPairVector::iterator iter_end = texnames->end();

			for ( ; iter != iter_end ; ++iter )
			{
				if ( ImageUtility::findImageFileExtension( iter->first ) == "dds" &&
					iter->first.empty() == false )
				{
					nameSet->insert( std::make_pair( iter->first , iter->second ) );
				}
			}

			input_dds->assign( nameSet->begin() , nameSet->end() );
			delete nameSet;
		}

		//------------------------------------------
		// 读取每个纹理文件,判断存在的同时,读入
		// 文件的大小,然后可以判断如何切割vgi文件.
		//------------------------------------------
		uint64 wholesize = 0;		// 总共的文件大小.
		unsigned int one_vgi_size = 0;
		int cur_list_num = 0;

		typedef std::vector<StringPairVectorPtr> StringPairVecPtrVec;
		StringPairVecPtrVec split_list;

		int dds_size = input_dds->size();
		StringPairVector& ddsvec = *input_dds.getPointer();

		for ( int i = 0 ; i < dds_size ; ++ i )
		{
			ImageMiniature* img = imgmgr.getImageMiniature( ddsvec[i].first );
			
			if ( img == NULL )
			{
				err_files->push_back( ddsvec[i].first );
				continue;
			}

			int filesize = img->getMetaFileSize();

			if ( filesize == 0 )
			{
				err_files->push_back( ddsvec[i].first );
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
				split_list.push_back( StringPairVectorPtr( new StringPairVector() ) );
			}

			assert( cur_list_num < split_list.size() );

			// 最后插入
			split_list[ cur_list_num ]->push_back(
				std::make_pair( ddsvec[i].first , ddsvec[i].second ) );
		}

		//------------------------------------------
		// 开始保存
		//------------------------------------------
		String metaname =
			StringUtility::getFilenameWithoutExtFromAbsPath( output_filename );
		String path = StringUtility::getPathFromAbsoluteFilename( output_filename );

		// 申请一块内存置为背景颜色，待保存完vgi后释放
		if ( split_list.size() > 0 )
		{
			vgKernel::StringPairVector::iterator iter = split_list[0]->begin();
			setBackgroundPicBuf( iter->first );
		}


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

			// 此步将选区外的纹理像素置为背景色，并生成dds文件
			vgKernel::StringVector resultDdsVec;
			bool setok = dealTextureData( split_list[i], resultDdsVec );

			if ( !setok )
			{
				String msg = "设置选区外的纹理像素时出错！";
				vgKernel::SystemUtility::showModelDialog( msg );
				return false;
			}

			// 将dds文件写入到vgi中
			vgImage::FileWriterDdsToVgi vgiwriter;

			vgKernel::StringVectorPtr strVecPtr( new StringVector );
			for ( int i = 0; i < resultDdsVec.size(); i++ )
			{
				strVecPtr->push_back( resultDdsVec[i] );
			}

			vgiwriter.writeToVgiFileFromDdsNames(
				strVecPtr, output_filename, false );

		}

		// 移除临时目录
		assert( s_tempPathDir != "" );
		if ( s_tempPathDir == "" )
		{
			return false;
		}

		bool exist = vgKernel::SystemUtility::checkDirectoryExist( s_tempPathDir );
		if ( exist )
		{
			bool removeOk = vgKernel::SystemUtility::removeDirectory( s_tempPathDir );
			if ( !removeOk )
			{
				String msg = "移除临时目录失败！";
				vgKernel::SystemUtility::showModelDialog( msg );
				return false;
			}
		}

		// 将参数置为初始化
		s_pixelIndexMap = NULL;
		s_tempPathDir = "";
		s_ddsFistName = "";

		if ( s_backgroundPicBuf != NULL )
		{
			delete[] s_backgroundPicBuf;
			s_backgroundPicBuf = NULL;
		}

		return true;
	}

	//----------------------------------------------------------------
	bool FileWriterVgi::writeToVgiFileWithRename( 
		const vgKernel::StringPairVectorPtr texnames ,
		const String& output_filename , const long& nextfileid )
	{
		if ( texnames.isNull() == true )
		{
			MessageBox( NULL , "输入纹理序列为空" , "Error" , MB_OK );
			return false;
		}

		if ( texnames->empty() == true )
		{
			return false;
		}

		//------------------------------------------
		// 1.首先对输入的序列做如下处理:
		//	-删除非dds文件
		//	-删除同名文件
		//------------------------------------------
		typedef std::map<String, String> StringMap;
		StringMap nameSet;
		StringVector errList;

		{
			vgKernel::StringPairVector::iterator iter = texnames->begin();
			vgKernel::StringPairVector::iterator iter_end = texnames->end();

			for ( ; iter != iter_end ; ++iter )
			{
				if ( ImageUtility::findImageFileExtension( iter->first ) == "dds" &&
					iter->first.empty() == false &&
					iter->second.size() < VGI_NAME_LENGTH - 1 )
				{
					nameSet.insert(  std::make_pair( iter->first , iter->second ) );
				}
				else
				{
					errList.push_back( iter->first );
				}
			}
		}

		if ( nameSet.empty() == true )
		{
			return false;
		}

		//------------------------------------------
		// 2.创建写入文件Stream
		//------------------------------------------
		vgKernel::StreamWriterPtr pwriter = 
			vgKernel::StreamWriterFactory::createFromFile( output_filename , true );

		if ( pwriter.isNull() == true )
		{
			return false;
		}

		if ( pwriter->isValid() == false )
		{
			return false;
		}

		//------------------------------------------
		// 3.写头文件
		//------------------------------------------
		VgiHeader header;
		long filebegin = pwriter->tell();

		pwriter->write( &header , sizeof( header ) );

		vgImage::ImageManager& imgmgr = 
			vgImage::ImageManager::getSingleton();

		//------------------------------------------
		// 4.开始得到文件数据,并从文件数据得到briefs
		//------------------------------------------
		VgiBriefPtrVec briefs;
		vgKernel::StringVector validLIst;

		{
			StringMap::iterator iter = nameSet.begin();
			StringMap::iterator iter_end = nameSet.end();

			for ( ; iter != iter_end ; ++iter )
			{
				long writebegpos = pwriter->tell();

				ImageMiniature* img = imgmgr.getImageMiniature( iter->first );

				if ( img == NULL )
				{
					errList.push_back( iter->first );
					continue;
				}

				IoRequestDumpImage request( img );
				request.sendRequestAndDoAsynHandlerFunc( true );

				VgiBrief* brief = request.getBriefFromBuffer();
				assert( brief != NULL );

				//------------------------------------------
				// 注意在这里改名
				//------------------------------------------
				if ( iter->second.size() > VGI_NAME_LENGTH - 1 )
				{
					errList.push_back( iter->first );
					continue;
				}

				StringUtility::toLowerCase( iter->second );
				strcpy( brief->_fileName , iter->second.c_str() );
				assert( brief->_fileName[ VGI_NAME_LENGTH - 1 ] == 0 );

				//------------------------------------------
				// 开始写入buffer
				//------------------------------------------
				// 写入buf
				char* buf = request.getBuffer();
				long buf_len = request.getBufferSize();

				long writenum = pwriter->write( buf , buf_len );
				assert( writenum == buf_len );

				// 更新brief
				brief->_metaFileOffset = writebegpos;

				briefs.push_back( VgiBriefPtr( brief ) );
				validLIst.push_back( iter->first );

				delete[] buf;
				buf = NULL;
			}
		}

		assert( briefs.size() == validLIst.size() );
		//------------------------------------------
		// 5.写入briefs,并更新header
		//------------------------------------------
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
			VgiBriefPtrVec::iterator iter = briefs.begin();
			VgiBriefPtrVec::iterator iter_end = briefs.end();

			for ( ; iter != iter_end ; ++iter )
			{
				VgiBrief* curbrief = (*iter).getPointer();
				long writenum =pwriter->write( curbrief, sizeof( VgiBrief ));
				assert( writenum == sizeof( VgiBrief ) );
			}
		}


		//------------------------------------------
		// 6.开始计算校验码
		//------------------------------------------
		DWORD crcCode;

		CrcUtility::initCrc32Code( crcCode );

		// 校验header
		for ( int i = 0 ; i < sizeof( header ) ; ++ i )
		{
			CrcUtility::calculateCrc32Code( (char*)&header + i , crcCode );
		}

		// 校验数据区
		{
			StringVector::iterator iter = validLIst.begin();
			StringVector::iterator iter_end = validLIst.end();

			for ( ; iter != iter_end ; ++iter )
			{
				ImageMiniature* img = imgmgr.getImageMiniature( *iter );
				assert( img != NULL );

				IoRequestDumpImage request( img );
				request.sendRequestAndDoAsynHandlerFunc( true );

				char* buf = request.getBuffer();
				long buf_len = request.getBufferSize();

				for ( int  i = 0 ; i < buf_len ; ++ i )
				{
					CrcUtility::calculateCrc32Code( buf + i , crcCode );
				}

				delete[] buf;
				buf = NULL;
			}
		}

		// 校验brief
		{
			VgiBriefPtrVec::iterator iter = briefs.begin();
			VgiBriefPtrVec::iterator iter_end = briefs.end();

			for ( ; iter != iter_end ; ++iter )
			{
				for ( int i = 0 ; i < sizeof( VgiBrief ) ; ++ i )
				{
					CrcUtility::calculateCrc32Code( (char*)(*iter).getPointer() + i , crcCode );
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
#if 0
		DWORD checkcode;
		bool getres = CrcUtility::getFileCrc32Code( output_filename , checkcode );
		assert( getres == true );

		if ( checkcode != 0xFFFFFFFF )
		{
			MessageBox( NULL , "文件校验失败,请重新保存." , "保存失败" , 
				MB_OK | MB_ICONINFORMATION );

			return false;
		}

#endif

		//------------------------------------------
		// 清理工作并生成report
		//------------------------------------------
		if ( errList.empty() == false )
		{
			std::ostringstream o;
			o << "下列纹理没有查找到对应的输入项, 或者文件名格式不正确, 其输出已被忽略.\n";

			StringVector::iterator iter = errList.begin();
			StringVector::iterator iter_end = errList.end();

			for ( ; iter != iter_end ; ++ iter )
			{
				o << *iter << ", ";
			}

			MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd , 
				o.str().c_str() , "提示", MB_OK );
		}


		return true;
	}
	//----------------------------------------------------------------
	bool FileWriterVgi::dealTextureData( 
		const vgKernel::StringPairVectorPtr texnames,
		vgKernel::StringVector& outVec )
	{
		if ( texnames.isNull() == true )
		{
			String msg = "输入纹理序列为空!";
			vgKernel::SystemUtility::showModelDialog( msg );
			return false;
		}

		if ( texnames->empty() == true )
		{
			return false;
		}

		//------------------------------------------
		// 1.首先对输入的序列做如下处理:
		//	-删除非dds文件
		//	-删除同名文件
		//------------------------------------------
		typedef std::map<String, String> StringMap;
		StringMap nameSet;
		StringVector errList;

		{
			vgKernel::StringPairVector::iterator iter = texnames->begin();
			vgKernel::StringPairVector::iterator iter_end = texnames->end();

			for ( ; iter != iter_end ; ++iter )
			{
				if ( ImageUtility::findImageFileExtension( iter->first ) == "dds" &&
					iter->first.empty() == false &&
					iter->second.size() < VGI_NAME_LENGTH - 1 )
				{
					nameSet.insert(  std::make_pair( iter->first , iter->second ) );
				}
				else
				{
					errList.push_back( iter->first );
				}
			}
		}

		if ( nameSet.empty() == true )
		{
			return false;
		}


		//------------------------------------------
		// 2. 根据dds数据生成纹理贴图 
		//------------------------------------------
		vgImage::ImageManager& imgmgr = 
			vgImage::ImageManager::getSingleton();
		StringMap::iterator iter = nameSet.begin();
		StringMap::iterator iter_end = nameSet.end();

		for ( ; iter != iter_end ; ++iter )
		{
			ImageMiniature* img = imgmgr.getImageMiniature( iter->first );

			if ( img == NULL )
			{
				errList.push_back( iter->first );
				continue;
			}

			IoRequestDumpImage request( img );
			request.sendRequestAndDoAsynHandlerFunc( true );

			char* buf = request.getBuffer();
			buf += 128;  // 跳过dds文件头的128个字节

			long buf_len = request.getBufferSize();
			buf_len -= 128;

			int lod = 2;
			GLuint textureId =  img->createTextureID( buf, buf_len, lod );  // 用dds数据生成纹理

			// 此时buf内存可释放
			buf -= 128;
			delete[] buf;
			buf = NULL;

			long buf_size = img->getHeight()*img->getWidth()*3; // RGB模式 每像素占3字节

			char* src_buffer = new char[buf_size];
			char* dst_buffer = new char[buf_size];
			memset( src_buffer, 0, buf_size );
			memset( dst_buffer, 0, buf_size );

			assert( s_backgroundPicBuf != NULL );
			memcpy( dst_buffer, s_backgroundPicBuf, buf_size );

			// 根据纹理ID把纹理数据读到内存中以便操作
			getTexDataFormTexture( textureId, src_buffer, img->getWidth() ); // 宽度=高度

			// 根据像素索引置被索引的像素为背景色
			setPixelColor( src_buffer, dst_buffer, img->getMetaFileName(), img->getWidth() );

			// 将内存中的像素数据存成dds文件,返回dds的绝对路径
			String dds_abs_path = saveDataToDds( dst_buffer, img->getMetaFileName(), img->getWidth() );
			if ( dds_abs_path == "" )
			{
				String msg = "bmp转dds失败！";
				vgKernel::SystemUtility::showModelDialog( msg );
				return false;
			}

			outVec.push_back( dds_abs_path );

		}


		return true;
	}

	//----------------------------------------------------------------
	void FileWriterVgi::setBackgroundPicBuf( String ddsName )
	{
		ImageManager& imgmgr = ImageManager::getSingleton();
		ImageMiniature* img = imgmgr.getImageMiniature( ddsName );
		
		assert( img != NULL );
		if ( img == NULL )
		{
			return;
		}
		
		long buf_size = img->getWidth()*img->getHeight()*3;
		s_backgroundPicBuf = new char[buf_size];
		memset( s_backgroundPicBuf, 0, buf_size );

		for ( int i = 0; i < buf_size / 3; i++ )
		{
			s_backgroundPicBuf[3*i]   = 256*0.5;
			s_backgroundPicBuf[3*i+1] = 256*0.6;
			s_backgroundPicBuf[3*i+2] = 256*0.8;
		}
	}

	//----------------------------------------------------------------
	bool FileWriterVgi::getTexDataFormTexture( GLuint texId, char* src_buf, int texWidth )
	{
		assert( texId != 0 );
		assert( src_buf != NULL );

		if ( texId == 0 || src_buf == NULL )
		{
			return false;
		}

		glBindTexture( GL_TEXTURE_2D , texId );

		glGetTexLevelParameteriv( GL_TEXTURE_2D , 0 , GL_TEXTURE_WIDTH , &texWidth );
		glGetTexLevelParameteriv( GL_TEXTURE_2D , 0 , GL_TEXTURE_HEIGHT , &texWidth );

		// 从纹理中读取数据到内存buf中
		glGetTexImage( GL_TEXTURE_2D , 0 , GL_RGB , GL_UNSIGNED_BYTE , src_buf );

		// 此处的纹理ID是为了读纹理数据读到内存中，故读完后应马上释放纹理占有的显存
		glDeleteTextures( 1, &texId );

		return true;
	}

	//----------------------------------------------------------------
	bool FileWriterVgi::setPixelColor( char* src_buf, char* dst_buf, String ddsName, int texWidth )
	{
		assert( src_buf != NULL );
		assert( dst_buf != NULL );
		assert( ddsName != "" );
		
		if ( src_buf == NULL || dst_buf == NULL || ddsName == "" )
		{
			return false;
		}

		// bmp左下角为第一个像素，故需镜像取值
		// des左上角取src左下角；des右上角取src右下角
		vgTerritory::ptIndexMap::iterator itr = s_pixelIndexMap->find( ddsName );

		if ( itr != s_pixelIndexMap->end() )
		{
			vgTerritory::ptIndexVec* indexVec = itr->second;
			assert( indexVec != NULL );

			for ( int i = 0; i < indexVec->size(); i++ )
			{
				int des_index = indexVec->at(i);

				int picRow = des_index / texWidth;
				int picCol = des_index % texWidth;

				int src_index = ( texWidth - 1 - picRow )*texWidth + picCol;

				dst_buf[3*des_index]    = src_buf[3*src_index];   //背景色R分量 
				dst_buf[3*des_index+1]  = src_buf[3*src_index+1]; //背景色G分量
				dst_buf[3*des_index+2]  = src_buf[3*src_index+2]; //背景色B分量
			}
		}
		else // 纹理无需切割，整张保存
		{
			memcpy( dst_buf, src_buf, texWidth*texWidth*3 );
			
			int size = texWidth*3;
			char* temp = new char[size];
			memset( temp, 0, size );

			for ( int i = 0; i < texWidth / 2; i++ )
			{
				char* pa = dst_buf + i * size;
				char* pb = dst_buf + ( texWidth - 1 - i ) * size;

				memcpy( temp, pa, size );
				memcpy( pa, pb, size );
				memcpy( pb, temp, size );
			}
		}

		// 不再需要src数据，释放内存
		delete[] src_buf;
		src_buf = NULL;

		return true;
	}

	//----------------------------------------------------------------
	String FileWriterVgi::saveDataToDds( const char* dst_buf, String ddsFileName, int texWidth )
	{
		assert( dst_buf != NULL );
		assert( ddsFileName != "" );

		if ( dst_buf == NULL || ddsFileName == "" )
		{
			return "";
		}

		//================================================================
		// 1. 先将数据保存成bmp文件
		vgImage::CximageWrapper bmpimg;
		bmpimg.createFromArray( (void*)dst_buf, texWidth, texWidth, 24, true, true );

			// 在系统临时目录建立文件夹
		String sysTempPath = vgKernel::SystemUtility::getSystemTempPath();
		String abs_path = sysTempPath + "\\bmpForCutScene";

		s_tempPathDir = abs_path; // 用于移除前一步建立临时文件夹

		bool exist = vgKernel::SystemUtility::checkDirectoryExist( abs_path );
		if ( !exist )
		{
			bool creatOk = vgKernel::SystemUtility::createDirectory( abs_path );
			if ( !creatOk )
			{
				String msg = "在系统临时目录建立文件夹失败！";
				vgKernel::SystemUtility::showModelDialog( msg );
				return "";
			}
		}

			// 确定bmp文件名称
		String fileNameWithoutExt = vgKernel::StringUtility::getFilenameWithoutExtension( ddsFileName );
		String bmp_name = fileNameWithoutExt + ".bmp";

			// 保存内存中的数据到指定目录的bmp文件
		String abs_bmp = abs_path + "\\" + bmp_name;
		bmpimg.saveToFile( abs_bmp );


		delete[] dst_buf;
		dst_buf = NULL;


		//================================================================
		// 2. 将bmp文件转换成dds文件
		FreeImageWrapper img;
			
			// 加载bmp文件
		bool loadok = img.loadFromFile( abs_bmp );
		if ( loadok == false )
		{
			return "";
		}
			
			// 此处dds文件的名称需与vtr中vgtr的纹理名一至
		// 现在是硬编码为类terrain_level0-9-7.dds
		String dds_otherName = fileNameWithoutExt + ".dds";
		String::size_type pos = dds_otherName.find_first_of( "_");
		dds_otherName = dds_otherName.substr( pos );

		String dds_name = s_ddsFistName + dds_otherName;
		String abs_dds = abs_path + "\\" + dds_name;
			
			// 按指定格式保存到指定目录的dds文件
		GLenum dds_format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT; //DXT1的压缩方式

		bool saveok = img.saveToDdsFile( abs_dds , dds_format , true );
		if ( saveok == false )
		{
			String msg = "保存dds文件失败！";
			vgKernel::SystemUtility::showModelDialog( msg );
			return "";
		}


		//================================================================
		// 3. 移除bmp文件
		bool removeOk = vgKernel::SystemUtility::removeFile( abs_bmp, true );
		if ( !removeOk )
		{
			String msg = "移除bmp文件失败!";
			vgKernel::SystemUtility::showModelDialog( msg );
			return "";
		}

		return abs_dds;
	}


}// end of namespace vgImage

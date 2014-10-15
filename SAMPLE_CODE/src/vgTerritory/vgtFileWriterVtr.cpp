



#include <vgStableHeaders.h>
#include <vgTerritory/vgtFileWriterVtr.h>
#include <vgTerritory/vgtFileHandleVtr.h>
#include <vgTerritory/vgtDefinition.h>
#include <vgImage/vgiFileWriterVgi.h>
#include <vgKernel/vgkCrcUtility.h>
#include <vgKernel/vgkStringUtility.h>

#include <vgTerritory/vgtTerrainManager.h>
#include <vgTerritory/vgtCutArea.h>
#include <gdal/ogr_geometry.h>
#include <vgKernel/vgkSystemUtility.h>

namespace vgTerritory {
	
	

	//----------------------------------------------------------------
	bool FileWriterVtr::writeToVtrFromItemsWithoutDecomposition(
		const VtrHeaderPtr input_new_vtrheader,
		const long& next_fileid,
		const ElevationItemVectorPtr pitems , 
		const String& out_filepath )
	{
		using namespace vgAsyn;

		if ( pitems.isNull() == true || input_new_vtrheader.isNull() == true )
		{
			return false;
		}

		if ( pitems->empty() == true )
		{
			return false;
		}

		if ( out_filepath.empty() == true )
		{
			return false;
		}

#if _DEBUG

		{
			std::set<String> names;

			ElevationItemVector::iterator iter = pitems->begin();
			ElevationItemVector::iterator iter_end = pitems->end();

			for ( ; iter != iter_end ; ++ iter )
			{
				ElevationItem* itm = *iter;

				if ( itm->isEmptyItem() == true )
				{
					assert(0);
				}

				std::pair< std::set<String>::iterator , bool> res = names.insert( itm->getName() );

				if ( res.second == false )
				{
					assert(0);
				}
			}
		}

#endif

		//------------------------------------------
		// 确定process的进度条
		// 最后加2分别是文件开始的工作和文件收尾的工作
		//------------------------------------------
		int processCounter = 0;
		this->notifyProcessObserversStart( "开始生成vtr文件..." ,0,
			pitems->size() - 1 + 2);

		//------------------------------------------
		// 检查是否覆盖文件
		//------------------------------------------
		String out_fileabsname = out_filepath + "\\" +
			input_new_vtrheader->name + ".vtr";

		vgKernel::StreamWriterPtr pwriter = 
			vgKernel::StreamWriterFactory::createFromFile( out_fileabsname ,true );

		if ( pwriter.isNull() == true )
		{
			return false;
		}

		if ( pwriter->isValid() == false )
		{
			return false;
		}

		this->notifyProcessObserversPos( "开始写vtr文件" , processCounter ++ );





		//////////////////////////////////////////////////////////////////////////
		//------------------------------------------
		// 其次开始写文件
		//------------------------------------------
		VtrHeader header;
		
		std::vector<VtrBrief*> briefs;
		vgKernel::StringVector errList;
		ElevationItemVector validItemList;

		//------------------------------------------
		// 最开始对header进行赋值
		//------------------------------------------
		VtrHeader* inputheader = input_new_vtrheader.getPointer();

		// 直接利用operator = 进行赋值操作.
		header = *inputheader;

		// _nextVtrFileID域需要更改.
		header._nextVtrFileID = next_fileid;

		String terrainName = header.name;

		//------------------------------------------
		// 1.先预写一边header
		// brief写在最后即可.
		//------------------------------------------
		long filebegin = pwriter->tell();
		assert( filebegin == 0 );
		pwriter->write( &header , sizeof( header ) );

		// 写data数据区
		{
			ElevationItemVector::iterator iter = pitems->begin();
			ElevationItemVector::iterator iter_end = pitems->end();


			for ( ; iter != iter_end ; ++ iter )
			{
				ElevationItem* itm = *iter;

				this->notifyProcessObserversPos( "正在处理:" + itm->getName()  , 
					processCounter ++ );

				FileInfo* wholefileinfo = itm->getMetaFileInfoClone();

				IoRequest req( wholefileinfo );

				// 一定要设置同步模式.
				req.setAsynchronousMode( false );
				req.sendRequestAndDoAsynHandlerFunc( true );

				char* buffer_pointer = req.getBuffer();
				assert( buffer_pointer != NULL );
				long buffer_size = req.getBufferSize();

				//------------------------------------------
				// 查找到新的名称
				//------------------------------------------
				std::ostringstream o;
				o << terrainName << "_level" << itm->getLevel() <<  "_" << itm->getBlockNumberX() 
					<< "_" << itm->getBlockNumberZ();

				String prefix = o.str();
				String newname = prefix + ".vgtr";

				// 创建brief
				VtrBrief* brief = new VtrBrief;
				bool getinfores = 
					brief->getInfoFromBuffer( newname , buffer_pointer , buffer_size );

				if ( getinfores == false )
				{
					delete brief;
					errList.push_back( itm->getName() );
					continue;
				}

				//------------------------------------------
				// 注意,在这里,需要更改每个brief的texture filename
				//------------------------------------------
				String texname = prefix + ".dds";
				strcpy( brief->_vgtrHeader.texname , texname.c_str() );

				// 写入文件
				long metafilebegin = pwriter->tell();
				brief->_metaFileOffset = metafilebegin;

				// 将选区之外点的高程置零
				setUnSelectAreaHeightToZERO( buffer_pointer, itm );

				long writenum = pwriter->write( (void*)buffer_pointer , buffer_size );
				assert( writenum == buffer_size );

				if ( writenum != buffer_size )
				{
					MessageBox( NULL , "致命错误" , "Error" , MB_OK );
					return false;
				}

				// 插入队列
				briefs.push_back( brief );
				validItemList.push_back( itm );
			}

		} // 写data区域结束.


		//------------------------------------------
		// 开始更新header
		//------------------------------------------
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

			ElevationItemVector::iterator iter = validItemList.begin();
			ElevationItemVector::iterator iter_end = validItemList.end();

			for ( ; iter != iter_end ; ++ iter )
			{
				ElevationItem* itm = *iter;

				FileInfo* wholefileinfo = itm->getMetaFileInfoClone();

				IoRequest req( wholefileinfo );

				// 一定要设置同步模式.
				req.setAsynchronousMode( false );
				req.sendRequestAndDoAsynHandlerFunc( true );

				char*  buffer_pointer = req.getBuffer();
				assert( buffer_pointer != NULL );

				ptIndexMap::iterator itr = m_pointIndexMap.find( itm->getMetaFilename() );
				if ( itr != m_pointIndexMap.end() )
				{
					bool bOk = 
					setHeightToZEROFromIndexVec( buffer_pointer, itm, req.getBufferSize(), itr->second );

					if ( !bOk )
					{
						String msg = "校验数据区高程置0错误";
						vgKernel::SystemUtility::showModelDialog( msg );
						return false;
					}
				}

				long buffer_size = req.getBufferSize();

				for ( int  i = 0 ; i < buffer_size ; ++ i )
				{
					vgKernel::CrcUtility::calculateCrc32Code( buffer_pointer + i , crcCode );
				}
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
		
		clearPointIndexMap();

		//------------------------------------------
		// 开始检查文件正确性
		// 这一步应该由外部的应用程序完成
		// 比如提示:已完成, 正在校验中....
		//------------------------------------------
#if 1
		DWORD checkcode;
		bool getres = vgKernel::CrcUtility::getFileCrc32Code( out_fileabsname , checkcode );
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
	bool FileWriterVtr::writeToVtrFromItems( 
		const FileHandleVtr* const main_vtr_handle , 
		const String& terrain_name,
		const ElevationItemVectorPtr pitems , const String& out_filepath )
	{
		if ( main_vtr_handle == NULL )
		{
			return false;
		}

		String new_terrain_name = terrain_name;
		StringUtility::toLowerCase( new_terrain_name );

		if ( new_terrain_name.empty() == true )
		{
			return false;
		}

		if ( out_filepath.empty() == true )
		{
			return false;
		}
		if ( new_terrain_name.size() > VTR_NAME_LENGTH - 12 )
		{
			std::ostringstream o;
			o << "文件名过长:" << new_terrain_name;
			MessageBox( NULL  , o.str().c_str() , "出错", MB_OK	 );

			return false;
		}

		VtrHeaderPtr oldheader = main_vtr_handle->getHeader();
		assert( oldheader.isNull() == false );
		if ( oldheader.isNull() == true )
		{
			return false;
		}

		VtrHeaderPtr headercopy( new VtrHeader );

		( *headercopy ) = *(oldheader.getPointer());

		memset( headercopy->name , 0 , VTR_NAME_LENGTH );
		assert( new_terrain_name.size() < VTR_NAME_LENGTH - 1 );
		strcpy( headercopy->name , new_terrain_name.c_str() );

		//------------------------------------------
		// 更改imagefilename
		//------------------------------------------
		String vginame = new_terrain_name + ".vgi";
		memset( headercopy->imageFilename , 0 , VTR_NAME_LENGTH );
		assert( vginame.size() < VTR_NAME_LENGTH - 1 );
		strcpy( headercopy->imageFilename , vginame.c_str() );

		return writeToVtrFromItems( headercopy, pitems , out_filepath );
	}
	//----------------------------------------------------------------
	bool FileWriterVtr::writeToVtrFromItems( 
		const VtrHeaderPtr input_new_vtrheader, 
		const ElevationItemVectorPtr pitems ,
		const String& out_filepath )
	{
		if ( input_new_vtrheader.isNull() == true )
		{
			return false;
		}

		String terrainname = input_new_vtrheader->name;

		if ( terrainname.empty() == true )
		{
			return false;
		}

		//------------------------------------------
		// 先写vtr文件
		//------------------------------------------
		bool writevtrok =  writeToVtrFromItemsImplement( pitems, out_filepath, 
			input_new_vtrheader);

		if ( writevtrok == false )
		{
			std::ostringstream o;
			o << "写入vtr文件到路径:" << out_filepath  << " 时失败.";
			MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd , 
				o.str().c_str() , "提示" , MB_OK );

			return false;
		}

		//------------------------------------------
		// 然后写vgi文件.
		//------------------------------------------
		return writeToVgiForVtrFromItems( terrainname , pitems , out_filepath );
	}
	//----------------------------------------------------------------
	bool FileWriterVtr::writeToVgiForVtrFromItems( 
		const String& new_terrain_name , const ElevationItemVectorPtr pitems ,
		const String& out_filepath )
	{
		using namespace vgImage;

		//------------------------------------------
		// 做必要的检查
		//------------------------------------------
		if ( pitems.isNull() == true )
		{
			return false;
		}
		if ( pitems->empty() == true )
		{
			return false;
		}

		if ( new_terrain_name.empty() == true || 
			out_filepath.empty() == true )
		{
			return false;
		}
		//------------------------------------------
		// 首先构建pairs
		//------------------------------------------
		StringPairVectorPtr pairlist( new StringPairVector );

		ElevationItemVector::iterator iter = pitems->begin();
		ElevationItemVector::iterator iter_end= pitems->end();

		for ( ; iter != iter_end ; ++ iter )
		{
			ElevationItem* itm = *iter;

			String oldname = itm->getTextureName();

			std::ostringstream o;
			o << new_terrain_name << "_level" << itm->getLevel()
				<< "_" << itm->getBlockNumberX() 
				<< "_" << itm->getBlockNumberZ() << ".dds";

			String newname = o.str();

			pairlist->push_back( std::make_pair( oldname , newname ) );
		}

		if ( pairlist->empty() == true )
		{
			return false;
		}

		//------------------------------------------
		// 开始保存纹理.
		//------------------------------------------
		String vgifilename  = out_filepath + "\\" + new_terrain_name + ".vgi";

		// 将m_pixelIndexMap中存储的索引对应的纹理像素数据置为背景色
		bool writeok = FileWriterVgi::writeToVgiFromTexNamesWithRename(
			pairlist , vgifilename, &m_pixelIndexMap );
		/*bool writeok = FileWriterVgi::writeToVgiFromTexNamesWithRename(
			pairlist , vgifilename );*/

		if ( writeok == false )
		{
			std::ostringstream o;
			o << "写入vgi文件:" << vgifilename  << " 失败.";
			MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd , 
				o.str().c_str() , "提示" , MB_OK );
			
			clearPixelIndexMap();
			return false;
		}

		// 清空用于设置纹理数据的像素索引数组
		clearPixelIndexMap();

		return true;
	}	
	//----------------------------------------------------------------
	bool FileWriterVtr::writeToVtrFromItemsImplement( 
		const ElevationItemVectorPtr &pitems, 
		const String &out_filepath, const VtrHeaderPtr input_new_vtrheader )
	{
		using namespace vgKernel;

		//------------------------------------------
		// 做必要的检查
		//------------------------------------------
		if ( pitems.isNull() == true )
		{
			return false;
		}
		if ( pitems->empty() == true )
		{
			return false;
		}

		if ( out_filepath.empty() == true )
		{
			return false;
		}


		// 存储需要保存的列表文件.
		// VtrPair中的int表示是下一个nextfileid.
		typedef std::pair<int,ElevationItemVectorPtr> VtrPair;
		typedef std::vector< VtrPair > VtrPairVec;
		//------------------------------------------
		// 首先检查输入的队列,如有必要,进行切块处理
		//------------------------------------------
		VtrPairVec fileVec;

		ElevationItemVector& in_names = *pitems.getPointer();

		int vtrnum = ( in_names.size() + VGT_VTR_MAX_FILENUM - 1 ) / VGT_VTR_MAX_FILENUM;


		for ( int i = 0 ; i < vtrnum ; ++ i )
		{
			ElevationItemVectorPtr strvec( new ElevationItemVector );
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
		String out_terrainname = input_new_vtrheader->name;
		String path = out_filepath;

		for ( int i = 0 ; i < fileVec.size() ; ++ i )
		{
			String curoutname;

			if ( i == 0 )
			{
				curoutname = path + "\\" + out_terrainname + ".vtr";
			}
			else
			{
				std::ostringstream o;
				o << path << "\\" << out_terrainname << ".part" << i << ".vtr";
				curoutname = o.str();
			}

			bool writeok = writeToVtrFromItemsWithoutDecomposition( 
				input_new_vtrheader , 
				fileVec[i].first , 
				fileVec[i].second , 
				out_filepath );

			if ( writeok == false )
			{
				return false;
			}
		}

		return true;
	}
	//----------------------------------------------------------------
	bool FileWriterVtr::setUnSelectAreaHeightToZERO( 
		char* buf, 
		ElevationItem* elevItem )
	{
		assert( buf != NULL );
		char* pBuffer = NULL;

		if ( elevItem->getStateWithInPolygon() )
		{
			return true;
		}

		float scale = pow( (float)2.0, ( elevItem->getLevel() + 1 ) );

		ptIndexVec* pPointVec = new ptIndexVec;
		ptIndexVec* pPixelVec = new ptIndexVec;

		int counter = -1;
		int rows = elevItem->getHeightMapWidth();
		
		OGRGeometry* pIntersectPoly = elevItem->getOgrPtr();

		for ( int i = 0; i < rows; i++ )
		{
			for ( int j = 0; j < rows; j++ )
			{
				counter ++;

				double dx = j % (rows-1); 
				double dz = i % (rows-1);

				if ( j != 0 && j % (rows-1) == 0 )
				{
					dx = rows - 1;
				}
				if ( i != 0 && i % (rows-1) == 0 )
				{
					dz = rows - 1;
				}

				double x = dx * elevItem->_displaceChunkScale * scale;
				double z = dz * elevItem->_displaceChunkScale * scale;

				OGRGeometry* pGeo = OGRGeometryFactory::createGeometry( wkbPoint );
				OGRPoint* pOgrPoint = dynamic_cast<OGRPoint*>( pGeo );

				pOgrPoint->setX( x );
				pOgrPoint->setY( z );

				OGRBoolean bIntersect = pOgrPoint->Intersect( pIntersectPoly );

				OGRGeometryFactory::destroyGeometry( pGeo );
				pGeo = NULL;

				if ( !bIntersect ) // 区域之外的点
				{
					pBuffer = buf + sizeof(VgtrHeader) + 8; // VgtrHeader后又写入8个字节数据
					pBuffer += counter * 4;

					*(float *)pBuffer = 0.0;
				} 
				else  
				{
					// 用于校验
					int pointIndex = i * rows + j;
					pPointVec->push_back( pointIndex );

					// 用于纹理
					int pixelIndex = 0;
					if ( i != ( rows - 1 )  )
					{
						pixelIndex = i * ( rows - 1 );
						pixelIndex += ( j != (rows-1) ) ? j : ( j - 1 );
					}
					else
					{
						pixelIndex = ( i - 1 ) * ( rows - 1 );
						pixelIndex += ( j != ( rows - 1 ) ) ? j : ( j - 1 );
					}
					pPixelVec->push_back( pixelIndex );
				}

			} // end for j

		} // end for i
		
		elevItem->setOgrGeoPtr( NULL ); // 恢复状态以备继续切块

		m_pointIndexMap.insert( std::make_pair( elevItem->getMetaFilename(), pPointVec ) );
		m_pixelIndexMap.insert( std::make_pair( elevItem->getTextureName(), pPixelVec ) );

		return true;
	}

	//----------------------------------------------------------------
	bool FileWriterVtr::setHeightToZEROFromIndexVec( char* buf, 
		ElevationItem* elevItem, int bufSize, const ptIndexVec* vec )
	{
		assert( buf != NULL );
		if ( buf == NULL )
		{
			return false;
		}

		if ( elevItem->getStateWithInPolygon() )
		{
			elevItem->setStateWithInPolygon( false ); // 恢复状态以备继续切块
			return true;
		}

		int headerSize = sizeof(VgtrHeader) + 8;
		char* pBuffer = buf + headerSize;

		// 拷贝原有内存数据
		int size = bufSize - headerSize;
		BYTE* copy = new BYTE[size];
		memset( copy, 0, size );
		memcpy( copy, pBuffer, size );

		// 将原始数据全部置零
		memset( pBuffer, 0, size );


		BYTE* pCopy = NULL;

		for ( int i = 0; i < vec->size(); i++ )
		{
			pBuffer = buf + headerSize;
			pCopy = copy;

			int index = vec->at(i);

			pBuffer += 4 * index;  // sizeof(float)=4个字节
			pCopy += 4 * index;
			*(float *)pBuffer = *(float *)pCopy;
		}

		delete[] copy;
		copy = NULL;

		return true;
	}

	//----------------------------------------------------------------
	void FileWriterVtr::clearPointIndexMap()
	{
		if ( m_pointIndexMap.size() > 0 )
		{
			ptIndexMap::iterator iter = m_pointIndexMap.begin();
			ptIndexMap::iterator iter_end = m_pointIndexMap.end();

			for ( ; iter != iter_end; iter++ )
			{
				if ( iter->second != NULL )
				{
					delete iter->second;
					iter->second = NULL;
				}

			} // end for

		} // end if size

		m_pointIndexMap.clear();
	}

	//----------------------------------------------------------------
	void FileWriterVtr::clearPixelIndexMap()
	{
		if ( m_pixelIndexMap.size() > 0 )
		{
			ptIndexMap::iterator iter = m_pixelIndexMap.begin();
			ptIndexMap::iterator iter_end = m_pixelIndexMap.end();

			for ( ; iter != iter_end; iter++ )
			{
				if ( iter->second != NULL )
				{
					delete iter->second;
					iter->second = NULL;
				}

			} // end for

		} // end if size
	}

}// end of namespace vgTerritory

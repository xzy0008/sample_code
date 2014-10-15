




#include <vgStableHeaders.h>
#include <vgTerritory/vgTerrainHugeImageProcessor.h>
#include <vgTerritory/vgtDefinition.h>
#include <vgImage/vgiFreeImageWrapper.h>


namespace vgTerritory {
	

	//----------------------------------------------------------------
	HugeImagesProcessor::~HugeImagesProcessor()
	{
		this->clear();
	}
	//----------------------------------------------------------------
	void HugeImagesProcessor::clear()
	{
		m_pFileNamesInfo.setNull();

		m_pAimsblocksOption.setNull();

		m_pfblockVector.setNull();

		m_pSmallblockLayout.setNull();
	}
	//----------------------------------------------------------------
	bool HugeImagesProcessor::checkFileExist( const String& filename )
	{
		std::fstream f( filename.c_str() ,std::fstream::in);
		if ( f.fail() )
		{
			return false;
		}
		f.close();
		return true;
	}
	//----------------------------------------------------------------
	bool HugeImagesProcessor::removeFile( const String& filename , const bool& iflog /*= true */)
	{
		/// use stdio.h 
		int ret_remove;

#ifdef UNICODE
		assert(0);
		ret_remove = ::remove( (StringUtil::convertWStringToString(filename)).c_str() );
#else
		ret_remove = ::remove( filename.c_str() );
#endif

		if ( ret_remove == 0 )
		{
			/// 此时成功返回
			if( iflog )
			{
				LogManager::getSingleton().logMessage( String( _T("File: ")) + filename + _T(" has been deleted."));
			}
			return true;
		}			
		else  
		{
			/// 未成功返回的情况.
			if ( iflog )
			{
				LogManager::getSingleton().logMessage( String( _T("When deleting ")) 
					+ filename + _T(" , failed. The file may be not exist or just in use"));
			}
			return false;
		}
	}

	//----------------------------------------------------------------
	bool HugeImagesProcessor::initSavingEnvironment( const fileBlockVector& fblockvec ,
		const AimSmallBlocksOption& aiminfo,
		const smallBlockVector& sblockLayout  )
	{
		const bool& deleteAllExistFiles = aiminfo.ifOverrideExist;
		const bool& iflog = aiminfo.ifLogInfo;

		int delcount = 0;

		/// 若选择保留所有的已存在文件,则返回
		if ( deleteAllExistFiles == false )
		{
			return true;
		}

		/// 不得不说下面某些文件可能检查了2次.但是考虑到override的时候并不是很多,
		/// 这里的效率稍微低了一点还是可以接受.

		if ( iflog )
		{
			LogManager::getSingleton().logMessage(
				 _T("============================== now begin deleting the exist files========================"));
		}

		/// 遍历fileblockvector文件目录,删除存在的文件(不包含从tmp生成的最终文件).
		for ( fileBlockVector::const_iterator pfblock = fblockvec.begin() ;
			pfblock != fblockvec.end() ;
			++ pfblock )
		{
			for ( smallBlockVector::const_iterator psblock = pfblock->taskList.begin() ;
				psblock != pfblock->taskList.end() ;
				++ psblock )
			{
				if ( checkFileExist( psblock->blockFileName ) )
				{
					if( !removeFile( psblock->blockFileName , iflog ) )
					{
						return false;
					}
					delcount ++;
				}
			}// end of psblock
		}// end of pfblock

		/// 遍历smallBlockLayout文件目录,删除存在的文件(包含从tmp生成的最终文件).
		for ( smallBlockVector::const_iterator i = sblockLayout.begin() ;
			i != sblockLayout.end() ;
			++ i )
		{
			if ( checkFileExist( i->blockFileName ) )
			{
				if( !removeFile( i->blockFileName , iflog ) )
				{
					return false;
				}
				delcount ++;
			}
		}

		/// 删除CombinedFileBlocks
		if ( aiminfo.ifOutputCombinedFileBlocks )
		{
			if ( checkFileExist( aiminfo.aimCombinedFBlockName ) )
			{
				if ( !removeFile( aiminfo.aimCombinedFBlockName , iflog ) )
				{
					return false;
				}
				delcount ++;
			}
		}

		/// 删除CombinedSmallBlocks
		if ( aiminfo.ifOutputCombinedSmallBlocks )
		{
			if ( checkFileExist( aiminfo.aimCombinedSBlockName ))
			{
				if ( !removeFile( aiminfo.aimCombinedSBlockName , iflog ))
				{
					return false;
				}
				delcount ++;
			}
		}

		/// 生成日志.
		if ( iflog )
		{
			LogManager::getSingleton().logMessage(
				 _T("============================== now end deleting the exist files : ")
				+ StringUtility::textCast(delcount) +  _T(" files deleted ") +
				 _T("========================"));
		}

		return true;
	}
	//----------------------------------------------------------------
	fileBlockVectorPtr HugeImagesProcessor::createFileblockLayout(
		const FileNamesInfo& fileinfo ,
		const AimSmallBlocksOption& aiminfo )
	{
		const std::vector<String> &stringVec = fileinfo.filenameVector;

		const long& col = fileinfo.columnNum;
		const long& row = fileinfo.rowNum;
		//const bool& ifkownsize = fileinfo.ifKnownSize;

		fileBlockVectorPtr  resultVector( new fileBlockVector );

		fileBlock		 fblock;
		ImagePos		 nowPos( 0 );
		ImageRect		 nowRect;

		for ( int y = 0 ; y < row ; ++ y )
		{
			for ( int x = 0 ; x < col ; ++ x )
			{
				/// 这里的越界检查是否是抛出异常???????
				const String &file = stringVec.at( y * col + x );

WARN_YES_AGAIN:
				/// 读入文件.
				if ( !readImageFileRect(file , nowRect))
				{
					int ret = VGK_WARN(Warning::WARN_FILE_NOT_FOUND ,
						Warning::BUTTON_ABORT_RETRY_IGNORE,
						 _T("读取文件") + file + _T("信息时出现错误,文件不存在或者已损坏,是否重试?"),
						 _T("HugeImagesProcessor::createFileblockLayout()"));

					if ( ret == Warning::RETURN_RETRY )
					{
						goto WARN_YES_AGAIN;
					}
					if ( ret == Warning::RETURN_ABORT )
					{
						VGK_EXCEPT(Exception::ERR_FILE_NOT_FOUND,
							 _T("读取文件大小信息时出现错误!文件不存在或者已损坏!"),
							 _T("HugeImagesProcessor::createFileblockLayout()"));
					}
					if ( ret == Warning::RETURN_IGNORE )
					{
						nowRect = ImageRect::ZERO;
					}
				}


				/// 赋值fblock.
				fblock.fileSrcName = file;
				fblock.fileAbsoluteRect = nowRect.translate( nowPos );

				/// 是否写入日志.
				if ( aiminfo.ifLogInfo )
				{
					LogManager &logmgr = LogManager::getSingleton();
					logmgr.logMessage( String( _T("handing File:")) + file );
				}

				resultVector->push_back( fblock );

				/// 更新位置.
				nowPos.x += nowRect.getWidth() ;

			}// end of x

			/// 更新位置.
			nowPos.x = 0;
			nowPos.y += nowRect.getHeight() ;

		}// end of y

		/// 是否写入日志.
		if ( aiminfo.ifLogInfo )
		{
			LogManager &logmgr = LogManager::getSingleton();
			logmgr.logMessage(
				 _T("================= now ready to print fileblockVector information ===================") );
			for ( fileBlockVector::const_iterator i = resultVector->begin() ;
				i != resultVector->end() ;
				++ i )
			{
				logmgr.logMessage( i->getDetails() );
			}
			logmgr.logMessage(
				 _T("================= end to print fileblockVector information ===================") );
		}

		return resultVector;
	}
	//----------------------------------------------------------------
	smallBlockVectorPtr HugeImagesProcessor::createDefaultSmallblockLayout( 
		const fileBlockVector& fblockvec , 
		const AimSmallBlocksOption& aiminfo )
	{
		LogManager &logmgr = LogManager::getSingleton();

		const long& widthAndHeightAddOne = aiminfo.widthAndHeightAddOne;

		/// 想要得到的block的信息.
		const ImagePos&  aim_offset			 = aiminfo.aimOffset;
		const long&	 aim_block_height	 =
			aiminfo.aimHeight;
		const long&	 aim_block_width	 = 
			aiminfo.aimWidth;

		const long&	 overlap			 = aiminfo.aimPixcelOverlap;
		const String&	 aim_block_filename	 = aiminfo.aimFilePrefix;
		const String&	 aim_ext			 = aiminfo.aimFilePostfix;
		const bool&      aim_log			 = aiminfo.ifLogInfo;

		
		

		const bool&		 aim_reversSeq		= aiminfo.ifReverseSequence;

		const long&   aim_sblock_layout_num = aiminfo.aimSmallBlocksNum;

		const ImageRect aim_block_rect ( 0 , 0 , aim_block_width , aim_block_height );

		/// 得到整个大图的长宽
		const ImageRect worldRect = fblockvec.getWorldImageRect();

		if ( aim_log )
		{
			logmgr.logMessage( String( _T("worldRect : ")) + worldRect.getDetails() );
		}

		/// 计算所需的blocks数.注意,这里计算了重叠数.

#if 0
		assert( aim_block_width  == aim_block_height );

		long blocks_num_x =  
			(worldRect.getWidth() + aim_block_width - 2 * overlap - 1) / (aim_block_width  - overlap);

		long blocks_num_y =  
			(worldRect.getHeight() + aim_block_height - 2 * overlap - 1) / (aim_block_height - overlap);

		blocks_num_x = blocks_num_y = VGT_MAX( blocks_num_x , blocks_num_y );

#else

		//------------------------------------------
		// 后来修改
		//------------------------------------------
		assert( aim_block_width  == aim_block_height );

		long blocks_num_x =  
			(worldRect.maxPos.x + aim_block_width - 2 * overlap - 1) / (aim_block_width  - overlap);

		long blocks_num_y =  
			(worldRect.maxPos.y + aim_block_height - 2 * overlap - 1) / (aim_block_height - overlap);

		blocks_num_x = blocks_num_y = VGT_MAX( blocks_num_x , blocks_num_y );


#endif

		if ( aim_log )
		{
			logmgr.logMessage( String( _T("blocks_num_x : ")) + StringUtility::textCast(blocks_num_x) );
			logmgr.logMessage( String( _T("blocks_num_y : ")) + StringUtility::textCast(blocks_num_y) );
		}

		smallBlock  sblock;
		ImagePos	nowPos;
		ImageRect   nowRect;
		ImageRect	nowIntersectRect;
		String		sblockPostfix;
		long		sblocknum = 0;

		/// 开辟内存空间.
		smallBlockVectorPtr psblockvector( new smallBlockVector );

		// 开始所有的smallBlock循环
		for ( long sblock_y = 0 ; sblock_y < blocks_num_y ; ++ sblock_y )
		{
			for ( long sblock_x = 0 ; sblock_x < blocks_num_x ; ++ sblock_x )
			{
				/// 更新计算器.
				/// 判断是否达到所要的数目
				if ( aim_sblock_layout_num != -1 && sblocknum ++ == aim_sblock_layout_num )
				{
					goto ENDFUNC;
				}

				nowRect = aim_block_rect;
				nowRect.translate( nowPos + aim_offset );

				/// 设置序号.
				sblock.worldSequenceNumber.x = sblock_x;
				sblock.worldSequenceNumber.y = sblock_y;

				/// 设置绝对位置
				sblock.absoluteRect = nowRect;



				//////////////////////////////////////////////////////////////////////////
				//------------------------------------------
				// 注意这里!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				// !!!!!!!!!!!!!!!!!!!
				//------------------------------------------
				sblock.absoluteRect.maxPos.x += widthAndHeightAddOne;
				sblock.absoluteRect.maxPos.y += widthAndHeightAddOne;
				//////////////////////////////////////////////////////////////////////////




				/// 设置标记.此时并不是intersect的含义,只是为了下面得到想要的字符后缀.
				/// 但是默认构造函数已经设置false了,那我还需要设置吗?
				/// 是的,除非非有必要的理由如提高这一丁点的效率,此时才可以去掉.
				sblock.hasIntersect = false;

				/// 设置文件名.
				sblockPostfix = sblock.getPostfixNumFlag(aim_reversSeq);
				sblock.blockFileName = aim_block_filename + sblockPostfix + aim_ext;

				/// 加入vector.
				psblockvector->push_back( sblock );

				/// 更新位置.
				/// 为什么不直接用aim_block_width?
				/// 因为这样保险又加一层,以后nowRect可能是变的,这里先确保正确性,稍后完成再改.
				nowPos.x += nowRect.getWidth() - overlap;
			} // end of sblock_x

			/// 更新位置.
			nowPos.x = 0;
			nowPos.y += nowRect.getHeight() - overlap;
		} // end of sblock_y

ENDFUNC:
		if ( aim_log )
		{
			logmgr.logMessage(
				 _T("================= now ready to print SmallblockLayout information ===================") );
			/// 打印fileBlockVector信息.
			for ( smallBlockVector::iterator i = psblockvector->begin() ;
				i != psblockvector->end() ;
				++ i )
			{
				logmgr.logMessage( i->getDetails() );
			}
			logmgr.logMessage( 
				 _T("================= end to print SmallblockLayout information ===================") );
		}
		return psblockvector;
	}
	//----------------------------------------------------------------
	bool HugeImagesProcessor::coreFunction( fileBlockVector& fblockvec ,
		const smallBlockVector& sblockvec , 
		const AimSmallBlocksOption& aimblockinfo )
	{
		LogManager &logmgr = LogManager::getSingleton();

		const String& sfileprefix = aimblockinfo.aimFilePrefix;
		const String& sfilepostfix = aimblockinfo.aimFilePostfix;
		const String& sfiletmppostfix = aimblockinfo.aimTempFilePostfix;
		const bool&   iflog = aimblockinfo.ifLogInfo;

		const bool&	  reverseSq = aimblockinfo.ifReverseSequence;

		smallBlock tmpsblock;

		for ( fileBlockVector::iterator pfblock = fblockvec.begin() ;
			pfblock != fblockvec.end() ;
			++ pfblock )
		{

			for ( smallBlockVector::const_iterator psblock = sblockvec.begin() ;
				psblock != sblockvec.end() ;
				++ psblock )
			{
				if ( psblock->absoluteRect.testIntersection( pfblock->fileAbsoluteRect ) )
				{
					tmpsblock = *psblock;

					/// 计算相对Rect
					tmpsblock.relativeRect = psblock->absoluteRect;
					tmpsblock.relativeRect.translate( -pfblock->fileAbsoluteRect.minPos );

					/// 查看是否在文件内部.
					if ( pfblock->fileAbsoluteRect.testInside( tmpsblock.absoluteRect ) )
					{
						tmpsblock.hasIntersect = false;

						/// 更新文件名称
						tmpsblock.blockFileName = sfileprefix 
							+ tmpsblock.getPostfixNumFlag(reverseSq) + sfilepostfix;
					}
					else
					{
						tmpsblock.hasIntersect = true;

						/// 更新文件名称
						tmpsblock.blockFileName = sfileprefix 
							+ tmpsblock.getPostfixNumFlag(reverseSq) + sfiletmppostfix;
					}

					pfblock->taskList.push_back( tmpsblock );
				}
			}// end for psblock

		} // end of pfblock

		if ( iflog )
		{
			logmgr.logMessage(
				 _T("================= now ready to print the calculated fileBlockVector information ===================") );
			/// 打印fileBlockVector信息.
			for ( fileBlockVector::const_iterator i = fblockvec.begin() ;
				i != fblockvec.end() ;
				++ i )
			{
				logmgr.logMessage( i->getDetails() );
			}
			logmgr.logMessage( 
				 _T("================= end to print the calculated fileBlockVector information ===================") );
		}
		return true;
	}
	//----------------------------------------------------------------
	bool HugeImagesProcessor::processSaving( const fileBlockVector& fblockvec ,
		const AimSmallBlocksOption& aiminfo )
	{
		LogManager &logmgr = LogManager::getSingleton();

#define CximageWrapperPtr FreeImageWrapperPtr
#define CximageWrapper FreeImageWrapper

 		CximageWrapperPtr fileNimg( new CximageWrapper );
		CximageWrapperPtr tempNimg( new CximageWrapper );
		CximageWrapperPtr tmpNimg( new CximageWrapper );

		const bool& iflog = aiminfo.ifLogInfo;
		const bool& ifoverride = aiminfo.ifOverrideExist;
		const bool& ifdrawinfo = aiminfo.ifDrawInfo;

		const bool&		 aim_axis_left_top	 = aiminfo.ifAxisLeftTop;

		if ( iflog )
		{
			logmgr.logMessage(
				 _T("================= now processing saving begin ===================") );
		}

		//------------------------------------------
		// 计算大小
		//------------------------------------------
		
		int allsize = fblockvec.size();
		for ( fileBlockVector::const_iterator pfblock = fblockvec.begin() ;
			pfblock != fblockvec.end() ;
			++ pfblock )
		{
			allsize +=  pfblock->taskList.size();
		}

		this->notifyProcessObserversStart( "开始处理切块图像" , 0 , allsize );
		int counter = 0;

		/// 最后考虑const_interator的问题.
		for ( fileBlockVector::const_iterator pfblock = fblockvec.begin() ;
			pfblock != fblockvec.end() ;
			++ pfblock )
		{

			this->notifyProcessObserversPos( pfblock->fileSrcName , counter ++ );


			if ( fileNimg->loadFromFile(pfblock->fileSrcName) == false )
			{
				/// !!!!!!!!!!warn!
				continue;
			}

			for ( smallBlockVector::const_iterator psblock = pfblock->taskList.begin() ;
				psblock != pfblock->taskList.end() ;
				++ psblock )
			{

				this->notifyProcessObserversPos( psblock->blockFileName, counter ++ );


				if ( psblock->hasIntersect == false )  /// 没有重叠的情况.
				{
					/// 注意if里面是左到右运行的顺序.
					if ( !ifoverride && checkFileExist( psblock->blockFileName ) )
					{
						/// !!!!!!!!!!warn!
						continue;
					}

					if( fileNimg->crop( psblock->relativeRect , tmpNimg.getPointer() ,aim_axis_left_top) == false )
					{
						/// !!!!!!!!!!warn!
						tmpNimg->release();
						continue;
					}

					if ( ifdrawinfo )
					{
						String info( _T("FileName : "));
						info += psblock->blockFileName
							+  _T("\n Width : ") + StringUtility::textCast( psblock->absoluteRect.getWidth() )
							+  _T("\n Height : ") + StringUtility::textCast( psblock->absoluteRect.getHeight() );
						//tmpNimg->drawString( 10 , 50 , info ,  _T("") ,16);
						assert(0);
					}

					if ( ImageUtility::findImageFileExtension(psblock->blockFileName)
						== "dds" )
					{
						if( !tmpNimg->saveToDdsFile( psblock->blockFileName ,
							CximageWrapper::DDS_FORMAT_DXT1 ) )
						{
							assert( 0 &&  _T("存取失败!"));
							//warn!!!!!!!!!!!!!!!!!!
							tmpNimg->release();
							continue;
						}
					}
					else
					{
						if( !tmpNimg->saveToFile( psblock->blockFileName ) )
						{
							assert( 0 &&  _T("存取失败!"));
							//warn!!!!!!!!!!!!!!!!!!
							tmpNimg->release();
							continue;
						}
					}

					tmpNimg->release();
				}
				else ///有重叠的情况.
				{
					/// 注意if里面是左到右运行的顺序.
					if ( !ifoverride && checkFileExist( psblock->blockFileName ) )
					{
						continue;
					}

					//读文件,如果失败,则创建.
					if( !tmpNimg->loadFromFile( psblock->blockFileName ) )
					{
						tmpNimg->createFromSize( psblock->absoluteRect.getWidth() ,
							psblock->absoluteRect.getHeight() );
					}

					tmpNimg->overlap( *fileNimg , psblock->relativeRect ,aim_axis_left_top);

					/// tmp文件不用写上info的信息.
					/// 在最后处理的时候写上信息.

					if ( ImageUtility::findImageFileExtension(psblock->blockFileName)
						== "dds" )
					{
						assert(0&&"tmp文件不应该为dds文件");
						if( !tmpNimg->saveToDdsFile( psblock->blockFileName ,
							CximageWrapper::DDS_FORMAT_DXT1 ) )
						{
							assert( 0 && "存取失败22!");
							tmpNimg->release();
							continue;
						}
					}
					else
					{
						if( !tmpNimg->saveToFile( psblock->blockFileName ) )
						{
							assert( 0 && "存取失败22!");
							tmpNimg->release();
							continue;
						}
					}


					tmpNimg->release();
				}
			}// end of psblock

			fileNimg->release();
		}// end of pfblock


		this->notfiyProcessObserversFinish("切割图像操作完成");



		if ( iflog )
		{
			logmgr.logMessage(
				 _T("================= now processing saving end ===================") );
		}
		return true;
	}
	//----------------------------------------------------------------
	bool HugeImagesProcessor::processTempFiles( fileBlockVector& fblockvec ,
		const AimSmallBlocksOption& aiminfo )
	{
		LogManager &logmgr = LogManager::getSingleton();

		const bool& iflog = aiminfo.ifLogInfo;
		const bool& ifoutCombinefb = aiminfo.ifOutputCombinedFileBlocks;
		const bool& ifoutCombinesb = aiminfo.ifOutputCombinedSmallBlocks;
		const String& aimfileprefix = aiminfo.aimFilePrefix;
		const String& aimfilepostfix = aiminfo.aimFilePostfix;
		const bool& ifdrawinfo = aiminfo.ifDrawInfo;

		const bool& ifReverse = aiminfo.ifReverseSequence;

		const String&	 aim_block_filename	 = aiminfo.aimFilePrefix;
		const String&	 aim_ext			 = aiminfo.aimFilePostfix;

		//UniformImageFile  tmpimg;
		CximageWrapperPtr tmpNimg( new CximageWrapper );

		if ( iflog )
		{
			logmgr.logMessage(
				 _T("================= now processing temp file begin ===================") );
		}

		for ( fileBlockVector::iterator pfblock = fblockvec.begin() ;
			pfblock != fblockvec.end() ;
			++ pfblock )
		{
			for ( smallBlockVector::iterator psblock = pfblock->taskList.begin() ;
				psblock != pfblock->taskList.end() ;
				++ psblock )
			{
				if ( psblock->hasIntersect && checkFileExist( psblock->blockFileName ) )
				{
					psblock->hasIntersect = false;

					String oldfile = psblock->blockFileName;
					String newfile = aim_block_filename + psblock->getPostfixNumFlag(ifReverse) + aim_ext;

					/// 设置文件名.
					psblock->blockFileName = newfile;

					tmpNimg->loadFromFile( oldfile );

					if ( ifdrawinfo )
					{
						String info( _T("FileName : "));
						info += newfile
							+  _T("\n Width : ") + StringUtility::textCast( psblock->absoluteRect.getWidth() )
							+  _T("\n Height : ") + StringUtility::textCast( psblock->absoluteRect.getHeight() );
						//tmpNimg->drawString( 10 , 50 , info,  _T("") ,16);
						assert(0);
					}

					if ( ImageUtility::findImageFileExtension( psblock->blockFileName )
						== "dds" )
					{
						tmpNimg->saveToDdsFile(psblock->blockFileName,
							CximageWrapper::DDS_FORMAT_DXT1 );
					}
					else
					{
						tmpNimg->saveToFile(psblock->blockFileName);
					}


					removeFile( oldfile , iflog );

					tmpNimg->release();
				}
			}// end of psblock
		}// end of pfblock

		if ( iflog )
		{
			logmgr.logMessage(
				 _T("================= now processing temp file end ===================") );
		}

		return true;
	}
	//----------------------------------------------------------------
	bool HugeImagesProcessor::processCombining( 
		const fileBlockVector& fblockvec , 
		const AimSmallBlocksOption& aiminfo ,
		const smallBlockVector& sblockLayout)
	{
		/*
		LogManager &logmgr = LogManager::getSingleton();

		const bool& iflog = aiminfo.ifLogInfo;
		const bool& ifoutCombinefb = aiminfo.ifOutputCombinedFileBlocks;
		const bool& ifoutCombinesb = aiminfo.ifOutputCombinedSmallBlocks;
		const String& aimfileprefix = aiminfo.aimFilePrefix;
		const String& aimfilepostfix = aiminfo.aimFilePostfix;
		const bool& ifdrawinfo = aiminfo.ifDrawInfo;
		const bool& ifoverride = aiminfo.ifOverrideExist;

		const String&	 aim_block_filename	 = aiminfo.aimFilePrefix;
		const String&	 aim_ext			 = aiminfo.aimFilePostfix;

		if ( iflog )
		{
			logmgr.logMessage(
				"================= now processing combining begin ===================" );
		}

		/// 首先检查返回的情况.这种情况经常出现.
		if ( ifoutCombinefb == false && ifoutCombinesb == false )
		{
			return true;
		}

		/// 存储大文件拼合图,由于内存使用相当大,这里假设
		/// AimSmallBlocksOption首先做好了测试
		if ( ifoutCombinefb )
		{
			/// 得到整个大图的长宽
			const ImageRect worldRect = fblockvec.getWorldImageRect();

			UniformImageFile bigimage;
			UniformImageFile tmpimg;

			String finalname = aimfileprefix + '.' + aimfilepostfix;

			bigimage.Create( worldRect.getWidth() , worldRect.getHeight() );

			/// 开始遍历.
			for ( fileBlockVector::const_iterator pfblock = fblockvec.begin() ;
				pfblock != fblockvec.end() ;
				++ pfblock )
			{
				tmpimg.LoadFromFile( pfblock->fileSrcName );

				bigimage.Overlap( tmpimg , -pfblock->fileAbsoluteRect );

				tmpimg.Release();
			}// end of pfblock

			bigimage.SaveToFile( finalname );
			bigimage.Release();

		}// end if ifoutCombinefb


		/// 存储大文件拼合图,由于内存使用相当大,这里假设
		/// AimSmallBlocksOption首先做好了测试
		if ( ifoutCombinesb )
		{
			/// 得到整个大图的长宽
			const ImageRect worldRect = sblockLayout.getWorldImageRect();

			UniformImageFile bigimage;
			UniformImageFile tmpimg;

			/// 暂时命名为***2.dds的形式.
			String finalname = aimfileprefix + "2." + aimfilepostfix;

			bigimage.Create( worldRect.getWidth() , worldRect.getHeight() );

			/// 开始遍历.
			for ( smallBlockVector::const_iterator psblock = sblockLayout.begin() ;
				psblock != sblockLayout.end() ;
				++ psblock )
			{
				tmpimg.LoadFromFile( psblock->blockFileName );

				bigimage.Overlap( tmpimg , -psblock->absoluteRect );

				tmpimg.Release();
			}// end of pfblock

			bigimage.SaveToFile( finalname );
			bigimage.Release();

		}// end if ifoutCombinefb

		if ( iflog )
		{
			logmgr.logMessage(
				"================= now processing combining end ===================" );
		}

		*/
		return true;
	}
	//----------------------------------------------------------------
	HugeImageBlockInfoVectorPtr HugeImagesProcessor::getHugeImageBlockInfoVector(
		const smallBlockVector& sblockLayout ,
		const AimSmallBlocksOption& aiminfo )
	{
		/// 这里以后要更改!~~~~~~~~~~~~~~~~~~~~~
		const float& ratio = 1.0f;

		HugeImageBlockInfo tempinfo(ratio);

		HugeImageBlockInfoVectorPtr pinfovec(new HugeImageBlockInfoVector);

		/// 开始遍历.
		for ( smallBlockVector::const_iterator psblock = sblockLayout.begin() ;
			psblock != sblockLayout.end() ;
			++ psblock )
		{
			const ImagePos& pos = psblock->worldSequenceNumber;


			tempinfo.m_Vertex[3] =
				ImageUtility::getVector2FromImagePos( pos , tempinfo.m_Ratio ); 

			tempinfo.m_Vertex[2] =
				ImageUtility::getVector2FromImagePos( ImagePos( pos.x + 1 , pos.y ) , tempinfo.m_Ratio ); 

			tempinfo.m_Vertex[1] =
				ImageUtility::getVector2FromImagePos( ImagePos( pos.x + 1 , pos.y + 1 ) , tempinfo.m_Ratio ); 

			tempinfo.m_Vertex[0] =
				ImageUtility::getVector2FromImagePos( ImagePos( pos.x , pos.y + 1 ) , tempinfo.m_Ratio ); 


			tempinfo.m_BlockFileName = psblock->blockFileName;
			tempinfo.m_WorldNumber = pos;

			pinfovec->push_back( tempinfo );
		}// end of psblock

		return pinfovec;
	}
	//----------------------------------------------------------------
	bool HugeImagesProcessor::makeProcessingAndSaving()
	{


		_hugeProcessor.process();

		return true;


		/// 查看是否有错误.
		assert(isSafe());
		if ( !isSafe() )
		{
			return false;
		}

		/// 创建文件块的布局.
		if ( m_pfblockVector.isNull() == true )
		{
			this->m_pfblockVector = 
				createFileblockLayout( *m_pFileNamesInfo , *m_pAimsblocksOption );
		}

		if ( m_pfblockVector.isNull() )
		{
			return false;
		}

		/// 创建输出块(小块)的布局.
		this->m_pSmallblockLayout =
			createDefaultSmallblockLayout( *m_pfblockVector , *m_pAimsblocksOption );

		if ( m_pSmallblockLayout.isNull() )
		{
			return false;
		}

		/// 核心运算处理数据.
		if( !coreFunction( *m_pfblockVector , *m_pSmallblockLayout , *m_pAimsblocksOption ))
		{
			return false;
		}

		/// 初始化保存环境:删除原有的文件等等.
		if(!initSavingEnvironment( *m_pfblockVector , *m_pAimsblocksOption , 
			*m_pSmallblockLayout ))
		{
			return false;
		}

		/// 开始保存文件.
		if( !processSaving( *m_pfblockVector , *m_pAimsblocksOption ))
		{
			return false;
		}

		/// 处理临时文件(即拼合临时文件,产生想要的输出).
		if( !processTempFiles( *m_pfblockVector , *m_pAimsblocksOption ))
		{
			return false;
		}

		/// 若输出拼合图选项为真,则开始处理拼合图.
		if( !processCombining( *m_pfblockVector , *m_pAimsblocksOption , *m_pSmallblockLayout))
		{
			return false;
		}

		return true;
	}
	//----------------------------------------------------------------
	bool HugeImagesProcessor::makeProcessing()
	{
		/// 查看是否有错误.
		assert(isSafe());
		if ( !isSafe() )
		{
			return false;
		}

		/// 创建文件块的布局.

		if ( m_pfblockVector.isNull() == true )
		{
			this->m_pfblockVector = 
				createFileblockLayout( *m_pFileNamesInfo , *m_pAimsblocksOption );
		}

		if ( m_pfblockVector.isNull() )
		{
			return false;
		}

		/// 创建输出块(小块)的布局.
		this->m_pSmallblockLayout =
			createDefaultSmallblockLayout( *m_pfblockVector , *m_pAimsblocksOption );

		if ( m_pSmallblockLayout.isNull() )
		{
			return false;
		}

		/// 核心运算处理数据.
		if( !coreFunction( *m_pfblockVector , *m_pSmallblockLayout , *m_pAimsblocksOption ))
		{
			return false;
		}
		return true;
	}

	bool HugeImagesProcessor::makeSaving()
	{
		/// 查看是否有错误.
		assert(isSafe());
		if ( !isSafe() )
		{
			return false;
		}
		if ( m_pfblockVector.isNull() )
		{
			return false;
		}
		if ( m_pSmallblockLayout.isNull() )
		{
			return false;
		}

		/// 初始化保存环境:删除原有的文件等等.
		if(!initSavingEnvironment( *m_pfblockVector , *m_pAimsblocksOption , 
			*m_pSmallblockLayout ))
		{
			return false;
		}

		/// 开始保存文件.
		if( !processSaving( *m_pfblockVector , *m_pAimsblocksOption ))
		{
			return false;
		}

		/// 处理临时文件(即拼合临时文件,产生想要的输出).
		if( !processTempFiles( *m_pfblockVector , *m_pAimsblocksOption ))
		{
			return false;
		}

		/// 若输出拼合图选项为真,则开始处理拼合图.
		if( !processCombining( *m_pfblockVector , *m_pAimsblocksOption , *m_pSmallblockLayout))
		{
			return false;
		}

		return true;
	}
	//----------------------------------------------------------------
	bool HugeImagesProcessor::initialiseParameters(
		uchar* filledColor,
		const bool& remove_input_files,
		const String& temp_file_ext , 
		const String& tmp_path , 
		const bool& remove_tmp_file,
		const String& fileprefix,  const long& width,  
		const long& height,  
		const String& tmpfilepostfix /*= "bmp"*/, 
		const String& fileposfix /*= "dds"*/,  
		const bool& reverseSequence			/*= false*/,
		const bool& axisLeftTop				/*= false*/,
		const bool& loginfo  /*= true*/, 
		const bool& overrid  /*= false*/, 
		const bool& outputcombinesblock /*= false*/,
		const String& outcombinesblockname /*= ""*/,
		const bool& outputcombinefblock /*= false*/, 
		const String& outcombinefblockname /*= ""*/, 
		const bool& drawinfo /*= false*/, 
		const ImagePos& offset /*= IMAGEPOS_ZERO*/, 
		const long& pixceloverlap /*= 1*/,  
		const long& sblocknum /*= -1 */ ,
		const long& width_and_height_add_one/* = 0*/)
	{

		assert( width == height );

		_hugeProcessor.initParams( filledColor , 
			tmp_path , fileprefix , fileposfix , temp_file_ext ,width ,
			width_and_height_add_one , remove_tmp_file , getProcessObs() ,
			remove_input_files );

		if ( !m_pAimsblocksOption.isNull() )
		{
			return false;
		}
		this->m_pAimsblocksOption.bind(
			new AimSmallBlocksOption(fileprefix,
			width,
			height,
			tmpfilepostfix,
			fileposfix,
			reverseSequence,
			axisLeftTop,
			loginfo,
			overrid	,
			outputcombinesblock,
			outcombinesblockname,
			outputcombinefblock,
			outcombinefblockname,
			drawinfo,
			offset,
			pixceloverlap,
			sblocknum ,
			width_and_height_add_one ) );

		return true;
	}
	//----------------------------------------------------------------
	bool HugeImagesProcessor::initDefaultParameters( const String& fileprefix )
	{
		if ( !m_pAimsblocksOption.isNull())
		{
			return false;
		}
		this->m_pAimsblocksOption.bind( new AimSmallBlocksOption(fileprefix) );

		return true;
	}
	//----------------------------------------------------------------
	bool HugeImagesProcessor::initialiseFileNames( const TCHAR** const &chararray , 
		const long& col ,  const long& row , const bool& loginfo /*= true */ )
	{
		if ( !m_pFileNamesInfo.isNull() )
		{
			VGK_EXCEPT(Exception::ERR_INVALID_STATE ,
				 _T("自身不为空,已被初始化. The self data struct must be inited.") ,
				 _T("HugeImagesProcessor::initialiseFileNames"));
			return false;
		}
		this->m_pFileNamesInfo = HugeImageUtil::createFileNamesInfoFormArray(
			chararray , col , row , false );
		if ( m_pFileNamesInfo.isNull() )
		{
			return false;
		}

		if ( loginfo )
		{
			LogManager::getSingleton().logMessage(m_pFileNamesInfo->getDetails());
		}
		return true;
	}
	//----------------------------------------------------------------
	void HugeImagesProcessor::initialiseFileBlocks( const fileBlockVectorPtr inputfileblocks )
	{
		assert( inputfileblocks.isNull() == false );
		m_pfblockVector = inputfileblocks;

		_hugeProcessor.initFileBlocks( inputfileblocks);
	}
	//----------------------------------------------------------------
	vgTerritory::HugeImageBlockInfoVectorPtr HugeImagesProcessor::getHugeImageBlockInfos() 
	{
		return _hugeProcessor.getHugeImageBlockInfoVectorPtr();


		//return getHugeImageBlockInfoVector( *m_pSmallblockLayout ,
		//	*m_pAimsblocksOption);
	}
	//----------------------------------------------------------------

	

}// end of namespace vgTerritory

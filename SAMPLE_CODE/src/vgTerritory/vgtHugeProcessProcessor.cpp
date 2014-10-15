


#include <vgStableHeaders.h>
#include <vgTerritory/vgtHugeProcessProcessor.h>
#include <vgImage/vgiBatchProcessor.h>


namespace vgTerritory {
	
	
	
	
	//----------------------------------------------------------------
	void HugeProcess::Processor::clear()
	{

		if ( _threadPool != NULL )
		{
			delete _threadPool;
			_threadPool = NULL;
		}

		delete _globalData;
		_globalData = new Global;

		{
			//------------------------------------------
			// 清除smallblock
			//------------------------------------------
			std::vector<SmallBlock*>::iterator iter = _smallBlocks.begin();
			std::vector<SmallBlock*>::iterator iter_end = _smallBlocks.end();

			for ( ; iter != iter_end ; ++ iter )
			{
				delete *iter;
			}
			_smallBlocks.clear();
		}

		{
			//------------------------------------------
			// 清除fileblock
			//------------------------------------------
			std::vector<FileBlock*>::iterator iter = _fileBlocks.begin();
			std::vector<FileBlock*>::iterator iter_end = _fileBlocks.end();

			for ( ; iter != iter_end ; ++ iter )
			{
				delete *iter;
			}
			_fileBlocks.clear();
		}

		{
			//------------------------------------------
			// 清除cutBlocks
			//------------------------------------------
			std::vector<CutBlock*>::iterator iter = _cutBlocks.begin();
			std::vector<CutBlock*>::iterator iter_end = _cutBlocks.end();

			for ( ; iter != iter_end ; ++ iter )
			{
				delete *iter;
			}
			_cutBlocks.clear();
		}
	}
	//----------------------------------------------------------------
	bool HugeProcess::Processor::initFileBlocks(
		const fileBlockVectorPtr inputfileblocks )
	{
		assert( inputfileblocks.isNull() == false );
		fileBlockVector::iterator iter = inputfileblocks->begin();
		fileBlockVector::iterator iter_end = inputfileblocks->end();

		for ( ; iter != iter_end ; ++ iter )
		{
			FileBlock* block = new FileBlock( 
				iter->fileSrcName , iter->fileAbsoluteRect , getGlobalPtr() );
			_fileBlocks.push_back( block );
		}

		assert( _fileBlocks.empty() == false );

		//------------------------------------------
		// 查找imagerect信息
		//------------------------------------------
		ImageRect worldrect = _fileBlocks[0]->getAbsoluteRect();

		std::vector<FileBlock*>::iterator fiter = _fileBlocks.begin();
		std::vector<FileBlock*>::iterator fiter_end = _fileBlocks.end();

		for ( ; fiter != fiter_end ; ++ fiter )
		{
			FileBlock* block = *fiter;
			worldrect.merge( block->getAbsoluteRect() );
		}

		// 更新global信息
		_globalData->_worldRect = worldrect;

		return true;
	}
	//----------------------------------------------------------------
	bool HugeProcess::Processor::initParams(  uchar* filledColor , 
		const String& temppath , 
		const String& prefix , 
		const String& ext ,const String&temp_ext , const long& smallblockwidth ,
		const long& widthandheightaddon , const bool& removetempfiles ,
		std::vector<ProcessObserver*> observers ,
		const bool& remove_input_files )
	{
		assert( smallblockwidth > 0 );
		for ( int i = 0 ; i < 4 ; ++ i )
		{
			_globalData->_filledColor[i] = filledColor[i];
		}
		
		_globalData->_tempPath = temppath;
		_globalData->_smallBlockWidth = smallblockwidth;
		_globalData->_widthAndHeightAddition = widthandheightaddon;
		_globalData->_outputExtension = ext;
		_globalData->_outputPrefix = prefix;
		_globalData->_removeTempFiles = removetempfiles;
		_globalData->_removeInputFiles = remove_input_files;
		_globalData->_tempExtension = temp_ext;

		assert( temp_ext != "dds" );
		registerProcessObs( observers );

		//assert( _globalData->_outputExtension == "bmp" || 
		//	_globalData->_outputExtension == "dds"/* ||
		//	_globalData->_outputExtension == "tga"*/ );

		if ( _globalData->_worldRect.isEmpty() == false )
		{
			_globalData->_isValid = true;
		}

		return true;
	}
	//----------------------------------------------------------------
	void HugeProcess::Processor::process()
	{
		assert( _fileBlocks.empty() == false );
		assert( _smallBlocks.empty() == true );
		assert( _globalData->_worldRect.isEmpty()  == false );
		assert( _globalData->isValid() == true );
		assert( _cutBlocks.empty() == true );

		//------------------------------------------
		// 首先创建default的smallblock的layout
		//------------------------------------------
		long x1 = ( _globalData->_worldRect.minPos.x ) / _globalData->_smallBlockWidth;
		long y1 = ( _globalData->_worldRect.minPos.y ) / _globalData->_smallBlockWidth;

		long x2 =  ( _globalData->_worldRect.maxPos.x + _globalData->_smallBlockWidth - 1 ) /
			_globalData->_smallBlockWidth;
		long y2 =  ( _globalData->_worldRect.maxPos.y + _globalData->_smallBlockWidth - 1 ) /
			_globalData->_smallBlockWidth;

		for ( int i = x1 ; i < x2 ; ++ i )
		{
			for ( int j = y1 ; j < y2 ; ++ j )
			{
				SmallBlock* sblock = new SmallBlock( 
					i , j , getGlobalPtr() );

				_smallBlocks.push_back( sblock );
			}
		}

		//------------------------------------------
		// 然后fileblock和smallblock分别做相交测试
		//------------------------------------------
		{
			std::vector<SmallBlock*>::iterator iter = _smallBlocks.begin();
			std::vector<SmallBlock*>::iterator iter_end = _smallBlocks.end();

			for ( ; iter != iter_end ; ++ iter )
			{
				(*iter)->testIntersects( _fileBlocks );
			}
		}

		{
			std::vector<FileBlock*>::iterator iter = _fileBlocks.begin();
			std::vector<FileBlock*>::iterator iter_end = _fileBlocks.end();

			for ( ; iter != iter_end ; ++ iter )
			{
				(*iter)->testIntersects( _smallBlocks );
			}
		}

		//------------------------------------------
		// 开始输出到cutblocks
		//------------------------------------------
#if 0
		{
			std::vector<FileBlock*>::iterator iter = _fileBlocks.begin();
			std::vector<FileBlock*>::iterator iter_end = _fileBlocks.end();

			for ( ; iter != iter_end ; ++ iter )
			{
				(*iter)->beginToCut( _cutBlocks );
			}
		}
#endif
		{

			notifyProcessObserversStart( "File Block cutting..." , 0 , _fileBlocks.size() );

			//------------------------------------------
			// 创建ThreadPool
			//------------------------------------------
			assert( _threadPool  == NULL );
			if ( _threadPool == NULL )
			{
				_threadPool = new ThreadPool( VGT_THREAD_NUM );
				_threadPool->initialize();
			}

			assert( _counter == NULL );
			_counter = new Counter( _fileBlocks.size() );
			_event.reset();

			for ( int i = 0 ; i < _fileBlocks.size() ; ++ i )
			{
				FileBlockRequest* req = new FileBlockRequest( _fileBlocks[i] , 
					_cutBlocks , &_criticalSect , _counter , &_event , this );
				_threadPool->submitRequest( req );
			}

			bool outwhile = false;
			while ( 1 )
			{
				switch(::WaitForSingleObject( _event.getHandle() , 
					VGT_MULTITHREAD_UI_REFRESH_WAIT ) )
				{
				case WAIT_OBJECT_0:
					outwhile = true;
					break;
				case WAIT_TIMEOUT:

					notifyCurrentProcessObserversPos();
					continue;

				case WAIT_ABANDONED:	   
				default:
					assert(0);
				}

				if ( outwhile )	{break;}
			}


			_threadPool->shutdown();

			delete _counter;
			_counter = NULL;
			delete _threadPool;
			_threadPool = NULL;

			notfiyProcessObserversFinish("File Block cut done");
		}

		//------------------------------------------
		// 将cutblocks和smallblock进行相交测试
		//------------------------------------------
		{
			std::vector<SmallBlock*>::iterator iter = _smallBlocks.begin();
			std::vector<SmallBlock*>::iterator iter_end = _smallBlocks.end();

			for ( ; iter != iter_end ; ++ iter )
			{
				(*iter)->testIntersects( _cutBlocks );
			}
		}

		//------------------------------------------
		// 将smallblock的cutblock进行overlap, 并保存bmp处理
		//------------------------------------------
		StringVectorPtr bmplist( new StringVector );
#if 0
		
		{
			std::vector<SmallBlock*>::iterator iter = _smallBlocks.begin();
			std::vector<SmallBlock*>::iterator iter_end = _smallBlocks.end();

			for ( ; iter != iter_end ; ++ iter )
			{
				String file = (*iter)->overlapCutBlocks();

				if ( file != "" )
				{
					bmplist->push_back( file );
				}
			}
		}
#endif
		{
			notifyProcessObserversStart( "Small Block creating..." , 0 , _fileBlocks.size() );

			//------------------------------------------
			// 创建ThreadPool
			//------------------------------------------
			assert( _threadPool  == NULL );
			if ( _threadPool == NULL )
			{
				_threadPool = new ThreadPool(VGT_THREAD_NUM);
				_threadPool->initialize();
			}

			assert( _counter == NULL );
			_counter = new Counter( _smallBlocks.size() );
			_event.reset();

			for ( int i = 0 ; i < _smallBlocks.size() ; ++ i )
			{
				SmallBlockRequest* req = new SmallBlockRequest( _smallBlocks[i] , 
					&_criticalSect , _counter , &_event , bmplist.getPointer() , this );
				_threadPool->submitRequest( req );
			}

			bool outwhile = false;
			while ( 1 )
			{
				switch(::WaitForSingleObject( _event.getHandle() , 
					VGT_MULTITHREAD_UI_REFRESH_WAIT ) )
				{
				case WAIT_OBJECT_0:
					outwhile = true;
					break;
				case WAIT_TIMEOUT:

					notifyCurrentProcessObserversPos();
					continue;

				case WAIT_ABANDONED:	   
				default:
					assert(0);
				}

				if ( outwhile )	{break;}
			}

			_threadPool->shutdown();

			delete _counter;
			_counter = NULL;
			delete _threadPool;
			_threadPool = NULL;

			notfiyProcessObserversFinish("Small Block create done");
		}

		//------------------------------------------
		// 然后将这些bmp处理成dds文件
		//------------------------------------------
		_outputNames = bmplist;

		//if ( _globalData->_outputExtension == "dds" )
		//{
		//	StringVectorPtr ddslist = BatchProcessor::process( 
		//		bmplist , _globalData->_tempPath , _globalData->_outputExtension , 
		//		GL_COMPRESSED_RGBA_S3TC_DXT1_EXT , this , true );

		//	assert( ddslist.isNull() == false );

		//	_outputNames = ddslist;

		//}

		//------------------------------------------
		// 清除没用的文件
		//------------------------------------------
		if ( _globalData->_removeTempFiles )
		{
			//------------------------------------------
			// 清除cutBlocks
			//------------------------------------------
			{
				std::vector<CutBlock*>::iterator iter = _cutBlocks.begin();
				std::vector<CutBlock*>::iterator iter_end = _cutBlocks.end();

				for ( ; iter != iter_end ; ++ iter )
				{
					SystemUtility::removeFile( (*iter)->getFilePath() , false );
				}
			}

			//if ( _globalData->_outputExtension == "dds" )
			//{
			//	StringVector::iterator iter = bmplist->begin();
			//	StringVector::iterator iter_end = bmplist->end();

			//	for ( ; iter != iter_end ; ++ iter )
			//	{
			//		SystemUtility::removeFile( (*iter) ,false );
			//	}

			//}
		}

		clear();

		return;
	}
	//----------------------------------------------------------------
	HugeImageBlockInfoVectorPtr HugeProcess::Processor::getHugeImageBlockInfoVectorPtr()
	{
		assert( _outputNames.isNull() == false );

		HugeImageBlockInfoVectorPtr ret( new HugeImageBlockInfoVector );

		StringVector::iterator iter = _outputNames->begin();
		StringVector::iterator iter_end = _outputNames->end();

		for ( ; iter != iter_end ; ++ iter )
		{
			HugeImageBlockInfo info;
			info.m_BlockFileName = *iter;

			info.m_BlockFileName = 
				StringUtility::getFilenameFromAbsolutePath( info.m_BlockFileName );
			ret->push_back( info );
		}

		return ret;
	}

	HugeProcess::Processor::Processor()
	{
		_threadPool = NULL;
		_globalData = new Global;
		_counter = NULL;
	}

	HugeProcess::Processor::~Processor()
	{
		clear();

		if ( _globalData != NULL )
		{
			delete _globalData;
			_globalData = NULL;
		}
	}
	//----------------------------------------------------------------



	//----------------------------------------------------------------
	void HugeProcess::FileBlockRequest::operator()( int threadId )
	{
		_notifier->setCurrentProcessPos( _fileBlock->getFilePath() , 
			_counter->getCount() );

		_fileBlock->beginToCut( _cutBlocks , _cutBlockCriticalSect );

		_counter->addCount();

		if ( _counter->checkCount() == true )
		{
			_event->signal();
		}
	}
	//----------------------------------------------------------------
	HugeProcess::FileBlockRequest::FileBlockRequest( FileBlock* fileblock ,
		std::vector<CutBlock*>& cutblocks, CriticalSection* cutblockcritical , 
		Counter* counter , 
		ManualEvent* cut_event ,vgKernel::ProcessNotifier* notifier ) 
		: ThreadRequest(),
		_cutBlocks( cutblocks )
	{
		_event = cut_event;
		_fileBlock = fileblock;
		_cutBlockCriticalSect = cutblockcritical;
		_counter = counter;
		_notifier = notifier;
	}
	//----------------------------------------------------------------
	HugeProcess::FileBlockRequest::~FileBlockRequest()
	{

	}
	//----------------------------------------------------------------





	//----------------------------------------------------------------
	void HugeProcess::SmallBlockRequest::operator()( int threadId )
	{
		_notifier->setCurrentProcessPos( _block->getDstFilename() , 
			_counter->getCount() );

		String file = _block->overlapCutBlocks();

		if ( file != "" )
		{
			_criticalSect->enter();
			_list->push_back( file );
			_criticalSect->leave();
		}

		_counter->addCount();

		if ( _counter->checkCount() == true )
		{
			_event->signal();
		}
	}
	//----------------------------------------------------------------
	HugeProcess::SmallBlockRequest::SmallBlockRequest(  SmallBlock* sblock , 
		CriticalSection* cutblockcritical , Counter* counter , 
		ManualEvent* cut_event  , StringVector* list ,
		vgKernel::ProcessNotifier* notifier ) 
		: ThreadRequest()
	{
		_notifier = notifier;
		_event = cut_event;
		_block = sblock;
		_criticalSect = cutblockcritical;
		_counter = counter;
		_list = list;
	}
	//----------------------------------------------------------------
	HugeProcess::SmallBlockRequest::~SmallBlockRequest()
	{

	}
	//----------------------------------------------------------------





}// end of namespace vgTerritory

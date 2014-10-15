


#include <vgStableHeaders.h>
#include <vgTerritory/vgtHugeProcessSmallBlock.h>
#include <vgTerritory/vgtHugeProcessFileBlock.h>
#include <vgImage/vgiCximageWrapper.h>
#include <vgImage/vgiFreeImageWrapper.h>


namespace vgTerritory {
	
	
	
	
	//----------------------------------------------------------------
	bool HugeProcess::SmallBlock::testIntersects( 
		std::vector<FileBlock*>& input_file_blocks )
	{
		assert( _intersectFileBlocks.empty() == true );

		std::vector<FileBlock*>::iterator iter = input_file_blocks.begin();
		std::vector<FileBlock*>::iterator iter_end = input_file_blocks.end();

		for ( ; iter != iter_end ; ++iter )
		{
			if ( (*iter)->getAbsoluteRect().testIntersection2( getAbsoluteRect() ) )
			{
				_intersectFileBlocks.push_back( ( *iter ) );
			}
		}

		if ( _intersectFileBlocks.empty() == true )
		{
			return false;
		}

		return true;
	}
	//----------------------------------------------------------------
	bool HugeProcess::SmallBlock::testIntersects( 
		std::vector<CutBlock*>& input_cut_blocks )
	{
		assert( _insideCutBlocks.empty() == true );

		std::vector<CutBlock*>::iterator iter = input_cut_blocks.begin();
		std::vector<CutBlock*>::iterator iter_end = input_cut_blocks.end();

		for ( ; iter != iter_end ; ++iter )
		{
			if ( getAbsoluteRect().testInside( (*iter)->getAbsoluteRect() ) )
			{
				_insideCutBlocks.push_back( ( *iter ) );
			}
		}

		if ( _insideCutBlocks.empty() == true )
		{
			return false;
		}

		return true;
	}
	//----------------------------------------------------------------
	HugeProcess::SmallBlock::SmallBlock( long worldnumX, long worldnumY , Global* global )
	{
		using namespace vgImage;
		assert( worldnumX >= 0 );
		assert( worldnumY >= 0 );
		assert( global->isValid() );

		_global = global;
		_worldNumX = worldnumX;
		_worldNumY = worldnumY;

		_absoluteRect.minPos.x = 
			global->_smallBlockWidth * _worldNumX;

		_absoluteRect.minPos.y = 
			global->_smallBlockWidth * _worldNumY;

		_absoluteRect.maxPos.x = _absoluteRect.minPos.x + 
			global->_smallBlockWidth + global->_widthAndHeightAddition - 1;

		_absoluteRect.maxPos.y = _absoluteRect.minPos.y + 
			global->_smallBlockWidth + global->_widthAndHeightAddition - 1;
	}
	//----------------------------------------------------------------
	String HugeProcess::SmallBlock::overlapCutBlocks()
	{
		using namespace vgImage;
		if ( _insideCutBlocks.empty() == true )
		{
			return "";
		}

		String dst = getDstFilename();

		static vgThreads::CriticalSection read_write_lock;


#define ImageWrapper FreeImageWrapper

		//------------------------------------------
		// 首先检查一个是否有一样大小的cutblock,
		// 如果有,复制到输出目录即可.
		//------------------------------------------
		{
			std::vector<CutBlock*>::iterator iter = _insideCutBlocks.begin();
			std::vector<CutBlock*>::iterator iter_end = _insideCutBlocks.end();

			for ( ; iter != iter_end ; ++ iter )
			{
				if ( getAbsoluteRect() == (*iter)->getAbsoluteRect() )
				{
					ImageWrapper img;

					bool saveok = img.loadFromFile( (*iter)->getFilePath() );

					assert( saveok == true );

					if ( _global->_outputExtension == "dds" )
					{
						saveok = img.saveToDdsFile(
								dst , ImageWrapper::DDS_FORMAT_DXT1 );
					}
					else
					{
						img.saveToFile( dst );
					}

					return dst;
				}
			}
		}

		//------------------------------------------
		// 开始overlap
		//------------------------------------------
		ImageWrapper selfimg;
		selfimg.createFromSize( getAbsoluteRect().getWidth() + 1 , 
			getAbsoluteRect().getHeight() + 1 , 32 );

		selfimg.clearColor( _global->_filledColor[0] , 
			_global->_filledColor[1] , 
			_global->_filledColor[2] , 
			_global->_filledColor[3] );

		std::vector<CutBlock*>::iterator iter = _insideCutBlocks.begin();
		std::vector<CutBlock*>::iterator iter_end = _insideCutBlocks.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			ImageWrapper tmp;
			bool loadok = tmp.loadFromFile( (*iter)->getFilePath() );

			if ( loadok == false )
			{
				continue;
			}

			ImageRect src_rect = (*iter)->getAbsoluteRect();

			// 注意有负号.
			src_rect.translate( - getAbsoluteRect().minPos );

			selfimg.overlap2( tmp , src_rect.minPos.x , src_rect.minPos.y );
		}

		bool saveok = false ;
		
		if ( _global->_outputExtension == "dds" )
		{
			saveok = selfimg.saveToDdsFile(
				dst , ImageWrapper::DDS_FORMAT_DXT1 );
		}
		else
		{
			saveok = selfimg.saveToFile( dst );
		}

		if ( saveok == true )
		{
			return dst;
		}

		return  "";
	}
	//----------------------------------------------------------------
	String HugeProcess::SmallBlock::getDstFilename()
	{
		// dds时特别处理
		std::ostringstream o;

		//if ( _global->_outputExtension == "dds" )
		//{
		//	o << _global->_tempPath << "\\" << _global->_outputPrefix << "_" << _worldNumX << "_"
		//		<< _worldNumY << ".bmp";
		//}
		//else
		//{
			o << _global->_tempPath << "\\" << _global->_outputPrefix << "_" << _worldNumX << "_"
				<< _worldNumY << "." << _global->_outputExtension;
		//}

		return o.str();
	}
	//----------------------------------------------------------------



}// end of namespace vgTerritory

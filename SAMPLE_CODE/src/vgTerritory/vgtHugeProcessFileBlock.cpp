


#include <vgStableHeaders.h>
#include <vgTerritory/vgtHugeProcessFileBlock.h>
#include <vgTerritory/vgtHugeProcessSmallBlock.h>
#include <vgTerritory/vgtGdalDataSetGuide.h>
#include <vgImage/vgiCximageWrapper.h>
#include <vgImage/vgiFreeImageWrapper.h>



namespace vgTerritory {
	
	
	
	
	//----------------------------------------------------------------
	bool HugeProcess::FileBlock::testIntersects(
		std::vector<SmallBlock*>& input_small_blocks )
	{
		assert( _intersectSmallBlocks.empty() == true );

		std::vector<SmallBlock*>::iterator iter = input_small_blocks.begin();
		std::vector<SmallBlock*>::iterator iter_end = input_small_blocks.end();

		for ( ; iter != iter_end ; ++iter )
		{
			if ( (*iter)->getAbsoluteRect().testIntersection2( getAbsoluteRect() ) )
			{
				_intersectSmallBlocks.push_back( ( *iter ) );
			}
		}

		if ( _intersectSmallBlocks.empty() == true )
		{
			return false;
		}

		return true;
	}
	//----------------------------------------------------------------
	void HugeProcess::FileBlock::beginToCutImpl( 
		std::vector<CutBlock*>& output_cutblocks , 
		CriticalSection* cutblock_critialsect )
	{

#if 1
		using namespace vgImage;

		if ( _intersectSmallBlocks.empty() == true )
		{
			return;
		}

#if 0
		CximageWrapper img;
		bool loadok = img.loadFromFile( _filePath );
		if ( loadok == false )
		{
			int counter = 0;
			while ( counter < 100 && loadok == false )
			{
				loadok = img.loadFromFile( _filePath);
				counter ++;
				Sleep(100);
			}

			if ( loadok == false )
			{
				assert( 0&& "loadok == true" );
			}
		}
#else



		FreeImageWrapper img;
		bool loadok = img.loadFromFile( _filePath );
		if ( loadok == false )
		{
			int counter = 0;
			while ( counter < 100 && loadok == false )
			{
				loadok = img.loadFromFile( _filePath);
				counter ++;
				Sleep(100);
			}

			if ( loadok == false )
			{
				assert( 0&& "loadok == true" );
			}
		}



#endif
		


		std::vector<SmallBlock*>::iterator iter = _intersectSmallBlocks.begin();
		std::vector<SmallBlock*>::iterator iter_end = _intersectSmallBlocks.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			ImageRect inter;
			ImageRect interAbs;
			bool interok = (*iter)->getAbsoluteRect().findIntersection2( 
				getAbsoluteRect() , interAbs );

			assert( interok == true );

			// 注意有负号.
			inter = interAbs.translateCopy( - getAbsoluteRect().minPos );

#if 0
			CximageWrapperPtr tmp( new CximageWrapper );
#else

			FreeImageWrapperPtr tmp( new FreeImageWrapper );
#endif

			//------------------------------------------
			// 开始读取
			//------------------------------------------
			ImageRect biggerinter = inter;
			biggerinter.maxPos.x += 1;
			biggerinter.maxPos.y += 1;

			bool cropok = img.crop( biggerinter , tmp.getPointer() , true );
			assert( cropok == true );

			//------------------------------------------
			// 开始保存
			//------------------------------------------
			// 得到文件名
			String savename = _global->_tempPath + "\\";
			std::ostringstream o;
			o << interAbs.minPos.x << "_" << interAbs.minPos.y << "_"
				<< interAbs.maxPos.x << "_" << interAbs.maxPos.y << "_"
				<< UniqueIDFactory::getUniqueID().getString() << "." << _global->_tempExtension;
			savename += o.str();


			bool saveok = tmp->saveToFile( savename );

			if ( saveok == false )
			{
				std::ostringstream o;
				o << "保存文件:" << savename << "失败";
				MessageBox( NULL , o.str().c_str() , "提示" , MB_OK );
				continue;
			}

			CutBlock* block = new CutBlock( savename , interAbs , _global );

			if ( cutblock_critialsect != NULL )
			{
				cutblock_critialsect->enter();
			}

			output_cutblocks.push_back( block );

			if ( cutblock_critialsect != NULL )
			{
				cutblock_critialsect->leave();
			}
		}

		return;


#else
		using namespace vgImage;

		if ( _intersectSmallBlocks.empty() == true )
		{
			return;
		}

		GDALDataset* pDataSet = ( GDALDataset *)GDALOpen( 
			_filePath.c_str() , GA_ReadOnly );

		assert( pDataSet != NULL );
		if ( pDataSet == NULL )
		{
			assert(0);
			return;
		}

		GdalDataSetGuide guide( &pDataSet );
		long nBand = pDataSet->GetRasterCount();
		assert( nBand <= 4 );
		assert( nBand >= 3);
		if ( nBand < 3 || nBand > 4 )
		{
			MessageBox( NULL , "读取源文件失败", "Error" , MB_OK );
			return;
		}

		std::vector<SmallBlock*>::iterator iter = _intersectSmallBlocks.begin();
		std::vector<SmallBlock*>::iterator iter_end = _intersectSmallBlocks.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			ImageRect inter;
			ImageRect interAbs;
			bool interok = (*iter)->getAbsoluteRect().findIntersection2( 
				getAbsoluteRect() , interAbs );

			assert( interok == true );

			// 注意有负号.
			inter = interAbs.translateCopy( - getAbsoluteRect().minPos );

			//------------------------------------------
			// 开始使用GDAL读取
			//------------------------------------------
			long buffer_width = inter.getWidth() + 1;
			long buffer_height = inter.getHeight() + 1;
			long buffer_size = buffer_width * buffer_height * nBand;
			byte* buffer = new byte[ buffer_size ];
			memset( buffer , 0 , buffer_size );

			CPLErr raster_ret = pDataSet->RasterIO( 
				GF_Read , inter.minPos.x , inter.minPos.y , 
				buffer_width ,  buffer_height ,
				buffer , buffer_width ,  buffer_height ,
				GDT_Byte, nBand, NULL, nBand, 0, 1 );

			if ( raster_ret != CE_None )
			{
				::AfxMessageBox("读取影像数据时失败!");
				delete[] buffer;

				return;
			}

			//------------------------------------------
			// 开始保存
			//------------------------------------------
			CximageWrapper img;
			long bpp = ( nBand == 3 ? 24 : 32 );
			// 得到文件名
			String savename = _global->_tempPath + "\\";
			std::ostringstream o;
			o << interAbs.minPos.x << "_" << interAbs.minPos.y << "_"
				<< interAbs.maxPos.x << "_" << interAbs.maxPos.y << "_"
				<< UniqueIDFactory::getUniqueID().getString() << "." << _global->_tempExtension;
			savename += o.str();


			bool createok = img.createFromArray( buffer , buffer_width , 
				buffer_height , bpp , true , true );
			
			delete[] buffer;
			buffer = NULL;

			bool saveok = img.saveToFile( savename );

			if ( saveok == false )
			{
				std::ostringstream o;
				o << "保存文件:" << savename << "失败";
				MessageBox( NULL , o.str().c_str() , "提示" , MB_OK );
				continue;
			}

			assert( createok == true );

			CutBlock* block = new CutBlock( savename , interAbs , _global );

			if ( cutblock_critialsect != NULL )
			{
				cutblock_critialsect->enter();
			}

			output_cutblocks.push_back( block );

			if ( cutblock_critialsect != NULL )
			{
				cutblock_critialsect->leave();
			}
		}

		return;
#endif
	}
	//----------------------------------------------------------------
	void HugeProcess::FileBlock::beginToCut( std::vector<CutBlock*>& output_cutblocks ,
		CriticalSection* cutblock_critialsect )
	{
		beginToCutImpl( output_cutblocks , cutblock_critialsect );

		if ( _global->_removeInputFiles )
		{
			SystemUtility::removeFile( getFilePath() , false );
		}
	}
	//----------------------------------------------------------------
}// end of namespace vgTerritory

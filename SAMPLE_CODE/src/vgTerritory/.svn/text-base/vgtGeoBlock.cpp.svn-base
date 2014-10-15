




#include <vgStableHeaders.h>
#include <vgTerritory/vgtGeoBlock.h>
#include <vgKernel/vgkConvertUtility.h>
#include <vgTerritory/vgVgtrWriter.h>
#include <vgImage/vgiBmpFactory.h>
#include <vgImage/vgiFreeImageWrapper.h>
#include <vgImage/vgiCximageWrapper.h>

namespace vgTerritory {
	
	
	
	
	//----------------------------------------------------------------
	GeoBlock::GeoBlock( GeoGlobalData* global_data , String imgpath )
	{
		setDefault();

		_globalData = global_data;
		_imgFilepath = imgpath;
	}
	//----------------------------------------------------------------
	GeoBlock::~GeoBlock()
	{


		if ( _buffer != NULL )
		{
			delete _buffer;
			_buffer = NULL;
		}
	}
	//----------------------------------------------------------------
	bool GeoBlock::open()
	{
		long width, height;

		vgImage::getImageFormatInfo( _imgFilepath, width, height);

		_width = width;
		_height = height;


		//------------------------------------------
		//	然后文件名开始
		//------------------------------------------
		String _metafilename = 
			vgKernel::StringUtility::getFilenameFromAbsolutePath( _imgFilepath );

		if ( _metafilename.find("origin") != String::npos )
		{
			_isOriginImage = true;
		}

		if ( _isOriginImage == true )
		{
			if ( (_width % 2) != 0 || 
				(_height%2) != 0 ) 
			{
				assert(0);
				return false;
			}

			assert( _level == -1);

			String::size_type lpos = _metafilename.find("origin");

			if ( lpos == String::npos )
			{
				return false;
			}
			String::size_type lpos2 = _metafilename.find_first_of("_" , lpos );

			String::size_type lpos3 = _metafilename.find_last_of("n" , lpos2 );

			_level = 
				vgKernel::ConvertUtility::textCast<long>( 
				_metafilename.substr( lpos3+1 , lpos2 - lpos3 - 1 ) );
			assert( _level >= 0 );
			assert( _level <= 15 );

#if _DEBUG
			int ratio = pow(2.0f , _level );
			assert( VGT_ORIGIN_IMG_SIZE / ratio  != 0 );

			assert( _width == VGT_ORIGIN_IMG_SIZE / ratio);
			assert( _height == VGT_ORIGIN_IMG_SIZE / ratio );
#endif

		}
		else
		{
			String::size_type lpos = _metafilename.find("level");

			if ( lpos == String::npos )
			{
				return false;
			}
			String::size_type lpos2 = _metafilename.find_first_of("_" , lpos );

			String::size_type lpos3 = _metafilename.find_last_of("l" , lpos2 );

			_level = 
				vgKernel::ConvertUtility::textCast<long>( 
				_metafilename.substr( lpos3+1 , lpos2 - lpos3 - 1 ) );

			//assert( _level != -1 );

			assert( _width == _globalData->_globalChunkSize  + 1);
			assert( _height == _globalData->_globalChunkSize  + 1 );

		}

		String::size_type pos1 = _metafilename.find_last_of(".");
		String::size_type pos2 = _metafilename.find_last_of("_");
		String::size_type pos3 = _metafilename.find_last_of("_" , pos2 - 1);

		_blockPosX = 
			vgKernel::ConvertUtility::textCast<long>( 
			_metafilename.substr( pos3 + 1, pos2 - pos3 ) );

		_blockPosY = 
			vgKernel::ConvertUtility::textCast<long>( 
			_metafilename.substr( pos2 + 1 , pos1 - pos2 ) );

		
		_bufferSizeInFloat = _width * _height;

		return true;
	}
	//----------------------------------------------------------------
	void GeoBlock::setDefault()
	{
		_isOriginImage = false;
		_globalData =NULL;

		_width = 0;
		_height = 0;
		_bufferSizeInFloat = 0;
		_buffer = NULL;
		_blockPosX = 0;
		_blockPosY = 0;


		_level = -1;
	}
	//----------------------------------------------------------------
	VgtrFilePtr GeoBlock::generateVgtr()
	{
		assert( _isOriginImage == false );
		assert( _buffer == NULL );
		assert( _width != 0 );

		assert( _width % 2 == 1 );

		long width = _globalData->_globalAdjustRect.getWidth() + 1;

		// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		long layer = _level;
		long pow_2_layer = (long)pow( 2.0f , layer );
		long worldwidth = width * _globalData->_globalAdjustCellsize;

		//------------------------------------------
		// 首先开始读取
		//------------------------------------------

#if 0
		CximageWrapper img;
		bool loadok = img.loadFromFile( _imgFilepath );

		assert( loadok == true );
		if ( loadok == false )
		{
			return VgtrFilePtr();
		}

		CxImage* cximage = img.getCximagePtr().getPointer();

		assert( cximage->AlphaIsValid() );

		// 申请float数据,配置
		_buffer = new float[ _bufferSizeInFloat ];
		memset( _buffer , 0 , _bufferSizeInFloat * sizeof( float ) );

		/**
			在这里上下反转!!!!注意!!!!!!!!!!!!!!!!!!!!!!!!!
		*/
		for ( int i = 0 ; i < _height ; ++ i )
		{
			for ( int j = 0 ; j < _width ; ++ j )
			{
				RGBQUAD quad = cximage->GetPixelColor( j ,_height - 1 - i , true );

				memcpy( _buffer + _width * i + j , &quad , sizeof( RGBQUAD ) );
			}
		}
#else

		using namespace vgImage;

		FreeImageWrapper img;
		bool loadok = img.loadFromFile( _imgFilepath );

		assert( loadok == true );
		if ( loadok == false )
		{
			return VgtrFilePtr();
		}

		assert( img.getBitsPerPixel() == 32 );

		img.flipVertical();

		_buffer = (float*)img.getAlignedPixelsCopy();
		assert( _buffer != NULL );
		if ( _buffer == NULL )
		{
			return VgtrFilePtr();
		}

#endif

		//------------------------------------------
		// 对边界进行处理!
		//------------------------------------------
		if ( _blockPosY == 0 )
		{
			memset( _buffer , 0 , _width * sizeof(float) );
		}

		if ( _blockPosX == 0 )
		{
			for ( int j = 0 ; j < _height ; ++ j )
			{
				_buffer[ j * _height ] = 0.0f;
			}
		}

		//------------------------------------------
		// 产生lod数据.注意!!这里先暂时不用lod!!只用空的数据
		// !!!!!!!!!!!!!
		//------------------------------------------

		long pow_2_N = _globalData->_globalChunkSize;

#if 0
		
		float* newdatalod1 = new float[ pow_2_N * pow_2_N / 4 ];
		memset( newdatalod1 , 0 , pow_2_N * pow_2_N / 4 * sizeof( float ) );

		float* newdatalod0 = new float[ pow_2_N * pow_2_N / 16 ];
		memset( newdatalod0 , 0 , pow_2_N * pow_2_N / 16 * sizeof( float ) );
#else


		float* newdatalod1 = new float[ 1 ];
		memset( newdatalod1 , 0 , 1 * sizeof( float ) );

		float* newdatalod0 = new float[ 1 ];
		memset( newdatalod0 , 0 , 1 * sizeof( float ) );

#endif

		//------------------------------------------
		// 开始赋值
		//------------------------------------------
		VgtrFilePtr tmp( new VgtrFile );
		tmp->_dataLod[VGLOD_CLEAR] = _buffer;
		tmp->_dataLod[VGLOD_CLEAR-1] = newdatalod1;
		tmp->_dataLod[VGLOD_CLEAR-2] = newdatalod0;
		tmp->_headerPtr.bind( new VgtrHeader );

		// 计算scale和bias的值.
		float s = (float)width / (float)pow_2_N / (float)pow_2_layer;
		float disscale = s / worldwidth;
		float disbiasX = _blockPosX;
		float disbiasZ = _blockPosY;
		tmp->_headerPtr->displaceChunkScale = disscale;
		tmp->_headerPtr->displaceChunkBiasX = disbiasX;
		tmp->_headerPtr->displaceChunkBiasZ = disbiasZ;


		std::ostringstream o;
		o << _globalData->_terrainName << 
			"_level" << layer << "_" << _blockPosX << "_" << _blockPosY;
		String tmpname = o.str();
		assert( tmpname.size() < VG_VGTR_NAME_LENGTH );

		strcpy( tmp->_headerPtr->name , tmpname.c_str() );

		String tmptex = tmpname + ".dds";
		assert( tmptex.size() < VG_VGTR_NAME_LENGTH );
		strcpy( tmp->_headerPtr->texname , tmptex.c_str() );

		tmp->_headerPtr->N = _globalData->_globalN;	


		//////////////////////////////////////////////////////////////////////////
		// cellTexSize不再使用!!!!!!!!!!!
		tmp->_headerPtr->cellTexSize = 2;	
		//////////////////////////////////////////////////////////////////////////

		// 注意这里的长宽
		//tmp->_headerPtr->xNum = pow_2_N + 1;	
		//tmp->_headerPtr->zNum = pow_2_N + 1;	
		assert( _width != 0 );
		tmp->_headerPtr->xNum = _width;	
		tmp->_headerPtr->zNum = _height;	

		tmp->_headerPtr->cellsize = _globalData->_globalAdjustCellsize;	

		//////////////////////////////////////////////////////////////////////////
		// 这里用统一原点!!!!!!!!!!
		// 当前所处的位置
		tmp->_headerPtr->originX = _globalData->_globalUpperLeftX;
		tmp->_headerPtr->originY = _globalData->_globalMinElevation;
		tmp->_headerPtr->originZ = _globalData->_globalUpperLeftY;

		tmp->_headerPtr->displaceScaleY = _globalData->_globalElevationScale;

		//////////////////////////////////////////////////////////////////////////

		// 注意这里是以字节为单位.
		tmp->_headerPtr->dataLen[VGLOD_CLEAR] = 
			_bufferSizeInFloat * sizeof( float );

#if 0 
		tmp->_headerPtr->dataLen[VGLOD_CLEAR-1] = 
			pow_2_N * pow_2_N * sizeof( float ) / 4;

		tmp->_headerPtr->dataLen[VGLOD_CLEAR-2] = 
			pow_2_N * pow_2_N * sizeof( float ) / 16;
#else

		tmp->_headerPtr->dataLen[VGLOD_CLEAR-1] = 
			1 * sizeof( float )  ;

		tmp->_headerPtr->dataLen[VGLOD_CLEAR-2] = 
			1 * sizeof( float )  ;
#endif
	

		_buffer = NULL;
	
		return tmp;
	}
	//----------------------------------------------------------------
	bool GeoBlock::saveToVgtr( String& out_vgtrname , String& out_debugimagename )
	{
		VgtrFilePtr pvgtr = generateVgtr();
		assert( pvgtr.isNull() == false );
		if ( pvgtr.isNull() == true )
		{
			return false;
		}

		String vgtrname = _globalData->_demDirectory + "\\" + 
			pvgtr->_headerPtr->name + ".vgtr" ;
		
		String debugname = _globalData->_debugImageDirectory + "\\" + 
			pvgtr->_headerPtr->name + "." + VGT_GEOMGR_TEMP_EXT;

		bool writeok = VgtrWriter::writeVgtrToFile( pvgtr , vgtrname );

		if ( writeok == true )
		{
			out_vgtrname = vgtrname;

			//------------------------------------------
			// 开始生成debug的图像
			//------------------------------------------
			CximageWrapperPtr img = generateDebugImgUsingVgtr( pvgtr );

			if ( img.isNull() == false )
			{
				bool saveok = img->saveToFile( debugname );
				assert( saveok == true );

				out_debugimagename = debugname;
			}

			//------------------------------------------
			// 删除临时文件
			//------------------------------------------
			_globalData->pushNeedToCleanFile( _imgFilepath );
			_globalData->cleanTempFiles();

			return true;
		}

		return false;
	}
	//----------------------------------------------------------------
	fileBlock* GeoBlock::getFileBlock()
	{
		assert( _isOriginImage == true );
		assert( _width == _height );

		fileBlock* ret = new fileBlock;

		ret->fileSrcName = _imgFilepath;
		ret->fileAbsoluteRect = ImageRect( 
			_blockPosX * _width , 
			_blockPosY * _height ,
			_blockPosX * _width + _width - 1 , 
			_blockPosY * _height + _height - 1 );

		return ret;
	}
	//----------------------------------------------------------------
	bool GeoBlock::isEmpty()
	{
		assert(0);

#if 0
		assert( _width != 0 );

		//------------------------------------------
		// 首先开始读取
		//------------------------------------------
		CximageWrapper img;
		bool loadok = img.loadFromFile( _imgFilepath );

		assert( loadok == true );
		if ( loadok == false )
		{
			return false;
		}

		CxImage* cximage = img.getCximagePtr().getPointer();

		assert( loadok == true );
		if ( loadok == false )
		{
			return false;
		}
		assert( cximage->AlphaIsValid() );

		//------------------------------------------
		// 开始检查
		// 注意了!!这里不能用GetBits拷贝.
		// 例如,_width为257,此时bits中的排列并不是顺序的!!
		//------------------------------------------
		for ( int i = 0 ; i < _width ; ++ i )
		{
			for ( int j = 0 ; j < _height ; ++ j )
			{
				RGBQUAD quad = cximage->GetPixelColor( i , j , true );

				if ( quad.rgbBlue != 0 || 
					quad.rgbGreen != 0 ||
					quad.rgbRed != 0 || 
					quad.rgbReserved != 0 )
				{
					return false;
				}
			}
		}

#endif

		return true;
	}
	//----------------------------------------------------------------
	bool GeoBlock::resize()
	{
		assert( _isOriginImage == true );
		assert( _width %2 == 0 );
		assert( _width != 0 );

		//------------------------------------------
		// 首先开始加载图像 
		//------------------------------------------
		FreeImageWrapper originImg;
		bool loadok = originImg.loadFromFile( _imgFilepath );

		assert( loadok == true );
		if ( loadok == false )
		{
			return false;
		}

		std::ostringstream o;
		o << _globalData->_demDirectory << "\\" << _globalData->_terrainName 
			<< "_origin"  << ( _level + 1 ) << "_" << _blockPosX << "_" << _blockPosY
			<< "." << VGT_GEOMGR_TEMP_EXT;

		String newfilename = o.str();
		assert(  _width % 2 == 0 );

		// 创建临时文件
		FreeImageWrapper tmpImg;

		long dwWidth = _width / 2;
		long dwHeight = _height / 2;

		tmpImg.createFromSize( dwWidth , dwHeight , 32 );


		//CxImage* src = originImg.getCximagePtr().getPointer();
		//CxImage* dst = tmpImg.getCximagePtr().getPointer();

#if 0
		for ( int i = 0 ; i < _width / 2 ; ++ i )
		{
			for ( int j = 0 ; j < _height / 2 ; ++ j )
			{
				//------------------------------------------
				// 注意!!!!!!这里取 j * 2 + 1
				// why???原因还不知道!!!!!!!!!!!!!
				//------------------------------------------
				//RGBQUAD quad = src->GetPixelColor( i * 2, j * 2 + 1, true );
				//dst->SetPixelColor( i , j , quad , true );
			}
		}
#else
		for ( int j = 0 ; j < _height / 2 ; ++ j )
		{
			BYTE* src = originImg.getScanLine( j * 2 + 1 );
			BYTE* dst = tmpImg.getScanLine( j );
			assert( src != NULL );
			assert( dst != NULL );

			for ( int x = 0 ; x < _width / 2 ; ++ x )
			{
				memcpy( dst ,src , 4 );

				src += 8;
				dst += 4;
			}
		}

#endif


		//------------------------------------------
		// 保存图像
		//------------------------------------------
		// 肯定是bmp格式
		bool saveok = tmpImg.saveToFile( newfilename );

		assert( saveok == true );
		if ( saveok == false )
		{
			MessageBox(NULL , "保存图像失败!","Error", MB_OK);
			return false;
		}

		//------------------------------------------
		// 删除数据
		//------------------------------------------
		originImg.release();
		tmpImg.release();

		//------------------------------------------
		//  重新设置
		//------------------------------------------
		_globalData->pushNeedToCleanFile( _imgFilepath );
		
		_isOriginImage = false;
		//_globalData =NULL;	//注意!这个不能变!!

		_width = 0;
		_height = 0;
		_bufferSizeInFloat = 0;
		_buffer = NULL;
		_blockPosX = 0;
		_blockPosY = 0;
		_level = -1;

		_imgFilepath = newfilename;

		//------------------------------------------
		// 重新打开文件
		//------------------------------------------
		return open();
	}
	//----------------------------------------------------------------
	CximageWrapperPtr GeoBlock::generateDebugImgUsingVgtr(VgtrFilePtr vgtrfile )
	{
		if ( _globalData->_genDebugImages == false )
		{
			return  CximageWrapperPtr();
		}

		vgTerritory::VgtrHeaderPtr header = vgtrfile->_headerPtr;

		float* data = vgtrfile->_dataLod[ VGLOD_CLEAR ];

		//------------------------------------------
		// 申请图像的内存并赋值
		//------------------------------------------
		long w = header->xNum;
		long h = header->zNum;
		assert( w % 2 == 1 );
		assert( w - 1 == _globalData->_globalChunkSize );

		uchar* imgdata = new uchar[ w * h * 3 ];
		memset( imgdata , 0 , w * h * 3 );


		for ( int i = 0 ; i < w * h ; ++ i )
		{
			if ( data[i] > 1.0f || data[i] < 0 )
			{
				assert(0 && "data[i] > 1.0f || data[i] < 0");
			}

			float curvalue = data[i];

			curvalue *= 10.0;

			uchar r = 0;
			uchar g = 0;
			uchar b = 0;

			if ( curvalue < 1.0 )
			{
				r = (curvalue) * 255;
			}
			else if( curvalue < 2.0 )
			{
				g = (curvalue - 1.0) * 255;
			}
			else if( curvalue < 3.0 )
			{
				b = (curvalue - 2.0) * 255;
			}
			else if( curvalue < 4.0 )
			{
				r = (curvalue - 3.0) * 255;
				g = 255;
			}
			else if( curvalue < 5.0 )
			{
				g = (curvalue - 4.0) * 255;
				b = 255;
			}
			else if( curvalue < 6.0 )
			{
				b = (curvalue - 5.0) * 255;
				g = 128;
			}
			else if( curvalue < 7.0 )
			{
				r = (curvalue - 6.0) * 255;
				g = 64;
			}
			else if( curvalue < 8.0 )
			{
				g = (curvalue - 7.0) * 255;
				b = 128;
			}
			else if( curvalue < 9.0 )
			{
				b = (curvalue - 8.0) * 255;
				r = 64;
			}
			else
			{
				r = (curvalue - 9.0) * 255;
				g = 128;
				b = 64;
			}

			//------------------------------------------
			// 背景色
			//------------------------------------------
			if ( r == 0 && g == 0 && b == 0 )
			{
				r = _globalData->_filledColor[2];
				g = _globalData->_filledColor[1];
				b = _globalData->_filledColor[0];
			}

			imgdata[ 3 * i ] = r;
			imgdata[ 3 * i + 1 ] = g;
			imgdata[ 3 * i + 2 ] = b;
		}

		CximageWrapperPtr ret( new CximageWrapper );

		bool createok = ret->cxCreateFromArray( (BYTE*)imgdata , w - 1, h - 1 , 24 , 
			w * 3 , true );

		if ( createok == false )
		{
			delete[] imgdata;
			return CximageWrapperPtr();
		}

		delete[] imgdata;
		return ret;
	}
	//----------------------------------------------------------------



}// end of namespace vgTerritory

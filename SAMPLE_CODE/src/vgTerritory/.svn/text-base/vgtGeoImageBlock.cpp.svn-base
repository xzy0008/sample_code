


#include <vgStableHeaders.h>
#include <vgTerritory/vgtGeoImageBlock.h>
#include <vgKernel/vgkConvertUtility.h>
#include <vgTerritory/vgVgtrWriter.h>

#include <vgImage/vgiFreeImageWrapper.h>
#include <vgImage/vgiCximageWrapper.h>

namespace vgTerritory {
	


	//----------------------------------------------------------------
	GeoImageBlock::GeoImageBlock( GeoGlobalData* global_data , String imgpath )
	{
		setDefault();

		_globalData = global_data;
		_imgFilepath = imgpath;
	}
	//----------------------------------------------------------------
	GeoImageBlock::~GeoImageBlock()
	{
		//if ( _cximage != NULL )
		//{
		//	delete _cximage;
		//	_cximage = NULL;
		//}

		//if ( _buffer != NULL )
		//{
		//	delete _buffer;
		//	_buffer = NULL;
		//}
	}
	//----------------------------------------------------------------
	bool GeoImageBlock::open()
	{
		//------------------------------------------
		// 读取文件
		//------------------------------------------

		CximageWrapperPtr tmpimg( new CximageWrapper );

		bool loadok = tmpimg->loadHeaderFromFile( _imgFilepath );

		if ( loadok == false )
		{
			return false;
		}

		_width = tmpimg->getWidth();
		_height = tmpimg->getHeight();

		tmpimg.setNull();

		//------------------------------------------
		//	然后文件名开始
		//------------------------------------------
		String _metafilename = 
			vgKernel::StringUtility::getFilenameFromAbsolutePath( _imgFilepath );

		if ( _metafilename.find("origin") != String::npos )
		{
			_isOriginImage = true;
		}

		assert( _isOriginImage == true );


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



		String::size_type pos1 = _metafilename.find_last_of(".");
		String::size_type pos2 = _metafilename.find_last_of("_");
		String::size_type pos3 = _metafilename.find_last_of("_" , pos2 - 1);

		_blockPosX = 
			vgKernel::ConvertUtility::textCast<long>( 
			_metafilename.substr( pos3 + 1, pos2 - pos3 ) );

		_blockPosY = 
			vgKernel::ConvertUtility::textCast<long>( 
			_metafilename.substr( pos2 + 1 , pos1 - pos2 ) );


		return true;
	}
	//----------------------------------------------------------------
	void GeoImageBlock::setDefault()
	{
		_isOriginImage = false;
		_globalData =NULL;
		//_cximage = NULL;
		_width = 0;
		_height = 0;


		_blockPosX = 0;
		_blockPosY = 0;


		_level = -1;
	}
	////----------------------------------------------------------------
	//fileBlock* GeoImageBlock::getFileBlock()
	//{
	//	assert( _isOriginImage == true );
	//	assert( _width == _height );

	//	fileBlock* ret = new fileBlock;

	//	ret->fileSrcName = _imgFilepath;
	//	ret->fileAbsoluteRect = ImageRect( 
	//		_blockPosX * _width , 
	//		_blockPosY * _height ,
	//		_blockPosX * _width + _width - 1 , 
	//		_blockPosY * _height + _height - 1 );

	//	return ret;
	//}
	//----------------------------------------------------------------
	bool GeoImageBlock::isEmpty()
	{
		assert( _width != 0 );

		//assert( _cximage == NULL );

		vgImage::CximageWrapper img;
		bool loadok = img.loadFromFile( _imgFilepath );

		assert( loadok == true );
		if ( loadok == false )
		{
			return false;
		}

		CxImage* cximage = img.getCximagePtr()/*.getPointer()*/;

		assert( loadok == true );
		if ( loadok == false )
		{
			return false;
		}
		//assert( _cximage->AlphaIsValid() );

		//------------------------------------------
		// 开始检查
		// 注意了!!这里不能用GetBits拷贝.
		// 例如,_width为257,此时bits中的排列并不是顺序的!!
		//------------------------------------------
		for ( int i = 0 ; i < _width ; ++ i )
		{
			for ( int j = 0 ; j < _height ; ++ j )
			{
				RGBQUAD quad = cximage->GetPixelColor( i , j , false );

				if ( quad.rgbBlue != 0 || 
					quad.rgbGreen != 0 ||
					quad.rgbRed != 0 /*|| 
					quad.rgbReserved != 0 */)
				{
					return false;
				}
			}
		}

		return true;
	}
	//----------------------------------------------------------------
	bool GeoImageBlock::resize()
	{
		assert( _isOriginImage == true );
		assert( _width %2 == 0 );
		assert( _width != 0 );
		//assert( _cximage == NULL );

		//------------------------------------------
		// 首先开始加载图像 
		//------------------------------------------

		FreeImageWrapperPtr pimg( new FreeImageWrapper );

		bool loadok = pimg->loadFromFile( _imgFilepath );

		assert( loadok == true );

		if ( loadok == false )
		{
			return false;
		}

		std::ostringstream o;
		o << _globalData->_imageDirectory << "\\" << _globalData->_terrainName 
			<< "_origin"  << ( _level + 1 ) << "_" << _blockPosX << "_" << _blockPosY
			<< "." << VGT_GEOMGR_TEMP_EXT;

		String newfilename = o.str();

		//////////////////////////////////////////////////////////////////////////
		bool resizeok = pimg->resize( ImageSize( _width / 2 , _height / 2 ) );

		if ( resizeok == false )
		{
			return false;
		}

#if 0
		//------------------------------------------
		// 开始进行边界处理!!
		//------------------------------------------
		long maxblack = 1;
		//if ( _level == _globalData->_maxLayerNum - 1  )
		//{
		//	maxblack = 25;
		//}

		if ( _blockPosY == 0 )
		{
			RGBQUAD black;
			black.rgbBlue = 0;
			black.rgbGreen = 0 ;
			black.rgbRed = 0 ;
			black.rgbReserved  = 255 ;
			for ( int i = 0 ; i < _width / 2 ; ++ i )
			{
				for ( int j = 0 ; j < maxblack ; ++j )
				{
					pimg->getCximagePtr()->SetPixelColor( i , _height / 2 - 1 - j , 
						black , true );
				}
			}
		}

		if ( _blockPosX == 0 )
		{
			RGBQUAD black;
			black.rgbBlue = 0;
			black.rgbGreen = 0 ;
			black.rgbRed = 0 ;
			black.rgbReserved  = 255 ;
			for ( int i = 0 ; i < _height / 2 ; ++ i )
			{
				for ( int j = 0 ; j < maxblack ; ++j )
				{
					pimg->getCximagePtr()->SetPixelColor( j , i , 
						black , true );
				}
			}
		}

#endif


		bool saveok = pimg->saveToFile( newfilename );

		if ( saveok == false )
		{
			return false;
		}

		//------------------------------------------
		//  重新设置
		//------------------------------------------
		_globalData->pushNeedToCleanFile( _imgFilepath );
		_globalData->cleanTempFiles();

		_isOriginImage = true;
		//_globalData =NULL;	//注意!这个不能变!!

		_width = 0;
		_height = 0;

		_blockPosX = 0;
		_blockPosY = 0;
		_level = -1;

		_imgFilepath = newfilename;

		//------------------------------------------
		// 重新打开文件
		//------------------------------------------
		return open();
		

		//assert(  _width % 2 == 0 );

		//CxImage* tmp = new CxImage;

		//long dwWidth = _width / 2;
		//long dwHeight = _height / 2;
		//byte* buf = new byte[ 4 * dwWidth * dwHeight ];
		//memset( buf , 0  , 4 * dwWidth * dwHeight );

		//bool create_result = 
		//	tmp->CreateFromArray( (BYTE*)buf , dwWidth , dwHeight , 32 , 
		//	dwWidth * 4 , false );

		//if ( create_result == false )
		//{
		//	assert(0);
		//}

		//for ( int i = 0 ; i < _width / 2 ; ++ i )
		//{
		//	for ( int j = 0 ; j < _height / 2 ; ++ j )
		//	{
		//		//------------------------------------------
		//		// 注意!!!!!!这里取 j * 2 + 1
		//		// why???原因还不知道!!!!!!!!!!!!!
		//		//------------------------------------------
		//		RGBQUAD quad = _cximage->GetPixelColor( i * 2, j * 2 + 1, true );
		//		tmp->SetPixelColor( i , j , quad , true );
		//	}
		//}

		//delete _cximage;
		//_cximage = tmp;
		////////////////////////////////////////////////////////////////////////////
		////bool resizeok = _cximage->Resample2( _width / 2 , _height / 2 , 
		////	CxImage::IM_NEAREST_NEIGHBOUR ,
		////	CxImage::OM_REPEAT , NULL );
		////assert( resizeok == true );

		////if ( resizeok == false )
		////{
		////	MessageBox(NULL , "重建图像失败!","Error", MB_OK);
		////	return false;
		////}

		//bool saveok = _cximage->Save( newfilename.c_str() , CXIMAGE_FORMAT_TGA );

		//assert( saveok == true );

		//if ( saveok == false )
		//{
		//	MessageBox(NULL , "保存图像失败!","Error", MB_OK);
		//	return false;
		//}

		//if ( _cximage != NULL )
		//{
		//	delete _cximage;
		//	_cximage = NULL;
		//}

		////------------------------------------------
		////  重新设置
		////------------------------------------------
		//_globalData->pushNeedToCleanFile( _imgFilepath );

		//_isOriginImage = false;
		////_globalData =NULL;	//注意!这个不能变!!
		//_cximage = NULL;
		//_width = 0;
		//_height = 0;

		//_blockPosX = 0;
		//_blockPosY = 0;
		//_level = -1;

		//_imgFilepath = newfilename;

		////------------------------------------------
		//// 重新打开文件
		////------------------------------------------
		//return open();
	}
	//----------------------------------------------------------------
	fileBlock* GeoImageBlock::getFileBlock()
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

	
	
}// end of namespace vgTerritory

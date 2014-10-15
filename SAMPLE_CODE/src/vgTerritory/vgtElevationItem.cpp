



#include <vgStableHeaders.h>
#include <vgTerritory/vgtElevationItem.h>
#include <vgTerritory/vgtFileHandleVtr.h>
#include <vgTerritory/vgTerrainGpuProgram.h>
#include <vgTerritory/vgtTerrainManager.h>
#include <vgImage/vgiTextureManager.h>
#include <vgKernel/vgkConvertUtility.h>
#include <vgTerritory/vgtDefinition.h>
#include <vgTerritory/vgtIoRequestElevationRetrive.h>

#include <vgKernel/vgkPlane.h>

#include <vgTerritory/vgtElevationFilter.h>



#include <vgKernel/vgkOpenGLSupport.h>

namespace vgTerritory {


	GLuint ElevationItem::s_emptyTextureId  = VG_NULL_TEXTURE_ID;
	GLuint ElevationItem::s_emptyElevationTextureId = VG_NULL_TEXTURE_ID;
	
	//----------------------------------------------------------------
	ElevationItem::ElevationItem( VtrBrief* brief , FileHandleVtr* vtrfilehandle )
	{
		_refCount = 0;

		_vtrFilehandle = vtrfilehandle;

		_bWithInSelectPolygon = false;
		_pOgrGeo = NULL;

		if ( brief == NULL )
		{
			//------------------------------------------
			// 此时创建空的ElevationItem
			//------------------------------------------
			_isEmptyItem = true;

			_gpuProgram = TerrainManager::getSingleton().getGpuProgramPtr();
			_metaFilename = "Empty ElevationItem";

			for ( int i = 0 ; i < VGLOD_N ; ++ i )
			{
				_elevLod[i] = NULL;
				_refElev[i] = NULL;
			}
			_metaFileInfo = NULL;
			_texObs = NULL;

			 _displaceScaleY = 100.0f;
			 _displaceChunkScale = 1.0f;
			 _displaceChunkBiasX = 0.0f;
			 _displaceChunkBiasZ = 0.0f;

		}
		else
		{
			_isEmptyItem = false;

			_gpuProgram = NULL;
			assert( vtrfilehandle != NULL );
			assert( brief != NULL );

			_metaFilename = brief->_fileName;

			for ( int i = 0 ; i < VGLOD_N ; ++ i )
			{
				_elevLod[i] = NULL;
				_refElev[i] = NULL;
			}

			for ( int i = 0 ; i < VGLOD_N ; ++ i )
			{
				_elevLod[i] = new Elevation( this , brief , vtrfilehandle , i );
			}

			_metaFileInfo = new vgAsyn::FileInfo( brief->_fileName , vtrfilehandle ,
				brief->_metaFileOffset , brief->_metaFileSize);

			_heightMapWidth = brief->_vgtrHeader.xNum;
			_metaTexFilename = brief->_vgtrHeader.texname;
			_displaceScaleY = brief->_vgtrHeader.displaceScaleY;	
			_displaceChunkScale = brief->_vgtrHeader.displaceChunkScale;	
			_displaceChunkBiasX = brief->_vgtrHeader.displaceChunkBiasX;	
			_displaceChunkBiasZ = brief->_vgtrHeader.displaceChunkBiasZ;	

			_gpuProgram = TerrainManager::getSingleton().getGpuProgramPtr();

			_texObs = NULL;

		}


		//------------------------------------------
		// 查找level和block num
		//------------------------------------------
		_level = 0;
		_blockX = 0;
		_blockZ = 0;

		if ( _isEmptyItem == false )
		{
			String::size_type lpos = _metaFilename.find("level");

			assert( lpos != String::npos );


			String::size_type pos1 = _metaFilename.find_last_of(".");
			String::size_type pos2 = _metaFilename.find_last_of("_");
			String::size_type pos3 = _metaFilename.find_last_of("_" , pos2 - 1);

			String::size_type lpos2 = _metaFilename.find_first_of("_" , lpos );
			String::size_type lpos3 = _metaFilename.find_last_of("l" , lpos2 );

			_level = 
				vgKernel::ConvertUtility::textCast<long>( 
				_metaFilename.substr( lpos3+1 , lpos2 - lpos3 - 1 ) );

			_blockX = 
				vgKernel::ConvertUtility::textCast<long>( 
				_metaFilename.substr( pos3 + 1, pos2 - pos3 ) );

			_blockZ = 
				vgKernel::ConvertUtility::textCast<long>( 
				_metaFilename.substr( pos2 + 1 , pos1 - pos2 ) );

		}
	}
	//----------------------------------------------------------------
	ElevationItem::~ElevationItem()
	{
		deleteEmptyTextureId();
		deleteEmptyElevationTextureId();

		for ( int i = 0 ; i < VGLOD_N ; ++ i )
		{
			if ( _refElev[i] != NULL )
			{
				_refElev[i]->releaseReference();
				_refElev[i] = NULL;
			}

			if ( _elevLod[i] != NULL )
			{
				delete _elevLod[i];
				_elevLod[i] = NULL;
			}
		}

		if ( _metaFileInfo != NULL )
		{
			delete _metaFileInfo;
			_metaFileInfo = NULL;
		}

		if ( _pOgrGeo != NULL )
		{
			_pOgrGeo = NULL;
		}
	}
	//----------------------------------------------------------------
	void ElevationItem::useBindInGpuProgram()
	{
		if ( _elevLod[0] == NULL )
		{
			if ( s_emptyTextureId == VG_NULL_TEXTURE_ID )
			{
				createEmptyTextureId();
			}

			if ( s_emptyElevationTextureId == VG_NULL_TEXTURE_ID )
			{
				createEmptyElevationTextureId();
			}

			// 为空的Item
			_gpuProgram->setDecalUVParamsEveryFrame(
				s_emptyTextureId , _displaceParams );
			_gpuProgram->setHeightMapIdEveryFrame( 
				s_emptyElevationTextureId );

			return;
		}

		//------------------------------------------
		// 正常条件下的set
		//------------------------------------------
		if ( _texObs == NULL )
		{
			if ( s_emptyTextureId == VG_NULL_TEXTURE_ID )
			{
				createEmptyTextureId();
			}

			_gpuProgram->setDecalUVParamsEveryFrame(
				s_emptyTextureId , _displaceParams );
		}
		else
		{
			_texObs->useBind();

			//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S ,GL_CLAMP_TO_BORDER);
			//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T ,GL_CLAMP_TO_BORDER);

			//if ( _isBorderImage == true )
			//{
			//	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
			//		GL_LINEAR );
			//}
			//else
			//{
			//	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
			//		GL_LINEAR_MIPMAP_LINEAR );
			//}



			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S ,GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T ,GL_CLAMP_TO_EDGE);


			_gpuProgram->setDecalUVParamsEveryFrame(
				_texObs->getTextureID() , _displaceParams );
		}

		//------------------------------------------
		// 查找最清晰的一级绑定
		//------------------------------------------
		

		_gpuProgram->setHeightMapIdEveryFrame( 
			_elevLod[VGLOD_CLEAR]->getHeightMapID() );

		return;
		assert(0);

		for ( int i = VGLOD_CLEAR ; i >=0 ; -- i )
		{
			if ( _elevLod[i]->isEmptyHeightMap() == false )
			{

				_gpuProgram->setHeightMapIdEveryFrame( 
					_elevLod[i]->getHeightMapID() );

				return;
			}
		}

		_gpuProgram->setHeightMapIdEveryFrame( 
			_elevLod[ VGLOD_COARSE ]->getHeightMapID() );

		return;
	}
	//----------------------------------------------------------------
	void ElevationItem::addViewRef()
	{
		if ( _elevLod[0] == NULL )
		{
			// Empty ElevationItem
			return;
		}

		++_refCount;

		if ( _refCount == 1 )
		{
			//------------------------------------------
			// 这个时候需要载入
			//------------------------------------------
			assert( _refElev[ VGLOD_CLEAR ] == NULL );

			_refElev[ VGLOD_CLEAR ] = _elevLod[ VGLOD_CLEAR ];
			_refElev[ VGLOD_CLEAR ]->addReference();

			assert( _texObs == NULL );

			_texObs = vgImage::TextureManager::getSingleton().getTextureObserver( 
				_metaTexFilename , VGLOD_CLEAR );

			if ( _texObs != NULL )
			{
				_texObs->addRef();
			}
		}

	}
	//----------------------------------------------------------------
	void ElevationItem::releaseViewRef()
	{
		if ( _elevLod[0] == NULL )
		{
			// Empty ElevationItem
			return;
		}

		assert( _refCount > 0 );

		-- _refCount;

		if ( _refCount == 0 )
		{
			//------------------------------------------
			// 此时需要卸载掉
			//------------------------------------------
			if ( _refElev[ VGLOD_CLEAR ] != NULL )
			{
				_refElev[ VGLOD_CLEAR ]->releaseReference();
				_refElev[ VGLOD_CLEAR ] = NULL;
			}

			if ( _texObs != NULL )
			{
				_texObs->releaseRef();
				_texObs = NULL;
			}
		}

	}
	//----------------------------------------------------------------
	bool ElevationItem::getElevationByPosInMemory( const Vec3& pos , 
		float& out_elevation )
	{
		if ( _vtrFilehandle == NULL )
		{
			return false;
		}

		//------------------------------------------
		// 创建需要读取的fileinfo
		//------------------------------------------
		float u = pos.x * _displaceChunkScale - _displaceChunkBiasX;
		float v = pos.z * _displaceChunkScale - _displaceChunkBiasZ;

		float w =  _heightMapWidth - 1;

		long imgx = floor( u *  w );
		long imgy = floor( v * w );

		assert( imgx != _heightMapWidth );
		assert( imgy != _heightMapWidth );

		// 检查是否越界            
		if ( imgx < 0 || 
			imgx > (_heightMapWidth - 1)||
			imgy < 0 || 
			imgy > (_heightMapWidth - 1))
		{
			assert(0);
			return false;
		}

		Elevation* elev = _elevLod[ VGLOD_CLEAR ];
		assert( elev != NULL );

		if ( elev->getHeightMapBuffer() == NULL )
		{
			return false;
		}

		//------------------------------------------
		// 开始分别求高程值.
		// 如果在内存中,则从内存里面读数据.
		//------------------------------------------
		float result = 0.0f;

		float* buf = elev->getHeightMapBuffer();

		assert( elev->getBufferHeightMapWidth() == _heightMapWidth );

		// 计算偏移
		long offset = imgx + imgy *  _heightMapWidth;

		float elevations[4];

		elevations[ VGT_LEFT_UP ] = buf[ offset ];
		elevations[ VGT_RIGHT_UP ] = buf[ offset + 1 ];
		elevations[ VGT_LEFT_DOWN ] = buf[ offset + _heightMapWidth ];
		elevations[ VGT_RIGHT_DOWN ] = buf[ offset + _heightMapWidth + 1 ];

		for ( int i = 0 ; i < 4 ; ++ i )
		{
			elevations[i] *= _displaceScaleY;
		}
		//------------------------------------------
		// 开始插值
		//------------------------------------------
		float cellsize = _vtrFilehandle->getHeader()->cellsize;

		float x = ( u *  w - floor( u *  w ) );
		float z = ( v *  w - floor( v *  w ) );

		if ( x + z < 1.0f )
		{
			vgKernel::Plane plane(
				vgKernel::Vec3( 0 , elevations[ VGT_LEFT_UP ] , 0) , 
				vgKernel::Vec3( 1 , elevations[ VGT_RIGHT_UP ] , 0 ) , 
				vgKernel::Vec3( 0 , elevations[ VGT_LEFT_DOWN ] , 1 ) );

			float tmp = plane._normal.x * x + plane._normal.z * z + plane._distance;

			// 注意tmp是负号
			result = -tmp / plane._normal.y;
		}
		else
		{
			vgKernel::Plane plane(
				vgKernel::Vec3( 1 , elevations[ VGT_RIGHT_UP ] , 0) , 
				vgKernel::Vec3( 0 , elevations[ VGT_LEFT_DOWN ] , 1 ) , 
				vgKernel::Vec3( 1 , elevations[ VGT_RIGHT_DOWN ] , 1 ) );

			float tmp = plane._normal.x * x + plane._normal.z * z + plane._distance;

			// 注意tmp是负号
			result = -tmp / plane._normal.y;
		}


		out_elevation = result;

		return true;
	}
	//----------------------------------------------------------------
	bool ElevationItem::getElevationByPosInDisk( const Vec3& pos , float& out_elevation )
	{
		if ( _vtrFilehandle == NULL )
		{
			return false;
		}

		//------------------------------------------
		// 精确模式
		//------------------------------------------
		Elevation* elev = _elevLod[ VGLOD_CLEAR ];
		assert( elev != NULL );

		//------------------------------------------
		// 创建需要读取的fileinfo
		//------------------------------------------
		float u = pos.x * _displaceChunkScale - _displaceChunkBiasX;
		float v = pos.z * _displaceChunkScale - _displaceChunkBiasZ;

		float w =  _heightMapWidth - 1;

		long imgx = floor( u *  w );
		long imgy = floor( v * w );

		assert( imgx != _heightMapWidth );
		assert( imgy != _heightMapWidth );

		// 检查是否越界
		if ( imgx < 0 || 
			imgx > (_heightMapWidth - 1)||
			imgy < 0 || 
			imgy > (_heightMapWidth - 1))
		{
			assert(0);
			return false;
		}

		//------------------------------------------
		// 开始分别求高程值.
		// 如果在内存中,则从内存里面读数据.
		//------------------------------------------
		float result = 0.0f;

		//------------------------------------------
		// 这个时候从外存请求读入
		//------------------------------------------
		// 计算偏移
		long offset = imgx * 4 + imgy * 4 *  _heightMapWidth;

		//------------------------------------------
		// 分别读相邻的4个高程值
		//------------------------------------------
		vgAsyn::FileInfo* aimfileinfo = elev->getFileInfoClone();

		aimfileinfo->_fileOffset += offset;
		aimfileinfo->_fileSize = 
			sizeof( float ) * ( _heightMapWidth + 2 );

		assert( offset < elev->getFileInfoPtr()->_fileSize );
		assert( offset + aimfileinfo->_fileSize  <= elev->getFileInfoPtr()->_fileSize );

		//------------------------------------------
		// 开始申请IO,注意是同步模式
		//------------------------------------------
		IoRequestElevationRetrive request( aimfileinfo , _displaceScaleY );
		request.sendRequestAndDoAsynHandlerFunc( true );

		float* elevations = request.getElevation();

		//////////////////////////////////////////////////////////////////////////

		//------------------------------------------
		// 注意!在这里开始过滤!!!!
		//------------------------------------------

		ElevationFilter::getSingleton().doFilterPoint( this ,
			elevations[ VGT_LEFT_UP ] , imgx , imgy );

		ElevationFilter::getSingleton().doFilterPoint( this ,
			elevations[ VGT_LEFT_DOWN ] , imgx , imgy + 1);

		ElevationFilter::getSingleton().doFilterPoint( this ,
			elevations[ VGT_RIGHT_UP ] , imgx + 1 , imgy );

		ElevationFilter::getSingleton().doFilterPoint( this ,
			elevations[ VGT_RIGHT_DOWN ] , imgx + 1, imgy + 1);

		//////////////////////////////////////////////////////////////////////////

		//------------------------------------------
		// 开始插值
		//------------------------------------------
		float cellsize = _vtrFilehandle->getHeader()->cellsize;

		float x = ( u *  w - floor( u *  w ) );
		float z = ( v *  w - floor( v *  w ) );

		if ( x < 0.5f )
		{
			vgKernel::Plane plane(
				vgKernel::Vec3( 0 , elevations[ VGT_LEFT_UP ] , 0) , 
				vgKernel::Vec3( 1 , elevations[ VGT_RIGHT_UP ] , 0 ) , 
				vgKernel::Vec3( 0 , elevations[ VGT_LEFT_DOWN ] , 1 ) );

			float tmp = plane._normal.x * x + plane._normal.z * z + plane._distance;

			// 注意tmp是负号
			result = -tmp / plane._normal.y;
		}
		else
		{
			vgKernel::Plane plane(
				vgKernel::Vec3( 1 , elevations[ VGT_RIGHT_UP ] , 0) , 
				vgKernel::Vec3( 0 , elevations[ VGT_LEFT_DOWN ] , 1 ) , 
				vgKernel::Vec3( 1 , elevations[ VGT_RIGHT_DOWN ] , 1 ) );

			float tmp = plane._normal.x * x + plane._normal.z * z + plane._distance;

			// 注意tmp是负号
			result = -tmp / plane._normal.y;
		}


		out_elevation = result;
		return true;
	}
	//----------------------------------------------------------------
	bool ElevationItem::getElevationByPos( const Vec3& pos , float& out_elevation )
	{
		if ( getElevationByPosInMemory( pos , out_elevation ) == true )
		{
			return true;
		}

		return getElevationByPosInDisk( pos , out_elevation );
	}
	//----------------------------------------------------------------
	Vec3 ElevationItem::mappingVertexToUV( const Vec3& world_vertex , 
		const bool& map_height )
	{
		Vec3 ret;

		if ( map_height )
		{
			ret.y = world_vertex.y / _displaceScaleY;
		}
		else
		{
			ret.y = world_vertex.y;
		}

		ret.x = world_vertex.x  * _displaceChunkScale - _displaceChunkBiasX;
		ret.z = world_vertex.z  * _displaceChunkScale - _displaceChunkBiasZ;

		return ret;
	}
	//----------------------------------------------------------------
	Vec2 ElevationItem::mappingVertexToUV( const Vec2& world_vertex )
	{
		Vec2 ret;

		ret.x = world_vertex.x  * _displaceChunkScale - _displaceChunkBiasX;
		ret.y = world_vertex.y  * _displaceChunkScale - _displaceChunkBiasZ;

		return ret;
	}
	//----------------------------------------------------------------
	Vec2 ElevationItem::mappingVertexToGrid( const Vec2& world_vertex )
	{
		Vec2 ret = mappingVertexToUV( world_vertex );

		float w =  _heightMapWidth - 1;

		ret.x *= w;
		ret.y *= w;

		return ret;
	}
	//----------------------------------------------------------------
	ImagePos ElevationItem::mappingVertexToImagePos( 
		const Vec2& world_vertex )
	{
		ImagePos ret;

		Vec2 tmp = mappingVertexToGrid( world_vertex );

		ret.x = floor( tmp.x );
		ret.y = floor( tmp.y );

		return ret;
	}
	//----------------------------------------------------------------
	void ElevationItem::deleteEmptyTextureId()
	{
		if ( s_emptyTextureId != VG_NULL_TEXTURE_ID )
		{
			glDeleteTextures( 1, &s_emptyTextureId );
			s_emptyTextureId = VG_NULL_TEXTURE_ID;
		}
	}
	//----------------------------------------------------------------
	void ElevationItem::deleteEmptyElevationTextureId()
	{
		if ( s_emptyElevationTextureId != VG_NULL_TEXTURE_ID )
		{
			glDeleteTextures( 1, &s_emptyElevationTextureId );
			s_emptyElevationTextureId = VG_NULL_TEXTURE_ID;
		}
	}
	//----------------------------------------------------------------
	void ElevationItem::createEmptyTextureId()
	{
		assert( s_emptyTextureId == VG_NULL_TEXTURE_ID );
		if ( s_emptyTextureId != VG_NULL_TEXTURE_ID )
		{
			return;
		}

		assert( _vtrFilehandle != NULL );
		VGK_CHECK_OPENGL_ERROR();

		//unsigned char color[4] = { 127, 153 , 204, 255 };
		//unsigned char vtrcolor[4] = { 255, 1 , 1, 255 };

		uchar* vtrcolor = _vtrFilehandle->getHeader()->_filledColor;

		glGenTextures( 1, &s_emptyTextureId );
		assert( s_emptyTextureId != VG_NULL_TEXTURE_ID );
		glBindTexture( GL_TEXTURE_2D, s_emptyTextureId );

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S ,GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T ,GL_CLAMP_TO_EDGE);

		glTexImage2D( GL_TEXTURE_2D , 0 , GL_RGBA , 
			1, 1 , 
			0 , GL_RGBA , GL_UNSIGNED_BYTE , vtrcolor );

		VGK_CHECK_OPENGL_ERROR();

		return;
	}
	//----------------------------------------------------------------
	void ElevationItem::createEmptyElevationTextureId()
	{
		assert( s_emptyElevationTextureId == VG_NULL_TEXTURE_ID );
		if ( s_emptyElevationTextureId != VG_NULL_TEXTURE_ID )
		{
			return;
		}

		assert( _vtrFilehandle != NULL );
		VGK_CHECK_OPENGL_ERROR();

		float data = 0.0f;


		glGenTextures( 1, &s_emptyElevationTextureId );
		glBindTexture( GL_TEXTURE_2D, s_emptyElevationTextureId );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);


		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S ,GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T ,GL_CLAMP_TO_EDGE);

		//gluBuild2DMipmaps(GL_TEXTURE_2D, GL_LUMINANCE_FLOAT32_ATI, w, 
		//	h , GL_LUMINANCE, GL_FLOAT,  data );

		glTexImage2D(GL_TEXTURE_2D, 0 , GL_LUMINANCE_FLOAT32_ATI, 1, 
			1 , 0 , GL_LUMINANCE, GL_FLOAT,  &data );

		assert( s_emptyElevationTextureId != 0 );

		VGK_CHECK_OPENGL_ERROR();

		return;
	}

	//----------------------------------------------------------------
	bool ElevationItem::testIntersection( const ElevationBound& bound )
	{
		ElevationBound tmp;

		tmp.minPos = mappingVertexToUV( bound.minPos );
		tmp.maxPos = mappingVertexToUV( bound.maxPos );

		return tmp.testIntersection( ElevationBound::UNIT_BOUND );
	}
	//----------------------------------------------------------------



}// end of namespace vgTerritory




#include <vgStableHeaders.h>
#include <vgTerritory/vgtElevation.h>
#include <vgTerritory/vgtIoRequestElevation.h>

#include <vgKernel/vgkOpenGLSupport.h>

namespace vgTerritory {


	//----------------------------------------------------------------
	Elevation::Elevation( ElevationItem* father , VtrBrief* brief , 
		vgAsyn::FileHandle* pfilehandle  , int lod )
	{
		assert( lod >= 0 );
		assert( lod < VGLOD_N );
		assert( pfilehandle != NULL );

		_referenceCount = 0;
		_lod = lod;

		_fatherItem = father;
		// 设定初始值
		_lodInfo = NULL;

		//------------------------------------------
		// 开始赋值Fileinfo
		//------------------------------------------
		_lodInfo = new vgAsyn::FileInfo( brief->_fileName , pfilehandle ,
			brief->_metaFileOffset + brief->_vgtrHeader.dataPosition[ lod ] ,
			brief->_vgtrHeader.dataLen[ lod ] );

		_heightMapID = VG_NULL_TEXTURE_ID;

		_heightMapBuffer = NULL;
		_heightMapBufWidth = 0;
		_heightMapBufHeight = 0;
	}
	//----------------------------------------------------------------
	Elevation::~Elevation()
	{
		if ( _lodInfo != NULL )
		{
			delete _lodInfo;
			_lodInfo = NULL;
		}

		if ( _heightMapID != VG_NULL_TEXTURE_ID )
		{
			glDeleteTextures( 1 , &_heightMapID );
			_heightMapID = VG_NULL_TEXTURE_ID;
		}

		if ( _heightMapBuffer != NULL )
		{
			delete[] _heightMapBuffer;
			_heightMapBuffer = NULL;
		}
	}
	//----------------------------------------------------------------
	void Elevation::addReference()
	{
		++_referenceCount;

		if ( _referenceCount == 1 )
		{	
			// 这个时候需要载入
			
			assert( _heightMapID == VG_NULL_TEXTURE_ID );

			assert( _fatherItem != NULL );

			vgAsyn::IoRequest* request = NULL;
			//vgAsyn::FileInfo* fileinfo = _lodInfo->clone();

			
			// 目前只测试最清晰一级的
			assert( _lod ==  VGLOD_CLEAR );

			request = 	new IoRequestElevation( this );

			// 设定优先级
			if ( _lod == VGLOD_CLEAR )
			{
				request->setPriority( true );
			}

			//------------------------------------------
			// 注意!为同步模式!
			//------------------------------------------
			request->sendRequestAndDoAsynHandlerFunc( true );
		}
	}
	//----------------------------------------------------------------
	void Elevation::releaseReference()
	{
		assert( _referenceCount > 0 );

		if ( _referenceCount <= 0 )
		{
			assert(0);
		}

		if ( _referenceCount == 0 )
		{
			return;
		}

		--_referenceCount;

		if ( _referenceCount == 0 )
		{
			// 这个时候需要载出
			if ( _heightMapID != VG_NULL_TEXTURE_ID )
			{
				glDeleteTextures( 1 , &_heightMapID );
				_heightMapID = VG_NULL_TEXTURE_ID;
			}

			if ( _heightMapBuffer != NULL )
			{
				delete[] _heightMapBuffer;
				_heightMapBuffer = NULL;
			}
		}
	}
	//----------------------------------------------------------------
	bool Elevation::setHeightMapID( void* buffer, long buf_size )
	{
		assert( buffer != NULL );
		if ( buffer == NULL )
		{
			return false;
		}

		assert( buf_size == _lodInfo->_fileSize );

		if ( buf_size != _lodInfo->_fileSize )
		{
			return false;
		}

		int w = _fatherItem->getHeightMapWidth();

		assert( (w * w * sizeof(float)) == buf_size );

		if ( (w * w * sizeof(float)) != buf_size )
		{
			return false;
		}

		float* data = (float*)buffer;

		GLuint texid = 0;
		glGenTextures( 1, &texid );
		glBindTexture( GL_TEXTURE_2D, texid );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);


		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S ,GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T ,GL_CLAMP_TO_EDGE);


		//gluBuild2DMipmaps(GL_TEXTURE_2D, GL_LUMINANCE_FLOAT32_ATI, w, 
		//	h , GL_LUMINANCE, GL_FLOAT,  data );

		glTexImage2D(GL_TEXTURE_2D, 0 , GL_LUMINANCE_FLOAT32_ATI, w, 
			w , 0 , GL_LUMINANCE, GL_FLOAT,  data );


		assert( texid != 0 );

		VGK_CHECK_OPENGL_ERROR();

		_heightMapID = texid;

		return true;
	}
	//----------------------------------------------------------------
	float* Elevation::getHeightMapBuffer()
	{
		if ( _heightMapID == VG_NULL_TEXTURE_ID )
		{
			return NULL;
		}

		if ( _heightMapBuffer != NULL )
		{
			return _heightMapBuffer;
		}

		assert( _heightMapBuffer == NULL );
		assert( _heightMapID != VG_NULL_TEXTURE_ID );

		glBindTexture( GL_TEXTURE_2D , _heightMapID );

		glGetTexLevelParameteriv( GL_TEXTURE_2D , 0 , GL_TEXTURE_WIDTH , &_heightMapBufWidth );
		glGetTexLevelParameteriv( GL_TEXTURE_2D , 0 , GL_TEXTURE_HEIGHT , &_heightMapBufHeight );

		assert( _heightMapBufWidth == _heightMapBufHeight );
		assert( _heightMapBufWidth % 2 == 1 );

		_heightMapBuffer = new float[ _heightMapBufHeight * _heightMapBufWidth ]; 

		memset( _heightMapBuffer , 0 , 
			_heightMapBufHeight * _heightMapBufWidth * sizeof( float ) );

		glGetTexImage( GL_TEXTURE_2D , 0 , GL_LUMINANCE , GL_FLOAT , 
			_heightMapBuffer );

		VGK_CHECK_OPENGL_ERROR();

		return _heightMapBuffer;
	}
	//----------------------------------------------------------------
	bool Elevation::dumpBufferToHeightMap()
	{
		if ( isEmptyHeightMap() )
		{
			return false;
		}

		if ( _heightMapBuffer == NULL )
		{
			return false;
		}

		setHeightMapID( _heightMapBuffer , 
			_heightMapBufWidth * _heightMapBufHeight * sizeof( float ) );

		return true;
	}
	//----------------------------------------------------------------
	vgAsyn::IoRequest* Elevation::getIoRequest()
	{
		// 目前只测试最清晰一级的
		assert( _lod ==  VGLOD_CLEAR );

		using namespace vgAsyn;

		IoRequest* ret = new IoRequest( getFileInfoClone() );

		ret->setAsynchronousMode( false );

		return ret;
	}
	//----------------------------------------------------------------

	
}// end of namespace vgTerritory

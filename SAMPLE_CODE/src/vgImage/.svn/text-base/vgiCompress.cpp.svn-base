



#include <vgStableHeaders.h>
#include <vgImage/vgiCompress.h>


namespace vgImage {
	
	
	
	
	//----------------------------------------------------------------
	long Compress::processToBuffer( void* src , const long& width , 
		const long& height , void* dst , const GLenum& dds_format )
	{
		using namespace nvtt;

		Format method = getNvFormat( dds_format );

		long store_size = ImageUtility::getDdsImageStorageRequirements(
			width , height , dds_format , false );

		NvOutputHandler outhandler( (byte*)dst , store_size );

		//------------------------------------------
		// 开始nvtt
		//------------------------------------------
		InputOptions inputOptions;
		inputOptions.setTextureLayout( TextureType_2D, width, height );
		inputOptions.setMipmapData( src, width, height );
		inputOptions.setMipmapGeneration( false );

		OutputOptions outputOptions;
		//outputOptions.setFileName( "d:\\output.dds" );
		outputOptions.setOutputHandler( &outhandler );
		outputOptions.setOutputHeader( false );

		CompressionOptions compressionOptions;
		compressionOptions.setFormat( method );
		compressionOptions.setQuality( Quality_Fastest  );

		Compressor compressor;

		bool processok = compressor.process(inputOptions, compressionOptions,
			outputOptions);

		assert( processok == true );
		if ( processok == false )
		{
			return 0;
		}

		//------------------------------------------
		// 检查
		//------------------------------------------
		bool checkok = outhandler.checkValidWhenDone();
		assert( checkok == true );

		return store_size;
	}
	//----------------------------------------------------------------
	long Compress::processWholeFileToBuffer( void* src , const long& width , 
		const long& height , void* dst , const GLenum& dds_format )
	{
		using namespace nvtt;

		Format method = getNvFormat( dds_format );

		long store_size = ImageUtility::getDdsFileStorage(
			width , height , dds_format );

		NvOutputHandler outhandler( (byte*)dst , store_size );

		//------------------------------------------
		// 开始nvtt
		//------------------------------------------
		InputOptions inputOptions;
		inputOptions.setTextureLayout( TextureType_2D, width, height );
		inputOptions.setMipmapData( src, width, height );
		inputOptions.setMipmapGeneration( true );
		//inputOptions.setWrapMode( WrapMode_Mirror );

		OutputOptions outputOptions;
		outputOptions.setOutputHandler( &outhandler );
		outputOptions.setOutputHeader( true );

		CompressionOptions compressionOptions;
		compressionOptions.setFormat( method );
		compressionOptions.setQuality( Quality_Fastest  );

		Compressor compressor;

		bool processok = compressor.process(inputOptions, compressionOptions,
			outputOptions);

		assert( processok == true );
		if ( processok == false )
		{
			return 0;
		}

		//------------------------------------------
		// 检查
		//------------------------------------------
		bool checkok = outhandler.checkValidWhenDone();
		assert( checkok == true );

		return store_size;
	}
	//----------------------------------------------------------------
	nvtt::Format Compress::getNvFormat( const GLenum& dds_format )
	{
		using namespace nvtt;
		Format method;
		switch( dds_format )
		{
		case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
			{	
				method = Format_DXT1; // DXT1
				break;
			}
		case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
			{	
				method = Format_DXT3; // DXT3
				break;
			}
		case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
			{	
				method = Format_DXT5; // DXT5
				break;
			}
		default:
			{
				assert(0);
				return Format_DXT1;
			}
		}
		return method;
	}
	//----------------------------------------------------------------
	long Compress::processWholeFileToStream( void* src , const long& width ,
		const long& height , StreamWriterPtr output, const GLenum& dds_format )
	{
		assert( output.isNull() == false );

		long store_size = ImageUtility::getDdsFileStorage(
			width , height , dds_format );

		byte* buf = new byte[ store_size ];
		memset( buf , 0 , store_size );

		long retnum = processWholeFileToBuffer( src , width , height , buf ,dds_format );
		assert( retnum == store_size);

		long writenum = output->write( buf,  store_size );

		assert( writenum == store_size );
		delete[] buf;

		return store_size;
	}
	//----------------------------------------------------------------
	long Compress::processWholeFileToFile( void* src , const long& width , 
		const long& height , const String& outputfile , const GLenum& dds_format )
	{
		StreamWriterPtr pwriter = StreamWriterFactory::createFromFile( outputfile );
		assert( pwriter.isNull() == false );
		if ( pwriter.isNull() == true )
		{
			return 0;
		}

		return processWholeFileToStream( src , width , height , pwriter , dds_format );
	}
	//----------------------------------------------------------------


	//----------------------------------------------------------------
	void NvOutputHandler::beginImage( int size, int width, int height, 
		int depth, int face, int miplevel )
	{
		return;
	}
	//----------------------------------------------------------------
	bool NvOutputHandler::writeData( const void * data, int size )
	{
		assert( ( _bufferSize - (_curPointer - _buffer) ) >= size );
		memcpy( _curPointer , data , size );

		_curPointer += size;

		return true;
	}
	//----------------------------------------------------------------
	NvOutputHandler::NvOutputHandler( long buffersize )
	{
		setDefault();

		assert( buffersize > 0 );

		// 申请内存
		_bufferSize = buffersize;
		_buffer = new byte[ _bufferSize ];
		memset( _buffer , 0 , _bufferSize );

		_curPointer = _buffer;

	}
	//----------------------------------------------------------------
	NvOutputHandler::NvOutputHandler( byte* buffer, long buffersize )
	{
		setDefault();

		assert( buffersize > 0 );

		// 申请内存
		_bufferSize = buffersize;
		_buffer = buffer;

		_curPointer = _buffer;

		_deleteBufFlag = false;
	}
	//----------------------------------------------------------------
	NvOutputHandler::~NvOutputHandler()
	{
		if ( _deleteBufFlag == true )
		{
			if ( _buffer != NULL )
			{
				delete _buffer;
				_buffer = NULL;
			}
		}

		setDefault();
	}
	//----------------------------------------------------------------
	void NvOutputHandler::setDefault()
	{
		_buffer = NULL;

		_bufferSize = 0;
		_curPointer = NULL;

		_deleteBufFlag = true;
	}
	//----------------------------------------------------------------


}// end of namespace vgImage

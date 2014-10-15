


#include <vgStableHeaders.h>
#include <vgTerritory/vgVgtrFile.h>


namespace vgTerritory {
	
	
	

	
	//----------------------------------------------------------------
	VgtrFile::VgtrFile()
	{
		for ( int i = 0 ; i < VGLOD_N ; ++ i )
		{
			_dataLod[i] = NULL;
		}
	}
	//----------------------------------------------------------------
	VgtrFile::~VgtrFile()
	{
		for ( int i = 0 ; i < VGLOD_N ; ++ i )
		{
			if ( _dataLod [i] != NULL )
			{
				delete[] _dataLod[i];
				_dataLod[i] = NULL;
			}
		}
	}
	//----------------------------------------------------------------
	long VgtrFile::writeToStream( const vgKernel::StreamWriterPtr pwriter )
	{
		if ( _headerPtr.isNull() == true || 
			_dataLod[0] == NULL || 
			_dataLod[1] == NULL || 
			_dataLod[2] == NULL || pwriter.isNull() == true )
		{
			MessageBox(NULL,"Vgtr为空!" , "写入Vgtr错误",MB_OK);
			return 0;
		}

		assert( _dataLod[0] != NULL );
		assert( _dataLod[1] != NULL );
		assert( _dataLod[2] != NULL );

		long filebeg = pwriter->tell();
		
		pwriter->write( _headerPtr.getPointer() , sizeof( VgtrHeader ) );

		assert( _headerPtr->dataLen[0] != 0 );

		//------------------------------------------
		// 写入数据
		//------------------------------------------
		for ( int i = 0 ; i < VGLOD_N ; ++ i )
		{
			long curpos = pwriter->tell();
			_headerPtr->dataPosition[i] = curpos;

			pwriter->write( _dataLod[i] , _headerPtr->dataLen[i] );
		}
	
		long fileend = pwriter->tell();

		//------------------------------------------
		// 重新写入header
		//------------------------------------------
		pwriter->seek( filebeg );
		pwriter->write( _headerPtr.getPointer() , sizeof( VgtrHeader ) );

		pwriter->seek( fileend );

		return fileend - filebeg ;
	}
	//----------------------------------------------------------------
	bool VgtrFile::readFromStream( const vgKernel::StreamReaderPtr preader )
	{
		if ( preader.isNull() == true )
		{
			return false;
		}

		assert( _headerPtr.isNull() == true );
		assert( _dataLod[0] == NULL );
		assert( _dataLod[1] == NULL );
		assert( _dataLod[2] == NULL );
		assert( preader.isNull() == false );

		_headerPtr.bind( new VgtrHeader );

		preader->read( _headerPtr.getPointer() , sizeof( VgtrHeader ) );

		for ( int i = 0 ; i < VGLOD_N ; ++ i )
		{
			preader->seek( _headerPtr->dataPosition[i] );

			assert( _headerPtr->dataLen[i] % 4 == 0 );
			assert( _headerPtr->dataLen[i]  != 0 );

			assert( _dataLod[i] == NULL );

			_dataLod[i] = new float[ _headerPtr->dataLen[i] / 4 ];

			preader->read( _dataLod[i] , _headerPtr->dataLen[i] );
		}



		return true;
	}
	//----------------------------------------------------------------
	String VgtrFile::getDetails()
	{
		assert(0);


		assert( _headerPtr.isNull() == false );

		std::ostringstream o;
		o << "VgtrFile Details: " << _headerPtr->getDetails();

		//------------------------------------------
		// 打印data信息
		//------------------------------------------

		//o << "\n\t\t Data details:";

		//for ( int i = 0 ; i < _headerPtr->xNum * _headerPtr->zNum ; ++ i )
		//{
		//	if ( (i % _headerPtr->xNum) == 0 )
		//	{
		//		o << '\n';
		//	}

		//	o << _data[i] << ' ';
		//}

		return o.str();
	}
	//----------------------------------------------------------------
#if 0 
	void VgtrFile::render()
	{
		assert( _headerPtr.isNull() == false );
		assert( _data != NULL );

		float currentX;
		float currentZ;

		glDisable(GL_TEXTURE_2D);

		glPushMatrix();
		glTranslatef(1,-400,1);
		//glRotatef( 90 , 0,1,0);
		glScalef(0.5,1,0.5);

		glBegin( GL_POINTS );
		//for ( int i = 0 ; i < _header->xNum * _header->zNum ; ++ i )
		//{
		//	currentX = i % _header->xNum;

		//	currentZ = i / _header->xNum;

		//	float& currentY = _data[i];

		//	glVertex3f( currentX , currentY , currentZ );
		//}
		for ( int i = 0 ; i < 1024 * 1024 ; ++ i )
		{
			currentX = i %   _headerPtr->xNum ;

			currentZ = i /  _headerPtr->xNum ;

			float& currentY = _data[i];

			//if ( currentY == 0.0f )
			//{
			//	continue;
			//}

			glVertex3f( currentX , currentY , currentZ );
		}
		glEnd();
		glPopMatrix();

		glEnable(GL_TEXTURE_2D);

	}
#endif
	//----------------------------------------------------------------



	//----------------------------------------------------------------
	VgtrHeader::VgtrHeader()
	{
		fourCC[0] = 'v';
		fourCC[1] = 'g';
		fourCC[2] = 't';
		fourCC[3] = 'r';

		version		= 1;		// 1

		xNum		= 0;			// x和z方向数量
		zNum		= 0;

		originX		= 0;		// 逻辑原点
		originY		= 0;
		originZ		= 0;

		displaceScaleY		= 1.0f;
		displaceChunkScale = 1.0f;
		displaceChunkBiasX = 0.0f;
		displaceChunkBiasZ = 0.0f;

		cellsize		= 0;		// 间距

		// 数据区起始和大小
		for ( int i = 0 ; i < VGLOD_N ; ++ i )
		{
			dataPosition[ i ] = 0 ;
			dataLen[ i ] = 0;
		}

		N = 0;

		cellTexSize		= 0;

		memset( name , 0 , VG_VGTR_NAME_LENGTH );
		memset( texname , 0 , VG_VGTR_NAME_LENGTH );
	}
	//----------------------------------------------------------------
	String VgtrHeader::getDetails()
	{
		std::ostringstream o;
		o << "-- VgtrHeader Details: ( "
			<< " fourCC : " << fourCC[0]<<fourCC[1]<<fourCC[2]<<fourCC[3]
			<< " , version : " << version
			<< " , zNum : " << zNum
			<< " , xNum : " << xNum
			<< " , originX : " << originX
			<< " , originY : " << originY
			<< " , originZ : " << originZ
			<< " , displaceScaleY : " << displaceScaleY
			<< " , cellTexSize : " << cellTexSize
			<< " )";

		return o.str();
	}
	//----------------------------------------------------------------



}// end of namespace vgTerritory

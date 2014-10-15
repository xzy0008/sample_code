


#include <vgStableHeaders.h>
#include <vgModel/vgmoFileReaderMod.h>


// MOD属性
#define 	MTL_STANDARD	(1<<0)
//#define 	MTL_SHELL		(MTL_STANDARD<<1)


#define 	OBJ_BAKED		(MTL_STANDARD<<2)
#define 	OBJ_KEYFRAME	(MTL_STANDARD<<3)


namespace vgModel {
	
	
	
	
	//----------------------------------------------------------------
	ModObjPtrVector* FileReaderMod::readFromStream(
		const vgKernel::StreamReaderPtr pstream )
	{

		if ( pstream.isNull() == true )
		{
			return NULL;
		}

		//-----------------------------------------
		// 文件头读取
		//-----------------------------------------
		ModHeader _modheader;

		pstream->read( _modheader._headerFourCC , 32 );
		pstream->read( (char*)&_modheader._version , sizeof( unsigned int ) );

		if( _modheader._version >= VERSION_MOD(2008,5) )
		{
			float tmp;
			// 跳过
			pstream->read( &tmp, sizeof( float ) );
			pstream->read( &tmp, sizeof( float ) );
			pstream->read( &tmp, sizeof( float ) );
		}

		pstream->read( (char*)&_modheader._numberOfObjects , sizeof( int ) );

		assert( String( _modheader._headerFourCC) == "VRGIS" );

		ModIndex _modindex( _modheader._numberOfObjects );


		pstream->read( _modindex._objectsPos , 
			sizeof( long ) *_modindex._numberOfObjects );

		//------------------------------------------
		// 更改09-3-6
		//------------------------------------------
		{

			if( _modheader._version > VERSION_MOD(2008,5) )
			{
				int objnum = _modindex._numberOfObjects;

				bool* boolarray = _modindex._bakedFlag;
				bool* keyframearray = _modindex._keyframeFlag;

				memset( boolarray , 0 , _modindex._numberOfObjects);

				uint* uintarray = new uint[ _modindex._numberOfObjects ];
				memset( uintarray , 0 , sizeof( int) *  _modindex._numberOfObjects);

				pstream->read( uintarray, sizeof( int) *  _modindex._numberOfObjects  );


				for ( int i = 0 ; i < objnum; ++ i )
				{
					//uint dfff=0;
					//if ( i == 4 )
					//{
					//	dfff = uintarray[i];

					//}

					if ( uintarray[i] & OBJ_KEYFRAME )
					{
						if ( uintarray[i] & OBJ_BAKED  )
						{
							boolarray[i] = true;
						}
						else
						{
							boolarray[i] = false;
						}

						keyframearray[i] = true;
						//MessageBox( NULL , "含有Keyframe物体, 程序错误,退出" , "Error" , MB_OK );
						//delete uintarray;
						//return NULL;
					}
					else if ( uintarray[i] & OBJ_BAKED  )
					{
						boolarray[i] = true;
						keyframearray[i] = false;
					}
					else
					{
						boolarray[i] = false;
						keyframearray[i] = false;
					}
				}

			}
			else
			{
				//MessageBox( NULL , "mod版本过旧,退出" , "Error" , MB_OK );
				//return NULL;

				pstream->read( _modindex._bakedFlag , 
					sizeof(bool) * _modindex._numberOfObjects );
			}



			//pstream->read( _modindex._bakedFlag , 
			//	sizeof(bool) * _modindex._numberOfObjects );
		}




		//for ( int i = 0; i < _modindex._numberOfObjects ; ++ i )
		//{
		//	assert( _modindex._bakedFlag[i] == false );
		//}

		unsigned int	uiKeyFramesHeadPos = 0;
		if ( _modheader._version >= VERSION_MOD(2008,6))
		{
			pstream->read( &uiKeyFramesHeadPos , sizeof(long));
		}

		ModObjPtrVector* ret = new ModObjPtrVector;
		//-----------------------------------------
		// 以上读入文件头，以下读入obj数据
		//-----------------------------------------
		for (int i = 0; i < _modheader._numberOfObjects ; i++)
		{
			long objchunklength;

			long pos = 0;

			char *objdata = NULL;

			//assert( _modindex._bakedFlag[i] == false );

			pstream->seek( _modindex._objectsPos[i] );
			pstream->read( &objchunklength , sizeof(long) );

			assert( objdata == NULL );
			objdata = new char[objchunklength];
			size_t readsize = pstream->read( objdata , sizeof(char) * objchunklength );

			assert( readsize == objchunklength );

			ModObjectPtr modobj( new ModObject );

			bool readret = modobj->readFromMemory( 
				objdata , objchunklength , _modheader._version ,
				_modindex._bakedFlag[i] ,
				_modindex._keyframeFlag[i] );
			//assert( readret == true );

			if (readret == true)
			{
				ret->push_back( modobj );
			}

			delete objdata;
		}

		return ret;
	}


}// end of namespace vgModel

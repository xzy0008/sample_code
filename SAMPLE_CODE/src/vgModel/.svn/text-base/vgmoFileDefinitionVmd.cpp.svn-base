


#include <vgStableHeaders.h>
#include <vgModel/vgmoFileDefinitionVmd.h>
#include <vgModel/vgmoFileModObject.h>
#include <vgKernel/vgkStringUtility.h>

namespace vgModel { 
	
	//----------------------------------------------------------------
	VmdDataStruct::VmdDataStruct()
	{
		setDefault();
	}
	//----------------------------------------------------------------
	VmdDataStruct::~VmdDataStruct()
	{
		destroy();
	}
	//----------------------------------------------------------------
	void VmdDataStruct::destroy()
	{
		if ( _vertexElements != NULL )
		{
			delete[] _vertexElements;
			_vertexElements = NULL;
		}

		if ( _metaFaces != NULL )
		{
			delete[] _metaFaces;
			_metaFaces = NULL;
		}

		if ( _keyframeInfo != NULL )
		{
			delete _keyframeInfo;
			_keyframeInfo =NULL;
		}

		setDefault();
	}
	//----------------------------------------------------------------
	void VmdDataStruct::setDefault()
	{

		_keyframeInfo =NULL;
		_numberOfVertexElements = 0;
		_layersOfTexture = 0;
		_vertexElements = NULL;
		_numberOfMetaFaces = 0;
		_metaFaces = NULL;

		_renderType = 0;

		_shadowNumberOfFaces = 0;
		_shadowNormalOfFaces = NULL;
		_shadowNumberOfVertices = 0;
		_shadowVerticesOfFaces = NULL;
		_shadowIndicesOfFaces = NULL;
	}
	//----------------------------------------------------------------
#if 0
	void VmdDataStruct::render()
	{
		assert( _vertexElements !=  NULL );

		glPushMatrix();
		for ( int i = 0 ; i < _numberOfMetaFaces ; ++ i )
		{
			glEnable( GL_TEXTURE_2D );
			glColor3f(1, 1, 1);		

			String texname( _metaFaces[i]._textureFileName[0] );

			vgImage::TextureObserver* tex = 
				vgImage::TextureManager::getSingleton().getTextureObserver(
				texname , VG_LOD_CLEAREST );

			if ( tex != NULL )
			{
				tex->useBind();
			}

			assert( _sizeOfVertexElements == sizeof( VmdVertexElement1 ) );
			glInterleavedArrays( GL_T2F_N3F_V3F, 0 , _vertexElements );

			glDrawElements(GL_TRIANGLES, _metaFaces[i]._numberOfFaceIndex * 3,
				GL_UNSIGNED_INT , _metaFaces[i]._faceIndex );
		}
		glPopMatrix();
	}
#endif
	//----------------------------------------------------------------
	void VmdDataStruct::getInfoFromModObject( ModObject* mod )
	{
		assert( mod != NULL );
		assert( mod->_vertexElements != NULL );
		assert( mod->_isValid == true );

		//------------------------------------------
		// 1.赋值必要的参数
		//------------------------------------------
		_renderType = mod->_renderType;

		//assert(  mod->_numberOfNoMaterial > 0 );
		if ( mod->_numberOfNoMaterial == 0 )
		{
			_numberOfMetaFaces = mod->_numberOfMaterial;
		}
		else
		{
			_numberOfMetaFaces = mod->_numberOfMaterial + 1;
		}

		_numberOfVertexElements = mod->_numberOfVertices;

		//------------------------------------------
		// 多纹理情况
		//------------------------------------------
		if ( mod->_isBaked /*== true*/ )
		{
			_layersOfTexture = 2;
			_sizeOfVertexElements = sizeof( VmdVertexElement2 );
		}
		else
		{
			_layersOfTexture = 1;
			_sizeOfVertexElements = sizeof( VmdVertexElement1 );
		}



		//------------------------------------------
		// 2.开始申请内存并拷贝
		//------------------------------------------
		_metaFaces = new VmdMetaFaceStruct[ _numberOfMetaFaces ];

		// vertex elements
		if ( mod->_isBaked /*== true*/ )
		{
			_vertexElements = 
				new VmdVertexElement2[ _numberOfVertexElements ];
			memcpy( _vertexElements , mod->_vertexElements , 
				mod->_numberOfVertices * sizeof( VmdVertexElement2 ) );
		}
		else
		{
			_vertexElements = 
				new VmdVertexElement1[ _numberOfVertexElements ];
			memcpy( _vertexElements , mod->_vertexElements , 
				mod->_numberOfVertices * sizeof( VmdVertexElement1 ) );
		}

		// material faces
		for ( int i = 0 ; i < mod->_numberOfMaterial ; ++i )
		{
			// texture name
			_metaFaces[i]._sizeOfOneTexName = VMD_TEXTURE_NAME_LENGTH;

			if ( mod->_isBaked /*== true*/ )
			{
				_metaFaces[i]._numberOfTexture = 2;
				_metaFaces[i]._textureFileName = new char*[2];

				_metaFaces[i]._textureFileName[0] = new char[VMD_TEXTURE_NAME_LENGTH];
				_metaFaces[i]._textureFileName[1] = new char[VMD_TEXTURE_NAME_LENGTH];

				memset( _metaFaces[i]._textureFileName[0] , 0 ,VMD_TEXTURE_NAME_LENGTH);
				memset( _metaFaces[i]._textureFileName[1] , 0 ,VMD_TEXTURE_NAME_LENGTH);


				MaterialStruct2* mat =(MaterialStruct2*) mod->_material;

				String texnobake( mat[i].materialinfo.strFile );
				vgKernel::StringUtility::toLowerCase( texnobake );
				assert( texnobake.size() < VMD_TEXTURE_NAME_LENGTH );

				String texbake( mat[i].materialinfo.strFileBaked );
				vgKernel::StringUtility::toLowerCase( texbake );

				assert( texbake.size() < VMD_TEXTURE_NAME_LENGTH );

				if ( String(mat[i].materialinfo.strFile) != "," )
				{
					strcpy( _metaFaces[i]._textureFileName[0] , texnobake.c_str()  );
				}

				if ( String(mat[i].materialinfo.strFileBaked) != "," )
				{
					strcpy( _metaFaces[i]._textureFileName[1] , texbake.c_str()  );
				}
			}
			else
			{
				_metaFaces[i]._numberOfTexture = 1;
				_metaFaces[i]._textureFileName = new char*[1];

				_metaFaces[i]._textureFileName[0] = new char[VMD_TEXTURE_NAME_LENGTH];

				memset( _metaFaces[i]._textureFileName[0] , 0 ,VMD_TEXTURE_NAME_LENGTH);


				MaterialStruct* mat =(MaterialStruct*) mod->_material;

				String texnobake( mat[i].materialinfo.strFile );
				vgKernel::StringUtility::toLowerCase( texnobake );

				if( texnobake.size() >= VMD_TEXTURE_NAME_LENGTH - 1 )
				{
					std::ostringstream o;
					o << "纹理的文件名太长:" << texnobake << ", 此纹理将被忽略掉.";
					MessageBox( NULL , o.str().c_str() , "提示" , MB_OK );

					texnobake.clear();
				}
				
				if ( String(mat[i].materialinfo.strFile) != "," )
				{
					strcpy( _metaFaces[i]._textureFileName[0] , texnobake.c_str()  );
				}
			}
	

			// number of face index
			_metaFaces[i]._sizeOfFaceIndex = sizeof( VmdFaceIndex );
			_metaFaces[i]._numberOfFaceIndex = 
				mod->_materialFaces[i].m_numOfFace;

			// face index
			_metaFaces[i]._faceIndex = 
				new VmdFaceIndex[ _metaFaces[i]._numberOfFaceIndex ];

			memcpy( _metaFaces[i]._faceIndex , 
				mod->_materialFaces[i].pFace , 
				sizeof( FaceIndex ) * _metaFaces[i]._numberOfFaceIndex );

#if 0
			for ( int k = 0 ; k < _metaFaces[i]._numberOfFaceIndex ; ++ k )
			{
				int value = _metaFaces[i]._faceIndex[k]._point0;
				assert( value < _numberOfVertexElements );

				value = _metaFaces[i]._faceIndex[k]._point1;
				assert( value < _numberOfVertexElements );

				value = _metaFaces[i]._faceIndex[k]._point2;
				assert( value < _numberOfVertexElements );

			}
#endif
		}

		// no material face 
		if ( mod->_numberOfNoMaterial != 0 )
		{
			int i = mod->_numberOfMaterial;

			// texture name
			_metaFaces[i]._sizeOfOneTexName = VMD_TEXTURE_NAME_LENGTH;
			_metaFaces[i]._numberOfTexture = 1;
			_metaFaces[i]._textureFileName = new char*[1];

			_metaFaces[i]._textureFileName[0] = new char[VMD_TEXTURE_NAME_LENGTH];

			memset( _metaFaces[i]._textureFileName[0] , 0 ,VMD_TEXTURE_NAME_LENGTH);


			_metaFaces[i]._sizeOfFaceIndex = sizeof( VmdFaceIndex );

			_metaFaces[i]._numberOfFaceIndex = mod->_numberOfNoMaterial;
			_metaFaces[i]._faceIndex = new VmdFaceIndex[ mod->_numberOfNoMaterial ];

			memcpy( _metaFaces[i]._faceIndex , 	mod->_faceIndexOfNoMaterial , 
				sizeof( VmdFaceIndex ) * _metaFaces[i]._numberOfFaceIndex );
		}


		//------------------------------------------
		// // DataPlus
		//------------------------------------------
		//----------------------------------------------------------------
		_shadowNumberOfFaces = mod->_shadowNumberOfFaces;
		assert( mod->_shadowNormalOfFaces != NULL );

		_shadowNormalOfFaces = new vgKernel::Vec3[ _shadowNumberOfFaces ];
		memcpy( _shadowNormalOfFaces , 
			mod->_shadowNormalOfFaces , sizeof( vgKernel::Vec3 ) * _shadowNumberOfFaces );

		//----------------------------------------------------------------
		_shadowNumberOfVertices = mod->_shadowNumberOfVertices;
		assert( mod->_shadowVerticesOfFaces != NULL );

		_shadowVerticesOfFaces = 
			new vgKernel::Vec3[ _shadowNumberOfVertices ];
		memcpy( _shadowVerticesOfFaces , 
			mod->_shadowVerticesOfFaces , sizeof( vgKernel::Vec3 ) * _shadowNumberOfVertices );

		//----------------------------------------------------------------
		_shadowIndicesOfFaces = 
			new ShadowFaceIndex[ _shadowNumberOfFaces ];
		memcpy( _shadowIndicesOfFaces , 
			mod->_shadowIndicesOfFaces , sizeof( ShadowFaceIndex ) * _shadowNumberOfFaces );


		if ( mod->_keyframeInfo != NULL )
		{
			_keyframeInfo = mod->_keyframeInfo->createVmdKeyFrameInfo();
		}
	}
	//----------------------------------------------------------------
	long VmdDataStruct::writeToStream( const vgKernel::StreamWriterPtr pwriter )
	{
		assert( pwriter.isNull() == false );
		assert( _metaFaces != NULL );


		long beginpos = pwriter->tell();


		pwriter->write( (char*)&_renderType , sizeof( _renderType ) );
		
		pwriter->write( (char*)&_layersOfTexture , sizeof( _layersOfTexture ) );

		pwriter->write( (char*)&_numberOfVertexElements , sizeof( _numberOfVertexElements ) );
		
		pwriter->write( (char*)&_sizeOfVertexElements , sizeof( _sizeOfVertexElements ) );

		pwriter->write( (char*)_vertexElements , _sizeOfVertexElements * _numberOfVertexElements );

		pwriter->write( (char*)&_numberOfMetaFaces , sizeof( _numberOfMetaFaces ) );

		for ( int i = 0 ; i < _numberOfMetaFaces ; ++i )
		{
			_metaFaces[i].writeToStream( pwriter );
		}

		//------------------------------------------
		// dataplus
		//------------------------------------------
		pwriter->write( &_shadowNumberOfFaces , sizeof( int ) );
		pwriter->write( _shadowNormalOfFaces , sizeof( Vec3 ) * _shadowNumberOfFaces );
		pwriter->write( &_shadowNumberOfVertices , sizeof( int ) );
		pwriter->write( _shadowVerticesOfFaces , sizeof( Vec3 ) * _shadowNumberOfVertices );
		pwriter->write( _shadowIndicesOfFaces , sizeof( ShadowFaceIndex ) * _shadowNumberOfFaces );

	
		//------------------------------------------
		// keyframe
		//------------------------------------------
		if ( _keyframeInfo == NULL )
		{
			int count = 0;
			pwriter->write( &count , sizeof( int ) );
		}
		else
		{
			pwriter->write( &_keyframeInfo->_frameCount , sizeof( int ) );
			pwriter->write( &_keyframeInfo->_startFrame , sizeof( int ) );
			pwriter->write( &_keyframeInfo->_endFrame , sizeof( int ) );
			pwriter->write( &_keyframeInfo->_play , sizeof( bool ) );
			pwriter->write( &_keyframeInfo->_loop , sizeof( bool ) );


			pwriter->write( _keyframeInfo->_frames , sizeof(VmdKeyFrame) 
				* _keyframeInfo->_frameCount );

		}
		

		long endpos = pwriter->tell();

		return endpos - beginpos;
	}
	//----------------------------------------------------------------
	long VmdDataStruct::getNumberOfTriangles()
	{
		long ret = 0 ;

		for ( int i = 0 ; i < _numberOfMetaFaces ; ++i )
		{
			ret += _metaFaces[i]._numberOfFaceIndex;
		}

		return ret;
	}
	//----------------------------------------------------------------



	//----------------------------------------------------------------
	void VmdMetaFaceStruct::destroy()
	{
		if ( _textureFileName != NULL )
		{
			for ( int i = 0 ; i < _numberOfTexture ; ++i )
			{
				delete _textureFileName[i];
			}

			delete[] _textureFileName;
		}

		if( _faceIndex != NULL )
		{
			delete[] _faceIndex;
		}

		setDefault();
	}
	//----------------------------------------------------------------
	void VmdMetaFaceStruct::setDefault()
	{
		memset( _colorRGBA , 0 , 4 );
		_textureFileName = NULL;
		_numberOfFaceIndex = 0;
		_faceIndex = NULL;
		_numberOfTexture = 0;
		_sizeOfFaceIndex = 0;
		_sizeOfOneTexName = 0;
	}
	//----------------------------------------------------------------
	VmdMetaFaceStruct::~VmdMetaFaceStruct()
	{
		//destroy();
	}
	//----------------------------------------------------------------
	VmdMetaFaceStruct::VmdMetaFaceStruct()
	{
		setDefault();
	}
	//----------------------------------------------------------------
	long VmdMetaFaceStruct::writeToStream( const vgKernel::StreamWriterPtr pwriter )
	{
		long beginpos = pwriter->tell();

		pwriter->write( (char*)_colorRGBA , sizeof( _colorRGBA ) );

		pwriter->write( (char*)&_numberOfTexture , sizeof( _numberOfTexture ) );

		assert( _sizeOfOneTexName == VMD_TEXTURE_NAME_LENGTH );
		pwriter->write( (char*)&_sizeOfOneTexName , sizeof( _sizeOfOneTexName ) );

		for ( int i = 0 ; i < _numberOfTexture ; ++i )
		{
			pwriter->write( (char*)_textureFileName[i] , VMD_TEXTURE_NAME_LENGTH );
		}

		pwriter->write( (char*)&_numberOfFaceIndex , sizeof( _numberOfFaceIndex ) );
		pwriter->write( (char*)&_sizeOfFaceIndex , sizeof( _sizeOfFaceIndex ) );

		assert( _faceIndex != NULL );
		pwriter->write( (char*)_faceIndex , _numberOfFaceIndex * _sizeOfFaceIndex );

		long endpos = pwriter->tell();

		return endpos - beginpos;
	}
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//----------------------------------------------------------------
	void VmdHeader::setDefault()
	{
		_fourCC[0] = 'V';
		_fourCC[1] = 'G';
		_fourCC[2] = 'M';
		_fourCC[3] = 0;

		_version = 1;
		_sizeOfWholeFile = 0;

		_sizeOfHeader = sizeof( VmdHeader );

		_numberOfBriefs		= 0;
		_lengthOfOneBrief		= sizeof( VmdBrief );
		_positionOfBriefs		= 0;
		_reserved1		= 0;
		_reserved2		= 0;
		_reserved3		= 0;
		_reserved4		= 0;
	}
	//----------------------------------------------------------------
	//----------------------------------------------------------------
	void VmdBrief::setDefault()
	{
		_positionOfFile = 0;
		_lengthOfFile = 0;

		memset( _className , 0 , VMD_MODEL_NAME_LENGTH );
		memset( _modelName , 0 , VMD_MODEL_NAME_LENGTH );


		_isVisible = true;
		//------------------------------------------
		// ！！！！！！！
		// 注意这里为false
		//------------------------------------------
		

		_multMatrix = vgKernel::Mat4::IDENTITY;

		_numberOfFaces = 0;

		_positionOfModelData = 0;
		_lengthOfModelData = 0;

		for ( int i = 0 ; i < 16 ; ++ i )
		{
			_reservedData[i] = 0;
		}

		_squaredDistanceOfLodNear = VGLOD_SQU_DIST_NEAR;
		_squaredDistanceOfLodFar = VGLOD_SQU_DIST_FAR;

		_reserved0 = 0;
		_reserved1 = 0;
		_reserved2 = 0;

		_colorQuad.red = 0;
		_colorQuad.blue = 0;
		_colorQuad.green = 0;
		_colorQuad.alpha = 0;
		_reserved3 = 0;
		_reserved4 = 0;
		_reserved5 = 0;
		_reserved6 = 0;

		memset( _reserved7 , 0 , 256 * sizeof( long ) );
	}
	//----------------------------------------------------------------
	void VmdBrief::getInfoFromModObject( ModObject* mod )
	{
		assert( mod != NULL );

		memcpy( _modelName , mod->_name , 20 );

		_dynamicBoundingBox = mod->_mergedBox;
		_staticBoundingBox = _dynamicBoundingBox;
		_numberOfFaces = mod->_numberOfFaces;

	}
	//----------------------------------------------------------------
	VmdBrief::VmdBrief() 
		:_uniqueId( UniqueIDFactory::getUniqueID() )
	{
		setDefault();
	}

	bool VmdBrief::setClassName( const String& classname )
	{
		if ( classname.size() >= VMD_MODEL_NAME_LENGTH )
		{
			return false;
		}

		strcpy( _className , classname.c_str() );
		return true;
	}
	//----------------------------------------------------------------
}// end of namespace vgModel

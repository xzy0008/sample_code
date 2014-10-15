


#include <vgStableHeaders.h>
#include <vgMesh/vgmFileDefinitionVgm.h>
#include <vgImage/vgiTextureManager.h>
#include <vgMesh/vgmFileModObject.h>
#include <vgKernel/vgkStringUtility.h>
#include <vgKernel/vgkSystemUtility.h>

namespace vgMesh { 
	
	//----------------------------------------------------------------
	VgmDataStruct::VgmDataStruct()
	{
		setDefault();
	}
	//----------------------------------------------------------------
	VgmDataStruct::~VgmDataStruct()
	{
		destroy();
	}
	//----------------------------------------------------------------
	void VgmDataStruct::destroy()
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

		setDefault();
	}
	//----------------------------------------------------------------
	void VgmDataStruct::setDefault()
	{
		_dataType = VGM_DATATYPE_OBJECT;
		_numberOfVertexElements = 0;
		_layersOfTexture = 0;
		_vertexElements = NULL;
		_numberOfMetaFaces = 0;
		_metaFaces = NULL;

		_renderType = 0;
	}
	//----------------------------------------------------------------
#if 0
	void VgmDataStruct::render()
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

			assert( _sizeOfVertexElements == sizeof( VgmVertexElement1 ) );
			glInterleavedArrays( GL_T2F_N3F_V3F, 0 , _vertexElements );

			glDrawElements(GL_TRIANGLES, _metaFaces[i]._numberOfFaceIndex * 3,
				GL_UNSIGNED_INT , _metaFaces[i]._faceIndex );
		}
		glPopMatrix();
	}
#endif
	//----------------------------------------------------------------
	void VgmDataStruct::getInfoFromModObject( ModObject* mod )
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
			_sizeOfVertexElements = sizeof( VgmVertexElement2 );
		}
		else
		{
			_layersOfTexture = 1;
			_sizeOfVertexElements = sizeof( VgmVertexElement1 );
		}



		//------------------------------------------
		// 2.开始申请内存并拷贝
		//------------------------------------------
		_metaFaces = new VgmMetaFaceStruct[ _numberOfMetaFaces ];

		// vertex elements
		if ( mod->_isBaked /*== true*/ )
		{
			_vertexElements = 
				new VgmVertexElement2[ _numberOfVertexElements ];
			memcpy( _vertexElements , mod->_vertexElements , 
				mod->_numberOfVertices * sizeof( VgmVertexElement2 ) );
		}
		else
		{
			_vertexElements = 
				new VgmVertexElement1[ _numberOfVertexElements ];
			memcpy( _vertexElements , mod->_vertexElements , 
				mod->_numberOfVertices * sizeof( VgmVertexElement1 ) );
		}

		// material faces
		for ( int i = 0 ; i < mod->_numberOfMaterial ; ++i )
		{
			// texture name
			_metaFaces[i]._sizeOfOneTexName = VGM_TEXTURE_NAME_LENGTH;

			if ( mod->_isBaked /*== true*/ )
			{
				_metaFaces[i]._numberOfTexture = 2;
				_metaFaces[i]._textureFileName = new char*[2];

				_metaFaces[i]._textureFileName[0] = new char[VGM_TEXTURE_NAME_LENGTH];
				_metaFaces[i]._textureFileName[1] = new char[VGM_TEXTURE_NAME_LENGTH];

				memset( _metaFaces[i]._textureFileName[0] , 0 ,VGM_TEXTURE_NAME_LENGTH);
				memset( _metaFaces[i]._textureFileName[1] , 0 ,VGM_TEXTURE_NAME_LENGTH);


				MaterialStruct2* mat =(MaterialStruct2*) mod->_material;

				String texnobake( mat[i].materialinfo.strFile );
				vgKernel::StringUtility::toLowerCase( texnobake );
				assert( texnobake.size() < VGM_TEXTURE_NAME_LENGTH );

				String texbake( mat[i].materialinfo.strFileBaked );
				vgKernel::StringUtility::toLowerCase( texbake );

				assert( texbake.size() < VGM_TEXTURE_NAME_LENGTH );

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

				_metaFaces[i]._textureFileName[0] = new char[VGM_TEXTURE_NAME_LENGTH];

				memset( _metaFaces[i]._textureFileName[0] , 0 ,VGM_TEXTURE_NAME_LENGTH);


				MaterialStruct* mat =(MaterialStruct*) mod->_material;

				String texnobake( mat[i].materialinfo.strFile );
				vgKernel::StringUtility::toLowerCase( texnobake );

				if( texnobake.size() >= VGM_TEXTURE_NAME_LENGTH - 1 )
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
			_metaFaces[i]._sizeOfFaceIndex = sizeof( VgmFaceIndex );
			_metaFaces[i]._numberOfFaceIndex = 
				mod->_materialFaces[i].m_numOfFace;

			// face index
			_metaFaces[i]._faceIndex = 
				new VgmFaceIndex[ _metaFaces[i]._numberOfFaceIndex ];

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
			_metaFaces[i]._sizeOfOneTexName = VGM_TEXTURE_NAME_LENGTH;
			_metaFaces[i]._numberOfTexture = 1;
			_metaFaces[i]._textureFileName = new char*[1];

			_metaFaces[i]._textureFileName[0] = new char[VGM_TEXTURE_NAME_LENGTH];

			memset( _metaFaces[i]._textureFileName[0] , 0 ,VGM_TEXTURE_NAME_LENGTH);


			_metaFaces[i]._sizeOfFaceIndex = sizeof( VgmFaceIndex );

			_metaFaces[i]._numberOfFaceIndex = mod->_numberOfNoMaterial;
			_metaFaces[i]._faceIndex = new VgmFaceIndex[ mod->_numberOfNoMaterial ];

			memcpy( _metaFaces[i]._faceIndex , 	mod->_faceIndexOfNoMaterial , 
				sizeof( VgmFaceIndex ) * _metaFaces[i]._numberOfFaceIndex );
		}
	}
	//----------------------------------------------------------------
	long VgmDataStruct::writeToStream( const vgKernel::StreamWriterPtr pwriter )
	{
		assert( pwriter.isNull() == false );
		assert( _metaFaces != NULL );


		long beginpos = pwriter->tell();

		pwriter->write( (char*)&_dataType , sizeof( _dataType ) );

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

		long endpos = pwriter->tell();

		return endpos - beginpos;
	}
	//----------------------------------------------------------------
	long VgmDataStruct::getNumberOfTriangles()
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
	void VgmMetaFaceStruct::destroy()
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
	void VgmMetaFaceStruct::setDefault()
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
	VgmMetaFaceStruct::~VgmMetaFaceStruct()
	{
		//destroy();
	}
	//----------------------------------------------------------------
	VgmMetaFaceStruct::VgmMetaFaceStruct()
	{
		setDefault();
	}
	//----------------------------------------------------------------
	long VgmMetaFaceStruct::writeToStream( const vgKernel::StreamWriterPtr pwriter )
	{
		long beginpos = pwriter->tell();

		pwriter->write( (char*)_colorRGBA , sizeof( _colorRGBA ) );

		pwriter->write( (char*)&_numberOfTexture , sizeof( _numberOfTexture ) );

		assert( _sizeOfOneTexName == VGM_TEXTURE_NAME_LENGTH );
		pwriter->write( (char*)&_sizeOfOneTexName , sizeof( _sizeOfOneTexName ) );

		for ( int i = 0 ; i < _numberOfTexture ; ++i )
		{
			pwriter->write( (char*)_textureFileName[i] , VGM_TEXTURE_NAME_LENGTH );
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
	void VgmHeader::setDefault()
	{
		_fourCC[0] = 'V';
		_fourCC[1] = 'G';
		_fourCC[2] = 'M';
		_fourCC[3] = 0;

		_version = 1;
		_sizeOfWholeFile = 0;

		_sizeOfHeader = sizeof( VgmHeader );

		_numberOfBriefs		= 0;
		_lengthOfOneBrief		= sizeof( VgmBrief );
		_positionOfBriefs		= 0;
		_reserved1		= 0;
		_reserved2		= 0;
		_reserved3		= 0;
		_reserved4		= 0;
	}
	//----------------------------------------------------------------
	//----------------------------------------------------------------
	void VgmBrief::setDefault()
	{
		_type = VGM_BRIEFTYPE_MESH;

		_positionOfFile = 0;
		_lengthOfFile = 0;

		memset( _meshName , 0 , VGM_MESH_NAME_LENGTH );

		_meshDataType = VGM_DATATYPE_OBJECT;
		_meshDataPlusType = VGM_DATAPLUSTYPE_SHADOW;

		_isVisible = true;
		_isLodMesh = true;

		_multMatrix = vgKernel::Mat4::IDENTITY;

		_numberOfFaces = 0;

		for ( int i = 0 ; i < VGLOD_N ; ++ i )
		{
			_positionOfMeshData[i] = 0;
			_lengthOfMeshData[i] = 0;

			_positionOfMeshDataPlus[i] = 0;
			_lengthOfMeshPlus[i] = 0;
		}

		_squaredDistanceOfLodNear = VGLOD_SQU_DIST_NEAR;
		_squaredDistanceOfLodFar = VGLOD_SQU_DIST_FAR;

		_reserved0 = 0;
		_reserved1 = 0;

		_colorQuad.red = 0;
		_colorQuad.blue = 0;
		_colorQuad.green = 0;
		_colorQuad.alpha = 0;
		//_reserved3 = 0;
		_reserved4 = 0;
		_reserved5 = 0;
		_reserved6 = 0;
	}
	//----------------------------------------------------------------
	void VgmBrief::getInfoFromModObject( ModObject* mod )
	{
		assert( mod != NULL );

		memcpy( _meshName , mod->_name , 20 );

		_dynamicBoundingBox = mod->_box;
		_staticBoundingBox = _dynamicBoundingBox;
		_numberOfFaces = mod->_numberOfFaces;

	}
	//----------------------------------------------------------------
	VgmBrief::VgmBrief() 
		:_uniqueId( UniqueIDFactory::getUniqueID() )
	{
		setDefault();
	}
	//----------------------------------------------------------------
}// end of namespace vgMesh

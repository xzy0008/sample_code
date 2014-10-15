

#include <vgStableHeaders.h>
#include <vgMesh/vgmFileModObject.h>


namespace vgMesh {
	
	
	
	
	//----------------------------------------------------------------
	bool ModObject::readFromMemory( char* buf, const int& buf_size,
		const uint& fileversion , const bool& isbaked )
	{
		assert( _isValid == false );

		_isBaked = isbaked;

		//------------------------------------------
		// 首先读取box信息
		//------------------------------------------
		const char* const objdata = buf;
		long boxpos = 0;

		if( fileversion < VERSION_4 )
		{
			_box._maxVertex.x = *(float *)(objdata + boxpos);
			boxpos += sizeof(float);

			_box._minVertex.x = *(float *)(objdata + boxpos);
			boxpos += sizeof(float);

			_box._maxVertex.y = *(float *)(objdata + boxpos);
			boxpos += sizeof(float);

			_box._minVertex.y = *(float *)(objdata + boxpos);
			boxpos += sizeof(float);

			_box._maxVertex.z = *(float *)(objdata + boxpos);
			boxpos += sizeof(float);

			_box._minVertex.z = *(float *)(objdata + boxpos);
			boxpos += sizeof(float);

		}
		else
		{
			_box._minVertex.x = *(float *)(objdata + boxpos);
			boxpos += sizeof(float);

			_box._minVertex.y = *(float *)(objdata + boxpos);
			boxpos += sizeof(float);

			_box._minVertex.z = *(float *)(objdata + boxpos);
			boxpos += sizeof(float);


			_box._maxVertex.x = *(float *)(objdata + boxpos);
			boxpos += sizeof(float);

			_box._maxVertex.y = *(float *)(objdata + boxpos);
			boxpos += sizeof(float);

			_box._maxVertex.z = *(float *)(objdata + boxpos);
			boxpos += sizeof(float);
		}


		//------------------------------------------
		// 开始正式读取数据
		//------------------------------------------
		char* data = buf + boxpos;

		int i;
		long pos = 0;

		if( fileversion < VERSION_4 )
		{
			_renderType = *(int *)(data + pos);
			pos += sizeof(int);

			memcpy( _name , ( data + pos ) , sizeof( _name ) );
			pos += sizeof(_name);

			_shadowNumberOfFaces = *(long *) (data + pos);	
			_numberOfFaces = _shadowNumberOfFaces;
			pos += sizeof(long);
		}
		else
		{
			//Vec3			m_oPosition;		// 节点中心位置

			//E_NODE_TYPE		m_eNodeType;		// 节点类型
			//unsigned int	m_uFaceCount;		// 节点面数
			//TCHAR			m_sNodeName[20];	// 节点名字
			//E_RENDER_TYPE	m_eRenderType;		// 节点绘制类型

			// 跳过position
			pos += sizeof(float) * 3;

			// 跳过type
			pos += sizeof(int);

			_shadowNumberOfFaces = *(long *) (data + pos);	
			_numberOfFaces = _shadowNumberOfFaces;
			pos += sizeof(long);

			memcpy( _name , ( data + pos ) , sizeof( _name ) );
			pos += sizeof(_name);

			_renderType = *(int *)(data + pos);
			pos += sizeof(int);
		}


		if ( _shadowNumberOfFaces == 0 )
		{
			return false;
		}
		/////////////////////////材质处理//////////////////////

		_numberOfMaterial = *(int *) (data + pos);

		//if ( _numberOfMaterial == 0 )
		//{
		//	return false;
		//}

		//assert( _numberOfMaterial != 0);

		pos += sizeof(int);

		if ( _numberOfMaterial < 0 )
		{
			assert( _numberOfMaterial > 0 );
			return false;
		}


		if ( _isBaked /*== true*/ )
		{
			_material = new MaterialStruct2 [_numberOfMaterial];
			_sizeOfMaterialStruct = sizeof( MaterialStruct2 );

			MaterialStruct2* curmat = (MaterialStruct2*)_material;

			for (i = 0; i <_numberOfMaterial ; i++)
			{
				memcpy(&curmat[i].materialinfo, data + pos, sizeof(MaterialInfoStruct2) /*-1*/);

				pos += sizeof(MaterialInfoStruct2) /*- 1*/;
			}
		}
		else
		{
			_material = new MaterialStruct [_numberOfMaterial];
			_sizeOfMaterialStruct = sizeof( MaterialStruct );

			MaterialStruct* curmat = (MaterialStruct*)_material;

			for (i = 0; i <_numberOfMaterial ; i++)
			{
				curmat[i].materialinfo =  *(MaterialInfoStruct *)(data + pos);

				//string aa(_material[i].materialinfo.strFile);

				pos += sizeof(MaterialInfoStruct);
			}
		}




		///////////////////////点处理//////////////////////////

		_numberOfVertices = *(int *)(data + pos);
		pos += sizeof(int);
		assert( _numberOfVertices >0 );

		if ( _isBaked /*== true*/ )
		{
			_vertexElements = new VertexElementStruct2[_numberOfVertices];
			memcpy(_vertexElements , data+pos ,
				sizeof(VertexElementStruct2) * _numberOfVertices);
			pos += sizeof(VertexElementStruct2) * _numberOfVertices;

		}
		else
		{
			_vertexElements = new VertexElementStruct[_numberOfVertices];
			memcpy(_vertexElements , data+pos ,
				sizeof(VertexElementStruct) * _numberOfVertices);
			pos += sizeof(VertexElementStruct) * _numberOfVertices;
		}

		//////////////////////有材质的面/////////////////////////

		//assert( _numberOfMaterial != 0 );
		_materialFaces = new MaterialFaces[_numberOfMaterial];

		for (i = 0; i < _numberOfMaterial ; i ++)
		{
			//pos += ReadRenderControl(data+pos , _materialFaces[i] );

			_materialFaces[i].b_hastexture = *(bool *)(data + pos);
			pos += sizeof(bool);

			_materialFaces[i].m_numOfFace = *(int *)(data + pos);
			pos += sizeof(int);

			//assert( _materialFaces[i].m_numOfFace > 0 );
			_materialFaces[i].pFace = new FaceIndex[_materialFaces[i].m_numOfFace];

			memcpy(_materialFaces[i].pFace , data + pos , 
				sizeof(FaceIndex) * _materialFaces[i].m_numOfFace);
			pos += sizeof(FaceIndex) * _materialFaces[i].m_numOfFace;
		}

		_numberOfNoMaterial = *(int *)(data + pos);

		pos += sizeof(int);


		if ( _numberOfNoMaterial != 0 )
		{
			assert( _numberOfNoMaterial > 0 );
			_faceIndexOfNoMaterial = new FaceIndex[_numberOfNoMaterial];

			memcpy(_faceIndexOfNoMaterial , data+pos , sizeof(FaceIndex) * _numberOfNoMaterial);

			pos += sizeof(FaceIndex) * _numberOfNoMaterial;
		}


		//------------------------------------------
		// for shadow
		//------------------------------------------
		// 三角面法线
		//assert( _shadowNumberOfFaces > 0 );
		_shadowNormalOfFaces = new Vec3[_shadowNumberOfFaces];	
		memcpy(_shadowNormalOfFaces , data+pos , 
			sizeof(Vec3) * _shadowNumberOfFaces);	
		pos += sizeof(Vec3) * _shadowNumberOfFaces;

		// 实际点数目	
		_shadowNumberOfVertices = *(long *)(data + pos);	
		pos += sizeof(long);	

		// 点坐标数组
		//assert( _shadowNumberOfVertices > 0 );
		_shadowVerticesOfFaces = new Vec3[_shadowNumberOfVertices];	
		memcpy(_shadowVerticesOfFaces , data+pos , 
			sizeof(Vec3) * _shadowNumberOfVertices);	
		pos += sizeof(Vec3) * _shadowNumberOfVertices;

		// 阴影面所以结构体
		//assert( _shadowNumberOfFaces > 0 );
		_shadowIndicesOfFaces = new ShadowFaceIndex[_shadowNumberOfFaces];
		memcpy(_shadowIndicesOfFaces , data+pos , 
			sizeof(ShadowFaceIndex) * _shadowNumberOfFaces);	
		pos += sizeof(ShadowFaceIndex) * _shadowNumberOfFaces;


		//assert( ( pos + boxpos ) == buf_size );

		_isValid = true;
		return true;
	}
	//----------------------------------------------------------------
	void ModObject::destroy()
	{
		if( _material != NULL )
		{
			delete[] _material;
		}

		if ( _materialFaces != NULL )
		{
			for ( int i = 0; i < _numberOfMaterial ; ++i )
			{
				if( _materialFaces[i].pFace != NULL )
				{
					delete[] _materialFaces[i].pFace;
				}
			}
		}

		if ( _faceIndexOfNoMaterial != NULL )
		{
			delete[] _faceIndexOfNoMaterial;
		}

		if ( _vertexElements != NULL )
		{
			delete[] _vertexElements;
		}

		if ( _shadowNormalOfFaces != NULL )
		{
			delete[] _shadowNormalOfFaces;
		}

		if ( _shadowVerticesOfFaces != NULL)
		{
			delete[] _shadowVerticesOfFaces;
		}

		if ( _shadowIndicesOfFaces != NULL )
		{
			delete[] _shadowIndicesOfFaces;
		}

		setDefault();
	}
	//----------------------------------------------------------------
	void ModObject::setDefault()
	{
		_renderType = 0;
		memset( _name, 0 , 20 );

		_numberOfFaces = 0 ;

		_numberOfMaterial = 0;
		_material = NULL;
		_materialFaces = NULL;

		_numberOfNoMaterial = NULL;
		_faceIndexOfNoMaterial = NULL;

		_numberOfVertices = NULL;
		_vertexElements = NULL;

		// DataPlus
		_shadowNumberOfFaces = NULL;
		_shadowNormalOfFaces = NULL;
		_shadowNumberOfVertices = NULL;
		_shadowVerticesOfFaces = NULL;
		_shadowIndicesOfFaces = NULL;

		_isValid = false;

		_isBaked = false;

		_sizeOfMaterialStruct = 0;
	}
	//----------------------------------------------------------------
	void ModObject::render()
	{
		assert( _isValid == true );

		glPushMatrix();

		for ( int i = 0 ; i < _numberOfMaterial; ++ i )
		{
			if (_materialFaces[i].b_hastexture == false )
			{
				glDisable(GL_TEXTURE_2D);
				glColor3f(1, 1, 1);		

				glInterleavedArrays(GL_T2F_N3F_V3F, 0 , _vertexElements);

				glDrawElements(GL_TRIANGLES, _materialFaces[i].m_numOfFace * 3,
					GL_UNSIGNED_INT,_materialFaces[i].pFace);

				continue;
			}

			//------------------------------------------
			// render with texture
			//------------------------------------------
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0);

			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);

			glColor3f(1, 1, 1);		

			glEnable(GL_TEXTURE_2D);

			//glBindTexture(GL_TEXTURE_2D, pObject->pMats[i].texureId);
			//pMats[i].pTexture->useBind();

			glInterleavedArrays(GL_T2F_N3F_V3F, 0 , _vertexElements);

			glDrawElements(GL_TRIANGLES, _materialFaces[i].m_numOfFace * 3,
				GL_UNSIGNED_INT , _materialFaces[i].pFace);

			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
		}

		if (_numberOfNoMaterial != 0)
		{
			glDisable(GL_TEXTURE_2D);
			glColor3f(0.5, 0.5, 0.5);
			glInterleavedArrays(GL_T2F_N3F_V3F, 0 , _vertexElements);			
			glDrawElements(GL_TRIANGLES, _numberOfNoMaterial * 3,
				GL_UNSIGNED_INT,_faceIndexOfNoMaterial);
		}

		glPopMatrix();

	}
	//----------------------------------------------------------------
}// end of namespace vgMesh

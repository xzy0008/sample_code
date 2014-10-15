


#include <vgStableHeaders.h>
#include <vgMesh/vgmMeshDataPlus.h>
#include <vgMesh/vgmMesh.h>
#include <vgMesh/vgmMeshData.h>
#include <vgMesh/vgmMeshItem.h>
#include <vgMesh/vgmMeshRenderWayVertexArray.h>


namespace vgMesh {
	
	
	
	
	//----------------------------------------------------------------
	void MeshDataPlus::destroy()
	{
		//if ( _wholeChunkOfData == NULL )
		//{
		//	delete _wholeChunkOfData;
		//	_wholeChunkOfData = NULL;
		//}

		if ( _vaway != NULL )
		{
			_vaway->doReferenceDelete();
			_vaway = NULL;
		}

		if ( _shadowMetaFaces != NULL )
		{
			delete[] _shadowMetaFaces;
			_shadowMetaFaces = NULL;
		}

		if ( _shadowDisplayListID != 0 )
		{
			glDeleteLists( _shadowDisplayListID , 1 );
			_shadowDisplayListID  = 0;
		}
	}
	//----------------------------------------------------------------
	bool MeshDataPlus::importFromMeshData( MeshData* meshdata )
	{

		assert( _shadowMetaFaces == NULL );


		//_meshData = meshdata;

		assert( meshdata != NULL );

		MeshRenderWay* renderway = meshdata->getRenderWay();

		MeshRenderWayVertexArray* vaway = 
			dynamic_cast<MeshRenderWayVertexArray*>( renderway );

		assert( vaway != NULL );

		_vaway = vaway;

		if ( vaway == NULL )
		{
			return false;
		}

		_vaway->addRef();

		//assert( vaway->_sizeOfVertexElements == sizeof( VgmVertexElement1 )  );

		_shadowMetaFaces = new ShadowMetaFace[ vaway->_numberOfMetaFaces ];


		for ( int i = 0 ; i < vaway->_numberOfMetaFaces ; ++ i )
		{
			_shadowMetaFaces[i].setFromMetaFaceStruct( 
				vaway , &vaway->_metaFaces[i] , this );
		}

		//------------------------------------------
		// 注意，上一步要完成之后再执行这一步，不然
		// 很多内存都没有申请呢
		//------------------------------------------
		for ( int i = 0 ; i < vaway->_numberOfMetaFaces ; ++ i )
		{
			_shadowMetaFaces[i].searchAndSetAdj();
		}

#if _DEBUG

		for ( int i = 0 ; i < vaway->_numberOfMetaFaces ; ++ i )
		{
			_shadowMetaFaces[i].debugCheckAdj();
		}

#endif

		//vaway->_vertexElements;

		//------------------------------------------
		// 算法：首先查找本face面内的
		//------------------------------------------
		//for ( int i = 0 ; i < vaway->_numberOfMetaFaces; ++ i )
		//{
		//	MetaFaceStruct& face = vaway->_metaFaces[i];

		//	for ( int facei = 0 ; facei < face._numberOfFaceIndex ; ++ i )
		//	{
		//		VgmFaceIndex& faceindex = face._faceIndex[ facei ];

		//	}
		//	
		//}



		return true;
	}
	//----------------------------------------------------------------
	void MeshDataPlus::renderOnceInShadowMode()
	{
		if ( _shadowDisplayListID == 0 )
		{
			//assert( _fatherMesh != NULL );
			if ( _fatherMesh == NULL )
			{
				return;
			}

			vgKernel::Vec3& lightDir = 
				_fatherMesh->getFatherMeshItem()->getShadowLightDirection();

			//vgKernel::Vec3 lightDir( 1 , 0 , 0 );
			//vgKernel::Vec3 downdir(  0 , -1 , 0 );

			//////////////////////////////////////////////////////////////////////////
#if 0

			{

			}
			vgKernel::Quat q1;
			vgKernel::Quat q2;
			vgKernel::Quat q3;
			q1.createFromAxisRadian( 1 , 0 , 0 , lightDir.x );
			q2.createFromAxisRadian( 0 , 1 , 0 , lightDir.y );
			q3.createFromAxisRadian( 0 , 0 , 1 , lightDir.z );

			vgKernel::Mat4 matr;
			vgKernel::Mat4 inv_matr;

			vgKernel::Quat q;

			q = q1 * q2 * q3;

			q.createMatrix( matr._m );

			vgKernel::Math::invertMatrix( matr , inv_matr );

#endif


			//------------------------------------------
			// 开始计算
			//------------------------------------------
			calcuateForShadow(lightDir);

			//------------------------------------------
			// 开始生成display list
			//------------------------------------------
			_shadowDisplayListID = glGenLists(1);
			assert( _shadowDisplayListID != 0 );

			glNewList( _shadowDisplayListID , GL_COMPILE );
			{
				//glDisable( GL_LIGHTING );

				
				//glMultMatrixf(matr._m);

				//glTranslatef( 50 , 0 , 0 );



				glPushMatrix();

				//assert( _vaway->_sizeOfVertexElements == 
				//	sizeof( VgmVertexElement1 ) );

				VgmVertexElement1* elements1 = NULL;
				VgmVertexElement2* elements2 = NULL;

				if ( _vaway->_sizeOfVertexElements == 
					sizeof( VgmVertexElement1 ) )
				{
					elements1 = (VgmVertexElement1*)_vaway->_vertexElements;
				}
				else
				{
					assert( _vaway->_sizeOfVertexElements == sizeof( VgmVertexElement2 ) );

					elements2 = (VgmVertexElement2*)_vaway->_vertexElements;
				}

				static vgKernel::Vec3 farpoint1;
				static vgKernel::Vec3 farpoint2;
				static vgKernel::Vec3 farpoint3;

				for ( int iface = 0 ; iface < _vaway->_numberOfMetaFaces ; ++ iface )
				{
					ShadowMetaFace& cur_face = _shadowMetaFaces[ iface ];

					for ( int j = 0 ; j < cur_face._metaFaceStruct->_numberOfFaceIndex ; ++ j )
					{
						ShadowMetaFaceData& curdata = cur_face._shadowFaceData[j];

						if ( curdata.faceVisible == false )
						{
							continue;
						}

						vgKernel::Vec3* po1 = NULL;
						vgKernel::Vec3* po2 = NULL;
						vgKernel::Vec3* po3 = NULL;

						if ( elements1 != NULL )
						{
							po1 = (vgKernel::Vec3*)
								&elements1[ curdata._faceindex->_point0 ].positionX;

							po2 = (vgKernel::Vec3*)
								&elements1[ curdata._faceindex->_point1 ].positionX;

							po3 = (vgKernel::Vec3*)
								&elements1[ curdata._faceindex->_point2 ].positionX;
						}
						else
						{
							assert( elements2 !=  NULL );

							po1 = (vgKernel::Vec3*)
								&elements2[ curdata._faceindex->_point0 ].positionX;

							po2 = (vgKernel::Vec3*)
								&elements2[ curdata._faceindex->_point1 ].positionX;

							po3 = (vgKernel::Vec3*)
								&elements2[ curdata._faceindex->_point2 ].positionX;
						}

						farpoint1 = *po1 + lightDir * 10000;
						farpoint2 = *po2 + lightDir * 10000;
						farpoint3 = *po3 + lightDir * 10000;

#if 0
						glLineWidth(5.0f);

						
						glBegin( GL_LINES );
						if ( curdata.p1p2Visible )
						{
							glVertex3fv( (float*)po1 );
							//glVertex3fv( farpoint1.v );
							//glVertex3fv( farpoint2.v );
							glVertex3fv( (float*)po2 );
						}
						if ( curdata.p2p3Visible )
						{
							glVertex3fv( (float*)po2 );
							//glVertex3fv( farpoint2.v );
							//glVertex3fv( farpoint3.v );
							glVertex3fv( (float*)po3 );
						}
						if ( curdata.p3p1Visible )
						{
							glVertex3fv( (float*)po3 );
							//glVertex3fv( farpoint3.v );
							//glVertex3fv( farpoint1.v );
							glVertex3fv( (float*)po1 );
						}
						glEnd();
#endif

#if 1
						glBegin( GL_QUADS );
						if ( curdata.p1p2Visible )
						{
							glVertex3fv( (float*)po1 );
							glVertex3fv( farpoint1.v );
							glVertex3fv( farpoint2.v );
							glVertex3fv( (float*)po2 );
						}
						if ( curdata.p2p3Visible )
						{
							glVertex3fv( (float*)po2 );
							glVertex3fv( farpoint2.v );
							glVertex3fv( farpoint3.v );
							glVertex3fv( (float*)po3 );
						}
						if ( curdata.p3p1Visible )
						{
							glVertex3fv( (float*)po3 );
							glVertex3fv( farpoint3.v );
							glVertex3fv( farpoint1.v );
							glVertex3fv( (float*)po1 );
						}
						glEnd();

#endif

					}
				}
				glPopMatrix();
			}
			glEndList();
		}

		glPushMatrix();
		
		//glTranslatef( 200 , 0 , 200 );

		glCallList( _shadowDisplayListID );

		glPopMatrix();
		return;
	}
	//----------------------------------------------------------------
	void MeshDataPlus::calcuateForShadow( const vgKernel::Vec3& lightDir )
	{
		int iface = 0;

		// 首先更新每个normal值
		for (  iface = 0 ; iface < _vaway->_numberOfMetaFaces ; ++ iface )
		{
			ShadowMetaFace& cur_face = _shadowMetaFaces[ iface ];

			for ( int j = 0 ; j < cur_face._metaFaceStruct->_numberOfFaceIndex ; ++ j )
			{
				ShadowMetaFaceData& curdata = cur_face._shadowFaceData[j];

				if ( curdata._normal.dotProduct( lightDir ) <= 0 )
				{
					curdata.faceVisible = true;
				}
				else
				{
					curdata.faceVisible = false;
				}
			}
		}

		// 更新visible的赋值
		for (  iface = 0 ; iface < _vaway->_numberOfMetaFaces ; ++ iface )
		{
			ShadowMetaFace& cur_face = _shadowMetaFaces[ iface ];

			for ( int j = 0 ; j < cur_face._metaFaceStruct->_numberOfFaceIndex ; ++ j )
			{
				ShadowMetaFaceData& curdata = cur_face._shadowFaceData[j];

				if ( curdata.faceVisible == true )
				{
					if ( curdata.p1p2AdjFace != &curdata )
					{
						const bool& linevisible = curdata.p1p2AdjFace->faceVisible;
						curdata.p1p2Visible = (linevisible == false ? true : false );
					}
					else
					{
						curdata.p1p2Visible = true;
					}

					if ( curdata.p2p3AdjFace != &curdata )
					{
						const bool& linevisible =curdata.p2p3AdjFace->faceVisible;
						curdata.p2p3Visible = (linevisible == false ? true : false );
					}
					else
					{
						curdata.p2p3Visible = true;
					}

					if ( curdata.p3p1AdjFace != &curdata )
					{
						const bool& linevisible = curdata.p3p1AdjFace->faceVisible;
						curdata.p3p1Visible = (linevisible == false ? true : false );
					}
					else
					{
						curdata.p3p1Visible = true;
					}

				} // end of cur_face.faceVisible == true
			}
		}
	}
	//----------------------------------------------------------------
	void MeshDataPlus::invalidateShadowRendering()
	{
		assert( _fatherMesh != NULL );

		if ( _shadowDisplayListID != 0 )
		{
			glDeleteLists( _shadowDisplayListID , 1 );
			_shadowDisplayListID  = 0;
		}
	}
	//----------------------------------------------------------------

}// end of namespace vgMesh


#include <vgStableHeaders.h>
#include <vgEffect/vgBillboardConvert.h>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

namespace vgMod
{
//  	BillSetData::BillSetData(BillSetData &p)
//  	{
//  
//  		pTexture = p.pTexture;
//  		texid = p.texid;
//  		m_texname = p.m_texname;
//  		pVertex = p.pVertex;
//  		pFaceNoMat = p.pFaceNoMat;
//  		m_numOfbill = p.m_numOfbill;
//  		_vertexBufferObjectID = p._vertexBufferObjectID;
//  		_elementBufferObjectID = p._elementBufferObjectID;
//  		_isReadyForVBORender = p._isReadyForVBORender;
//  
//  	}
	vgConvertBillboard::vgConvertBillboard(void)
	{
		b_render = false;

	}

	vgConvertBillboard::~vgConvertBillboard(void)
	{


	}

	void vgConvertBillboard::SetRender(bool brender)
	{
		b_render = brender;

		return;
	}
	//----------------------------------------------------------------
	void vgConvertBillboard::Render()
	{

		if (b_render)
		{

			//------------------------------------------
			// in explorer edtion
			//------------------------------------------
			glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE );
			glEnable(GL_TEXTURE_2D);

			//glDisable( GL_BLEND );
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.5f);

			for (int m =0 ; m < BillSet.size(); m++)
			{
				BillSetData *p = BillSet.at(m);

				//------------------------------------------
				// begin VBO
				//------------------------------------------
				if (  p->_isReadyForVBORender == false )
				{

					int nArrayObjectSize = sizeof(VertexElementStruct) * ( p->m_numOfbill) * 4;
					int nParam_ArrayObjectSize = 0;

					if ( nArrayObjectSize != 0 )
					{		
						glGenBuffersARB( 1, & p->_vertexBufferObjectID );
						glBindBufferARB( GL_ARRAY_BUFFER_ARB,  p->_vertexBufferObjectID );
						glBufferDataARB( GL_ARRAY_BUFFER_ARB, nArrayObjectSize,  p->pVertex, GL_STATIC_DRAW_ARB );
						glGetBufferParameterivARB( GL_ARRAY_BUFFER_ARB, GL_BUFFER_SIZE_ARB, &nParam_ArrayObjectSize );

						glMapBufferARB(GL_ARRAY_BUFFER_ARB , GL_READ_WRITE_ARB);

						if( nParam_ArrayObjectSize <= 0 )
						{
							assert(0);
							::MessageBox(NULL,"glBufferDataARB failed to allocate any memory!",
								"ERROR",MB_OK|MB_ICONEXCLAMATION);

						}

#if _DEBUG
						VG_CHECK_OPENGL_ERROR();
#endif
					}


					//------------------------------------------
					// deal m_numOfMat
					//------------------------------------------
					nArrayObjectSize = sizeof(vFaceIndex) *(  p->m_numOfbill);

					glGenBuffersARB( 1, & p->_elementBufferObjectID );
					glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB,  p->_elementBufferObjectID );
					glBufferDataARB( GL_ELEMENT_ARRAY_BUFFER_ARB, nArrayObjectSize,  p->pFaceNoMat, GL_STATIC_DRAW_ARB );

					glGetBufferParameterivARB( GL_ELEMENT_ARRAY_BUFFER_ARB, GL_BUFFER_SIZE_ARB, &nParam_ArrayObjectSize );

					if( nParam_ArrayObjectSize <= 0 )
					{
						MessageBox(NULL,"glBufferDataARB failed to allocate any memory!",
							"ERROR",MB_OK|MB_ICONEXCLAMATION);
					}
					//------------------------------------------
					// end VBO
					//------------------------------------------
					glUnmapBufferARB(GL_ARRAY_BUFFER_ARB);
					if (  p->pVertex != NULL )
					{
						delete[]  p->pVertex;
						 p->pVertex = NULL;
					}

					if (  p->pFaceNoMat != NULL )
					{
						delete[]  p->pFaceNoMat;
						 p->pFaceNoMat = NULL;
					}
#if _DEBUG
					VG_CHECK_OPENGL_ERROR();
#endif

					 p->_isReadyForVBORender = true;

				}

				if (  p->_vertexBufferObjectID == -1 )
				{
					continue;
				}



				cgGLSetTextureParameter(
					cgGetNamedParameter( mpWaterProgram->mCgPixelProgram, "decalMap"), 
					 p->texid );

				mpWaterProgram->useBindBegin();

				//////////////////////////////////////////////////////////////////////////// 
				glBindBufferARB( GL_ARRAY_BUFFER_ARB,  p->_vertexBufferObjectID );


				glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB,  p->_elementBufferObjectID );

				const int nVertexStride = sizeof(VertexElementStruct);
				const int nIndexStride = sizeof(GLubyte);
				const int nOffsetForNormals = sizeof(GLfloat) * 2;
				const int nOffsetForVertices = sizeof(GLfloat) * 5;

				glTexCoordPointer( 2, GL_FLOAT, nVertexStride, BUFFER_OFFSET(0) );
				glNormalPointer( GL_FLOAT, nVertexStride, BUFFER_OFFSET(nOffsetForNormals) );
				glVertexPointer( 3, GL_FLOAT, nVertexStride, BUFFER_OFFSET(nOffsetForVertices) );

				glEnableClientState( GL_TEXTURE_COORD_ARRAY );
				glEnableClientState( GL_NORMAL_ARRAY );
				glEnableClientState( GL_VERTEX_ARRAY );
				glEnableClientState( GL_INDEX_ARRAY );

				glDrawElements(GL_QUADS, ( p->m_numOfbill)* 4, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

				glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, NULL );
#if _DEBUG
				VG_CHECK_OPENGL_ERROR();
#endif


 				mpWaterProgram->useBindEnd();
			}


			glDisable(GL_ALPHA_TEST);
			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);



		}


	}
	void vgConvertBillboard::convert()
	{
		for (int m =0 ; m < BillSet.size(); m++)
		{
			BillSetData *p = BillSet.at(m);

			int k = p->tempvertexbuffer.size();

			p->pVertex = new  VertexElementStruct[k];

			for (int i = 0; i < k; i++)
			{
				p->pVertex[i] = p->tempvertexbuffer.at(i);
			}

			p->tempvertexbuffer.clear();

			k = p->tempface.size();

			p->pFaceNoMat = new vFaceIndex[k];

			for (int i = 0; i < k ; i++)
			{
				p->pFaceNoMat[i] = p->tempface.at(i);
			}

			p->tempface.clear();
		}



		mpWaterProgram = new BillGpuProgram;

		mpWaterProgram->init();

	}
	void vgConvertBillboard::AddBillboard(BillboardNode &node)
	{

		vgCore::Billboard &pp = node.mBillboard;

		int tempid = pp.getTexturePtr()->getTextureID();

		int i;

		for (i = 0; i < BillSet.size(); i++)
		{
			BillSetData *a = BillSet.at(i);

			if (tempid == a->texid)
			{
				AddBillboardToBillSet(node, a);

				break;
			}
		}

		if (i == BillSet.size())
		{
			BillSetData *qq = new BillSetData();

			qq->pTexture = pp.getTexturePtr();

			qq->texid = tempid;

			qq->m_texname = node.m_texturename;

			AddBillboardToBillSet(node, qq);

			BillSet.push_back( qq );
		}
	}

	void vgConvertBillboard::AddBillboardToBillSet(BillboardNode &node, BillSetData *billset)
	{
		vgCore::Billboard &pp = node.mBillboard;

		const Integer& width = pp.getWidth();
		const Integer& height = pp.getHeight();

		const Vector3& pos = pp.getPosition();

		vgCore::VertexElementStruct aa;

		aa.normalX = -1;

		aa.normalY = -1;

		aa.normalZ = floor(width * 100.0) + height / 100.0 ;

		aa.positionX = pos.x;

		aa.positionY = pos.y ;

		aa.positionZ = pos.z ;

		aa.texCoorS = 0.0;

		aa.texCoorT = 0.0;

		billset->tempvertexbuffer.push_back(aa);

		aa.normalX = 1;

		aa.normalY = -1;

		aa.normalZ = floor(width * 100.0) + height / 100.0 ;

		aa.positionX = pos.x;

		aa.positionY = pos.y ;

		aa.positionZ = pos.z ;

		aa.texCoorS = 1.0;

		aa.texCoorT = 0.0;

		billset->tempvertexbuffer.push_back(aa);

		aa.normalX = 1;

		aa.normalY = 1;

		aa.normalZ = floor(width * 100.0) + height / 100.0 ;

		aa.positionX = pos.x;

		aa.positionY = pos.y ;

		aa.positionZ = pos.z ;

		aa.texCoorS = 1.0;

		aa.texCoorT = 1.0;

		billset->tempvertexbuffer.push_back(aa);

		aa.normalX = -1;

		aa.normalY = 1;

		aa.normalZ = floor(width * 100.0) + height / 100.0 ;

		aa.positionX = pos.x;

		aa.positionY = pos.y ;

		aa.positionZ = pos.z ;

		aa.texCoorS = 0.0;

		aa.texCoorT = 1.0;

		billset->tempvertexbuffer.push_back(aa);

		vFaceIndex bb;

		bb.x = billset->m_numOfbill * 4;

		bb.y = billset->m_numOfbill * 4 + 1;

		bb.z = billset->m_numOfbill * 4 + 2;

		bb.v = billset->m_numOfbill * 4 + 3;

		billset->tempface.push_back(bb);

		billset->m_numOfbill ++;
	}
	//------------------------------------------------------
	void vgConvertBillboard::PreWriteProc(BillSetData *billset)
	{
		if ( billset->_isReadyForVBORender == false )
		{				
			int nArrayObjectSize = sizeof(VertexElementStruct) * (billset->m_numOfbill) * 4;
			int nParam_ArrayObjectSize = 0;

			if ( nArrayObjectSize != 0 )
			{		
				glGenBuffersARB( 1, &billset->_vertexBufferObjectID );
				glBindBufferARB( GL_ARRAY_BUFFER_ARB, billset->_vertexBufferObjectID );
				glBufferDataARB( GL_ARRAY_BUFFER_ARB, nArrayObjectSize, billset->pVertex, GL_STATIC_DRAW_ARB );
				glGetBufferParameterivARB( GL_ARRAY_BUFFER_ARB, GL_BUFFER_SIZE_ARB, &nParam_ArrayObjectSize );

				glMapBufferARB(GL_ARRAY_BUFFER_ARB , GL_READ_WRITE_ARB);

				if( nParam_ArrayObjectSize <= 0 )
				{
					assert(0);
					::MessageBox(NULL,"glBufferDataARB failed to allocate any memory!",
						"ERROR",MB_OK|MB_ICONEXCLAMATION);

				}

#if _DEBUG
				VG_CHECK_OPENGL_ERROR();
#endif
			}


			//------------------------------------------
			// deal m_numOfMat
			//------------------------------------------
			nArrayObjectSize = sizeof(vFaceIndex) *( billset->m_numOfbill);

			glGenBuffersARB( 1, &billset->_elementBufferObjectID );
			glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, billset->_elementBufferObjectID );
			glBufferDataARB( GL_ELEMENT_ARRAY_BUFFER_ARB, nArrayObjectSize, billset->pFaceNoMat, GL_STATIC_DRAW_ARB );

			glGetBufferParameterivARB( GL_ELEMENT_ARRAY_BUFFER_ARB, GL_BUFFER_SIZE_ARB, &nParam_ArrayObjectSize );

			if( nParam_ArrayObjectSize <= 0 )
			{
				MessageBox(NULL,"glBufferDataARB failed to allocate any memory!",
					"ERROR",MB_OK|MB_ICONEXCLAMATION);
			}
			//------------------------------------------
			// end VBO
			//------------------------------------------
			glUnmapBufferARB(GL_ARRAY_BUFFER_ARB);
			if ( billset->pVertex != NULL )
			{
				delete[] billset->pVertex;
				billset->pVertex = NULL;
			}

			if ( billset->pFaceNoMat != NULL )
			{
				delete[] billset->pFaceNoMat;
				billset->pFaceNoMat = NULL;
			}
#if _DEBUG
			VG_CHECK_OPENGL_ERROR();
#endif

			billset->_isReadyForVBORender = true;

		}

		if ( billset->_vertexBufferObjectID == -1 )
		{
			assert(0);
			return;
		}

		//------------------------------------------
		// vertex mapping
		//------------------------------------------
		if ( billset->_vertexBufferObjectID == -1 )
		{
			return;
		}

		GLvoid *vertexbuf = NULL;
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, billset->_vertexBufferObjectID );
		vertexbuf = glMapBufferARB(GL_ARRAY_BUFFER_ARB , GL_READ_WRITE_ARB);
		assert( vertexbuf != NULL) ;

		billset->pVertex = (VertexElementStruct*)vertexbuf;


		//------------------------------------------
		// face index mapping
		//------------------------------------------

 		if ( billset->m_numOfbill != 0 )
 		{
 			GLvoid* facenomat = NULL;
 			glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, billset->_elementBufferObjectID );
 			facenomat = glMapBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB , GL_READ_WRITE_ARB);
 			assert( facenomat != NULL);
 
 			billset->pFaceNoMat = (vFaceIndex*)facenomat;
 		}

	}
	//------------------------------------------------------------
	void vgConvertBillboard::WriteToFile(CFile &fp)
	{
 		int k = BillSet.size();
 
 		fp.Write(&k , sizeof(int));
 
 		for (int m =0 ; m < k; m++)
 		{
 			BillSetData *p = BillSet.at(m);
 
 #if VG_VBO_SUPPORT
 			PreWriteProc(p);
 #endif
 			fp.Write(&p->m_numOfbill, sizeof(int));
 
 			fp.Write(p->m_texname.c_str(), 20);
  
  			fp.Write(p->pVertex , sizeof(VertexElementStruct) * p->m_numOfbill * 4);
  
  			fp.Write(p->pFaceNoMat, sizeof(vFaceIndex) * p->m_numOfbill);

			AfterWritefile(p);
		}
	}
	//--------------------------------------------
	void vgConvertBillboard::AfterWritefile(BillSetData *billset)
	{
		if ( billset->_vertexBufferObjectID == -1 )
		{
			return;
		}

		glUnmapBufferARB(GL_ARRAY_BUFFER_ARB);
		billset->pVertex = NULL;

		glBindBufferARB( GL_ARRAY_BUFFER_ARB, NULL );

#	if _DEBUG
		VG_CHECK_OPENGL_ERROR();
#	endif

		if (billset->m_numOfbill != 0)
		{
			GLvoid* facenomat = NULL;
			glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, billset->_elementBufferObjectID );
			glUnmapBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB);

			billset->pFaceNoMat = NULL;
		}

#if _DEBUG
		VG_CHECK_OPENGL_ERROR();
#endif

	}
	//------------------------------------------------------------

	void vgConvertBillboard::ReadFromFile(CFile &fp)
	{
		int k;

		char a[20];

		fp.Read( &k, sizeof(int));

		for (int m =0; m < k; m++)
		{
			BillSetData *p = new BillSetData();

			fp.Read(& p->m_numOfbill, sizeof(int));

			fp.Read(a, 20);

			 p->m_texname = a;

			TextureManager &mgr = 
				TextureManager::getSingleton();

			 p->pTexture = mgr.getTexturePtr( p->m_texname);

			 p->texid =  p->pTexture->getTextureID();

 			 p->pVertex = new VertexElementStruct[ p->m_numOfbill * 4];
 
 			fp.Read( p->pVertex, sizeof(VertexElementStruct) *  p->m_numOfbill * 4);
 
 			 p->pFaceNoMat = new vFaceIndex[ p->m_numOfbill];
 
 			fp.Read( p->pFaceNoMat, sizeof(vFaceIndex) *  p->m_numOfbill);

			BillSet.push_back(p);
		}

		if ( k > 0)
		{
			mpWaterProgram = new BillGpuProgram;

			mpWaterProgram->init();

			b_render = true;
		}

	}


}
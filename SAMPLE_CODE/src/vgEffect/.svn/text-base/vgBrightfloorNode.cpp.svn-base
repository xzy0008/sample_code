

#include <vgStableHeaders.h>
#include <vgEffect/vgBrightfloorNode.h>


namespace vgMod {

#define EFFECT_NAME_LENGTH	128

	//static GLuint brightfloorspheremapid = 0;

	static bool buildFaceTextureUsingGDI_( const String& filename , GLenum target )
	{
		FileInfoPtr pfile = ArchiveManager::getSingleton().getFileInfo( filename );

		if ( pfile.isNull() )
		{
			MessageBox(NULL , "创建立方体贴图时出错." , "Error"  , MB_OK );
			return false;
		}

		NormalImagePtr pimg = ImageFactory::createNormalImagePtr();

		bool ret = pimg->loadFromFileInfo( pfile);

		if ( ret == false )
		{
			assert(0);
		}

		pimg->buildTextureByGLEnum( target );

		//没有用，但是这样可以用于保存纹理。
		vgCore::TextureManager::getSingleton().addTexturePtr( filename );


		return true;
	}

	GLuint buildDecalMapID_( const String& decalmap )
	{
		GLuint textureID = 0;

		vgCore::OpenGLSupport::makeErrorStackEmpty();

		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		VG_CHECK_OPENGL_ERROR();

		if ( !buildFaceTextureUsingGDI_( decalmap , GL_TEXTURE_2D ) )
		{
			assert(0 && " DECALMAP图像载入失败! ");
		}

		return textureID;
	}

	//----------------------------------------------------------------
	BrightfloorNode::BrightfloorNode(int nVersionMod /*= VERSION_1*/)
		:ObjectNode(nVersionMod)
	{
		//_rendererType = RENDERER_TYPE_GPUSPECIAL_FLOOR;
		setDefault();
	}
	//----------------------------------------------------------------
	BrightfloorNode::~BrightfloorNode()
	{
		destroy();
	}
	//----------------------------------------------------------------
	void BrightfloorNode::Render()
	{

		if (! _visible)
			return ;



		if (m_isVisible == false )
		{
			return;
		}

		if (!(_isReadyForVBORender||_readyForDisplayListRendering))
		{
			Initialize();
		}

		prepareForRender();

		if ( _vertexBufferObjectID == -1 )
		{
			assert("You have Forgotten/Failed To Initialize VBO Before Rendering!");
			return;
		}


		_constColor[0] = 1.0 - m_fBumpScale;
		_constColor[1] = 1.0 - m_fBumpScale;
		_constColor[2] = 1.0 - m_fBumpScale;

		//	准备渲染
		glEnable( GL_TEXTURE_2D);
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, _vertexBufferObjectID );
		glPushMatrix();

		//	渲染有材质面
		for (int i = 0; i < m_numOfMat; i++)
		{
			if (pMatRender[i].b_hastexture == true)
			{
				if ( pMatRender[i]._elementBufferObjectID == -1 )
				{
					return;
				}

				//	part 1：准备渲染，设置OpenGL状态、绑定某级Lod的面索引				
				glDisable( GL_BLEND );
				if(m_RenderTypeInt == 1||m_RenderTypeInt == 2)
				{
					glEnable(GL_ALPHA_TEST);
					//Edit by KingHJ @2010.05.26 带通道的物体转光亮物体会转没了，将下面一句注销掉就好了
					//glAlphaFunc(GL_GREATER, 0.5f);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glEnable(GL_BLEND);
				}

				//----------------------------------------------------------------
				glActiveTexture( GL_TEXTURE0 );

				glEnable( GL_TEXTURE_2D );
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);		

				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD );

				if ( pMats[i].pTexture.isNull() == false )
				{
					pMats[i].pTexture->useBind();
				}

				glClientActiveTexture( GL_TEXTURE0 );
				glEnableClientState( GL_TEXTURE_COORD_ARRAY );
				glEnableClientState( GL_NORMAL_ARRAY );
				glEnableClientState( GL_VERTEX_ARRAY );
				glEnableClientState( GL_INDEX_ARRAY );	

				glNormalPointer( GL_FLOAT, m_nVertexStride, BUFFER_OFFSET(m_nOffsetForNormals) );
				glVertexPointer( 3, GL_FLOAT, m_nVertexStride, BUFFER_OFFSET(m_nOffsetForVertices) );
				glTexCoordPointer( 2, GL_FLOAT, m_nVertexStride, BUFFER_OFFSET(0) );



				VGK_CHECK_OPENGL_ERROR();


				glActiveTexture( GL_TEXTURE1 );
				glEnable( GL_TEXTURE_2D );

				glEnable(GL_TEXTURE_GEN_S);
				glEnable(GL_TEXTURE_GEN_T);

				glBindTexture( GL_TEXTURE_2D , _brightfloorspheremapid );
				glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
				glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
				glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_REPLACE);
				glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB, GL_TEXTURE);
				glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB, GL_SRC_COLOR);

				glTexEnvfv( GL_TEXTURE_ENV , GL_TEXTURE_ENV_COLOR , _constColor );

				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
				glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_INTERPOLATE);
				glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB, GL_TEXTURE0);
				glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB, GL_SRC_COLOR );
				glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB, GL_TEXTURE1);
				glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB, GL_SRC_COLOR );
				glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE2_RGB, GL_CONSTANT );
				glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND2_RGB, GL_SRC_COLOR );

				VGK_CHECK_OPENGL_ERROR();


				glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, pMatRender[i]._elementBufferObjectID );


				//----------------------------------------------------------------

				glDrawElements( GL_TRIANGLES, pMatRender[i].m_numOfFace*3, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

				//	part 4：渲染暂时结束
				//resetTexture();

				glDisable( GL_TEXTURE_2D );
				glDisable(GL_TEXTURE_GEN_S);
				glDisable(GL_TEXTURE_GEN_T);
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

				glActiveTexture( GL_TEXTURE0 );
				glClientActiveTexture( GL_TEXTURE0 );
				glDisableClientState( GL_TEXTURE_COORD_ARRAY );
				glDisableClientState( GL_NORMAL_ARRAY );
				glDisableClientState( GL_VERTEX_ARRAY );
				glDisableClientState( GL_INDEX_ARRAY );

				//glClientActiveTexture( GL_TEXTURE0 );
				//glDisableClientState( GL_TEXTURE_COORD_ARRAY );
				//glDisableClientState( GL_NORMAL_ARRAY );
				//glDisableClientState( GL_VERTEX_ARRAY );
				//glDisableClientState( GL_INDEX_ARRAY );

				//glActiveTexture( GL_TEXTURE1 );
				glDisable( GL_BLEND );
				glDisable( GL_ALPHA_TEST );
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

				//glActiveTexture( GL_TEXTURE0 );
				////glDisable(GL_TEXTURE_2D);
				//glDisable( GL_BLEND );
				//glDisable( GL_ALPHA_TEST );


				glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, NULL );

				VGK_CHECK_OPENGL_ERROR();

				//glDisableClientState( GL_TEXTURE_COORD_ARRAY );
				//glDisableClientState( GL_NORMAL_ARRAY );
				//glDisableClientState( GL_VERTEX_ARRAY );
				//glDisableClientState( GL_INDEX_ARRAY );		

			}//	if(纹理文件)
			else
			{
				//renderFaceWithColor(i);
			}// else(颜色)

		}//for ( m_numOfMat )

		//	渲染无材质面
		//renderFaceNoMaterial();

		//	结束渲染
		glPopMatrix();
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, NULL );


		//VGK_CHECK_OPENGL_ERROR();

		//glActiveTexture( GL_TEXTURE1 );
		////
		////glDisableClientState( GL_TEXTURE_COORD_ARRAY );
		////glDisableClientState( GL_NORMAL_ARRAY );
		////glDisableClientState( GL_VERTEX_ARRAY );
		////glDisableClientState( GL_INDEX_ARRAY );		


		////glDisable(GL_TEXTURE_GEN_S);
		////glDisable(GL_TEXTURE_GEN_T);

		////glDisable( GL_BLEND );
		////glDisable( GL_ALPHA_TEST );

		//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		//glDisable( GL_TEXTURE_2D );


		////VGK_CHECK_OPENGL_ERROR();

		//glActiveTexture( GL_TEXTURE0 );
		//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		////glClientActiveTexture( GL_TEXTURE0 );
		////glDisableClientState( GL_TEXTURE_COORD_ARRAY );
		////glDisableClientState( GL_NORMAL_ARRAY );
		////glDisableClientState( GL_VERTEX_ARRAY );
		////glDisableClientState( GL_INDEX_ARRAY );		

		//glDisable(GL_TEXTURE_GEN_S);
		//glDisable(GL_TEXTURE_GEN_T);
		//glDisable( GL_BLEND );

		//glDisable( GL_TEXTURE_2D );


		VGK_CHECK_OPENGL_ERROR();

		return;


#if 0 
		//------------------------------------------
		// 注意!!!只是VBO的情况!
		//------------------------------------------

		if ( mIsInited == false )
		{
			// 直接返回.
			return;
		}


		//mpWaterProgram->setParametersEveryFrame(
		//	Vector3( mpEyeCamera->getCurrentPosition().x,mpEyeCamera->getCurrentPosition().y,
		//	mpEyeCamera->getCurrentPosition() .z) );

		//glPushMatrix();
		//{
		//mpWaterProgram->useBindBegin();

		//mpWaterProgram->useBindEnd();

		ObjectNode::Render();

		//if ( pMats[0].pTexture.isNull() == false )
		//{
		//	pMats[0].pTexture->useBind();

		//glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP); // Set The Texture Generation Mode For S To Sphere Mapping (NEW)
		//glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP); // Set The Texture Generation Mode For T To Sphere Mapping (NEW)

		//glutSolidTeapot( 2.0f );

		//}

		//}
		//glPopMatrix();

#endif
	}
	//----------------------------------------------------------------
	void BrightfloorNode::WriteNodeToVG( CFile &fp )
	{
		//assert( mIsInited == true );

		//------------------------------------------
		// 1.先写文件头必要信息
		//------------------------------------------
		int temp;

		temp = VG_BRIGHTFLOOR;

		long newpos;	

		//fp.Write(&m_id , sizeof(int));                 //写该节点的ID		

		long Posinfile1 = fp.GetPosition();

		fp.Write(&nodelength, sizeof(long));

		fp.Write(&temp , sizeof(int));	               //写类型type


		//------------------------------------------
		// 2.开始写贴图等信息
		//------------------------------------------

		assert( m_StrDecalMap.size() <= EFFECT_NAME_LENGTH );


		char buf[EFFECT_NAME_LENGTH];
		memset( buf , 0 , EFFECT_NAME_LENGTH );
		strcpy( buf , m_StrDecalMap.c_str() );

		fp.Write( buf , EFFECT_NAME_LENGTH);

		fp.Write( &m_fBumpScale , sizeof( float ) );



		//------------------------------------------
		// 3.写入object.这里注意,读出时要对头信息如id,type等信息
		// 跳过才可以.
		//------------------------------------------
		ObjectNode::WriteNodeToVG( fp );


		//------------------------------------------
		// plus.写入nodelength
		//------------------------------------------
		newpos = fp.GetPosition();

		nodelength = newpos - Posinfile1- sizeof(long);

		fp.Seek(Posinfile1, CFile::begin);

		fp.Write(&nodelength, sizeof(long));

		fp.SeekToEnd();

		return;
	}
	//----------------------------------------------------------------
	unsigned long BrightfloorNode::PositDataToNode( char *data )
	{
		unsigned long pos = 0;

		//------------------------------------------
		// 1.先读贴图信息
		//------------------------------------------
		char strbuf[EFFECT_NAME_LENGTH];

		//for ( int i = 0 ; i < 6 ; ++ i )
		//{
		//	memcpy( strbuf , data + pos, EFFECT_NAME_LENGTH );
		//	m_StrEnvMap[i] = strbuf;
		//	pos += ( EFFECT_NAME_LENGTH );
		//}

		//memcpy( strbuf , data + pos, EFFECT_NAME_LENGTH );
		//pos += EFFECT_NAME_LENGTH;
		//m_StrBumpMap = strbuf;

		memcpy( strbuf , data + pos, EFFECT_NAME_LENGTH );
		pos += EFFECT_NAME_LENGTH;
		m_StrDecalMap = strbuf;

		memcpy( &m_fBumpScale , data + pos , sizeof( float ) );
		pos += sizeof( float );

		// 2.跳过object必要头文件信息: long nodelength, int type
		pos += sizeof(long);
		pos += sizeof(int);

		nodelength -= pos;

		// 3.开始object读取
		pos += ObjectNode::PositDataToNode( data + pos );

		// 相机
		//setCamera(vgCam::CamManager::getSingletonPtr() ); 


		//if ( mpWaterProgram == NULL )
		//{
		//	mpWaterProgram = new BrightfloorGpuProgram;
		//}

		bool init_result = initWaterImpl();
		assert( init_result == true );

		return pos;
	}
	//----------------------------------------------------------------
	bool BrightfloorNode::initWaterImpl()
	{

		TexturePtr ptex = 
			vgCore::TextureManager::getSingleton().getTexturePtr( m_StrDecalMap );

		if ( ptex.isNull() == true )
		{
			MessageBox( NULL , "初始化光亮物体错误!" , "", MB_OK );
		}
		else
		{
			_brightfloorspheremapid = ptex->getTextureID();
		}

		//----------------------------------------------------------------

		mIsInited = true;

		return true;
	}
	//----------------------------------------------------------------
	bool BrightfloorNode::recreate( vgCam::CamManager *camera , const vgCore::StringVector& strvec , 
		const String& bumpmap , const String& decalmap , const float& bumpscale )
	{
		if ( mIsInited == true )
		{
			//MessageBox( NULL , "水将被重建" ,"提示"  , MB_OK );
			destroy();
		}

		assert( camera != NULL );

		if ( strvec.size() != 6 )
		{
			MessageBox( NULL , "生成水时立方体贴图设置不正确" ,"警告"  , MB_OK );
			return false;
		}


		m_StrDecalMap = decalmap;
		m_fBumpScale = bumpscale;


		return this->initWaterImpl();
	}
	//----------------------------------------------------------------
	void BrightfloorNode::setDefault()
	{
		mIsInited = false;

		m_fBumpScale = 0.6f;
		mIsInited = false;


		m_StrDecalMap = "";

		//------------------------------------------
		// 注意,写型别信息
		//------------------------------------------
		TYPE = VG_BRIGHTFLOOR;

		_constColor[0] = 1.0f;
		_constColor[1] = 1.0f;
		_constColor[2] = 1.0f;
		_constColor[3] = 1.0f;

		_brightfloorspheremapid = 0;
		setCategory( NODE_TYPE_MOD_EFFECT );
	}
	//----------------------------------------------------------------
	void BrightfloorNode::destroy()
	{

		setDefault();
	}

	void BrightfloorNode::assignTexture( int i )
	{
		if ( pMats[i].pTexture.isNull() == false )
		{
			pMats[i].pTexture->useBind();

			//glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP); // Set The Texture Generation Mode For S To Sphere Mapping (NEW)
			//glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP); // Set The Texture Generation Mode For T To Sphere Mapping (NEW)

		}
		glTexCoordPointer( 2, GL_FLOAT, m_nVertexStride, BUFFER_OFFSET(0) );
	}

	//----------------------------------------------------------------
	vgKernel::StringVector BrightfloorNode::getTexNameVec()
	{
		vgKernel::StringVector texNameVec;

		if ( m_StrDecalMap != "" )
		{
			texNameVec.push_back( m_StrDecalMap );
		}

		return texNameVec;
	}

	//----------------------------------------------------------------





}// end of namespace vgCore

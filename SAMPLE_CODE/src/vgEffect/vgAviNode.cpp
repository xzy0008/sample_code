

#include <vgStableHeaders.h>
#include <vgEffect/vgAviNode.h>

//#include <vgMod/vgQuadtreeSceneManager.h>
#include <vgMod/vgModEffectConvertor.h>
#include <vgMod/vgModUtility.h>
#include <vgKernel/vgkSystemUtility.h>

#include <vgConf/vgcoExeConfig.h>

#define VGDATA_PATHCONF					"DataPathConfig"
#define VGDATA_PATHCONF_PATH_VIDEO		"VideoPath"




namespace vgMod {

	using namespace vgCore;	
#define EFFECT_NAME_LENGTH	128





	//----------------------------------------------------------------
	AviNode::AviNode(int nVersionMod /*= VERSION_1*/)
		:ObjectNode(nVersionMod)
	{
		//_rendererType = RENDERER_TYPE_GPUSPECIAL_AVI;
		setDefault();
	}
	//----------------------------------------------------------------
	AviNode::~AviNode()
	{
		destroy();
	}
	//----------------------------------------------------------------
	void AviNode::Render()
	{
		//------------------------------------------
		// 注意!!!只是VBO的情况!
		//------------------------------------------

		if ( mIsInited == false )
		{
			// 直接返回.
			return;
		}



		//assert(0);


#define BUFFER_OFFSET(i) ((char *)NULL + (i))

		if (m_isVisible == false )
		{
			return;
		}
//		VG_CHECK_OPENGL_ERROR();

		if ( _isReadyForVBORender == false )
		{
			Initialize();
		}
		//glEnable( GL_TEXTURE_2D);
		//glEnable(GL_ALPHA_TEST);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glEnable(GL_BLEND);

		assert( _vertexBufferObjectID != -1 );
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, _vertexBufferObjectID );

		glPushMatrix();

		setOGLTestStates();

		for (int i = 0; i < m_numOfMat; i++)
		{
			if (pMatRender[i].b_hastexture == true)
			{


				assert( pMatRender[i]._elementBufferObjectID != -1 );
				glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, pMatRender[i]._elementBufferObjectID );

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

				glEnable( GL_TEXTURE_2D );
				m_avitexture->GrabAVIFrame(m_avitexture->Update (m_bPlay));

				glDrawElements( GL_TRIANGLES, pMatRender[i].m_numOfFace*3, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

				//glDisableClientState( GL_TEXTURE_COORD_ARRAY );
				//glDisableClientState( GL_NORMAL_ARRAY );
				//glDisableClientState( GL_VERTEX_ARRAY );
				//glDisableClientState( GL_INDEX_ARRAY );

				glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, NULL );

				glDisable( GL_TEXTURE_2D );
			}
		}

		resetOGLTestStates();

		glPopMatrix();
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, NULL );

		//VG_CHECK_OPENGL_ERROR();
	}
	//----------------------------------------------------------------
	void AviNode::WriteNodeToVG( CFile &fp )
	{
		//assert( mIsInited == true );

		// 1.先写文件头必要信息
		int temp;
		temp = VG_AVINODE;

		long newpos;	
		//fp.Write(&m_id , sizeof(int));                 //写该节点的ID		

		long Posinfile1 = fp.GetPosition();

		fp.Write(&nodelength, sizeof(long));

		fp.Write(&temp , sizeof(int));	               //写类型type


		// 2.开始写贴图等信息
		assert( m_StrAvi_basename.size() <= EFFECT_NAME_LENGTH );
		fp.Write(m_StrAvi_basename.c_str() , EFFECT_NAME_LENGTH);


		// 存储avi文件

		String	dest = vgMod::ModEffectConvertor::getProDataPath();

		dest = vgKernel::StringUtility::getPathFromAbsoluteFilename(dest);

		String g_DataPath =  VG_EXECONF_GET_STRING( 
			VGDATA_PATHCONF,  
			VGDATA_PATHCONF_PATH_VIDEO);

		dest = dest + g_DataPath + m_StrAvi_basename;

		bool bReadDerectly = vgMod::ModUtility::getFlagReadDirectly();

		if (!bReadDerectly)
		{
			bool save_ret = vgKernel::SystemUtility::copyFile( m_StrAvi, dest);
			assert( save_ret == true );
		}

		// 3.写入object.这里注意,读出时要对头信息如id,type等信息 , 跳过才可以.
		ObjectNode::WriteNodeToVG( fp );


		// plus.写入nodelength
		newpos = fp.GetPosition();

		nodelength = newpos - Posinfile1- sizeof(long);

		fp.Seek(Posinfile1, CFile::begin);

		fp.Write(&nodelength, sizeof(long));

		fp.SeekToEnd();


		return;
	}
	//----------------------------------------------------------------
	unsigned long AviNode::PositDataToNode( char *data )
	{
		unsigned long pos = 0;

		// 1.先读贴图信息
		char strbuf[EFFECT_NAME_LENGTH];

		memcpy( strbuf , data + pos, EFFECT_NAME_LENGTH );
		pos += EFFECT_NAME_LENGTH;
		m_StrAvi_basename = strbuf;


		// 2.跳过object必要头文件信息: long nodelength, int type
		pos += sizeof(long);
		pos += sizeof(int);

		nodelength -= pos;
		
		// 3.开始object读取
		pos += ObjectNode::PositDataToNode( data + pos );



		String strProDataPath = vgMod::ModEffectConvertor::getProDataPath();
		//m_StrAvi = strProDataPath + m_StrAvi_basename;

		strProDataPath = vgKernel::StringUtility::getPathFromAbsoluteFilename(strProDataPath);

		String g_DataPath =  VG_EXECONF_GET_STRING( 
			VGDATA_PATHCONF,  
			VGDATA_PATHCONF_PATH_VIDEO);

		m_StrAvi = strProDataPath + g_DataPath + m_StrAvi_basename;




		bool init_result = recreate(m_StrAvi);
		assert( init_result == true );

		return pos;
	}

	//----------------------------------------------------------------
	bool AviNode::recreate( const String& decalmap )
	{
		if ( mIsInited == true )
		{
			destroy();
		}

		assert( m_avitexture == NULL );

		m_StrAvi = decalmap;

		m_StrAvi_basename = m_StrAvi.substr(
			m_StrAvi.find_last_of("\\/") + 1 , String::npos );


		m_avitexture = new AviTexture( m_StrAvi.c_str() );


		bool ret = m_avitexture->init();
		
		if ( ret == false )
		{
			return false;
		}


		mIsInited = true;
		return true;
	}
	//----------------------------------------------------------------
	void AviNode::setDefault()
	{
		mIsInited = false;

		m_bPlay = true;

		m_StrAvi = "";
		m_StrAvi_basename = "";

		m_avitexture = NULL;
		//------------------------------------------
		// 注意,写型别信息
		//------------------------------------------
		TYPE = VG_AVINODE;
		setCategory( NODE_TYPE_MOD_EFFECT );
	}
	//----------------------------------------------------------------
	void AviNode::destroy()
	{

		if ( m_avitexture != NULL )
		{
			m_avitexture->CloseAVI();
			delete m_avitexture;
			m_avitexture = NULL;
		}

		setDefault();
	}

	//----------------------------------------------------------------
	void AviNode::setPlayState( bool bPlay )
	{
		m_bPlay = bPlay;
	}

	//----------------------------------------------------------------
	string& AviNode::getAviName()
	{
		return m_StrAvi;
	}

	//----------------------------------------------------------------
	bool AviNode::getInitFlag()
	{
		return mIsInited;
	}

	//----------------------------------------------------------------
	vgKernel::StringVector AviNode::getTexNameVec()
	{
		vgKernel::StringVector texNameVex;
		
		for ( int i = 0; i < m_numOfMat; i++ )
		{
			string strFile = (string)(pMats[i].materialinfo.strFile);
			if ( strFile != "" )
			{
				texNameVex.push_back( strFile );
			}

			string alphaFile = (string)(pMats[i].materialinfo.alphaFile);
			if ( alphaFile != "" )
			{
				texNameVex.push_back( alphaFile );
			}
		}

		return texNameVex;
	}

	//----------------------------------------------------------------
	void AviNode::setOGLTestStates()
	{
		if (isDissolveable())
		{
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);			

			glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
			glEnable( GL_TEXTURE_2D );
			glColor4f( 1.0f, 1.0f, 1.0f, getDissolveAlpha() );	

		}

	}
	//----------------------------------------------------------------
	void AviNode::resetOGLTestStates()
	{
		if (isDissolveable())
		{
			glDisable(GL_BLEND);
		}
	}
	//----------------------------------------------------------------


}// end of namespace vgCore

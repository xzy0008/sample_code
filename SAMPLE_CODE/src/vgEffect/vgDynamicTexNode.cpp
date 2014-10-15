

#include <vgStableHeaders.h>
#include <vgEffect/vgDynamicTexNode.h>

//#include <vgMod/vgQuadtreeSceneManager.h>
#include <vgMod/vgModEffectConvertor.h>

#include <vgMod/vgModUtility.h>
#include <vgKernel/vgkSystemUtility.h>



#include <vgConf/vgcoExeConfig.h>

#define VGDATA_PATHCONF					"DataPathConfig"
#define VGDATA_PATHCONF_PATH_MODEFFECT	"ModEffectPath"


namespace vgMod {

	using namespace vgCore;
	
#define EFFECT_NAME_LENGTH	128



	//extern BOOL CommonCopyFile(CString SourceFileName, CString DestFileName);

	//----------------------------------------------------------------
	DynamicTexNode::DynamicTexNode(int nVersionMod /*= VERSION_1*/)
		:ObjectNode(nVersionMod)
	{
		setDefault();
	}
	//----------------------------------------------------------------
	DynamicTexNode::~DynamicTexNode()
	{
		destroy();
	}
	//----------------------------------------------------------------
	void DynamicTexNode::Render()
	{
		//------------------------------------------
		// 注意!!!只是VBO的情况!
		//------------------------------------------

		if ( mIsInited == false )
		{
			// 直接返回.
			return;
		}

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

		if (m_isVisible == false )
		{
			return;
		}

		if ( _isReadyForVBORender == false )
		{
			Initialize();
		}

		assert( _vertexBufferObjectID != -1 );
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, _vertexBufferObjectID );

		glPushMatrix();

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

				glEnable( GL_BLEND );
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				glEnable(GL_ALPHA_TEST);
				glAlphaFunc(GL_GREATER, 0.1f);
				//*********************************************************
				m_dyntexture->GetFrameTexture(m_dyntexture->Update());

  				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);	// Set Texture Max Filter
  				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);	// Set Texture Min Filter
 
				//*********************************************************

				glDrawElements( GL_TRIANGLES, pMatRender[i].m_numOfFace*3, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

				glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, NULL );
	
				glDisable( GL_BLEND );
				glDisable(GL_ALPHA_TEST);
				glDisable( GL_TEXTURE_2D );
			}
		}

		glPopMatrix();
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, NULL );


		//VG_CHECK_OPENGL_ERROR();
	}
	//----------------------------------------------------------------
	void DynamicTexNode::WriteNodeToVG( CFile &fp )
	{
		//assert( mIsInited == true );

		// 1.先写文件头必要信息
		int temp;
		temp = VG_DYNAMICTEXNODE;

		long newpos;	
		//fp.Write(&m_id , sizeof(int));                 //写该节点的ID		

		long Posinfile1 = fp.GetPosition();

		fp.Write(&nodelength, sizeof(long));

		fp.Write(&temp , sizeof(int));	               //写类型type


		// 2.开始写贴图等信息
		assert( m_StrDtx_basename.size() <= EFFECT_NAME_LENGTH );
		fp.Write(m_StrDtx_basename.c_str() , EFFECT_NAME_LENGTH);
		
		ObjectNode::WriteNodeToVG( fp );

		// plus.写入nodelength
		newpos = fp.GetPosition();

		nodelength = newpos - Posinfile1- sizeof(long);

		fp.Seek(Posinfile1, CFile::begin);

		fp.Write(&nodelength, sizeof(long));

		fp.SeekToEnd();

		// 存储DTX文件
#if 0
		String	dest = vgMod::ModEffectConvertor::getProDataPath() + m_StrDtx_basename;
#else
		String	dest = vgMod::ModEffectConvertor::getProDataPath();

		dest = vgKernel::StringUtility::getPathFromAbsoluteFilename(dest);

		String g_DataPath =  VG_EXECONF_GET_STRING( 
			VGDATA_PATHCONF,  
			VGDATA_PATHCONF_PATH_MODEFFECT);

		dest = dest + g_DataPath + m_StrDtx_basename;
#endif

		bool bReadDerectly = vgMod::ModUtility::getFlagReadDirectly();

		if (!bReadDerectly)
		{
			bool save_ret = vgKernel::SystemUtility::copyFile( m_StrDtx , dest );
			assert( save_ret == true );
		}

		return;
	}
	//----------------------------------------------------------------
	unsigned long DynamicTexNode::PositDataToNode( char *data )
	{
		unsigned long pos = 0;

		// 1.先读DTX文件信息
		char strbuf[EFFECT_NAME_LENGTH];

		memcpy( strbuf , data + pos, EFFECT_NAME_LENGTH );
		pos += EFFECT_NAME_LENGTH;
		m_StrDtx_basename = strbuf;


		// 2.跳过object必要头文件信息: long nodelength, int type
		pos += sizeof(long);
		pos += sizeof(int);

		nodelength -= pos;
		
		// 3.开始object读取
		pos += ObjectNode::PositDataToNode( data + pos );

		/*QuadtreeSceneManager &mgr = 
			QuadtreeSceneManager::getSingleton();

		m_StrDtx = vgGlobal::SystemFacade::getCurrentScenePath()+
			"\\ProAttachdata\\" + m_StrDtx_basename;*/

		String strProDataPath = vgMod::ModEffectConvertor::getProDataPath();
#if 0		
		m_StrDtx = strProDataPath + m_StrDtx_basename;
#else
		strProDataPath = vgKernel::StringUtility::getPathFromAbsoluteFilename(strProDataPath);

		String g_DataPath =  VG_EXECONF_GET_STRING( 
			VGDATA_PATHCONF,  
			VGDATA_PATHCONF_PATH_MODEFFECT);

		m_StrDtx = strProDataPath + g_DataPath + m_StrDtx_basename;

#endif

		bool init_result = recreate(m_StrDtx);
		assert( init_result == true );

		return pos;
	}

	//----------------------------------------------------------------
	bool DynamicTexNode::recreate( const String& decalmap )
	{
		if ( mIsInited == true )
		{
			destroy();
		}

//  	assert( m_dyntexture == NULL );

		m_StrDtx = decalmap;

		m_StrDtx_basename = m_StrDtx.substr(
			m_StrDtx.find_last_of("\\/") + 1 , String::npos );

 		m_dyntexture = new DynamicTexture( m_StrDtx );

 		bool ret = m_dyntexture->init();
		
 		if ( ret == false )
 		{
 			return false;
 		}

		mIsInited = true;
		return true;
	}
	//----------------------------------------------------------------
	void DynamicTexNode::setDefault()
	{
		mIsInited = false;

		m_StrDtx = "";
		m_StrDtx_basename = "";

 		m_dyntexture = NULL;
		//------------------------------------------
		// 注意,写型别信息
		//------------------------------------------
		TYPE = VG_DYNAMICTEXNODE;
		setCategory( NODE_TYPE_MOD_EFFECT );
	}
	//----------------------------------------------------------------
	void DynamicTexNode::destroy()
	{
 
 		if ( m_dyntexture != NULL )
 		{
 			delete m_dyntexture;
 			m_dyntexture = NULL;
 		}

		setDefault();
	}
	//----------------------------------------------------------------
	vgKernel::StringVector DynamicTexNode::getTexNameVec()
	{
		vgKernel::StringVector texNameVec;
		
		if ( m_dyntexture != NULL )
		{
			vgKernel::StringVector tempVec = m_dyntexture->getTexfilePaths();

			for ( int i = 0; i < tempVec.size(); i++ )
			{
				string texName = tempVec[i].substr( tempVec[i].find_last_of("\\/") + 1 , String::npos );
				if ( texName != "" )
				{
					texNameVec.push_back( texName );
				}
			}
		}

		return texNameVec;
	}
	





}// end of namespace vgCore

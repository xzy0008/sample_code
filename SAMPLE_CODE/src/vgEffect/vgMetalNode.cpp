

#include <vgStableHeaders.h>
#include <vgEffect/vgMetalNode.h>


namespace vgMod {

	VGK_RENDERER_IMPLEMENT( MetalNode , RENDERER_TYPE_GPUSPECIAL_METAL )

	using namespace vgCore;	
#define EFFECT_NAME_LENGTH	128
	//----------------------------------------------------------------
	MetalNode::MetalNode(int nVersionMod /*= VERSION_1*/)
		:ObjectNode(nVersionMod)
	{
		//_rendererType = RENDERER_TYPE_GPUSPECIAL_METAL;
		setDefault();
	}
	//----------------------------------------------------------------
	MetalNode::~MetalNode()
	{
		destroy();
	}
	//----------------------------------------------------------------
	void MetalNode::Render()
	{
		//------------------------------------------
		// 注意!!!只是VBO的情况!
		//------------------------------------------

		if ( mIsInited == false )
		{
			// 直接返回.
			return;
		}


		mpGpuProgram->setParametersEveryFrame(
			Vector3(
			vgCam::CamManager::getSingleton().getCurrentPosition().x ,
			vgCam::CamManager::getSingleton().getCurrentPosition().y ,
			vgCam::CamManager::getSingleton().getCurrentPosition().z ));

		glPushMatrix();
		{
			mpGpuProgram->useBindBegin();
			RenderWithoutTex(1,1,1);
			mpGpuProgram->useBindEnd();
		}
		glPopMatrix();

	}
	//----------------------------------------------------------------
	void MetalNode::WriteNodeToVG( CFile &fp )
	{
		//assert( mIsInited == true );

		//------------------------------------------
		// 1.先写文件头必要信息
		//------------------------------------------
		int temp;

		temp = VG_METAL;

		long newpos;	

		//fp.Write(&m_id , sizeof(int));                 //写该节点的ID		

		long Posinfile1 = fp.GetPosition();

		fp.Write(&nodelength, sizeof(long));

		fp.Write(&temp , sizeof(int));	               //写类型type


		//------------------------------------------
		// 2.开始写贴图等信息
		//------------------------------------------
		for ( int i= 0 ; i < 6 ; ++ i )
		{
			assert( m_StrEnvMap[i].size() <= EFFECT_NAME_LENGTH );
			fp.Write( m_StrEnvMap[i].c_str() , EFFECT_NAME_LENGTH );
		}

		assert( m_StrBumpMap.size() <= EFFECT_NAME_LENGTH );
		assert( m_StrDecalMap.size() <= EFFECT_NAME_LENGTH );

		fp.Write(m_StrBumpMap.c_str() , EFFECT_NAME_LENGTH);
		fp.Write(m_StrDecalMap.c_str() , EFFECT_NAME_LENGTH);

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
	unsigned long MetalNode::PositDataToNode( char *data )
	{
		unsigned long pos = 0;

		//------------------------------------------
		// 1.先读贴图信息
		//------------------------------------------
		char strbuf[EFFECT_NAME_LENGTH];

		for ( int i = 0 ; i < 6 ; ++ i )
		{
			memcpy( strbuf , data + pos, EFFECT_NAME_LENGTH );
			m_StrEnvMap[i] = strbuf;
			pos += ( EFFECT_NAME_LENGTH );
		}
		
		memcpy( strbuf , data + pos, EFFECT_NAME_LENGTH );
		pos += EFFECT_NAME_LENGTH;
		m_StrBumpMap = strbuf;

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
		setCamera(vgCam::CamManager::getSingletonPtr() ); 

		if ( mpGpuProgram == NULL )
		{
			mpGpuProgram = new MetalGpuProgram;
		}

		bool init_result = initWaterImpl();
		assert( init_result == true );

		return pos;
	}
	//----------------------------------------------------------------
	bool MetalNode::initWaterImpl()
	{
		try
		{
			vgCore::StringVector temp;
			for ( int i = 0 ; i < 6 ; ++ i )
			{
				temp.push_back( m_StrEnvMap[i] );
			}

			mpGpuProgram->setParametersOnce(  _T("") ,("") , 
				temp , m_StrBumpMap , m_StrDecalMap , m_fBumpScale );

			mpGpuProgram->init();

		}
		catch (vgCore::Exception &e)
		{
			MessageBox( NULL , e.getFullDescription().c_str(), "水初始化出现错误!", MB_OK );
			return false;
		}

		mIsInited = true;

		return true;
	}
	//----------------------------------------------------------------
	bool MetalNode::recreate( vgCam::CamManager *camera , const vgCore::StringVector& strvec , 
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

		///配置自身参数
		for ( int i= 0 ; i < 6 ; ++ i )
		{
			m_StrEnvMap[i] = strvec[i];
		}

		m_StrBumpMap = bumpmap;
		m_StrDecalMap = decalmap;
		m_fBumpScale = bumpscale;

		if ( mpGpuProgram == NULL )
		{
			mpGpuProgram = new MetalGpuProgram;
		}

		this->setCamera( camera );

		return this->initWaterImpl();
	}
	//----------------------------------------------------------------
	void MetalNode::setDefault()
	{
		mIsInited = false;
		mpEyeCamera = NULL;

		mpGpuProgram = NULL;
		m_fBumpScale = 0.6f;
		mIsInited = false;

		for ( int i = 0 ; i < 6 ; ++i )
		{
			m_StrEnvMap[i] = "";
		}

		m_StrBumpMap = "";
		m_StrDecalMap = "";

		//------------------------------------------
		// 注意,写型别信息
		//------------------------------------------
		TYPE = VG_METAL;
		setCategory( NODE_TYPE_MOD_EFFECT );
	}
	//----------------------------------------------------------------
	void MetalNode::destroy()
	{
		if ( mpGpuProgram != NULL )
		{
			delete mpGpuProgram;
			mpGpuProgram = NULL;
		}

		setDefault();
	}

	//----------------------------------------------------------------
	vgKernel::StringVector MetalNode::getTexNameVec()
	{
		vgKernel::StringVector texNameVec;

		for( int i = 0; i < 6; i++ )
		{
			if ( m_StrEnvMap[i] != "" )
			{
				texNameVec.push_back( m_StrEnvMap[i] );
			}
		}

		if ( m_StrBumpMap != "" )
		{
			texNameVec.push_back( m_StrBumpMap );
		}

		if ( m_StrDecalMap != "" )
		{
			texNameVec.push_back( m_StrDecalMap );
		}

		return texNameVec;
	}

	//----------------------------------------------------------------





}// end of namespace vgCore

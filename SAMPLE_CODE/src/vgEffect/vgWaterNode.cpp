

#include <vgStableHeaders.h>
#include <vgEffect/vgWaterNode.h>

#include <vgMod/vgModUtility.h>
#include <vgMod/vgVersionControl.h>  // Added By FengYK @2010-03-27 17:08 读取vg版本信息

namespace vgMod {

	//using namespace vgCore;
#define EFFECT_NAME_LENGTH	128

	//----------------------------------------------------------------
	WaterNode::WaterNode(int nVersionMod /*= VERSION_1*/)
		:ObjFrameNode(nVersionMod)
	{
		//_rendererType = RENDERER_TYPE_GPUSPECIAL_WARTER;
		setDefault();
	}
	//----------------------------------------------------------------
	WaterNode::~WaterNode()
	{
		destroy();
	}
	//----------------------------------------------------------------
	void WaterNode::Render()
	{

		//------------------------------------------
		// 注意!!!只是VBO的情况!
		//------------------------------------------

		if ( mIsInited == false )
		{
			// 直接返回.
			return;
		}

		if (!(_isReadyForVBORender||_readyForDisplayListRendering))
		{
			Initialize();
		}


		glEnable( GL_BLEND );
		glBlendFunc( GL_CONSTANT_ALPHA ,
			GL_ONE_MINUS_CONSTANT_ALPHA );

		glBlendColor( m_redValue, m_greenValue, m_blueValue, m_alphaVaule );

		mpWaterProgram->_utimeline = _utimeline;
		mpWaterProgram->_vtimeline = _vtimeline;

  		mpWaterProgram->setParametersEveryFrame( 
  			Vector3( mpEyeCamera->getCurrentPosition().x,mpEyeCamera->getCurrentPosition().y,
  			mpEyeCamera->getCurrentPosition() .z) );

 		glPushMatrix();
 		{
			mpWaterProgram->useBindBegin();
		
			//RenderWithoutTex(1,1,1);
			//RenderWithoutTex(1,1,1);
			ObjFrameNode::RenderWithoutTex(1,1,1);
			
			mpWaterProgram->useBindEnd();
 		}
 		glPopMatrix();
		
		glDisable(GL_BLEND);
	}
	//----------------------------------------------------------------
	void WaterNode::WriteNodeToVG( CFile &fp )
	{
		//assert( mIsInited == true );

		//------------------------------------------
		// 1.先写文件头必要信息
		//------------------------------------------
		int temp;

		temp = VG_WATER;

		long newpos;	

		//fp.Write(&m_id , sizeof(int));                 //写该节点的ID		

		long Posinfile1 = fp.GetPosition();

		fp.Write(&nodelength, sizeof(long));

		fp.Write(&temp , sizeof(int));	               //写类型type


		//------------------------------------------
		// 2.开始写贴图等信息
		//------------------------------------------
		char buf[ EFFECT_NAME_LENGTH ];
		memset( buf , 0 , EFFECT_NAME_LENGTH );

		for ( int i= 0 ; i < 6 ; ++ i )
		{
			assert( m_StrEnvMap[i].size() <= EFFECT_NAME_LENGTH );
			memset( buf , 0 , EFFECT_NAME_LENGTH );
			strcpy( buf , m_StrEnvMap[i].c_str() );
			fp.Write( buf , EFFECT_NAME_LENGTH );
		}

		assert( m_StrBumpMap.size() <= EFFECT_NAME_LENGTH );
		assert( m_StrDecalMap.size() <= EFFECT_NAME_LENGTH );

		memset( buf , 0 , EFFECT_NAME_LENGTH );
		strcpy( buf , m_StrBumpMap.c_str() );
		fp.Write(buf , EFFECT_NAME_LENGTH);

		memset( buf , 0 , EFFECT_NAME_LENGTH );
		strcpy( buf , m_StrDecalMap.c_str() );
		fp.Write(buf , EFFECT_NAME_LENGTH);

		fp.Write( &m_fBumpScale , sizeof( float ) );


		// added by zsc 写入半透明参数
		fp.Write( &m_redValue, sizeof(float) );
		fp.Write( &m_greenValue, sizeof(float) );
		fp.Write( &m_blueValue, sizeof(float) );
		fp.Write( &m_alphaVaule, sizeof(float) );

		// Added By FengYK @2010-03-23 13:30 写入水流方向信息 vg 2.19版本
		fp.Write( &_utimeline, sizeof(float) );
		fp.Write( &_vtimeline, sizeof(float) );

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
	unsigned long WaterNode::PositDataToNode( char *data )
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

		// added by zsc 读入保存的半透明参数
		memcpy( &m_redValue, data + pos , sizeof(float) );
		pos += sizeof ( float );

		memcpy( &m_greenValue, data + pos , sizeof(float) );
		pos += sizeof (float);

		memcpy( &m_blueValue, data + pos, sizeof(float) );
		pos += sizeof (float);

		memcpy( &m_alphaVaule, data + pos , sizeof(float) );
		pos += sizeof (float);

		// Added By FengYK 读取保存的水流方向信息
		// 如果vg 版本号低于 2.19 则无此数据,不进行读取
		String vgVersion = vgMod::VersionControl::getVgVersionRead();

		if ( vgVersion >= String("VRGIS.VERSION 2.19") )
		{
			memcpy( &_utimeline, data + pos , sizeof(float) );
			pos += sizeof (float);

			memcpy( &_vtimeline, data + pos , sizeof(float) );
			pos += sizeof (float);
		}

		// 2.跳过object必要头文件信息: long nodelength, int type
		pos += sizeof(long);
		pos += sizeof(int);

		nodelength -= pos;
		// 3.开始object读取
		pos += ObjectNode::PositDataToNode( data + pos );

		// 相机
		setCamera(vgCam::CamManager::getSingletonPtr() ); 

		bool bReadDerectly = vgMod::ModUtility::getFlagReadDirectly( );
		if( !bReadDerectly )
		{
			if ( mpWaterProgram == NULL )
			{
				mpWaterProgram = new WaterGpuProgram;
			}

			bool init_result = initWaterImpl();
			assert( init_result == true );
		}
		return pos;
	}
	//----------------------------------------------------------------
	bool WaterNode::initWaterImpl()
	{
		try
		{
			vgCore::StringVector temp;
			for ( int i = 0 ; i < 6 ; ++ i )
			{
				temp.push_back( m_StrEnvMap[i] );
			}

			mpWaterProgram->setParametersOnce(  _T("") ,("") , 
				temp , m_StrBumpMap , m_StrDecalMap , m_fBumpScale );

			mpWaterProgram->init();

		}
		catch (vgCore::Exception &e)
		{
			MessageBox( NULL , e.getFullDescription().c_str(), "水初始化出现错误!", MB_OK );
			return false;
		}

		mIsInited = true;

		return true;
	}
	//chunyongma----------------------------------------------------------------
	bool WaterNode::recreate( vgCam::CamManager *camera , const vgCore::StringVector& strvec , 
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

		if ( mpWaterProgram == NULL )
		{
			mpWaterProgram = new WaterGpuProgram;
		}

		this->setCamera( camera );

		return this->initWaterImpl();
	}
	//----------------------------------------------------------------
	vgKernel::StringVector WaterNode::getTexNameVec()
	{
		vgKernel::StringVector texNameVec;
		for ( int i = 0; i < 6; i++ )
		{
			if ( m_StrEnvMap[i] != "" )
			{
				texNameVec.push_back( m_StrEnvMap[i] );
			}
		}

		if ( m_StrBumpMap != "")
		{
			texNameVec.push_back( m_StrBumpMap );
		}

		if( m_StrDecalMap != "" )
		{
			texNameVec.push_back( m_StrDecalMap );
		}

		return texNameVec;
	}

	//----------------------------------------------------------------
	void WaterNode::setDefault()
	{
		mIsInited = false;
		mpEyeCamera = NULL;

		mpWaterProgram = NULL;
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
		TYPE = VG_WATER;

		m_redValue = 1;
		m_blueValue = 1;
		m_greenValue = 1;
		m_alphaVaule = 1;

		_utimeline = 50.0;
		_vtimeline = 50.0;

		setCategory( NODE_TYPE_MOD_EFFECT );
	}
	//----------------------------------------------------------------
	void WaterNode::destroy()
	{
		if ( mpWaterProgram != NULL )
		{
			delete mpWaterProgram;
			mpWaterProgram = NULL;
		}

		setDefault();
	}
	//----------------------------------------------------------------

	//////////////////////////////////////////////////////////////////////////chunyongma
// 	template<>
// 	PropertiesParam	GpuseAdapter::s_ParamArray[s_NumOfParam];
	//	bcg






}// end of namespace vgCore

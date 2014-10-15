

#include <vgStableHeaders.h>
#include <vgEffect/vgSkyboxNode.h>
//#include <vgMod/vgQuadtreeSceneManager.h>

namespace vgMod {

	using namespace vgCore;
	

#define EFFECT_NAME_LENGTH	128

	//----------------------------------------------------------------
	SkyboxNode::SkyboxNode(int nVersionMod /*= VERSION_1*/)
		:ObjectNode(nVersionMod)
	{
		//_rendererType = RENDERER_TYPE_GPUSPECIAL_SKYNODE;
		setDefault();
	}
	//----------------------------------------------------------------
	SkyboxNode::~SkyboxNode()
	{
		destroy();
	}
	//----------------------------------------------------------------
	void SkyboxNode::Render()
	{
		//------------------------------------------
		// 注意!!!只是VBO的情况!
		//------------------------------------------

//		this->m_BoundryBox = 
//			QuadtreeSceneManager::getSingleton().rootnode->aabb;


		glPushMatrix();
		{
			glTranslatef( mpEyeCamera->getCurrentPosition().x - _oldPosX ,
				0 ,  mpEyeCamera->getCurrentPosition().z  - _oldPosZ );

			ObjectNode::Render();
		}
		glPopMatrix();

	}
	//----------------------------------------------------------------
	void SkyboxNode::WriteNodeToVG( CFile &fp )
	{

		//assert( mIsInited == true );

		//------------------------------------------
		// 1.先写文件头必要信息
		//------------------------------------------
		int temp;
		temp = VG_SKYBOX;

		//fp.Write(&m_id , sizeof(int));                 //写该节点的ID		

		long Posinfile1 = fp.GetPosition();

		fp.Write(&nodelength, sizeof(long));

		fp.Write(&temp , sizeof(int));	               //写类型type
	

		fp.Write(&_oldPosX , sizeof( float ));
		fp.Write(&_oldPosZ , sizeof( float ));
		

		//------------------------------------------
		// 3.写入object.这里注意,读出时要对头信息如id,type等信息
		// 跳过才可以.
		//------------------------------------------
		ObjectNode::WriteNodeToVG( fp );

		//------------------------------------------
		// plus.写入nodelength
		//------------------------------------------
		long newpos = fp.GetPosition();

		nodelength = newpos - Posinfile1- sizeof(long);

		fp.Seek(Posinfile1, CFile::begin);

		fp.Write(&nodelength, sizeof(long));

		fp.SeekToEnd();

		return;
	}
	//----------------------------------------------------------------
	unsigned long SkyboxNode::PositDataToNode( char *data )
	{
		unsigned long pos = 0;
		

		_oldPosX = *(float*)(data + pos);
		pos += sizeof( float );
		_oldPosZ = *(float*)(data + pos);
		pos += sizeof( float );
		
		// 2.跳过object必要头文件信息: long nodelength, int type
		pos += sizeof(long);
		pos += sizeof(int);

		nodelength -= pos;

		// 3.开始object读取
		pos += ObjectNode::PositDataToNode( data + pos );

		
		// 相机
		/*_oldPosX = 
			vgCam::CamManager::getSingleton().getCurrentPosition().x;
		_oldPosZ = 
			vgCam::CamManager::getSingleton().getCurrentPosition().z;*/

		setCamera(vgCam::CamManager::getSingletonPtr() ); 

		//vgCam::CamManager* camera = NULL;// 待修改！ &QuadtreeSceneManager::getSingleton().GetCurrentCamera();
		//setCamera( camera );

		bool init_result = initImpl();
		assert( init_result == true );

		return pos;
	}
	//----------------------------------------------------------------
	bool SkyboxNode::initImpl()
	{
		//try
		//{
		//	StringVector temp;
		//	for ( int i = 0 ; i < 6 ; ++ i )
		//	{
		//		temp.push_back( m_StrEnvMap[i] );
		//	}

		//	mpWaterProgram->setParametersOnce(  _T("") ,("") , 
		//		temp , m_StrBumpMap , m_StrDecalMap , m_fBrightness );

		//	mpWaterProgram->init();

		//}
		//catch (Exception &e)
		//{
		//	MessageBox( NULL , e.getFullDescription().c_str(), "水初始化出现错误!", MB_OK );
		//	return false;
		//}

		mIsInited = true;

		return true;
	}
	//----------------------------------------------------------------
	//bool SkyboxNode::recreate( CameraNode *camera , const StringVector& strvec , 
	//	const String& bumpmap , const String& decalmap , const float& bumpscale )
	//{
	//	if ( mIsInited == true )
	//	{
	//		//MessageBox( NULL , "水将被重建" ,"提示"  , MB_OK );
	//		destroy();
	//	}

	//	assert( camera != NULL );

	//	if ( strvec.size() != 6 )
	//	{
	//		MessageBox( NULL , "生成水时立方体贴图设置不正确" ,"警告"  , MB_OK );
	//		return false;
	//	}

	//	///配置自身参数
	//	for ( int i= 0 ; i < 6 ; ++ i )
	//	{
	//		m_StrEnvMap[i] = strvec[i];
	//	}

	//	m_StrBumpMap = bumpmap;
	//	m_StrDecalMap = decalmap;
	//	m_fBrightness = bumpscale;

	//	if ( mpWaterProgram == NULL )
	//	{
	//		mpWaterProgram = new MirrorGpuProgram;
	//	}

	//	this->setCamera( camera );

	//	return this->initImpl();
	//}
	//----------------------------------------------------------------
	void SkyboxNode::setDefault()
	{
		mIsInited = false;
		mpEyeCamera = NULL;

		mIsInited = true;
		// 注意,写型别信息
		//------------------------------------------
		TYPE = VG_SKYBOX;

		m_RenderTypeInt = 2;
		setCategory( NODE_TYPE_MOD_EFFECT );
	}
	//----------------------------------------------------------------
	void SkyboxNode::destroy()
	{
		//if ( mpWaterProgram != NULL )
		//{
		//	delete mpWaterProgram;
		//	mpWaterProgram = NULL;
		//}

		setDefault();
	}

	//----------------------------------------------------------------
	vgKernel::StringVector SkyboxNode::getTexNameVec()
	{
		vgKernel::StringVector texNameVec;

		for ( int i = 0; i < m_numOfMat; i++ )
		{
			string strFile = (string)( pMats[i].materialinfo.strFile );
			if ( strFile != "" )
			{
				texNameVec.push_back( strFile );
			}

			string alphaFile = (string)( pMats[i].materialinfo.alphaFile );
			if ( alphaFile != "" )
			{
				texNameVec.push_back( alphaFile );
			}
		} // end for i

		return texNameVec;
	}






}// end of namespace vgCore

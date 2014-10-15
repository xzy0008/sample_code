
#include <vgStableHeaders.h>
#include <vgEffect/vgDynamicBillBoardNode.h>


#include <vgConf/vgcoExeConfig.h>

#define VGDATA_PATHCONF					"DataPathConfig"
#define VGDATA_PATHCONF_PATH_MODEFFECT	"ModEffectPath"


namespace vgMod {
	
	VGK_RENDERER_IMPLEMENT( DynamicBillboardNode , RENDERER_TYPE_DYNAMICBILLBOARD )

	using namespace vgMath;

	DynamicBillboardNode::DynamicBillboardNode()
		: _uniqueID(vgKernel::UniqueIDFactory::getUniqueID() )
		, vgMod::Node( NODE_TYPE_FOUNTAIN )
	{

		TYPE = VG_DYNAMICBILLBOARDNODE;

		m_height = 10.0;

		m_width = 10.0;

		m_StrDtxPath = _T("");

		strcpy( m_name, "fountain");

		m_BoundryBox.maxPoint.x = m_Position.x + m_width / 2.0;
		m_BoundryBox.maxPoint.y = m_Position.y + m_height;
		m_BoundryBox.maxPoint.z = m_Position.z + m_width / 2.0;

		m_BoundryBox.minPoint.x = m_Position.x - m_width / 2.0;
		m_BoundryBox.minPoint.y = m_Position.y - m_height;
		m_BoundryBox.minPoint.z = m_Position.z - m_width / 2.0;

		m_numOfFaces = 2;


		m_RenderTypeInt = 1;
	}

	DynamicBillboardNode::~DynamicBillboardNode()
	{

	}

	void DynamicBillboardNode::Render()
	{

		glColor3f(1.0,1.0,1.0);

 		m_dynBillboard.GetFrameTexture(m_dynBillboard.Update());

		m_dynBillboard.draw();

	}

	BoundingBox DynamicBillboardNode::ComputeBoundBox()
	{
		m_BoundryBox.maxPoint.x = m_Position.x + m_width / 2.0;
		m_BoundryBox.maxPoint.y = m_Position.y + m_height;
		m_BoundryBox.maxPoint.z = m_Position.z + m_width / 2.0;

		m_BoundryBox.minPoint.x = m_Position.x - m_width / 2.0;
		m_BoundryBox.minPoint.y = m_Position.y;
		m_BoundryBox.minPoint.z = m_Position.z - m_width / 2.0;

		return m_BoundryBox;	
	}


	void DynamicBillboardNode::Initialize()
	{
		m_dynBillboard.setPosition( m_Position );

		m_dynBillboard.setDtxFilePath( m_StrDtxPath );

		m_dynBillboard.setWidth( m_width );
		m_dynBillboard.setHeight( m_height );

		m_dynBillboard.init();

	}



	void DynamicBillboardNode::scale( Vector3 Scale )
	{
		m_width = m_width * Scale.x;

		m_width = m_width  * Scale.z;

		m_height= m_height * Scale.y;

		m_dynBillboard.setWidth( m_width );
		m_dynBillboard.setHeight( m_height );

		ComputeBoundBox();

		notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);

	}

	void DynamicBillboardNode::translate( Vector3 offset )
	{

		m_Position.x += offset.x;

		m_Position.y += offset.y;

		m_Position.z += offset.z;
		m_dynBillboard.setPosition(m_Position);

		m_prePositon = m_Position;

		ComputeBoundBox();

		UpdatePos();

		notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);

	}

	void DynamicBillboardNode::WriteNodeToVG( CFile &fp )
	{
		long newpos;	

		//fp.Write(&m_id , sizeof(int));                 //写该节点的ID		

		Posinfile = fp.GetPosition();

		fp.Write(&nodelength, sizeof(long));

		fp.Write(&TYPE , sizeof(int));	               //写类型type

		fp.Write(m_LayerName , 20);

		fp.Write(&m_isVisible, sizeof(bool));

		fp.Write(m_name, 20);

		fp.Write(m_StrDtx_basename.c_str(), 20);
		
		fp.Write(&m_height, sizeof(float));

		fp.Write(&m_width, sizeof(float));

		fp.Write(&m_Position.x , sizeof(float));

		fp.Write(&m_Position.y, sizeof(float));

		fp.Write(&m_Position.z , sizeof(float));

		newpos = fp.GetPosition();

		nodelength = newpos - Posinfile- sizeof(long);

		fp.Seek(Posinfile, CFile::begin);

		fp.Write(&nodelength, sizeof(long));

		fp.SeekToEnd();

		// 存储DTX文件--------------------------------------------
#if 0
		String dest = vgMod::ModEffectConvertor::getProDataPath() + m_StrDtx_basename ;
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
			bool save_ret = vgKernel::SystemUtility::copyFile( m_StrDtxPath, dest);
			assert( save_ret == true );
		}

		//---------------------------------------------------------------------

	}

	unsigned long DynamicBillboardNode::PositDataToNode( char *data )
	{
		unsigned long pos = 0;

		for (int i = 0 ; i < 20; i ++)
		{
			m_LayerName[i] = *(data + pos);
			pos ++; 
		}

		m_isVisible = *(bool *)(data + pos);

		pos += sizeof(bool);

		// Name
		for (int j =0; j < 20; j++)
		{
			m_name[j] = *(data + pos);

			pos ++;
		}

		// TexturnName
		char name[20];
		for (int j =0; j < 20; j++)
		{
			name[j] = *(data + pos);

			pos ++;
		}
		m_StrDtx_basename = name;

		m_height = *(float *)(data + pos);

		pos += sizeof(float);

		m_width = *(float *)(data + pos);

		pos += sizeof(float);

		m_Position.x = *(float *)(data + pos);

		pos += sizeof(float);

		m_Position.y = *(float *)(data + pos);

		pos += sizeof(float);

		m_Position.z = *(float *)(data + pos);

		pos += sizeof(float);
		
		String strProDataPath = vgMod::ModEffectConvertor::getProDataPath();
#if 0			
		//读取dtx文件-----------------------------------
		m_StrDtxPath =
			vgMod::ModEffectConvertor::getProDataPath() + m_StrDtx_basename;
		//---------------------------------------------------
#else
		strProDataPath = vgKernel::StringUtility::getPathFromAbsoluteFilename(strProDataPath);

		String g_DataPath =  VG_EXECONF_GET_STRING( 
			VGDATA_PATHCONF,  
			VGDATA_PATHCONF_PATH_MODEFFECT);

		m_StrDtxPath = strProDataPath + g_DataPath + m_StrDtx_basename;

#endif
		Initialize();

		m_prePositon = m_Position;

		ComputeBoundBox();

		return pos;



	}
	//----------------------------------------------------------------
	void DynamicBillboardNode::UpdatePos()
	{

		m_prePositon = m_Position;

	}

	float	DynamicBillboardNode::setDistanceToViewer( const vgKernel::Vec3& viewer_pos )
	{
		// 1.首先通过包围盒计算与视点的距离.
		float delta[3];

		for ( int i = 0 ; i < 3 ; ++ i )
		{
			float _cur = viewer_pos[i];
			float _max = m_BoundryBox.maxPoint.v[i];
			float _min = m_BoundryBox.maxPoint.v[i];

			if ( _cur > _max )
			{
				delta[i] = _cur - _max;
			}
			else if ( _cur < _min )
			{
				delta[i] = _min - _cur;
			}
			else
			{
				delta[i] = 0.0f;
			}
		}

		_squaredDistanceToViewer = 
			delta[0] * delta[0] + delta[1] * delta[1] + delta[2] * delta[2];

		// 2.更新_distanceLod

		return _squaredDistanceToViewer;
	}

	std::pair<bool, float> DynamicBillboardNode::testIntersectWithTriangles( 
		const vgKernel::Ray& ray )
	{
		std::pair<bool, float> result;

		bool test_result = false;
		if (m_isVisible == false )
		{
			result.first = false;
			return result;
		}

		// 遍历

		result = vgKernel::Math::intersects( ray , getBoundingBox() );

		if( result.first == true )
		{
			test_result = true;
			goto TEST_INTERSECTION_END;
		}

#if _DEBUG
		VG_CHECK_OPENGL_ERROR();
#endif

TEST_INTERSECTION_END:
		return result;
	}


	//----------------------------------------------------------------
	vgKernel::StringVector DynamicBillboardNode::getTexNameVec()
	{
		vgKernel::StringVector texNameVec;

		for ( int i = 0; i < m_numOfMat; i++ )
		{
			string strFile = (string)(pMats[i].materialinfo.strFile);
			if ( strFile != "" )
			{
				texNameVec.push_back( strFile );
			}

			string alphaFile = (string)(pMats[i].materialinfo.alphaFile);
			if ( alphaFile != "" )
			{
				texNameVec.push_back( alphaFile );
			}
		}

		return texNameVec;
	}
}

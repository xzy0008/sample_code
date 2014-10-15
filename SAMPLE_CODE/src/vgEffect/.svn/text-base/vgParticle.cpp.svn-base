


#include <vgStableHeaders.h>
#include <vgEffect/vgParticle.h>


#include <vgConf/vgcoExeConfig.h>

#define VGDATA_PATHCONF						"DataPathConfig"
#define VGDATA_PATHCONF_TEXTURE_PATH		"TexturePath"

#define VGDATA_FILECONF						"DataFileConfig"
#define VGDATA_FILECONF_TEXTURE_NAME		"ParticleTexName"

namespace vgMod 
{
	
	//----------------------------------------------------------------
	void vgParticle::translate(Vector3 offset)		//平移
	{
		SetPosition(m_Position + offset);

		m_prePositon = m_Position;
		ComputeBoundBox();

		UpdatePos();
	}	//	translate(Vector3 offset)
	
	//----------------------------------------------------------------
	unsigned long vgParticle::PositDataToNode(char *data  )  //从文件读取
	{
		unsigned long pos = 0;
		
		//读取节点的ID	和 所属层次名
// 		m_id = *(int *)(data + pos);		
// 		pos += sizeof(int);
		for (int i = 0 ; i < 20; i ++)
		{
			m_LayerName[i] = *(data + pos);
			pos ++; 
		}

		for (int i = 0 ; i < 20; i ++)
		{
			m_name[i] = *(data + pos);
			pos ++; 
		}
		
		//读取可见性标记
		m_isVisible = *(bool *)(data + pos);
		
		pos += sizeof(bool);
		
		//读取材质名
		char name[20];						
		
		for (int j =0; j < 20; j++)
		{
			name[j] = *(data + pos);
			
			pos ++;
		}
		m_texturename = name;
		
		//读取节点中心点位置
		m_Position  = *(Vector3 *)(data + pos);	
		pos += sizeof(Vector3);
		
		
		//写粒子属性 含高度、宽度、速度、大小
		m_height = *(float *)(data + pos);	
		pos += sizeof(float);
		
		m_width = *(float *)(data + pos);	
		pos += sizeof(float);
		
		m_speed = *(float *)(data + pos);	
		pos += sizeof(float);

		m_PartLenth = *(float *)(data + pos);	
		pos += sizeof(float);

		m_PartWidth = *(float *)(data + pos);	
		pos += sizeof(float);
		
		//读取粒子数目
		m_nParticleCount = *(int *)(data + pos);	
		pos += sizeof(int);
		
		//设置参数并初始化
		//SetCenter(m_Position);
		SetCount(m_nParticleCount);

		SetHeight(m_height);
		SetWidth(m_width);
		SetSpeed(m_speed);
		SetPartLength(m_PartLenth);
		SetPartWidth( m_PartWidth);

		Initialize();
		
		m_prePositon = m_Position;	
		ComputeBoundBox();
		
		return pos;		
	}


	
	//----------------------------------------------------------------
	void vgParticle::WriteNodeToVG(CFile &fp)	//写入文件
	{
		int i;

		i = VG_PARTICLE;
		long newpos;

		//fp.Write(&m_id , sizeof(int));                 //写该节点的ID		

		Posinfile = fp.GetPosition();

		fp.Write(&nodelength, sizeof(long));			
		fp.Write(&i , sizeof(int));	                //写类型type

		//i = 2;									//写烟类型
		//fp.Write(&i, sizeof(int));
		//WriteSubTypeToVG(fp);
		fp.Write(&m_eSubType, sizeof(E_PARTICLE_TYPE) ); 


		fp.Write(m_LayerName , 20);					//层名字

		fp.Write(m_name, 20);						//节点名字

		fp.Write(&m_isVisible, sizeof(bool));			//写可见性标记

		/*	char name[20]=" ";*/			
		fp.Write(m_texturename.c_str(), 20);			//写材质名

		fp.Write(&m_Position.x , sizeof(float));		//写节点中心点位置
		fp.Write(&m_Position.y, sizeof(float));	
		fp.Write(&m_Position.z , sizeof(float));

		fp.Write(&m_height, sizeof(float));	//写粒子属性 含高度、宽度、速度、大小
		fp.Write(&m_width, sizeof(float));
		fp.Write(&m_speed, sizeof(float));
		fp.Write(&m_PartLenth, sizeof(float));
		fp.Write(&m_PartWidth, sizeof(float));

		fp.Write(&m_nParticleCount, sizeof(int));		//写粒子数目
		newpos = fp.GetPosition();

		nodelength = newpos - Posinfile- sizeof(long);

		fp.Seek(Posinfile, CFile::begin);

		fp.Write(&nodelength, sizeof(long));

		fp.SeekToEnd();
	}	//	WriteNodeToVG(CFile &fp)

	
	//----------------------------------------------------------------
	BoundingBox vgParticle::ComputeBoundBox()
	{
		// 由参数m_height、m_width、m_speed计算特效空间范围
		float	gravity =-m_speed / 1000.0f;
		float	maxVelocity= m_height/ 100.0f;
		float	maxTheta   = (m_width + 2.0f)*PI/ 180.0f;
		
		float	maxHeight = (maxVelocity*maxVelocity) 
			/ (-2.0f*gravity); // Smax = v^2 / 2*a;
		float   maxWidth  = (maxVelocity*maxVelocity*sin(maxTheta)) 
			/ (-gravity);
		
		m_BoundryBox.maxPoint.x = m_Position.x + maxWidth;
		m_BoundryBox.maxPoint.y = m_Position.y + maxHeight/2;
		m_BoundryBox.maxPoint.z = m_Position.z + maxWidth;
		
		m_BoundryBox.minPoint.x = m_Position.x - maxWidth;
		m_BoundryBox.minPoint.y = m_Position.y - maxHeight/2;
		m_BoundryBox.minPoint.z = m_Position.z - maxWidth;
		
		return m_BoundryBox;	
	}	//	ComputeBoundBox() 
	

	//----------------------------------------------------------------
	vgParticle::vgParticle()
		:_uniqueID(vgKernel::UniqueIDFactory::getUniqueID() )
		,vgMod::Node( NODE_TYPE_PARTICLE )
	{
		m_Position.x = 0.0f;
		m_Position.y = 0.0f;
		m_Position.z = 0.0f;
		pMats		 = NULL;

		m_nParticleCount = PARTICLECOUNT;
		m_bStopSE	= TRUE;
		m_bSwitchSE = FALSE;
		m_height	= 0.0f;
		m_width		= 0.0f;
		m_speed		= 0.0f;


		m_numOfFaces = 499;

		TYPE = VG_PARTICLE;

		configTextureName();
	}

	void vgParticle::configTextureName()
	{
#if 0
		String exepath = vgKernel::SystemUtility::getCurrentProcessPath();

		String texturePath =  VG_EXECONF_GET_STRING( 
			VGDATA_PATHCONF,  
			VGDATA_PATHCONF_TEXTURE_PATH);

		String textureName =  VG_EXECONF_GET_STRING( 
			VGDATA_FILECONF,  
			VGDATA_FILECONF_TEXTURE_NAME);

		texturePath = exepath + texturePath;
		m_texturename = texturePath + textureName;
#else

		m_texturename =  VG_EXECONF_GET_STRING( 
			VGDATA_FILECONF,  
			VGDATA_FILECONF_TEXTURE_NAME);

#endif
	}
	
	
	//----------------------------------------------------------------
	vgParticle::~vgParticle()	
	{
		if ( pMats )
		{
			delete pMats;
			pMats	= NULL;
		}
	}






	
	
	//--继承Renderer而来的接口-------------------------------------------
	float	vgParticle::setDistanceToViewer( const vgKernel::Vec3& viewer_pos )
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



	
	
	//----------------------------------------------------------------
	std::pair<bool, float> vgParticle::testIntersectWithTriangles( 
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

}	//	namespace vgCore


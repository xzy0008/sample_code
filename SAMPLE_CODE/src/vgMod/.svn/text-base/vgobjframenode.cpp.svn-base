#include <vgStableHeaders.h>
#include <vgMod/vgObjFrameNode.h>


#include <vgMod/vgVersionControl.h>

#include <vgMod/vgStringUtilityPlus.h>
#include <OceanCaustics/LivensonCg.h>

using namespace vgMs3d;

namespace vgMod
{

	VGK_RENDERER_IMPLEMENT( ObjFrameNode ,RENDERER_TYPE_MODOJBECT )
	ObjFrameNode::ObjFrameNode( int nVersionMod/* = VERSION_1*/)
		:ObjectNode( nVersionMod)
	{
		m_uiKeyFramesCount	= 0;
		m_pKeyFrames = NULL;

		m_startframe		= 0;
		m_endframe			= 0;

		b_loop = false/*true*/;
		m_speed = 1000.0;
		rotangel = 0;

		bFirstTime = true;
		bFirstRender = true;
		_matrix = vgKernel::Mat4::IDENTITY;

		nCurrentFrame = 0;


		b_play = true;


	}

	ObjFrameNode::~ObjFrameNode(void)
	{
		string name = this->getName();
		TRACE("Delete Mod %s \n", this->getName().c_str());
	}

	bool	ObjFrameNode::cloneFromObjectNode( ObjectNode* src_node )
	{
#if 0
		if (!src_node->confirmVBO())
		{
			return false;
		}
		// vertex mapping
		src_node->mapVertexBuffer();

		// face index mapping
		src_node->mapFaceIndex();

		m_isSelected		=src_node->m_isSelected;       
		m_isCollideCheck	=src_node->m_isCollideCheck; 
		m_isVisible			=src_node->m_isVisible;       
		m_isDeleted			=src_node->m_isDeleted;      
		m_BoundryBox		= src_node->m_BoundryBox;
		m_Pivot				= src_node->m_Pivot;
		m_prePositon		=src_node->m_prePositon;
		m_Position			=src_node->m_Position;         
		m_PreRotation		= src_node->m_PreRotation;		
		m_Rotation			= src_node->m_Rotation;        
		m_PreScale			=src_node->m_PreScale;
		m_Scale				= src_node->m_Scale;
		m_numOfMat			= src_node->m_numOfMat;
		pMats				= src_node->pMats;
		nodelength			=src_node->nodelength;	
		Posinfile			= src_node->Posinfile;
		m_numOfFaces		= src_node->m_numOfFaces;
		m_numOfVerts		= src_node->m_numOfVerts;

		// Part 3: 渲染类型
		m_RenderTypeInt = src_node->m_RenderTypeInt;

		// Part 4: 节点名称
		memcpy( m_name , src_node->m_name , 20 * sizeof( TCHAR ) );

		// Part 5: 面数
		m_numOfFaces = src_node->m_numOfFaces;	
		//////////////////////////////////////////////////////////////////////////
		m_numOfMat = src_node->m_numOfMat;

		pMats = new MaterialStruct [m_numOfMat];
		for (int	i = 0; i <m_numOfMat ; i++)
		{
			pMats[i].materialinfo =  src_node->pMats[i].materialinfo;
			try
			{
				vgCore::TextureManager &mgr = vgCore::TextureManager::getSingleton();

				string aa(pMats[i].materialinfo.strFile);

				//QuadtreeSceneManager &scenemgr = QuadtreeSceneManager::getSingleton();

				pMats[i].pTexture = mgr.getTexturePtr(aa);

			}
			catch (vgCore::Exception& e)
			{
				MessageBox( NULL , e.getFullDescription().c_str() ,"载入", MB_OK);
			}

		}
		//////////////////////////////////////////////////////////////////////////
		m_numOfVerts = src_node->m_numOfVerts;

		pVertex = new VertexElementStruct[m_numOfVerts];

		memcpy(pVertex , src_node->pVertex, sizeof(VertexElementStruct) * m_numOfVerts);
		//////////////////////////////////////////////////////////////////////////

		pMatRender = new ObjectRenderControl[m_numOfMat];
		for (int	i = 0; i < m_numOfMat ; i ++)
		{
			pMatRender[i].b_hastexture = src_node->pMatRender[i].b_hastexture;

			pMatRender[i].m_numOfFace = src_node->pMatRender[i].m_numOfFace;

			pMatRender[i].pFace = new FaceIndex[pMatRender[i].m_numOfFace];

			memcpy(pMatRender[i].pFace , src_node->pMatRender[i].pFace , sizeof(FaceIndex) * pMatRender[i].m_numOfFace);
		}

		m_numOfNoMat = src_node->m_numOfNoMat;

		pFaceNoMat = new FaceIndex[m_numOfNoMat];

		memcpy(pFaceNoMat , src_node->pFaceNoMat, sizeof(FaceIndex) * m_numOfNoMat);
		//////////////////////////////////////////////////////////////////////////

		// 三角面法线
		pNormalOfFaces = new Vector3[m_numOfFaces];	
		memcpy(pNormalOfFaces , src_node->pNormalOfFaces , 
			sizeof(Vector3) * m_numOfFaces);	
		// 实际点数目	
		m_numOfVertexs = src_node->m_numOfVertexs;	
		// 点坐标数组
		pVert = new Vector3[m_numOfVertexs];	
		memcpy(pVert , src_node->pVert , 
			sizeof(Vector3) * m_numOfVertexs);	

		// 阴影面所以结构体
		pShadowFaces = new ShadowFaceIndex[m_numOfFaces];
		memcpy(pShadowFaces , src_node->pShadowFaces , 
			sizeof(ShadowFaceIndex) * m_numOfFaces);


		//b_renderlod         = src_node->b_renderlod;

		_isReadyForVBORender = false;
#else
		ObjectNode::cloneFromObjectNode(src_node);
#endif
		//////////////////////////////////////////////////////////////////////////
		ObjFrameNode* src_framenode = dynamic_cast<ObjFrameNode*>(src_node);
		
		m_uiKeyFramesCount = src_framenode->m_uiKeyFramesCount;
		m_pKeyFrames = new ModKeyFrame[m_uiKeyFramesCount];
		memcpy( m_pKeyFrames, src_framenode->m_pKeyFrames, sizeof(ModKeyFrame) * m_uiKeyFramesCount);

		m_startframe = src_framenode->m_startframe;
		m_endframe = src_framenode->m_endframe;
		b_play = src_framenode->b_play;
		b_loop = src_framenode->b_loop;
		m_mergeBox = src_framenode->m_mergeBox;
		

		return true;
	}


	//	Part 4 :重载基类的纯虚函数
	void	ObjFrameNode::prepareMatrix()
	{
		//b_loop = true;
		glMatrixMode( GL_MODELVIEW );

		if (m_bUnderWater)
		{
			double modelviewmat[16];
			glGetDoublev( GL_MODELVIEW_MATRIX, modelviewmat );
			cgSetMatrixParameterdr(cgGetNamedParameter(VR_Ocean::CLivensonCg::getSingleton().myCgVertexProgram,"ViewMatrix"),(const double*)modelviewmat);

			glLoadIdentity();
			VR_Ocean::CLivensonCg::getSingleton().Begin();
		}
		if (m_uiKeyFramesCount == 0)
		{
			memcpy( &m_mergeBox._maxVertex,  &m_BoundryBox.maxPoint, sizeof(float)*3);
			memcpy( &m_mergeBox._minVertex,  &m_BoundryBox.minPoint, sizeof(float)*3);
			return;
		}

		if(	b_play == true)
		{
			if(bFirstTime)
			{//修改的部分
				fStartTime = getTimeWithFrame( m_startframe );
				fEndTime = getTimeWithFrame( m_endframe );
				fLastTime= fStartTime;
				m_Timer.Init();
				m_Timer.GetSeconds() ;
				bFirstTime = false;

				bFirstRender = true;
				/*if ( m_mergeBox._maxVertex != vgKernel::Vec3() )
				{
					bFirstRender = false;
				}*/
				memcpy( &m_mergeBox._maxVertex,  &m_BoundryBox.maxPoint, sizeof(float)*3);
				memcpy( &m_mergeBox._minVertex,  &m_BoundryBox.minPoint, sizeof(float)*3);

			}
			//	static float fLastTime= fStartTime;// 

			//	float 
			fTime = m_Timer.GetSeconds() * m_speed;//帧时间
			fTime += fLastTime;
			fLastTime = fTime;
	

			//looping
			if(fTime >= fEndTime)
			{
				if(b_loop)
				{
					//			Reset();
					m_Timer.Init();
					m_Timer.GetSeconds();
					fLastTime = fStartTime;
					fTime = fStartTime;
				}
				else
					fTime = fEndTime;
				bFirstRender = false;
			}	

			//Current frame]
			unsigned int uiFrame = 0;//当前帧序列
			//if there are no keyframes, don't do any transformations

			//Calculate the current frame
			while(uiFrame < m_uiKeyFramesCount && m_pKeyFrames[uiFrame].m_fTime < fTime)
				uiFrame++;

			nCurrentFrame = uiFrame;
				
		}//if(m_uiKeyFramesCount!=0 &&b_play == true)
		else //if(b_play == false)
		{
			memcpy( &m_mergeBox._maxVertex,  &m_BoundryBox.maxPoint, sizeof(float)*3);
			memcpy( &m_mergeBox._minVertex,  &m_BoundryBox.minPoint, sizeof(float)*3);
		}


		updateMatrix();
		

	}//prepareForRender


	
	long	ObjFrameNode::readExtraData(char	*pBytes)
	{
		long	posRelative	= 0;

		if( m_nVersionMod < VERSION_MOD(2008,6) )
		{
			memcpy( &m_mergeBox._maxVertex,  &m_BoundryBox.maxPoint, sizeof(float)*3);
			memcpy( &m_mergeBox._minVertex,  &m_BoundryBox.minPoint, sizeof(float)*3);
		}
		else
		{
			posRelative	+= readKeyFrames(pBytes+posRelative);
		}

		String	vgVersion = VersionControl::getVgVersionRead();
		//vgGlobal::GlobalFacade::getSingleton().getVgVersionRead();
		if( !m_bReadMod && vgVersion >= String("VRGIS.VERSION 2.13") )
		{
			posRelative	+= readUniqueID(pBytes+posRelative);
		}

		//	双面渲染标记
		if ( posRelative < nodelength)
		{
			posRelative	+= readRenderDoubleSidesState(pBytes+posRelative);
		}

		if ( posRelative < nodelength)
		{
			//	是否触发器
			posRelative	+= readTriggerState(pBytes+posRelative);

			//	触发信息
			posRelative	+= readTriggerInfo(pBytes+posRelative);
		}

		if ( posRelative < nodelength )
		{
			posRelative += readColorProperty(pBytes+posRelative);
		}

		if (posRelative < nodelength )
		{
			posRelative += readCollisionProperty(pBytes + posRelative);
		}

		//for ocean property read
		if (posRelative < nodelength )
		{
			this->m_bUnderWater=*(bool*)(pBytes+posRelative);
			posRelative+=sizeof(bool);
		}

		if( !m_bReadMod && vgVersion >= String("VRGIS.VERSION 2.20") )
		{
			posRelative	+= readTimelineProperty(pBytes+posRelative);
		}

		return	posRelative;
	}
#if 0
	void	ObjFrameNode::readExtraDataFromVG(CFile &fp)
	{
		readKeyFrames(fp);
		
		String	vgVersion  = VersionControl::getVgVersionRead();
		//vgGlobal::GlobalFacade::getSingleton().getVgVersionRead();//getVgVersionString();
		if( vgVersion >= String("VRGIS.VERSION 2.13") )
		{
			readUniqueID(fp);
		}

		//	双面渲染标记
		//readRenderDoubleSidesState(fp);
	}
#endif
	void	ObjFrameNode::writeExtraDataToVG(CFile &fp)
	{
		writeKeyFramesToVG(fp);

		String	vgVersion  = VersionControl::getVgVersionWrite();
		// vgGlobal::GlobalFacade::getSingleton().getVgVersionString();
		if( vgVersion >= String("VRGIS.VERSION 2.13") )
		{
			writeUniqueID(fp);
		}

		//	双面渲染标记
		writeRenderDoubleSidesState(fp);

		//	是否触发器
		writeTriggerState(fp);

		//	触发信息
		writeTriggerInfo(fp);

		//  颜色属性信息
		writeColorProperty(fp);
		
		//  碰撞检测信息
		writeCollisionProperty(fp);
		
		//Ocean property
		writeOceanProperty(fp);

		//时间轴属性
		writeTimelineProperty(fp);

	}

	
	//	Part 7 :新增其它函数
	float	ObjFrameNode::getTimeWithFrame( int m_frame )
	{
		return (float)m_pKeyFrames[m_frame].m_fTime;
	}

	void	ObjFrameNode::setup()
	{
		if( hasKeyFrame() )
		{
			ModKeyFrame * pkCur = &m_pKeyFrames[0];

			m_pos0 = pkCur->key_translate;

			m_endframe	= m_uiKeyFramesCount - 1;
				//chunyongma
			//_rendererType = vgMod::RENDERER_TYPE_KEYFRAME;

			if( OBJ_BAKED+OBJ_KEYFRAME == TYPE )
			{
				TYPE = VG_OBJECT_BAKED_KEY;
			}
			else if( OBJ_BAKED == TYPE )
			{
				TYPE = VG_OBJECT_BAKED;
			}
			else
			{
				TYPE = VG_OBJECT_KEYFRAME;
			}
		}
	}


	
	long	ObjFrameNode::readKeyFrames(char	*pBytes)
	{
		long	posRelative	= 0;

		m_uiKeyFramesCount = *(int *)(pBytes + posRelative);
		posRelative += sizeof(int);

		// 测试用 临时添加
		//m_uiKeyFramesCount = 0;

		m_pKeyFrames = new ModKeyFrame[m_uiKeyFramesCount];

		memcpy(m_pKeyFrames , pBytes+posRelative , sizeof(ModKeyFrame) * m_uiKeyFramesCount);
		posRelative += sizeof(ModKeyFrame) * m_uiKeyFramesCount;

//////////////////////////////////////////////////////////////////////////chunyongma

		setup();
		//?????????????????????????????????????
		if( !m_bReadMod )
		{
			m_startframe = *(int *)(pBytes + posRelative);
			posRelative += sizeof(int);

			m_endframe = *(int *)(pBytes + posRelative);
			posRelative += sizeof(int);

			b_play = *(bool *)(pBytes + posRelative);
			posRelative += sizeof(bool);

			b_loop = *(bool *)(pBytes + posRelative);
			posRelative += sizeof(bool);

			String	vgVersion  = VersionControl::getVgVersionRead();
			// vgGlobal::GlobalFacade::getSingleton().getVgVersionRead();
			if( vgVersion >= String("VRGIS.VERSION 2.1") )
			{
				m_mergeBox = *(vgKernel::Box *)(pBytes + posRelative);
				posRelative += sizeof(vgKernel::Box);
			}
		}
		return	posRelative;
	}
	
	void	ObjFrameNode::readKeyFrames(CFile &fp)
	{
		fp.Read(&m_uiKeyFramesCount, sizeof(int));
		m_pKeyFrames = new ModKeyFrame[m_uiKeyFramesCount];
		fp.Read(m_pKeyFrames, sizeof(ModKeyFrame)* m_uiKeyFramesCount);

		fp.Read(&m_startframe, sizeof(int) );
		fp.Read(&m_endframe , sizeof(int) );
		fp.Read(&b_play, sizeof(bool) );
		fp.Read(&b_loop, sizeof(bool) );

		String	vgVersion  = VersionControl::getVgVersionRead();
		// vgGlobal::GlobalFacade::getSingleton().getVgVersionRead();
		if( vgVersion >= String("VRGIS.VERSION 2.1") )
		{
			fp.Read(&m_mergeBox, sizeof(vgKernel::Box));
		}

		setup();
	}


	void	ObjFrameNode::writeKeyFramesToVG(CFile &fp)
	{
		fp.Write(&m_uiKeyFramesCount, sizeof(unsigned int));
		fp.Write(m_pKeyFrames , sizeof(ModKeyFrame) * m_uiKeyFramesCount);
	//////////////////////////////////////////////////////////////////////////
		//chunyongma
		fp.Write(&m_startframe, sizeof(int) );
		fp.Write(&m_endframe , sizeof(int) );
		fp.Write(&b_play, sizeof(bool) );
		fp.Write(&b_loop, sizeof(bool) );

		String	vgVersion  = VersionControl::getVgVersionWrite();
		// vgGlobal::GlobalFacade::getSingleton().getVgVersionString();
		if( vgVersion >= String("VRGIS.VERSION 2.1") )
		{
			fp.Write(&m_mergeBox, sizeof(vgKernel::Box));
		}
	}

	long	ObjFrameNode::readUniqueID(char	*pBytes)
	{
		long	posRelative	= 0;

		//_uniqueID = *(vgKernel::UniqueID *)(pBytes + posRelative);
		
		unsigned long _id1, _id2;
		_id1 = *(unsigned long *)(pBytes + posRelative);
		posRelative += sizeof(unsigned long);
		
		_id2 = *(unsigned long *)(pBytes + posRelative);
		posRelative += sizeof(unsigned long);

		_uniqueID._id1 = _id1;
		_uniqueID._id2 = _id2;

		return	posRelative;

	}
	void	ObjFrameNode::readUniqueID(CFile &fp)
	{
		fp.Read(&_uniqueID, sizeof(vgKernel::UniqueID) );
	}
	void	ObjFrameNode::writeUniqueID(CFile &fp)
	{
		fp.Write(&_uniqueID._id1, sizeof(unsigned long) );
		fp.Write(&_uniqueID._id2, sizeof(unsigned long) );
	}

//////////////////////////////////////////////////////////////////////////chunyongma
	void	ObjFrameNode::translate( Vector3 offset )
	{
		ObjectNode::translate( offset );

		for (int i = 0; i < m_uiKeyFramesCount; i++)
		{
			m_pKeyFrames[i].key_translate += offset;
		}

		// 平移
		vgKernel::Mat4 tran;
		vgKernel::Math::createTranslationMatrix(offset.x, offset.y, offset.z, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, _matrix);
		
		m_mergeBox.matrixTranslation(tran);

		setup();

		notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);
	}
	
	void	ObjFrameNode::startPlayingByTime(float fAnytime/* = 0.0f*/)
	{// unit:ms
		fLastTime= fAnytime;
		m_Timer.Init();
		m_Timer.GetSeconds() ;
	}
	void	ObjFrameNode::startPlayingByFrame(long uiAnyFrame)
	{
		float	fAnyTime = getTimeWithFrame(uiAnyFrame);
		startPlayingByTime(fAnyTime);
	}

	void	ObjFrameNode::pausePlaying()
	{
		b_play = false;
	}

	void	ObjFrameNode::continuePlaying()
	{
		b_play = true;
		startPlayingByFrame(nCurrentFrame);
	}

	void	ObjFrameNode::updateMatrix()
	{
		CMatrix4X4 matTmp;
		//unsigned int uiFrame = 0;//当前帧序列

		Vector3 fTranslation;
		Vector3 fScale;
		float*	pRotate;

		float fDeltaT = 1;
		float fInterp = 0;
		//If its at the extremes

		if(nCurrentFrame == 0)
		{
			fTranslation = m_pKeyFrames[0].key_translate;
			pRotate = m_pKeyFrames[0].key_rotate;

			{
				//Create a rotation quaternion for each frame
				CQuaternion qCur;
				CVector3 aa(m_pKeyFrames[0].key_rotate[0],m_pKeyFrames[0].key_rotate[1],
					m_pKeyFrames[0].key_rotate[2]);

				qCur.FromAxisAngle(aa, m_pKeyFrames[0].key_rotate[3]*(-1) );

				//Convert the quaternion to a rotation matrix
				matTmp = qCur.ToMatrix4();
			}


			fScale = m_pKeyFrames[0].key_scale;
		}
		else if(nCurrentFrame == m_uiKeyFramesCount)
		{
			fTranslation = m_pKeyFrames[nCurrentFrame - 1].key_translate;

			pRotate = m_pKeyFrames[0].key_rotate  ;

			{
				//Create a rotation quaternion for each frame
				CQuaternion qCur;
				CVector3 aa(m_pKeyFrames[nCurrentFrame - 1].key_rotate[0],m_pKeyFrames[nCurrentFrame - 1].key_rotate[1],
					m_pKeyFrames[nCurrentFrame - 1].key_rotate[2]);

				qCur.FromAxisAngle(aa, m_pKeyFrames[nCurrentFrame - 1].key_rotate[3]*(-1) );

				//Convert the quaternion to a rotation matrix
				matTmp = qCur.ToMatrix4();
			}


			fScale = m_pKeyFrames[nCurrentFrame - 1].key_scale;
		}
		//If its in the middle of two frames
		else
		{
			ModKeyFrame * pkCur = &m_pKeyFrames[nCurrentFrame];
			ModKeyFrame * pkPrev = &m_pKeyFrames[nCurrentFrame-1];
			fDeltaT = pkCur->m_fTime - pkPrev->m_fTime;
			fInterp = (fTime - pkPrev->m_fTime) / fDeltaT;

			{
				fTranslation = pkPrev->key_translate 
					+ (pkCur->key_translate - pkPrev->key_translate) * fInterp;

				pRotate = pkCur->key_rotate;
			}
			{
				//Create a rotation quaternion for each frame
				CQuaternion qCur;
				CVector3 aa(pkCur->key_rotate[0],pkCur->key_rotate[1],
					pkCur->key_rotate[2]);

				CQuaternion qPrev;
				CVector3 bb(pkPrev->key_rotate[0],pkPrev->key_rotate[1],
					pkPrev->key_rotate[2]);
				qCur.FromAxisAngle(aa, pkCur->key_rotate[3] * (-1) );
				qPrev.FromAxisAngle(bb, pkPrev->key_rotate[3] * (-1));
				// 						//SLERP between the two frames
				CQuaternion qFinal = SLERP(qPrev, qCur, fInterp);

				matTmp = qFinal.ToMatrix4();

			}
			{
				fScale = pkPrev->key_scale 
					+ (pkCur->key_scale - pkPrev->key_scale) * fInterp;
			}
		}

		////////////////////////////矩阵变换//////////////////////////////////////////////

		glTranslatef( fTranslation.x, fTranslation.y, fTranslation.z);

		glMultMatrixf( matTmp.Get() );

		//glRotated(
		//	pRotate[3]*(180.0/3.14),
		//	pRotate[0],
		//	pRotate[1],
		//	pRotate[2]);

		glScalef(fScale.x, fScale.y, fScale.z);

		glScalef(1.0/m_pKeyFrames[0].key_scale.x,1.0/m_pKeyFrames[0].key_scale.y,1.0/m_pKeyFrames[0].key_scale.z);


		{
			CQuaternion qCur;
			CVector3 aa(			m_pKeyFrames[0].key_rotate[0],
				m_pKeyFrames[0].key_rotate[1],
				m_pKeyFrames[0].key_rotate[2]);

			qCur.FromAxisAngle(aa, m_pKeyFrames[0].key_rotate[3] );

			matTmp = qCur.ToMatrix4();

			glMultMatrixf( matTmp.Get() );
		}


		//glRotated(m_pKeyFrames[0].key_rotate[3]*(180.0/3.14),
		//	m_pKeyFrames[0].key_rotate[0],
		//	m_pKeyFrames[0].key_rotate[1],
		//	m_pKeyFrames[0].key_rotate[2]);

		glTranslatef(-m_pos0.x, -m_pos0.y, -m_pos0.z);

		//////////////////////////////////////////////////////////////////////////包围盒变换
		//if (bFirstRender)
		{
			memcpy( &_staticBox._maxVertex,  &m_BoundryBox.maxPoint, sizeof(float)*3);
			memcpy( &_staticBox._minVertex,  &m_BoundryBox.minPoint, sizeof(float)*3);

			vgKernel::Mat4 tran;
			vgKernel::Mat4 tmp = vgKernel::Mat4::IDENTITY;

			// 平移复位
			vgKernel::Math::createTranslationMatrix(-m_pos0.x, -m_pos0.y, -m_pos0.z, tran);
			vgKernel::Math::multiplyMatrix(tran, tmp, tmp);
			
#if 1			
			// 旋转复位
			vgKernel::Math::createRotationMatrix(
				m_pKeyFrames[0].key_rotate[3]/**(180.0/3.14)*/,
				m_pKeyFrames[0].key_rotate[0],
				m_pKeyFrames[0].key_rotate[1],
				m_pKeyFrames[0].key_rotate[2], tran);
			vgKernel::Math::multiplyMatrix(tran, tmp, tmp);
	

			// 缩放复位
			vgKernel::Math::createScaleMatrix(
				1.0/m_pKeyFrames[0].key_scale.x,
				1.0/m_pKeyFrames[0].key_scale.y,
				1.0/m_pKeyFrames[0].key_scale.z, tran);
			vgKernel::Math::multiplyMatrix(tran, tmp, tmp);

			// 缩放
			vgKernel::Math::createScaleMatrix(fScale.x, fScale.y, fScale.z, tran);
			vgKernel::Math::multiplyMatrix(tran, tmp, tmp);


			// 旋转
			vgKernel::Math::createRotationMatrix(-pRotate[3]/**(180.0/3.14)*/, 
				pRotate[0], pRotate[1], pRotate[2], tran);
			vgKernel::Math::multiplyMatrix(tran, tmp, tmp);
#endif						
			
			// 平移
			vgKernel::Math::createTranslationMatrix(fTranslation.x, fTranslation.y, fTranslation.z, tran);
			vgKernel::Math::multiplyMatrix(tran, tmp, tmp);
					

			_dynamicBox = _staticBox;
			_dynamicBox.matrixTranslation(tmp);
			m_mergeBox.merge(_dynamicBox);

			/*if (bFirstTime)
			{
			m_mergeBox.matrixTranslation(_matrix);
			}*/

		}//if (bFirstRender)
	}

	
	long	ObjFrameNode::readRenderDoubleSidesState( char *pBytes )
	{
		long	posRelative	= 0;
		
		_bRenderDoubleSides = *(bool *)(pBytes + posRelative);
		posRelative += sizeof(bool);
		
		return	posRelative;
	}

	void	ObjFrameNode::readRenderDoubleSidesState( CFile &fp )
	{
		fp.Read(&_bRenderDoubleSides, sizeof(bool) );
	}

	void	ObjFrameNode::writeRenderDoubleSidesState( CFile &fp )
	{
		fp.Write(&_bRenderDoubleSides, sizeof(bool) );
	}

	void ObjFrameNode::prepareExtra()
	{
		if (_bRenderDoubleSides)
		{
			glDisable(GL_CULL_FACE);
		} 
		else
		{
			glEnable(GL_CULL_FACE);
		}
	}

	void ObjFrameNode::initializeTrigger()
	{
		setAsTrigger(false);
		setTriggerInfo(getName());
	}

	void ObjFrameNode::initializeColor()
	{
		setColorableValue( m_ColorProperty.m_rgbaColor ); 
	}

	void ObjFrameNode::initializeExtra()
	{
		initializeTrigger();
		initializeColor();
	}

	long	ObjFrameNode::readTriggerState(char	*pBytes)
	{
		long	posRelative	= 0;

		_bSetAsTrigger = *(bool *)(pBytes + posRelative);
		posRelative += sizeof(bool);

		return	posRelative;
	}
	void	ObjFrameNode::readTriggerState(CFile &fp)
	{
		fp.Read(&_bSetAsTrigger, sizeof(bool) );

	}
	void	ObjFrameNode::writeTriggerState(CFile &fp)
	{
		fp.Write(&_bSetAsTrigger, sizeof(bool) );

	}

	long	ObjFrameNode::readTriggerInfo(char	*pBytes)
	{
		return vgMod::StringUtilityPlus::readString(_strTriggerInfo,pBytes);
	}
	void	ObjFrameNode::readTriggerInfo(CFile &fp)
	{
		vgMod::StringUtilityPlus::readString(_strTriggerInfo,&fp);
	}
	void	ObjFrameNode::writeTriggerInfo(CFile &fp)
	{
		vgMod::StringUtilityPlus::writeString(_strTriggerInfo,&fp);
	}

	void ObjFrameNode::resetExtra()
	{
		if (m_bUnderWater)
		{
			VR_Ocean::CLivensonCg::getSingleton().End();
		}
		if (!_bRenderDoubleSides)
		{
			glDisable(GL_CULL_FACE);
		}
	}

	void ObjFrameNode::writeColorProperty( CFile &fp )
	{
		m_ColorProperty.m_rgbaColor = *getRgbaQuadRef();
		fp.Write(&m_ColorProperty, sizeof(ColorProperty));
	}

	void ObjFrameNode::readColorProperty( CFile &fp )
	{
		fp.Read(&m_ColorProperty, sizeof(ColorProperty));
	}

	long ObjFrameNode::readColorProperty( char *pBytes )
	{
		long	posRelative	= 0;

		m_ColorProperty = *(ColorProperty*)(pBytes + posRelative);
		posRelative += sizeof(ColorProperty);

		return	posRelative;
	}

	long ObjFrameNode::readCollisionProperty( char *pBtyes )
	{
		long posRelative = 0;

		m_enableCollision = *(bool*)(pBtyes + posRelative);

		posRelative += sizeof(bool);

		return posRelative;
	}

	void ObjFrameNode::writeCollisionProperty(CFile &fp)
	{
		// 碰撞检测
		fp.Write(&m_enableCollision, sizeof(bool));
	}

	void ObjFrameNode::writeOceanProperty(CFile& fp)
	{
		fp.Write( &m_bUnderWater, sizeof(bool));
	}

	long ObjFrameNode::readTimelineProperty(char *pBytes)
	{
		long	posRelative	= 0;

		m_startTime = *(int*)(pBytes + posRelative);
		posRelative += sizeof(int);

		m_endTime = *(int*)(pBytes + posRelative);
		posRelative += sizeof(int);

		return	posRelative;
	}

	void ObjFrameNode::readTimelineProperty(CFile &fp)
	{
		fp.Read(&m_startTime, sizeof(int));
		fp.Read(&m_endTime, sizeof(int));
	}

	void ObjFrameNode::writeTimelineProperty(CFile &fp)
	{
		fp.Write(&m_startTime, sizeof(int));
		fp.Write(&m_endTime, sizeof(int));
	}

}

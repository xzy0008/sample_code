#include <vgStableHeaders.h>
#include <vgms3d/ms3d.h>
#include <OceanCaustics/LivensonCg.h>

using namespace vgMath;
namespace vgMs3d 
{

	VGK_RENDERER_IMPLEMENT( CMs3d,RENDERER_TYPE_MS3D )


		//-------------------------------------------------------------
		//- Load
		//- Loads an MS3D file into memory
		//-------------------------------------------------------------
		//	static float fLastTime;
		//	static CTimer m_Timer;
		bool CMs3d::Load(const char * szFilename)
	{
		int x;
		unsigned int sizeCnt = 0;

		//初始化！！！
		bFirstTime=TRUE;
		m_load=FALSE;
		m_fAngle=0;
		loadfilename=szFilename;

		m_ms3dFileName  = vgKernel::StringUtility::getFilenameFromAbsolutePath(loadfilename);
		if (_meshName.empty())
		{
			_meshName = vgKernel::StringUtility::getFilenameWithoutExtension(m_ms3dFileName);
		}

		//_matrix= vgKernel::Mat4::IDENTITY;

		m_fTotalTime=0;
		//strcpy(m_name,""); 
		m_name[200]= 0;//
		// 	m_bDrawBones=TRUE;
		// 	m_bDrawMesh=TRUE;
		unsigned char * ucpBuffer = 0;
		unsigned char * ucpPtr = 0;

		//Open the file
		FILE * f = fopen(szFilename, "rb");
		if(!f)
		{
			//APP->Log(COLOR_RED, "Could not open %s", szFilename);
			return false;
		}



		//Get file size
		fseek(f, 0, SEEK_END);
		int iEnd = ftell(f);
		fseek(f, 0, SEEK_SET);
		int iStart = ftell(f);
		unsigned int uiSize = iEnd - iStart;
		//Allocate memory
		TRACE("UISIZE ALLOCATE %d \n", uiSize);
		ucpBuffer = new unsigned char[uiSize];

		sizeCnt += uiSize;

		ucpPtr = ucpBuffer;
		if(!ucpBuffer)
		{
			//APP->Log(COLOR_RED, "Could not allocate memory");
			return false;
		}
		//Read file into buffer
		if(fread(ucpBuffer, 1, uiSize, f) != uiSize)
		{
			//APP->Log(COLOR_RED, "Could not read %s", szFilename);
			delete [] ucpBuffer;
			return false;
		}

		//Check out the header, it should be 10 bytes, MS3D000000
		if(memcmp(ucpPtr, "MS3D000000", 10) != 0)
		{
			//APP->Log(COLOR_RED, "%s is not a valid Milkshape 3D file", szFilename);
			delete [] ucpBuffer;
			return false;
		}
		//Check the version (should be 3 or 4)
		ucpPtr += 10;
		if(*(int *)ucpPtr != 3 && *(int *)ucpPtr != 4)
		{
			//APP->Log(COLOR_RED, "%s is the wrong version, should be 3 or 4", szFilename);
			delete [] ucpBuffer;
			return false;
		}
		ucpPtr += 4;

		//Read the vertices
		//Number of vertices
		m_usNumVerts = *(unsigned short *)ucpPtr;//从指针所指地址处取数值
		ucpPtr += 2;
		//Allocate memory
		m_pVertices = new SMs3dVertex[m_usNumVerts];

		sizeCnt += sizeof(SMs3dVertex) * m_usNumVerts;

		//Copy the vertices
		memcpy(m_pVertices, ucpPtr, m_usNumVerts * sizeof(SMs3dVertex));
		ucpPtr += m_usNumVerts * sizeof(SMs3dVertex);

		int ddd = sizeof(SMs3dVertex);

		//Read the triangles
		m_usNumTriangles = *(unsigned short *)ucpPtr;
		ucpPtr += 2;
		//Alloc memory for triangles
		m_pTriangles = new SMs3dTriangle[m_usNumTriangles];

		sizeCnt += sizeof(SMs3dTriangle) * m_usNumVerts;

		//Copy triangles
		memcpy(m_pTriangles, ucpPtr, m_usNumTriangles * sizeof(SMs3dTriangle));
		ucpPtr += m_usNumTriangles * sizeof(SMs3dTriangle);

		//Load mesh groups
		m_usNumMeshes = *(unsigned short *)ucpPtr;
		ucpPtr += 2;
		//Alloc memory for the mesh data
		m_pMeshes = new SMs3dMesh[m_usNumMeshes];

		sizeCnt += sizeof(SMs3dMesh) * m_usNumVerts;

		//Copy the mesh data
		for(x = 0; x < m_usNumMeshes; x++)
		{
			//Copy the first part of the data
			memcpy(&m_pMeshes[x], ucpPtr, 35);
			ucpPtr += 35;
			//Allocate triangle index memory
			m_pMeshes[x].m_uspIndices = new unsigned short[m_pMeshes[x].m_usNumTris];

			sizeCnt += sizeof(short) * m_pMeshes[x].m_usNumTris;

			//Copy triangle index data, plus the material index
			memcpy(m_pMeshes[x].m_uspIndices, ucpPtr, m_pMeshes[x].m_usNumTris * 2);
			ucpPtr += m_pMeshes[x].m_usNumTris * 2;
			m_pMeshes[x].m_cMaterial = ucpPtr[0];
			ucpPtr ++;
		}

		//Read material information
		m_usNumMaterials = *(unsigned short *)ucpPtr;
		ucpPtr += 2;
		//Alloc memory
		m_pMaterials = new SMs3dMaterial[m_usNumMaterials];

		sizeCnt += sizeof(SMs3dMaterial) * m_usNumMaterials;

		bool missingTexture = false;
		//Copy material information
		for(x = 0; x < m_usNumMaterials; x++)
		{
			memcpy(&m_pMaterials[x], ucpPtr, 361);
			ucpPtr += 361;
			//Load the images
			if(m_pMaterials[x].m_cTexture[0] != '\0')
			{
				std::string aa(loadfilename);
				std::string::size_type p1 = aa.find_last_of("\\");

				if (p1 == string::npos)
				{
					return false;
				}

				std::string s1 = aa.substr(0,p1+1);

				std::string s2(m_pMaterials[x].m_cTexture );

				std::string s3 = s2.substr(0, string::npos);

				s1 = s1 + s3;

				// m_pMaterials[x].m_Texture.Load((char *)s1.c_str());

				// modified by zsc.
				string fn = s1.substr( s1.find_last_of("\\/") + 1, std::string::npos);
				//String _filename = fn.substr(0, _filename.find_last_of("."));

				String metaname = 
					vgKernel::StringUtility::getFilenameWithoutExtension( fn );
				String ext = 
					vgKernel::StringUtility::getFileExtension( fn );
				String _filename = metaname;
				_filename += "_";
				_filename += ext;

				_filename += ".dds";

				vgKernel::StringUtility::toLowerCase(_filename);

				m_pMaterials[x].m_Texture = 
					vgImage::TextureManager::getSingleton().getTextureObserver(_filename.c_str() , VGLOD_CLEAR );

				if (m_pMaterials[x].m_Texture != NULL)
				{
					m_pMaterials[x].m_Texture->addRef();
				}
				else
				{
					missingTexture = true;
				}
			}
		}

		if (missingTexture)
		{
			AfxMessageBox("骨骼动画缺失纹理贴图，请检查是否已载入vgi纹理文件.");
			return false;
		}

		//Skip some data we do not need
		ucpPtr += 4;
		ucpPtr += 8;

		//Read in joint and animation info
		m_usNumJoints = *(unsigned short *)ucpPtr;
		ucpPtr += 2;
		//Allocate memory
		m_pJoints = new SMs3dJoint[m_usNumJoints];

		sizeCnt += sizeof(SMs3dJoint) * m_usNumJoints;

		//Read in joint info
		for(x = 0; x < m_usNumJoints; x++)
		{

			memcpy(&m_pJoints[x], ucpPtr, 93);//骨骼信息
			ucpPtr += 93;
			//Allocate memory 
			m_pJoints[x].m_RotKeyFrames = new SMs3dKeyFrame[m_pJoints[x].m_usNumRotFrames];

			sizeCnt += sizeof(SMs3dKeyFrame) * m_pJoints[x].m_usNumRotFrames;

			m_pJoints[x].m_TransKeyFrames = new SMs3dKeyFrame[m_pJoints[x].m_usNumTransFrames];

			sizeCnt += sizeof(SMs3dKeyFrame) * m_pJoints[x].m_usNumTransFrames;

			//copy keyframe information
			memcpy(m_pJoints[x].m_RotKeyFrames, ucpPtr, m_pJoints[x].m_usNumRotFrames * sizeof(SMs3dKeyFrame));
			ucpPtr += m_pJoints[x].m_usNumRotFrames * sizeof(SMs3dKeyFrame);
			memcpy(m_pJoints[x].m_TransKeyFrames, ucpPtr, m_pJoints[x].m_usNumTransFrames * sizeof(SMs3dKeyFrame));
			ucpPtr += m_pJoints[x].m_usNumTransFrames * sizeof(SMs3dKeyFrame);

		}

		sizeCnt ++;
		//Find the parent joint array indices
		for(x = 0; x < m_usNumJoints; x++)
		{
			//If the bone has a parent
			if(m_pJoints[x].m_cParent[0] != '\0')
			{
				//Compare names of theparent bone of x with the names of all bones
				for(int y = 0; y < m_usNumJoints; y++)
				{
					//A match has been found
					if(strcmp(m_pJoints[y].m_cName, m_pJoints[x].m_cParent) == 0)
					{
						m_pJoints[x].m_sParent = y;
					}
				}
			}
			//The bone has no parent
			else
			{
				m_pJoints[x].m_sParent = -1;
			}
		}


		//计算m_fTotalTime的数值
		float temp;
		for(int x = 0; x < m_usNumJoints; x++)
		{
			//Current joint
			SMs3dJoint * pJoint = &m_pJoints[x];
			temp=pJoint->m_TransKeyFrames[pJoint->m_usNumTransFrames-1].m_fTime;
			if(m_fTotalTime<temp)m_fTotalTime=temp;
			temp=pJoint->m_RotKeyFrames[pJoint->m_usNumRotFrames-1].m_fTime;
			if(m_fTotalTime<temp)m_fTotalTime=temp;
		}
		m_startframe = 0;
		m_endframe = m_fTotalTime;
		//拿出一个点作为包围盒的初始值
		/*_staticBox._maxVertex.x = _staticBox._minVertex.x = m_pVertices->m_vVert[0];

		_staticBox._maxVertex.y = _staticBox._minVertex.y = m_pVertices->m_vVert[1];

		_staticBox._maxVertex.z = _staticBox._minVertex.z = m_pVertices->m_vVert[2];*/

		_dynamicBox.matrixTranslation(_matrix);
		notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);

		//File loaded
		delete [] ucpBuffer;

		fclose( f );

		//APP->Log(COLOR_GREEN, "MS3D File: %s Loaded", szFilename);
		return true;
	}

	//-------------------------------------------------------------
	//- Render
	//- Renders the model in its position at time 0
	//-------------------------------------------------------------
	void CMs3d::Render()
	{
		//Note: This function really isn't needed, as it preforms the same basic function
		//      as the render function below.  It is included to provide an implementation of the
		//      Render() function put forth in the CModel class.
		// 	SetCurrentDirectoryA(loadfilename);

		glColor3f (1.0, 1.0, 1.0); //默认绘制白色，避免因没有指定颜色，带来其他颜色的影响

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		if (bUnderWater)
		{
			double modelviewmat[16];
			glGetDoublev( GL_MODELVIEW_MATRIX, modelviewmat );
			cgSetMatrixParameterdr(cgGetNamedParameter(VR_Ocean::CLivensonCg::getSingleton().myCgVertexProgram,"ViewMatrix"),(const double*)modelviewmat);
			glLoadIdentity();
			VR_Ocean::CLivensonCg::getSingleton().Begin();
			float Speed=0.1;
			float Xtran,Ztran;
			float DelTheta=0.2;
		
			if (!GetSelected())
			{
				m_ThetaX+=DelTheta;
				if (m_ThetaX>=360.0)
				{
					m_ThetaX=0.0f;
				}
				Xtran=Speed*cos(m_ThetaX*PI/180.0);
				Ztran=Speed*sin(m_ThetaX*PI/180.0);
				translate(Vector3(Xtran,0,Ztran));
				rotateSelf(-DelTheta,0,1,0);
			}
			setSelected(false);
		}
		glMultMatrixf(_matrix._m);
		
		if (m_endframe>=m_fTotalTime)
		{
			m_endframe=m_fTotalTime;
		}
		if (m_bPlay)
			Animate( getSpeed(), float(m_startframe), float(m_endframe) , b_loop);	
		else
			Animate( getSpeed(), 0.0f, 0.0f, b_loop);
		if (bUnderWater)
		{
			VR_Ocean::CLivensonCg::getSingleton().End();
		}
		glPopMatrix();

	}

	//-------------------------------------------------------------
	//- Render
	//- Renders the model as it would be at time "fTime" (in seconds)
	//-------------------------------------------------------------
	void CMs3d::Render(float fTime)
	{
		Animate( getSpeed(), fTime, fTime, false);
	}

	//-------------------------------------------------------------
	//- Animate
	//- Animates the model from start time to end time (in seconds)
	//- at specified speed and can loop
	//-------------------------------------------------------------
	void CMs3d::Animate(float fSpeed, float fStartTime, float fEndTime, bool bLoop)
	{

		int x;

		if(m_bPlay==false)fEndTime=0;

		if (m_load==FALSE)
		{
			Setup();
			m_load=TRUE;
			bFirstTime = true;
		}

		//First time animate has been called

		if(bFirstTime)
		{//修改的部分
			fLastTime= fStartTime;
			m_Timer.Init();
			m_Timer.GetSeconds();
			bFirstTime = false;
		}

		if (m_bPlay)
		{
			fTime = m_Timer.GetSeconds() * fSpeed;//帧时间
			fTime += fLastTime;
			fLastTime = fTime;
		}


		if (maxreachtime<fLastTime)
		{
			maxreachtime=fLastTime;			
		}
		/*if (maxreachtime>=fEndTime)
		{
		bNeedCalBoundBox=false;
		}*/

		//looping
		if(fTime > fEndTime)
		{
			// notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);
			if(bLoop)
			{			
				// Reset();
				// 注释掉此部分防止超时后所有动画置0的错误.
				// m_Timer.Init();
				// m_Timer.GetSeconds();
				// fLastTime = fStartTime;
				// fTime = fStartTime;

				float dt = fEndTime - fStartTime;

				while (fTime > dt)
				{
					fTime -= dt;
				}

				fTime += fStartTime;

			}
			else
				fTime = fEndTime;

			bNeedCalBoundBox=false;

			if (b_loop==false)
			{
				bNeedCalVertex=false;
			}	
		}	
		if (m_bPlay==false)
		{
			bNeedCalVertex=false;
		}
		//if (b_loop==false&&(maxreachtime>fEndTime||maxreachtime==fEndTime))
		//{
		//	bNeedCalVertex=false;
		//}	

		if (!bNeedCalVertex)
		{
			//return;
			goto drawcode;
		}

		for(x = 0; x < m_usNumJoints; x++)
		{
			//Transformation matrix
			CMatrix4X4 matTmp;
			//Current joint
			SMs3dJoint * pJoint = &m_pJoints[x];
			//Current frame]
			unsigned int uiFrame = 0;

			//if there are no keyframes, don't do any transformations
			if(pJoint->m_usNumRotFrames == 0 && pJoint->m_TransKeyFrames == 0)
			{
				pJoint->m_matFinal = pJoint->m_matAbs;
				continue;
			}
			//Calculate the current frame
			//Translation
			while(uiFrame < pJoint->m_usNumTransFrames && pJoint->m_TransKeyFrames[uiFrame].m_fTime < fTime)
				uiFrame++;
			pJoint->m_usCurTransFrame = uiFrame;

			float fTranslation[3];
			float fDeltaT = 1;
			float fInterp = 0;

			//If its at the extremes
			if(uiFrame == 0)
				memcpy(fTranslation, pJoint->m_TransKeyFrames[0].m_fParam, sizeof(float[3]));
			else if(uiFrame == pJoint->m_usNumTransFrames)
				memcpy(fTranslation, pJoint->m_TransKeyFrames[uiFrame-1].m_fParam, sizeof(float[3]));
			//If its in the middle of two frames
			else
			{
				SMs3dKeyFrame * pkCur = &pJoint->m_TransKeyFrames[uiFrame];
				SMs3dKeyFrame * pkPrev = &pJoint->m_TransKeyFrames[uiFrame-1];

				fDeltaT = pkCur->m_fTime - pkPrev->m_fTime;
				fInterp = (fTime - pkPrev->m_fTime) / fDeltaT;

				//Interpolate between the translations
				fTranslation[0] = pkPrev->m_fParam[0] + (pkCur->m_fParam[0] - pkPrev->m_fParam[0]) * fInterp;
				fTranslation[1] = pkPrev->m_fParam[1] + (pkCur->m_fParam[1] - pkPrev->m_fParam[1]) * fInterp;
				fTranslation[2] = pkPrev->m_fParam[2] + (pkCur->m_fParam[2] - pkPrev->m_fParam[2]) * fInterp;
			}
			//Calculate the current rotation
			uiFrame = 0;
			while(uiFrame < pJoint->m_usNumRotFrames && pJoint->m_RotKeyFrames[uiFrame].m_fTime < fTime)
				uiFrame++;


			//If its at the extremes
			if(uiFrame == 0)
				matTmp.SetRotation(pJoint->m_RotKeyFrames[0].m_fParam);
			else if(uiFrame == pJoint->m_usNumTransFrames)
				matTmp.SetRotation(pJoint->m_RotKeyFrames[uiFrame-1].m_fParam);
			//If its in the middle of two frames, use a quaternion SLERP operation to calculate a new position
			else
			{
				SMs3dKeyFrame * pkCur = &pJoint->m_RotKeyFrames[uiFrame];
				SMs3dKeyFrame * pkPrev = &pJoint->m_RotKeyFrames[uiFrame-1];

				fDeltaT = pkCur->m_fTime - pkPrev->m_fTime;
				fInterp = (fTime - pkPrev->m_fTime) / fDeltaT;

				//Create a rotation quaternion for each frame
				CQuaternion qCur;
				CQuaternion qPrev;
				qCur.FromEulers(pkCur->m_fParam);
				qPrev.FromEulers(pkPrev->m_fParam);
				//SLERP between the two frames
				CQuaternion qFinal = SLERP(qPrev, qCur, fInterp);

				//Convert the quaternion to a rotation matrix
				matTmp = qFinal.ToMatrix4();
			}

			//Set the translation part of the matrix
			matTmp.SetTranslation(fTranslation);

			//Calculate the joints final transformation
			CMatrix4X4 matFinal = pJoint->m_matLocal * matTmp;

			//if there is no parent, just use the matrix you just made
			if(pJoint->m_sParent == -1)
				pJoint->m_matFinal = matFinal;
			//otherwise the final matrix is the parents final matrix * the new matrix
			else
				pJoint->m_matFinal = m_pJoints[pJoint->m_sParent].m_matFinal * matFinal;
		}


drawcode:

		//Transform and render the meshes
		if(m_bDrawMesh)
		{
			//RenderT();
			renderByVertexArray();
		}

		if(m_bDrawBones)
		{
			glDisable(GL_DEPTH_TEST);
			//glDisable(GL_LIGHTING);
			glLineWidth(5);
			//Draw the bones
			glColor3f(0.0f, 1.0f, 0.0f);
			glBegin(GL_LINES);	
			for(x = 1; x < m_usNumJoints; x++)
			{
				float * fMat = m_pJoints[x].m_matFinal.Get();
				float * fMatParent = m_pJoints[m_pJoints[x].m_sParent].m_matFinal.Get();
				glVertex3f(fMat[12], fMat[13], fMat[14]);
				glVertex3f(fMatParent[12], fMatParent[13], fMatParent[14]);
			}
			glEnd();

			glEnable(GL_DEPTH_TEST);
		}

		//////////////////////////////////////////////////////////////////////////
		//for(x = 1; x < m_usNumJoints; x++)
		//{
		//	float * fMat = m_pJoints[x].m_matFinal.Get();
		//	float * fMatParent = m_pJoints[m_pJoints[x].m_sParent].m_matFinal.Get();
		//	ComputeBoundBoxmm(&fMat[12]);//, fMat[13], fMat[14]
		//	ComputeBoundBoxmm(&fMatParent[12]);//, fMatParent[13], fMatParent[14]
		//}
	}

	void CMs3d::renderByVertexArray()
	{
		CVector3 vecNormal;
		CVector3 vecVertex;

		// 遍历每个Mesh，根据Joint更新每个Vertex的坐标
		for(int x = 0; x < m_usNumMeshes; x++)
		{
			int vertexCnt = 0;

			//遍历Mesh的每个三角面
			for(int y = 0; y < m_pMeshes[x].m_usNumTris; y++)
			{
				//Set triangle pointer to triangle #1
				float* pVertexArray = m_meshVertexData.m_pMesh[x].pVertexArray;

				SMs3dTriangle * pTri = &m_pTriangles[m_pMeshes[x].m_uspIndices[y]];
				// 遍历三角面的三个顶点 
				for(int z = 0; z < 3; z++)
				{
					//Get the vertex
					SMs3dVertex * pVert = &m_pVertices[pTri->m_usVertIndices[z]];

					//If it has no bone, render as is
					if(pVert->m_cBone == -1)
					{
						//Send all 3 components without modification
						vecNormal = pTri->m_vNormals[z];
						vecVertex = pVert->m_vVert;
					}
					//Otherwise, transform the vertices and normals before displaying them
					else
					{
						SMs3dJoint * pJoint = &m_pJoints[pVert->m_cBone];
						// Transform the normals
						// vecNormal = pTri->m_vNormals[z];
						// Only rotate it, no translation
						// 当前版本不计算法线					
						// vecNormal.Transform3(pJoint->m_matFinal);

						// Transform the vertex
						vecVertex = pVert->m_vVert;
						// translate as well as rotate
						vecVertex.Transform4(pJoint->m_matFinal);

					}

					// 纹理坐标不需要更新	
					// pVertexArray[vertexCnt++] = pTri->m_fTexCoords[0][z];
					// pVertexArray[vertexCnt++] = pTri->m_fTexCoords[1][z];
					vertexCnt += 2;

					// 法线没有被计算和拷贝
					pVertexArray[vertexCnt++] = vecNormal[0];
					pVertexArray[vertexCnt++] = vecNormal[1];
					pVertexArray[vertexCnt++] = vecNormal[2];

					pVertexArray[vertexCnt++] = vecVertex[0];
					pVertexArray[vertexCnt++] = vecVertex[1];
					pVertexArray[vertexCnt++] = vecVertex[2];

					if (bNeedCalBoundBox)
						ComputeBoundBoxmm(vecVertex.Get());
				}
			}
		}

		//glEnable(GL_TEXTURE_2D);

		//glBegin(GL_TRIANGLES);

		glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
		glEnable( GL_TEXTURE_2D );

		glDisable(GL_BLEND);
		glDisable(GL_ALPHA_TEST);


		for (int i=0; i< m_meshVertexData.m_numberOfMesh; i++)
		{
			//Texture map
			if (m_meshVertexData.m_pMesh[i].materialID >= 0)
			{
				SMs3dMaterial * pCurMat = &m_pMaterials[m_meshVertexData.m_pMesh[i].materialID];

				if (pCurMat->m_Texture != NULL)
				{
					pCurMat->m_Texture->useBind();
				}
				else
				{
					glDisable(GL_TEXTURE_2D);
				}
			}

			/*
			int cnt = 0;
			for (int j=0; j<m_meshVertexData.m_pMesh[i].numOfVertex / 3; j++)
			{

			glTexCoord2f(m_meshVertexData.m_pMesh[i].pVertexArray[cnt++], 
			m_meshVertexData.m_pMesh[i].pVertexArray[cnt++]);		

			glNormal3f(m_meshVertexData.m_pMesh[i].pVertexArray[cnt++],
			m_meshVertexData.m_pMesh[i].pVertexArray[cnt++],
			m_meshVertexData.m_pMesh[i].pVertexArray[cnt++]);


			glVertex3f(m_meshVertexData.m_pMesh[i].pVertexArray[cnt++],
			m_meshVertexData.m_pMesh[i].pVertexArray[cnt++],
			m_meshVertexData.m_pMesh[i].pVertexArray[cnt++]);

			glTexCoord2f(m_meshVertexData.m_pMesh[i].pVertexArray[cnt++], 
			m_meshVertexData.m_pMesh[i].pVertexArray[cnt++]);		


			glNormal3f(m_meshVertexData.m_pMesh[i].pVertexArray[cnt++],
			m_meshVertexData.m_pMesh[i].pVertexArray[cnt++],
			m_meshVertexData.m_pMesh[i].pVertexArray[cnt++]);

			glVertex3f(m_meshVertexData.m_pMesh[i].pVertexArray[cnt++],
			m_meshVertexData.m_pMesh[i].pVertexArray[cnt++],
			m_meshVertexData.m_pMesh[i].pVertexArray[cnt++]);

			glTexCoord2f(m_meshVertexData.m_pMesh[i].pVertexArray[cnt++], 
			m_meshVertexData.m_pMesh[i].pVertexArray[cnt++]);		


			glNormal3f(m_meshVertexData.m_pMesh[i].pVertexArray[cnt++],
			m_meshVertexData.m_pMesh[i].pVertexArray[cnt++],
			m_meshVertexData.m_pMesh[i].pVertexArray[cnt++]);

			glVertex3f(m_meshVertexData.m_pMesh[i].pVertexArray[cnt++],
			m_meshVertexData.m_pMesh[i].pVertexArray[cnt++],
			m_meshVertexData.m_pMesh[i].pVertexArray[cnt++]);


			}*/



			glBindBufferARB( GL_ARRAY_BUFFER_ARB, NULL );
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, NULL);
			glInterleavedArrays(GL_T2F_N3F_V3F, 0, m_meshVertexData.m_pMesh[i].pVertexArray);
			glDrawElements(GL_TRIANGLES, m_meshVertexData.m_pMesh[i].numOfVertex,
				GL_UNSIGNED_INT , m_pIndexArray);
		}

		//glEnd();

		//glDisable(GL_TEXTURE_2D);

	}

	//-------------------------------------------------------------
	//- RenderT 
	//- Transform and render the meshes
	//-------------------------------------------------------------
	void CMs3d::RenderT()
	{
		assert(0);
		return;

		glEnable(GL_TEXTURE_2D);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		for(int x = 0; x < m_usNumMeshes; x++)
		{
			//Set up materials
			if(m_pMeshes[x].m_cMaterial >= 0)
			{  
				SMs3dMaterial * pCurMat = &m_pMaterials[m_pMeshes[x].m_cMaterial];
				//Set the alpha for transparency
				pCurMat->m_fDiffuse[3] = pCurMat->m_fTransparency;

				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, pCurMat->m_fAmbient);
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, pCurMat->m_fDiffuse);
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, pCurMat->m_fSpecular);
				glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, pCurMat->m_fEmissive);
				glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, pCurMat->m_fShininess);
				// 			glEnable(GL_BLEND);
				// 			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				//Texture map
				//pCurMat->m_Texture->useBind();


			}
			//		else
			//			glDisable(GL_BLEND);

			//Draw mesh
			//Transformed vertices and normals
			CVector3 vecNormal;
			CVector3 vecVertex;

			glBegin(GL_TRIANGLES);
			//Loop through triangles
			for(int y = 0; y < m_pMeshes[x].m_usNumTris; y++)
			{
				//Set triangle pointer to triangle #1

				SMs3dTriangle * pTri = &m_pTriangles[m_pMeshes[x].m_uspIndices[y]];
				//Loop through each vertex 
				for(int z = 0; z < 3; z++)
				{
					//Get the vertex
					SMs3dVertex * pVert = &m_pVertices[pTri->m_usVertIndices[z]];

					//If it has no bone, render as is
					if(pVert->m_cBone == -1)
					{
						//Send all 3 components without modification
						glTexCoord2f(pTri->m_fTexCoords[0][z], pTri->m_fTexCoords[1][z]);
						glVertex3fv(pVert->m_vVert.Get());
						glNormal3fv(pTri->m_vNormals[z].Get());

						// 666 [9/6/2008 zhu]	
						if (bNeedCalBoundBox)
							ComputeBoundBoxmm(vecVertex.Get());
					}
					//Otherwise, transform the vertices and normals before displaying them
					else
					{
						//Send the texture coordinates
						glTexCoord2f(pTri->m_fTexCoords[0][z], pTri->m_fTexCoords[1][z]);

						SMs3dJoint * pJoint = &m_pJoints[pVert->m_cBone];
						//Transform the normals
						vecNormal = pTri->m_vNormals[z];
						//Only rotate it, no translation
						//vecNormal.Transform3(pJoint->m_matFinal);
						//Send the normal to OpenGL
						glNormal3fv(vecNormal.Get());

						//Transform the vertex
						vecVertex = pVert->m_vVert;
						//translate as well as rotate
						//vecVertex.Transform4(pJoint->m_matFinal);
						//Send vertex to openGL
						glVertex3fv(vecVertex.Get());

						// 666 [9/6/2008 zhu]	
						if (bNeedCalBoundBox)
							ComputeBoundBoxmm(vecVertex.Get());
					}

				}
			}

			glEnd();
		}

		glDisable(GL_TEXTURE_2D);

	}

	//-------------------------------------------------------------
	//- Reset
	//- Reset the model
	//-------------------------------------------------------------
	void CMs3d::Reset()
	{

		//	m_Timer.Init();
		//	m_Timer.GetSeconds();
	}

	//-------------------------------------------------------------
	//- SwapBoneDraw
	//- Turn the display of bones on and off
	//-------------------------------------------------------------
	void CMs3d::SwapBoneDraw()
	{
		m_bDrawBones = !m_bDrawBones;
	}

	//-------------------------------------------------------------
	//- SwapMeshDraw
	//- Turn the display of the meshes on and off
	//-------------------------------------------------------------
	void CMs3d::SwapMeshDraw()
	{
		m_bDrawMesh = !m_bDrawMesh;
	}

	//-------------------------------------------------------------
	//- AreBonesEnabled
	//- Check if bones are being drawn
	//-------------------------------------------------------------
	bool CMs3d::AreBonesEnabled()
	{
		return m_bDrawBones;
	}


	//-------------------------------------------------------------
	//- AreMeshesEnabled
	//- Check if meshes are being drawn
	//-------------------------------------------------------------
	bool CMs3d::AreMeshesEnabled()
	{
		return m_bDrawMesh;
	}

	//-------------------------------------------------------------
	//- Setup
	//- Get the joints set up to their beggining positions
	//-------------------------------------------------------------
	void CMs3d::Setup()
	{
		int x;
		static int cnt = 0;

		PreSetup();
		//Go through each vertex
		for(x = 0; x < m_usNumVerts; x++)
		{
			//If there is no bone..
			if(m_pVertices[x].m_cBone== -1)
				continue;

			CMatrix4X4 * mat = &m_pJoints[m_pVertices[x].m_cBone].m_matFinal;


			mat->InverseTranslateVec(m_pVertices[x].m_vVert.Get());
			mat->InverseRotateVec(m_pVertices[x].m_vVert.Get());
		}
		//Go through the normals and transform them
		for(x = 0; x < m_usNumTriangles; x++)
		{
			SMs3dTriangle * pTri = &m_pTriangles[x];

			//Loop through each index
			for(int z = 0; z < 3; z++)
			{
				//Get the vertex so we can find out what joint we need to use to transform the normal
				SMs3dVertex * pVert = &m_pVertices[pTri->m_usVertIndices[z]];

				//if it is not attached to a bone, don't do any transforms
				if(pVert->m_cBone == -1)
					continue;

				SMs3dJoint * pJoint = &m_pJoints[pVert->m_cBone];

				//Transform the normal
				pJoint->m_matFinal.InverseRotateVec(pTri->m_vNormals[z].Get());

			}
		}

		setupVertexArray();
	}

	void CMs3d::setupVertexArray()
	{
		// 根据Mesh数生成m_usNumMeshes个VertexArray.
		// 在m_meshVertexData的析构函数中释放.
		m_meshVertexData.m_pMesh = new Ms3dVertexArrayMesh[m_usNumMeshes];
		m_meshVertexData.m_numberOfMesh = m_usNumMeshes;

		unsigned int maxMeshVertexNumber = 0;

		for(int x = 0; x < m_usNumMeshes; x++)
		{
			// 在m_pMesh的析构函数中释放. 如需要增加法线则使用
			float* pVertexArray = new float[(2+3+3) * m_pMeshes[x].m_usNumTris * 3];

			//float* pVertexArray = new float[(2+3) * m_pMeshes[x].m_usNumTris * 3];

			m_meshVertexData.m_pMesh[x].numOfVertex = m_pMeshes[x].m_usNumTris * 3;
			m_meshVertexData.m_pMesh[x].pVertexArray = pVertexArray;
			m_meshVertexData.m_pMesh[x].materialID = m_pMeshes[x].m_cMaterial;

			if (m_meshVertexData.m_pMesh[x].numOfVertex > maxMeshVertexNumber)
			{
				maxMeshVertexNumber = m_meshVertexData.m_pMesh[x].numOfVertex;
			}
		}

		CVector3 vecNormal;
		CVector3 vecVertex;

		m_pIndexArray = new unsigned int[maxMeshVertexNumber];

		for (int i=0; i<maxMeshVertexNumber; i++)
		{
			m_pIndexArray[i] = i;
		}

		for(int x = 0; x < m_usNumMeshes; x++)
		{
			int vertexCnt = 0;

			float* pVertexArray = m_meshVertexData.m_pMesh[x].pVertexArray;

			for(int y = 0; y < m_pMeshes[x].m_usNumTris; y++)
			{
				//Set triangle pointer to triangle #1

				SMs3dTriangle * pTri = &m_pTriangles[m_pMeshes[x].m_uspIndices[y]];
				//Loop through each vertex 
				for(int z = 0; z < 3; z++)
				{
					//Get the vertex
					SMs3dVertex * pVert = &m_pVertices[pTri->m_usVertIndices[z]];

					pVertexArray[vertexCnt++] = pTri->m_fTexCoords[0][z];
					pVertexArray[vertexCnt++] = 1.0f - pTri->m_fTexCoords[1][z];

					// 不初始化法线
					pVertexArray[vertexCnt++] = pTri->m_vNormals[z].Get()[0];
					pVertexArray[vertexCnt++] = pTri->m_vNormals[z].Get()[1];
					pVertexArray[vertexCnt++] = pTri->m_vNormals[z].Get()[2];

					pVertexArray[vertexCnt++] = pVert->m_vVert.Get()[0];
					pVertexArray[vertexCnt++] = pVert->m_vVert.Get()[1];
					pVertexArray[vertexCnt++] = pVert->m_vVert.Get()[2];
				}
			}
		}		

		return ;
	}

	void CMs3d::ComputeBoundBoxmm(float *point)
	{

		if (point[0] >_staticBox._maxVertex.x)
		{
			_staticBox._maxVertex.x = point[0];
		}

		if (point[0] < _staticBox._minVertex.x)
		{
			_staticBox._minVertex.x = point[0];
		}

		if (point[1]>_staticBox._maxVertex.y)
		{
			_staticBox._maxVertex.y = point[1];
		}

		if (point[1] < _staticBox._minVertex.y)
		{
			_staticBox._minVertex.y = point[1];
		}

		if (point[2] >_staticBox._maxVertex.z)
		{
			_staticBox._maxVertex.z = point[2];
		}

		if (point[2] < _staticBox._minVertex.z)
		{
			_staticBox._minVertex.z = point[2];
		}

	}
	void CMs3d::translate(Vector3 offset)
	{
		vgKernel::Mat4 tran;
		vgKernel::Mat4 tmp;

		vgKernel::Math::createTranslationMatrix(offset.x, offset.y, offset.z, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;


		_dynamicBox = _staticBox;
		_dynamicBox.matrixTranslation(_matrix);

		this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);
	}
	void CMs3d::rotateSelf(const float& angle, const float& x, const float& y, const float& z)
	{

		vgKernel::Mat4 tran;
		vgKernel::Mat4 tmp;

		vgKernel::Math::createTranslationMatrix(-_dynamicBox.getCenter().x, -_dynamicBox.getCenter().y, -_dynamicBox.getCenter().z, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;

		vgKernel::Math::createRotationMatrix(angle, x, y, z, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;

		vgKernel::Math::createTranslationMatrix(_dynamicBox.getCenter().x, _dynamicBox.getCenter().y, _dynamicBox.getCenter().z, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;

		_dynamicBox = _staticBox;
		_dynamicBox.matrixTranslation(_matrix);
		this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);
	}
	void CMs3d::rotate(const float& angle, const float& cx, const float& cy, const float& cz, 
		const float& x, const float& y, const float& z) 
	{
		vgKernel::Mat4 tran;
		vgKernel::Mat4 tmp;

		vgKernel::Math::createTranslationMatrix(-cx, -cy, -cz, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;

		vgKernel::Math::createRotationMatrix(angle, x, y, z, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;

		vgKernel::Math::createTranslationMatrix(cx, cy,cz, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;

		_dynamicBox = _staticBox;
		_dynamicBox.matrixTranslation(_matrix);

	}

	void CMs3d::PreSetup()
	{
		//Go through each joint
		for(int x = 0; x < m_usNumJoints; x++)
		{

			m_pJoints[x].m_matLocal.SetRotation(m_pJoints[x].m_fRotation);
			m_pJoints[x].m_matLocal.SetTranslation(m_pJoints[x].m_fPosition);

			//Set the Abs transformations to the parents transformations, combined with their own local ones
			if(m_pJoints[x].m_sParent != -1)
			{
				m_pJoints[x].m_matAbs = m_pJoints[m_pJoints[x].m_sParent].m_matAbs * m_pJoints[x].m_matLocal;

			}
			//		//If there is no parent
			else
			{
				m_pJoints[x].m_matLocal.SetTranslation(m_pJoints[x].m_fPosition);
				m_pJoints[x].m_matAbs = m_pJoints[x].m_matLocal;

			}
			m_pJoints[x].m_matFinal = m_pJoints[x].m_matAbs;
		}
	}


	void CMs3d::Play()
	{
		m_bPlay=true;
	}
	void CMs3d::Stop()
	{
		m_bPlay=false;
	}
	//-------------------------------------------------------------
	//- Constructors
	//- 1. Default contructor
	//- 2. Load an ms3d (takes a const char *)
	//- 3. Destructor
	//-------------------------------------------------------------
	CMs3d::CMs3d()
		:vgKernel::Renderer(  )
		,_uniqueID( vgKernel::UniqueIDFactory::getUniqueID())
	{
		setDefault();
	}

	CMs3d::CMs3d(const char * szFilename)
		:vgKernel::Renderer(  )
	{
		setDefault();

		Load(szFilename);
	}

	void CMs3d::WriteToFile(CFile &fp)
	{//写(保存)文件--livenson 2009.12.01
		fp.Write(&m_bPlay, sizeof(bool));
		fp.Write(&b_loop, sizeof(bool));
		fp.Write(&m_startframe, sizeof(float));
		fp.Write(&m_endframe, sizeof(float));

		int length=m_ms3dFileName.size();
		fp.Write(&length,  sizeof(int));//文件名长度
		fp.Write(m_ms3dFileName.c_str(), length);//文件名

		length= _meshName.size();
		fp.Write(&length,  sizeof(int));//文件名长度
		fp.Write(_meshName.c_str(), length);//文件名


		fp.Write(_matrix._m , sizeof(float)*16);//变换的矩阵


		fp.Write(&bUnderWater, sizeof(bool));

		fp.Write(&_speed, sizeof(float));
		fp.Write(&m_ThetaX,sizeof(float));


	};
	void CMs3d::ReadFromFile(CFile &fp)
	{
		fp.Read(&m_bPlay, sizeof(bool));
		fp.Read(&b_loop, sizeof(bool));
		fp.Read(&m_startframe, sizeof(float));
		fp.Read(&m_endframe, sizeof(float));

		int length;
		char	tempBuffer[255];
		fp.Read(&length , sizeof(int));
		fp.Read(tempBuffer, length);//文件名
		tempBuffer[length] = '\0';
		m_ms3dFileName = tempBuffer;

		fp.Read(&length , sizeof(int));
		fp.Read(tempBuffer, length);//文件名
		tempBuffer[length] = '\0';
		_meshName = tempBuffer;

		fp.Read(_matrix._m , sizeof(float)*16);

		fp.Read(&bUnderWater, sizeof(bool));

		fp.Read(&_speed, sizeof(float));
		fp.Read(&m_ThetaX,sizeof(float));

		//this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);
	}
	CMs3d::~CMs3d()
	{
		if(m_pVertices)
		{
			delete [] m_pVertices;
			m_pVertices = 0;
		}
		if(m_pTriangles)
		{
			delete [] m_pTriangles;
			m_pTriangles = 0;
		}
		if(m_pMeshes)
		{
			delete [] m_pMeshes;
			m_pMeshes = 0;
		}
		if(m_pMaterials)
		{
			for (int i=0; i<m_usNumMaterials ;i++)
			{
				if (m_pMaterials[i].m_Texture != NULL)
				{
					m_pMaterials[i].m_Texture->releaseRef();
				}
			}

			delete [] m_pMaterials;
			m_pMaterials = 0;
		}

		if (m_pIndexArray != NULL)
		{
			delete[] m_pIndexArray;
		}
	}

	float CMs3d::getSpeed()
	{
		return _speed;
	}

	void CMs3d::setSpeed( float speed )
	{
		_speed = speed;
	}

	void CMs3d::setDefault()
	{
		m_pVertices = 0;
		m_pTriangles = 0;
		m_pMeshes = 0;
		m_pMaterials = 0;
		m_bDrawMesh = true;
		m_bDrawBones = false;
		//	m_changed=false;
		m_load=false;
		m_bPlay=true;
		b_loop = true;//chunyongma
		m_startframe = 0;
		m_endframe = 0;

		_matrix= vgKernel::Mat4::IDENTITY;// add by lss when 2008-10-7 19:34:36


		maxreachtime=0;
		bNeedCalBoundBox=true;
		bNeedCalVertex=true;

		m_pIndexArray = NULL;
		bUnderWater = false;
		m_bSelected=false;
		m_ThetaX=0.0f;


		_speed = 1.0f;
	}
}
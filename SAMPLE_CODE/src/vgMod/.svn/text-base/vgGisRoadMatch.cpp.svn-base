
#include <vgStableHeaders.h>
#include <vgMod/vgGisRoadMatch.h>


namespace vgMod
{
	VGK_RENDERER_IMPLEMENT( GisRoadMatch , RENDERER_TYPE_GISMATCH ) 


	GisRoadMatch::GisRoadMatch() 
	{
		b_render = false;

		m_texdensity = 20.0;
		m_height = 10.0;
		m_bili = 0.0;

		strcpy_s(m_matchname, "_match");

	}

	GisRoadMatch::~GisRoadMatch() 
	{
	}

	void GisRoadMatch::AccessPoint( CPoint &pp )
	{
		/*vgCore::QuadtreeSceneManager &qq = 
		vgCore::QuadtreeSceneManager::getSingleton();

		Vector3 pp2 = qq.Trans2DTo3D(pp);*/
		vgKernel::Vec3	pt3D = vgKernel::Math::trans2DPointTo3DVec(pp.x, pp.y);

		matchpath.push_back(Vector3(pt3D));

	}

	void GisRoadMatch::addPoint( vgKernel::Vec3 _point )
	{
		matchpath.push_back( Vector3(_point) );
	}

	float GisRoadMatch::mathcal1(Vector2 &V1, Vector2 &V2)
	{
		float a = sqrt((V1.x - V2.x) * (V1.x - V2.x) + (V1.y - V2.y) * (V1.y - V2.y));

		return a;

	}
	Vector3 GisRoadMatch::GalPoint(Vector2 &V1, Vector2 &V2, Vector2 &V3, float &y)
	{
		float a = mathcal1(V1, V2);

		float c = mathcal1(V3, V2);

		float b = a*((V3.x - V2.x)*m_width*a + (V2.x*V1.y - V1.x*V2.y)*(V3.x-V2.x) - V2.x*(V3.x-V2.x)*(V1.y-V2.y) - V2.y*(V3.y-V2.y)*(V1.y-V2.y));

		float d = c*((V1.x - V2.x)*m_width*a + (V2.x*V1.y - V1.x*V2.y)*(V1.x-V2.x) - V2.x*(V1.x-V2.x)*(V1.y-V2.y) - V2.y*(V1.y-V2.y)*(V1.y-V2.y));

		float e = c*a*a - a*((V3.x-V2.x)*(V1.x-V2.x)+(V3.y-V2.y)*(V1.y-V2.y));

		if (e == 0)
		{
			e = 0.1;
		}

		float z = (b-d)/e;

		float x = (m_width*a + (V1.x-V2.x)*z + V2.x*V1.y - V1.x*V2.y)/(V1.y-V2.y);

		return Vector3(x,y,z);

	}

	void GisRoadMatch::Processport()
	{
		if (matchpath.size() >= 2)
		{
			Vector2 v1(matchpath[0].x, matchpath[0].z);
			Vector2 v2(matchpath[1].x, matchpath[1].z);

			Vector2 v3 = v1 - ( v2 - v1);

			Vector3 head(v3.x, matchpath[0].y, v3.y );

			vector<Vector3>::iterator _begin = matchpath.begin();

			matchpath.insert( _begin,head );

			int k = matchpath.size();

			Vector2 v5(matchpath[k-2].x, matchpath[k-2].z);
			Vector2 v6(matchpath[k-1].x, matchpath[k-1].z);

			Vector2 v4 = v6 + ( v6 - v5);

			Vector3 end(v4.x, matchpath[k-1].y, v4.y );

			matchpath.push_back( end );
		}
	}

	void GisRoadMatch::GenRoadWithPoints()
	{

		Processport();

		//BoundingBox	m_BoundryBox;	//	包围盒
		//Vector3     m_Position;		//	中心位置    	

		//------------------------------------------
		// 开始和末尾创建点
		//------------------------------------------
		//{
		//	if ( matchpath.size() >= 2  )
		//	{
		//		matchpath.insert( matchpath.begin() , matchpath[0] );
		//		matchpath.insert( matchpath.end()  , *matchpath.end() );
		//	}
		//}

		if (matchpath.size() >= 2)
		{
			for(int i = 0; i < matchpath.size()-2; i++)
			{
				Vector2 v1(matchpath[i].x, matchpath[i].z);
				Vector2 v2(matchpath[i+1].x, matchpath[i+1].z);
				Vector2 v3(matchpath[i+2].x, matchpath[i+2].z);

				Vector3 bb = GalPoint(v1, v2, v3, matchpath[i+1].y);

				Vector3 cc(bb);
				cc.x = v2.x * 2 - bb.x;
				cc.z = v2.y * 2 - bb.z;

				RenderPoints.push_back(bb);
				RenderPoints.push_back(cc);

				Vector3 dd = bb - Vector3(0,m_luya,0);
				LuyaPoints1.push_back(dd);

				Vector3 ee = cc - Vector3(0,m_luya,0);
				LuyaPoints2.push_back(ee);


			}

		}

		m_bili = m_luya / (m_width+m_luya) / 2.0 ;

		{// 材质
			if (!m_texname.empty())
			{
				//////////////////////////////////////////////////////////////////////////

				string  filefolderpath = m_texname;
				filefolderpath.erase( filefolderpath.find_last_of("\\/") , std::string::npos );
				try
				{
					vgCore::ArchiveManager &archmgr = vgCore::ArchiveManager::getSingleton();

					//vgCore::ArchivePtr parch( new vgCore::ZipArchive("win_zip.zip" ,"zip") );

					vgCore::ArchivePtr parch( new vgCore::FileSystemArchive(filefolderpath ,"filesystem") );

					//vgCore::ArchivePtr parch_vgimg( new vgCore::VgimgArchive("allimage.vgimg" ,"vgimg") );

					parch->load();

					static int weight = 9194;

					archmgr.addArchive( weight ++ , parch );

					//VG_TRACE( archmgr.getDetails() );
				}
				catch (vgCore::Exception &e)
				{
					MessageBox( NULL , e.getFullDescription().c_str() , "ERROR" , MB_OK );
				}

				m_texname.erase( 0,m_texname.find_last_of("\\/")+1); 


				vgCore::TextureManager &mgr = 
					vgCore::TextureManager::getSingleton();

				pTexture = mgr.getTexturePtr(m_texname);
				//////////////////////////////////////////////////////////////////////////
			}
		}
		calUV();

		b_render = true;
		ComputeBoundBox();

	}

	void GisRoadMatch::ReGenRoadWithPoints()
	{
		if (matchpath.size() >= 2)
		{
			for(int i = 0; i < matchpath.size()-2; i++)
			{
				Vector2 v1(matchpath[i].x, matchpath[i].z);
				Vector2 v2(matchpath[i+1].x, matchpath[i+1].z);
				Vector2 v3(matchpath[i+2].x, matchpath[i+2].z);

				Vector3 bb = GalPoint(v1, v2, v3, matchpath[i+1].y);

				Vector3 cc(bb);
				cc.x = v2.x * 2 - bb.x;
				cc.z = v2.y * 2 - bb.z;

				RenderPoints.push_back(bb);
				RenderPoints.push_back(cc);

				Vector3 dd = bb - Vector3(0,m_luya,0);
				LuyaPoints1.push_back(dd);

				Vector3 ee = cc - Vector3(0,m_luya,0);
				LuyaPoints2.push_back(ee);


			}

		}

		m_bili = m_luya / (m_width+m_luya) / 2.0 ;

		calUV();

		b_render = true;
		ComputeBoundBox();
	}

	void GisRoadMatch::calUV()
	{
		float dis0 = 0;

		float dis1 = 0;

		for (int i =0 ; i < RenderPoints.size(); i++)
		{
			Vector3 pp = RenderPoints[i];

			if (i == 0)
			{
				uv_u1.push_back(0);
			}

			else if (i%2 == 0 && i > 0)
			{
				Vector3 qq = RenderPoints[i-2];

				dis0 += pp.distance(qq);

				uv_u1.push_back(dis0/m_texdensity);
			}

			else if (i == 1)
			{
				uv_u2.push_back(0);
			}

			else
			{
				Vector3 qq = RenderPoints[i-2];

				dis1 += pp.distance(qq);
				if(dis1 - dis0 >= m_texdensity/4)
				{
					dis1 = dis0 + m_texdensity/4;
				}
				uv_u2.push_back(dis1/m_texdensity);


			}
		}

	}

	void GisRoadMatch::RenderRoadSurface()
	{
		glPushMatrix();

		if (!pTexture.isNull())
		{
			pTexture->useBind();
		}

		glBegin(GL_TRIANGLE_STRIP);

		//m_vPointRender.clear();
		for (int i =0 ; i < RenderPoints.size(); i++)
		{
			Vector3 pp = RenderPoints[i];

			if (i%2 == 0)
			{
				glTexCoord2f(uv_u1[i/2], m_bili);

			}
			else
			{
				glTexCoord2f(uv_u2[(i-1)/2], 1-m_bili);

			}
			glVertex3f(pp.x, pp.y+m_height, pp.z);	

			//point = Vector3(pp.x, pp.y + m_height, pp.z);
			//m_vPointRender.push_back(point);//YX

		}

		glEnd();
		//////////////////////////////////////////////////////////////////////////	

		glPopMatrix();
	}

	void GisRoadMatch::RenderLuya1()
	{
		glPushMatrix();

		if (!pTexture.isNull())
		{
			pTexture->useBind();
		}

		glBegin(GL_TRIANGLE_STRIP);

		for (int i =0 ; i < LuyaPoints1.size(); i++)
		{
			Vector3 pp = LuyaPoints1[i];

			Vector3 qq = RenderPoints[i * 2];

			glTexCoord2f(uv_u1[i], 0);

			glVertex3f(pp.x, pp.y + m_height, pp.z);

			//point = Vector3(pp.x, pp.y + m_height, pp.z);
			//m_vPointLuYa1.push_back(point);//YX

			glTexCoord2f(uv_u1[i], m_bili);

			glVertex3f(qq.x, qq.y + m_height, qq.z);

			//point = Vector3(qq.x, qq.y + m_height, qq.z);
			//m_vPointLuYa1.push_back(point);//YX

		}
		glEnd();
		//////////////////////////////////////////////////////////////////////////	

		glPopMatrix();

	}

	void GisRoadMatch::ReadMatchToscene(CFile &fp, String readPath)
	{
		String  GMatchPath(readPath);

		// 属性
		fp.Read( &m_id, sizeof(int));

		fp.Read( m_matchname, 20);

		char name[20];

		fp.Read(name, 20);

		m_texname = string(name);

		GMatchPath += name;

		vgCore::TextureManager &mgr = 
			vgCore::TextureManager::getSingleton();

		mgr.addTexturePtrByName(m_texname,GMatchPath );

		pTexture = mgr.getTexturePtr(m_texname);

		fp.Read(&m_width, sizeof(float));

		fp.Read(&m_luya, sizeof(float));

		fp.Read(&m_texdensity, sizeof(float));

		fp.Read(&m_height, sizeof(float));

		fp.Read(&m_bili, sizeof(float));


		// 数据块，地理坐标和纹理坐标
		int k ;
		fp.Read(&k, sizeof(int));

		for (int i =0 ; i < 2 * k; i++)
		{
			Vector3 pp;

			fp.Read(&pp.x, sizeof(float));
			fp.Read(&pp.y, sizeof(float));
			fp.Read(&pp.z, sizeof(float));

			RenderPoints.push_back(pp);
		}
		for (int i =0 ; i < k; i++)
		{
			Vector3 pp;

			fp.Read(&pp.x, sizeof(float));
			fp.Read(&pp.y, sizeof(float));
			fp.Read(&pp.z, sizeof(float));

			LuyaPoints1.push_back(pp);
		}

		for (int i =0 ; i < k; i++)
		{
			Vector3 pp;

			fp.Read(&pp.x, sizeof(float));
			fp.Read(&pp.y, sizeof(float));
			fp.Read(&pp.z, sizeof(float));

			LuyaPoints2.push_back(pp);
		}

		for (int i =0 ; i < k; i++)
		{
			float aa;

			fp.Read(&aa, sizeof(float));

			uv_u1.push_back(aa);
		}

		for (int i =0 ; i < k; i++)
		{
			float aa;

			fp.Read(&aa, sizeof(float));

			uv_u2.push_back(aa);
		}

		b_render = true;
		ComputeBoundBox();


	}

	void GisRoadMatch::SaveMatchTovg(CFile &fp)
	{
		// 属性
		fp.Write(&m_id, sizeof(int));

		fp.Write(m_matchname, 20);

		char buf[20];

		String shortname = vgKernel::StringUtility::getFilenameFromAbsolutePath(
			m_texname );

		if ( shortname.size() > 20 )
		{
			MessageBox( NULL , "gis match名字过长!" , "error" , MB_OK );
			memset( buf , 0 , 20 );

			fp.Write( buf , 20);
		}
		else
		{
			strcpy( buf , shortname.c_str() );
			fp.Write( buf , 20);
		}

		//fp.Write(m_texname.c_str(), 20);

		fp.Write(&m_width, sizeof(float));

		fp.Write(&m_luya, sizeof(float));

		fp.Write(&m_texdensity, sizeof(float));

		fp.Write(&m_height, sizeof(float));

		fp.Write(&m_bili , sizeof(float));


		// 数据块，地理坐标和纹理坐标
		int k = LuyaPoints1.size();
		fp.Write(&k, sizeof(int));
		for (int i =0 ; i < RenderPoints.size(); i++)
		{
			fp.Write(&RenderPoints[i], sizeof(Vector3));
		}// fp.Write(&RenderPoints, sizeof(Vector3)*2*k);

		for (int i =0 ; i < LuyaPoints1.size(); i++)
		{	
			fp.Write(&LuyaPoints1[i], sizeof(Vector3));
		}// fp.Write(&LuyaPoints1, sizeof(Vector3)*k);

		for (int i =0 ; i < LuyaPoints2.size(); i++)
		{
			fp.Write(&LuyaPoints2[i], sizeof(Vector3));
		}// fp.Write(&LuyaPoints2, sizeof(Vector3)*k);

		for (int i = 0; i < uv_u1.size(); i++)
		{
			fp.Write(&uv_u1[i], sizeof(float));
		}// fp.Write(&uv_u1, sizeof(float)*k);

		for (int i =0 ; i < uv_u2.size(); i++)
		{
			fp.Write(&uv_u2[i], sizeof(float));
		}// fp.Write(&uv_u2, sizeof(float)*k);
	}

	void GisRoadMatch::RenderLuya2()
	{
		glPushMatrix();

		if (!pTexture.isNull())
		{
			pTexture->useBind();
		}

		glBegin(GL_TRIANGLE_STRIP);

		for (int i =0 ; i < LuyaPoints2.size(); i++)
		{
			Vector3 pp = LuyaPoints2[i];

			Vector3 qq = RenderPoints[i * 2 + 1];

			glTexCoord2f(uv_u2[i], 1);

			glVertex3f(pp.x, pp.y + m_height, pp.z);

			//point = Vector3(pp.x, pp.y + m_height, pp.z);
			//m_vPointLuYa2.push_back(point);//YX


			glTexCoord2f(uv_u2[i], 1-m_bili);

			glVertex3f(qq.x, qq.y + m_height, qq.z);

			//point = Vector3(qq.x, qq.y + m_height, qq.z);
			//m_vPointLuYa2.push_back(point);//YX

		}
		glEnd();
		//////////////////////////////////////////////////////////////////////////	

		glPopMatrix();

	}

	void GisRoadMatch::SetTempPoint(CPoint &pp)
	{
		vgKernel::Vec3	pt3D = vgKernel::Math::trans2DPointTo3DVec(pp.x, pp.y);

		tempPoint = pt3D;
	}

	void GisRoadMatch::RenderPointAndLine()
	{

		glPushMatrix();

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glDisable( GL_TEXTURE_2D );


		glDisable( GL_BLEND );

		glPointSize(10.0);
		glColor3f(0,0,1.0);			
		glBegin(GL_POINTS);
		glVertex3f(tempPoint.x,tempPoint.y,tempPoint.z);//pos3[0].x,pos3[0].y,pos3[0].z
		glEnd();

		glPopMatrix();
		//////////////////////////////////////////////////////////////////////////
		glPushMatrix();

		//glPointSize(5.0);
		glColor3f(0,1.0,0);			
		glBegin(GL_POINTS);

		for (int i =0 ; i < matchpath.size(); i++)
		{
			Vector3 aa = matchpath[i];
			glVertex3f(aa.x,aa.y,aa.z);//pos3[0].x,pos3[0].y,pos3[0].z
		}
		glEnd();

		//////////////////////////////////////////////////////////////////////////
		glLineWidth(5.0f);
		glColor3f(0,0,1.0);			
		glBegin(GL_LINE_STRIP);

		for (int i =0 ; i < matchpath.size(); i++)
		{
			Vector3 aa = matchpath[i];
			glVertex3f(aa.x,aa.y,aa.z);//pos3[0].x,pos3[0].y,pos3[0].z
		}
		glEnd();

		glPopMatrix();

	}

	void GisRoadMatch::Render()
	{
		if (b_render)
		{

			glEnable(GL_TEXTURE_2D);

			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

			RenderRoadSurface();

			RenderLuya1();

			RenderLuya2();

			//ComputeBoundBox();

			glDisable(GL_TEXTURE_2D);
		}

		//else
			//RenderPointAndLine();

	}
	// ------------------------------------------------------------------ [9/23/2008 YX]
	void	GisRoadMatch::traslateVector3Array( Vector3 offset, vector<Vector3>& vecVec)
	{
		for (int i =0 ; i < vecVec.size(); i++)
		{
			vecVec[i]	+= offset;
		}

	}

	void GisRoadMatch::translate(const float& x, const float& y, const float& z)
	{
		Vector3 offset(x,y,z);
		if ( offset == Vector3::ZERO )
		{
			return;
		}
		traslateVector3Array(offset, LuyaPoints1);
		traslateVector3Array(offset, LuyaPoints2);
		traslateVector3Array(offset, RenderPoints);
		ComputeBoundBox();
		return;
	}


	void	GisRoadMatch::scaleVector3Array( Vector3 scale , Vector3 centerVec,  vector<Vector3>& vecVec)
	{
		for (int i =0 ; i < vecVec.size(); i++)
		{
			vecVec[i]	-= centerVec;
			vecVec[i]	*= scale;
			vecVec[i]	+= centerVec;
		}

	}

	void GisRoadMatch::scale(const float& cx, const float& cy, const float& cz, const float& x, const float& y, const float& z)
	{
		/*Vector3 scale(x,y, z), centerVec(cx, cy, cz);
		scaleVector3Array( scale, centerVec, LuyaPoints1 );
		scaleVector3Array( scale, centerVec, LuyaPoints2 );
		scaleVector3Array( scale, centerVec, RenderPoints );

		m_width		*= x*z;
		m_luya	*= y ;

		ComputeBoundBox();*/
		return;
	}

	void	GisRoadMatch::rotatePointArray( short axis, float angle ,Vector3 centerVec, vector<Vector3>& vecVec )
	{
		for(int i =0 ; i < vecVec.size() ; i++)
		{
			switch(axis)
			{
			case 0:
				RotatePoint(centerVec.y, centerVec.z, angle, &vecVec[i].y, &vecVec[i].z);
				break;

			case 1:
				RotatePoint(centerVec.z, centerVec.x, angle, &vecVec[i].z, &vecVec[i].x);
				break;

			default:
				RotatePoint(centerVec.x, centerVec.y, angle, &vecVec[i].x, &vecVec[i].y);
				break;
			}//switch(axis)
		}//for(m_numOfVertexs)	
		return;
	}
	void GisRoadMatch::rotate(const float& angle, const float& cx, const float& cy, const float& cz, const float& x, const float& y, const float& z)
	{
		Vector3 rot(x,y, z), centerVec(cx, cy, cz);

		short axis = -1;
		if(rot.x>1.0e-3)
		{
			axis = 0;
		}
		else if(rot.y>1.0e-3)
		{
			axis = 1;
		}
		else if(rot.z>1.0e-3)
		{
			axis = 2;
		}

		rotatePointArray(axis, angle, centerVec, LuyaPoints1);
		rotatePointArray(axis, angle, centerVec, LuyaPoints2);
		rotatePointArray(axis, angle, centerVec, RenderPoints);
		ComputeBoundBox();
		return;
	}

	std::pair<bool, float> GisRoadMatch::testIntersectWithTriangles( const vgKernel::Ray& ray )
	{
		std::pair<bool, float> result;
		bool test_result = false;


		for ( int i = 0 ; i < LuyaPoints1.size()-1; ++ i )
		{
			vgKernel::Vec3	p1 = vgKernel::Vec3(LuyaPoints1[i].x, LuyaPoints1[i].y		 + m_height, 
				LuyaPoints1[i].z);
			vgKernel::Vec3	p2 = vgKernel::Vec3(RenderPoints[2*(i+1)].x, RenderPoints[2*(i+1)].y	 + m_height, 
				RenderPoints[2*(i+1)].z);
			vgKernel::Vec3	p3 = vgKernel::Vec3(LuyaPoints1[i+1].x, LuyaPoints1[i+1].y	 + m_height, 
				LuyaPoints1[i+1].z);

			result = vgKernel::Math::intersects( ray ,p1  , p2, p3 );

			if (result.first==true)
			{
				return result;
			}

			p1 = vgKernel::Vec3(LuyaPoints1[i].x, LuyaPoints1[i].y		 + m_height, 
				LuyaPoints1[i].z);
			p2 = vgKernel::Vec3(RenderPoints[2*i].x, RenderPoints[2*i].y	 + m_height, 
				RenderPoints[2*i].z);
			p3 = vgKernel::Vec3(RenderPoints[2*(i+1)].x, RenderPoints[2*(i+1)].y	 + m_height, 
				RenderPoints[2*(i+1)].z);

			result = vgKernel::Math::intersects( ray ,p1  , p2, p3 );

			if (result.first==true)
			{
				return result;
			}

		}

		// cc-ee
		for ( int i = 0 ; i < LuyaPoints2.size()-1; ++ i )
		{
			vgKernel::Vec3	p1 = vgKernel::Vec3(LuyaPoints2[i].x, LuyaPoints2[i].y		 + m_height, 
				LuyaPoints2[i].z);
			vgKernel::Vec3	p2 = vgKernel::Vec3(LuyaPoints2[i+1].x, LuyaPoints2[i+1].y	 + m_height, 
				LuyaPoints2[i+1].z);
			vgKernel::Vec3	p3 = vgKernel::Vec3(RenderPoints[2*i+3].x, RenderPoints[2*i+3].y	 + m_height, 
				RenderPoints[2*i+3].z);

			result = vgKernel::Math::intersects( ray ,p1  , p2, p3 );

			if (result.first==true)
			{
				return result;
			}

			p1 = vgKernel::Vec3(LuyaPoints2[i].x, LuyaPoints2[i].y		 + m_height, 
				LuyaPoints2[i].z);
			p2 = vgKernel::Vec3(RenderPoints[2*i+3].x, RenderPoints[2*i+3].y	 + m_height, 
				RenderPoints[2*i+3].z);
			p3 = vgKernel::Vec3(RenderPoints[2*i+1].x, RenderPoints[2*i+1].y	 + m_height, 
				RenderPoints[2*i+1].z);

			result = vgKernel::Math::intersects( ray ,p1  , p2, p3 );

			if (result.first==true)
			{
				return result;
			}
		}

		// bb-cc
		for ( int i = 0 ; i < RenderPoints.size()-2; ++ i )
		{
			vgKernel::Vec3	p1 = vgKernel::Vec3(RenderPoints[i].x, RenderPoints[i].y	 + m_height, 
				RenderPoints[i].z);
			vgKernel::Vec3	p2 = vgKernel::Vec3(RenderPoints[i+1].x, RenderPoints[i+1].y + m_height, 
				RenderPoints[i+1].z);
			vgKernel::Vec3	p3 = vgKernel::Vec3(RenderPoints[i+2].x, RenderPoints[i+2].y + m_height, 
				RenderPoints[i+2].z);

			result = vgKernel::Math::intersects( ray , p1 , p2 , p3 );

			if (result.first==true)
			{
				return result;
			}
		}

		return result;
	}

	BoundingBox GisRoadMatch::ComputeBoundBox()
	{
		/*Vector3		tempVec = getVertexElementPosition(0);

		m_BoundryBox	= BoundingBox(tempVec, tempVec);

		for (int i =1 ; i < m_vPointQuad.size() ; i++)
		{
		tempVec = getVertexElementPosition(i);

		m_BoundryBox.minPoint.makeFloor(tempVec);

		m_BoundryBox.maxPoint.makeCeil(tempVec);
		}*/
		m_BoundryBox	= BoundingBox();
		for (int i = 0; i < LuyaPoints1.size(); i++)
		{
			m_BoundryBox.minPoint.makeFloor(LuyaPoints1[i]);
			m_BoundryBox.maxPoint.makeCeil(LuyaPoints1[i]);
		}

		for (int i = 0; i < LuyaPoints2.size(); i++)
		{
			m_BoundryBox.minPoint.makeFloor(LuyaPoints2[i]);
			m_BoundryBox.maxPoint.makeCeil(LuyaPoints2[i]);
		}

		for (int i = 0; i < RenderPoints.size(); i++)
		{
			m_BoundryBox.minPoint.makeFloor(RenderPoints[i]);
			m_BoundryBox.maxPoint.makeCeil(RenderPoints[i]);
		}

		m_BoundryBox.minPoint.y += m_height;
		m_BoundryBox.maxPoint.y += m_height;

		m_Position	= m_BoundryBox.getCenter();

		this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);
		return m_BoundryBox;
	}





}

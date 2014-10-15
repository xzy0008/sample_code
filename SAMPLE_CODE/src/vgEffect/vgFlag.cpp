//vgFlag.cpp


#include <vgStableHeaders.h>
#include "vgEffect/vgFlag.h"  //改为 vgFlag.h
//#include <vgMod/vgQuadtreeSceneManager.h>

// class vgFlag
namespace vgMod
{
	
	VGK_RENDERER_IMPLEMENT( vgFlag ,RENDERER_TYPE_PARTICLE)

	
	//////////////////////////////////////////////////////////////////////////
	vgFlag::vgFlag()
	{
		int i,j;
		for(i=0;i<XN;i++)
			for(j=0;j<YN;j++)	
			{
				cloth[i][j] = Vector3(0,0,0);
				d[i][j] = Vector3(0,0,0);
				dd[i][j] = Vector3(0,0,0);
				
			}
			m_Position.x = -47.59f;
			m_Position.y = 25.73f;
			m_Position.z = -198.01f;
			
			m_width		= 4.0f;
			m_height	= 3.0f;
			m_speed     = 3.0f;
// 			deltaX		= m_width /XN;
// 			deltaY		= m_height/YN;

			strcpy( m_name, "flag");
//			Init();
			
			
			//TYPE = VG_FLAG;	
			
			//m_numOfFaces = 100;  //???
			m_eSubType = PARTICLE_FLAG;
			
	}
	
	vgFlag::~vgFlag()
	{
		
	}
	
	
	void vgFlag::fixlen(Vector3 a,Vector3 b,float L,Vector3 *d)  
	{//使节点间距恢复到定长
		
		float tmp;
		Vector3 delta;
		float lamda = 0.98f;				// 参数1
		
		delta=b-a;
		tmp= delta.length ();
		if(tmp>0.0)
		{
			tmp=0.5f*(1-L/tmp);
			if(tmp<0.0f) tmp*=0.1f;
			
			*d=delta*(tmp*lamda);
		}
	}
	
	
	void vgFlag::straighten(Vector3 a,Vector3 b,
		Vector3 c,Vector3 *d1,Vector3 *d2,Vector3 *d3)
	{//直线方向的弹性
		
		Vector3 u,v,delta,delta1;
		float tmp,tmp1,tmp2,lamda=0.005f*(float)(deltaX+deltaY);				// 参数2
		
		
		u=b-a;
		v=c-b;
		
		tmp=(u.length ())*(v.length ());
		
		if(tmp>0.0)
		{
			tmp=(tmp-u.dotProduct(v) /*.FlagDot(v)*/ )/tmp;
			delta1 = u.crossProduct(v) /*.FlagCross(v)*/;
			tmp1= delta1.length() ;
			
			if(tmp1>0.0)
			{
				tmp2=tmp/tmp1;
				
				delta=u^delta1 /*.FlagCross( delta1)*/;
				
				*d1 = *d1 + (delta/u.length() )*(lamda*tmp2);
				*d2 = *d2 - (delta/u.length() )*(lamda*tmp2);
				
				
				delta = v^delta1 /*.FlagCross( delta1)*/;
				
				*d3 = *d3 + (delta/u.length() )*(lamda*tmp2);
				*d2 = *d2 - (delta/u.length() )*(lamda*tmp2);
				
			}
		}
	}
	
	void vgFlag::strtangl(Vector3 a,Vector3 b,
		Vector3 c,Vector3 *d1,Vector3 *d2,Vector3 *d3)
	{//直角方向的弹性
		
		Vector3 u,v,delta,delta1;
		float tmp,tmp1,lamda=0.006f*(float)(deltaX+deltaY);				// 参数3
		
		
		u=b-a;
		v=c-b;
		
		tmp=u.dotProduct(v) /*.FlagDot( v)*/;
		if(tmp!=0.0)
		{
			tmp/=u.length( );
			tmp/=v.length( );
			
			delta1 = u^v /*.FlagCross( v)*/;
			delta = delta1^u /*.FlagCross( u)*/;
			
			tmp1=delta.length( );
			if(tmp1>0.0)
			{
				tmp1=tmp/tmp1;
				
				
				*d1=*d1+delta*(lamda*tmp1);
				*d2=*d2-delta*(lamda*tmp1);
				
			}
			
			delta = delta1^v /*.FlagCross( v)*/;
			tmp1=delta.length();
			if(tmp1>0.0)
			{
				tmp1=tmp/tmp1;
				
				
				*d3=*d3+delta*(lamda*tmp1);
				*d2=*d2-delta*(lamda*tmp1);
				
			}
		}
	}
	
	void vgFlag::wind(Vector3 w,Vector3 n,Vector3 *dd)
	{//风力的作用
		float tmp,lamda=(float)(deltaX+deltaY)*m_speed/1000;				// 参数5
		
		tmp=w.dotProduct(n) /*.FlagDot( n)*/*lamda;
		
		*dd=*dd+n*tmp;
		
	}
	
	void vgFlag::Initialize(void)
	{
		int i,j;

		deltaX		= m_width /XN;
		deltaY		= m_height/YN;		
		for(i=0;i<15;i++) //15
			for(j=0;j<10;j++) //10
			{
				cloth[i][j].x= m_Position.x /*-2.0f*/+i*(float)deltaX; //-40~40
				cloth[i][j].y= m_Position.y /*-20.0f*/+j*(float)deltaY; //-20~40
				cloth[i][j].z= m_Position.z /*+ .0f*//*-45*/;
			}
			w.x=1.0f;w.y=0.0f;w.z=0.001f;				// 参数6
			
			// 	float mat_amb[]={0.4,0.2,0.2,1.0};   //此四句定义旗帜的材质 
			// 	float mat_dif[]={0.5,0.5,0.0,1.0};//float mat_dif[]={0.9,0.1,0.0,1.0};
			// 	float mat_spe[]={0.0,0.0,0.0,1.0};
			// 	float mat_shininess[]={50.0};
			
			// 	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_amb);
			// 	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mat_dif);
			// 	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_spe);
			// 	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,mat_shininess);
			
			//	return  TRUE;
	}	//void vgFlag::Init(void)
	
	void vgFlag::Render()
	{
		render2();
		update();
	}
	
	
	void vgFlag::update()
	{
		int i,j;
		Vector3 tmpd,tmpu,tmpv;
		float tmplen,lamda=0.98f;				// 参数7
		
		float  mg = (deltaX+deltaY)*0.0004 ;
		
		for(i=0;i<XN;i++)
			for(j=0;j<YN;j++)
			{
				
				d[i][j]=d[i][j]*lamda;
				dd[i][j]=Vector3(0,0,0);
			};
			
		for(i=0;i<XN;i++)
			for(j=0;j<YN;j++)
				d[i][j].y=d[i][j].y- mg ;
				
		for(i=0;i<XN;i++)
			{
				for(j=0;j<YN-1;j++)
				{
					fixlen(cloth[i][j],cloth[i][j+1],(float)deltaY,&tmpd);
						
					d[i][j]=d[i][j]+tmpd;
					d[i][j+1]=d[i][j+1]-tmpd;
						
				}
			};
		for(j=0;j<YN;j++)
		{
			for(i=0;i<XN-1;i++)
			{
				fixlen(cloth[i][j],cloth[i+1][j],(float)deltaX,&tmpd);
				
				d[i][j]=d[i][j]+tmpd;
				d[i+1][j]=d[i+1][j]-tmpd;
				
			}
		};
				
				
		for(i=0;i<XN;i++)
			for(j=0;j<YN-2;j++)
			{
				straighten(cloth[i][j],cloth[i][j+1],cloth[i][j+2],
					&d[i][j],&d[i][j+1],&d[i][j+2]);
			}
		for(j=0;j<YN;j++)
			for(i=0;i<XN-2;i++)
			{
				straighten(cloth[i+2][j],cloth[i+1][j],cloth[i][j],
				&d[i][j],&d[i+1][j],&d[i+2][j]);
			}
				
		for(i=0;i<XN-1;i++)
			for(j=0;j<YN-1;j++)
			{
				strtangl(cloth[i][j],cloth[i+1][j],cloth[i+1][j+1],
				&d[i][j],&d[i+1][j],&d[i+1][j+1]);
				strtangl(cloth[i][j],cloth[i][j+1],cloth[i+1][j+1],
				&d[i][j],&d[i][j+1],&d[i+1][j+1]);
			}
					
		//////////////////////////////////////
		////////////////////////////////////
		// 计算normal
		for(i=1;i<XN-1;i++)
			for(j=1;j<YN-1;j++)
				{
							
					tmpu=cloth[i+1][j]-cloth[i-1][j];
					tmpv=cloth[i][j+1]-cloth[i][j-1];
							
					normal[i][j] = tmpu^tmpv /*.FlagCross( tmpv)*/;
					tmplen= normal[i][j].length();
					if(tmplen>0.0)
					{
						normal[i][j]=normal[i][j]/tmplen;
					}
				}
						
			for(i=1;i<XN-1;i++)
			{
				
				tmpu=cloth[i+1][0]-cloth[i-1][0];
				tmpv=cloth[i][1]-cloth[i][0];
				
				normal[i][0]= tmpu^tmpv /*.FlagCross( tmpv)*/;
				
				tmplen= normal[i][0].length();
				
				if(tmplen>0.0)
				{
					normal[i][0]=normal[i][0]/tmplen;
				}
				
				tmpu=cloth[i+1][YN-1]-cloth[i-1][YN-1];
				tmpv=cloth[i][YN-1]-cloth[i][YN-2];
				
				normal[i][YN-1] = tmpu^tmpv /*.FlagCross( tmpv)*/;
				
				tmplen= normal[i][YN-1].length();
				
				if(tmplen>0.0)
				{
					normal[i][YN-1]=normal[i][YN-1]/tmplen;
				}
			}
			
			for(j=1;j<YN-1;j++)
			{
				
				tmpu=cloth[1][j]-cloth[0][j];
				tmpv=cloth[0][j+1]-cloth[0][j-1];
				
				normal[0][j] = tmpu^tmpv /*.FlagCross( tmpv)*/;
				tmplen= normal[0][j].length();
				
				if(tmplen>0.0)
				{
					normal[0][j]=normal[0][j]/tmplen;
				}
				
				tmpu=cloth[XN-1][j]-cloth[XN-2][j];
				tmpv=cloth[XN-1][j+1]-cloth[XN-1][j-1];
				
				normal[XN-1][j] = tmpu^tmpv /*.FlagCross( tmpv)*/;
				
				tmplen= normal[XN-1][j].length();
				if(tmplen>0.0)
				{
					normal[XN-1][j]=normal[XN-1][j]/tmplen;
				}
			}
			
			// 左下角
			tmpu=cloth[1][0]-cloth[0][0];
			tmpv=cloth[0][1]-cloth[0][0];
			
			normal[0][0] = tmpu^tmpv /*.FlagCross( tmpv)*/;
			
			tmplen= normal[0][0].length();
			if(tmplen>0.0) 
			{
				normal[0][0]=normal[0][0]/tmplen;
			}// 左下角
			// 
			// 右下角
			tmpu=cloth[XN-1][0]-cloth[XN-2][0];
			tmpv=cloth[XN-1][1]-cloth[XN-1][0];
			
			normal[XN-1][0] = tmpu^tmpv /*.FlagCross( tmpv)*/;
			tmplen= normal[XN-1][0].length();
			if(tmplen>0.0) 
			{
				normal[XN-1][0]=normal[XN-1][0]/tmplen;
			}// 右下角
			// 	
			// 左上角
			tmpu=cloth[1][YN-1]-cloth[0][YN-1];
			tmpv=cloth[0][YN-1]-cloth[0][YN-2];
			
			normal[0][YN-1] = tmpu^tmpv /*.FlagCross( tmpv)*/;
			tmplen= normal[0][YN-1].length();
			if(tmplen>0.0) 
			{
				normal[0][YN-1]=normal[0][YN-1]/tmplen;
			}// 左上角
			// 
			// 右上角
			tmpu=cloth[XN-1][YN-1]-cloth[XN-2][YN-1];
			tmpv=cloth[XN-1][YN-1]-cloth[XN-1][YN-2];
			
			normal[XN-1][YN-1] = tmpu^tmpv /*.FlagCross( tmpv)*/;
			tmplen= normal[XN-1][YN-1].length();
			if(tmplen>0.0) 
			{
				normal[XN-1][YN-1]=normal[XN-1][YN-1]/tmplen;
			}	// 右上角
			
			
			// 更新 no problem
			for(i=0;i<XN;i++)
				for(j=0;j<YN;j++)
				{
					wind(w,normal[i][j],&dd[i][j]);
					
					d[i][j]=d[i][j]+dd[i][j];
				}
				
			for(j=0;j<YN;j++)		
				d[0][j]=Vector3(0,0,0);
				
			for(i=0;i<XN;i++)
				for(j=0;j<YN;j++)	
					cloth[i][j]=cloth[i][j]+d[i][j];
					
	}	//void vgFlag::update()

	void vgFlag::render2()
	{
		//glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
		glPushMatrix();
		int i,j;
		glColor3f(0.7f, 0.1f, 0.1f);
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		for(i=0;i<XN-1;i++)
		{
			glBegin(GL_QUAD_STRIP);
			for(j=0;j<YN;j++)
			{
				glNormal3f(normal[i][j].x,normal[i][j].y,normal[i][j].z);
				glVertex3f(cloth[i][j].x,cloth[i][j].y,cloth[i][j].z);
				glNormal3f(normal[i+1][j].x,normal[i+1][j].y,normal[i+1][j].z);
				glVertex3f(cloth[i+1][j].x,cloth[i+1][j].y,cloth[i+1][j].z);
			}
			glEnd();
		}
		glPopMatrix();
		//glEnable(GL_BLEND);
		//glDisable(GL_DEPTH_TEST);
		
	}	//void vgFlag::render()

	BoundingBox vgFlag::ComputeBoundBox()
	{
//		float maxWidth;
//		m_width > m_height ? (maxWidth=m_width) : (maxWidth=m_height) ;

		m_BoundryBox.maxPoint.x = m_Position.x + m_width;
		m_BoundryBox.maxPoint.y = m_Position.y + m_height;
		m_BoundryBox.maxPoint.z = m_Position.z + m_width/5.0f;
		
		m_BoundryBox.minPoint.x = m_Position.x /*- maxWidth*/;
		m_BoundryBox.minPoint.y = m_Position.y ;
		m_BoundryBox.minPoint.z = m_Position.z - m_width/5.0f;

		return	m_BoundryBox;
	}	//BoundingBox ComputeBoundBox()
	
	//void vgFlag::WriteNodeToVG(CFile &fp)	//写入文件
	//{
	//	int i;
	//	
	//	i = VG_PARTICLE;
	//
	//long newpos;

	////fp.Write(&m_id , sizeof(int));                 //写该节点的ID		

	//Posinfile = fp.GetPosition();
	//	
	//fp.Write(&nodelength, sizeof(long));
	//	
	//	fp.Write(&i , sizeof(int));	               //写类型type
	//	
	//	i = 3;									//写烟类型
	//	
	//	fp.Write(&i, sizeof(int));
	//	fp.Write(m_LayerName , 20);						
	//	
	//	fp.Write(&m_isVisible, sizeof(bool));			//写可见性标记
	//	
	//	/*	char name[20]=" ";*/			
	//	fp.Write(m_texturename.c_str(), 20);			//写材质名
	//	
	//	fp.Write(&m_Position.x , sizeof(float));		//写节点中心点位置
	//	fp.Write(&m_Position.y, sizeof(float));	
	//	fp.Write(&m_Position.z , sizeof(float));
	//	
	//	fp.Write(&m_height, sizeof(float));	//写粒子属性 含高度、宽度、速度、大小
	//	fp.Write(&m_width, sizeof(float));

	//newpos = fp.GetPosition();
	//	
	//nodelength = newpos - Posinfile- sizeof(long);

	//fp.Seek(Posinfile, CFile::begin);

	//fp.Write(&nodelength, sizeof(long));

	//fp.SeekToEnd();
	//	
	//}	//	WriteNodeToVG(CFile &fp)
	
	void vgFlag::ReadDataFromSc(CFile &fp)
	{
		fp.Read(&TYPE , sizeof(int));	               //写类型type
		
		fp.Read(&m_id , sizeof(int));                 //写节点的ID	和 所属层次名
		fp.Read(m_LayerName , 20);						
		
		fp.Read(&m_isVisible, sizeof(bool));			//写可见性标记
		
		char name[20];
			
		fp.Read(name, 20);			//写材质名

		m_texturename = name;
		
		fp.Read(&m_Position.x , sizeof(float));		//写节点中心点位置
		fp.Read(&m_Position.y, sizeof(float));	
		fp.Read(&m_Position.z , sizeof(float));
		
		fp.Read(&m_height, sizeof(float));	//写粒子属性 含高度、宽度、速度、大小
		fp.Read(&m_width, sizeof(float));
		fp.Read(&m_speed, sizeof(float));
		fp.Read(&m_PartLenth, sizeof(float));
		fp.Read(&m_PartWidth, sizeof(float));
		
		fp.Read(&m_nParticleCount, sizeof(int));		//写粒子数目

		Initialize();
	}
	
//	unsigned long vgFlag::PositDataToNode(char *data  )  //从文件读取
//	{
//
//
//		unsigned long pos = 0;
//
//		//读取节点的ID	和 所属层次名
//		// 		m_id = *(int *)(data + pos);		
//		// 		pos += sizeof(int);
//
//		for (int i = 0 ; i < 20; i ++)
//		{
//			m_LayerName[i] = *(data + pos);
//			pos ++; 
//		}
//
//		//读取可见性标记
//		m_isVisible = *(bool *)(data + pos);
//
//		pos += sizeof(bool);
//// 		unsigned long pos = 0;
//// 		
//// 		//读取节点的ID	和 所属层次名
//// 		m_id = *(int *)(data + pos);		
//// 		pos += sizeof(int);
//// 		
//// 		for (int i = 0 ; i < 20; i ++)
//// 		{
//// 			m_LayerName[i] = *(data + pos);
//// 			pos ++; 
//// 		}
//// 		
//// 		//读取可见性标记
//// 		m_isVisible = *(bool *)(data + pos);
//		
////		pos += sizeof(bool);
//		
//		//读取材质名
//		char name[20];						
//		
//		for (int j =0; j < 20; j++)
//		{
//			name[j] = *(data + pos);
//			
//			pos ++;
//		}
//		m_texturename = name;
//		
//		//读取节点中心点位置
//		m_Position.x = *(float *)(data + pos);	
//		pos += sizeof(float);
//		
//		m_Position.y = *(float *)(data + pos);	
//		pos += sizeof(float);
//		
//		m_Position.z = *(float *)(data + pos);	
//		pos += sizeof(float);
//		
//		//写粒子属性 含高度、宽度、速度、大小
//		m_height = *(float *)(data + pos);	
//		pos += sizeof(float);
//		
//		m_width = *(float *)(data + pos);	
//		pos += sizeof(float);
//		
//		
//		//设置参数并初始化
//		//SetCenter(m_Position);
//		SetCount(m_nParticleCount);
//
//		SetHeight(m_height);
//		SetWidth(m_width);
//
//		Initialize();
//		
//		m_prePositon = m_Position;	
//		ComputeBoundBox();
//		
//		return pos;		
//	}
//
	
	
	void vgFlag::UpdatePos()
	{
		m_Position.x =  m_BoundryBox.minPoint.x;

		m_Position.y = m_BoundryBox.minPoint.y;

		m_Position.z = (m_BoundryBox.maxPoint.z + m_BoundryBox.minPoint.z) / 2;

		m_prePositon = m_Position;

		Initialize();
		/*vgCore::QuadtreeSceneManager &mgr = 
			vgCore::QuadtreeSceneManager::getSingleton();

		if (mgr.GetNodeAbstract(m_id))
		{
			mgr.GetNodeAbstract(m_id)->GetBoundryBox() = m_BoundryBox;

			mgr.GetNodeAbstract(m_id)->m_Position = m_Position;
		}*/
	}
}	//namespace vgCore

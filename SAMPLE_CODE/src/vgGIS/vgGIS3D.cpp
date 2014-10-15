#include <vgStableHeaders.h>
#if 0

#include <vgGis/vgGIS3D.h>

#include <vgKernel/vgkRendererManager.h>
#include <vgKernel/vgkInputSystem.h>

#include <vgMath/vgfMath.h>
#include <vgMath/vgfPointInPolygon.h>
#include "vgDlgPlaneLevel.h"
s
#include <vgKernel/vgkMath.h>

namespace vgGIS3D//vgGIS3D命名空间
{


	//----------------------------------------------------------------
	GIS3D::GIS3D(): Singleton<GIS3D>(VGK_SINGLETON_LEFE_GIS3D)
	{
		reset();

		//this->SetHandleStatus(VG_INPUTMODE_GIS);
		//vgKernel::InputSystem::getSingleton().registerHandle(this);
	}
	//----------------------------------------------------------------
	GIS3D::~GIS3D()
	{

	}

	//----------------------------------------------------------------
	void GIS3D::init()
	{
		m_gis_state=GisNone;
		//psnum=0;
	}
	//----------------------------------------------------------------
	//void GIS3D::OnLButtonDown(UINT nFlags, CPoint position)
	//{
	//	GisLBtDn(position);
	//}
	////----------------------------------------------------------------
	//void GIS3D::OnLButtonDbClick(UINT nFlags, CPoint position)
	//{
	//	GisLBtDblClk(position);
	//}
	////----------------------------------------------------------------
	//void GIS3D::OnMouseMove(UINT nFlags, CPoint position)
	//{
	//	if ( !m_bOperationDone )
	//	{
	//		GisMsMv(position);
	//	}
	//}
	////----------------------------------------------------------------
	//void GIS3D::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
	//{
	//	GisMouseWheel(zDelta);
	//}
	////----------------------------------------------------------------
	//void GIS3D::OnRBottonDown(UINT nFlags, CPoint position) 
	//{


	//	if(m_gis_state==GisTerLeveling&&btm==TRUE)
	//	{
	//		CPlaneLevel dlg;
	//		MessageBox(NULL,"你要进行输入吗？","GIS",0);
	//		dlg.m_plane_level=avh;
	//		//CWnd *pwnd=AfxGetApp()->m_pMainWnd;
	//		//pwnd->SetTimer(1, 150, NULL);
	//		dlg.DoModal();	
	//		//pwnd->SetTimer(1, 15, NULL);

	//	}
	//}

	//----------------------------------------------------------------
	void GIS3D::GisMouseWheel(short zDelta)
	{
		//if (gis_state==5||gis_state==61||gis_state==62)
		if(m_gis_state==GisWaterArea||m_gis_state==GisWaterVolume||m_gis_state==GisSoilVolume)
		{	if(zDelta>0)
		WaterHeight+=1;
		else if(zDelta<0)
			WaterHeight-=1;
		}
		//if (gis_state==10&&gis_plane==1)
		if (m_gis_state==GisTerLeveling&&btm==true)/*&&gis_plane==1*/
		{
			if(zDelta>0)

				avh+=1;
			else if(zDelta<0)
				avh-=1;

			//if (!thisLevelVertexString.getPointer()->empty())
			//{
			//	int num=thisLevelVertexString.getPointer()->size();
			//	for(int dnum=0;dnum<num;dnum++)
			//	{
			//		rect[dnum][1]=avh;
			//	}
			//}


		}

	}
	//----------------------------------------------------------------
	void GIS3D::GisLBtDn(CPoint point)
	{
#if 1	
		switch(m_gis_state)
		{
		case GisDistance:
		case GisArea:
		case GisVolume:
			{
				pickAndAppendPoint(point);
			}
			break;

		case GisCoordinate:
		default:
			break;
		}

#else
		{
			if (m_gis_state==GisEditVertexString)//如果是编辑状态的话
			{	
				assert(0);
				//if (CurrentVertexStringPtr)//如果已经选中一个串的话
				//	//接下来遍历该串所有点，找出捕捉到的点，把选中点设为此点				
				//{
				//	if(SelectedPoint)
				//		SelectedPoint=NULL;
				//	else
				//		SelectedPoint=GetTheNearestPointPtr(CurrentVertexStringPtr,Trans2DTo3D(point));
				//}
				return;
			}
			if (m_gis_state==GisAddVertexString||m_gis_state==GisTerLeveling&&btm==false)
			{
				assert(0);
				//if (CurrentVertexStringPtr)
				//CurrentVertexStringPtr->push_back(Trans2DTo3D(point));
				return;
			}
			//if (gis_state==8||gis_state==61||gis_state==62)//横截面，地形体积
			if(m_gis_state==GisWaterVolume||m_gis_state==GisSoilVolume)
			{
				getDynamicPoint(point);
				//10-24
				/*if ((m_endPoint.z)/demdata.DX>demdata.Col||(m_endPoint.z)/demdata.DX<0||
				(m_endPoint.x)/demdata.DX>demdata.Row||(m_endPoint.x)/demdata.DX<0)
				{MessageBox(NULL,"请在地形上取点!",TEXT("GIS分析"),0);
				}	*/	
			}

			if (m_gis_state>GisCoordinate&&btm==FALSE)
			{
				if(gis_plane!=2)
					pickAndAppendPoint(point);
				if (m_gis_state==GisP2PVisibility&&psnum==1)
					m_pointsInLine[0].y+=3;

				if (m_gis_state==GisSection&&psnum==2)
				{
					psnum--;
					PreCalculation();
					if (dhk==true)
					{
						m_gis_state=GisNone;
					}
					else
						ShowMessage();
				}
				if ((m_gis_state==GisP2PVisibility)&&psnum==2)
				{	
					m_pointsInLine[1].y+=2;
					psnum--;
					ShowMessage();
				}
			}
			if(m_gis_state==GisWaterVolume||m_gis_state==GisSoilVolume)
			{

				if(gis_cut==1)
				{
					gis_cut=2;//停止切割面的调整
				}
				else 
					if(gis_cut==2)
					{
						OnePoint(point);
						gis_cut=3;
					}
					else if (gis_cut==4)
					{	gis_cut=0;
				ThreePoints(point);		//四点不对
				ShowMessage();

				}
			}
			bMouseMove=FALSE;
		}
#endif

	}
	//----------------------------------------------------------------
	void GIS3D::GisLBtDblClk(CPoint point)
	{
#if 1
		m_bOperationDone = true;

		switch(m_gis_state)
		{
		case GisCoordinate:
			{
				//getDynamicPoint(point);
				m_pointsInLine.clear();
				pickAndAppendPoint(point);
				ShowMessage();
			}
			break;

		case GisDistance:
		case GisArea:
		case GisWaterArea:
			{
				ShowMessage();
			}
			break;

		case GisVolume:
			{
				if(btm==FALSE)
				{
					MousePoint(point);
					getDynamicPoint(point);
					btm=TRUE;
				}
				else
				{

					getDynamicPoint(point);
					ShowMessage();
					btm=FALSE;
				}
			}
			break;

		default:
			break;
		}

		m_gis_state=GisNone;
		vgKernel::InputSystem::getSingleton().setDefaultStatus();


#else
		{

			if (m_gis_state==GisEditVertexString)//如果是编辑状态的话
			{	
				assert(0);
				//CurrentVertexStringPtr=NULL;
				//m_gis_state=GisNone;
				//SelectedPoint=NULL;
				//vgKernel::InputSystem::getSingleton().setDefaultStatus();
				return;
			}

			if (m_gis_state==GisAddVertexString||m_gis_state==GisTerLeveling)
			{
				assert(0);



				return;
			}

			if (m_gis_state==GisCoordinate)
			{
				getDynamicPoint(point);
				ShowMessage();
			}
			if (m_gis_state==GisDistance||m_gis_state==GisArea)
			{	
				ShowMessage();
			}
			if (m_gis_state==GisVolume)
			{
				if(btm==FALSE)
				{
					MousePoint(point);
					getDynamicPoint(point);
					btm=TRUE;
				}
				else
				{

					getDynamicPoint(point);
					ShowMessage();
					btm=FALSE;
				}

			}
			//if (m_gis_state==GisTerrainLeveling)
			//{	
			//	if (gis_plane==0)
			//	{
			//		avh=0;
			//		for(int dnum=0;dnum<psnum-1;dnum++)
			//			avh+=m_pointsInLine[dnum].y;
			//		avh/=psnum;
			//		if(btm==FALSE)
			//		{
			//			MousePoint(point);
			//			btm=TRUE;
			//		}
			//		gis_plane=1;
			//	}
			//	else if (gis_plane==1)
			//	{
			//		PolyTerPlane(psnum,m_pointsInLine);
			//	}

			//}
			//if (gis_state>50&&gis_state<54)
			if (m_gis_state==GisWaterArea)//这个先这么写着，一会再改
				ShowMessage();


		}
#endif

	}
	//----------------------------------------------------------------
	void GIS3D::GisMsMv(CPoint point)
	{
#if 1

		getDynamicPoint(point);

#else
		{

			if (m_gis_state==GisEditVertexString)
			{
				//if(SelectedPoint)
				//	*SelectedPoint=Trans2DTo3D(point);
				return;
			}
			if (m_gis_state==GisAddVertexString||m_gis_state==GisTerLeveling&&btm==false)
			{
				getDynamicPoint(point);
				return;
			}
			bMouseMove=TRUE;
			//if(gis_state<50&&gis_state>=1)
			if (m_gis_state>=GisCoordinate&&m_gis_state<=GisWaterArea\
				||m_gis_state>=GisP2PVisibility&&m_gis_state<=GisSection)/*GisTerrainLeveling*/
			{
				if(gis_ss==FALSE)
				{	
					if (btm==FALSE)
					{
						if(m_gis_state==GisCoordinate)
							getDynamicPoint(point);
						else 
							MousePoint(point);			

					}
					else if(gis_tt==TRUE);
					else 	
						getDynamicPoint(point);
				}
			}
			//暂时屏蔽，以后再改
			//if(gis_state==52)
			//{
			//	int oldMouseY = newMouseY;
			//	newMouseY = point.y;
			//	if ((newMouseY - oldMouseY) > 0)       // mouse move  up
			//		WaterHeight -= 0.2f;
			//	else if ((newMouseY - oldMouseY) < 0)   // mouse move  down
			//		WaterHeight += 0.20f;
			//}

			if(gis_cut==3||gis_cut==4)
			{
				gis_cut=4;
				ThreePoints(point);
			}

		}
#endif

	}

	//----------------------------------------------------------------
	void GIS3D::pickAndAppendPoint(CPoint point)
	{
		vgKernel::Vec3 tempVec = vgKernel::Math::
			trans2DPointTo3DVec(point.x, point.y);

		m_pointsInLine.push_back( tempVec );

#if 0
		glPushMatrix();
		int ViewPort[4],winy;
		GLdouble ModelView[16];
		GLdouble Projection[16];
		GLfloat winx,winz;
		GLdouble vrx,vry, vrz;

		glGetIntegerv(GL_VIEWPORT,ViewPort);
		winx = (float)point.x;
		winy = ViewPort[3] - point.y;
		glGetDoublev(GL_MODELVIEW_MATRIX,ModelView);
		glGetDoublev(GL_PROJECTION_MATRIX,Projection);
		glReadPixels(point.x,winy,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&winz);
		gluUnProject((GLdouble)winx,(GLdouble)winy,(GLdouble)winz,
			ModelView,Projection,ViewPort,
			&vrx,&vry,&vrz);
		/*m_pointsInLine[psnum].x = (float) vrx;
		m_pointsInLine[psnum].y = (float) vry;
		m_pointsInLine[psnum].z = (float) vrz;

		psnum++;*/
		dotsInLine.push_back( vgKernel::Vec3(vrx, vry, vrz) );

		glPopMatrix();
#endif
	}
	//----------------------------------------------------------------
	void GIS3D::OnePoint(CPoint point)
	{
#if 1
		m_pointsInLine.clear();

		pickAndAppendPoint(point);
#else
		{
			glPushMatrix();
			int ViewPort[4],winy;
			GLdouble ModelView[16];
			GLdouble Projection[16];
			GLfloat winx,winz;
			GLdouble vrx,vry, vrz;

			glGetIntegerv(GL_VIEWPORT,ViewPort);
			winx = (float)point.x;
			winy = ViewPort[3] - point.y;
			glGetDoublev(GL_MODELVIEW_MATRIX,ModelView);
			glGetDoublev(GL_PROJECTION_MATRIX,Projection);
			glReadPixels(point.x,winy,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&winz);
			gluUnProject((GLdouble)winx,(GLdouble)winy,(GLdouble)winz,
				ModelView,Projection,ViewPort,
				&vrx,&vry,&vrz);

			m_pointsInLine.clear();
			m_pointsInLine.push_back( vgKernel::Vec3(vrx, vry, vrz) );

			glPopMatrix();
		}
#endif

	}
	//----------------------------------------------------------------
	void GIS3D::ThreePoints(CPoint point)
	{
		vgKernel::Vec3 tempVec = vgKernel::Math::
			trans2DPointTo3DVec(point.x, point.y);
		tempVec.y  = WaterHeight;

		m_pointsInLine.resize(1);

		vgKernel::Vec3 firstVec(m_pointsInLine[0]), otherVec(tempVec);

		otherVec.z = firstVec.z;
		m_pointsInLine.push_back(otherVec);

		otherVec.z = tempVec.z;
		m_pointsInLine.push_back(otherVec);

		otherVec.x = firstVec.x;
		m_pointsInLine.push_back(otherVec);

#if 0
		glPushMatrix();
		int ViewPort[4],winy;
		GLdouble ModelView[16];
		GLdouble Projection[16];
		GLfloat winx,winz;
		GLdouble vrx,vry, vrz;

		glGetIntegerv(GL_VIEWPORT,ViewPort);
		winx = (float)point.x;
		winy = ViewPort[3] - point.y;
		glGetDoublev(GL_MODELVIEW_MATRIX,ModelView);
		glGetDoublev(GL_PROJECTION_MATRIX,Projection);
		glReadPixels(point.x,winy,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&winz);
		gluUnProject((GLdouble)winx,(GLdouble)winy,(GLdouble)winz,
			ModelView,Projection,ViewPort,
			&vrx,&vry,&vrz);

		dotsInLine.resize(1);

		vgKernel::Vec3 tempVec(vrx, WaterHeight, vrz);
		vgKernel::Vec3 firstVec(dotsInLine[0]);

		tempVec.z = firstVec.z;
		dotsInLine.push_back(tempVec);

		tempVec.z = vrz;
		dotsInLine.push_back(tempVec);

		tempVec.x = firstVec.x;
		dotsInLine.push_back(tempVec);

		/*dotsInLine[1].x=(float) vrx;
		dotsInLine[1].y=WaterHeight;
		dotsInLine[1].z=dotsInLine[0].z;

		dotsInLine[2].x=(float) vrx;
		dotsInLine[2].y=WaterHeight;
		dotsInLine[2].z=(float) vrz;

		dotsInLine[3].x=dotsInLine[0].x;
		dotsInLine[3].y=WaterHeight;
		dotsInLine[3].z=(float) vrz;*/

		glPopMatrix();

#endif

	}	
	//----------------------------------------------------------------
	void GIS3D::MousePoint(CPoint point)
	{
#if 1		
		pickAndAppendPoint(point);
#else
		glPushMatrix();
		int ViewPort[4],winy;
		GLdouble ModelView[16];
		GLdouble Projection[16];
		GLfloat winx,winz;
		GLdouble vrx,vry, vrz;

		glGetIntegerv(GL_VIEWPORT,ViewPort);
		winx = (float)point.x;
		winy = ViewPort[3] - point.y;
		glGetDoublev(GL_MODELVIEW_MATRIX,ModelView);
		glGetDoublev(GL_PROJECTION_MATRIX,Projection);
		glReadPixels(point.x,winy,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&winz);
		gluUnProject((GLdouble)winx,(GLdouble)winy,(GLdouble)winz,ModelView,Projection,ViewPort,&vrx,&vry,&vrz);
		m_pointsInLine[psnum].x = (float) vrx;
		m_pointsInLine[psnum].y = (float) vry;
		m_pointsInLine[psnum].z = (float) vrz;
		glPopMatrix();
#endif

	}
	//----------------------------------------------------------------
	void GIS3D::getDynamicPoint(CPoint point)
	{
#if 1
		m_pointDynamic = vgKernel::Math::
			trans2DPointTo3DVec(point.x, point.y);

#else

		glPushMatrix();
		int ViewPort[4],winy;
		GLdouble ModelView[16];
		GLdouble Projection[16];
		GLfloat winx,winz;
		GLdouble vrx,vry, vrz;

		glGetIntegerv(GL_VIEWPORT,ViewPort);
		winx = (float)point.x;
		winy = ViewPort[3] - point.y;
		glGetDoublev(GL_MODELVIEW_MATRIX,ModelView);
		glGetDoublev(GL_PROJECTION_MATRIX,Projection);
		glReadPixels(point.x,winy,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&winz);
		gluUnProject((GLdouble)winx,(GLdouble)winy,(GLdouble)winz,ModelView,Projection,ViewPort,&vrx,&vry,&vrz);
		m_endPoint.x = (float) vrx;
		m_endPoint.y = (float) vry;
		m_endPoint.z = (float) vrz;
		glPopMatrix();
#endif

	}

	//----------------------------------------------------------------
	float  GIS3D::getDistance()
	{
		float distance=0;
		int dnum;
		for(dnum=0;dnum<m_pointsInLine.size()-1;dnum++)
			distance+=calcdist(m_pointsInLine[dnum],m_pointsInLine[dnum+1]);

		return distance;
	}
	//----------------------------------------------------------------
	float  GIS3D::getArea()
	{	
		float totalarea=0;
		totalarea = areaxz(/*psnum, m_pointsInLine*/);

		return totalarea;	
	}

	//----------------------------------------------------------------
	double  GIS3D::getVolume()
	{
		// 待整理
		return 0;
#if 0
		float totalarea=0;
		double  volum=0;
		float	height=fabs(m_endPoint.y-dotsInLine[psnum].y);
		totalarea=areaxz(/*psnum, dotsInLine*/);
		volum=totalarea*height;

		return volum;
#endif	
	
	}
	//----------------------------------------------------------------
	void GIS3D::PreCalculation( )
	{
	}

	
	//----------------------------------------------------------------
	float GIS3D::calcdist(vgKernel::Vec3 v1,vgKernel::Vec3 v2)
	{	
		float a,b,c;
		a=v1.x-v2.x;b=v1.y-v2.y;c=v1.z-v2.z;
		return sqrt(a*a+b*b+c*c);
	}
	//----------------------------------------------------------------
	float GIS3D::detxz(vgKernel::Vec3 p0,vgKernel::Vec3 p1,vgKernel::Vec3 p2)   //根据叉积计算三点组成的面积.
	{ 
		return (p1.x-p0.x)*(p2.z-p0.z)-(p1.z-p0.z)*(p2.x-p0.x);
	}
	//----------------------------------------------------------------
	float GIS3D::detxy(vgKernel::Vec3 p0,vgKernel::Vec3 p1,vgKernel::Vec3 p2)   //根据叉积计算三点组成的面积.
	{ 
		return (p1.x-p0.x)*(p2.y-p0.y)-(p1.y-p0.y)*(p2.x-p0.x);
	}
	//----------------------------------------------------------------
	float GIS3D::detyz(vgKernel::Vec3 p0,vgKernel::Vec3 p1,vgKernel::Vec3 p2)   //根据叉积计算三点组成的面积.
	{ 
		return (p1.y-p0.y)*(p2.z-p0.z)-(p1.z-p0.z)*(p2.y-p0.y);
	}
	//----------------------------------------------------------------
	float GIS3D::areaxz(/*int n,PointsArray& p*/)   //计算所有点组成几何图形的面积
	{  
		float s=0.00;
		int i=1;
		for(;i<m_pointsInLine.size()-1;i++)
			s=s+detxz(m_pointsInLine[0],m_pointsInLine[i],m_pointsInLine[i+1]);
		return fabs(s)/2.00;
	}
	//----------------------------------------------------------------
	float GIS3D::areaxy(int n,PointsArray& p)   //计算所有点组成几何图形的面积
	{  float s=0.00;
	int i=1;
	for(;i<n-1;i++)
		s=s+detxy(p[0],p[i],p[i+1]);
	return fabs(s)/2.00;}
	//----------------------------------------------------------------
	float GIS3D::areayz(int n,PointsArray& p)   //计算所有点组成几何图形的面积
	{  float s=0.00;
	int i=1;
	for(;i<n-1;i++)
		s=s+detyz(p[0],p[i],p[i+1]);
	return fabs(s)/2.00;}
	//----------------------------------------------------------------
	int GIS3D::pdcz(PointsArray& p)
	{	vgKernel::Vec3 v1=p[1]-p[0];
	vgKernel::Vec3 v2=p[2]-p[0];
	vgKernel::Vec3 face=v1-v2;
	face.normalise();
	if(fabs(face.y)<0.01)	//垂直于 xz大地平面
		if(fabs(face.z)<0.01)
			return 1;//且垂直于 xy平面
		else return 2;
	else return 0;

	}
	//----------------------------------------------------------------
	float GIS3D::mycos(int a,PointsArray& p)
	{
		vgKernel::Vec3 v1=p[1]-p[0];
		vgKernel::Vec3 v2=p[2]-p[0];
		vgKernel::Vec3 face=v1-v2;
		face.normalise();
		vgKernel::Vec3 vxy,vxz,vyz;
		vxy.x=0;vxy.y=0;vxy.z=1.0;
		vxz.x=0;vxy.y=1.0;vxy.z=0;
		vyz.x=1.0;vyz.y=0;vyz.z=0;
		float cosa;

		if(a==1)
		{	cosa= 1.0;}
		if(a==2)//只垂直于 xz地平面，求与xy平面夹角余弦
		{vgKernel::Vec3 c=vxy-face;
		c.normalise();

		float l=c.length ();
		cosa=1-l*l/2.0;
		cosa=fabs(cosa);
		}
		if(a==0)//一般倾斜面，求与xz平面夹角余弦
		{vgKernel::Vec3 c=vxz-face;
		c.normalise();
		float l=c.length ();
		cosa=1-l*l/2.0;
		cosa=fabs(cosa);}
		return cosa;			
	}
	//----------------------------------------------------------------
	float GIS3D::area(int n,PointsArray& p)   //综合计算各种面积
	{  ///////////////////////////
		//分类讨论限定算法
		///////////////////////////
		float s=0.0;

		if(pdcz(p)==0)
		{
			s=areaxz(/*n, p*/)/mycos(0, p);
		}
		else if(pdcz(p)==2)
		{
			s=areaxy(n, p)/mycos(2, p);
		}
		else if(pdcz(p)==1)
		{
			s=areayz(n, p)/mycos(1, p);
		}
		return s;
	}
	//----------------------------------------------------------------
	float GIS3D::hailun(vgKernel::Vec3 a,vgKernel::Vec3 b,vgKernel::Vec3 c)
	{	
		vgKernel::Vec3 aa,bb,cc;
		float la,lb,lc;
		aa=(a-b);bb=b-c;cc=a-c;
		la=aa.length();
		lb=bb.length();
		lc=cc.length();
		float p=(la+lb+lc)/2;
		float s=sqrt(p*(p-la)*(p-lb)*(p-lc));
		return  s;

	}
	//----------------------------------------------------------------
	bool GIS3D::dmn(vgKernel::Vec3 m[3],vgKernel::Vec3 p1)//重新用海伦公式面积准则判定好了，这样只需要求几个罢了
	{
		if(fabs(hailun(m[0],m[1],m[2])-(hailun(p1,m[1],m[2])+hailun(m[0],p1,m[2])+hailun(m[0],m[1],p1)))<0.01)
		{
			return TRUE;
		}
		else 
			return FALSE;
	}

	//----------------------------------------------------------------
	float GIS3D::dmjl(vgKernel::Vec3 m[3],vgKernel::Vec3 p1)//点面的距离，需要
		//先求系数，用到行列式！
		//｜Ax+By+Cz+D｜除以跟号下(A*A+B*B+C*C)
	{	//设平面方程是ax+by+cz=1;ax+by+cz-1=0
		float aa,bb,cc,mm,a,b,c,distance;
		mm=m[0].x*(m[1].y*m[2].z-m[1].z*m[2].y)
			+m[0].y*(m[1].z*m[2].x-m[1].x*m[2].z)
			+m[0].z*(m[1].x*m[2].y-m[1].y*m[2].x);
		aa=1*(m[1].y*m[2].z-m[1].z*m[2].y)
			+m[0].y*(m[1].z*1-1*m[2].z)
			+m[0].z*(1*m[2].y-m[1].y*1);
		bb=m[0].x*(1*m[2].z-m[1].z*1)
			+1*(m[1].z*m[2].x-m[1].x*m[2].z)
			+m[0].z*(m[1].x*1-1*m[2].x);
		cc=m[0].x*(m[1].y*1-1*m[2].y)
			+m[0].y*(1*m[2].x-m[1].x*1)
			+1*(m[1].x*m[2].y-m[1].y*m[2].x);
		a=aa/mm;
		b=bb/mm;
		c=cc/mm;
		distance=fabs(a*p1.x+b*p1.y+c*p1.z-1)/(sqrt(a*a+b*b+c*c));
		return distance;

	}
	//----------------------------------------------------------------
	bool GIS3D::tcpd(vgKernel::Vec3 m[3],vgKernel::Vec3 p1,vgKernel::Vec3 p2)//同侧判定，依赖于dmjl
	{		

		float l1,l2,l3,ml;
		l1=dmjl(m,p1);
		l2=dmjl(m,p2);
		l3=sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y)+(p1.z-p2.z)*(p1.z-p2.z));

		vgKernel::Vec3 v,face;
		v=p1-p2;
		v.normalise();
		vgKernel::Vec3 v1=m[1]-m[0];
		vgKernel::Vec3 v2=m[2]-m[0];
		face=v1.crossProduct(v2);
		face.normalise();
		vgKernel::Vec3 v0=v-face;
		float len= v0.length();
		float cosa=1-len*len/2;
		cosa=fabs(cosa);
		if(l1>l2)ml=l1;
		else ml=l2;
		////////////////////////
		//新的判定方法!!
		vgKernel::Vec3 vv1=p1-m[0];
		vgKernel::Vec3 vv2=p2-m[0];
		float xx=(vv1.x*face.x+vv1.y*face.y+vv1.z*face.z)*(vv2.x*face.x+vv2.y*face.y+vv2.z*face.z);
		if(((l3*cosa)>=ml)&&(xx<0)&&(l1>0.03&&l2>0.03))//没法！
			//两侧返回
		{	
			return FALSE;
		}
		else 
		{	
			return TRUE;
		}
	}
	//----------------------------------------------------------------
	bool GIS3D::dyzdpd(vgKernel::Vec3 m[3],vgKernel::Vec3 p1,vgKernel::Vec3 p2)//遮挡判定函数
	{	
		if(tcpd(m,p1,p2)==TRUE)
			return FALSE;//同侧必不遮挡
		else//两侧有可能遮挡,两侧的情况先求交点，然后判定交点是否在三角面内
		{		
			float aa,bb,cc,mm,a1,b1,c1,d1;//先求平面方程
			mm=m[0].x*(m[1].y*m[2].z-m[1].z*m[2].y)
				+m[0].y*(m[1].z*m[2].x-m[1].x*m[2].z)
				+m[0].z*(m[1].x*m[2].y-m[1].y*m[2].x);
			aa=1*(m[1].y*m[2].z-m[1].z*m[2].y)
				+m[0].y*(m[1].z*1-1*m[2].z)
				+m[0].z*(1*m[2].y-m[1].y*1);
			bb=m[0].x*(1*m[2].z-m[1].z*1)
				+1*(m[1].z*m[2].x-m[1].x*m[2].z)
				+m[0].z*(m[1].x*1-1*m[2].x);
			cc=m[0].x*(m[1].y*1-1*m[2].y)
				+m[0].y*(1*m[2].x-m[1].x*1)
				+1*(m[1].x*m[2].y-m[1].y*m[2].x);
			a1=aa/mm;
			b1=bb/mm;
			c1=cc/mm;
			d1=1;

			float a2,b2,c2,d2,a3,b3,c3,d3;
			a2=(p2.y-p1.y);
			b2=-(p2.x-p1.x);
			c2=0;
			d2=(p2.y-p1.y)*p1.x-(p2.x-p1.x)*p1.y;
			a3=(p2.z-p1.z);
			b3=0;
			c3=-(p2.x-p1.x);//刚刚修改过来，添加了负号！！
			d3=(p2.z-p1.z)*p1.x-(p2.x-p1.x)*p1.z;
			float x0,y0,z0,nn,xx,yy,zz;	
			nn=a1*(b2*c3-b3*c2)+b1*(c2*a3-c3*a2)+c1*(a2*b3-a3*b2);//应该对
			xx=d1*(b2*c3-b3*c2)+b1*(c2*d3-c3*d2)+c1*(d2*b3-d3*b2);
			yy=a1*(d2*c3-d3*c2)+d1*(c2*a3-c3*a2)+c1*(a2*d3-a3*d2);
			zz=a1*(b2*d3-b3*d2)+b1*(d2*a3-d3*a2)+d1*(a2*b3-a3*b2);//应该对
			x0=xx/nn;y0=yy/nn;z0=zz/nn;
			vgKernel::Vec3 jd;
			jd.x=x0;jd.y=y0;jd.z=z0;

			return dmn(m,jd)&&(dmjl(m,p2)>5);
		}

	}
	//----------------------------------------------------------------
	bool GIS3D::zdpd(vgKernel::Vec3 p1,vgKernel::Vec3 p2,float a,float b,float c)//遍历各个面的遮挡判定函数
	{
		return FALSE;
	}

	//----------------------------------------------------------------
	void GIS3D::KeyBDWater()
	{	 
	}

	//----------------------------------------------------------------
	void GIS3D::renderWaterSurface()//辅助GisRender()
	{

	}
	//----------------------------------------------------------------
	float GIS3D::getWaterArea( )
	{
		float v=0; 
		return v;
	}
	//----------------------------------------------------------------
	float GIS3D::getSoilVolume( )
	{
		float v=0;
		return v;
	}
	//----------------------------------------------------------------
	float GIS3D::getWaterVolume()
	{
		float v=0;
		return v;

	}
	//----------------------------------------------------------------
	bool GIS3D:: seeornot(vgKernel::Vec3 p1,vgKernel::Vec3 p2)
	{
		PreCalculation();
		float eyeheight=0,landheight=0;
		if (fabs((m_pointsInLine[1].z - m_pointsInLine[0].z) / ( m_pointsInLine[1].x - m_pointsInLine[0].x))>=1)
			for(int i=0;i<hjmnum;i++)
			{
				eyeheight=(m_pointsInLine[1].y+i*(m_pointsInLine[0].y-m_pointsInLine[1].y)/hjmnum);
				landheight=m_pointsInLine[1].z >m_pointsInLine[0].z? zz[hjmnum-1-i]:zz[i];
				if(eyeheight<landheight)
					return TRUE;
			}
		else
			for(int i=0;i<hjmnum;i++)
			{
				eyeheight=(m_pointsInLine[1].y+i*(m_pointsInLine[0].y-m_pointsInLine[1].y)/hjmnum);
				landheight=m_pointsInLine[1].x >m_pointsInLine[0].x? zz[hjmnum-1-i]:zz[i];
				if(eyeheight<landheight)
					return TRUE;
			}
			return FALSE;
	}


	//----------------------------------------------------------------
	void GIS3D:: renderTT()
	{
		glColor3f(100,100,0);
		if(hjm==TRUE)//横截面111
		{
			if (fabs((m_pointsInLine[1].z - m_pointsInLine[0].z) / ( m_pointsInLine[1].x - m_pointsInLine[0].x))>=1)
			{ 

				glBegin(GL_LINE_STRIP);//POLYGON
				for(int i=0;i<hjmnum;i++)//横截面的点数
					glVertex3f(m_pointsInLine[1].x+i*(m_pointsInLine[0].x-m_pointsInLine[1].x)/hjmnum,
					m_pointsInLine[1].z >m_pointsInLine[0].z? zz[hjmnum-1-i]:
					zz[i],m_pointsInLine[1].z+i*(m_pointsInLine[0].z-m_pointsInLine[1].z)/hjmnum);
				glEnd();
			}
			else
			{glColor3f(0,0,100);
			glBegin(GL_LINE_STRIP);//POLYGON				
			for(int i=0;i<hjmnum;i++)
				glVertex3f(m_pointsInLine[1].x+i*(m_pointsInLine[0].x-m_pointsInLine[1].x)/hjmnum,
				m_pointsInLine[1].x >m_pointsInLine[0].x? zz[hjmnum-1-i]:zz[i],
				m_pointsInLine[1].z+i*(m_pointsInLine[0].z-m_pointsInLine[1].z)/hjmnum);//zz[hjmnum-1-i]
			glEnd();
			}
		}

	}

	//----------------------------------------------------------------
#if 0
	vgKernel::Vec3 GIS3D::Trans2DTo3D(CPoint &point)
	{
		GLint viewport[4];
		GLdouble modelview[16];
		GLdouble projection[16];
		GLfloat winX,winY,winZ;
		GLdouble object_x,object_y,object_z;

		glGetIntegerv(GL_VIEWPORT, viewport);
		winX=(float)point.x;//OGL中的窗口x坐标
		winY=(float)viewport[3]-(float)point.y - 1.0f;//OGL中的窗口y坐标


		glGetDoublev(GL_MODELVIEW_MATRIX, modelview);//视图矩阵
		glGetDoublev(GL_PROJECTION_MATRIX, projection);//投影矩阵


		glReadPixels(point.x,//x坐标
			int(winY),//y坐标
			1,1,//读取一个像素
			GL_DEPTH_COMPONENT,//获得深度信息
			GL_FLOAT,//数据类型为浮点型
			&winZ);//获得的深度值保存在winZ中



		gluUnProject((GLdouble)winX,
			(GLdouble)winY,
			(GLdouble)winZ,
			modelview,
			projection,
			viewport,
			&object_x,
			&object_y,
			&object_z);



		return vgKernel::Vec3(object_x,object_y,object_z);

	}

	//----------------------------------------------------------------
	void GIS3D::PolyTerPlane(int num, vgKernel::Vec3* pos)
	{

		float vvv=0;
		vgKernel::Vec2 _many_vector2[50];
		for(int an=0;an<num;an++)
		{_many_vector2[an].x=pos[an].x;
		_many_vector2[an].y=pos[an].z;
		}
		vgMath::PointInPolygon pip( num, _many_vector2 );
		float minz=_many_vector2[0].y,maxz=_many_vector2[0].y,minx=_many_vector2[0].x,maxx=_many_vector2[0].x;
		for(int an=0;an<num;an++)
		{
			if(minz>_many_vector2[an].y)minz=_many_vector2[an].y;
			if(maxz<_many_vector2[an].y)maxz=_many_vector2[an].y;
			if(minx>_many_vector2[an].x)minx=_many_vector2[an].x;
			if(maxx<_many_vector2[an].x)maxx=_many_vector2[an].x;
		}


		for(int i = (int(minx)-demdata.vert[0][0].x)/demdata.DX; i < (int(maxx)-demdata.vert[0][0].x)/demdata.DX; i++)//-demdata->X0
		{
			for(long j = (int(minz)-demdata.vert[0][0].z)/demdata.DX; j < (int(maxz)-demdata.vert[0][0].z)/demdata.DX; j++)//-demdata->Y0
			{
				if(pip.contains(vgKernel::Vec2(demdata.vert[i][j].x,demdata.vert[i][j].z)))//多边形内部的点才需要平整
					demdata.vert[i][j].y=avh;//更新高度值！！
			}

		}
		ShowMessage();

	}
#endif

	// 活跃模块 ------------------------------------------------------
	void GIS3D::ShowMessage()
	{

		std::ostringstream msg;

		float tempResult = 0.0f;

		switch(m_gis_state)
		{
		case GisCoordinate:
			{
				assert( !m_pointsInLine.empty() );
				m_pointsInLine[0] += vgKernel::CoordSystem::getSingleton().getProjectionCoord();
#if VGK_LANG_CHS				
				msg << "所测坐标是:" ;
#else				
				msg << "3D Coordinate equals:" ;
#endif
				msg << m_pointsInLine[0].getDetails() ;
			}
			break;

		case GisDistance:
			{
				tempResult = getDistance();

#if VGK_LANG_CHS				
				msg << "所测距离是:" ;
#else				
				msg << "3D Distance equals" ;
#endif
				msg << "\n" << tempResult ;
			}
			break;

		case GisArea:
			{
				tempResult = getArea();

#if VGK_LANG_CHS				
				msg << "所测面积是:" ;
#else				
				msg << "3D Area equals" ;
#endif
				msg << "\n" << tempResult ;
			}
			break;

		case GisVolume:
			{
				tempResult = getVolume();

#if VGK_LANG_CHS				
				msg << "所测体积是:" ;
#else				
				msg << "3D Volume equals" ;
#endif
				msg << "\n" << tempResult ;
			}
			break;

		default:
			break;
		}

		MessageBox(NULL, msg.str().c_str(), "GIS分析", MB_OK);

	}
	//----------------------------------------------------------------
	void  GIS3D::renderGisElements()
	{	
#if 1

		if (_gisAnalysis)
		{
			_gisAnalysis->renderGisElements();
		}

#else
		{
			switch( m_gis_state )
			{
			case GisCoordinate:
				{
					renderPoint();
				}
				break;

			case GisDistance:
				{
					renderLine();
				}
				break;

			case GisArea:
				{
					renderPolygon();
				}
				break;

			case GisVolume:
				{
					renderBody();
				}
				break;

			case GisWaterArea:
				{
					renderWaterSurface();
				}
				break;

			case GisWaterVolume:
				{
					renderWaterBody();
				}
				break;

			case GisP2PVisibility:
				{
					renderPoint2PointVisible();
				}
				break;

			case GisSection:
				{
					renderEqualHeightLine();
				}
				break;

			default:
				break;
			}
		}
#endif


	}
	//----------------------------------------------------------------
	vgGIS3D::EGisState GIS3D::getGisState()
	{
		//return	m_gis_state;
		if (getGisAnalysis())
		{
			return	getGisAnalysis()->getGisState();
		}
		else
		{
			return	GisNone;
		}
	}


	//----------------------------------------------------------------
	bool GIS3D::setGisState( EGisState gisState )
	{
		reset();

		vgKernel::InputSystem::getSingleton().setCurrentStatus(VG_INPUTMODE_GIS);

		m_gis_state = gisState;

		return m_gis_state;
	}


	//----------------------------------------------------------------
	void GIS3D::reset()
	{
		m_gis_state=GisNone;
		gis_cut=0;
		gis_plane=0;
		//psnum=0;
		dhk=false;
		btm=FALSE;
		gis_tt=FALSE;
		gis_ss=FALSE;
		WaterHeight=0;
		hjm=FALSE;
		//SelectedPoint=NULL;
		m_gis_state=GisNone;
		//psnum=0;
		avh=0;

		m_pointsInLine.clear();
		m_bOperationDone	= false;
		m_bCloseRing		= false;

		_gisAnalysis = NULL;
	}


	//----------------------------------------------------------------
	void GIS3D::renderPoint()
	{
		// 红点
		glColor3f(100,0,0);
		renderPointsByMode(m_pointsInLine, GL_POINTS, 
			m_bOperationDone, m_bCloseRing);
	}


	//----------------------------------------------------------------
	void GIS3D::renderLine()
	{

		renderPoint();

		// 绿线
		glColor3f(0,100,0);
		renderPointsByMode(m_pointsInLine, GL_LINE_STRIP, 
			m_bOperationDone, m_bCloseRing);

	}


	//----------------------------------------------------------------
	void GIS3D::renderPolygon()
	{
		m_bCloseRing = true;
		renderLine();
	}


	//----------------------------------------------------------------
	void GIS3D::renderBody()
	{
		if (m_pointsInLine.empty() )
		{
			return;
		}

		int dnum = 0;
		glPushAttrib(GL_CURRENT_BIT);	
		glPointSize(5.0);
		glColor3f(100,0,0);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_TEXTURE_1D);
		glDisable(GL_DEPTH_TEST);

		// 
		glBegin(GL_POINTS);
		for(dnum=0;dnum<m_pointsInLine.size();dnum++)
		{
			glVertex3f(m_pointsInLine[dnum].x,m_pointsInLine[dnum].y,m_pointsInLine[dnum].z);
		}
#if 0	

		if(bMouseMove==TRUE)
		{
			glVertex3f(dotsInLine[psnum].x,dotsInLine[psnum].y,dotsInLine[psnum].z);
		}
#endif

		if(btm==TRUE)
		{
			glVertex3f(m_endPoint.x,m_endPoint.y,m_endPoint.z);
		}
		glEnd();

		//
		glColor3f(0,100,100);
		glBegin(GL_LINES);
		for(dnum=0;dnum<m_pointsInLine.size()-1;dnum++)
		{
			glVertex3f(m_pointsInLine[dnum].x,m_pointsInLine[dnum].y,m_pointsInLine[dnum].z);
			glVertex3f(m_pointsInLine[dnum+1].x,m_pointsInLine[dnum+1].y,m_pointsInLine[dnum+1].z);
		}
#if 0	

		if(bMouseMove==TRUE&&(psnum>1))
		{
			glVertex3f(dotsInLine[dnum+1].x,dotsInLine[dnum+1].y,dotsInLine[dnum+1].z);
			glVertex3f(dotsInLine[0].x,dotsInLine[0].y,dotsInLine[0].z);
		}
		else
		{	
			glVertex3f(dotsInLine[dnum].x,dotsInLine[dnum].y,dotsInLine[dnum].z);
			glVertex3f(dotsInLine[0].x,dotsInLine[0].y,dotsInLine[0].z);
		}

		/*if(bMouseMove==TRUE&&psnum==1)
		{	
		glVertex3f(dotsInLine[0].x,dotsInLine[0].y,dotsInLine[0].z);
		glVertex3f(dotsInLine[psnum].x,dotsInLine[psnum].y,dotsInLine[psnum].z);
		}*/

		if(bMouseMove==TRUE&&(psnum>1))
		{
			glVertex3f(dotsInLine[psnum-1].x,dotsInLine[psnum-1].y,dotsInLine[psnum-1].z);
			glVertex3f(dotsInLine[psnum].x,dotsInLine[psnum].y,dotsInLine[psnum].z);
		}
#endif
		glEnd();

		if(btm==TRUE)
		{
			glColor3f(100,100,0);
			glBegin(GL_LINES);
			glVertex3f(m_pointsInLine[m_pointsInLine.size()-1].x,m_pointsInLine[m_pointsInLine.size()-1].y,m_pointsInLine[m_pointsInLine.size()-1].z);
			glVertex3f(m_endPoint.x,m_endPoint.y,m_endPoint.z);
			glEnd();
		}

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_1D);
		glEnable(GL_TEXTURE_2D);
		glPopAttrib();
	}


	//----------------------------------------------------------------
	void GIS3D::renderWaterBody()
	{
		if (m_pointsInLine.empty() )
		{
			return;
		}

		if(gis_cut>2)
		{
			glBegin(GL_LINES);
			glVertex3f(m_pointsInLine[0].x,m_pointsInLine[0].y+5,m_pointsInLine[0].z);
			glVertex3f(m_pointsInLine[1].x,m_pointsInLine[1].y+5,m_pointsInLine[1].z);
			glVertex3f(m_pointsInLine[1].x,m_pointsInLine[1].y+5,m_pointsInLine[1].z);
			glVertex3f(m_pointsInLine[2].x,m_pointsInLine[2].y+5,m_pointsInLine[2].z);
			glVertex3f(m_pointsInLine[2].x,m_pointsInLine[2].y+5,m_pointsInLine[2].z);
			glVertex3f(m_pointsInLine[3].x,m_pointsInLine[3].y+5,m_pointsInLine[3].z);
			glVertex3f(m_pointsInLine[3].x,m_pointsInLine[3].y+5,m_pointsInLine[3].z);
			glVertex3f(m_pointsInLine[0].x,m_pointsInLine[0].y+5,m_pointsInLine[0].z);
			glEnd();
		}
		renderWaterSurface();
	}


	//----------------------------------------------------------------
	void GIS3D::renderPoint2PointVisible()
	{
		if (m_pointsInLine.empty() )
		{
			return;
		}

		glEnable(GL_DEPTH_TEST);

		glPointSize(5.0);
		glColor3f(0,1000,0);


		// Points
		glBegin(GL_POINTS);

		for(int dnum=0;dnum<m_pointsInLine.size();dnum++)
		{
			glVertex3f(m_pointsInLine[dnum].x,m_pointsInLine[dnum].y,m_pointsInLine[dnum].z);
		}
#if 0	

		if(bMouseMove==TRUE)
		{
			glVertex3f(dotsInLine[psnum].x,dotsInLine[psnum].y,dotsInLine[psnum].z);
		}
#endif

		glEnd();			


		// Lines
		glColor3f(100,0,0);
		glBegin(GL_LINES);

		for(int dnum=0;dnum<m_pointsInLine.size()-1;dnum++)
		{	
			glVertex3f(m_pointsInLine[dnum].x,m_pointsInLine[dnum].y,m_pointsInLine[dnum].z);		
			glVertex3f(m_pointsInLine[dnum+1].x,m_pointsInLine[dnum+1].y,m_pointsInLine[dnum+1].z);
		}
#if 0	

		if(bMouseMove==TRUE&&psnum==1)
		{	
			glVertex3f(dotsInLine[0].x,dotsInLine[0].y,dotsInLine[0].z);
			glVertex3f(dotsInLine[psnum].x,dotsInLine[psnum].y,dotsInLine[psnum].z);
		}

		if(bMouseMove==TRUE&&(psnum==1)&&gis_ss==FALSE)
		{
			glVertex3f(dotsInLine[psnum-1].x,dotsInLine[psnum-1].y,dotsInLine[psnum-1].z);
			glVertex3f(dotsInLine[psnum].x,dotsInLine[psnum].y,dotsInLine[psnum].z);
		}
#endif

		glEnd();
		glEnable(GL_DEPTH_TEST);
	}


	//----------------------------------------------------------------
	void GIS3D::renderEqualHeightLine()
	{
		if (m_pointsInLine.empty() )
		{
			return;
		}

		{	
			glPointSize(5.0);
			glColor3f(0,1000,0);
			glBegin(GL_POINTS);
			for(int dnum=0;dnum<m_pointsInLine.size();dnum++)
			{
				glVertex3f(m_pointsInLine[dnum].x,m_pointsInLine[dnum].y,m_pointsInLine[dnum].z);
			}
#if 0	

			if(bMouseMove==TRUE)
			{
				glVertex3f(dotsInLine[psnum].x,dotsInLine[psnum].y,dotsInLine[psnum].z);
			}
#endif
			glEnd();
		}//Points

		{
			glColor3f(100,0,0);
			glBegin(GL_LINES);
			for(int dnum=0;dnum<m_pointsInLine.size()-1;dnum++)
			{	
				glVertex3f(m_pointsInLine[dnum].x,m_pointsInLine[dnum].y,m_pointsInLine[dnum].z);		
				glVertex3f(m_pointsInLine[dnum+1].x,m_pointsInLine[dnum+1].y,m_pointsInLine[dnum+1].z);
			}
#if 0	

			if(bMouseMove==TRUE&&psnum==1)
			{	
				glVertex3f(dotsInLine[0].x,dotsInLine[0].y,dotsInLine[0].z);
				glVertex3f(dotsInLine[psnum].x,dotsInLine[psnum].y,dotsInLine[psnum].z);
			}

			if(bMouseMove==TRUE&&(psnum==1)&&gis_ss==FALSE)
			{
				glVertex3f(dotsInLine[psnum-1].x,dotsInLine[psnum-1].y,dotsInLine[psnum-1].z);
				glVertex3f(dotsInLine[psnum].x,dotsInLine[psnum].y,dotsInLine[psnum].z);
			}
#endif

			glEnd();

			if(hjm==TRUE)//横截面
			{
				if (fabs((m_pointsInLine[1].z - m_pointsInLine[0].z) / ( m_pointsInLine[1].x - m_pointsInLine[0].x))>=1)
				{ 
					glBegin(GL_LINE_STRIP);//POLYGON
					glVertex3f(m_pointsInLine[0].x,m_pointsInLine[0].y+50,m_pointsInLine[0].z);
					glVertex3f(m_pointsInLine[1].x,m_pointsInLine[0].y+50,m_pointsInLine[1].z);

					for(int i=0;i<hjmnum;i++)//横截面的点数
						glVertex3f(m_pointsInLine[1].x+i*(m_pointsInLine[0].x-m_pointsInLine[1].x)/hjmnum,
						m_pointsInLine[1].z >m_pointsInLine[0].z? m_pointsInLine[0].y+60+1*(zz[hjmnum-1-i]-zzmin):
						m_pointsInLine[0].y+60+1*(zz[i]-zzmin),
						m_pointsInLine[1].z+i*(m_pointsInLine[0].z-m_pointsInLine[1].z)/hjmnum);
					glVertex3f(m_pointsInLine[0].x,m_pointsInLine[0].y+50,m_pointsInLine[0].z);
					glEnd();
				}
				else
				{
					glColor3f(0,1,0);
					glBegin(GL_LINE_STRIP);//POLYGON
					glVertex3f(m_pointsInLine[0].x,m_pointsInLine[0].y+50,m_pointsInLine[0].z);
					glVertex3f(m_pointsInLine[1].x,m_pointsInLine[0].y+50,m_pointsInLine[1].z);
					if (m_pointsInLine[1].x >m_pointsInLine[0].x)
					{
						for(int i=0;i<hjmnum;i++)
						{
							glVertex3f(m_pointsInLine[1].x+i*(m_pointsInLine[0].x-m_pointsInLine[1].x)/hjmnum,m_pointsInLine[0].y+60+1*(zz[hjmnum-1-i]-zzmin),m_pointsInLine[1].z+i*(m_pointsInLine[0].z-m_pointsInLine[1].z)/hjmnum);
						}
					}
					else 
					{
						for(int i=0;i<hjmnum;i++)
						{
							glVertex3f(m_pointsInLine[1].x+i*(m_pointsInLine[0].x-m_pointsInLine[1].x)/hjmnum,m_pointsInLine[0].y+60+1*(zz[i]-zzmin),m_pointsInLine[1].z+i*(m_pointsInLine[0].z-m_pointsInLine[1].z)/hjmnum);
						}
						glVertex3f(m_pointsInLine[0].x,m_pointsInLine[0].y+50,m_pointsInLine[0].z);
						glEnd();
					}
				}//else
			}//if

		}//line
	}

	
	//----------------------------------------------------------------
	void GIS3D::renderPointsByMode( const PointsArray& points, int nRenderMode,
		bool bOperationDone /*= false*/, bool bCloseRing /*= false*/)
	{
		glPushMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_DEPTH_TEST);
		glPushAttrib(GL_CURRENT_BIT);
		glPointSize(3.0);

		
		glBegin(nRenderMode);
		for(PointsArray::const_iterator itr = points.begin();
			itr != points.end(); itr ++)
		{
			glVertex3fv(itr->v);
		}
		
		if ( !bOperationDone )
		{
			glVertex3fv(m_pointDynamic.v);
		}
		else if( bCloseRing )
		{
			glVertex3fv(points[0].v);
		}

		glEnd();

		
		glPopAttrib();
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		glPopMatrix();
	}

	//----------------------------------------------------------------
	bool GIS3D::setGisAnalysis( EGisState eType )
	{
		bool bDelete = false, bCreate = false;

		if( _gisAnalysis != NULL )
		{
			bDelete = true;
		}

		if ( _gisAnalysis == NULL 
			|| _gisAnalysis->getGisState() != eType )
		{
			bCreate = true;
		}

		if (bDelete)
		{
			delete _gisAnalysis;
			_gisAnalysis = NULL;
		}

		if (bCreate)
		{
			_gisAnalysis = new GisAnalysis(eType);
		}


		return true;
	}

	GisAnalysis* GIS3D::getGisAnalysis()
	{
		return _gisAnalysis;
	}

	vgGIS3D::EGisState GIS3D::getAnalysisType()
	{
		return m_gis_state;
	}
	//----------------------------------------------------------------
}//vgGIS3D命名空间结束

#endif
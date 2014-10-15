// ContourObj.cpp: implementation of the CContourObj class.
//
//////////////////////////////////////////////////////////////////////

// #include "stdafx.h"
#include <vgStableHeaders.h>
//#include "vgGIS3D\vgFrameWork.h"
#include "vgNoise\vgnContourObj.h"
/*#include "MainFrm.h"*/
//#include "vgNoise\vgFrameWorkDoc.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace vgGIS3D
{
CContourObj::CContourObj(CCurve*  pCoord, float value)
{
	ASSERT( pCoord != NULL );
	m_pCoord = pCoord;
	m_Value = value;
	//m_FillColor = RGB(255,0,0);
	m_LineColor = RGB(0,0,0);

}

CContourObj::~CContourObj()
{
	//不要在这里delete m_pCoord;
	TRACE0("CContourObj::~CContourObj()\n");
}


void CContourObj::LookUpColor(const CColorLookUpTable& clrTbl)
{//在颜色表中查找m_Value对应的颜色值
	m_LineColor = clrTbl.LookUpColor(m_Value);
}

void CContourObj::LookUpColor1(const CColorLookUpTable& clrTbl,float m_Value) //查找颜色表,设定绘制颜色 
{
	m_FillColor = clrTbl.LookUpColor(m_Value);
}


void CContourObj::Draw(CDC* pDC, const CColorLookUpTable& clrTbl,
					   float scaleRatio, float moveDeltX, float moveDeltY)
{//把等值线区域居中显示在rt中

	//1.在绘制之前先查找好颜色
	LookUpColor(clrTbl);

	//2.绘制等值线
	DrawContours(pDC,scaleRatio, moveDeltX, moveDeltY);

}



void CContourObj::DrawContours(CDC* pDC, float scaleRatio, float moveDeltX, float moveDeltY)
{
	ASSERT( m_pCoord!=NULL );

	int nSize = m_pCoord->GetSize(); //为一条等值线的大小
	ASSERT(nSize>=2); 

	CPen pen(PS_SOLID,1,RGB(0,0,0));//m_LineColor
	CPen *pOldPen=pDC->SelectObject(&pen);



	pDC->MoveTo(int(m_pCoord->GetAt(0).x/scaleRatio + moveDeltX),
		int(m_pCoord->GetAt(0).y/scaleRatio + moveDeltY));

	for(int i=1;i<nSize;i++)//
	{//坐标映射变换(先比例变换再平移)

		pDC->LineTo(int(m_pCoord->GetAt(i).x/scaleRatio+moveDeltX),
			int(m_pCoord->GetAt(i).y/scaleRatio+moveDeltY));
	}
	pDC->SelectObject(pOldPen);

	//	CCurve *m_curve1 = new CCurve;

}

void CContourObj::FillContours(CDC* pDC,int j, float scaleRatio, float moveDeltX, float moveDeltY,const CColorLookUpTable& clrTbl)
{
	//ASSERT( m_pCoord!=NULL );

	//int nSize = m_pCoord->GetSize(); //为一条等值线的大小　点数
	//ASSERT(nSize>=2); 
	//CPoint *pt = new CPoint[nSize+2];//,pt1[1000];//;
	////	pt = pt1;
	//CvgFrameWorkApp *theApp =(CvgFrameWorkApp *) AfxGetApp();
	//CMainFrame *pFrame = (CMainFrame *)theApp->m_pMainWnd;
	//CvgFrameWorkDoc *pdoc =(CvgFrameWorkDoc *) pFrame->GetActiveDocument();
	//float **m_ppGridData = pdoc->m_GeoData.GetGridData();
	//float zmax,zmin,cols,rows,xmin,xmax,ymin,ymax;
	//zmax = pdoc->m_GeoData.GetDataInfo().zMax;
	//zmin = pdoc->m_GeoData.GetDataInfo().zMin;
	//rows = pdoc->m_GeoData.GetDataInfo().rows;
	//cols = pdoc->m_GeoData.GetDataInfo().cols;
	//xmax = pdoc->m_GeoData.GetDataInfo().xMax;
	//xmin = pdoc->m_GeoData.GetDataInfo().xMin;
	//ymax = pdoc->m_GeoData.GetDataInfo().yMax;
	//ymin = pdoc->m_GeoData.GetDataInfo().yMin;

	//switch(j)
	//{
	//case 0: //起点在最小值，终点在最右侧
	//	{
	//		if( fabs(m_pCoord->GetAt(0).x - xmin)<0.0001 && fabs(m_pCoord->GetAt(nSize-1).x - xmax)<0.0001)
	//		{
	//			for ( int i=0; i<nSize; i++)
	//			{
	//				/*
	//				pt1[i].x = m_pCoord->GetAt(i).x/scaleRatio+moveDeltX;
	//				pt1[i].y = m_pCoord->GetAt(i).y/scaleRatio+moveDeltY;*/
	//				pt->x = m_pCoord->GetAt(i).x/scaleRatio+moveDeltX;
	//				pt->y = m_pCoord->GetAt(i).y/scaleRatio+moveDeltY;
	//				pt++;
	//			}
	//			pt->x = xmax/scaleRatio+moveDeltX;
	//			pt->y = ymax/scaleRatio+moveDeltY;
	//			pt++;
	//			pt->x = xmin/scaleRatio+moveDeltX;
	//			pt->y = ymax/scaleRatio+moveDeltY;
	//			/*pt1[nSize+1].x = 0/scaleRatio+moveDeltX; 
	//			pt1[nSize+1].y = ymax/scaleRatio+moveDeltY; 
	//			pt1[nSize].x = xmax/scaleRatio+moveDeltX; 
	//			pt1[nSize].y = ymax/scaleRatio+moveDeltY; */
	//			//CGeoPoint pt(xmax/scaleRatio+moveDeltX,moveDeltY);
	//			pt = pt-nSize-1;

	//			// 根据起点坐标与网格数据的比较来确定绘制颜色
	//			int icoord, jcoord;
	//			jcoord = 0;
	//			icoord = m_pCoord->GetAt(0).y/(ymax-ymin)*(rows-1); //49 为rows-1
	//			float m ,m1;
	//			m	= m_ppGridData[icoord][jcoord];
	//			m1	= m_ppGridData[icoord+1][jcoord];
	//			COLORREF m_color,m_color1;
	//			if(m_Value>=m && m_Value<m1)
	//			{
	//				float m_colorfind;
	//				m_colorfind = m_Value+pdoc->inc ;
	//				if (m_colorfind>zmax)
	//				{
	//					m_colorfind = m_Value;
	//				}
	//				LookUpColor1(clrTbl, m_colorfind);
	//				m_color = m_FillColor;
	//				LookUpColor1(clrTbl, m_Value);
	//				m_color1 = m_FillColor;

	//			}
	//			else
	//			{
	//				LookUpColor1(clrTbl, m_Value);
	//				m_color = m_FillColor;
	//				float m_colorfind;
	//				m_colorfind = m_Value+pdoc->inc ;
	//				if( icoord == 0)
	//					m_colorfind = m_Value-pdoc->inc  ;
	//				if (m_colorfind>zmax ||m_colorfind<zmin)
	//				{
	//					m_colorfind = m_Value;
	//				}
	//				LookUpColor1(clrTbl, m_colorfind);
	//				//LookUpColor1(clrTbl, m_Value+5);
	//				m_color1 = m_FillColor;
	//			}

	//			CBrush brA ,brB;
	//			brA.CreateSolidBrush(m_color);
	//			brB.CreateSolidBrush(m_color1);
	//			//brA.CreateSolidBrush(m_LineColor);
	//			//brB.CreateSolidBrush(m_LineColor);
	//			CRgn rgn,rgn1;
	//			rgn.CreatePolygonRgn(pt,nSize+2,ALTERNATE);
	//			pDC->FillRgn(&rgn,&brA);
	//			if( theApp->FirstFillLine  ==0)
	//			{
	//				pt = pt +nSize;
	//				pt->x = xmax/scaleRatio+moveDeltX;
	//				pt->y = ymin/scaleRatio+moveDeltY;
	//				pt++;
	//				pt->x = xmin/scaleRatio+moveDeltX;
	//				pt->y = ymin/scaleRatio+moveDeltY;
	//				pt = pt -nSize-1;
	//				rgn1.CreatePolygonRgn(pt,nSize+2,ALTERNATE);
	//				pDC->FillRgn(&rgn1,&brB);
	//			}
	//			theApp->FirstFillLine ++;
	//			brA.DeleteObject();
	//			brB.DeleteObject();

	//		}

	//		break;

	//	}

	//case 1:
	//	{
	//		if( (   fabs(m_pCoord->GetAt(0).x - xmin)<0.0001 && fabs(m_pCoord->GetAt(nSize-1).y - ymax)<0.0001 )
	//			||( fabs(m_pCoord->GetAt(0).y - ymax)<0.0001 && fabs(m_pCoord->GetAt(nSize-1).x - xmax)<0.0001 )
	//			||( fabs(m_pCoord->GetAt(0).x - xmax)<0.0001 && fabs(m_pCoord->GetAt(nSize-1).y - ymin)<0.0001 )
	//			||( fabs(m_pCoord->GetAt(0).y - ymin)<0.0001 && fabs(m_pCoord->GetAt(nSize-1).x - xmin)<0.0001 )
	//			)
	//		{
	//			for ( int i=0; i<nSize; i++)
	//			{
	//				pt->x = m_pCoord->GetAt(i).x/scaleRatio+moveDeltX;
	//				pt->y = m_pCoord->GetAt(i).y/scaleRatio+moveDeltY;
	//				pt++;
	//			}
	//			COLORREF m_color,m_color1;
	//			if(  fabs(m_pCoord->GetAt(0).x - xmin)<0.0001 && fabs(m_pCoord->GetAt(nSize-1).y - ymax)<0.0001 )
	//			{
	//				pt->x = xmin/scaleRatio+moveDeltX;
	//				pt->y = ymax/scaleRatio+moveDeltY;
	//				int icoord, jcoord;
	//				jcoord = 0;
	//				icoord = m_pCoord->GetAt(0).y/(ymax-ymin)*(rows-1);// 49 为rows-1
	//				float m ,m1;
	//				m	= m_ppGridData[icoord][jcoord];
	//				m1	= m_ppGridData[icoord+1][jcoord];
	//				float m_colorfind;
	//				if(m_Value>=m && m_Value<m1)
	//				{

	//					m_colorfind = m_Value+pdoc->inc ;
	//					if (m_colorfind>zmax)
	//					{
	//						m_colorfind = m_Value;
	//					}
	//					LookUpColor1(clrTbl, m_colorfind);
	//					m_color = m_FillColor;
	//				}
	//				else if (m_Value > m && m_Value==m1)
	//				{
	//					float m_colorfind;
	//					m_colorfind = m_Value+pdoc->inc ;
	//					if (m_colorfind>zmax)
	//					{
	//						m_colorfind = m_Value;
	//					}
	//					LookUpColor1(clrTbl, m_colorfind);
	//					m_color = m_FillColor;
	//				}
	//				else
	//				{
	//					float m_colorfind;
	//					m_colorfind = m_Value;
	//					LookUpColor1(clrTbl, m_colorfind);
	//					m_color = m_FillColor;
	//				}

	//			}
	//			if(  fabs(m_pCoord->GetAt(0).y - ymax)<0.0001 && fabs(m_pCoord->GetAt(nSize-1).x - xmax)<0.0001 )
	//			{
	//				pt->x = xmax/scaleRatio+moveDeltX;
	//				pt->y = ymax/scaleRatio+moveDeltY;
	//				int icoord, jcoord;
	//				icoord = rows-1;
	//				jcoord = m_pCoord->GetAt(0).x/(xmax-xmin)*(cols-1);// 49 为rows-1
	//				float m ,m1;
	//				m	= m_ppGridData[icoord][jcoord];
	//				m1	= m_ppGridData[icoord][jcoord+1];

	//				if(m_Value>m && m_Value<=m1)
	//				{
	//					float m_colorfind;
	//					m_colorfind = m_Value+pdoc->inc ;
	//					if (m_colorfind>zmax)
	//					{
	//						m_colorfind = m_Value;
	//					}
	//					LookUpColor1(clrTbl, m_colorfind);
	//					m_color = m_FillColor;
	//				}
	//				else
	//				{
	//					LookUpColor1(clrTbl, m_Value);
	//					m_color = m_FillColor;
	//				}
	//			}				
	//			if(  fabs(m_pCoord->GetAt(0).x - xmax)<0.001 && fabs(m_pCoord->GetAt(nSize-1).y - ymin)<0.001 )
	//			{
	//				pt->x = xmax/scaleRatio+moveDeltX;
	//				pt->y = ymin/scaleRatio+moveDeltY;
	//				int icoord, jcoord;
	//				jcoord = cols-1;
	//				icoord = m_pCoord->GetAt(0).y/(ymax-ymin)*(rows-1);// 49 为rows-1
	//				float m ,m1;
	//				m	= m_ppGridData[icoord][jcoord];
	//				m1	= m_ppGridData[icoord+1][jcoord];
	//				float m_colorfind;
	//				if(m_Value<=m && m_Value>m1)
	//				{

	//					m_colorfind = m_Value+pdoc->inc ;
	//					if (m_colorfind>zmax)
	//					{
	//						m_colorfind = m_Value;
	//					}

	//				}
	//				else
	//				{
	//					m_colorfind = m_Value;
	//				}
	//				LookUpColor1(clrTbl, m_colorfind);
	//				m_color = m_FillColor;
	//			}
	//			if(  fabs(m_pCoord->GetAt(0).y - ymin)<0.0001 && fabs(m_pCoord->GetAt(nSize-1).x - xmin)<0.0001 )
	//			{
	//				pt->x = xmin/scaleRatio+moveDeltX;
	//				pt->y = ymin/scaleRatio+moveDeltY;
	//				int icoord, jcoord;
	//				icoord = 0;
	//				jcoord = m_pCoord->GetAt(0).x/(xmax-xmin)*(cols-1);// 49 为rows-1
	//				float m ,m1;
	//				m	= m_ppGridData[icoord][jcoord];
	//				m1	= m_ppGridData[icoord][jcoord+1];

	//				float m_colorfind;
	//				if(m_Value<=m && m_Value>m1)
	//				{
	//					m_colorfind = m_Value+pdoc->inc ;
	//					if (m_colorfind>zmax)
	//					{
	//						m_colorfind = m_Value;
	//					}
	//				}
	//				else
	//				{
	//					m_colorfind = m_Value ;
	//				}
	//				LookUpColor1(clrTbl, m_colorfind);
	//				m_color = m_FillColor;
	//			}
	//			pt = pt-nSize;

	//			// 根据起点坐标与网格数据的比较来确定绘制颜色
	//			/*int icoord, jcoord;
	//			jcoord = 0;
	//			icoord = m_pCoord->GetAt(0).y/(ymax-ymin)*49;// 49 为rows-1
	//			float m ,m1;
	//			m	= m_ppGridData[icoord][jcoord];
	//			m1	= m_ppGridData[icoord+1][jcoord];
	//			COLORREF m_color,m_color1;
	//			if(m_Value>m && m_Value<m1)
	//			{

	//			LookUpColor1(clrTbl, m_Value+pdoc->inc);
	//			m_color = m_FillColor;

	//			}
	//			else
	//			{
	//			LookUpColor1(clrTbl, m_Value);
	//			m_color = m_FillColor;
	//			}*/

	//			CBrush brA ;
	//			brA.CreateSolidBrush(m_color);
	//			CRgn rgn;
	//			rgn.CreatePolygonRgn(pt,nSize+1,ALTERNATE);
	//			pDC->FillRgn(&rgn,&brA);
	//			theApp->FirstFillLine ++;
	//			brA.DeleteObject();
	//		}

	//		break;

	//	}
	//case 2:
	//	{
	//		if( (   fabs(m_pCoord->GetAt(0).x - xmin)<0.0001 && fabs(m_pCoord->GetAt(nSize-1).x - xmin)<0.0001 )
	//			||( fabs(m_pCoord->GetAt(0).y - ymax)<0.0001 && fabs(m_pCoord->GetAt(nSize-1).y - ymax)<0.0001 )
	//			||( fabs(m_pCoord->GetAt(0).x - xmax)<0.0001 && fabs(m_pCoord->GetAt(nSize-1).x - xmax)<0.0001 )
	//			||( fabs(m_pCoord->GetAt(0).y - ymin)<0.0001 && fabs(m_pCoord->GetAt(nSize-1).y - ymin)<0.0001 )
	//			)
	//		{
	//			COLORREF m_color,m_color1;
	//			for ( int i=0; i<nSize; i++)
	//			{
	//				pt->x = m_pCoord->GetAt(i).x/scaleRatio+moveDeltX;
	//				pt->y = m_pCoord->GetAt(i).y/scaleRatio+moveDeltY;
	//				pt++;
	//			}
	//			pt = pt-nSize;
	//			float m_colorfind;
	//			if( fabs(m_pCoord->GetAt(0).x - xmin)<0.0001 && fabs(m_pCoord->GetAt(nSize-1).x - xmin)<0.0001 )
	//			{
	//				int icoord, jcoord;
	//				jcoord = 0;
	//				icoord = m_pCoord->GetAt(0).y/(ymax-ymin)*(rows-1);// 49 为rows-1
	//				float m ,m1,m2;
	//				m	= m_ppGridData[icoord][jcoord];
	//				m1	= m_ppGridData[icoord+1][jcoord];
	//				m2 = m_ppGridData[icoord+2][jcoord];

	//				if(m_Value>=m && m_Value<m1)
	//				{

	//					m_colorfind = m_Value+pdoc->inc ;
	//					if (m_colorfind>zmax)
	//					{
	//						m_colorfind = m_Value;
	//					}
	//					LookUpColor1(clrTbl, m_colorfind);
	//					m_color = m_FillColor;
	//				}
	//				else if( m_Value == m1 && m_Value != m)
	//				{
	//					if( m1 < m2)
	//						m_colorfind = m_Value+pdoc->inc ;
	//					else
	//						m_colorfind = m_Value;
	//					LookUpColor1(clrTbl, m_colorfind);
	//					m_color = m_FillColor;

	//				}
	//				else
	//				{
	//					LookUpColor1(clrTbl, m_Value);
	//					m_color = m_FillColor;
	//				}
	//			}
	//			if(  fabs(m_pCoord->GetAt(0).y - ymax)<0.0001 && fabs(m_pCoord->GetAt(nSize-1).y - ymax)<0.0001  )
	//			{
	//				int icoord, jcoord;
	//				icoord = rows-1;
	//				jcoord = m_pCoord->GetAt(0).x/(xmax-xmin)*(cols-1);// 38 为cols-1
	//				float m ,m1, m2;
	//				m	= m_ppGridData[icoord][jcoord];
	//				m1	= m_ppGridData[icoord][jcoord+1];
	//				m2	= m_ppGridData[icoord][jcoord+2];
	//				//					float m_colorfind;
	//				if(m_Value>=m && m_Value<m1)
	//				{
	//					m_colorfind = m_Value+pdoc->inc ;
	//					if (m_colorfind>zmax)
	//					{
	//						m_colorfind = m_Value;
	//					}
	//					LookUpColor1(clrTbl, m_colorfind);
	//					m_color = m_FillColor;
	//				}
	//				else if( m_Value == m1 && m_Value != m)
	//				{
	//					if( m1 < m2)
	//						m_colorfind = m_Value+pdoc->inc ;
	//					else
	//						m_colorfind = m_Value;
	//					LookUpColor1(clrTbl, m_colorfind);
	//					m_color = m_FillColor;

	//				}
	//				else
	//				{
	//					LookUpColor1(clrTbl, m_Value);
	//					m_color = m_FillColor;
	//				}
	//			}
	//			if( fabs(m_pCoord->GetAt(0).x - xmax)<0.0001 && fabs(m_pCoord->GetAt(nSize-1).x - xmax)<0.0001 )
	//			{
	//				int icoord, jcoord;
	//				jcoord = cols-1;
	//				icoord = m_pCoord->GetAt(0).y/(ymax-ymin)*(rows-1);// 49 为rows-1
	//				float m , m1, m2;
	//				m	= m_ppGridData[icoord][jcoord];
	//				m1	= m_ppGridData[icoord+1][jcoord];
	//				m2	= m_ppGridData[icoord-1][jcoord];

	//				if(m_Value>m && m_Value<=m1)
	//				{
	//					LookUpColor1(clrTbl, m_Value);
	//					m_color = m_FillColor;
	//				}
	//				else if( m_Value == m && m_Value != m1)
	//				{
	//					if( m < m2)
	//						m_colorfind = m_Value+pdoc->inc ;
	//					else
	//						m_colorfind = m_Value;
	//					LookUpColor1(clrTbl, m_colorfind);
	//					m_color = m_FillColor;
	//				}

	//				else
	//				{
	//					float m_colorfind;
	//					m_colorfind = m_Value+pdoc->inc ;
	//					if (m_colorfind>zmax)
	//					{
	//						m_color = RGB(200,0,0);
	//					}
	//					else
	//						LookUpColor1(clrTbl, m_colorfind);
	//					m_color = m_FillColor;
	//				}
	//			}
	//			if(  fabs(m_pCoord->GetAt(0).y - ymin)<0.0001 && fabs(m_pCoord->GetAt(nSize-1).y - ymin)<0.0001 )
	//			{
	//				int icoord, jcoord;
	//				icoord = 0;
	//				jcoord = m_pCoord->GetAt(0).x/(xmax-xmin)*(cols-1);// 38 为cols-1
	//				float m, m1, m2;
	//				m	= m_ppGridData[icoord][jcoord];
	//				m1	= m_ppGridData[icoord][jcoord+1];
	//				m2	= m_ppGridData[icoord][jcoord-1];

	//				if(m_Value > m && m_Value <= m1)
	//				{
	//					LookUpColor1(clrTbl, m_Value);
	//					m_color = m_FillColor;
	//				}
	//				else if( m_Value == m && m_Value != m1)
	//				{
	//					if( m < m2)
	//						m_colorfind = m_Value+pdoc->inc ;
	//					else
	//						m_colorfind = m_Value;
	//					LookUpColor1(clrTbl, m_colorfind);
	//					m_color = m_FillColor;
	//				}
	//				else
	//				{
	//					//						float m_colorfind;
	//					m_colorfind = m_Value+pdoc->inc ;
	//					if (m_colorfind>zmax)
	//					{
	//						m_color = RGB(200,0,0);
	//					}
	//					else
	//					{
	//						LookUpColor1(clrTbl, m_colorfind);
	//						m_color = m_FillColor;
	//					}
	//				}
	//			}

	//			CBrush brA ;
	//			brA.CreateSolidBrush(m_color);
	//			CRgn rgn;
	//			rgn.CreatePolygonRgn(pt,nSize,ALTERNATE);
	//			pDC->FillRgn(&rgn,&brA);
	//			theApp->FirstFillLine ++;
	//			brA.DeleteObject();
	//		}

	//		break;

	//	}	
	//case 3:
	//	{
	//		if( m_pCoord->GetAt(0).x == m_pCoord->GetAt(nSize-1).x && m_pCoord->GetAt(0).y == m_pCoord->GetAt(nSize-1).y)
	//		{
	//			COLORREF m_color,m_color1;
	//			for ( int i=0; i<nSize; i++)
	//			{
	//				pt->x = m_pCoord->GetAt(i).x/scaleRatio+moveDeltX;
	//				pt->y = m_pCoord->GetAt(i).y/scaleRatio+moveDeltY;
	//				pt++;
	//			}
	//			pt = pt-nSize;
	//			CRgn rgn;
	//			rgn.CreatePolygonRgn(pt,nSize,ALTERNATE);

	//			int icoord, jcoord;
	//			icoord = m_pCoord->GetAt(0).y/(ymax-ymin)*(rows-1);
	//			jcoord = m_pCoord->GetAt(0).x/(xmax-xmin)*(cols-1);// 38 为cols-1
	//			float m ,m1,m2,m3;
	//			m	= m_ppGridData[icoord][jcoord];
	//			m1	= m_ppGridData[icoord][jcoord+1];
	//			m2	= m_ppGridData[icoord+1][jcoord];
	//			m3	= m_ppGridData[icoord+1][jcoord+1];

	//			float x ,y,x1,y1;
	//			x = jcoord*(xmax-xmin)/(cols-1);
	//			y = icoord*(ymax-ymin)/(rows-1);
	//			x1 = (jcoord+1)*(xmax-xmin)/(cols-1);
	//			y1 = icoord*(ymax-ymin)/(rows-1);
	//			CPoint pt(x,y),pt1(x1,y1);
	//			float m_colorfind;

	//			if( m_Value>m && m_Value<m1 )
	//			{
	//				if( rgn.PtInRegion(pt) )
	//					m_colorfind = m_Value;
	//				if( rgn.PtInRegion(pt1))
	//					m_colorfind = m_Value+pdoc->inc ;
	//				if( !rgn.PtInRegion(pt) && !rgn.PtInRegion(pt1) && m2>=m_Value )
	//					m_colorfind = m_Value+pdoc->inc ;
	//				if( !rgn.PtInRegion(pt) && !rgn.PtInRegion(pt1) && m2<m_Value)
	//					m_colorfind = m_Value ;
	//			}
	//			else if ( m == m_Value && m1 != m_Value )
	//			{
	//				if ( m < m1 )
	//				{
	//					if ( rgn.PtInRegion(pt1) )
	//					{
	//						m_colorfind = m_Value+pdoc->inc ;
	//					}
	//					else
	//					{
	//						if( m2 > m ) m_colorfind = m_Value+pdoc->inc ;
	//						if( m2 < m ) m_colorfind = m_Value ;
	//					}
	//				}
	//				else
	//				{
	//					if ( rgn.PtInRegion(pt1) )
	//					{
	//						m_colorfind = m_Value ;
	//					}
	//					else
	//					{
	//						if( m2 > m ) m_colorfind = m_Value+pdoc->inc ;
	//						if( m2 < m ) m_colorfind = m_Value ;
	//					}
	//				}
	//			}
	//			else if ( m != m_Value && m1 == m_Value )
	//			{
	//				if ( m < m1 )
	//				{
	//					if ( rgn.PtInRegion(pt) )
	//					{
	//						m_colorfind = m_Value ;
	//					}
	//					else
	//					{
	//						if( m3 > m ) m_colorfind = m_Value+pdoc->inc ;
	//						if( m3 < m ) m_colorfind = m_Value ;
	//					}
	//				}
	//				else
	//				{
	//					if ( rgn.PtInRegion(pt) )
	//					{
	//						m_colorfind = m_Value+pdoc->inc ;
	//					}
	//					else
	//					{
	//						if( m3 > m ) m_colorfind = m_Value+pdoc->inc ;
	//						if( m3 < m ) m_colorfind = m_Value ;
	//					}
	//				}
	//			}
	//			else if( m_Value>m1 && m_Value<m )
	//			{
	//				if( rgn.PtInRegion(pt1) )
	//					m_colorfind = m_Value;
	//				if( rgn.PtInRegion(pt))
	//				{
	//					m_colorfind = m_Value+pdoc->inc ;
	//				}
	//				if( !rgn.PtInRegion(pt) && !rgn.PtInRegion(pt1) && m2>=m_Value)//
	//					m_colorfind = m_Value ;
	//				if( !rgn.PtInRegion(pt) &&!rgn.PtInRegion(pt1)  && m2<m_Value)//
	//					m_colorfind = m_Value+pdoc->inc ;
	//			}
	//			else
	//			{
	//				if (m_Value<m  && m_Value<m1)
	//				{
	//					if( rgn.PtInRegion(pt))
	//					{
	//						m_colorfind = m_Value+pdoc->inc ;
	//					}
	//					else
	//						m_colorfind = m_Value;
	//				}
	//				if (m_Value>m  && m_Value>m1)
	//				{
	//					if( rgn.PtInRegion(pt))
	//					{
	//						m_colorfind = m_Value ;
	//					}
	//					else
	//					{
	//						m_colorfind = m_Value +pdoc->inc;

	//					}

	//				}
	//			}
	//			if (m_colorfind>zmax)
	//			{
	//				m_color = RGB(200,0,0);
	//			}

	//			else
	//			{
	//				LookUpColor1(clrTbl, m_colorfind);
	//				m_color = m_FillColor;
	//			}
	//			CBrush brA ;
	//			brA.CreateSolidBrush(m_color);
	//			pDC->FillRgn(&rgn,&brA);
	//			brA.DeleteObject();
	//			theApp->FirstFillLine ++;
	//		}
	//		break;

	//	}	
	//default:
	//	break;
	//}
	//delete pt;
}
}

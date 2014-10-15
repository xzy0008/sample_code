// DEMView.cpp : 实现文件
//

//#include "stdafx.h"
#include "vgStableHeaders.h"
#include "TifView.h"

#include "TifRect.h"
#include <vector>

#include <vgImage/vgiCximageWrapper.h>
#include <algorithm>

#include <vgKernel/vgkStringVector.h>
#include <gdal/gdal_priv.h>
#include <gdal/cpl_multiproc.h>
#include <ximage.h>

using std::vector;
// DEMView


IMPLEMENT_DYNCREATE(TifView, CScrollView)

TifView::TifView()
{
	_globalData = NULL;
}

TifView::~TifView()
{
}


BEGIN_MESSAGE_MAP(TifView, CScrollView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// DEMView 绘图

void TifView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 计算此视图的合计大小
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);

}


void TifView::SetFileVector(std::vector<string>& fileList)
{
	m_orgiX = 1e10;
	m_orgiY = -1e10;

	m_lowRightX = -1e10;
	m_lowRightY = 1e10;

	GDALDataset *pDataSet;
	double      adfGeoTransform[6];

	vector<string>::iterator  iter = fileList.begin();
	vector<string>::iterator  iter_end = fileList.end();
	
	struct Dataset_t * pDataSet_key;

	while (iter != iter_end)
	{
		// TRACE("import %s \n", (*iter).c_str());
		pDataSet = (GDALDataset *)GDALOpen((*iter).c_str(), GA_ReadOnly);
		
		pDataSet_key = new struct Dataset_t;

		pDataSet_key->dataset_name = (*iter);
		
		if (pDataSet != NULL)
		{
			//m_vdataSet.push_back(pDataSet);
			if( pDataSet->GetGeoTransform( adfGeoTransform ) == CE_None )
			{
				TRACE( "Origin = (%.6f,%.6f)\n",
					adfGeoTransform[0], adfGeoTransform[3] );

				TRACE( "Pixel Size = (%.6f,%.6f)\n",
					adfGeoTransform[1], adfGeoTransform[5] );

				TRACE( "Size = (%d, %d) \n",
					pDataSet->GetRasterXSize(), pDataSet->GetRasterYSize());

				// 				m_totalSizeX += pDataSet->GetRasterXSize();
				// 				m_totalSizeY += pDataSet->GetRasterYSize();

				// m_totalBlockCnt += (int)((float)() / blockSize + 0.5);

				double dfGeoX = adfGeoTransform[0] + adfGeoTransform[1] * pDataSet->GetRasterXSize()
					+ adfGeoTransform[2] * pDataSet->GetRasterYSize();
				double dfGeoY = adfGeoTransform[3] + adfGeoTransform[4] * pDataSet->GetRasterXSize()
					+ adfGeoTransform[5] * pDataSet->GetRasterYSize();

				TRACE( "lower right = (%12.3f, %12.3f) \n", dfGeoX, dfGeoY);

				if (adfGeoTransform[0] < m_orgiX)
				{
					m_orgiX = adfGeoTransform[0];
				}

				if (adfGeoTransform[3] > m_orgiY)
				{
					m_orgiY = adfGeoTransform[3];
				}

				if (dfGeoX > m_lowRightX)
				{
					m_lowRightX = dfGeoX;
				}

				if (dfGeoY < m_lowRightY)
				{
					m_lowRightY = dfGeoY;
				}
				
				// ================================
				pDataSet_key->startx = (int)((adfGeoTransform[0] - m_orgiX) / 0.2 / 50);
				pDataSet_key->starty = (int)((adfGeoTransform[3] - m_orgiY) / -0.2 / 50);
				pDataSet_key->sizex = pDataSet->GetRasterXSize() / 50;
				pDataSet_key->sizey = pDataSet->GetRasterYSize() / 50;

				//=================================
				int nBufferSizeX = pDataSet->GetRasterXSize() / 50;
				int nBufferSizeY = pDataSet->GetRasterYSize() / 50;
				int nImageSizeX = pDataSet->GetRasterXSize();
				int nImageSizeY = pDataSet->GetRasterYSize();
				int nBand = pDataSet->GetRasterCount();

				// 读入图片overview
				//m_vdataSet[pDataSet] = (BYTE *) CPLMalloc(sizeof(BYTE)*(nBufferSizeX)*(nBufferSizeY)*3);
				m_vdataSet[pDataSet_key] = (BYTE *) CPLMalloc(sizeof(BYTE)*(nBufferSizeX)*(nBufferSizeY)*3);
				
				//pDataSet->RasterIO(GF_Read, 0, 0, nImageSizeX, nImageSizeY, m_vdataSet[pDataSet], nBufferSizeX, nBufferSizeY, GDT_Byte, nBand, NULL, nBand,0,1);
				pDataSet->RasterIO(GF_Read, 0, 0, nImageSizeX, nImageSizeY, m_vdataSet[pDataSet_key], nBufferSizeX, nBufferSizeY, GDT_Byte, nBand, NULL, nBand,0,1);

				// 转换成BMP 格式
				int sizex = nBufferSizeX;
				int sizey = nBufferSizeY;

				// BYTE *imageBuffer = m_vdataSet[pDataSet];
			    BYTE *imageBuffer = m_vdataSet[pDataSet_key];

				BYTE *swapBuffer = new BYTE[sizex*3];

				for (int i=0; i<sizey/2; i++)
				{
					memcpy(swapBuffer, imageBuffer +i*sizex*3, sizex*3);
					memcpy(imageBuffer +i*sizex*3, imageBuffer + (sizey-i-1)*sizex*3, sizex*3);
					memcpy(imageBuffer + (sizey-i-1)*sizex*3, swapBuffer, sizex*3);
				}

				delete[] swapBuffer;

				BYTE tmp;
				for (int i=0; i<nBufferSizeX*nBufferSizeY; i++)
				{
					tmp = *(imageBuffer + i*3); 
					//*(data + i*3 +1)
					*(imageBuffer + i*3) = *(imageBuffer + i*3 + 2);
					*(imageBuffer + i*3 + 2) = tmp;
				}

			} // end while

			GDALClose(pDataSet);
		}

		iter ++;
	}

	SetScrollSizes(MM_TEXT, CSize((int)(m_lowRightX-m_orgiX) / adfGeoTransform[1] / 50, (int)(m_lowRightY - m_orgiY) / adfGeoTransform[5] / 50));
}
void TifView::OnDraw(CDC* /*pDC*/)
{
	//CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码

	CClientDC dc(this);

// 	std::map<GDALDataset*, BYTE*>::iterator iter = m_vdataSet.begin();
// 	std::map<GDALDataset*, BYTE*>::iterator end  = m_vdataSet.end();

	std::map<Dataset_t*, BYTE*>::iterator iter = m_vdataSet.begin();
	std::map<Dataset_t*, BYTE*>::iterator end  = m_vdataSet.end();

	BYTE *image;
	// GDALDataset *pDataSet;
	struct Dataset_t* pDataset_key;

	CPoint scrollPos = GetScrollPosition();

	while (iter != end)
	{
		//pDataSet = (*iter).first;
		pDataset_key = (*iter).first;

// 		int nBufferSizeX = pDataSet->GetRasterXSize() / 50;
// 		int nBufferSizeY = pDataSet->GetRasterYSize() / 50;

		int nBufferSizeX = pDataset_key->sizex;
		int nBufferSizeY = pDataset_key->sizey;

// 		double      adfGeoTransform[6];
// 		pDataSet->GetGeoTransform( adfGeoTransform );

// 		int nstartX = (int)((adfGeoTransform[0] - m_orgiX) / 0.2 / 50);
// 		int nstartY = (int)((adfGeoTransform[3] - m_orgiY) / -0.2 / 50);

		int nstartX = pDataset_key->startx;
		int nstartY = pDataset_key->starty;

		image = (*iter).second;

 		vgImage::CximageWrapper imageWrapper;
 		imageWrapper.createFromArray(image, nBufferSizeX, nBufferSizeY);
 		imageWrapper.getCximagePtr()->Draw(dc, nstartX-scrollPos.x, nstartY-scrollPos.y);
		iter ++;
	}
}


int TifView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 1024;
	SetScrollSizes(MM_TEXT, sizeTotal);

	return 0;
}

// DEMView 诊断

#ifdef _DEBUG
void TifView::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void TifView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG


// DEMView 消息处理程序

void TifView::OnDestroy()
{
	CScrollView::OnDestroy();
	
	ClearDataSet();
	// TODO: 在此处添加消息处理程序代码
}

void TifView::ClearDataSet()
{
 	std::map<struct Dataset_t*, BYTE*>::iterator iter = m_vdataSet.begin();
 	std::map<struct Dataset_t*, BYTE*>::iterator end  = m_vdataSet.end();
 
 	while (iter != end)
 	{
 		//delete (*iter).second;
 		delete((*iter).second);
 		//	GDALClose((*iter).first);
 		delete ((*iter).first);
		iter ++;
 	}

	m_vdataSet.clear();

}

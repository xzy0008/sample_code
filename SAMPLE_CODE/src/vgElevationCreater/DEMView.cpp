// DEMView.cpp : 实现文件
//

//#include "stdafx.h"
#include "vgStableHeaders.h"
#include "DEMView.h"

#include "DEMRect.h"

#include <vgTerritory/vgtGeoDemManager.h>

#include <vector>

using std::vector;
// DEMView

static vector<DEMRect> rectList;

IMPLEMENT_DYNCREATE(DEMView, CScrollView)

DEMView::DEMView()
{
}

DEMView::~DEMView()
{
}


BEGIN_MESSAGE_MAP(DEMView, CScrollView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// DEMView 绘图

void DEMView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

}

void DEMView::OnDraw(CDC* pDC)
{
	//CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码

	//for (int i=0; i<rectList.size(); i++)
	//{
	//	CRect rect(rectList[i].GetTopLeft().x, rectList[i].GetTopLeft().y,
	//		rectList[i].GetSize().cx, rectList[i].GetSize().cy);
	//	pDC->Rectangle(&rect);
	//}

	//CRect rect;
	//GetClientRect(&rect);

	//img->Draw(pDC->GetSafeHdc());

#if 1
	using namespace vgTerritory;

	GeoGlobalData* gdata = GeoDemManager::getSingleton().getGlobalDataPtr();

	if ( gdata->_genElevationOverview == false )
	{
		return;
	}


	assert( gdata != NULL );
	assert( gdata->_globalRect.getWidth() != 0 );

	CSize sizeTotal;
	sizeTotal.cx = sizeTotal.cy =
		( gdata->_globalAdjustRect.getWidth() + 1 ) / VGT_OVERVIEW_DIVIDE;
	SetScrollSizes( MM_TEXT, sizeTotal );



	GeoDemMap* dems = GeoDemManager::getSingleton().getGeoDemMap();

	assert( dems->empty() == false );
	GeoDemMap::iterator iter = dems->begin();
	GeoDemMap::iterator iter_end = dems->end();

	for ( ; iter !=  iter_end ; ++iter )
	{
		GeoDem* curdem = iter->second;
		GeoDemOverview* curov = curdem->getOverview();
		assert( curov != NULL );


		curov->draw( pDC->GetSafeHdc() );
	}



#endif
}


int DEMView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CSize sizeTotal;
	// TODO: 计算此视图的合计大小
	sizeTotal.cx = sizeTotal.cy = 1000;
	SetScrollSizes(MM_TEXT, sizeTotal);

	return 0;
}

// DEMView 诊断

#ifdef _DEBUG
void DEMView::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void DEMView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG


// DEMView 消息处理程序

// vgObjectPropPage.cpp : 实现文件
//

#include <vgStableHeaders.h>
#include "vgFrameWork.h"
#include "vgObjectPropPage.h"
#include "vgObjectNode.h"

// vgObjectPropPage 对话框

IMPLEMENT_DYNAMIC(vgObjectPropPage, CDialog)

vgObjectPropPage::vgObjectPropPage(CWnd* pParent /*=NULL*/)
	: CDialog(vgObjectPropPage::IDD, pParent)
{
}

vgObjectPropPage::~vgObjectPropPage()
{
}

void vgObjectPropPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

string vgObjectPropPage::GetTitle()
{
	return "属性";
}

CWnd* vgObjectPropPage::GetWnd()
{
	return this;
}


BEGIN_MESSAGE_MAP(vgObjectPropPage, CDialog)
	ON_REGISTERED_MESSAGE(BCGM_PROPERTY_CHANGED, OnPropertyChanged)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

void vgObjectPropPage::AdjustLayout()
{
	CRect rectClient,rectCombo;
	GetClientRect (rectClient);
	m_wndPropList.SetWindowPos (NULL,
		rectClient.left, 
		rectClient.top, 
		rectClient.Width(),
		rectClient.Height(),
		SWP_NOACTIVATE | SWP_NOZORDER);
}

void vgObjectPropPage::InitPropList()
{
	// 为设定初始值向下转型
	vgObjectNode* tnode = dynamic_cast<vgObjectNode*>(m_pNode);

	m_wndPropList.EnableHeaderCtrl (FALSE);
	m_wndPropList.EnableDesciptionArea ();
	m_wndPropList.SetVSDotNetLook ();
	m_wndPropList.MarkModifiedProperties ();
	
	CBCGPProp* pGroup0 = new CBCGPProp (_T("坐标属性"));
	pGroup0->AddSubItem(new CBCGPProp(_T("X 坐标"), (_variant_t)(float)tnode->m_posX, _T("指定X 坐标")));
	pGroup0->AddSubItem(new CBCGPProp(_T("Y 坐标"), (_variant_t)(float)tnode->m_posY, _T("指定Y 坐标")));
	pGroup0->AddSubItem(new CBCGPProp(_T("Z 坐标"), (_variant_t)(float)tnode->m_posZ, _T("指定Z 坐标")));	

	m_wndPropList.AddProperty(pGroup0);
	
	CBCGPProp* pGroup1 = new CBCGPProp (_T("LOD"));
	pGroup1->AddSubItem(new CBCGPProp(_T("NEAR"), (_variant_t)(long)tnode->m_near, _T("NEAR")));
	pGroup1->AddSubItem(new CBCGPProp(_T("FAR"), (_variant_t)(long)tnode->m_far, _T("FAR")));
	m_wndPropList.AddProperty (pGroup1);
		

	CBCGPProp* pGroup2 = new CBCGPProp (_T("旋转"));

	pGroup2->AddSubItem (new CBCGPProp (_T("开启旋转"), (_variant_t) false,
		_T("指定物体是否可以被旋转")));

	pGroup2->AddSubItem(new CBCGPProp(_T("X 轴弧度"), tnode->m_rotX, _T("指定X 轴旋转角度")));
	pGroup2->AddSubItem(new CBCGPProp(_T("Y 轴弧度"), tnode->m_rotY, _T("指定Y 轴旋转角度")));
	pGroup2->AddSubItem(new CBCGPProp(_T("Z 轴弧度"), tnode->m_rotZ, _T("指定Z 轴旋转角度")));	

	m_wndPropList.AddProperty (pGroup2);

	CBCGPProp* pGroup3 = new CBCGPProp (_T("缩放"));

	pGroup3->AddSubItem(new CBCGPProp(_T("X 轴"), (_variant_t)(float)tnode->m_scaleX, _T("指定X 轴缩放倍数")));
	pGroup3->AddSubItem(new CBCGPProp(_T("Y 轴"), (_variant_t)(float)tnode->m_scaley, _T("指定Y 轴缩放倍数")));
	pGroup3->AddSubItem(new CBCGPProp(_T("Z 轴"), (_variant_t)(float)tnode->m_scaleZ, _T("指定Z 轴缩放倍数")));	

	m_wndPropList.AddProperty (pGroup3);

}
// vgObjectPropPage 消息处理程序

LRESULT vgObjectPropPage::OnPropertyChanged(WPARAM w, LPARAM l)
{
	CBCGPProp* pProp = (CBCGPProp*)l;
	vgObjectNode* tnode = dynamic_cast<vgObjectNode*>(m_pNode);
	_variant_t var = pProp->GetValue(); 
	string name(pProp->GetName());

	if (name == "X 坐标")
	{
		tnode->m_posX = var.fltVal;	
	} 
	else if (name == "Y 坐标")
	{
		tnode->m_posY = var.fltVal;
	}
	else if (name == "Z 坐标")
	{
		tnode->m_posZ = var.fltVal;
	}
	else if (name == "NEAR")
	{
		tnode->m_near = var.intVal;
	}
	else if (name == "FAR")
	{
		tnode->m_far = var.intVal;
	}
	else if (name == "X 轴弧度")
	{
		tnode->m_rotX = var.fltVal;
	}
	else if (name == "Y 轴弧度")
	{
		tnode->m_rotY= var.fltVal;
	}	
	else if (name == "Z 轴弧度")
	{
		tnode->m_rotZ = var.fltVal;
	}
	else if (name == "X 轴")
	{
		tnode->m_scaleX = var.intVal;
	}
	else if (name == "Y 轴")
	{
		tnode->m_scaley = var.intVal;
	}
	else if (name == "Z 轴")
	{
		tnode->m_scaleZ = var.intVal;
	}
	return NULL;
}

int vgObjectPropPage::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CRect rectDummy;
	rectDummy.SetRectEmpty ();

	if (!m_wndPropList.Create (WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("Failed to create Properies Grid \n");
		return -1;      // fail to create
	}

	InitPropList();
	AdjustLayout ();

	return 0;
}

void vgObjectPropPage::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	AdjustLayout();
	// TODO: 在此处添加消息处理程序代码
}

BOOL vgObjectPropPage::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	// ::MessageBox(NULL , "Window Destory here","info" ,MB_OK);
	return __super::DestroyWindow();
}

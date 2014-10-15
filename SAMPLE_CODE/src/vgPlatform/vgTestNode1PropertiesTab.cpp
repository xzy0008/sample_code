// PropertiesTab.cpp : 实现文件
//

#include <vgStableHeaders.h>
#include "vgFrameWork.h"
#include "vgTestNode1PropertiesTab.h"
#include "vgTestNode1.h"

// PropertiesTab 对话框

IMPLEMENT_DYNAMIC(PropertiesTab, CDialog)

PropertiesTab::PropertiesTab(CWnd* pParent /*=NULL*/)
	: CDialog(PropertiesTab::IDD, pParent)
{
}

PropertiesTab::~PropertiesTab()
{
	// ::MessageBox(NULL, "Destory Message", "Info", MB_OK);
}

string PropertiesTab::GetTitle()
{
	return _T("设置属性");
}

CWnd* PropertiesTab::GetWnd()
{
	return this;
}

void PropertiesTab::AdjustLayout()
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

void PropertiesTab::InitPropList()
{
	// 为设定初始值向下转型
	vgTestNode1* tnode = dynamic_cast<vgTestNode1*>(m_pNode);
	
	m_wndPropList.EnableHeaderCtrl (FALSE);
	m_wndPropList.EnableDesciptionArea ();
	m_wndPropList.SetVSDotNetLook ();
	m_wndPropList.MarkModifiedProperties ();
	
	m_wndPropList.AddProperty(new CBCGPProp(_T("X 坐标"), (_variant_t)(float)tnode->m_posX, _T("指定X 坐标")));

	CBCGPProp* pGroup0 = new CBCGPProp (_T("坐标属性"));
	pGroup0->AddSubItem(new CBCGPProp(_T("X 坐标"), (_variant_t)(float)tnode->m_posX, _T("指定X 坐标")));
	pGroup0->AddSubItem(new CBCGPProp(_T("Y 坐标"), (_variant_t)(float)tnode->m_posY, _T("指定Y 坐标")));
	pGroup0->AddSubItem(new CBCGPProp(_T("Z 坐标"), (_variant_t)(float)tnode->m_posZ, _T("指定Z 坐标")));	

	m_wndPropList.AddProperty(pGroup0);

	CBCGPProp* pGroup1 = new CBCGPProp (_T("旋转"));

	pGroup1->AddSubItem (new CBCGPProp (_T("开启旋转"), (_variant_t) false,
		_T("指定物体是否可以被旋转")));

	CBCGPProp* pProp = new CBCGPProp (_T("旋转轴"), _T("无"),
		_T("选择物体的旋转轴"));
	pProp->AddOption (_T("无"));
	pProp->AddOption (_T("X 轴"));
	pProp->AddOption (_T("Y 轴"));
	pProp->AddOption (_T("Z 轴"));
	pProp->AllowEdit (FALSE);
	pGroup1->AddSubItem (pProp);
	m_wndPropList.AddProperty (pGroup1);

}

void PropertiesTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PropertiesTab, CDialog)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_REGISTERED_MESSAGE(BCGM_PROPERTY_CHANGED, OnPropertyChanged)
END_MESSAGE_MAP()


// PropertiesTab 消息处理程序

int PropertiesTab::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
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

void PropertiesTab::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	AdjustLayout ();
	// TODO: 在此处添加消息处理程序代码
}

LRESULT PropertiesTab::OnPropertyChanged(WPARAM w, LPARAM l)
{
	CBCGPProp* pProp = (CBCGPProp*)l;
	vgTestNode1* tnode = dynamic_cast<vgTestNode1*>(m_pNode);
	_variant_t var = pProp->GetValue(); 
	string name(pProp->GetName());

	if (name == "X 坐标")
	{
		tnode->m_posX = var.fltVal;	
	}
/*
	//以下代码演示为其余类型（补充）
	switch(var.vt)
	{

	case VT_BSTR:			//var is BSTR type
		str= var.bstrVal;
		break;

	case VT_I2:				//var is short int type
		str.Format("short %d",(int)var.iVal);
		break;

	case VT_I4:				//var is long int type
		str.Format("long %d",var.lVal);
		break;

	case VT_R4:				//var is float type
		str.Format("float %10.6f",(double)var.fltVal);
		break;

	case VT_R8:				//var is double type
		str.Format("Double %10.6f",var.dblVal);
		break;

	case VT_CY:				//var is CY type
		str="CY type " + COleCurrency(var).Format();
		break;

	case VT_DATE:			 //var is DATE type
		str="Time " + COleDateTime(var).Format();
		break;

	case VT_BOOL:     //var is  VARIANT_BOOL
		str= "Boolean " + (var.boolVal==0) ?"FALSE": "TRUE";
		break;

	default:
		str.Format("Unk type %d\n VALUE ",var.vt, var.bstrVal);
		TRACE("Unknown type %d\n",var.vt);
	}

	str += " Name:";
	str += pProp->GetName();

	::MessageBox(NULL, str, "Properties Changed!", MB_OK);
	*/
	return NULL;
}
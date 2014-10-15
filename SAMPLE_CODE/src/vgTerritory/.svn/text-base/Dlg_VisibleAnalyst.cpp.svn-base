// Dlg_VisibleAnalyst.cpp : 实现文件
//

#include "vgStableHeaders.h"
#include "vgTerritory/Dlg_VisibleAnalyst.h"
#include <vgKernel/vgkRendererManager.h>
//#include <vgCam/vgcaViewCam.h>
//#include <vgCam/vgcaCamManager.h>
#include <vgKernel/vgkSelectManager.h>
#include <vgCam/vgcaCamFacade.h>

// CDlg_VisibleAnalyst 对话框

IMPLEMENT_DYNAMIC(CDlg_VisibleAnalyst, CDialog)

CDlg_VisibleAnalyst::CDlg_VisibleAnalyst(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_VisibleAnalyst::IDD, pParent)
	, strVisiAnaRes(_T(""))
{
	bClosed = false;
}

CDlg_VisibleAnalyst::~CDlg_VisibleAnalyst()
{
	vecStrModName.clear();
}

void CDlg_VisibleAnalyst::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STC_VISIANA_RES, strVisiAnaRes);
	DDX_Control(pDX, IDC_STC_VISIANA_GRID_POS, cstcGridPos);
}


BEGIN_MESSAGE_MAP(CDlg_VisibleAnalyst, CDialog)
	ON_BN_CLICKED(IDOK, &CDlg_VisibleAnalyst::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlg_VisibleAnalyst::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlg_VisibleAnalyst 消息处理程序

BOOL CDlg_VisibleAnalyst::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rectGrid;
	cstcGridPos.GetClientRect (&rectGrid);

	cstcGridPos.MapWindowPoints (this, &rectGrid);

	m_wndGrid.Create (WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rectGrid, this, (UINT)-1);
	m_wndGrid.EnableHeader (TRUE, BCGP_GRID_HEADER_MOVE_ITEMS);

	m_wndGrid.SetWholeRowSel(FALSE);
	m_wndGrid.EnableMarkSortedColumn(FALSE);
	m_wndGrid.EnableHeader(TRUE, 0);

	m_wndGrid.InsertColumn(0, _T("编号"), 38);
	m_wndGrid.InsertColumn(1, _T("遮挡模型名称"), 180);
	UpdateData( FALSE );

	setList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlg_VisibleAnalyst::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//bClosed = true;
	vgKernel::SelectManager::getSingleton().clearSelection();

	OnOK();
}

void CDlg_VisibleAnalyst::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	// 定位至模型
	bClosed = true;

	m_wndGrid.Invalidate(true);

	CBCGPGridRow *pNowRow = m_wndGrid.GetCurSel();

	if ( pNowRow != NULL )
	{
		CString str_ModName(pNowRow->GetItem(1)->GetValue().bstrVal);

		if ( str_ModName == _T("地形") )
		{
			//OnCancel();
			return;
		}

		vgKernel::Renderer* pRender = vgKernel::RendererManager::getSingleton().getRendererbyName( str_ModName.GetString(), true );
		VGK_SHOW("切换至物体 \n");

		vgCam::CamFacade::gotoBox( pRender->getBoundingBox() );
		
		vgKernel::SelectManager::getSingleton().clearSelection();
		pRender->setSelected( true );
		vgKernel::SelectManager::getSingleton().addSelection( pRender, false );
	}

	//OnCancel();
}

void CDlg_VisibleAnalyst::setList()
{
	if ( vecStrModName.size() > 0 )
	{
		std::vector<CString>::iterator iter = vecStrModName.begin();
		std::vector<CString>::iterator iterEnd = vecStrModName.end();
		int num = 0;

		for ( iter; iter != iterEnd; iter++ )
		{
			CString modName(_T(""));
			modName = (*iter);

			CBCGPGridRow* pRow = m_wndGrid.CreateRow(m_wndGrid.GetColumnCount ());

			for (int i = 0; i < m_wndGrid.GetColumnCount();i++)
			{
				pRow->GetItem (i)->AllowEdit (FALSE);	
			}

			// Mod名称
			CString temstr(_T(""));
			temstr.Format("%d", num);
			pRow->GetItem(0)->SetValue(temstr.AllocSysString(), TRUE);
			pRow->GetItem(1)->SetValue(modName.AllocSysString(), TRUE);
			m_wndGrid.AddRow(pRow, TRUE);
			UpdateData( FALSE );
			num++;
		}
	}
	
}

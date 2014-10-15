// vgPipeAttriDlg.cpp : 实现文件
//

#include <vgStableHeaders.h>
#include <vgGIS3D\vgPipeAttriDlg.h>

#include <vgGis/vgGisManager.h>
#include <vgGIS3D/vggiDataSource.h>
#include <vgGis3d/vggiGeometry.h>
#include <vgGIS3D/vggiPrerequisite.h>
#include <vgGis3d/vggiLine.h>

#include <vgKernel/vgkSystemUtility.h>
#include <vgCam/vgcaCamFacade.h>


// vgPipeAttriDlg 对话框
namespace vgGIS3D
{
	IMPLEMENT_DYNAMIC(vgPipeAttriDlg, CDialog)

		vgPipeAttriDlg::vgPipeAttriDlg(CWnd* pParent /*=NULL*/)
		: CDialog(vgPipeAttriDlg::IDD, pParent)
	{
		//m_ogrPipeLineMap = NULL;
		m_ogrPipeLineMap = vgGIS3D::GisManager::getSingleton().getPipeLineMap();
	}

	vgPipeAttriDlg::~vgPipeAttriDlg()
	{
	}

	void vgPipeAttriDlg::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		DDX_Control(pDX, IDC_PIPEATTRI_LIST, m_wndGridLocation);
	}


	BEGIN_MESSAGE_MAP(vgPipeAttriDlg, CDialog)
		ON_WM_CREATE()	
		ON_WM_TIMER()
		ON_WM_DESTROY()
		ON_BN_CLICKED(ID_SET_FAULT, &vgPipeAttriDlg::OnBnSetFault)
		ON_BN_CLICKED(IDC_BTN_TURNTO, &vgPipeAttriDlg::OnTurnSelectToView)		
	END_MESSAGE_MAP()


	// vgPipeAttriDlg 消息处理程序

	int vgPipeAttriDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (CDialog::OnCreate(lpCreateStruct) == -1)
		{
			AfxMessageBox("Error.");
			return -1;
		}

		return 0;
	}

	BOOL vgPipeAttriDlg::OnInitDialog()
	{
		CDialog::OnInitDialog();

		// TODO:  在此添加额外的初始化
		// TODO:  在此添加您专用的创建代码

		UpdateData ();

		// TODO: Add extra initialization here
		CRect rectGrid;
		m_wndGridLocation.GetClientRect (&rectGrid);

		m_wndGridLocation.MapWindowPoints (this, &rectGrid);

		m_wndGrid.Create (WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rectGrid, this, (UINT)-1);
		m_wndGrid.EnableHeader (TRUE, BCGP_GRID_HEADER_MOVE_ITEMS);

		//m_wndGrid.SetReadOnly ();

		m_wndGrid.InsertColumn (0, _T("起点ID"), 100);
		m_wndGrid.InsertColumn (1, _T("终点ID"), 100);
		m_wndGrid.InsertColumn (2, _T("管径"), 100);
		//m_wndGrid.InsertColumn (3, _T("材质"), 80);
		//m_wndGrid.InsertColumn (4, _T("埋深"), 80);


		UpdateData(FALSE);

		GeometryPointerVec* selectedGeoVec = 
			vgGIS3D::GisManager::getSingleton().getSelectedGeometry();		

		for (int i = 0; i < selectedGeoVec->size(); i++)
		{
			LineString *Line = dynamic_cast<LineString*> (selectedGeoVec->at(i));
			if (Line == NULL)
			{
				AfxMessageBox("有管线不支持的类型");
			}
			else
			{
				RingStruct pipeLine = Line->getRing();

				CBCGPGridRow* pRow = m_wndGrid.CreateRow(m_wndGrid.GetColumnCount ());

				for (int i = 0; i < m_wndGrid.GetColumnCount ();i++)
				{
					pRow->GetItem (i)->AllowEdit (FALSE);
				}

				int begID = pipeLine._beginPointID;
				int endID = pipeLine._endPointID;
				float pipeRadius = m_ogrPipeLineMap->getPipeLineRadius();

				pRow->GetItem(0)->SetValue(begID);
				pRow->GetItem(1)->SetValue(endID);
				pRow->GetItem(2)->SetValue(pipeRadius);

				m_wndGrid.AddRow(pRow, TRUE);
			}
		}

		UpdateData(FALSE);

		m_wndGrid.SetWholeRowSel(TRUE);

		sLastRow = NULL;
		SetTimer(1, 100, NULL);

		return TRUE;  // return TRUE unless you set the focus to a control
		// 异常: OCX 属性页应返回 FALSE
	}

	void vgPipeAttriDlg::OnBnSetFault()
	{
		int rowNum = m_wndGrid.GetRowCount();

		CBCGPGridRow *pRow = m_wndGrid.GetRow(0);
		int begID = pRow->GetItem(0)->GetValue().intVal;
		int endID = pRow->GetItem(1)->GetValue().intVal;

		m_ogrPipeLineMap->callUpstreamPoint(begID, endID);

		//OnDestroy();
		OnOK();

	}

	void vgPipeAttriDlg::OnTimer(UINT_PTR nIDEvent)
	{
		CDialog::OnTimer(nIDEvent);
	}

	void vgPipeAttriDlg::OnDestroy()
	{
		CDialog::OnDestroy();

		// TODO: 在此处添加消息处理程序代码
		//delete this;
	}

	void vgGIS3D::vgPipeAttriDlg::OnOK()
	{
		CDialog::OnOK();
		DestroyWindow();
	}

	void vgPipeAttriDlg::OnTurnSelectToView()
	{
		CBCGPGridRow *pRow = m_wndGrid.GetRow(0);
		int begID = pRow->GetItem(0)->GetValue().intVal;
		int endID = pRow->GetItem(1)->GetValue().intVal;

		GeometryPointerVec geoPointerVec = m_ogrPipeLineMap->getGeometriesRef();
		for (int i = 0 ; i < geoPointerVec.size(); i++)
		{
			LineString *pLineString 
				= dynamic_cast<LineString*>(geoPointerVec[i]);

			if (pLineString != NULL)
			{
				RingStruct ringsRef = pLineString->getRing();
				if ((ringsRef._beginPointID == begID) &&
					(ringsRef._endPointID == endID))
				{
					vgCam::CamFacade::gotoBox(m_ogrPipeLineMap->getPipeLineBox(pLineString));
				}
				else
				{
					continue;
				}
			}
		}		
	}

}//end namespace



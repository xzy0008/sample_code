// D:\___visualVersion\trunkDLL\src\vgGIS3D\vggiDlgPointAttri.cpp : 实现文件
//

#include <vgStableHeaders.h>
#include <vgGIS3D\vggiDlgPointAttri.h>

#include <vgGis/vgGisManager.h>
#include <vgGIS3D/vggiDataSource.h>
#include <vgCam/vgcaCamManager.h>
#include <vgCam/vgcaCamFacade.h>

#include <vgKernel/vgkSystemUtility.h>


// vgDlgSelLayer 对话框

namespace vgGIS3D
{
	IMPLEMENT_DYNAMIC(vgDlgPointAttri, CDialog)

		vgDlgPointAttri::vgDlgPointAttri(CWnd* pParent /*=NULL*/)
		: CDialog(vgDlgPointAttri::IDD, pParent)
	{	
		//m_ogrPipeLineMap = NULL;
		m_ogrPipeLineMap = vgGIS3D::GisManager::getSingleton().getPipeLineMap();
	}

	vgDlgPointAttri::~vgDlgPointAttri()
	{
		//if (m_ogrPipeLineMap != NULL)
		//{
		//    delete m_ogrPipeLineMap;
		//	m_ogrPipeLineMap = NULL;
		//}
	}

	void vgDlgPointAttri::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		DDX_Control(pDX, IDC_ATTRI_LIST, m_wndGridLocation);
	}


	BEGIN_MESSAGE_MAP(vgDlgPointAttri, CDialog)
		ON_WM_CREATE()
		ON_WM_TIMER()
		ON_WM_DESTROY()
		ON_BN_CLICKED(ID_PRESS_CHANGE, &vgDlgPointAttri::OnBnSetPressEidt)
		ON_BN_CLICKED(ID_BN_SETBREAKPT, &vgDlgPointAttri::OnBnSetPointBreak)
		ON_BN_CLICKED(IDC_BTN_TURNTOVIEW, &vgDlgPointAttri::OnTurnViewToSelect)
		ON_WM_CLOSE()
	END_MESSAGE_MAP()


	// vgDlgSelLayer 消息处理程序

	string vgDlgPointAttri::getSelectLayerName()
	{
		// UpdateData(TRUE);
		return m_layerNameStr;
	}

	int vgDlgPointAttri::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (CDialog::OnCreate(lpCreateStruct) == -1)
		{
			AfxMessageBox("Error.");
			return -1;
		}

		return 0;
	}

	void vgDlgPointAttri::OnTimer(UINT_PTR nIDEvent)
	{
		CDialog::OnTimer(nIDEvent);
	}

	void vgDlgPointAttri::OnBnSetPressEidt()
	{
		vector<JointPointPtr>* jointArray = 
			vgGIS3D::GisManager::getSingleton().getJointArray();

		assert(jointArray->size());

		if (m_wndGrid.GetRowCount() > 1)
		{
			AfxMessageBox("每次只能够选择一个压力源");
			return;
		}
		else
		{
			CBCGPGridRow *pRow = m_wndGrid.GetRow(0);
			double pressValue = pRow->GetItem(2)->GetValue().dblVal;
			int ID = pRow->GetItem(0)->GetValue().intVal;
			
			double preValue = jointArray->at(ID)->m_pressValue; //记录下新压力源现在的压力值，以便反算结束后叠加
			jointArray->at(ID)->m_pressValue = pressValue;  //以新的压力值进行反算
			calculatePressure(ID, preValue);			
		}

		//OnDestroy();	
		OnOK();
	}

	void vgDlgPointAttri::calculatePressure(int id, double preValue)
	{		
		//m_ogrPipeLineMap = vgGIS3D::GisManager::getSingleton().getPipeLineMap();
		m_layerNameStr = m_ogrPipeLineMap->getName();

		m_ogrPipeLineMap->calEachPointPress(id, preValue);
	}

	BOOL vgDlgPointAttri::OnInitDialog()
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

		m_wndGrid.InsertColumn (0, _T("ID"), 50);
		m_wndGrid.InsertColumn (1, _T("坐标"), 220);
		m_wndGrid.InsertColumn (2, _T("压力值"), 80);

		UpdateData(FALSE);

		std::vector <PointStruct>* selectPointVec = 
			                    vgGIS3D::GisManager::getSingleton().getSelectPoints();		

		for (int i = 0; i < selectPointVec->size(); i++)
		{
			CBCGPGridRow* pRow = m_wndGrid.CreateRow(m_wndGrid.GetColumnCount ());

			for (int j = 0; j < 2; j++)
			{
				pRow->GetItem (j)->AllowEdit (FALSE);
			}

			int id = selectPointVec->at(i).ID;
			double pressValue = selectPointVec->at(i).pressValue;
			vgKernel::Vec3 pos = selectPointVec->at(i).pos;	

			//将不是联通节点的节点过滤掉
			if (m_ogrPipeLineMap->getPipeGeoIndex(id) != PipeGeoPtr())
			{
				CString value1, value2, value3, keyvalue;
				value1.Format("%f", pos.x);
				value2.Format("%f", pos.y);
				value3.Format("%f", pos.z);
				keyvalue = value1 + _T(",") + value2 + _T(",")  + value3;
				char* position = keyvalue.GetBuffer(keyvalue.GetLength());

				pRow->GetItem(0)->SetValue(id);
				pRow->GetItem(1)->SetValue(position);
				pRow->GetItem(2)->SetValue(pressValue);

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

	void vgGIS3D::vgDlgPointAttri::OnOK()
	{
		CDialog::OnOK();
		DestroyWindow();
	}

	void vgDlgPointAttri::OnBnSetPointBreak()
	{
		int rowNum = m_wndGrid.GetRowCount();
		if (rowNum > 1)
		{
			AfxMessageBox("每次只支持选择一个断点");
			return;
		}
		else
		{
			CBCGPGridRow *pRow = m_wndGrid.GetRow(0);
			int ID = pRow->GetItem(0)->GetValue().intVal;

			m_breakPointsVec.push_back(ID);

			//m_ogrPipeLineMap = vgGIS3D::GisManager::getSingleton().getPipeLineMap();
			m_ogrPipeLineMap->reCalPointPressure(m_breakPointsVec);
		}

		//OnDestroy();
		OnOK();
	}

	void vgDlgPointAttri::OnDestroy()
	{
		CDialog::OnDestroy();		

		// TODO: 在此处添加消息处理程序代码
		//delete this;
	}

	void vgDlgPointAttri::OnTurnViewToSelect()
	{
		// TODO: 在此添加控件通知处理程序代码
		// 定位至节点		

		vector<JointPointPtr>* jointArray = 
			vgGIS3D::GisManager::getSingleton().getJointArray();

		m_wndGrid.Invalidate(true);

		CBCGPGridRow *pNowRow = m_wndGrid.GetCurSel();

		if (pNowRow != NULL)
		{
			int index = pNowRow->GetItem(0)->GetValue().intVal;
			//m_ogrPipeLineMap = vgGIS3D::GisManager::getSingleton().getPipeLineMap();
			PipeGeoPtr pipeGeo = m_ogrPipeLineMap->getPipeGeoIndex(index);
			//m_ogrPipeLineMap->addSelectPipeGeo(pipeGeo);  //加入选择几何体，达到绘出包围盒的目的

			vgCam::CamFacade::gotoBox( m_ogrPipeLineMap->getPipeGeoBox(pipeGeo) );
		}
		else
		{
			AfxMessageBox("请选择节点");
			return;
		}		
	}

}//end nameSpace 
void vgGIS3D::vgDlgPointAttri::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值	
	CDialog::OnClose();
}

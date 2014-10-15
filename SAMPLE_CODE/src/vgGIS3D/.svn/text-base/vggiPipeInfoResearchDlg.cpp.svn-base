// vggiPipeInfoResearchDlg.cpp : 实现文件
//

//#include "stdafx.h"
#include <vgStableHeaders.h>
#include <vgKernel/vgkSystemUtility.h>

#include <vgGis3d/vggiPipeInfoResearchDlg.h>
#include <vgGis/vgGisManager.h>
#include <vgCam/vgcaCamFacade.h>
#include <vgCam/vgcaCamManager.h>
#include <vgGIS3D/vggiPipeGeometry.h>
#include <vgGIS3D/vggiLine.h>


// vggiPipeInfoResearchDlg 对话框
namespace vgGIS3D
{
	IMPLEMENT_DYNAMIC(vggiPipeInfoResearchDlg, CDialog)

		vggiPipeInfoResearchDlg::vggiPipeInfoResearchDlg(CWnd* pParent /*=NULL*/)
		: CDialog(vggiPipeInfoResearchDlg::IDD, pParent)
	{
		m_ogrPipeLineMap = vgGIS3D::GisManager::getSingleton().getPipeLineMap();
	}

	vggiPipeInfoResearchDlg::~vggiPipeInfoResearchDlg()
	{
	}

	void vggiPipeInfoResearchDlg::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		DDX_Control(pDX, IDC_PIPEINFO_LIST, m_wndGridLocation);
		DDX_Control(pDX, IDC_COMBO_SELECTION, m_selectTyple);
	}


	BEGIN_MESSAGE_MAP(vggiPipeInfoResearchDlg, CDialog)
		ON_WM_TIMER()
		ON_BN_CLICKED(IDC_RADIO_CHOICE1, &vggiPipeInfoResearchDlg::OnBnClickedRadioMaterial)
		ON_BN_CLICKED(IDC_RADIO_CHOICE2, &vggiPipeInfoResearchDlg::OnBnClickedRadioDate)
		ON_BN_CLICKED(IDC_RADIO_CHOICE3, &vggiPipeInfoResearchDlg::OnBnClickedRadioHandlingType)
		ON_BN_CLICKED(IDC_RADIO_CHOICE4, &vggiPipeInfoResearchDlg::OnBnClickedRadioRegion)
		ON_CBN_SELCHANGE(IDC_COMBO_SELECTION, &vggiPipeInfoResearchDlg::OnCbnSelchangeTyle)
		ON_BN_CLICKED(IDC_BTN_LOOK_AT, &vggiPipeInfoResearchDlg::OnTurnSelectToView)
	END_MESSAGE_MAP()

	BOOL vggiPipeInfoResearchDlg::OnInitDialog()
	{
		CDialog::OnInitDialog();

		UpdateData ();
		// TODO: Add extra initialization here
		CRect rectGrid;
		m_wndGridLocation.GetClientRect (&rectGrid);

		m_wndGridLocation.MapWindowPoints (this, &rectGrid);

		m_wndGrid.Create (WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rectGrid, this, (UINT)-1);
		m_wndGrid.EnableHeader (TRUE, BCGP_GRID_HEADER_MOVE_ITEMS);

		//m_wndGrid.SetReadOnly ();

		m_wndGrid.InsertColumn(0, _T("ID"), 50);
		m_wndGrid.InsertColumn (1, _T("目标名称"), 100);
		//m_wndGrid.InsertColumn (1, _T(""), 130);            //因为只有一列的话，弹出的时候会崩溃，加个空列
		UpdateData(FALSE);

		//选择模式
		if ( m_choiceMode == MODE_IN_MATERIAL )
		{
			( ( CButton* )GetDlgItem( IDC_RADIO_CHOICE1 ) )->SetCheck( TRUE ); 
			( ( CButton* )GetDlgItem( IDC_RADIO_CHOICE2 ) )->SetCheck( FALSE );
			( ( CButton* )GetDlgItem( IDC_RADIO_CHOICE3 ) )->SetCheck( FALSE );
			( ( CButton* )GetDlgItem( IDC_RADIO_CHOICE4 ) )->SetCheck( FALSE );
		}
		else if (m_choiceMode == MODE_IN_DATE)
		{
			( ( CButton* )GetDlgItem( IDC_RADIO_CHOICE1 ) )->SetCheck( FALSE ); 
			( ( CButton* )GetDlgItem( IDC_RADIO_CHOICE2 ) )->SetCheck( TRUE );
			( ( CButton* )GetDlgItem( IDC_RADIO_CHOICE3 ) )->SetCheck( FALSE );
			( ( CButton* )GetDlgItem( IDC_RADIO_CHOICE4 ) )->SetCheck( FALSE );
		}
		else if (m_choiceMode == MODE_IN_HANDLINGTYPE)
		{
			( ( CButton* )GetDlgItem( IDC_RADIO_CHOICE1 ) )->SetCheck( FALSE ); 
			( ( CButton* )GetDlgItem( IDC_RADIO_CHOICE2 ) )->SetCheck( FALSE );
			( ( CButton* )GetDlgItem( IDC_RADIO_CHOICE3 ) )->SetCheck( TRUE );
			( ( CButton* )GetDlgItem( IDC_RADIO_CHOICE4 ) )->SetCheck( FALSE );
		}
		else if (m_choiceMode == MODE_IN_REGION)
		{
			( ( CButton* )GetDlgItem( IDC_RADIO_CHOICE1 ) )->SetCheck( FALSE ); 
			( ( CButton* )GetDlgItem( IDC_RADIO_CHOICE2 ) )->SetCheck( FALSE );
			( ( CButton* )GetDlgItem( IDC_RADIO_CHOICE3 ) )->SetCheck( FALSE );
			( ( CButton* )GetDlgItem( IDC_RADIO_CHOICE4 ) )->SetCheck( TRUE );
		}

		//getValue();

		return FALSE;
	}

	void vggiPipeInfoResearchDlg::OnTimer(UINT_PTR nIDEvent)
	{
		CDialog::OnTimer(nIDEvent);
	}

	void vggiPipeInfoResearchDlg::getValue()
	{
		GeometryPointerVec pipeLineVec = m_ogrPipeLineMap->getGeometriesRef();

		CString num, keyName;
		eachRow rowValue;
		for (int i = 0; i < pipeLineVec.size(); i++)
		{			
			num.Format("%d", i);
			keyName = _T("管线") + num;
			char* keyValue = keyName.GetBuffer(keyName.GetLength());
			CBCGPGridRow* pRow = m_wndGrid.CreateRow(m_wndGrid.GetColumnCount ());
			pRow->GetItem(0)->AllowEdit(FALSE);
			pRow->GetItem(0)->SetValue(i);
			pRow->GetItem(1)->SetValue(keyValue);			
			m_wndGrid.AddRow(pRow, TRUE);	

			rowValue.ID = i;
			rowValue.keyName = keyName;
			m_pipeLineVec.push_back(rowValue);
		}		
	}

	void vggiPipeInfoResearchDlg::getHandlingValue(ChoiceMode mode)
	{
		CString num, keyName;
		int valvesNum = 0;
		int tripleHandlingNum = 0;
		int FourHandlingNum = 0;
		eachRow rowValue;

		PipeGeoPtrVector pipeGeoVec = m_ogrPipeLineMap->getAllPipeGeo();

		for (int i = 0; i < pipeGeoVec.size(); i++)                                                             
		{
			if (pipeGeoVec[i]->getType() == PIPEGEO_VALVES)
			{
				num.Format("%d", ++valvesNum);
				keyName = _T("阀门") + num;
				char *keyValue = keyName.GetBuffer(keyName.GetLength());
				CBCGPGridRow* pRow = m_wndGrid.CreateRow(m_wndGrid.GetColumnCount());
				pRow->GetItem(0)->AllowEdit(FALSE);
				pRow->GetItem(0)->SetValue(i);
				pRow->GetItem(1)->SetValue(keyValue);				
				m_wndGrid.AddRow(pRow, TRUE);	

				rowValue.ID = i;
				rowValue.keyName = keyName;
				m_valvesVec.push_back(rowValue);
			}

			if (pipeGeoVec[i]->getType() == PIPEGEO_TRIPLEHANDLING)
			{
				num.Format("%d", ++tripleHandlingNum);
				keyName = _T("三通") + num;
				char *keyValue = keyName.GetBuffer(keyName.GetLength());
				CBCGPGridRow* pRow = m_wndGrid.CreateRow(m_wndGrid.GetColumnCount());
				pRow->GetItem(0)->AllowEdit(FALSE);
				pRow->GetItem(0)->SetValue(i);
				pRow->GetItem(1)->SetValue(keyValue);				
				m_wndGrid.AddRow(pRow, TRUE);	

				rowValue.ID = i;
				rowValue.keyName = keyName;
				m_tripleHandlingVec.push_back(rowValue);
			}

			if (pipeGeoVec[i]->getType() == PIPEGEO_FOURHANDLING)
			{
				num.Format("%d", ++FourHandlingNum);
				keyName = _T("四通") + num;
				char *keyValue = keyName.GetBuffer(keyName.GetLength());
				CBCGPGridRow* pRow = m_wndGrid.CreateRow(m_wndGrid.GetColumnCount());
				pRow->GetItem(0)->AllowEdit(FALSE);
				pRow->GetItem(0)->SetValue(i);
				pRow->GetItem(1)->SetValue(keyValue);				
				m_wndGrid.AddRow(pRow, TRUE);	

				rowValue.ID = i;
				rowValue.keyName = keyName;
				m_fourHandlingVec.push_back(rowValue);				
			}
		}
	}

	void vggiPipeInfoResearchDlg::OnBnClickedRadioMaterial()
	{
		m_choiceMode = MODE_IN_MATERIAL;

		m_selectTyple.ResetContent();
		m_selectTyple.AddString("普通材质");
		m_selectTyple.AddString("特殊材质");				

		//m_selectTyple.SetCurSel(0);
		if (m_pipeLineVec.empty())
		{
			m_wndGrid.RemoveAll();
			getValue();
		}

		UpdateData(FALSE);
	}

	void vggiPipeInfoResearchDlg::OnBnClickedRadioDate()
	{
		m_choiceMode = MODE_IN_DATE;

		m_selectTyple.ResetContent();
		m_selectTyple.AddString("一期");
		m_selectTyple.AddString("二期");
		m_selectTyple.AddString("三期");		

		//m_selectTyple.SetCurSel(0);
		if (m_pipeLineVec.empty())
		{
			m_wndGrid.RemoveAll();
			getValue();
		}


		UpdateData(FALSE);
	}

	void vggiPipeInfoResearchDlg::OnBnClickedRadioHandlingType()
	{
		m_choiceMode = MODE_IN_HANDLINGTYPE;		

		m_selectTyple.ResetContent();		
		m_selectTyple.AddString("三通");
		m_selectTyple.AddString("四通");
		m_selectTyple.AddString("阀门");

		//m_selectTyple.SetCurSel(0);
		m_wndGrid.RemoveAll();
		getHandlingValue(m_choiceMode);

		if (!m_pipeLineVec.empty())
		{
			m_pipeLineVec.clear();
		}

		UpdateData(FALSE);
	}

	void vggiPipeInfoResearchDlg::OnBnClickedRadioRegion()
	{
		m_choiceMode = MODE_IN_REGION;
		
		m_selectTyple.ResetContent();
		m_selectTyple.AddString("城区");
		m_selectTyple.AddString("郊区");		

		//m_selectTyple.SetCurSel(0);
		if (m_pipeLineVec.empty())
		{
			m_wndGrid.RemoveAll();
			getValue();
		}

		UpdateData(FALSE);
	}

	void vggiPipeInfoResearchDlg::OnCbnSelchangeTyle()
	{
		// TODO: 在此添加控件通知处理程序代码
		CString wndStr, selectNameStr;

		int nSelIndex = 0;
		eachRow rowValue;
		nSelIndex = m_selectTyple.GetCurSel();
		if ( -1 == nSelIndex )
		{
			return;
		}

		wndStr.GetBuffer(m_selectTyple.GetLBTextLen( nSelIndex ));
		m_selectTyple.GetLBText(m_selectTyple.GetCurSel(), wndStr);

		selectNameStr = wndStr.GetString();
		if (m_choiceMode == MODE_IN_HANDLINGTYPE)
		{
			if (selectNameStr == _T("三通"))
			{
				m_wndGrid.RemoveAll();				
				for (int i = 0; i < m_tripleHandlingVec.size(); i++)
				{
					rowValue = m_tripleHandlingVec[i];
					CString keyName = rowValue.keyName;
					CBCGPGridRow* pRow = m_wndGrid.CreateRow(m_wndGrid.GetColumnCount());
					char* keyValue = keyName.GetBuffer(keyName.GetLength());
					pRow->GetItem(0)->AllowEdit(FALSE);
					pRow->GetItem(0)->SetValue(rowValue.ID);
					pRow->GetItem(1)->SetValue(keyValue);
					m_wndGrid.AddRow(pRow, TRUE);					
				}
			}
			if (selectNameStr == _T("四通"))
			{
				m_wndGrid.RemoveAll();
				for (int i = 0; i < m_fourHandlingVec.size(); i++)
				{
					rowValue = m_fourHandlingVec[i];
					CString keyName = rowValue.keyName;
					CBCGPGridRow* pRow = m_wndGrid.CreateRow(m_wndGrid.GetColumnCount());
					char* keyValue = keyName.GetBuffer(keyName.GetLength());
					pRow->GetItem(0)->AllowEdit(FALSE);
					pRow->GetItem(0)->SetValue(rowValue.ID);
					pRow->GetItem(1)->SetValue(keyValue);
					m_wndGrid.AddRow(pRow, TRUE);									
				}
			}
			if (selectNameStr == _T("阀门"))
			{
				m_wndGrid.RemoveAll();
				for (int i = 0; i < m_valvesVec.size(); i++)
				{
					rowValue = m_valvesVec[i];
					CString keyName = rowValue.keyName;
					CBCGPGridRow* pRow = m_wndGrid.CreateRow(m_wndGrid.GetColumnCount());
					char* keyValue = keyName.GetBuffer(keyName.GetLength());
					pRow->GetItem(0)->AllowEdit(FALSE);
					pRow->GetItem(0)->SetValue(rowValue.ID);
					pRow->GetItem(1)->SetValue(keyValue);
					m_wndGrid.AddRow(pRow, TRUE);								
				}				
			}
		}
	}

	void vggiPipeInfoResearchDlg::OnTurnSelectToView()
	{
		if (m_choiceMode == MODE_IN_HANDLINGTYPE)
		{
			vector<JointPointPtr>* jointArray = 
				vgGIS3D::GisManager::getSingleton().getJointArray();

			m_wndGrid.Invalidate(true);

			CBCGPGridRow *pNowRow = m_wndGrid.GetCurSel();

			if (pNowRow != NULL)
			{				
				int index = pNowRow->GetItem(0)->GetValue().intVal;				
				
				PipeGeoPtrVector pipeGeoVec = m_ogrPipeLineMap->getAllPipeGeo();	
				vgCam::CamFacade::gotoBox( m_ogrPipeLineMap->getPipeGeoBox(pipeGeoVec[index]) );
			}
			else
			{
				AfxMessageBox("请选择节点");
				return;
			}
		}
		else
		{
			m_wndGrid.Invalidate(true);

			GeometryPointerVec geoPointerVec = m_ogrPipeLineMap->getGeometriesRef();
			CBCGPGridRow *pNowRow = m_wndGrid.GetCurSel();

			if (pNowRow != NULL)
			{
				int index = pNowRow->GetItem(0)->GetValue().intVal;
				LineString *pLineString = dynamic_cast<LineString*>(geoPointerVec[index]);

				if (pLineString != NULL)
				{
					vgCam::CamFacade::gotoBox(m_ogrPipeLineMap->getPipeLineBox(pLineString));
					m_ogrPipeLineMap->addPipeLineToView(pLineString);
				}
				else
				{
					assert(0);
				}
			}
			else
			{
				return;
			}
		}
	}



}//end NameSpace





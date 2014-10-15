
#include <vgStableHeaders.h>
#include <vgGIS3D/vggiDlgContourEditor.h>
#include <vgGIS3D/vggiContourManager.h>
#include <vgGIS/vgGisManager.h>
#include <vgGIS3D/vggiDlgInputVal.h>

namespace vgGIS3D
{
	const static int WND_OFFSET = 125; 

	// vgDlgContourEditor 对话框

	IMPLEMENT_DYNAMIC(vgDlgContourEditor, CDialog)

		vgDlgContourEditor::vgDlgContourEditor(CWnd* pParent /*=NULL*/)
		: CDialog(vgDlgContourEditor::IDD, pParent)
	{

	}

	vgDlgContourEditor::~vgDlgContourEditor()
	{
	}

	void vgDlgContourEditor::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		DDX_Control(pDX, IDC_CONTOUR_LIST, m_wndGridLocation);
		DDX_Control(pDX, IDC_STATIC_CB1, m_colorBar1);
		DDX_Control(pDX, IDC_STATIC_CB2, m_colorBar2);

		DDX_Control(pDX, IDC_CONTOUR_COMBO, m_nameCombo);
		DDX_Text(pDX, IDC_CONTOUR_INFO, m_info);
		DDX_Check(pDX,IDC_CONTOUR_ENABLE_RENDER, m_enableRender );
		DDX_Control(pDX, IDC_AUTOCOLOR, m_autoColor);
	}

	BEGIN_MESSAGE_MAP(vgDlgContourEditor, CDialog)
		ON_CBN_SELCHANGE(IDC_CONTOUR_COMBO, &vgDlgContourEditor::OnCbnSelNameCombo)
		ON_BN_CLICKED(IDC_CONTOUR_ENABLE_RENDER, &vgDlgContourEditor::OnCheckRender)
		ON_BN_CLICKED(IDC_CONTOUR_ADD, &vgDlgContourEditor::OnBnClickedBtnAdd)
		ON_BN_CLICKED(IDC_CONTOUR_DEL, &vgDlgContourEditor::OnBnClickedBtnDelete)
		ON_BN_CLICKED(IDC_CONTOUR_REBUILD, &vgDlgContourEditor::OnBnClickedBtnRebuild)
		ON_BN_CLICKED(IDC_AUTOCOLOR, &vgDlgContourEditor::OnBnClickedBtnAutoColor)
		ON_BN_CLICKED(IDC_BUTTON_GEM_COLOR, &vgDlgContourEditor::OnBnClickedBtnGenColor)

		ON_COMMAND(IDC_STATIC_CB1, OnColorBar)
	
		ON_WM_TIMER()
	END_MESSAGE_MAP()

	// vgDlgContourEditor 消息处理程序

	void vgGIS3D::vgDlgContourEditor::OnCheckRender()
	{
		CString contourName;
		
		UpdateData();

		int selInt = m_nameCombo.GetCurSel();

		if ( selInt < 0 )
		{
			return ;
		}

		contourName.GetBuffer(m_nameCombo.GetLBTextLen(selInt));

		m_nameCombo.GetLBText(selInt, contourName);

		Contour *pContour = ContourManager::getSingleton().getContourByName(contourName.GetString());
		
		if (pContour == NULL)
		{
			return ;
		}

		if (m_enableRender)
		{
			pContour->SetVisiable(true);	
		}
		else
		{
			pContour->SetVisiable(false);
		}
	}

	BOOL vgGIS3D::vgDlgContourEditor::OnInitDialog()
	{
		CDialog::OnInitDialog();

		// TODO:  在此添加额外的初始化
		// TODO:  在此添加额外的初始化
		// TODO:  在此添加您专用的创建代码

		// Process Combo
		int numOfContour = ContourManager::getSingleton().getNumOfContour();

		for (int i=0; i<numOfContour; i++)
		{
			m_nameCombo.AddString(
				ContourManager::getSingleton().getContour(i)->GetName().c_str());
		}


		// TODO: Add extra initialization here
		CRect rectGrid;
		m_wndGridLocation.GetClientRect (&rectGrid);

		m_wndGridLocation.MapWindowPoints (this, &rectGrid);

		m_wndGrid.Create (WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rectGrid, this, (UINT)-1);
		m_wndGrid.EnableHeader (TRUE, BCGP_GRID_HEADER_MOVE_ITEMS);
		// 	m_wndGrid.SetColumnAlign(0, 1);
		// 	m_wndGrid.SetColumnAlign(1, 0);
		// 	m_wndGrid.SetColumnAlign(2, 2);

		// m_wndGrid.SetReadOnly ();
		// m_wndGrid.Sort(1);

		m_wndGrid.SetHeaderAlign(0,HDF_LEFT);
		m_wndGrid.SetHeaderAlign(1,HDF_LEFT);
		m_wndGrid.SetHeaderAlign(2,HDF_LEFT);

		m_wndGrid.InsertColumn (0, _T("序号"), 50);
		m_wndGrid.InsertColumn (1, _T("等值线值"), 80);
		m_wndGrid.InsertColumn (2, _T("颜色"), 75);
		m_wndGrid.SetWholeRowSel(TRUE);

		m_info = "信息显示";
		m_enableRender = FALSE;

		SetTimer(1, 500, NULL);

		m_autoColor.SetWindowText("自动着色 >>");

		RECT rect;

		GetWindowRect(&rect);

		SetWindowPos(NULL, rect.left, rect.top, rect.right-rect.left-WND_OFFSET,rect.bottom-rect.top, SWP_NOMOVE | SWP_NOZORDER);

		UpdateData (FALSE);

		CRect rectColorBar;
		m_colorBar1.GetClientRect (&rectColorBar);
		m_colorBar1.MapWindowPoints (this, &rectColorBar);

		m_wndColorBar1.SetHorzMargin (0);
		m_wndColorBar1.SetVertMargin (0);
		m_wndColorBar1.EnableOtherButton (_T("Other..."));

		m_wndColorBar1.CreateControl (this, rectColorBar, IDC_STATIC_CB1, 5 /* columns */);
		m_wndColorBar1.SetColor (RGB (0, 0, 0));

		m_colorBar2.GetClientRect (&rectColorBar);
		m_colorBar2.MapWindowPoints (this, &rectColorBar);

		m_wndColorBar2.SetHorzMargin (0);
		m_wndColorBar2.SetVertMargin (0);
		m_wndColorBar2.EnableOtherButton (_T("Other..."));

		m_wndColorBar2.CreateControl (this, rectColorBar, IDC_STATIC_CB2, 5 /* columns */);
		m_wndColorBar2.SetColor (RGB (0, 0, 0));

		return TRUE;  // return TRUE unless you set the focus to a control
		// 异常: OCX 属性页应返回 FALSE
	}

	void vgDlgContourEditor::OnCbnSelNameCombo()
	{
		UpdateData();

		m_wndGrid.RemoveAll();
		
		CString contourName;
		
		int selInt = m_nameCombo.GetCurSel();
		
		contourName.GetBuffer(m_nameCombo.GetLBTextLen(selInt));

		m_nameCombo.GetLBText(selInt, contourName);
		
		Contour *pContour = ContourManager::getSingleton().getContourByName(contourName.GetString());
		

		vgKernel::Box box = pContour->getBoundingBox();
		
		m_info.Format("面积 %.3f × %.3f 高程 %.3f - %.3f ", box.getSize().x, 
			 box.getSize().z, box.getMinimum().y, box.getMaximum().y);
		
		int numOfValue = pContour->GetNumberOfValues();
		
		if ( pContour->GetVisiable())
		{
			m_enableRender = TRUE;
		}
		else
		{
			m_enableRender = FALSE;
		}

 		for (int i=0; i<numOfValue; i++)
 		{
			float val = pContour->GetValue(i);
			vgKernel::ColorVal col = pContour->GetColorByValue(val);
			
			CBCGPGridRow* pRow = m_wndGrid.CreateRow(m_wndGrid.GetColumnCount ());
			pRow->GetItem(0)->SetValue(i);
			pRow->GetItem(0)->AllowEdit(FALSE);

			pRow->GetItem(1)->SetValue(val);
//  			_variant_t v;
//  			v.fltVal = val;
//  			pRow->ReplaceItem(1, new CBCGPGridItem (v));
			CBCGPGridColorItem* pColorItem = new CBCGPGridColorItem (
				col.getAsColorRef());

			ASSERT_VALID (pColorItem);

			pColorItem->EnableOtherButton (_T("Other"));

			pRow->ReplaceItem (2, pColorItem);

			m_wndGrid.AddRow(pRow, TRUE);
 		}

		UpdateData(FALSE);
	}

	void vgDlgContourEditor::OnTimer(UINT_PTR nIDEvent)
	{
		UpdateData();

		CDialog::OnTimer(nIDEvent);

		CString contourName;

		m_wndGrid.Invalidate(true);

		int selInt = m_nameCombo.GetCurSel();

		if (selInt < 0)
		{
			return ;
		}

		contourName.GetBuffer(m_nameCombo.GetLBTextLen(selInt));

		m_nameCombo.GetLBText(selInt, contourName);

		Contour *pContour = ContourManager::getSingleton().getContourByName(contourName.GetString());

		if (pContour != NULL)
		{
			int rows = m_wndGrid.GetRowCount();

			for (int i=0; i<rows; i++)
			{
				CBCGPGridRow *pRow = m_wndGrid.GetRow(i);

				CBCGPGridColorItem *item 
					= dynamic_cast<CBCGPGridColorItem*>(pRow->GetItem(2));
			
				vgKernel::ColorVal color;
				color.setAsColorRef(item->GetColor());

				pContour->SetColorByValue(pRow->GetItem(1)->GetValue().fltVal, color);
			}
		}
		
	}

	void vgDlgContourEditor::OnBnClickedBtnAdd()
	{
		float val;

		int selInt = m_nameCombo.GetCurSel();

		if (selInt < 0)
		{
			AfxMessageBox("没有选择等值线");
			return ;
		}

		CString contourName;

		contourName.GetBuffer(m_nameCombo.GetLBTextLen(selInt));

		m_nameCombo.GetLBText(selInt, contourName);

		Contour *pContour = ContourManager::getSingleton().getContourByName(contourName.GetString());

		vgDlgInputVal dlg;
		
		if (dlg.DoModal() == IDOK)
		{
			val = dlg.getVal();
			if (pContour != NULL)
			{
				// 需要线程同步
				pContour->useBind(true);

				pContour->AddContourValue(val);
				vgGIS3D::GisManager::getSingleton().setProcessingInfo("更新等值线...");
				vgGIS3D::GisManager::getSingleton().showProcessingDlg(true);
				pContour->GenerateContours(true);
				pContour->attachToTerrain();
				vgGIS3D::GisManager::getSingleton().showProcessingDlg(false);
				OnCbnSelNameCombo();
			
				pContour->unBind();
			}
		}

	}

	void vgDlgContourEditor::OnBnClickedBtnDelete()
	{
		CBCGPGridRow	*pRow = m_wndGrid.GetCurSel();
		
		for (int i=0; i<m_wndGrid.GetRowCount(); i++)
		{
			if (pRow == m_wndGrid.GetRow(i))
			{
				TRACE("Select row %d \n", i);
			}
		}

		if (pRow == NULL)
		{
			AfxMessageBox("请在列表中选择一列值.");
			return ;
		}

		int selInt = m_nameCombo.GetCurSel();

		if (selInt < 0)
		{
			return ;
		}

		CString contourName;
		contourName.GetBuffer(m_nameCombo.GetLBTextLen(selInt));

		m_nameCombo.GetLBText(selInt, contourName);

		Contour *pContour = ContourManager::getSingleton().getContourByName(contourName.GetString());

		if (pContour != NULL)
		{
			float val = pRow->GetItem(1)->GetValue().fltVal;
			TRACE("Delete %f \n", val);

			pContour->useBind(true);
			pContour->DeleteContourValue(val);
			
			vgGIS3D::GisManager::getSingleton().setProcessingInfo("更新等值线...");
			vgGIS3D::GisManager::getSingleton().showProcessingDlg(true);
			pContour->GenerateContours(true);
			pContour->attachToTerrain();
			vgGIS3D::GisManager::getSingleton().showProcessingDlg(false);
			pContour->unBind();
		}

		OnCbnSelNameCombo();
	}

	void vgDlgContourEditor::OnBnClickedBtnRebuild()
	{
		int selInt = m_nameCombo.GetCurSel();

		if (selInt < 0)
		{
			return ;
		}

		CString contourName;
		contourName.GetBuffer(m_nameCombo.GetLBTextLen(selInt));

		m_nameCombo.GetLBText(selInt, contourName);

		Contour *pContour = ContourManager::getSingleton().getContourByName(contourName.GetString());

		pContour->RemoveAllContours();

  		if (pContour != NULL)
  		{
			int rows = m_wndGrid.GetRowCount();
			pContour->useBind(true);

			pContour->DeleteAllContourValue();
			
			for (int i=0; i<rows; i++)
			{
				CBCGPGridRow *pRow = m_wndGrid.GetRow(i);

				CBCGPGridColorItem *item 
					= dynamic_cast<CBCGPGridColorItem*>(pRow->GetItem(2));

				vgKernel::ColorVal color;
				color.setAsColorRef(item->GetColor());
			
				pContour->AddContourValue(pRow->GetItem(1)->GetValue().fltVal);
				
				pContour->SetColorByValue(pRow->GetItem(1)->GetValue().fltVal, color);
			}

			vgGIS3D::GisManager::getSingleton().setProcessingInfo("更新等值线...");
			vgGIS3D::GisManager::getSingleton().showProcessingDlg(true);
 			pContour->GenerateContours(true);
			pContour->attachToTerrain();
			vgGIS3D::GisManager::getSingleton().showProcessingDlg(false);

			pContour->unBind();
		}
	}

	void vgDlgContourEditor::OnBnClickedBtnAutoColor()
	{
		// AfxMessageBox("Auto Color");
		RECT rect;

		CString wndText;
		m_autoColor.GetWindowText(wndText);
	
		if (wndText == "自动着色 >>")
		{
			m_autoColor.SetWindowText("<< 自动着色");
			
			GetWindowRect(&rect);

			SetWindowPos(NULL, rect.left, rect.top, rect.right-rect.left+WND_OFFSET,rect.bottom-rect.top, SWP_NOMOVE | SWP_NOZORDER);
		}
		else
		{
			m_autoColor.SetWindowText("自动着色 >>");

			GetWindowRect(&rect);

			SetWindowPos(NULL, rect.left, rect.top, rect.right-rect.left-WND_OFFSET,rect.bottom-rect.top, SWP_NOMOVE | SWP_NOZORDER);

		}

	}

	void vgDlgContourEditor::OnBnClickedBtnGenColor()
	{
		UpdateData(TRUE);

		CString contourName;

		int selInt = m_nameCombo.GetCurSel();

		if (selInt < 0)
		{
			AfxMessageBox("未选择等值线.");

			return;
		}

		contourName.GetBuffer(m_nameCombo.GetLBTextLen(selInt));

		m_nameCombo.GetLBText(selInt, contourName);

		Contour *pContour = ContourManager::getSingleton().getContourByName(contourName.GetString());

		if (pContour == NULL)
		{
			AfxMessageBox("未选择等值线.");

			return ;
		}

		COLORREF color = m_wndColorBar1.GetColor();
		COLORREF color2 = m_wndColorBar2.GetColor();

		vgKernel::ColorVal c1, c2, cc;
		c1.setAsColorRef(color);
		c2.setAsColorRef(color2);

		int numOfValue = pContour->GetNumberOfValues();

		float ri, gi, bi;
		ri = (c2.r - c1.r) / numOfValue;
		gi = (c2.g - c1.g) / numOfValue;
		bi = (c2.b - c1.b) / numOfValue;

		for (int i=0; i<numOfValue; i++)
		{
			float v = pContour->GetValue(i);

			pContour->SetColorByValue(v, vgKernel::ColorVal(c1.r+ri*i, c1.g+gi*i, c1.b+bi*i, 0));
		}

		OnCbnSelNameCombo();
	}

	void vgDlgContourEditor::OnColorBar()
	{
	
	}
}

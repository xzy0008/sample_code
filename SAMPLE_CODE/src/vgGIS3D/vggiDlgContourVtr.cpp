
#include <vgStableHeaders.h>
#include <vgGIS3D/vggiDlgContourVtr.h>
#include <vgGIS3D/vggiContourManager.h>

namespace vgGIS3D
{
	// vgDlgContourVtr 对话框

	IMPLEMENT_DYNAMIC(vgDlgContourVtr, CDialog)

		vgDlgContourVtr::vgDlgContourVtr(vgKernel::Vec3 area, CWnd* pParent /*=NULL*/)
		: CDialog(vgDlgContourVtr::IDD, pParent)
	{	
		m_area = area;
		m_step = 3;
		m_numOfLine = 10;
	}

	vgDlgContourVtr::~vgDlgContourVtr()
	{

	}

	void vgDlgContourVtr::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		DDX_Text(pDX, IDC_VTR_CONTOUR_STEP, m_step);
		DDX_Text(pDX, IDC_VTR_CONTOUR_NUM,	m_numOfLine);
		DDX_Text(pDX, IDC_VTR_CONTOUR_INFO, m_info);
		DDX_Text(pDX, IDC_VTR_CONTOUR_NAME, m_contourName);
	}


	BEGIN_MESSAGE_MAP(vgDlgContourVtr, CDialog)
	END_MESSAGE_MAP()


	// vgDlgContourVtr 消息处理程序

}

BOOL vgGIS3D::vgDlgContourVtr::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	m_info.Format("用户选择区域大小: %.0f × %.0f ", m_area.x, m_area.z);
	
	UpdateData(FALSE);
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void vgGIS3D::vgDlgContourVtr::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	UpdateData(TRUE);

	if (m_contourName.GetLength() == 0 || m_step < 0 || abs(m_step-0) < 1e-3 || m_numOfLine <= 0 )
	{
		AfxMessageBox("输入参数错误，请重新输入.");
	
		return ;
	}
	
	// Added By FengYK @2010-03-26 21:33 增加判断等值线是否重名功能
	int numOfContour = ContourManager::getSingleton().getNumOfContour();

	for (int i=0; i<numOfContour; i++)
	{
		std::string str_contourName = ContourManager::getSingleton().getContour(i)->GetName();

		if ( m_contourName.GetString() == str_contourName )
		{
			AfxMessageBox("已存在同名地形等值线,请重新输入等值线名称!");
			return;
		}
	}
	CDialog::OnOK();
}

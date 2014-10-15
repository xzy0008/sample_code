// FaecherAnalysisDlg.cpp : 实现文件
//

#include <vgStableHeaders.h>
#include <vgGIS3D/vggiFaecherAnalysisDlg.h>
#include <vgGis/vggisAnalysisHandle.h>
#include <vgKernel/vgkRendererManager.h>
#include <vgGIS/vgGisManager.h>


// FaecherAnalysisDlg 对话框

IMPLEMENT_DYNAMIC(FaecherAnalysisDlg, CDialog)

FaecherAnalysisDlg::FaecherAnalysisDlg(CWnd* pParent /*=NULL*/)
	: CDialog(FaecherAnalysisDlg::IDD, pParent)
{
}

FaecherAnalysisDlg::~FaecherAnalysisDlg()
{
}

void FaecherAnalysisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_STATIC, m_static);
}


BEGIN_MESSAGE_MAP(FaecherAnalysisDlg, CDialog)
	
END_MESSAGE_MAP()


// FaecherAnalysisDlg 消息处理程序
void FaecherAnalysisDlg::ShowName(std::deque<String> NameQue, int columnNum)
{
	int RowNum = 0;
	std::deque<String>::iterator iter = NameQue.begin();
	std::deque<String>::iterator end_iter = NameQue.end();

	for(; iter!=end_iter; iter++)
	{
		String name = *iter;
		m_List.GetRow(RowNum)->GetItem(columnNum)->SetValue(name.c_str());
		RowNum++;
	}


}

BOOL FaecherAnalysisDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString contain = "包含";
	CString disjoint = "相交";
	CString intersect = "相离";
	vgKernel::RendererQueue RenderQueTemp;

	CRect rect;
	m_static.GetClientRect(&rect);
	m_static.MapWindowPoints(this, &rect);
	m_List.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rect, this, (UINT)-1);
	m_List.EnableHeader(TRUE, BCGP_GRID_HEADER_MOVE_ITEMS);
	
	m_List.InsertColumn(0, contain, 178);
	m_List.InsertColumn(1, disjoint, 178);
	m_List.InsertColumn(2, intersect, 178);

	if ((m_ContainQue.size() > m_DisjointQue.size()) && (m_ContainQue.size() > m_IntersectQue.size()))
	{
		RenderQueTemp = m_ContainQue;
	}
	if ((m_DisjointQue.size() > m_ContainQue.size()) && (m_DisjointQue.size() > m_IntersectQue.size()))
	{
		RenderQueTemp = m_DisjointQue;
	}
	if ((m_IntersectQue.size() > m_ContainQue.size()) && (m_IntersectQue.size() > m_DisjointQue.size()))
	{
		RenderQueTemp = m_IntersectQue;
	}

	vgKernel::RendererQueue::iterator iter = RenderQueTemp.begin();
	vgKernel::RendererQueue::iterator end_iter = RenderQueTemp.end();

	for (; iter!=end_iter; iter++)
	{
		CBCGPGridRow*  pRow = m_List.CreateRow(m_List.GetColumnCount());
		for (int i = 0; i<m_List.GetColumnCount(); i++)
		{
			pRow->GetItem(i)->AllowEdit (FALSE);
		}
		m_List.AddRow(pRow, TRUE);
	}

	ShowName(GetName(m_ContainQue), 0);
	ShowName(GetName(m_IntersectQue), 1);
	ShowName(GetName(m_DisjointQue), 2);
	return 0;
}


std::deque<String> FaecherAnalysisDlg::GetName(vgKernel::RendererQueue  que)
{
	String name;
	std::deque<String> NameQue;
	vgKernel::RendererQueue::iterator iter = que.begin();
	vgKernel::RendererQueue::iterator end_iter = que.end();

	for (; iter!=end_iter; iter++)
	{
		vgKernel::Renderer* pRenderer = *iter;
		name = pRenderer->getName();
		NameQue.push_back(name);
	}
	return NameQue;
}

void FaecherAnalysisDlg::OnOK()
{
// 	if (isLineVisible == true)
// 	{
// 		isLineVisible = false;
// 	}
	vgGIS3D::GisManager::getSingleton().getGisAnalysis()->SetbOperationDone(false);

	CDialog::OnOK();

}

void FaecherAnalysisDlg::OnCancel()
{
	vgGIS3D::GisManager::getSingleton().getGisAnalysis()->SetbOperationDone(false);
	CDialog::OnCancel();
}
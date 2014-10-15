// outputbar.cpp : implementation of the COutputBar class
//

#include <vgStableHeaders.h>
#include "vgFrameWork.h"
#include "vgoutputbar.h"

#include <vgKernel/vgkLogManager.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int nBorderSize = 1;
/////////////////////////////////////////////////////////////////////////////
// COutputBar

BEGIN_MESSAGE_MAP(vgOutputBar, CBCGPDockingControlBar)
	//{{AFX_MSG_MAP(COutputBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutputBar construction/destruction

vgOutputBar::vgOutputBar()
{
	// TODO: add one-time construction code here
}

vgOutputBar::~vgOutputBar()
{
}

/////////////////////////////////////////////////////////////////////////////
// COutputBar message handlers

int vgOutputBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rectDummy;
	rectDummy.SetRectEmpty ();


	// Create list window.
	// TODO: create your own window here:
// 	const DWORD dwViewStyle =	
// 		LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;
// 	
// 	if (!m_wndList.Create (dwViewStyle, rectDummy, this, 1))
// 	{
// 		TRACE0("Failed to create output view\n");
// 		return -1;      // fail to create
// 	}
	const DWORD dwViewStyle =	
		ES_READONLY | ES_AUTOVSCROLL | ES_MULTILINE  | WS_CHILD | WS_VISIBLE | WS_VSCROLL;

	if (! m_editLog.Create(dwViewStyle, rectDummy, this, 1))
	{
 		TRACE0("Failed to create output view\n");
 		return -1;      // fail to create
	}
	m_editLog.SetBkColor(WHITE);

	m_editLog.SetMargins( 10 ,10 );
	//m_editLog.set
	
	vgKernel::LogManager::getSingleton().getDefaultLog()->addListener(this);

	return 0;
}

void vgOutputBar::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);

// 	m_wndList.SetWindowPos (NULL, nBorderSize, nBorderSize, 
// 		cx - 2 * nBorderSize, cy - 2 * nBorderSize,
// 		SWP_NOACTIVATE | SWP_NOZORDER);
	 	m_editLog.SetWindowPos (NULL, nBorderSize, nBorderSize, 
	 		cx - 2 * nBorderSize, cy - 2 * nBorderSize,
	 		SWP_NOACTIVATE | SWP_NOZORDER);
//	m_editLog.LineScroll(m_editLog.GetLineCount());

}

void vgOutputBar::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rectList;
	/*m_wndList.GetWindowRect (rectList);*/
	m_editLog.GetWindowRect (rectList);
	ScreenToClient (rectList);

	rectList.InflateRect (1, 1);
	dc.Draw3dRect (rectList,	::GetSysColor (COLOR_3DSHADOW), 
								::GetSysColor (COLOR_3DSHADOW));
}

void vgOutputBar::AddContent(  const String& content )
{

	//int  nLength  =  m_editLog.SendMessage(WM_GETTEXTLENGTH);
	//m_editLog.SetSel(nLength, nLength);
	//m_editLog.ReplaceSel( content.c_str() ); 

	////if ( m_editLog.GetLineCount() > 100 )
	////{
	////	
	////}

	////(*_contentStream) << content;

	////m_editLog.SetWindowText( _contentStream->rdbuf()->eback() );
	////m_editLog.LineScroll(m_editLog.GetLineCount());


	//return;

#if 1

	//replace_all(content, "\n", "\r\n");

	while ( m_contentList.size() >= 100 )
	{
		String* itm = m_contentList.front();
		delete itm;
		m_contentList.pop_front();
	}

#define MAX_CHAR_NUM  4096

	size_t foundPos = 0;

	String* newstr = NULL;

	if ( content.size() > MAX_CHAR_NUM )
	{
		newstr = new String( content.end() - MAX_CHAR_NUM , content.end() );
	}
	else
	{
		newstr = new String( content );
	}
	
	while ( (foundPos = newstr->find("\n",foundPos)) != string::npos)
	{
		newstr->replace(foundPos, 1, "\r\n");
		foundPos   =   foundPos   +   2; 
	}

	m_contentList.push_back( newstr );


	int charcount = 0;
	int siz = m_contentList.size();

	int i = 0;

	for ( i = siz - 1 ; i >= 0; -- i )
	{
		String* str = m_contentList[i];

		charcount += str->size();
		if ( charcount > MAX_CHAR_NUM )
		{
			break;
		}
	}

	static String logContent;

	logContent.clear();

	if ( i < 0 )
	{
		i = 0;
	}
	for ( int j = i ; j < siz ; ++j )
	{
		logContent += *m_contentList[j];
	}

	m_editLog.SetWindowText( logContent.c_str() );
	m_editLog.LineScroll(m_editLog.GetLineCount());

#endif
}

void vgOutputBar::messageLogged( const String& message, vgKernel::LogMessageLevel lml, bool maskDebug, const String &logName )
{
	////TRACE("%s \n", message);
	if (lml == vgKernel::LML_SHOW)
	{
		AddContent(message);
	}
}
// string& vgOutputBar::replace_all(string&   str,const   string&   old_value,const   string&   new_value)  
// {  
// // 	while(true) {  
// // 		string::size_type   pos(0);  
// // 		if(   (pos=str.find(old_value))!=string::npos   )  
// // 			str.replace(pos,old_value.length(),new_value);  
// // 		else   break;  
// // 	}  
// 	return   string();  
// }   
void vgOutputBar::OnDestroy()
{
	vgKernel::LogManager::getSingleton().getDefaultLog()->removeListener(this);

	__super::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}

void vgOutputBar::ClearContent()
{
	//if ( _contentStream != NULL )
	//{
	//	delete _contentStream;
	//	_contentStream = new std::ostringstream;
	//}

	while ( m_contentList.size() > 0 )
	{
		String* itm = m_contentList.front();
		delete itm;
		m_contentList.pop_front();
	}

	m_editLog.SetWindowText( "" );
}

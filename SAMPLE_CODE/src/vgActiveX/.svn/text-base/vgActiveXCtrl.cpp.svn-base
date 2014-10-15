// vgActiveXCtrl.cpp : Implementation of the CvgActiveXCtrl ActiveX Control class.

#include <vgStableHeaders.h>
#include "vgActiveX.h"
#include "vgActiveXCtrl.h"
#include "vgActiveXPropPage.h"

#include <vgAppProcParameters.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

bool b_threadcontrol;

IMPLEMENT_DYNCREATE(CvgActiveXCtrl, COleControl)


vgCore::Root *p_root = new vgCore::Root("win_log.log");  //李文的全局变量
// Message map

BEGIN_MESSAGE_MAP(CvgActiveXCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_KILLFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEWHEEL()
	ON_WM_KEYUP()
END_MESSAGE_MAP()



// Dispatch map

BEGIN_DISPATCH_MAP(CvgActiveXCtrl, COleControl)
	DISP_FUNCTION_ID(CvgActiveXCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CvgActiveXCtrl, "ImportVgFile", dispidImportVgFile, ImportVgFile, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION_ID(CvgActiveXCtrl, "ImportVgFileDlg", dispidImportVgFileDlg, ImportVgFileDlg, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CvgActiveXCtrl, "SetGisPos", dispidSetGisPos, SetGisPos, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CvgActiveXCtrl, "SetGisDis", dispidSetGisDis, SetGisDis, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CvgActiveXCtrl, "SetGisArea", dispidSetGisArea, SetGisArea, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CvgActiveXCtrl, "SetGisVolume", dispidSetGisVolume, SetGisVolume, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CvgActiveXCtrl, "SetGisFlood", dispidSetGisFlood, SetGisFlood, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CvgActiveXCtrl, "SetGisWVolume", dispidSetGisWVolume, SetGisWVolume, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CvgActiveXCtrl, "SetGisMVolume", dispidSetGisMVolume, SetGisMVolume, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CvgActiveXCtrl, "SetGisP2P", dispidSetGisP2P, SetGisP2P, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CvgActiveXCtrl, "SetGisCut", dispidSetGisCut, SetGisCut, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CvgActiveXCtrl, "SetSeSnow", dispidSetSeSnow, SetSeSnow, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CvgActiveXCtrl, "OffSeSnow", dispidOffSeSnow, OffSeSnow, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CvgActiveXCtrl, "SetSeRain", dispidSetSeRain, SetSeRain, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CvgActiveXCtrl, "OffSeRain", dispidOffSeRain, OffSeRain, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CvgActiveXCtrl, "SetSeFog", dispidSetSeFog, SetSeFog, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CvgActiveXCtrl, "OffSeFog", dispidOffSeFog, OffSeFog, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CvgActiveXCtrl, "SetGisHawkEyeOn", dispidSetGisHawkEyeOn, SetGisHawkEyeOn, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CvgActiveXCtrl, "SetGisHawkEyeOff", dispidSetGisHawkEyeOff, SetGisHawkEyeOff, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CvgActiveXCtrl, "SetGisShadowOn", dispidSetGisShadowOn, SetGisShadowOn, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CvgActiveXCtrl, "SetGisShadowOff", dispidSetGisShadowOff, SetGisShadowOff, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CvgActiveXCtrl, "SwitchCam", dispidSwitchCam, SwitchCam, VT_EMPTY, VTS_I4)
	DISP_FUNCTION_ID(CvgActiveXCtrl, "StartPlayAni", dispidStartPlayAni, StartPlayAni, VT_EMPTY, VTS_I4)
	DISP_FUNCTION_ID(CvgActiveXCtrl, "SetGisContour", dispidSetGisContour, SetGisContour, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CvgActiveXCtrl, "DBInfoShow", dispidDBInfoShow, DBInfoShow, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION_ID(CvgActiveXCtrl, "OnMusicOn", dispidOnMusicOn, OnMusicOn, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CvgActiveXCtrl, "OnMusicOff", dispidOnMusicOff, OnMusicOff, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CvgActiveXCtrl, "SetGisWaterLevel", dispidSetGisWaterLevel, SetGisWaterLevel, VT_EMPTY, VTS_R4)
	DISP_FUNCTION_ID(CvgActiveXCtrl, "ImportDemDom", dispidImportDemDom, ImportDemDom, VT_EMPTY, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CvgActiveXCtrl, "ImportDemDomDlg", dispidImportDemDomDlg, ImportDemDomDlg, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()



// Event map

BEGIN_EVENT_MAP(CvgActiveXCtrl, COleControl)
END_EVENT_MAP()



// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CvgActiveXCtrl, 1)
	PROPPAGEID(CvgActiveXPropPage::guid)
END_PROPPAGEIDS(CvgActiveXCtrl)



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CvgActiveXCtrl, "VGACTIVEX.vgActiveXCtrl.1",
	0xa2430265, 0x12c6, 0x42d2, 0xad, 0xa4, 0xd2, 0x35, 0x62, 0x1b, 0x1d, 0x7f)



// Type library ID and version

IMPLEMENT_OLETYPELIB(CvgActiveXCtrl, _tlid, _wVerMajor, _wVerMinor)



// Interface IDs

const IID BASED_CODE IID_DvgActiveX =
		{ 0xE6827ECF, 0x73D2, 0x4FE0, { 0xBF, 0xEA, 0x89, 0xAD, 0xF5, 0x66, 0xE, 0xD0 } };
const IID BASED_CODE IID_DvgActiveXEvents =
		{ 0x8CA75B3F, 0x4416, 0x4D82, { 0x8C, 0x7F, 0x42, 0xF6, 0x90, 0x50, 0xBA, 0x2A } };



// Control type information

static const DWORD BASED_CODE _dwvgActiveXOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CvgActiveXCtrl, IDS_VGACTIVEX, _dwvgActiveXOleMisc)



// CvgActiveXCtrl::CvgActiveXCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CvgActiveXCtrl

BOOL CvgActiveXCtrl::CvgActiveXCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_VGACTIVEX,
			IDB_VGACTIVEX,
			afxRegApartmentThreading,
			_dwvgActiveXOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CvgActiveXCtrl::CvgActiveXCtrl - Constructor

CvgActiveXCtrl::CvgActiveXCtrl()
{
	InitializeIIDs(&IID_DvgActiveX, &IID_DvgActiveXEvents);
	// TODO: Initialize your control's instance data here.
	b_threadcontrol = false;	
	AniPause = true;
	AniStop = true;
	Rainon = true;
	Snowon = true;
	firenum = 0;

	Settin1 = false;
	Settin2 = false;
	music = true;

	gis = false;	

	fog = false;

	m_lReadyState = READYSTATE_LOADING;

	//



}



// CvgActiveXCtrl::~CvgActiveXCtrl - Destructor

CvgActiveXCtrl::~CvgActiveXCtrl()
{
	// TODO: Cleanup your control's instance data here.
	b_threadcontrol = true;
}



// CvgActiveXCtrl::OnDraw - Drawing function

void CvgActiveXCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: Replace the following code with your own drawing code.
// 	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
// 	pdc->Ellipse(rcBounds);
	vgApp.run();
}



// CvgActiveXCtrl::DoPropExchange - Persistence support

void CvgActiveXCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.
}



// CvgActiveXCtrl::OnResetState - Reset control to default state

void CvgActiveXCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}



// CvgActiveXCtrl::AboutBox - Display an "About" box to the user

void CvgActiveXCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_VGACTIVEX);
	dlgAbout.DoModal();
}



// CvgActiveXCtrl message handlers

int CvgActiveXCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	SetTimer(1, 20, NULL);
	return 0;
}

void CvgActiveXCtrl::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(!vgApp.isNeedUpdate)
		Invalidate();
	vgApp.OnTimer(nIDEvent, this);
	COleControl::OnTimer(nIDEvent);
}

void CvgActiveXCtrl::OnSize(UINT nType, int cx, int cy)
{
	COleControl::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	gldAspect=(GLfloat)cx/(GLfloat)cy;
	if(vgApp.scenetree!=NULL)
	vgApp.size(cx,cy);
}

void CvgActiveXCtrl::OnShowWindow(BOOL bShow, UINT nStatus)
{
	COleControl::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码
	CDC *pDC = new CClientDC(this);

	vgApp.initialize(m_hWnd,pDC);
}

void CvgActiveXCtrl::OnDestroy()
{
	COleControl::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	vgApp.exit();
}

BOOL CvgActiveXCtrl::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return vgApp.eraseBkgnd();
}

void CvgActiveXCtrl::OnKillFocus(CWnd* pNewWnd)
{
	COleControl::OnKillFocus(pNewWnd);

	// TODO: 在此处添加消息处理程序代码
	vgApp.isNeedUpdate=false;
}

void CvgActiveXCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	vgApp.LButtonDown(nFlags , point, this);

	COleControl::OnLButtonDown(nFlags, point);
}

void CvgActiveXCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	vgApp.OnMouseMove(point,this);
	COleControl::OnMouseMove(nFlags, point);
}

void CvgActiveXCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	vgApp.LButtonDblClk(nFlags, point, gldAspect,this);
	COleControl::OnLButtonDblClk(nFlags, point);
}

void CvgActiveXCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	vgApp.LButtonUp(nFlags, point);
	ReleaseCapture();

	COleControl::OnLButtonUp(nFlags, point);
}

void CvgActiveXCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	vgApp.keyDown(nChar);

	COleControl::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CvgActiveXCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	vgApp.MouseWheel(zDelta, pt);
	return COleControl::OnMouseWheel(nFlags, zDelta, pt);
}

void CvgActiveXCtrl::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	vgApp.keyUp(nChar);
	COleControl::OnKeyUp(nChar, nRepCnt, nFlags);
}
BOOL CvgActiveXCtrl::PreCreateWindow(CREATESTRUCT& cs)
{
	return COleControl::PreCreateWindow(cs);;
}

BOOL CvgActiveXCtrl::PreTranslateMessage(MSG* pMsg)
{
	return COleControl::PreTranslateMessage(pMsg);
}

void CvgActiveXCtrl::Update(void)
{
	vgApp.isNeedUpdate=false;
}

void CvgActiveXCtrl::ImportVgFile(LPCTSTR vgfilename)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	vgCore::PARA_FileName *pPara=new vgCore::PARA_FileName;
	pPara->pa_filename=vgfilename;
	vgApp.appProc(VG_COMMAND_FILE,VG_COMMAND_FILE_OPEN_BYNAME, this , pPara);
	Update();

}

void CvgActiveXCtrl::ImportVgFileDlg(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	vgApp.appProc(VG_COMMAND_FILE,VG_COMMAND_FILE_OPEN, this );
	Update();
}

void CvgActiveXCtrl::SetGisPos(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	vgApp.appProc(VG_COMMAND_GIS,VG_COMMAND_GIS_ZUOBIAO, this );
}

void CvgActiveXCtrl::SetGisDis(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	vgApp.appProc(VG_COMMAND_GIS,VG_COMMAND_GIS_JULI, this );
}

void CvgActiveXCtrl::SetGisArea(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	vgApp.appProc(VG_COMMAND_GIS,VG_COMMAND_GIS_MIANJI, this );
}

void CvgActiveXCtrl::SetGisVolume(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	vgApp.appProc(VG_COMMAND_GIS,VG_COMMAND_GIS_TIJI, this );
}

void CvgActiveXCtrl::SetGisFlood(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	vgApp.appProc(VG_COMMAND_GIS,VG_COMMAND_GIS_SHUIYAN, this );
}

void CvgActiveXCtrl::SetGisWVolume(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	vgApp.appProc(VG_COMMAND_GIS,VG_COMMAND_GIS_SHUITI, this );
}

void CvgActiveXCtrl::SetGisMVolume(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	vgApp.appProc(VG_COMMAND_GIS,VG_COMMAND_GIS_SHANTI, this );
}

void CvgActiveXCtrl::SetGisP2P(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	vgApp.appProc(VG_COMMAND_GIS,VG_COMMAND_GIS_TONGTOU, this );
}

void CvgActiveXCtrl::SetGisCut(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	vgApp.appProc(VG_COMMAND_GIS,VG_COMMAND_GIS_HENGJIEMIAN, this );
}

void CvgActiveXCtrl::SetSeSnow(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	vgApp.appProc(VG_COMMAND_SE, VG_COMMAND_SE_SNOW, this);
}

void CvgActiveXCtrl::OffSeSnow(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	vgApp.appProc(VG_COMMAND_SE, VG_COMMAND_SE_SNOW_DEL, this);
}

void CvgActiveXCtrl::SetSeRain(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	vgApp.appProc(VG_COMMAND_SE, VG_COMMAND_SE_RAIN, this);

	vgApp.appProc(VG_COMMAND_SE, VG_COMMAND_SE_FOG, this);

	vgApp.appProc(VG_COMMAND_SE, VG_COMMAND_SE_SNOW_DEL, this);
}

void CvgActiveXCtrl::OffSeRain(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	vgApp.appProc(VG_COMMAND_SE, VG_COMMAND_SE_RAIN_DEL, this);
	vgApp.appProc(VG_COMMAND_SE, VG_COMMAND_SE_FOG_DEL, this);
}

void CvgActiveXCtrl::SetSeFog(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	vgApp.appProc(VG_COMMAND_SE, VG_COMMAND_SE_FOG, this);
}

void CvgActiveXCtrl::OffSeFog(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	vgApp.appProc(VG_COMMAND_SE, VG_COMMAND_SE_FOG_DEL, this);
}

void CvgActiveXCtrl::SetGisHawkEyeOn(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	vgApp.appProc(VG_COMMAND_GIS, VG_COMMAND_GIS_HAWKEYEON, this);
}

void CvgActiveXCtrl::SetGisHawkEyeOff(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	vgApp.appProc(VG_COMMAND_GIS, VG_COMMAND_GIS_HAWKEYEOFF, this);
}

void CvgActiveXCtrl::SetGisShadowOn(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	vgApp.appProc(VG_COMMAND_GIS,VG_COMMAND_GIS_SHADOW_ON, this);
}

void CvgActiveXCtrl::SetGisShadowOff(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	vgApp.appProc(VG_COMMAND_GIS,VG_COMMAND_GIS_SHADOW_OFF, this);
}

void CvgActiveXCtrl::SwitchCam(LONG ID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	vgCore::PARA_ID *pPara=new vgCore::PARA_ID;
	pPara->pa_ID=ID;
	vgApp.appProc(VG_COMMAND_CAMERA,VG_COMMAND_CAMERA_SWITCH, this, pPara);
}

void CvgActiveXCtrl::StartPlayAni(LONG ID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	vgCore::PARA_ID *pPara=new vgCore::PARA_ID;
	pPara->pa_ID=ID;
	vgApp.appProc(VG_COMMAND_CAMERA,VG_COMMAND_CAMERA_PLAY_ON, this, pPara);
	Update();
}

void CvgActiveXCtrl::SetGisContour(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	vgApp.appProc(VG_COMMAND_GIS,VG_COMMAND_GIS_DENGGAOXIAN, this);
}


void CvgActiveXCtrl::DBInfoShow(LPCTSTR buildingname)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	vgCore::PARA_FileName *pPara=new vgCore::PARA_FileName;
	pPara->pa_filename=buildingname;
	vgApp.appProc(VG_COMMAND_DB, VG_COMMAND_DB_SHOWPRO, this,pPara);
	Update();
}

void CvgActiveXCtrl::OnMusicOn(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	char strFilter[]=
		"MP3 Files (*.mp3)|*.mp3|" 
		"WAV Files (*.wav)|*.wav|"
		"MID Files (*.mid)|*.mid|"
		"WMA Files (*.wma)|*.wma||";
	CFileDialog  OpenDlg(TRUE,
		NULL,
		NULL,
		OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		strFilter);
	int nFlags=OpenDlg.DoModal();
	if(nFlags==IDOK)
	{
		//将文件路径名赋给成员变量m_strFileName备用
		m_strFileName=OpenDlg.GetPathName();

		CString filename = OpenDlg.GetFileName();
		LPCSTR filetype = OpenDlg.GetFileExt();

		mciOpen.lpstrElementName =(LPSTR)(LPCSTR) filename;//(char *)filename;
		MCIERROR   retu=   mciSendCommand(0,   MCI_OPEN,   
			MCI_OPEN_ELEMENT/*|MCI_OPEN_TYPE|MCI_OPEN_TYPE_ID|MCI_DGV_OPEN_PARENT|MCI_DGV_OPEN_WS*/,   
			(DWORD)(LPMCI_DGV_OPEN_PARMS)&mciOpen);   

		wDeviceID =mciOpen.wDeviceID;   

		mciSendCommand(wDeviceID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)&playParam);

		SetCurrentDirectoryA(vgApp.scenetree->pathbuffer);

		music = false;	
		Update();
	}

	else
		Update();
	return;
}

void CvgActiveXCtrl::OnMusicOff(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	mciSendCommand(wDeviceID, MCI_CLOSE, MCI_DGV_PLAY_REPEAT, (DWORD)&playParam);
	Update();

	music = true;
}

void CvgActiveXCtrl::SetGisWaterLevel(FLOAT waterlevel)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	vgApp.scenetree->Scene.vgDem->WaterHeight=waterlevel;

}

void CvgActiveXCtrl::ImportDemDom(LPCTSTR demfile, LPCTSTR domfile)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	vgCore::PARA_ImportDemDom *pPara=new vgCore::PARA_ImportDemDom;
 	pPara->pa_demfile=demfile;
 	pPara->pa_domfile=domfile;
 	vgApp.appProc(VG_COMMAND_TIN,VG_COMMAND_DEM_SET, this , pPara);
	Update();
}

void CvgActiveXCtrl::ImportDemDomDlg(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	vgApp.appProc(VG_COMMAND_TIN,VG_COMMAND_GEN_TIN, this );
}

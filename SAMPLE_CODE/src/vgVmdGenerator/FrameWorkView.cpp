// FrameWorkView.cpp : implementation of the CFrameWorkView class
//

#include <vgStableHeaders.h>
#include <resource.h>
#include "FrameWork.h"

#include "MainFrm.h"
#include "FrameWorkDoc.h"
#include "FrameWorkView.h"
//#include <mmsystem.h> 
#include <vgDlgOpenalSet.h>
#include <vgPictureInPicture.h>

#include <vgDlgPIPConfig.h>
#include <sys/timeb.h>

#include <vgEffect/vgGlassNode.h>
#include <vgDlgGlass.h>
#include <vgEffect/vgMirrorNode.h>
#include <vgDlgMirror.h>
#include <vgEffect/vgMetalNode.h>
#include <vgDlgMetal.h>
#include <vgDlgBrightfloor.h>
#include <vgDlgAviNode.h>
#include <vgUI/vgListTreeControlBar.h>

#include <vgViewerControl.h>

#include <vgRecvSock.h>
#include <vgDlgCamertrackRename.h>
#include <vgTerrainManager.h>

#include <vgSoundManager.h>


vgSock CFrameWorkView::m_socket;
CString CFrameWorkView::ipto;

/////////////////////////////////////////////////////////////////////////////
// CFrameWorkView
bool b_threadcontrol;
IMPLEMENT_DYNCREATE(CFrameWorkView, CView)

BEGIN_MESSAGE_MAP(CFrameWorkView, CView)
//{{AFX_MSG_MAP(CFrameWorkView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_SHOWWINDOW()
	ON_COMMAND(ID_IMPORT, OnImport)
	ON_WM_KILLFOCUS()
	ON_COMMAND(ID_CREATCAM, OnCreatcam)
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_OPEN, OnVGFileOpen)
	ON_COMMAND(id_shadowoff, Onshadowoff)
	ON_COMMAND(ID_ShadowON, OnShadowON)
	ON_WM_KEYUP()
	ON_COMMAND(ID_SWITCHCAM, OnSwitchcam)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_TRANSX, OnTransx)
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_TRANSY, OnTransy)
	ON_COMMAND(ID_TRANSZ, OnTransz)
	ON_COMMAND(ID_ROTX, OnRotx)
	ON_COMMAND(ID_ROTY, OnRoty)
	ON_COMMAND(ID_ROTZ, OnRotz)
	ON_COMMAND(ID_SCALEX, OnScalex)
	ON_COMMAND(ID_SCALEY, OnScaley)
	ON_COMMAND(ID_SCALEZ, OnScalez)
	ON_COMMAND(ID_SCALEXYZ, OnScalexyz)
	ON_COMMAND(ID_POSITIONTOOBJ, OnPositiontoobj)
	ON_COMMAND(ID_UNDO, OnUndo)
	ON_COMMAND(ID_SHOWCURCAMPRO, OnShowcurcampro)
	ON_UPDATE_COMMAND_UI(ID_UNDO, OnUpdateUndo)
	ON_COMMAND(ID_REDO, OnRedo)
	ON_UPDATE_COMMAND_UI(ID_REDO, OnUpdateRedo)
	ON_COMMAND(ID_SETTREE, OnSettree)
	ON_COMMAND(ID_BEGINPLANT, OnBeginplant)
	ON_COMMAND(ID_SELECT, OnSelect)
	ON_COMMAND(ID_PLANTINLINE, OnPlantinline)
	ON_COMMAND(ID_GENHAWKIMG, OnGenhawkimg)
	ON_COMMAND(ID_HAWKEYEON, OnHawkeyeon)
	ON_COMMAND(ID_HAWKEYEOFF, OnHawkeyeoff)
	ON_COMMAND(ID_GETTWOPOINT, OnGettwopoint)
	ON_COMMAND(ID_SHUTDOWNPATH, OnShutdownpath)
	ON_COMMAND(ID_PATHFLY, OnPathfly)
	ON_UPDATE_COMMAND_UI(ID_GETTWOPOINT, OnUpdateGettwopoint)
	ON_UPDATE_COMMAND_UI(ID_PATHFLY, OnUpdatePathfly)
	ON_UPDATE_COMMAND_UI(ID_SHUTDOWNPATH, OnUpdateShutdownpath)
	ON_COMMAND(ID_ADDANIMATION, OnAddanimation)
	ON_COMMAND(ID_ANI_Start, OnANIStart)
	ON_COMMAND(ID_ANI_END, OnAniEnd)
	ON_COMMAND(ID_ANI_PLAY, OnAniPlay)
	ON_COMMAND(ID_ANI_STOP, OnAniStop)
	ON_COMMAND(ID_ANI_PAUSE, OnAniPause)
	ON_COMMAND(ID_ANI_RESUME, OnAniResume)
	ON_UPDATE_COMMAND_UI(ID_ANI_PAUSE, OnUpdateAniPause)
	ON_UPDATE_COMMAND_UI(ID_ANI_RESUME, OnUpdateAniResume)
	ON_COMMAND(ID_SE_FOUNTAIN, OnSeFountain)
	ON_COMMAND(id_fountianset, Onfountianset)
	ON_COMMAND(ID_SETDEM, OnSetdem)
	ON_COMMAND(ID_GENTERRAIN, OnGenterrain)
	ON_COMMAND(ID_DDDDDDD, OnDdddddd)
	ON_COMMAND(IDM_Zuobiao, OnZuobiao)
	ON_COMMAND(IDM_Juli, OnJuli)
	ON_COMMAND(IDM_Mianji, OnMianji)
	ON_COMMAND(IDM_Tiji, OnTiji)
	ON_COMMAND(ID_Shuiyan, OnShuiyan)
	ON_COMMAND(IDM_SHUiTiTIJI, OnSHUiTiTIJI)
	ON_COMMAND(IDM_Shantitiji, OnShantitiji)
	ON_COMMAND(IDM_Tongtoupanding, OnTongtoupanding)
	ON_COMMAND(IDM_Hjm, OnHjm)
	ON_COMMAND(IDM_Dgx, OnDgx)
	ON_COMMAND(ID_RAIN, OnRain)
	ON_COMMAND(ID_SNOW, OnSnow)
	ON_COMMAND(ID_RAIN_DEL, OnRainDel)
	ON_COMMAND(ID_SNOW_DEL, OnSnowDel)
	ON_COMMAND(ID_FIRE_ADD, OnFireAdd)
	ON_COMMAND(ID_FOG_DEL, OnFogDel)
	ON_UPDATE_COMMAND_UI(ID_RAIN, OnUpdateRain)
	ON_UPDATE_COMMAND_UI(ID_RAIN_DEL, OnUpdateRainDel)
	ON_UPDATE_COMMAND_UI(ID_SNOW, OnUpdateSnow)
	ON_UPDATE_COMMAND_UI(ID_SNOW_DEL, OnUpdateSnowDel)
	ON_UPDATE_COMMAND_UI(ID_GENTERRAIN, OnUpdateGenterrain)
	ON_COMMAND(ID_MUSICON, OnMusicon)
	ON_UPDATE_COMMAND_UI(ID_MUSICON, OnUpdateMusicon)
	ON_COMMAND(ID_MUSICOFF, OnMusicoff)
	ON_UPDATE_COMMAND_UI(ID_MUSICOFF, OnUpdateMusicoff)
	ON_COMMAND(ID_DEM, OnDem)
	ON_COMMAND(ID_DOM, OnDom)
	ON_COMMAND(IDC_LOADANI, OnLoadani)
	ON_COMMAND(ID_UNLOADANI, OnUnloadani)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_UPDATE_COMMAND_UI(IDM_Hjm, OnUpdateHjm)
	ON_UPDATE_COMMAND_UI(IDM_Dgx, OnUpdateDgx)
	ON_UPDATE_COMMAND_UI(IDM_Tongtoupanding, OnUpdateTongtoupanding)
	ON_COMMAND(ID_SE_FOG, OnSeFog)
	ON_COMMAND(ID_SE_FOG_DEL, OnSeFogDel)
	ON_COMMAND(ID_SE_SMOKE, OnSeSmoke)
	ON_COMMAND(ID_SMOKESET, OnSmokeset)
	ON_COMMAND(ID_FIRESET, OnFireset)
	ON_UPDATE_COMMAND_UI(ID_FIRE_DEL, OnUpdateFireDel)
	ON_UPDATE_COMMAND_UI(ID_SE_FOG_DEL, OnUpdateSeFogDel)
	ON_UPDATE_COMMAND_UI(ID_SE_FOG, OnUpdateSeFog)
	ON_COMMAND(ID_DB_SHOW, OnDbShow)
	ON_COMMAND(ID_SETFLAG, OnSetflag)
	ON_COMMAND(ID_ADDFLAG, OnAddflag)
	ON_COMMAND(ID_DB_LINK, OnDbLink)
	ON_COMMAND(ID_DB_DATABASE, OnDbDatabase)
	ON_COMMAND(ID_DB_TABLE, OnDbTable)
	ON_COMMAND(ID_DB_RECORD, OnDbRecord)
	ON_COMMAND(ID_DLG_WATER, OnDlgWater)
	ON_COMMAND(id_selectcancel, Onselectcancel)
	ON_UPDATE_COMMAND_UI(ID_Shuiyan, OnUpdateShuiyan)
	ON_UPDATE_COMMAND_UI(IDM_SHUiTiTIJI, OnUpdateSHUiTiTIJI)
	ON_UPDATE_COMMAND_UI(IDM_Shantitiji, OnUpdateShantitiji)
	ON_COMMAND(ID_IMPORTBIGSCENE, OnImportbigscene)
	ON_UPDATE_COMMAND_UI(ID_ANI_STOP, OnUpdateAniStop)
	ON_COMMAND(ID_actuality, Onactuality)
	ON_COMMAND(ID_plan, Onplan)
	ON_COMMAND(id_loadbigterrain, Onloadbigterrain)
	ON_COMMAND(ID_SETHAWK, OnSethawk)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)

	ON_MESSAGE(WM_FILEOPEN,OnFileOpen)

	ON_COMMAND(ID_SOUNDSET, CFrameWorkView::OnSoundset)
	ON_COMMAND(ID_OPENALON, CFrameWorkView::OnOpenalon)
	ON_COMMAND(ID_OPENALOFF, CFrameWorkView::OnOpenaloff)
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_COMMAND(ID_WATER_EDIT, CFrameWorkView::OnWaterEdit)
	ON_COMMAND(ID_WATER_CONVERT, CFrameWorkView::OnWaterConvert)
	ON_COMMAND(ID_GLASS_CONVERT, CFrameWorkView::OnGlassConvert)
	ON_COMMAND(ID_MIRROR_CONVERT, CFrameWorkView::OnMirrorConvert)
	ON_COMMAND(ID_METAL_CONVERT, &CFrameWorkView::OnMetalConvert)
	ON_COMMAND(ID_CAMERA_CAPTURE, &CFrameWorkView::OnCameraCapture)
	ON_COMMAND(ID_PIP_TURNON, &CFrameWorkView::OnPipTurnon)
	ON_COMMAND(ID_PIP_TURNOFF, &CFrameWorkView::OnPipTurnoff)
	ON_COMMAND(ID_PIP_SAVE, &CFrameWorkView::OnPipSave)
	ON_COMMAND(ID_PIP_CONFIG, &CFrameWorkView::OnPipConfig)
	ON_COMMAND(ID_PIP_MOVE_X_SUB, &CFrameWorkView::OnPipMoveXSub)
	ON_COMMAND(ID_PIP_MOVE_X_ADD, &CFrameWorkView::OnPipMoveXAdd)
	ON_COMMAND(ID_PIP_MOVE_Y_SUB, &CFrameWorkView::OnPipMoveYSub)
	ON_COMMAND(ID_PIP_MOVE_Y_ADD, &CFrameWorkView::OnPipMoveYAdd)
	ON_COMMAND(ID_PIP_RESIZE_X_SUB, &CFrameWorkView::OnPipResizeXSub)
	ON_COMMAND(ID_PIP_RESIZE_X_ADD, &CFrameWorkView::OnPipResizeXAdd)
	ON_COMMAND(ID_PIP_RESIZE_Y_SUB, &CFrameWorkView::OnPipResizeYSub)
	ON_COMMAND(ID_PIP_RESIZE_Y_ADD, &CFrameWorkView::OnPipResizeYAdd)
	ON_COMMAND(ID_PIP_SAVE_CUBE_MAP, &CFrameWorkView::OnPipSaveCubeMap)
	ON_COMMAND(ID_GLASS_EDIT, &CFrameWorkView::OnGlassEdit)
	ON_COMMAND(ID_MIRROR_EDIT, &CFrameWorkView::OnMirrorEdit)
	ON_COMMAND(ID_METAL_EDIT, &CFrameWorkView::OnMetalEdit)
	ON_COMMAND(ID_CONTROL_PC, &CFrameWorkView::OnControlPc)
	ON_COMMAND(ID_CLOSE_SED, &CFrameWorkView::OnCloseSed)
	ON_COMMAND(ID_CONTROLED_PC, &CFrameWorkView::OnControledPc)
	ON_COMMAND(ID_P1, &CFrameWorkView::OnP1)
	ON_COMMAND(ID_M1, &CFrameWorkView::OnM1)
	ON_COMMAND(ID_CLOSE_REV, &CFrameWorkView::OnCloseRev)
	ON_COMMAND(ID_SOFTEDGE, &CFrameWorkView::OnSoftedge)
	ON_COMMAND(ID_HARDEDGE, &CFrameWorkView::OnHardedge)
	ON_COMMAND(ID_VS, &CFrameWorkView::OnVs)
	ON_COMMAND(ID_SKYBOX_CONVERT, &CFrameWorkView::OnSkyboxConvert)
	ON_COMMAND(ID_CONVERT_BRIGTHFLOOR, &CFrameWorkView::OnConvertBrigthfloor)
	ON_COMMAND(ID_BRIGHTFLOOR_EDIT, &CFrameWorkView::OnBrightfloorEdit)
	ON_COMMAND(ID_AVI_NODE_CONVERT, &CFrameWorkView::OnAviNodeConvert)
	ON_COMMAND(ID_AVINODE_EDIT, &CFrameWorkView::OnAvinodeEdit)
	ON_COMMAND(ID_CAMERATRACK_RENAME, &CFrameWorkView::OnCameratrackRename)
	ON_COMMAND(ID_PUBLISH, &CFrameWorkView::OnPublish)
	ON_COMMAND(ID_CHANGE_RENDERTYPE, &CFrameWorkView::OnChangeRendertype)
	ON_COMMAND(ID_RENDERMODE_SHADE, &CFrameWorkView::OnRendermodeShade)
	ON_COMMAND(ID_RENDERMODE_WIREFRAME, &CFrameWorkView::OnRendermodeWireframe)
	ON_COMMAND(ID_TERRAIN_LEVELLING_BEGIN, &CFrameWorkView::OnTerrainLevellingBegin)
	ON_COMMAND(ID_TERRAIN_SAVE, &CFrameWorkView::OnTerrainSave)
	ON_COMMAND(ID_TERRAIN_DROP_DATA, &CFrameWorkView::OnTerrainDropData)
	ON_COMMAND(ID_TERRAIN_RENDER_ON, &CFrameWorkView::OnTerrainRenderOn)
	ON_COMMAND(ID_TERRAIN_RENDER_OFF, &CFrameWorkView::OnTerrainRenderOff)
	ON_COMMAND(ID_TERRAIN_CONVER_DEMS_TO_VGTR, &CFrameWorkView::OnTerrainConverDemsToVgtr)
	ON_COMMAND(ID_TERRAIN_CONVERT_VGTR_TO_BMP, &CFrameWorkView::OnTerrainConvertVgtrToBmp)
	ON_COMMAND(ID_MATCH_ROAD, &CFrameWorkView::OnMatchRoad)
	ON_COMMAND(ID_OptPlant, &CFrameWorkView::OnOptplant)
	ON_UPDATE_COMMAND_UI(ID_OptPlant, &CFrameWorkView::OnUpdateOptplant)
	ON_COMMAND(ID_TRANSALL, &CFrameWorkView::OnTransall)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDBLCLK()
	ON_COMMAND(ID_CAMERA_MODE_FLY, &CFrameWorkView::OnCameraModeFly)
	ON_COMMAND(ID_CAMERA_MODE_KEYBOARD, &CFrameWorkView::OnCameraModeKeyboard)
	ON_COMMAND(ID_MUSIC_CONFIG, &CFrameWorkView::OnMusicConfig)
	ON_COMMAND(ID_DELETE_ALL_CAMERATRACK, &CFrameWorkView::OnDeleteAllCameratrack)
	END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFrameWorkView construction/destruction
CFrameWorkView::CFrameWorkView()
{
	// TODO: add construction code here
//	i=0;

		b_threadcontrol = false;

		//UI 控制

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

//		b_hasani = false;

		//三通道初始化
		if (!AfxSocketInit())
		{
			AfxMessageBox("socket init error!");
			return ;
		}
		//获取主机IP
		static char host_name[256]; 
		gethostname(host_name,sizeof(host_name)); 
		struct hostent *hp; 
		static struct in_addr sa; 
		char *buf; 
		hp = gethostbyname(host_name); 

		if (hp != NULL) 
		{ 
			//循环获取本地主机名 
			for (int i = 0; hp->h_addr_list[i]; i++) 
			{ 
				memcpy (&sa, hp->h_addr_list[i],hp->h_length); 

				buf= inet_ntoa(sa); 
			} 
		} 
		ipto=buf;
		String temp=ipto;
		int num=temp.find_last_of(".");
		temp.replace(num+1,3,"255");
		ipto=temp.c_str();

		m_recvsocket = NULL;
	
}
static int fognum = 0;
CFrameWorkView::~CFrameWorkView()
{
		b_threadcontrol = true;
}

BOOL CFrameWorkView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFrameWorkView drawing
void CFrameWorkView::OnDraw(CDC* pDC)
{
	CFrameWorkDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	static bool  g_bFirstRendering = true;
	static timeb g_lastTime;
	static float g_fTimeSinceLastReport = 0.0;
	static int   g_nFrameCount = 0;


#if VG_EXPLORER_AUTO_LOAD
	static bool contrl =true ;

	if ( contrl == true )
	{
		contrl = false ;
		vgApp.vgInitialProData(this);
	}
#endif

	vgApp.run();

	// 2008年5月9日20:02:17 add by lss
	//_mViewShowTestInfo();

	pFrm=(CMainFrame*)AfxGetApp()->m_pMainWnd;

	timeb currentTime;
	float fElapsed = 0.0f;

	if( g_bFirstRendering == true )
	{
		ftime( &g_lastTime );
		currentTime = g_lastTime;
		g_bFirstRendering = false;
	}
	else
	{
		ftime( &currentTime );

		// This is accurate to one second
		fElapsed  = (float)(currentTime.time - g_lastTime.time);
		// This gets it down to one ms
		fElapsed += (float)((currentTime.millitm - g_lastTime.millitm) / 1000.0f);
	}

	static char fpsString[50];

	++g_nFrameCount;

	char	IsQuadtreeUsed;
	if(vgApp.scenetree->m_currentmode == vgCore::QuadtreeSceneManager::drawmode::QUADTREE)
		IsQuadtreeUsed	=	'Y';
	else
		IsQuadtreeUsed	=	'N';

	string	IsOcclusionOn;
	if(vgApp.scenetree->b_occ)
		IsOcclusionOn	=	"On";
	else
		IsOcclusionOn	=	"Off";
	// Has one second passed?
	if( fElapsed - g_fTimeSinceLastReport > 1.0f )
	{
		sprintf( fpsString, "帧数 = %d FPS___遮挡剔除: %s___四叉树: %c", g_nFrameCount ,IsOcclusionOn.c_str(),IsQuadtreeUsed );

		g_fTimeSinceLastReport = fElapsed;
		g_nFrameCount = 0;
	}

	pFrm->m_wndStatusBar.SetPaneText(1,fpsString,TRUE);	

	pFrm->m_wndStatusBar.UpdateWindow();
}

/////////////////////////////////////////////////////////////////////////////
// CFrameWorkView printing

BOOL CFrameWorkView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFrameWorkView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFrameWorkView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CFrameWorkView diagnostics

#ifdef _DEBUG
void CFrameWorkView::AssertValid() const
{
	CView::AssertValid();
}

void CFrameWorkView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFrameWorkDoc* CFrameWorkView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFrameWorkDoc)));
	return (CFrameWorkDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFrameWorkView message handlers

int CFrameWorkView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CDC *pDC = new CClientDC(this);
	//pdc=pDC;
//	HWND   hWnd;   
	//hWnd=GetSafeHwnd();

//	vgApp.initialize(m_hWnd,pDC);


	SetTimer(1, 10, NULL);



	return 0;
}

void CFrameWorkView::OnDestroy() 
{
	CView::OnDestroy();
	vgApp.exit();
	// TODO: Add your message handler code here
	
}

BOOL CFrameWorkView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	//return CView::OnEraseBkgnd(pDC);
	return vgApp.eraseBkgnd();
}

void CFrameWorkView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	vgApp.LButtonDown(nFlags , point, this);
//	//?????
	CView::OnLButtonDown(nFlags, point);
}

void CFrameWorkView::OnSize(UINT nType, int cx, int cy) 
{

	CView::OnSize(nType, cx, cy);
	gldAspect=(GLfloat)cx/(GLfloat)cy;
	vgApp.size(cx,cy);
}

void CFrameWorkView::OnTimer(UINT nIDEvent) 
{
   if(!vgApp.isNeedUpdate)
        Invalidate();
   vgApp.OnTimer(nIDEvent, this);

	// TODO: Add your message handler code here and/or call default
	CView::OnTimer(nIDEvent);
}

void CFrameWorkView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
    vgApp.keyDown(nChar);
	if (nChar == 70)
	{
		pFrm->OnScreenFull();
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CFrameWorkView::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CView::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	CDC *pDC = new CClientDC(this);

	vgApp.initialize(m_hWnd,pDC);

	//pFrm->m_curprobar.m_PropCtrl.Invalidate();


}

void CFrameWorkView::OnImport() 
{
	// TODO: Add your command handler code here
	//vgApp.isNeedUpdate=false;
	vgApp.appProc(VG_COMMAND_MODEL, VG_COMMAND_MODEL_ADD,this);	
	Invalidate();

	//UpdateWindow();
	vgApp.isNeedUpdate=false;
	 pFrm->m_curprobar.m_PropCtrl.Invalidate();
	 pFrm->m_objTree.m_wndTree.Invalidate();

}

void CFrameWorkView::OnKillFocus(CWnd* pNewWnd) 
{
	CView::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
	vgApp.isNeedUpdate=false;
}

 void CFrameWorkView::OnGenterrain()  
 {
//DEL 	// TODO: Add your command handler code here
 	vgApp.appProc(VG_COMMAND_TIN , VG_COMMAND_GEN_TIN,this);

	gis =true;
	
 }

//////////////////////////////another thread/////////////////////////////////
LRESULT CFrameWorkView::OnFileOpen(WPARAM wParam,LPARAM lParam)   //自己做个消息
{
	////////////////////////////////////多线程/////////////////////////
//  	h_Thread = CreateThread(NULL , 0 , exchange, (LPVOID)&vgApp.m_terrain , 0, NULL);
//  	CloseHandle(h_Thread);
// 

 	return NULL;
}

DWORD WINAPI CFrameWorkView::exchange(LPVOID Data)
{
// 	Sleep(1000);
// 	vgCore::CTerrain *doc;
// 	doc = (vgCore::CTerrain *)Data;
// 
// 	while (TRUE)
// 	{
// 		if (b_threadcontrol == true)
// 		{
// 			break;
// 		}
// //		WaitForSingleObject(hMutex,INFINITE);
// 		if (doc->b_fileopen == true && doc->b_exchange == true)
// 		{
// 			doc->b_exchange = false;
// 			doc->ExchangeData(doc->RootTree);
// 		}
// 
// //		ReleaseMutex(hMutex);
// 	}
	return 0;		

}



void CFrameWorkView::OnCreatcam() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_CAMERA,VG_COMMAND_CAMERA_ADD, this);

}

BOOL CFrameWorkView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	vgApp.MouseWheel(zDelta, pt);

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CFrameWorkView::OnFileSave() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_FILE,VG_COMMAND_FILE_SAVE, this);
	Update();

}
void CFrameWorkView::Update()
{
	pFrm->m_curprobar.m_PropCtrl.Invalidate();
	pFrm->m_objTree.m_wndTree.Invalidate();
	vgApp.isNeedUpdate=false;
}
void CFrameWorkView::OnVGFileOpen() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_FILE,VG_COMMAND_FILE_OPEN, this);
	Update();

	gis =true;
}


void CFrameWorkView::Onshadowoff() 
{
	vgApp.appProc(VG_COMMAND_GIS,VG_COMMAND_GIS_SHADOW_OFF, this);
		Update();
}

void CFrameWorkView::OnShadowON() 
{
	vgApp.appProc(VG_COMMAND_GIS,VG_COMMAND_GIS_SHADOW_ON, this);	
		Update();
}

void CFrameWorkView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	vgApp.keyUp(nChar);
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

BOOL CFrameWorkView::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
		if(   pMsg->message   ==   WM_LBUTTONDBLCLK )   
	{   
	pFrm->m_curprobar.m_PropCtrl.Invalidate();
	}  
	return CView::PreTranslateMessage(pMsg);
}

void CFrameWorkView::OnSwitchcam() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_CAMERA,VG_COMMAND_CAMERA_SWITCH, this);
		Update();
}

void CFrameWorkView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	vgApp.LButtonDblClk(nFlags, point, gldAspect,this);
	CView::OnLButtonDblClk(nFlags, point);
}

void CFrameWorkView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	vgApp.OnMouseMove(point,this);

	CView::OnMouseMove(nFlags, point);
}

void CFrameWorkView::OnTransx() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_EDIT, VG_COMMAND_EDITTRANSX, this);

	Update();
}

void CFrameWorkView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	vgApp.LButtonUp(nFlags, point);
	pFrm->m_curprobar.m_PropCtrl.Invalidate();
	
	ReleaseCapture();

	CView::OnLButtonUp(nFlags, point);
}

void CFrameWorkView::OnTransy() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_EDIT, VG_COMMAND_EDITTRANSY, this);
		Update();
	
}

void CFrameWorkView::OnTransz() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_EDIT, VG_COMMAND_EDITTRANSZ, this);
		Update();
}

void CFrameWorkView::OnRotx() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_EDIT, VG_COMMAND_EDITROTX, this);
		Update();
}

void CFrameWorkView::OnRoty() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_EDIT, VG_COMMAND_EDITROTY, this);
		Update();
}

void CFrameWorkView::OnRotz() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_EDIT, VG_COMMAND_EDITROTZ, this);
		Update();
}

void CFrameWorkView::OnScalex() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_EDIT, VG_COMMAND_EDITSCLX, this);
		Update();
}

void CFrameWorkView::OnScaley() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_EDIT, VG_COMMAND_EDITSCLY, this);
		Update();
}

void CFrameWorkView::OnScalez() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_EDIT, VG_COMMAND_EDITSCLZ, this);
		Update();
}

void CFrameWorkView::OnScalexyz() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_EDIT, VG_COMMAND_EDITSCLXYZ, this);
		Update();
}

void CFrameWorkView::OnPositiontoobj() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_CAMERA, VG_COMMAND_CAMERA_POSTOOBJ, this);
		Update();
}

void CFrameWorkView::OnUndo() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_EDIT,VG_COMMAND_UNDO, this);
		Update();
}

void CFrameWorkView::OnShowcurcampro() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_CAMERA, VG_COMMAND_CAMERA_SHOW, this);
		Update();
}

void CFrameWorkView::OnUpdateUndo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(vgApp.scenetree->CanUndo);
		Update();

}

void CFrameWorkView::OnRedo() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_EDIT,VG_COMMAND_REDO, this);
		Update();
}

void CFrameWorkView::OnUpdateRedo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(vgApp.scenetree->CanRedo);
		Update();
}

void CFrameWorkView::OnSettree() 
{
	// TODO: Add your command handler code here

	vgApp.appProc(VG_COMMAND_TREE, VG_COMMAND_TREE_SETTING, this);
		Update();

}

void CFrameWorkView::OnBeginplant() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_TREE, VG_COMMAND_TREE_PLANT, this);
		Update();
}

void CFrameWorkView::OnSelect() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_EDIT , VG_COMMAND_SELECT, this);
		Update();
}

void CFrameWorkView::OnPlantinline() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_TREE, VG_COMMAND_TREE_PLANTINLINE, this);
		Update();
}

void CFrameWorkView::OnGenhawkimg() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_GIS, VG_COMMAND_GIS_HAWKGENMAP, this);
		Update();
}

void CFrameWorkView::OnHawkeyeon() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_GIS, VG_COMMAND_GIS_HAWKEYEON, this);
		Update();
}

void CFrameWorkView::OnHawkeyeoff() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_GIS, VG_COMMAND_GIS_HAWKEYEOFF, this);
		Update();
}

void CFrameWorkView::OnGettwopoint() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_GIS, VG_COMMAND_GIS_PATH_GETPOINTS, this);
		Update();
}

void CFrameWorkView::OnShutdownpath() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_GIS, VG_COMMAND_GIS_PATH_SHUT, this);
		Update();

}

void CFrameWorkView::OnPathfly() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_GIS, VG_COMMAND_GIS_PATH_SHOWPATH, this);
		Update();

}

void CFrameWorkView::OnUpdateGettwopoint(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(false);
}

void CFrameWorkView::OnUpdatePathfly(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(false);
}

void CFrameWorkView::OnUpdateShutdownpath(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(false);
}

void CFrameWorkView::OnAddanimation() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_CAMERA, VG_COMMAND_CAMERA_ADD_ANI, this);
		Update();
}

void CFrameWorkView::OnANIStart() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_CAMERA, VG_COMMAND_CAMERA_RECORD_ON, this);
		Update();
}

void CFrameWorkView::OnAniEnd() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_CAMERA, VG_COMMAND_CAMERA_RECORD_OFF, this);
		Update();
}

void CFrameWorkView::OnAniPlay() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_CAMERA, VG_COMMAND_CAMERA_PLAY_ON, this);
		AniStop = false;		
	Update();
}


void CFrameWorkView::OnAniStop() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_CAMERA, VG_COMMAND_CAMERA_PLAY_OFF, this);
		AniStop = true;
		Update();
}

void CFrameWorkView::OnAniPause() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_CAMERA, VG_COMMAND_CAMERA_PAUSE, this);
		
	Update();

	AniPause = false;

}

void CFrameWorkView::OnAniResume() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_CAMERA, VG_COMMAND_CAMERA_RESUME, this);
		Update();

	AniPause = true;
}

void CFrameWorkView::OnUpdateAniPause(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(AniPause && !AniStop);
}

void CFrameWorkView::OnUpdateAniResume(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!AniPause&& !AniStop);
}

void CFrameWorkView::OnSeFountain() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_SE, VG_COMMAND_SE_FOUNTAIN_ADD, this);
		Update();
}

void CFrameWorkView::Onfountianset() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_SE, VG_COMMAND_SE_FOUNTAIN_SET, this);
		Update();
}

void CFrameWorkView::OnSetdem() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_TIN , VG_COMMAND_DEM_SET, this);
		Update();

	Settin1 = true;
}

void CFrameWorkView::OnDdddddd() 
{
	// TODO: Add your command handler code here
	vgApp.scenetree->Readscene();
}

void CFrameWorkView::OnZuobiao() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_GIS, VG_COMMAND_GIS_ZUOBIAO, this);
		Update();
}

void CFrameWorkView::OnJuli() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_GIS, VG_COMMAND_GIS_JULI, this);	
		Update();
}

void CFrameWorkView::OnMianji() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_GIS, VG_COMMAND_GIS_MIANJI, this);
		Update();
}

void CFrameWorkView::OnTiji() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_GIS, VG_COMMAND_GIS_TIJI, this);
		Update();
}

void CFrameWorkView::OnShuiyan() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_GIS, VG_COMMAND_GIS_SHUIYAN, this);
		Update();
}

void CFrameWorkView::OnSHUiTiTIJI() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_GIS, VG_COMMAND_GIS_SHUITI, this);
		Update();
}

void CFrameWorkView::OnShantitiji() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_GIS, VG_COMMAND_GIS_SHANTI, this);
		Update();
}

void CFrameWorkView::OnTongtoupanding() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_GIS, VG_COMMAND_GIS_TONGTOU, this);
		Update();
}

void CFrameWorkView::OnHjm() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_GIS, VG_COMMAND_GIS_HENGJIEMIAN, this);
		Update();
}

void CFrameWorkView::OnDgx() 
{
	// TODO: Add your command handler code he
	vgApp.appProc(VG_COMMAND_GIS, VG_COMMAND_GIS_DENGGAOXIAN, this);
		Update();
}

void CFrameWorkView::OnRain() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_SE, VG_COMMAND_SE_RAIN, this);

	vgApp.appProc(VG_COMMAND_SE, VG_COMMAND_SE_FOG, this);
		Update();
	Rainon = false;

	fognum++;
}

void CFrameWorkView::OnSnow() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_SE, VG_COMMAND_SE_SNOW, this);

	vgApp.appProc(VG_COMMAND_SE, VG_COMMAND_SE_FOG, this);
		Update();
		Snowon = false;
	fognum++;	
}

void CFrameWorkView::OnFire() 
{
	// TODO: Add your command handler code here
	
}

void CFrameWorkView::OnRainDel() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_SE, VG_COMMAND_SE_RAIN_DEL, this);
		Update();

	fognum-=1;	
	if (fognum == 0)
	{
		vgApp.appProc(VG_COMMAND_SE, VG_COMMAND_SE_FOG_DEL, this);	

	}
	Rainon = true;
}

void CFrameWorkView::OnSnowDel() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_SE, VG_COMMAND_SE_SNOW_DEL, this);
		Update();
	fognum-=1;
	if (!fognum)
	{
		vgApp.appProc(VG_COMMAND_SE, VG_COMMAND_SE_FOG_DEL, this);	

	}
	Snowon = true;
}

void CFrameWorkView::OnFireAdd() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_SE, VG_COMMAND_SE_FIRE, this);
		Update();
}


void CFrameWorkView::OnFogDel() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_SE, VG_COMMAND_SE_FOG_DEL, this);
		Update();
/*		fognum--;*/
}

void CFrameWorkView::OnUpdateRain(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(Rainon);
}

void CFrameWorkView::OnUpdateRainDel(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!Rainon);
}

void CFrameWorkView::OnUpdateSnow(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(Snowon);
}

void CFrameWorkView::OnUpdateSnowDel(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!Snowon);
}

void CFrameWorkView::OnUpdateGenterrain(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(Settin1 && Settin2 && !vgApp.scenetree->Scene.vgDem->b_render);
}

void CFrameWorkView::OnMusicon() 
{
	vgCore::SoundManager::getSingleton().turnOnBackgroundMusic();

	return;



	//// TODO: Add your command handler code here
	//char strFilter[]=
	//	"MP3 Files (*.mp3)|*.mp3|" 
	//	"WAV Files (*.wav)|*.wav|"
	//	"MID Files (*.mid)|*.mid|"
	//	"WMA Files (*.wma)|*.wma||";
	//CFileDialog  OpenDlg(TRUE,
	//	NULL,
	//	NULL,
	//	OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
	//	strFilter);
	//int nFlags=OpenDlg.DoModal();
	//if(nFlags==IDOK)
	//{
	//	//将文件路径名赋给成员变量m_strFileName备用
	//	m_strFileName=OpenDlg.GetPathName();
	//	
	//	CString filename = OpenDlg.GetFileName();
	//	LPCSTR filetype = OpenDlg.GetFileExt();
	//	
	//	mciOpen.lpstrElementName =(LPSTR)(LPCSTR) filename;//(char *)filename;
	//	MCIERROR   retu=   mciSendCommand(0,   MCI_OPEN,   
	//		MCI_OPEN_ELEMENT/*|MCI_OPEN_TYPE|MCI_OPEN_TYPE_ID|MCI_DGV_OPEN_PARENT|MCI_DGV_OPEN_WS*/,   
	//		(DWORD)(LPMCI_DGV_OPEN_PARMS)&mciOpen);   
	//	
	//	wDeviceID =mciOpen.wDeviceID;   
	//	
	//	mciSendCommand(wDeviceID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)&playParam);

	//	SetCurrentDirectoryA(vgApp.scenetree->pathbuffer);
	//	
	//	music = false;	
	//		Update();
	//}

	//else
	//		Update();
	//	return;



}

void CFrameWorkView::OnUpdateMusicon(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(music);

}

void CFrameWorkView::OnMusicoff() 
{
	// TODO: Add your command handler code here

	//mciSendCommand(wDeviceID, MCI_CLOSE, MCI_DGV_PLAY_REPEAT, (DWORD)&playParam);
	//Update();

	//music = true;

	vgCore::SoundManager::getSingleton().turnOffBackgroundMusic();
	
}

void CFrameWorkView::OnUpdateMusicoff(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	bool enable_music = false;

	if ( vgCore::SoundManager::getSingleton().getCurrentBackgroundMusic() != NULL )
	{
		enable_music = true;
	}

	pCmdUI->Enable( enable_music );
}

void CFrameWorkView::OnDem() 
{
	// TODO: Add your command handler code here
		CString DefExt;
	
	DefExt.Format("%s","dem文件(*.dem)|*.dem|");
	
	CFileDialog dlgmodelFile(true,"dem",NULL,OFN_HIDEREADONLY|OFN_CREATEPROMPT|OFN_NONETWORKBUTTON,DefExt);
	
	dlgmodelFile.m_ofn.lpstrTitle="VG_DEM";
	
	if(dlgmodelFile.DoModal()==IDOK)
	{
		vgApp.scenetree->m_dempath1 = dlgmodelFile.GetPathName();

		SetCurrentDirectoryA(vgCore::QuadtreeSceneManager::getSingleton().pathbuffer);
	
		Settin1 = true;
			Update();
		return;

	}
	else
			Update();
		return;
}

void CFrameWorkView::OnDom() 
{
	// TODO: Add your command handler code here


	CString DefExt;
	
	DefExt.Format("%s","dds文件 (*.dds)|*.dds|bmp文件 (*.bmp)|*.bmp|");
	
	CFileDialog dlgmodelFile(true,"bmp|dds",NULL,OFN_HIDEREADONLY|OFN_CREATEPROMPT|OFN_NONETWORKBUTTON,DefExt);
	
	dlgmodelFile.m_ofn.lpstrTitle="VG_DOM";
	
	if(dlgmodelFile.DoModal()==IDOK)
	{
		vgApp.scenetree->m_dompath1 = dlgmodelFile.GetPathName();	
		
		SetCurrentDirectoryA(vgCore::QuadtreeSceneManager::getSingleton().pathbuffer);
		
		Settin2 = true;
			Update();
		return;
	}
	else
			Update();
		return;
}

void CFrameWorkView::OnLoadani() 
{
	// TODO: Add your command handler code here
	 	CString DefExt;
 	
 	DefExt.Format("%s","ms3d文件(*.ms3d)|*.ms3d|");
 	
 	///CFileDialog第一个参数若为true，为打开文件对话框,该段基于mfc
 	CFileDialog dlgmodelFile(true,"ms3d",NULL,OFN_HIDEREADONLY|OFN_CREATEPROMPT|OFN_NONETWORKBUTTON,DefExt);
 	
 	dlgmodelFile.m_ofn.lpstrTitle="VG_MS3D";
 	
 	if(dlgmodelFile.DoModal()==IDOK)
 	{
		CString FilePathName = dlgmodelFile.GetPathName();
		vgApp.scenetree->Addskelecton(FilePathName);
	}
	
	SetCurrentDirectoryA(vgApp.scenetree->pathbuffer);
	Update();

}

void CFrameWorkView::OnUnloadani() 
{
	// TODO: Add your command handler code here
//	vgApp.b_hasani = false;
		Update();
}

void CFrameWorkView::OnAppAbout() 
{
	// TODO: Add your command handler code here
	
	CAboutDlg aboutDlg;	
	SetTimer(2,500,NULL);


	aboutDlg.DoModal();
		Update();
}

void CFrameWorkView::OnUpdateHjm(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(vgApp.scenetree->Scene.vgDem->b_render);
}

void CFrameWorkView::OnUpdateDgx(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(vgApp.scenetree->Scene.vgDem->b_render);

}

void CFrameWorkView::OnUpdateTongtoupanding(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(vgApp.scenetree->Scene.vgDem->b_render);
}

void CFrameWorkView::OnSeFog() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_SE, VG_COMMAND_SE_FOG, this);

	fognum++;
	Update();
	fog = true;
}

void CFrameWorkView::OnSeFogDel() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_SE, VG_COMMAND_SE_FOG_DEL, this);	
	Update();
	fognum-=1;
	fog = false;
}

void CFrameWorkView::OnSeSmoke() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_SE, VG_COMMAND_SE_SMOKE, this);
		Update();
}

void CFrameWorkView::OnSmokeset() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_SE, VG_COMMAND_SE_SMOKE_SET, this);
		Update();
}

void CFrameWorkView::OnFireset() 
{
	// TODO: Add your command handler code here

	vgApp.appProc(VG_COMMAND_SE, VG_COMMAND_SE_FIRE_SET, this);
		Update();
}

void CFrameWorkView::OnUpdateFireDel(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
//	pCmdUI->Enable()
}

void CFrameWorkView::OnUpdateSeFogDel(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(fog);
}

void CFrameWorkView::OnUpdateSeFog(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!fog);
}

void CFrameWorkView::OnDbShow() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_DB, VG_COMMAND_DB_SHOWPRO, this);
		Update();
}

void CFrameWorkView::OnSetflag() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_SE, VG_COMMAND_SE_FLAG_SET, this);
		Update();
}

void CFrameWorkView::OnAddflag() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_SE, VG_COMMAND_SE_FLAG_ADD,this);
		Update();
}

void CFrameWorkView::OnDbLink() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_DB, VG_COMMAND_DB_LINK, this);

	SetCurrentDirectoryA(vgApp.scenetree->pathbuffer);

		Update();

}

void CFrameWorkView::OnDbDatabase() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_DB, VG_COMMAND_DB_DATABASE, this);
		Update();
	
}

void CFrameWorkView::OnDbTable() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_DB, VG_COMMAND_DB_TABLE, this);	
		Update();
	
}

void CFrameWorkView::OnDbRecord() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_DB, VG_COMMAND_DB_RECORD, this);	
		Update();
	
}

void CFrameWorkView::OnDlgWater() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_SE, VG_COMMAND_SE_WATER, this);
	SetCurrentDirectoryA(vgApp.scenetree->pathbuffer);
	Update();
	
}

void CFrameWorkView::Onselectcancel() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_EDIT,VG_COMMAND_SELCANCEL, this);
	Update();
}

void CFrameWorkView::OnUpdateShuiyan(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(vgApp.scenetree->Scene.vgDem->b_render);
}

void CFrameWorkView::OnUpdateSHUiTiTIJI(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(vgApp.scenetree->Scene.vgDem->b_render);

}

void CFrameWorkView::OnUpdateShantitiji(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(vgApp.scenetree->Scene.vgDem->b_render);

}

void CFrameWorkView::OnImportbigscene() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_FILE,VG_COMMAND_FILE_OPEN, this);
	Update();

	gis =true;
}

void CFrameWorkView::OnUpdateAniStop(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
//	pCmdUI->Enable(!AniStop);
}

void CFrameWorkView::Onactuality() 
{
	// TODO: Add your command handler code here

	if (vgApp.scenetree->GetNode(10636))
	{
		vgApp.scenetree->GetNode(10636)->m_isVisible = true;
	}

	if (vgApp.scenetree->GetNode(9896))
	{
		vgApp.scenetree->GetNode(9896)->m_isVisible = false;
	}
}

void CFrameWorkView::Onplan() 
{
	// TODO: Add your command handler code here

	if (vgApp.scenetree->GetNode(10636))
	{
		vgApp.scenetree->GetNode(10636)->m_isVisible = false;
	}

	if (vgApp.scenetree->GetNode(9896))
	{
		vgApp.scenetree->GetNode(9896)->m_isVisible = true;
	}
}

void CFrameWorkView::Onloadbigterrain() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_TIN , VG_COMMAND_GEN_BIG_TIN,this);

	SetCurrentDirectoryA(vgApp.scenetree->pathbuffer);

	gis =true;
}

void CFrameWorkView::OnSethawk() 
{
	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_GIS,VG_COMMAND_GIS_HAWKSET, this);
	Update();
}

void CFrameWorkView::OnSoundset()
{
	SetTimer(2, 500, NULL);

	// TODO: Add your command handler code here
	vgCore::QuadtreeSceneManager::getSingleton().vgOpenAlSet.DoModal();
}

void CFrameWorkView::OnOpenalon()
{
	// TODO: Add your command handler code here
	vgCore::QuadtreeSceneManager::getSingleton().vgOpenAlSet.Play();
}

void CFrameWorkView::OnOpenaloff()
{
	// TODO: Add your command handler code here
	vgCore::QuadtreeSceneManager::getSingleton().vgOpenAlSet.stop();
}

void CFrameWorkView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	vgApp.scenetree->vgCurrentMode = VG_STATUS_CAM;

	vgApp.m_CurrentCamera->m_Point1 = point;


	SetCursor(LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_HAND_CURSOR)));


}

void CFrameWorkView::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	vgApp.scenetree->vgCurrentMode = -1;

	SetCursor(LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_HAND_CURSOR)));

	CView::OnMButtonUp(nFlags, point);
}


void CFrameWorkView::OnWaterEdit()
{
	// TODO: Add your command handler code here

	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_SE, VG_COMMAND_SE_WATER_EDIT, this);
	SetCurrentDirectoryA(vgApp.scenetree->pathbuffer);
	Update();

}

void CFrameWorkView::OnWaterConvert()
{
	vgApp.appProc(VG_COMMAND_SE, VG_COMMAND_SE_WATER_CONVERT, this);
	SetCurrentDirectoryA(vgApp.scenetree->pathbuffer);
	Update();

}

void CFrameWorkView::OnGlassConvert()
{
	vgApp.appProc(VG_COMMAND_SE, VG_COMMAND_SE_GLASS_CONVERT, this);
	SetCurrentDirectoryA(vgApp.scenetree->pathbuffer);
	Update();
}

void CFrameWorkView::OnMirrorConvert()
{
	vgApp.appProc(VG_COMMAND_SE, VG_COMMAND_SE_MIRROR_CONVERT, this);
	SetCurrentDirectoryA(vgApp.scenetree->pathbuffer);
	Update();
}

void CFrameWorkView::OnMetalConvert()
{
	vgApp.appProc(VG_COMMAND_SE, VG_COMMAND_SE_METAL_CONVERT, this);
	SetCurrentDirectoryA(vgApp.scenetree->pathbuffer);
	Update();
}

void CFrameWorkView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	vgCore::QuadtreeSceneManager &mgr = 
		vgCore::QuadtreeSceneManager::getSingleton();

	vgCore::CameraNode &camera = mgr.GetCurrentCamera();

	if ( bActivate == true )
	{
		camera._useKeyControl = true;
	}
	else
	{
		camera._useKeyControl = false;
	}

	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CFrameWorkView::OnCameraCapture()
{
	vgCore::QuadtreeSceneManager::getSingleton().GetCurrentCamera().captureToFile();
	
}

void CFrameWorkView::OnPipTurnon()
{
	assert( vgCore::PictureInPicture::getSingletonPtr() != NULL );

	vgCore::PictureInPicture::getSingleton().turnOnOrOff();
}

void CFrameWorkView::OnPipTurnoff()
{
	assert( vgCore::PictureInPicture::getSingletonPtr() != NULL );

	vgCore::PictureInPicture::getSingleton().turnOff();
}

void CFrameWorkView::OnPipSave()
{
	assert( vgCore::PictureInPicture::getSingletonPtr() != NULL );

	vgCore::PictureInPicture::getSingleton().savePIP();
}

void CFrameWorkView::OnPipConfig()
{
	assert( vgCore::PictureInPicture::getSingletonPtr() != NULL );

	SetTimer(2, 500, NULL);

	vgCore::QuadtreeSceneManager::getSingleton().GetCurrentCamera()._useKeyControl = false;

	DlgPIPConfig dlg;
	dlg.DoModal();

	vgCore::QuadtreeSceneManager::getSingleton().GetCurrentCamera()._useKeyControl = true;
}

void CFrameWorkView::OnPipMoveXSub()
{
	vgCore::QuadtreeSceneManager::getSingleton().GetCurrentCamera()._useKeyControl = false;
	vgCore::PictureInPicture::getSingleton()._pipBegin.x -= 1;
	vgCore::QuadtreeSceneManager::getSingleton().GetCurrentCamera()._useKeyControl = true;
}

void CFrameWorkView::OnPipMoveXAdd()
{
	vgCore::QuadtreeSceneManager::getSingleton().GetCurrentCamera()._useKeyControl = false;

	vgCore::PictureInPicture::getSingleton()._pipBegin.x += 1;
	vgCore::QuadtreeSceneManager::getSingleton().GetCurrentCamera()._useKeyControl = true;

}

void CFrameWorkView::OnPipMoveYSub()
{
	vgCore::QuadtreeSceneManager::getSingleton().GetCurrentCamera()._useKeyControl = false;

	vgCore::PictureInPicture::getSingleton()._pipBegin.y -= 1;
	vgCore::QuadtreeSceneManager::getSingleton().GetCurrentCamera()._useKeyControl = true;

}

void CFrameWorkView::OnPipMoveYAdd()
{
	vgCore::QuadtreeSceneManager::getSingleton().GetCurrentCamera()._useKeyControl = false;

	vgCore::PictureInPicture::getSingleton()._pipBegin.y += 1;
	vgCore::QuadtreeSceneManager::getSingleton().GetCurrentCamera()._useKeyControl = true;

}

void CFrameWorkView::OnPipResizeXSub()
{
	vgCore::QuadtreeSceneManager::getSingleton().GetCurrentCamera()._useKeyControl = false;

	vgCore::PictureInPicture::getSingleton()._pipWidth -= 1;
	vgCore::QuadtreeSceneManager::getSingleton().GetCurrentCamera()._useKeyControl = true;

}

void CFrameWorkView::OnPipResizeXAdd()
{
	vgCore::QuadtreeSceneManager::getSingleton().GetCurrentCamera()._useKeyControl = false;

	vgCore::PictureInPicture::getSingleton()._pipWidth += 1;
	vgCore::QuadtreeSceneManager::getSingleton().GetCurrentCamera()._useKeyControl = true;

}

void CFrameWorkView::OnPipResizeYSub()
{
	vgCore::QuadtreeSceneManager::getSingleton().GetCurrentCamera()._useKeyControl = false;

	vgCore::PictureInPicture::getSingleton()._pipHeight -= 1;
	vgCore::QuadtreeSceneManager::getSingleton().GetCurrentCamera()._useKeyControl = true;

}

void CFrameWorkView::OnPipResizeYAdd()
{
	vgCore::QuadtreeSceneManager::getSingleton().GetCurrentCamera()._useKeyControl = false;

	vgCore::PictureInPicture::getSingleton()._pipHeight += 1;
	vgCore::QuadtreeSceneManager::getSingleton().GetCurrentCamera()._useKeyControl = true;

}

void CFrameWorkView::OnPipSaveCubeMap()
{
	vgCore::PictureInPicture::getSingleton().saveCubeMap();
}

void CFrameWorkView::OnGlassEdit()
{
	vgCore::QuadtreeSceneManager::getSingleton().editSelectedEffectNode<
		VG_GLASS, vgCore::GlassNode , DlgGlass >();
}

void CFrameWorkView::OnMirrorEdit()
{
	vgCore::QuadtreeSceneManager::getSingleton().editSelectedEffectNode<
		VG_MIRROR, vgCore::MirrorNode , DlgMirror >();}

void CFrameWorkView::OnMetalEdit()
{
	vgCore::QuadtreeSceneManager::getSingleton().editSelectedEffectNode<
		VG_METAL, vgCore::MetalNode , DlgMetal >();}

void CFrameWorkView::OnControlPc()
{
	// TODO: 在此添加命令处理程序代码
	m_socket.Create(2007,SOCK_DGRAM); 
	hSendThread=CreateThread(NULL,
		0,
		/*(LPTHREAD_START_ROUTINE)*/ThreadFunc,
		(LPVOID)&vgApp.scenetree->GetCurrentCamera(),/*NULL*/
		0,
		&ThreadID);
	vgApp.b3Channel=TRUE;
}

void CFrameWorkView::OnCloseSed()
{
	// TODO: 在此添加命令处理程序代码
	m_socket.Close();
	vgApp.b3Channel=FALSE;
}

void CFrameWorkView::OnControledPc()
{
	// TODO: 在此添加命令处理程序代码
	m_recvsocket=new vgRecvSock(this);
	m_recvsocket->Create(3550,SOCK_DGRAM);
	vgApp.b3Channel=TRUE;

}

void CFrameWorkView::OnP1()
{
	// TODO: 在此添加命令处理程序代码
	vgApp.PCnum=1;
	vgApp.b3Channel=TRUE;
}

void CFrameWorkView::OnM1()
{
	// TODO: 在此添加命令处理程序代码
	vgApp.PCnum=-1;
	vgApp.b3Channel=TRUE;
}

void CFrameWorkView::OnCloseRev()
{
	// TODO: 在此添加命令处理程序代码
	m_recvsocket->Close();
	vgApp.b3Channel=FALSE;
}

void CFrameWorkView::OnSoftedge()
{
	// TODO: 在此添加命令处理程序代码
	vgApp.bSoftEdge=TRUE;
}

void CFrameWorkView::OnHardedge()
{
	// TODO: 在此添加命令处理程序代码
	vgApp.bSoftEdge=FALSE;
}

void CFrameWorkView::OnVs()
{

	SetTimer(2, 500, NULL);

	// TODO: 在此添加命令处理程序代码VS
	vgDlgVS dlg;
	dlg.DoModal();
	vgApp.mNear=dlg.m_near;
	vgApp.mFar=dlg.m_far;
	vgApp.mFov=dlg.m_fov;
	vgApp.mAspect=dlg.m_aspect;
}


void CFrameWorkView::Process( char* lbuff )
{
	vgCore::CameraNode &cam=this->vgApp.scenetree->GetCurrentCamera();
	ViewerControl *buff=(class ViewerControl*)lbuff;
	//////////////////////////////////////////////////////////////////////////
	//只水平偏移！
	//  	float rad_xz = float (3.13149* buff->g_Angle/180.0f);	//计算左右旋转角度
	//  	//根据视点朝向的角度，决定那里向哪个方向的左侧或者右侧加一个偏移
	//  	cam.g_eye[0]=buff->x+200*(float)sin(rad_xz);
	//  	cam.g_eye[1]=buff->y;
	//  	cam.g_eye[2]=buff->z-200*(float)cos(rad_xz);
	//  	cam.g_look[0]=buff->dx+200*(float)sin(rad_xz);
	//  	cam.g_look[1]=buff->dy;
	//  	cam.g_look[2]=buff->dz-200*(float)cos(rad_xz);
	//  	cam.g_Angle=buff->g_Angle;
	//  	cam.g_elev=buff->g_elev;
	//  	cam.speed=buff->speed;


	//////////////////////////////////////////////////////////////////////////
	float rad_xz = float (3.13149* buff->g_Angle/180.0f);	//计算左右旋转角度
	//根据视点朝向的角度，决定那里向哪个方向的左侧或者右侧加一个偏移
	cam.g_eye[0]=buff->x;
	cam.g_eye[1]=buff->y;
	cam.g_eye[2]=buff->z;
	cam.g_look[0]=buff->dx;
	cam.g_look[1]=buff->dy;
	cam.g_look[2]=buff->dz;
	cam.g_Angle=buff->g_Angle;
	cam.g_elev=buff->g_elev;
	cam.speed=buff->speed;

	//////////////////////////////////////////////////////////////////////////
	// 	float rad_xz1 = float (3.13149* buff->g_Angle/180.0f);	//右视点只旋转角度
	// 	float rad_xz2 = float (3.13149* (buff->g_Angle-20)/180.0f);	//旋转20角度
	// 	float hhh=sqrt((buff->x-buff->dx)*(buff->x-buff->dx)+(buff->y-buff->dy)*(buff->y-buff->dy)+(buff->z-buff->dz)*(buff->z-buff->dz));
	// 	cam.g_eye[0]=buff->x;
	// 	cam.g_eye[1]=buff->y;
	// 	cam.g_eye[2]=buff->z;
	// 	cam.g_look[0]=buff->dx+hhh*(float)cos(rad_xz1)-hhh*(float)cos(rad_xz2);
	// 	cam.g_look[1]=buff->dy;
	// 	cam.g_look[2]=buff->dz+hhh*(float)sin(rad_xz1)-hhh*(float)sin(rad_xz2);
	// 	cam.g_Angle=buff->g_Angle-20;
	// 	cam.g_elev=buff->g_elev;
	// 	cam.speed=buff->speed;

	//  	this->vgApp.scenetree->eye_pos = Vector3(this->vgApp.scenetree->vgCurrentCamera.g_eye[0],
	//  		this->vgApp.scenetree->vgCurrentCamera.g_eye[1],
	//  		this->vgApp.scenetree->vgCurrentCamera.g_eye[2]);
	//	this->vgApp.scenetree->vgCurrentCamera.g_look[0]


	//	::SwapBuffers(this->vgApp.vgDC->GetSafeHdc());
	//InvalidateRect(vgApp.vgWnd,TRUE);
	//
	//	::glFinish();
	//	UpdateWindow();
	//	vgApp.isNeedUpdate=true;
	//InvalidateRect(vgApp.vgWnd,false);//
	//InvalidateRect(NULL); 
	Invalidate(TRUE);//这就是更新的关键句
}
DWORD WINAPI  CFrameWorkView::ThreadFunc(LPVOID Data)
{
	//	m_bSendRun=TRUE;m_bSendRun
	while(1)
	{
		vgCore::CameraNode *cam=(vgCore::CameraNode *)Data;/*vgApp.scenetree->GetCurrentCamera()*/
		ViewerControl nn;
		nn.x=cam->g_eye[0];
		nn.y=cam->g_eye[1];
		nn.z=cam->g_eye[2];
		nn.dx=cam->g_look[0];
		nn.dy=cam->g_look[1];
		nn.dz=cam->g_look[2];
		nn.g_Angle =cam->g_Angle;
		nn.g_elev=cam->g_elev;
		nn.speed = cam->speed;
		//vgSock m_socket;
		//CString ip="222.195.148.255";
		/*ipto="222.195.148.255";*/
		m_socket.SendTo(&nn,sizeof(nn),3550,ipto);
		Sleep(20);//
	}
	return 0;
}

void CFrameWorkView::OnSkyboxConvert()
{
	SetTimer(2, 500, NULL);

	vgCore::QuadtreeSceneManager::getSingleton().convertSelectedObjectToSkyboxNode();
}

void CFrameWorkView::OnConvertBrigthfloor()
{

	SetTimer(2, 500, NULL);
	vgCore::QuadtreeSceneManager::getSingleton().convertSelectedObjectToEffectNode
		< vgCore::BrightfloorNode , DlgBrightfloor , vgCore::IMG_BRIGHTFLOOR >();
}

void CFrameWorkView::OnBrightfloorEdit()
{
	SetTimer(2, 500, NULL);

	vgCore::QuadtreeSceneManager::getSingleton().editSelectedEffectNode<
		VG_BRIGHTFLOOR, vgCore::BrightfloorNode , DlgBrightfloor >();
}

void CFrameWorkView::OnAviNodeConvert()
{
	SetTimer(2, 500, NULL);

	vgCore::QuadtreeSceneManager::getSingleton().convertSelectedObjectToEffectNode
		< vgCore::AviNode , DlgAviNode , vgCore::IMG_AVINODE >();
}

void CFrameWorkView::OnAvinodeEdit()
{
	SetTimer(2, 500, NULL);

	vgCore::QuadtreeSceneManager::getSingleton().editSelectedEffectNode<
		VG_AVINODE, vgCore::AviNode , DlgAviNode >();
}

void CFrameWorkView::OnCameratrackRename()
{

	vgCore::CameraTrack *pani = vgCore::QuadtreeSceneManager::getSingleton().vgcurrentani;

	if (  pani == NULL )
	{
		::MessageBox(NULL, "请确认选中动画!" , "ERROR" , MB_OK );
		return;
	}

	vgCore::QuadtreeSceneManager::getSingleton().GetCurrentCamera()._useKeyControl = false;

	SetTimer(2, 500, NULL);


	DlgCamertrackRename dlg( pani );
	dlg.DoModal();

	vgCore::QuadtreeSceneManager::getSingleton().GetCurrentCamera()._useKeyControl = true;
}

void CFrameWorkView::OnPublish()
{
	vgCore::QuadtreeSceneManager::getSingleton().GetCurrentCamera()._useKeyControl = false;

	// TODO: Add your command handler code here
	vgApp.appProc(VG_COMMAND_FILE, VG_COMMAND_PUBLISH, this);	

	vgCore::QuadtreeSceneManager::getSingleton().GetCurrentCamera()._useKeyControl = true;


	Update();
}

void CFrameWorkView::OnChangeRendertype()
{
	std::set<int>::iterator iter =
		vgCore::QuadtreeSceneManager::getSingleton().model_pick_set.begin();
	std::set<int>::iterator iter_end =
		vgCore::QuadtreeSceneManager::getSingleton().model_pick_set.end();


	for ( ; iter != iter_end ; ++ iter )
	{
		vgCore::NodeAbstract* abs = 
			vgCore::QuadtreeSceneManager::getSingleton().GetNodeAbstract((*iter));


		abs->RenderType = 2;

		vgCore::Node* node = 
			vgCore::QuadtreeSceneManager::getSingleton().GetNode((*iter));

		node->RenderType = 2;
	}



}

void CFrameWorkView::OnRendermodeShade()
{
	vgCore::QuadtreeSceneManager::getSingleton()._bWireFrameMode = false;
}

void CFrameWorkView::OnRendermodeWireframe()
{
	vgCore::QuadtreeSceneManager::getSingleton()._bWireFrameMode = true;
}

void CFrameWorkView::OnTerrainLevellingBegin()
{
	vgApp.scenetree->vgCurrentMode = VG_STATUS_TERRAIN_LEVELLING_LBTNDOWN;
}

void CFrameWorkView::OnTerrainSave()
{
	vgCore::TerrainManager::getSingleton().saveVgtrFile();
}

void CFrameWorkView::OnTerrainDropData()
{
	vgCore::TerrainManager::getSingleton().dropTerrianData();
}

void CFrameWorkView::OnTerrainRenderOn()
{
	vgCore::TerrainManager::getSingleton().turnOnRenderFlag();
}

void CFrameWorkView::OnTerrainRenderOff()
{
	vgCore::TerrainManager::getSingleton().turnOffRenderFlag();
}

void CFrameWorkView::OnTerrainConverDemsToVgtr()
{
	vgCore::TerrainManager::getSingleton().selectDemsToVgtr();
}

void CFrameWorkView::OnTerrainConvertVgtrToBmp()
{
	vgCore::TerrainManager::getSingleton().convertVgtrToHeightImage();
}

void CFrameWorkView::OnMatchRoad()
{
	// TODO: 在此添加命令处理程序代码

	SetTimer(2, 500, NULL);

	vgApp.scenetree->AddGismatch();

	vgApp.scenetree->vgCurrentMode = VG_STATUS_GIS_MATCH;
}

void CFrameWorkView::OnOptplant()
{
	vgApp.scenetree->convertbillboard();
}

void CFrameWorkView::OnUpdateOptplant(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!vgApp.scenetree->Scene.m_BillConvert.b_render);
}

void CFrameWorkView::OnTransall()//2008.5.9
{
	SetTimer(2, 500, NULL);

	vgApp.scenetree->m_vgtransall.DoModal();

	vgDlgTransAll &p = vgApp.scenetree->m_vgtransall;

	vgApp.scenetree->TransAllNode(Vector3(p.m_transx, p.m_transy, p.m_transz));

	vgApp.scenetree->m_vgtransall.Reset();
	// TODO: 在此添加命令处理程序代码
}


void CFrameWorkView::_mViewShowTestInfo()
{
	CFrameWorkDoc* pDoc = _mViewGetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// 绘制三角面数/总三角面数 比率
	unsigned	faceCountVisible	= vgCore::QuadtreeSceneManager::getSingleton().GetFaceCountVisible();
	unsigned	faceCountTotal		= vgCore::QuadtreeSceneManager::getSingleton().GetFaceCountTotle();
	float	faceRateRender = faceCountVisible / (faceCountTotal+0.001f);

	// 是否使用四叉树标志
	string	strDrawMode;
	vgCore::QuadtreeSceneManager::drawmode	drawMode = 	vgCore::QuadtreeSceneManager::getSingleton().m_currentmode;
	switch( drawMode )
	{
	case vgCore::QuadtreeSceneManager::LineQueue:
		strDrawMode = "线性队列";
		break;

	case vgCore::QuadtreeSceneManager::QUADTREE:
		strDrawMode = "四叉树";
		break;

	default:
		break;
	}

	// 是否使用新四叉树标志
	string	strTreeMode;
	bool	bTreeMode = 	vgCore::QuadtreeSceneManager::getSingleton().m_bUseNewtree;
	if( bTreeMode )
	{
		strTreeMode = "新";
	}
	else
	{
		strTreeMode = "旧";
	}

	string	strVersionMode;
#ifdef	_DEBUG
	strVersionMode	= "Debug";
#else
	strVersionMode	= "Release";
#endif

	CString	strDataCountRender;
	strDataCountRender.Format( "渲染三角面数/总三角面数== %d / %d == %d%%____&&____%s____&&____%s____&&____%s",
		//渲染三角面数/总面数== %d / %d == %d%%",
		faceCountVisible ,
		faceCountTotal ,
		int(faceRateRender *100 + 0.5f ),
		strDrawMode.c_str(),
		strTreeMode.c_str(),
		strVersionMode.c_str()
		//faceCountVisible ,
		//faceCountTotal ,
		//int(faceRateRender *100 + 0.5f ) 
		);

	GetParent()->SetWindowText( strDataCountRender );


	//if(!pFrm)
	//	pFrm=(CMainFrame*)AfxGetApp()->m_pMainWnd;

	//pFrm->m_wndStatusBar.SetPaneText(0, strDataCountRender,false);	
	//pFrm->m_wndStatusBar.SetWindowText( strDataCountRender );

}

// 获取	文档对象
CFrameWorkDoc* CFrameWorkView::_mViewGetDocument(void) const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFrameWorkDoc)));
	return (CFrameWorkDoc*)m_pDocument;
}
void CFrameWorkView::OnRButtonDown(UINT nFlags, CPoint point)
{
	vgApp.RButtonDown(nFlags , point, this);

	CView::OnRButtonDown(nFlags, point);
}

void CFrameWorkView::OnRButtonUp(UINT nFlags, CPoint point)
{
	vgApp.RButtonUp(nFlags , point, this);

	CView::OnRButtonUp(nFlags, point);
}

void CFrameWorkView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	vgApp.RDoubleButtonUp(nFlags , point, this);

	CView::OnRButtonDblClk(nFlags, point);
}

void CFrameWorkView::OnCameraModeFly()
{
	vgApp.scenetree->_RDoubleBtnDown = true;
}

void CFrameWorkView::OnCameraModeKeyboard()
{
	vgApp.scenetree->_RDoubleBtnDown = false;
	//vgApp.scenetree->GetCurrentCamera().g_elev = 0;

}

void CFrameWorkView::OnMusicConfig()
{
	SetTimer(2, 500, NULL);

	vgCore::SoundManager::getSingleton().initBackgroundMusic();
}

void CFrameWorkView::OnDeleteAllCameratrack()
{
	vgCore::QuadtreeSceneManager::getSingleton().Scene.vgAnimationSet.RemoveAll();
}

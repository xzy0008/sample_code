// FrameWorkView.h : interface of the CFrameWorkView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FRAMEWORKVIEW_H__D982AEBD_95A2_4304_80CE_91A38EAD5957__INCLUDED_)
#define AFX_FRAMEWORKVIEW_H__D982AEBD_95A2_4304_80CE_91A38EAD5957__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <vgMFCApplication.h>
#include "FrameWorkDoc.h"

#include <afxmt.h>
#include <vfw.h>
#include <Digitalv.h>
#include <vgSock.h>
//#include <vgRecvSock.h>
#include "vgDlgVS.h"

class vgRecvSock;



#define	WM_FILEOPEN		WM_USER+1

class CMainFrame;
class CFrameWorkView : public CView
{
protected: // create from serialization only
	CFrameWorkView();
	DECLARE_DYNCREATE(CFrameWorkView)

// Attributes
public:
	CFrameWorkDoc* GetDocument();

public://UI控制

	bool AniPause;
	bool AniStop;


public:
	bool Rainon;
	bool Snowon;
	int firenum;
	bool Settin1;
	bool Settin2;
	bool music;

	bool gis;

	bool fog;


	//------------------------------------------
	// 三通道
	//------------------------------------------
	DWORD ThreadID;
	HANDLE hSendThread;
	vgRecvSock *m_recvsocket;


private:
	
	CEvent m_Event;
	HWND c_Player;
	
	unsigned   long   wLength;
	
	MCI_DGV_OPEN_PARMS   mciOpen;   
	MCI_DGV_PLAY_PARMS   playParam; 		
	
	UINT wDeviceID;
	
	//音乐文件名 default=_T("")
	CString m_strFileName;

	
	

// Operations
public:
	vgCore::MFCApplication vgApp;

	static DWORD WINAPI exchange(LPVOID Data);

	HANDLE h_Thread;

	GLdouble 	gldAspect;
	
	CMainFrame *pFrm;
	
	//------------------------------------------
	// 三通道
	//------------------------------------------
	void Process(char* lbuff);
	static DWORD WINAPI ThreadFunc(LPVOID Data);

	static vgSock m_socket;
	static CString ipto;

// 	CPoint pt1;
// 	CPoint pt2;
// 	int a,b,c,d;
//     int i;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFrameWorkView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	CString m_strFilePath;
	virtual ~CFrameWorkView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFrameWorkView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnImport();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnCreatcam();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnFileSave();
	afx_msg void OnVGFileOpen();
	afx_msg void Onshadowoff();
	afx_msg void OnShadowON();
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSwitchcam();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTransx();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTransy();
	afx_msg void OnTransz();
	afx_msg void OnRotx();
	afx_msg void OnRoty();
	afx_msg void OnRotz();
	afx_msg void OnScalex();
	afx_msg void OnScaley();
	afx_msg void OnScalez();
	afx_msg void OnScalexyz();
	afx_msg void OnPositiontoobj();
	afx_msg void OnUndo();
	afx_msg void OnShowcurcampro();
	afx_msg void OnUpdateUndo(CCmdUI* pCmdUI);
	afx_msg void OnRedo();
	afx_msg void OnUpdateRedo(CCmdUI* pCmdUI);
	afx_msg void OnSettree();
	afx_msg void OnBeginplant();
	afx_msg void OnSelect();
	afx_msg void OnPlantinline();
	afx_msg void OnGenhawkimg();
	afx_msg void OnHawkeyeon();
	afx_msg void OnHawkeyeoff();
	afx_msg void OnGettwopoint();
	afx_msg void OnShutdownpath();
	afx_msg void OnPathfly();
	afx_msg void OnUpdateGettwopoint(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePathfly(CCmdUI* pCmdUI);
	afx_msg void OnUpdateShutdownpath(CCmdUI* pCmdUI);
	afx_msg void OnAddanimation();
	afx_msg void OnANIStart();
	afx_msg void OnAniEnd();
	afx_msg void OnAniPlay();
	afx_msg void OnAniStop();
	afx_msg void OnAniPause();
	afx_msg void OnAniResume();
	afx_msg void OnUpdateAniPause(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAniResume(CCmdUI* pCmdUI);
	afx_msg void OnSeFountain();
	afx_msg void Onfountianset();
	afx_msg void OnSetdem();
	afx_msg void OnGenterrain();
	afx_msg void OnDdddddd();
	afx_msg void OnZuobiao();
	afx_msg void OnJuli();
	afx_msg void OnMianji();
	afx_msg void OnTiji();
	afx_msg void OnShuiyan();
	afx_msg void OnSHUiTiTIJI();
	afx_msg void OnShantitiji();
	afx_msg void OnTongtoupanding();
	afx_msg void OnHjm();
	afx_msg void OnDgx();
	afx_msg void OnRain();
	afx_msg void OnSnow();
	afx_msg void OnFire();
	afx_msg void OnRainDel();
	afx_msg void OnSnowDel();
	afx_msg void OnFireAdd();
	afx_msg void OnFogDel();
	afx_msg void OnUpdateRain(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRainDel(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSnow(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSnowDel(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGenterrain(CCmdUI* pCmdUI);
	afx_msg void OnMusicon();
	afx_msg void OnUpdateMusicon(CCmdUI* pCmdUI);
	afx_msg void OnMusicoff();
	afx_msg void OnUpdateMusicoff(CCmdUI* pCmdUI);
	afx_msg void OnDem();
	afx_msg void OnDom();
	afx_msg void OnLoadani();
	afx_msg void OnUnloadani();
	afx_msg void OnAppAbout();
	afx_msg void OnUpdateHjm(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDgx(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTongtoupanding(CCmdUI* pCmdUI);
	afx_msg void OnSeFog();
	afx_msg void OnSeFogDel();
	afx_msg void OnSeSmoke();
	afx_msg void OnSmokeset();
	afx_msg void OnFireset();
	afx_msg void OnUpdateFireDel(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSeFogDel(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSeFog(CCmdUI* pCmdUI);
	afx_msg void OnDbShow();
	afx_msg void OnSetflag();
	afx_msg void OnAddflag();
	afx_msg void OnDbLink();
	afx_msg void OnDbDatabase();
	afx_msg void OnDbTable();
	afx_msg void OnDbRecord();
	afx_msg void OnDlgWater();
	afx_msg void Onselectcancel();
	afx_msg void OnUpdateShuiyan(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSHUiTiTIJI(CCmdUI* pCmdUI);
	afx_msg void OnUpdateShantitiji(CCmdUI* pCmdUI);
	afx_msg void OnImportbigscene();
	afx_msg void OnUpdateAniStop(CCmdUI* pCmdUI);
	afx_msg void Onactuality();
	afx_msg void Onplan();
	afx_msg void Onloadbigterrain();
	afx_msg void OnSethawk();
	//}}AFX_MSG

	afx_msg LRESULT OnFileOpen(WPARAM wParam,LPARAM lParam);   //自己做个消息

	DECLARE_MESSAGE_MAP()
	void Update();
public:
	afx_msg void OnSoundset();
	afx_msg void OnOpenalon();
	afx_msg void OnOpenaloff();
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);

	afx_msg void OnWaterEdit();
	afx_msg void OnWaterConvert();
	afx_msg void OnGlassConvert();
	afx_msg void OnMirrorConvert();
	afx_msg void OnMetalConvert();
protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
public:
	afx_msg void OnCameraCapture();
	afx_msg void OnPipTurnon();
	afx_msg void OnPipTurnoff();
	afx_msg void OnPipSave();
	afx_msg void OnPipConfig();
	afx_msg void OnPipMoveXSub();
	afx_msg void OnPipMoveXAdd();
	afx_msg void OnPipMoveYSub();
	afx_msg void OnPipMoveYAdd();
	afx_msg void OnPipResizeXSub();
	afx_msg void OnPipResizeXAdd();
	afx_msg void OnPipResizeYSub();
	afx_msg void OnPipResizeYAdd();
	afx_msg void OnPipSaveCubeMap();
	afx_msg void OnGlassEdit();
	afx_msg void OnMirrorEdit();
	afx_msg void OnMetalEdit();
	afx_msg void OnControlPc();
	afx_msg void OnCloseSed();
	afx_msg void OnControledPc();
	afx_msg void OnP1();
	afx_msg void OnM1();
	afx_msg void OnCloseRev();
	afx_msg void OnSoftedge();
	afx_msg void OnHardedge();
	afx_msg void OnVs();
	afx_msg void OnSkyboxConvert();
	afx_msg void OnConvertBrigthfloor();
	afx_msg void OnBrightfloorEdit();
	afx_msg void OnAviNodeConvert();
	afx_msg void OnAvinodeEdit();
	afx_msg void OnCameratrackRename();
	afx_msg void OnPublish();
	afx_msg void OnChangeRendertype();
	afx_msg void OnRendermodeShade();
	afx_msg void OnRendermodeWireframe();
	afx_msg void OnTerrainLevellingBegin();
	afx_msg void OnTerrainSave();
	afx_msg void OnTerrainDropData();
	afx_msg void OnTerrainRenderOn();
	afx_msg void OnTerrainRenderOff();
	afx_msg void OnTerrainConverDemsToVgtr();
	afx_msg void OnTerrainConvertVgtrToBmp();
	afx_msg void OnMatchRoad();
	afx_msg void OnOptplant();
	afx_msg void OnUpdateOptplant(CCmdUI *pCmdUI);
	afx_msg void OnTransall();


	// 2008年5月9日20:00:39 add by lss
	void _mViewShowTestInfo(void);
	CFrameWorkDoc*  _mViewGetDocument(void)  const;
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnCameraModeFly();
	afx_msg void OnCameraModeKeyboard();
	afx_msg void OnMusicConfig();
	afx_msg void OnDeleteAllCameratrack();
};

#ifndef _DEBUG  // debug version in FrameWorkView.cpp
inline CFrameWorkDoc* CFrameWorkView::GetDocument()
   { return (CFrameWorkDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRAMEWORKVIEW_H__D982AEBD_95A2_4304_80CE_91A38EAD5957__INCLUDED_)

#pragma once

// vgActiveXCtrl.h : Declaration of the CvgActiveXCtrl ActiveX Control class.
#include <vgMFCApplication.h>
#include <afxmt.h>
#include <vfw.h>
#include "Digitalv.h"

// CvgActiveXCtrl : See vgActiveXCtrl.cpp for implementation.

class CvgActiveXCtrl : public COleControl
{
	DECLARE_DYNCREATE(CvgActiveXCtrl)

// Constructor
public:
	CvgActiveXCtrl();

// Overrides
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// Implementation
protected:
	~CvgActiveXCtrl();

	DECLARE_OLECREATE_EX(CvgActiveXCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CvgActiveXCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CvgActiveXCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CvgActiveXCtrl)		// Type name and misc status

// Message maps
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
		dispidImportDemDomDlg = 14L,
		dispidImportDemDom = 13L,
		dispidSetGisWaterLevel = 12L,
		dispidOnMusicOff = 29L,
		dispidOnMusicOn = 28L,
		dispidDBInfoShow = 27L,
		dispidSetGisContour = 11L,
		dispidStartPlayAni = 26L,
		dispidSwitchCam = 25L,
		dispidSetGisShadowOff = 24L,
		dispidSetGisShadowOn = 23L,
		dispidSetGisHawkEyeOff = 22L,
		dispidSetGisHawkEyeOn = 21L,
		dispidOffSeFog = 20L,
		dispidSetSeFog = 19L,
		dispidOffSeRain = 18L,
		dispidSetSeRain = 17L,
		dispidOffSeSnow = 16L,
		dispidSetSeSnow = 15L,
		dispidSetGisCut = 30L,
		dispidSetGisP2P = 10L,
		dispidSetGisMVolume = 9L,
		dispidSetGisWVolume = 8L,
		dispidSetGisFlood = 7L,
		dispidSetGisVolume = 6L,
		dispidSetGisArea = 5L,
		dispidSetGisDis = 4L,
		dispidSetGisPos = 3L,
		dispidImportVgFileDlg = 2L,
		dispidImportVgFile = 1L
	};
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

	//动画


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

	HANDLE h_Thread;

	GLdouble 	gldAspect;
public:

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void Update(void);
protected:
	void ImportVgFile(LPCTSTR vgfilename);
	void ImportVgFileDlg(void);
	void SetGisPos(void);
	void SetGisDis(void);
	void SetGisArea(void);
	void SetGisVolume(void);
	void SetGisFlood(void);
	void SetGisWVolume(void);
	void SetGisMVolume(void);
	void SetGisP2P(void);
	void SetGisCut(void);
	void SetSeSnow(void);
	void OffSeSnow(void);
	void SetSeRain(void);
	void OffSeRain(void);
	void SetSeFog(void);
	void OffSeFog(void);
	void SetGisHawkEyeOn(void);
	void SetGisHawkEyeOff(void);
	void SetGisShadowOn(void);
	void SetGisShadowOff(void);
	void SwitchCam(LONG ID);
	void StartPlayAni(LONG ID);
	void SetGisContour(void);
	void DBInfoShow(LPCTSTR buildingname);
	void OnMusicOn(void);
	void OnMusicOff(void);
	void SetGisWaterLevel(FLOAT waterlevel);
	void ImportDemDom(LPCTSTR demfile, LPCTSTR domfile);
	void ImportDemDomDlg(void);
};


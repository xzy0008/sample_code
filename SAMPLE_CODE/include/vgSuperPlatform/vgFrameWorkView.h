// vgFrameWorkView.h : interface of the CvgFrameWorkView class
//


#pragma once



#include "vgBaseEntry.h"
#include <vector>

#include <vgMFCApplication.h>
#include <vgSuperPlatform/IPDlg.h>
#include <afxsock.h>
using std::vector;
#include "ChannelClient.h"
#include "ChannelServer.h"
#include "vgViewerControl.h"
#include "vgFrameBuffer.h"
#include "vgCam/vgcaAviFile.h"
#include "vgAviExportDialog.h"

//////////////////////////////////////////////////////////////////////////
//三通道
//////////////////////////////////////////////////////////////////////////
//static ChannelClient *client;
//static ChannelServer *server;
#pragma   warning(disable:4099)
struct THREADFLAG 
{
	int height;
	int width;

	bool bResize;
	bool bTerminate;
	bool bModifyFlag;
};

class CvgFrameWorkView : public CView
{
protected: // create from serialization only
	CvgFrameWorkView();
	DECLARE_DYNCREATE(CvgFrameWorkView)

	//////////////////////////////////////////////////////////////////////////

	//------------------------------------------
	// 以前的版本都写在这里
	//------------------------------------------
	vgCore::MFCApplication vgApp;

	//------------------------------------------
	// zhu raknet三通道
	//------------------------------------------
	DWORD ThreadID;
	HANDLE hSendThread;
	static DWORD WINAPI threadFunc(LPVOID Data);


	//////////////////////////////////////////////////////////////////////////
// Attributes
public:
	CvgFrameWorkDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CvgFrameWorkView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	DECLARE_MESSAGE_MAP()
	bool initGLContext(void);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
private:
	// device
	CDC*	m_pDC;
	HGLRC	m_hGLContext;

	// UI
	vector <vgBaseEntry*> &pNodeList;
	vector <vgBaseEntry*>::iterator iter;
	vector <vgBaseEntry*>::iterator end;

	vector<vgBaseEntry*> testVector;
	
	// 特效
	bool Rainon;
	bool Snowon;
	int firenum;
	//int fognum ;

	// state
	//bool	m_bIsActive;
	//bool	m_bIsFirstRead;
	bool	m_bQuadtree;
	//bool	m_bRenderBox;


	bool	m_bShowShapeLayers;
	bool	m_bEditLayers;



	bool	m_bDoubleFaceRenderSelected;
	bool	m_bDoubleFaceRenderAll;

	bool	m_bSetAsTrigger;

public:
	afx_msg void OnDestroy();
	void releaseGLContext(void);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	void renderScene(void);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnVgmImportVgm();
	afx_msg void OnVgiImportVgi();
	afx_msg void OnVgmSaveVgm();
	afx_msg void OnVgmiSaveVgmVgi();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnVgterrainWireframe();
	afx_msg void OnVgterrainNowireframe();
	afx_msg void OnVgterrainTurnon();
	afx_msg void OnActivateApp(BOOL bActive, DWORD dwThreadID);

	afx_msg LRESULT OnRender(WPARAM wParam, LPARAM lParam); 
	virtual void OnInitialUpdate();
	afx_msg void OnVgtestFf();
	afx_msg void OnVgterrainConvertDemToVgtr();
	afx_msg void OnVgterrainConvertVgtrHeightmap();
	afx_msg void OnTtttttest();
	afx_msg void OnFileImportMod();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnCameraCapture();
	afx_msg void OnToolTraverseswitch();
	afx_msg void OnUpdateToolTraverseswitch(CCmdUI *pCmdUI);
	
	// 相机&相机动画
	afx_msg void OnCreatcam();
	afx_msg void OnAniStart();
	afx_msg void OnAniEnd();
	afx_msg void OnAniPlay();
	afx_msg void OnAniResume();
	afx_msg void OnAniStop();

	afx_msg void OnSwitchcam();
	afx_msg void OnPositiontoobj();


	// 特效
	afx_msg void Onfountianset();
	afx_msg void OnSeFountain();
	afx_msg void OnFireAdd();
	afx_msg void OnSeSmoke();
	afx_msg void OnAddflag();
	afx_msg void OnWaterConvert();
	afx_msg void OnWaterEdit();
	afx_msg void OnGlassConvert();
	afx_msg void OnAviNodeConvert();
	afx_msg void OnSkyboxConvert();
	afx_msg void OnBeginplant();
	afx_msg void OnDyntextureConvert();
	afx_msg void OnRain();
	afx_msg void OnRainDel();
	afx_msg void OnSnow();
	afx_msg void OnSnowDel();
	afx_msg void OnFogDel();
	afx_msg void OnSeFog();
	afx_msg void OnMirrorConvert();
	afx_msg void OnMetalConvert();
	afx_msg void OnConvertBrigthfloor();
	afx_msg void On3dsoundAdd();
	afx_msg void OnBacksoundSet();
	afx_msg void OnFileImportMs3d();
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnAddanimation();
	afx_msg void OnSettree();
	afx_msg void OnSelect();
	afx_msg void OnPlantinline();

	public:
			void showFps();

	afx_msg void OnVgterrainNewVtr();
	
	// GIS
	afx_msg void OnZuobiao();
	afx_msg void OnJuli();
	afx_msg void OnMianji();
	afx_msg void OnTiji();

	// Tools
	afx_msg void OnToolMakerVgm();
	afx_msg void OnToolMakerVgi();

	afx_msg void OnToolMakerDds();

	afx_msg void OnShapefileDb();

	// Database
	afx_msg void OnDbShow();
	afx_msg void OnDbLink();
	afx_msg void OnDbDatabase();
	afx_msg void OnDbTable();
	afx_msg void OnDbRecord();

	// File
	afx_msg void OnSceneRead();
	afx_msg void OnSceneSave();
	afx_msg void OnPublishCollect();

	// Edit
	afx_msg void OnEditSelect();
	afx_msg void OnEditSelectClear();
	afx_msg void OnFileImportKfm();

	// multi channel
	afx_msg void OnChannel1();
	afx_msg void OnChannel0();
	afx_msg void OnChannelm1();
	afx_msg void OnSetupServer();
	afx_msg void OnDestroyServer();
	afx_msg void OnNewClient();
	afx_msg void OnDelClient();

	// aboutDlg
	afx_msg void OnAppAbout();
//	afx_msg void OnSetFocus(CWnd* pOldWnd);
//	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnOccSwitch();
	afx_msg void OnFileImport();
	afx_msg void OnGismatch();


	void OnSceneSave(string	strSavePath);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnFileExport();
	afx_msg void OnUndo();
	afx_msg void OnRedo();
	afx_msg void OnMeshOrLine();
	afx_msg void OnTreeSwitch();
	afx_msg void OnUpdateTreeSwitch(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOccSwitch(CCmdUI *pCmdUI);
	afx_msg void OnEditTranall();
	afx_msg void OnShowModels();
	afx_msg void OnUpdateShowModels(CCmdUI *pCmdUI);
	afx_msg void OnNewplan();
	afx_msg void OnVgtAttach();
	afx_msg void On32971();
	afx_msg void OnUpdate32971(CCmdUI *pCmdUI);
	afx_msg void On32972();
	afx_msg void OnUpdate32972(CCmdUI *pCmdUI);
	afx_msg void On32973();
	afx_msg void OnUpdate32973(CCmdUI *pCmdUI);
	afx_msg void On32974();
	afx_msg void OnUpdate32974(CCmdUI *pCmdUI);
	afx_msg void OnVgtVisibility();
	afx_msg void OnUpdateVgtAttach(CCmdUI *pCmdUI);
	afx_msg void OnUpdateVgtVisibility(CCmdUI *pCmdUI);
	afx_msg void OnVecPoints();
	afx_msg void OnVecLines();
	afx_msg void OnVecPolygon();
	afx_msg void OnVecEdit();
	afx_msg void OnTerrainLeveling();
	afx_msg void OnHideVec();
	afx_msg void OnNoselVec();

	afx_msg void OnUpdateTerrainLeveling(CCmdUI *pCmdUI);
	afx_msg void OnVgtCutAnalysis2();
	afx_msg void OnUpdateVgtCutAnalysis2(CCmdUI *pCmdUI);
	afx_msg void OnVgtTerrainSave();
	afx_msg void OnUpdateVgtTerrainSave(CCmdUI *pCmdUI);
	afx_msg void OnVgtBlend();
	afx_msg void OnUpdateVgtBlend(CCmdUI *pCmdUI);
	afx_msg void OnVgtVisibility2();
	afx_msg void OnUpdateVgtVisibility2(CCmdUI *pCmdUI);
	afx_msg void OnVgtCutarea();
	afx_msg void OnUpdateVgtCutarea(CCmdUI *pCmdUI);
	afx_msg void OnNdbConnect();
	afx_msg void OnNdbCondition();
	afx_msg void OnCollisionOnoff();
	afx_msg void OnUpdateCollisionOnoff(CCmdUI *pCmdUI);
	afx_msg void OnVgtMappingOrigin();
	afx_msg void OnUpdateVgtMappingOrigin(CCmdUI *pCmdUI);
	afx_msg void OnVectorShpImport();
	afx_msg void OnVectorShpShow();
	afx_msg void OnVectorShpExport2db();
	afx_msg void OnVectorShpAttachTerrain();
	afx_msg void OnVectorShpTranLayer();
	afx_msg void OnVectorShpEditState();
	afx_msg void OnUpdateVectorShpShow(CCmdUI *pCmdUI);
	afx_msg void OnUpdateVectorShpEditState(CCmdUI *pCmdUI);




// for rfb version
private:
	void playVCR(string vcrName);

	void stopVCR(string vcrName);

	void continueVCR(string vcrName);

	void gotoCamera(string cameraName);

	void hideShowObject(string objName);

	void hideShowObject(const vector<string>& objectNames);



	bool checkPf;
	bool checkPs;
	bool checkXf;
	bool checkDl;
public:
	afx_msg void OnMusicOnoff();
	afx_msg void OnUpdateMusicOnoff(CCmdUI *pCmdUI);
	afx_msg void OnPdsPlay();
	afx_msg void OnPdsStop();
	afx_msg void OnPdsContinue();
	afx_msg void OnJkqPlay();
	afx_msg void OnJkqStop();
	afx_msg void OnJkqContinue();
	afx_msg void OnVgviBgConfig();
	afx_msg void OnNdbDisconnect();
	afx_msg void OnScriptRunfile();
	afx_msg void OnScriptTestscript();
	afx_msg void OnScriptTestmenu();
	afx_msg void OnScriptConsole();
	afx_msg void OnPublishPackageExe();
	afx_msg void OnSceneReset();
	afx_msg void OnVectorShpUnload();
	afx_msg void Onterraintesting();
	afx_msg void OnUpdate33109(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSetTerrain(CCmdUI *pCmdUI);
	afx_msg void OnSetTerrain();
	afx_msg void OnLoadModterrain();
	afx_msg void OnModterrainReload();
	afx_msg void OnModterrainSave();
	afx_msg void OnUpdateModterrainLoad(CCmdUI *pCmdUI);
	afx_msg void OnModterrainLeveling();
	afx_msg void OnUpdateModterrainLeveling(CCmdUI *pCmdUI);
	afx_msg void OnUpdateModterrainReload(CCmdUI *pCmdUI);
	afx_msg void OnUpdateModterrainSave(CCmdUI *pCmdUI);
	afx_msg void OnVgscUserScriptConfig();
	afx_msg void OnTestUnloadmod();
	afx_msg void OnTanslateSelected();
	afx_msg void OnGisSun();

private:
	// AVI 文件导出相关
	AviExportDialog m_expDialog;

	void exportFrameBufferToPath(string filePath, int width, int height);
	void exportFrameBufferToAVI(int frameId);

	vgCam::CAviFile *paviFile;

	int m_frameBufferWidth;
	int m_frameBufferHeight;
	
	string m_aviCameraName;
	CString m_aviFilePath;
	int m_fileId;
	int m_fps;

	// 是否在录制AVI状态 0-正常渲染，1-导出一张截图，n-播放相机动画
	int m_nAviRecord;
	float m_totalFrame;

	// BMP 文件导出相关
	string m_bmpFilePath;
	int    m_bmpWidth;
	int	   m_bmpHeight;

public:
	afx_msg void OnExpAvi();
	afx_msg void OnExpBmp();

	afx_msg void OnVgshapeReadshpfile();
	afx_msg void OnVgshapeSelectshparea();
	afx_msg void OnCamReheight();
	afx_msg void OnVgshapeSaveasshape();
	afx_msg void OnTestModOpacity();
	afx_msg void OnVgshapeTranslatetoorigin();
	afx_msg void OnVgshapeAttachtoterrain();
	afx_msg void OnVgshapeSetrendererboxasfilter();
	afx_msg void OnAutobuild();
	afx_msg void OnVgshapeReadgridshpfile();

	afx_msg void OnVectorShpGreenRatio();
	afx_msg void OnUpdateVectorShpGreenRatio(CCmdUI *pCmdUI);
	afx_msg void OnVgtestSelectMode();
	afx_msg void OnUpdateVgtestSelectMode(CCmdUI *pCmdUI);
	afx_msg void OnUpdateVgshapeSelectshparea(CCmdUI *pCmdUI);
	afx_msg void OnAutobuildClone();
	afx_msg void OnEditSingleFaceRender();
	afx_msg void OnEditSingleFaceRenderSel();
	afx_msg void OnEditSingleFaceRenderAll();
	afx_msg void OnUpdateEditSingleFaceRenderSel(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditSingleFaceRenderAll(CCmdUI *pCmdUI);
	afx_msg void OnTriggerSetAs();
	afx_msg void OnVgshapeImporttext();
	afx_msg void OnVgshapeExportshapeinfo();
	afx_msg void OnVgshapeCaculateposition();
	afx_msg void OnVgshapeClearplan();
	afx_msg void OnVgshapeGenerateselected();
	afx_msg void OnVgshapeImportinfofromtxt();
	afx_msg void OnAutobuildingCloseinfofile();
	afx_msg void OnTriggerConfig();
	afx_msg void OnQueryplaninfoQueryplotratio();
	afx_msg void OnUpdateQueryplaninfoQueryplotratio(CCmdUI *pCmdUI);
	afx_msg void OnVgshapeTranslateall();
	afx_msg void OnVgplanAddground();
	afx_msg void OnVgplanAddsecne();
	afx_msg void OnVgshadowTurnonshadow();
	afx_msg void OnVgshadowSelectshadowcastobjects();
	afx_msg void OnVgplanSetparameter();
	afx_msg void OnVgshadowChange();
	afx_msg void OnVgshadowTurnoffshadow();
	afx_msg void OnVgshadowSolaranalysis();
	afx_msg void OnUpdateVgshadowSolaranalysis(CCmdUI *pCmdUI);
	afx_msg void OnUpdateVgshadowTurnonshadow(CCmdUI *pCmdUI);
	afx_msg void OnTestModUnopacity();
	afx_msg void OnTesttestSelectchangecolor();
	afx_msg void OnVgplanAddstreetline();
	afx_msg void OnPlanExportscene();
	afx_msg void OnVgplanGenerateplanmap();
	afx_msg void OnVgplanAddregion();
	afx_msg void OnVgplanAddnew();
	afx_msg void OnVgplanCgrid();
	afx_msg void OnVgplanCalgrid();
	afx_msg void OnVgplanGenplan();
	afx_msg void OnVgplanOutput();
};

#ifndef _DEBUG  // debug version in vgFrameWorkView.cpp
inline CvgFrameWorkDoc* CvgFrameWorkView::GetDocument() const
   { return reinterpret_cast<CvgFrameWorkDoc*>(m_pDocument); }
#endif


#pragma once

#include <vgSimplePlatformView.h>

// CUserPlatformView view

class CUserPlatformView : public CSimplePlatformView
{
	DECLARE_DYNCREATE(CUserPlatformView)

protected:
	CUserPlatformView();           // protected constructor used by dynamic creation
	virtual ~CUserPlatformView();


public:


	virtual void fireRenderStarted()
	{
		__super::fireRenderStarted();
	}
	// ÐèÒªÖØÐ´
	virtual void renderScene();

	virtual void fireRenderEnded()
	{
		__super::fireRenderEnded();
	}

private:

	bool importSingleVgi( const String&  filename );


public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTestImportvgm();
	afx_msg void OnTestImportvgi();
	afx_msg void OnTestImportvmd();
	afx_msg void OnTestDeleteselected();
	afx_msg void OnTestDumpinfo();
	afx_msg void OnTestSave();
	afx_msg void OnShadowTurnon();
	afx_msg void OnShadowSelectshadowobjects();
	afx_msg void OnShadowChangelights();
	afx_msg void OnShadowTurnoff();
	afx_msg void OnShadowSolaranalysis();
	afx_msg void OnUpdateShadowSolaranalysis(CCmdUI *pCmdUI);
	afx_msg void OnUpdateShadowTurnon(CCmdUI *pCmdUI);
	afx_msg void OnTerritoryOpenterrainfile();
	afx_msg void OnScriptLoadscriptdll();
	afx_msg void OnLogoEnablelogo();
	afx_msg void OnLogoDisablelogo();
	afx_msg void OnUpdateLogoEnablelogo(CCmdUI *pCmdUI);
	afx_msg void OnLogoUnloadlogodll();
	afx_msg void OnTerritoryLoadterraindll();
	afx_msg void OnUpdateTerritoryOpenterrainfile(CCmdUI *pCmdUI);
	afx_msg void OnTerritoryUnloadterrainfile();
};



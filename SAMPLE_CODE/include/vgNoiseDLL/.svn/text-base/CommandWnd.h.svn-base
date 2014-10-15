/*
*/
#pragma once

typedef std::map<UINT, UINT>				CommandToMessage;
typedef std::map<UINT, BOOL>				CommandCheckMessage;
typedef std::map<UINT, BOOL>				CommandEnableMessage;

extern CWnd *								s_CommandWnd ;
extern CommandToMessage						s_CommandToMessage ; 
extern CommandCheckMessage					s_CommandCheckMessage;
extern CommandEnableMessage					s_CommandEnableMessage;
extern CBCGPMenuBar*						s_pMenuBar;

// CCommandWnd 响应窗口事件
class CCommandWnd : public CWnd
{
	DECLARE_DYNAMIC(CCommandWnd)

public:
	CCommandWnd();
	virtual ~CCommandWnd();

protected:

	//afx_msg LRESULT OnNoiseImportGridData( WPARAM wParam, LPARAM lParam ) ;

	LRESULT CCommandWnd::OnBgNoiseAreaGrid( WPARAM wParam, LPARAM lParam );
	LRESULT CCommandWnd::OnBgNoiseAreaPoint( WPARAM wParam, LPARAM lParam );
	LRESULT CCommandWnd::OnBgNoiseRoadGrid( WPARAM wParam, LPARAM lParam );
	LRESULT CCommandWnd::OnBgNoiseRoadPoint( WPARAM wParam, LPARAM lParam );
	LRESULT CCommandWnd::OnBgNoiseLongPoint( WPARAM wParam, LPARAM lParam );

	LRESULT CCommandWnd::OnNoiseGridProperty( WPARAM wParam, LPARAM lParam );
	LRESULT CCommandWnd::OnNoiseGridAppearance( WPARAM wParam, LPARAM lParam );
	LRESULT CCommandWnd::OnNoiseGridCalculate( WPARAM wParam, LPARAM lParam );
	LRESULT CCommandWnd::OnNoiseGirdColor( WPARAM wParam, LPARAM lParam );
	LRESULT CCommandWnd::OnNoiseGridContourLevel( WPARAM wParam, LPARAM lParam );
	LRESULT CCommandWnd::OnNoiseGridDataSet( WPARAM wParam, LPARAM lParam );

	DECLARE_MESSAGE_MAP()
	LRESULT OnVgSceneBorder( WPARAM wParam, LPARAM lParam );
	LRESULT OnVgSceneBgsupport( WPARAM wParam, LPARAM lParam );
	LRESULT OnAnnoyStd( WPARAM wParam, LPARAM lParam );
	LRESULT OnAnnoyParameter( WPARAM wParam, LPARAM lParam );
	LRESULT OnAnnoyCompute( WPARAM wParam, LPARAM lParam );
	LRESULT OnAnnoyGridFace( WPARAM wParam, LPARAM lParam );
	LRESULT OnAnnoyTexture( WPARAM wParam, LPARAM lParam );
	LRESULT OnVgSceneDisable( WPARAM wParam, LPARAM lParam );
	LRESULT OnNoiseGridDataOutput( WPARAM wParam, LPARAM lParam );
	LRESULT OnNoiseMapVertical( WPARAM wParam, LPARAM lParam );
	LRESULT OnAnnoyFlag( WPARAM wParam, LPARAM lParam );
};



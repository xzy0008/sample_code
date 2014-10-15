// SolarAnalysis.cpp : implementation file
//

#include <vgStableHeaders.h>
#include "vgsolar/SolarAnalysis.h"


// CSolarAnalysis dialog

IMPLEMENT_DYNAMIC(CSolarAnalysis, CDialog)

CSolarAnalysis::CSolarAnalysis(vgSolar::DateTimeAndLocation* loc , 
							   CWnd* pParent /*=NULL*/)
: CDialog(CSolarAnalysis::IDD, pParent)
, _year( loc->getYear() )
, _month( loc->getMonth() )
, _day( loc->getDay() )
, _hour( loc->getHour() )
, _minute( loc->getMinute() )
, _lat( loc->getLatitude() )
{
	
}

CSolarAnalysis::~CSolarAnalysis()
{
}

void CSolarAnalysis::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Text(pDX, IDC_YEAR, _year );
	////DDV_MinMaxInt(pDX, _year, 0, 1000 );

	//DDX_Text(pDX, IDC_MONTH, _month );
	//DDV_MinMaxInt(pDX, _month, 1, 12 );

	//DDX_Text(pDX, IDC_DAY, _day );
	//DDV_MinMaxInt(pDX, _day, 1, 31 );

	//DDX_Text(pDX, IDC_HOUR, _hour );
	//DDV_MinMaxInt(pDX, _hour, 0, 23 );

	//DDX_Text(pDX, IDC_SECOND, _minute );
	//DDV_MinMaxInt(pDX, _minute, 0, 59 );

	DDX_Text(pDX, IDC_LATITUDE, _lat );
	DDV_MinMaxFloat(pDX, _lat, -90.0f, 90.0f );

	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_wndDateTimePicker);
	DDX_Control(pDX, IDC_DURATION, m_wndDuration);
	DDX_Control(pDX, IDC_DURATION2, m_wndDuration2);
}

void CSolarAnalysis::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateData( TRUE );

	//------------------------------------------
	// 查看时间是否越界
	//------------------------------------------
	COleDateTime t1 = m_wndDuration.GetDuration();
	COleDateTime t2 = m_wndDuration2.GetDuration();

	_beginhour = t1.GetHour() + t1.GetMinute() / 60.0;
	_endhour = t2.GetHour() + t2.GetMinute() / 60.0;

	if ( _beginhour  >= _endhour )
	{
		MessageBox( "开始结束时间设置错误");
		return;
	}


	CString dasf = m_wndDateTimePicker.ToString();


	COleDateTime dt = m_wndDateTimePicker.GetDate();
	CString m_strDateTime = dt.Format(_T("%#x %X"));


	_year = dt.GetYear();
	_month = dt.GetMonth();
	_day = dt.GetDay();

	_hour = dt.GetHour();
	_minute = dt.GetMinute();




	CDialog::OnOK();
}

BEGIN_MESSAGE_MAP(CSolarAnalysis, CDialog)
END_MESSAGE_MAP()

BOOL CSolarAnalysis::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	UpdateData();

	UINT stateFlags = 0;


	stateFlags |= CBCGPDateTimeCtrl::DTM_SPIN;
	stateFlags |= CBCGPDateTimeCtrl::DTM_DROPCALENDAR;
	//stateFlags |= CBCGPDateTimeCtrl::DTM_CHECKBOX;
	stateFlags |= (CBCGPDateTimeCtrl::DTM_DATE /*| CBCGPDateTimeCtrl::DTM_TIME*/);
	stateFlags |= CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE;


	const UINT stateMask = 
		CBCGPDateTimeCtrl::DTM_SPIN |
		CBCGPDateTimeCtrl::DTM_DROPCALENDAR | 
		CBCGPDateTimeCtrl::DTM_DATE |
		CBCGPDateTimeCtrl::DTM_TIME24H |
		CBCGPDateTimeCtrl::DTM_CHECKBOX |
		CBCGPDateTimeCtrl::DTM_TIME | 
		CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE;

	m_wndDateTimePicker.SetState (stateFlags, stateMask);
	m_wndDateTimePicker.SizeToContent();


	UINT showFlags = 0;

	//showFlags |= CBCGPDurationCtrl::DRTN_DAYS;
	showFlags |= CBCGPDurationCtrl::DRTN_HOURS_MINS;
	//showFlags |= CBCGPDurationCtrl::DRTN_SECONDS;
	showFlags |= CBCGPDurationCtrl::DRTN_SPIN;

	const UINT showMask = 
		CBCGPDurationCtrl::DRTN_DAYS | 
		CBCGPDurationCtrl::DRTN_HOURS_MINS | 
		CBCGPDurationCtrl::DRTN_SECONDS | 
		CBCGPDurationCtrl::DRTN_SPIN;

	m_wndDuration.SetState (showFlags, showMask);
	m_wndDuration2.SetState (showFlags, showMask);

	m_wndDuration.SetAutoResize();
	m_wndDuration2.SetAutoResize();

	COleDateTime nowloc( _year , _month , _day , _hour , _minute , 0 );
	m_wndDateTimePicker.SetDate( nowloc );
	m_wndDuration.SetDuration( COleDateTimeSpan(0 , 8 ,0 ,0 ) );
	m_wndDuration2.SetDuration( COleDateTimeSpan(0 , 17 ,0 ,0 ) );

	UpdateData (FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

// CSolarAnalysis message handlers

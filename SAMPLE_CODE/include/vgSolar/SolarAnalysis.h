


#ifndef __SOLARANALYSIS_H__
#define __SOLARANALYSIS_H__



#include <vgSolar/vgsoDefinition.h>
#include <vgKernel/vgkForward.h>

#include <bcgpdialog.h>
#include <BCGPDurationCtrl.h>
#include <BCGPDateTimeCtrl.h>


#ifdef VGSO_DLL
#include <vgSolarResource.h>
#else
#include <vgLibraryResource.h>
#endif


#include <vgSolar/vgsoDateTimeAndLocation.h>



#define CDialog CBCGPDialog
// CSolarAnalysis dialog

class   VGSO_EXPORT  CSolarAnalysis : public CDialog
{
	DECLARE_DYNAMIC(CSolarAnalysis)

public:
	CSolarAnalysis(vgSolar::DateTimeAndLocation* loc , 
		CWnd* pParent = NULL);   // standard constructor
	virtual ~CSolarAnalysis();

	// Dialog Data
	enum { IDD = IDD_SOLAR_ANALYSIS_DLG };

public:

	vgSolar::DateTimeAndLocation getTimeAndLoc()
	{
		vgSolar::DateTimeAndLocation ret;
		ret.setYear( _year );
		ret.setMonth( _month );
		ret.setDay( _day );
		ret.setHour( _hour );
		ret.setMinute( _minute );
		ret.setLatitude( _lat );

		return ret;
	}

	float getHourBegin()
	{
		return _beginhour;
	}

	float getHourEnd()
	{
		return _endhour;
	}

	CBCGPDateTimeCtrl	m_wndDateTimePicker;
	CBCGPDurationCtrl	m_wndDuration;
	CBCGPDurationCtrl	m_wndDuration2;

protected:
	virtual void OnOK();
	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	int _year;
	int _month;
	int _day;
	int _hour;
	int _minute;
	float _lat;

	float _beginhour;
	float _endhour;
};



#endif // end of __SOLARANALYSIS_H__




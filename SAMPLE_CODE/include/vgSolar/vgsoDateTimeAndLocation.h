


#ifndef __VGSODATETIMEANDLOCATION_H__
#define __VGSODATETIMEANDLOCATION_H__



#include <vgSolar/vgsoDefinition.h>
#include <vgKernel/vgkForward.h>


	
namespace vgSolar {

	/**
		@date 	2009/04/21  15:30	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class DateTimeAndLocation
	{
	public:
		DateTimeAndLocation()
		{
			_year = VGSO_CURRENTYEAR_DEFAULT;
			_month = VGSO_CURRENTMONTH_DEFAULT;
			_hour = VGSO_CURRENTHOUR_DEFAULT;
			_day = VGSO_CURRENTDAY_DEFAULT;
			_minute = VGSO_CURRENTMINUTE_DEFAULT;
			_lat = VGSO_CURRENTLATITUDE_DEFAULT;
		}
		~DateTimeAndLocation()
		{

		}

		const float getLatitude() const { return _lat; }
		const int getDay() const { return _day; }
		const int getHour() const { return _hour; }
		const int getMonth() const { return _month; }
		const int getMinute() const { return _minute; }
		const int getYear() const { return _year; }
		float getLatitude() { return _lat; }
		int getDay() { return _day; }
		int getHour() { return _hour; }
		int getMonth() { return _month; }
		int getMinute() { return _minute; }
		int getYear() { return _year; }
		void setDay( const int& val ) { _day = val; }
		void setHour( const int& val ) { _hour = val; }
		void setLatitude( const float& val ) { _lat = val; }
		void setMonth( const int& val ) { _month = val; }
		void setMinute( const int& val ) { _minute = val; }
		void setYear( const int& val ) { _year = val; }

		String getDateDescription() const
		{
			COleDateTime t( _year , _month , _day, _hour , _minute , 0 );

			CString m_strDateTime = t.Format(_T("%#x"));

			return m_strDateTime.GetBuffer(0);

			//			std::ostringstream o;
			//#if VGK_LANG_CHS
			//			o << _year << "年"
			//				<< _month << "月"
			//				<< _day << "日"
			//#else
			//
			//#endif
		}

		String getDescription() const
		{
			COleDateTime t( _year , _month , _day, _hour , _minute , 0 );

			CString m_strDateTime = t.Format(_T("%#x %X"));

			return m_strDateTime.GetBuffer(0);

//			std::ostringstream o;
//#if VGK_LANG_CHS
//			o << _year << "年"
//				<< _month << "月"
//				<< _day << "日"
//#else
//
//#endif
		}


	private:

		int _year;
		int _month;
		int _hour;
		int _day;
		int _minute;
		float _lat;
	};
	
	
}// end of namespace vgSolar
	


#endif // end of __VGSODATETIMEANDLOCATION_H__
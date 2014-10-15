


#ifndef __VGSOSOLARDIRECTIONCALC_H__
#define __VGSOSOLARDIRECTIONCALC_H__



#include <vgSolar/vgsoDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkVec3.h>
#include <vgSolar/vgsoDateTimeAndLocation.h>

	
namespace vgSolar {

	/**
		@date 	2009/04/21  14:00	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class VGSO_EXPORT SolarDirectionCalc
	{
		//成员函数
	public :
		SolarDirectionCalc( DateTimeAndLocation* time_loc );
		~SolarDirectionCalc();
	public:
		

		// 返回值是经过normailisze之后的Vec3
		// 当光线还没出来的时候，返回的是NULL
		// 注意，用户负责释放
		vgKernel::Vec3* getSolarDirection();


	private:

		void setDateTimeAndLocation( 
			const DateTimeAndLocation& time_loc )
		{
			setDate( time_loc.getYear() , time_loc.getMonth() , 
				time_loc.getDay() );
			setTime( time_loc.getHour() , time_loc.getMinute() );

			setLatitude( time_loc.getLatitude() );
		}


		void setDate(int yearpar,int monthpar,int daypar);
		void setTime(int hourpar,int minutepar);
		void setLatitude(float latpar);


		float GetHeightOfSun();

		int jiri(int year,int month,int day);
		float GetLatOfSun();



	private:

		int year,month,day,hour,minute;//根据这个数值可以算出太阳直射点的纬度LatOfSun
		float LatOfPos;//当前位置的纬度
		float LatOfSun;//太阳直射点的纬度
		float h;//任意时刻的太阳高度角，所求的太阳高度角，也就是仰角
		vgKernel::Vec3 vecofsun;//太阳角度换算成的三维矢量
	}; 
	
}// end of namespace vgSolar
	


#endif // end of __VGSOSOLARDIRECTIONCALC_H__
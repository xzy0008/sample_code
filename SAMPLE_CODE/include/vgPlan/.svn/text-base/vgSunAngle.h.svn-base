#ifndef _VGSUNANGLE_H_INCLUDED_
#define _VGSUNANGLE_H_INCLUDED_

#include <vgMod/vgdepDefinition.h>


namespace vgPlan
{

	class  VGDEP_EXPORT vgSunAngle
	{
		//成员函数
	public :
		vgSunAngle();
		virtual ~vgSunAngle();
	public:
		int year,month,day,hour,minute;//根据这个数值可以算出太阳直射点的纬度LatOfSun
		float LatOfPos;//当前位置的纬度
		float LatOfSun;//太阳直射点的纬度
		float h;//任意时刻的太阳高度角，所求的太阳高度角，也就是仰角
		Vec3 vecofsun;//太阳角度换算成的三维矢量
	public:
		int jiri(int year,int month,int day);
		void SetDate(int yearpar,int monthpar,int daypar);
		void SetTime(int hourpar,int minutepar);
		void SetLat(float latpar);
		float GetLatOfSun();
		float GetHeightOfSun();


	}; 
}


#endif
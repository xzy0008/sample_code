


#include <vgStableHeaders.h>
#include <vgSolar/vgsoSolarDirectionCalc.h>


namespace vgSolar {
	


	SolarDirectionCalc::SolarDirectionCalc( DateTimeAndLocation* time_loc)
	{
		assert( time_loc != NULL );
		setDateTimeAndLocation( *time_loc );
	}
	SolarDirectionCalc::~SolarDirectionCalc()
	{

	}
	void SolarDirectionCalc::setDate(int yearpar,int monthpar,int daypar)
	{
		year=yearpar;
		month=monthpar;
		day=daypar;
	}
	void SolarDirectionCalc::setTime(int hourpar,int minutepar)
	{
		hour=hourpar;
		minute=minutepar;
	}
	int SolarDirectionCalc::jiri(int year,int month,int day)
	{
		int leap;
		if ( (year%4)==0 &&(year%100!=0 )||(year%400==0) )
			leap=1;
		else 
			leap=0;
		int mm[12]={ 0,31,leap+59,leap+90,leap+120,leap+151,leap+181,leap+212,leap+243,leap+273,leap+304,leap+334};		
		return mm[month-1]+day;
	}

	float SolarDirectionCalc::GetLatOfSun()//计算太阳的赤纬,这就是太阳的直射纬度了啊,而且是角度数值
	{
		float t=jiri(year,month,day)-79.6764-0.2422*(year-1985)+floor((year-1985)/4.0);//积日都是针对春分而言，春分之前是负数
		float sita=2*3.14159265*t/365.2422;//先转化为弧度,365天对应2pi的话，那么计算出现在的积日对应的弧度了，其实春分对应的积日是0
		float delta=0.3723+23.2567*sin(sita)+0.1149*sin(2*sita)-0.1712*sin(3*sita)-0.758*cos(sita)+0.3656*cos(2*sita)+0.0201*cos(3*sita);		
		return delta;
	}
	void SolarDirectionCalc::setLatitude(float latpar)
	{
		LatOfPos=latpar;
	}
	float SolarDirectionCalc::GetHeightOfSun()//计算此日此时此地的太阳角度,要先执行SetDate,SetLat,SetTime
	{
		//cout<<"纬度"<<LatOfPos<<"的此日正午太阳最大角度是"<<90-(LatOfPos-GetLatOfSun())<<endl;//这个数值是个度数呢，是个化成了度为单位的小数

		float nowtime=hour+minute/60.0f;
		float timeangle=(nowtime-12)/12.0*3.14159265;//化为弧度的时角
		//cout<<"时角"<<timeangle<<endl;

		float LatOfSun=3.14159265*GetLatOfSun()/180.0;//赤纬角度换算成弧度啊，才好计算
		float RadLatOfPos=LatOfPos*3.14159265/180.0;//所在地的纬度
		//cout<<"sinh:"<<cos(RadLatOfPos)*cos(LatOfSun)*cos(timeangle)+sin(RadLatOfPos)*sin(LatOfSun)<<endl;
		float h=asin(cos(RadLatOfPos)*cos(LatOfSun)*cos(timeangle)+sin(RadLatOfPos)*sin(LatOfSun));//得到弧度
		if( h > 0.0f )
		{
			//cout<<"此日此时此地的太阳角度是"<<h*180/3.1415926<<endl;	
			//还需要做的是如何根据太阳的时间角以及仰角换算出对应的vec3向量！且按照z负为北的话呢
			float x,y,z;
			float aa=h;//还用弧度计算三角函数呢
			float t=timeangle;
			x=-cos(aa)*sin(t);
			y=sin(aa);
			z=cos(aa)*cos(t);
			//cout<<"此日此时此地指向太阳的矢量是"<<x<<" "<<y<<" "<<z<<endl;
			//接下来应该根据这个三维矢量设定太阳的光线角！然后开始渲染阴影！
			return h;
		}
		else
		{
			//cout<<"太阳还没出"<<endl;
			return h;
		}
	}
	//----------------------------------------------------------------
	vgKernel::Vec3* SolarDirectionCalc::getSolarDirection()
	{
		float hh = GetHeightOfSun();

		float nowtime= hour + minute/60.0f;
		float t=(nowtime-12.0f)/12.0f*3.14159265;//化为弧度的时角

		vgKernel::Vec3* sun = new vgKernel::Vec3;

		if( hh > 0.0f )//太阳没出的话按照-1计算！
		{
			sun->x=-cos(hh)*sin(t);
			sun->y=-sin(hh);
			sun->z=cos(hh)*cos(t);

			//sun.normalise();
			sun->normalise();

			return sun;
		}
		else
		{
			return NULL;
		}

	}
	//----------------------------------------------------------------

	
	

}// end of namespace vgSolar




#ifndef __VGEFFECTUTILITY_H__
#define __VGEFFECTUTILITY_H__

#include <vgGlobal/vgglDefinition.h>
#include <vgKernel/vgkForward.h>


namespace vgGlobal{

	/**
		@date    2009/10/21  14:08
		@author  zzy

		@brief   

		@see
	*/	

	class	VGGL_EXPORT EffectUtility
	{
	public:
		EffectUtility()	{}
		~EffectUtility() {}

	public:
		static bool    addFountain();           //添加喷泉
		static bool    addFire();               //添加火
		static bool    addSmoke();              //添加烟

		static bool    beginRain();             //开始降雨
		static bool    endRain();               //停止降雨
		static bool    beginSnow();             //开始降雪
		static bool    endSnow();               //停止降雪

		static bool    configDynbillboard();    //设置动态纹理
		static bool    generateDynbillboard();  //生成动态纹理

		static bool    configPlanting();        //设置植被参数
		//static bool    beginPlanting();         //开始植树
		//static bool    plantInLine();           //沿线植树
		//static bool    optimizePlant();       //优化植被

		static bool    setAsTrigger();          //设为触发器
		static bool    configTrigger();         //配置触发器
	};
}//namespace vgGlobal

#endif//__VGEDITUTILITY_H__
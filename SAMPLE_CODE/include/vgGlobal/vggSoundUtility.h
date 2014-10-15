


#ifndef __VGSOUNDUTILITY_H__
#define __VGSOUNDUTILITY_H__

#include <vgGlobal/vgglDefinition.h>
#include <vgKernel/vgkForward.h>


namespace vgGlobal{

	/**
		@date    2009/10/21  14:08
		@author  zzy

		@brief   

		@see
	*/	

	class	VGGL_EXPORT SoundUtility
	{
	public:
		SoundUtility()	{}
		~SoundUtility()	{}
	
	public: 
		static bool    addBackgroundSound();    //添加背景音效  
		static bool    addStereo();             //添加立体音效

	};
}//namespace vgGlobal

#endif//__VGEDITUTILITY_H__
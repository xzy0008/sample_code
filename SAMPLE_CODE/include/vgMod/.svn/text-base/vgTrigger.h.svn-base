

#ifndef __VGMTRIGGER_H__
#define __VGMTRIGGER_H__


namespace vgMod{

	using namespace vgCore;
	
	/**
		@action		creation
		@date 		2009/03/13  9:43	
		@author  	lss
	
		@brief 		触发器
	
		@see    
		*/
	class	 VGDEP_EXPORT Trigger
	{
	public:
		Trigger();
		~Trigger();

	public:
		virtual	bool	testTriggered(const vgKernel::Vec3& eyePos)	= 0;	//触发条件
		virtual	void	respondAfterTriggered()	= 0;	//触发响应

	};

	typedef		std::vector<Trigger*>	TriggerArray;
	typedef		std::vector<Trigger*>::iterator	TriggerArrayItr;
}//namespace vgMod

#endif//__VGMTRIGGER_H__
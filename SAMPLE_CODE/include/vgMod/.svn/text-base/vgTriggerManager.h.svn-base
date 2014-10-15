

#ifndef __VGMTRIGGERMANAGER_H__
#define __VGMTRIGGERMANAGER_H__

#include <vgCore/vgSingleton.h>

#include "vgMod/vgTrigger.h"
#include <vgMod/vgobjframenode.h>
#include <vgCam/vgcaCamManager.h>
#include <vgKernel/vgkRenderCommandManager.h>

namespace vgMod{

	using namespace vgCore;
	
	/**
		@action		creation
		@date 		2009/03/13  10:53	
		@author  	lss
	
		@brief 		触发器管理器
	
		@see    
		*/
	class	 VGDEP_EXPORT TriggerManager: public vgKernel::Singleton<TriggerManager>
	{
		friend class vgKernel::Singleton<TriggerManager>;

	public:
		TriggerManager();
		virtual ~TriggerManager();
	
	protected:
		virtual bool initialise();

		virtual bool shutdown()
		{
			return true;
		}


		//仅引用，不负责删除
	public:
		virtual void reset();

		void	addTrigger(vgKernel::Renderer*	pRenderer);

		void	deleteTrigger(vgKernel::Renderer*	pRenderer);

		void	testAnyTriggered(vgKernel::Vec3 eyePos);

		bool	hasTrigger();

	protected:
		TriggerArray	_triggers;

		vgKernel::RenderCommand* m_pTriggerRenderCmd;
		
	};


	class triggerRenderCommand : public vgKernel::RenderCommand
	{
	public:
		triggerRenderCommand() : vgKernel::RenderCommand(VG_RP_TRIGGER_RENDER) {}

		inline virtual bool render()
		{
			if ( TriggerManager::getSingleton().hasTrigger() )
			{
				TriggerManager::getSingleton().testAnyTriggered(
					vgCam::CamManager::getSingleton().getCurrentPosition());
			}

			return true;
		}
	};



}//namespace vgMod

#endif//__VGMTRIGGERMANAGER_H__
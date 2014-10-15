#pragma once

#include <vgkernel/vgkSingleton.h>
#include <vgTrigger/vgtrTrigger.h>
#include <vgKernel/vgkInputSystem.h>
#include <vgKernel/vgkRendererHolder.h>
#include <vgTrigger/vgtrDefinition.h>
//#include <vgEntry/vgEntryFactory.h>

namespace vgTrigger{

	/**
		@action		creation
		@date 		2009/09/18  10:53	
		@author  	ZhouSC
	
		@brief 		触发器管理器
	
		@see    
		*/
	class	VGTRI_EXPORT TriggerManager: 
		public vgKernel::Singleton<TriggerManager>, 
		vgKernel::RendererHolder,
		vgKernel::InputHandler
	{
		friend class vgKernel::Singleton<TriggerManager>;

	public:
		TriggerManager();
		virtual ~TriggerManager();
	
	protected:
		virtual bool initialise()
		{
			m_triggerEnable = true;

			return true;
		}
		virtual bool shutdown();

		vgKernel::RenderCommand *m_pTriggerRenderBegin;
		
	public:
		virtual bool onDeleteRenderer( vgKernel::Renderer* renderer );

		//仅引用，不负责删除
	public:
		Trigger*	addTrigger(vgKernel::Renderer*	pRenderer);

		void	checkOnEveryFrame();

		bool	hasTrigger();
	
		void    setAllTriggerEnable(bool enable) { m_triggerEnable = enable; }
		
		bool    getAllTriggerEnable() { return m_triggerEnable; }
		
		Trigger* getCurrentSelectedTrigger();
		
		Trigger *getTriggerByName(string name);
	
		TriggerArray* getTriggerArrayPtr() { return &m_triggerList; }
		
	public:
		// 继承自InputHandle的函数
		virtual void OnLButtonUp(UINT nFlags, CPoint position);
		virtual void OnLButtonDown(UINT nFlags, CPoint position);

	public:
		// vge 文件读写
		bool writeToVgFile(string savePath);
		bool readFromVgFile(string readPath);

	protected:
		TriggerArray	m_triggerList;
		bool m_triggerEnable;

	private:
		Trigger* testClick(CPoint position);

		CPoint m_downPosition;
	};
}
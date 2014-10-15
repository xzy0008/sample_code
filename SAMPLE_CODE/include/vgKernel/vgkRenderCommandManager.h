#pragma once

#include <vgKernel/vgkSingleton.h>
#include <vgKernel/vgkRenderCommand.h>

namespace vgKernel
{
	class VGK_EXPORT RenderCommandManager 
		: public Singleton<RenderCommandManager>
	{
		friend class vgKernel::Singleton<RenderCommandManager>;

	public :
		RenderCommandManager();

		virtual ~RenderCommandManager();

		void renderAll();

		bool registerRenderCommand(RenderCommand *pRenderCommand);

		bool removeRenderCommand(RenderCommand *pRenderCommand);

	protected:

		virtual bool initialise()
		{
			return true;
		}

		virtual bool shutdown()
		{
			return true;
		}

		RenderCommandList m_renderCommandList;
	};

	class VGK_EXPORT RenderCommandFacade
	{
	public:

		static inline void RenderAll()
		{
			RenderCommandManager::getSingleton().renderAll();
		}

		static bool AddCommand(RenderCommand *pCommand)
		{
			return RenderCommandManager::getSingleton().registerRenderCommand(pCommand);
		}
		
		static bool RemoveCommand(RenderCommand *pCommand)
		{
			return RenderCommandManager::getSingleton().removeRenderCommand(pCommand);
		}
	};
}
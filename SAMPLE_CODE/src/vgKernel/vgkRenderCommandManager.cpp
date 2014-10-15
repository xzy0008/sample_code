#include <vgStableHeaders.h>
#include <vgKernel/vgkSingletonLifeTimeDefine.h>
#include <vgKernel/vgkRenderCommandManager.h>

namespace vgKernel
{
	struct RenderCommandOper
	{
		inline void operator() (RenderCommand* p)
		{
			p->render();
		}
	};

	RenderCommandManager::RenderCommandManager()
		: Singleton<RenderCommandManager>(VGK_SINGLETON_LEFE_RENDERCOMMANDMGR)
	{

	}

	RenderCommandManager::~RenderCommandManager()
	{

	}

	void RenderCommandManager::renderAll()
	{
		static RenderCommandOper render;

		for_each(m_renderCommandList.begin(), 
			m_renderCommandList.end(),
			render);
	}

	bool RenderCommandManager::registerRenderCommand(RenderCommand *pRenderCommand)
	{
		RenderCommandList::iterator iter = m_renderCommandList.begin();
		RenderCommandList::iterator iter_end = m_renderCommandList.end();

		while (iter != iter_end)
		{
			if ((*iter)->getPriority() > pRenderCommand->getPriority())
			{
				m_renderCommandList.insert(iter, pRenderCommand);
				return true;
			}
			iter ++;
		}
		
		m_renderCommandList.push_back(pRenderCommand);
		return true;
	}

	bool RenderCommandManager::removeRenderCommand(RenderCommand *pRenderCommand)
	{
		RenderCommandList::iterator iter = m_renderCommandList.begin();
		RenderCommandList::iterator iter_end = m_renderCommandList.end();
		RenderCommandList::iterator result;

		if (
			(result = find(iter, iter_end, pRenderCommand)) != iter_end
			)
		{
			delete *result;
			m_renderCommandList.erase(result);

			return true;
		}
		
		return false;
	}
}
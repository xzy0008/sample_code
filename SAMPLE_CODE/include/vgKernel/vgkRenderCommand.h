#pragma once
#include <list>
#include <vgKernel/vgkRenderCommandPriority.h>

namespace vgKernel
{	
	class VGK_EXPORT RenderCommand
	{
	public:
		RenderCommand(int priority = 0) { m_priority = priority; }
		virtual ~RenderCommand() {}	

		inline virtual bool render() = 0;

		int		getPriority() { return m_priority; }
		void	setPriority(int newPriority) {m_priority = newPriority; }

	protected:
		int m_priority;
	};

	typedef std::list<RenderCommand*> RenderCommandList;
}

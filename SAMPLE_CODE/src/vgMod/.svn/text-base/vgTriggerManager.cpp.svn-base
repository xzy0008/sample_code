
#include <vgStableHeaders.h>

#include <vgMod/vgTriggerManager.h>
#include <vgMod/vgobjframenode.h>

namespace vgMod{

	
	//----------------------------------------------------------------
	TriggerManager::TriggerManager()
		:Singleton<TriggerManager>(VGK_SINGLETON_LEFE_TRIGGER)
	{
		m_pTriggerRenderCmd = new triggerRenderCommand();

		vgKernel::RenderCommandFacade::AddCommand(m_pTriggerRenderCmd);
	}
	
	//----------------------------------------------------------------
	TriggerManager::~TriggerManager()
	{
		vgKernel::RenderCommandFacade::RemoveCommand(m_pTriggerRenderCmd);
	}

	bool TriggerManager::initialise()
	{

		return true;
	}

	void TriggerManager::testAnyTriggered(vgKernel::Vec3 eyePos)
	{
		for (TriggerArrayItr itr = _triggers.begin();
			itr != _triggers.end();
			itr ++)
		{
			if( (*itr)->testTriggered(eyePos) )
			{
				(*itr)->respondAfterTriggered();
			}
		}
		

	}

	void TriggerManager::addTrigger( vgKernel::Renderer*	pRenderer )
	{
		vgMod::ObjectNode* pNode = dynamic_cast<vgMod::ObjectNode*>(pRenderer);
		if (!pNode)
		{
			return;
		}	
		pNode->setAsTrigger(true);
		
		Trigger* pTrigger = dynamic_cast<Trigger*>(pRenderer);
		if (!pTrigger)
		{
			return;
		}	


		TriggerArrayItr itrResult = find(_triggers.begin(), _triggers.end(), pTrigger);
		if (itrResult == _triggers.end())
		{
			_triggers.push_back(pTrigger);
		}
	}

	void TriggerManager::deleteTrigger( vgKernel::Renderer*	pRenderer )
	{
		Trigger* pTrigger = dynamic_cast<Trigger*>(pRenderer);
		if (!pTrigger)
		{
			return;
		}

		TriggerArrayItr itrResult = find(_triggers.begin(), _triggers.end(), pTrigger);
		if (itrResult != _triggers.end())
		{
			vgMod::ObjectNode* pNode = dynamic_cast<vgMod::ObjectNode*>(*itrResult);
			if (!pNode)
			{
				return;
			}		
			pNode->setAsTrigger(false);
			_triggers.erase(itrResult);
		}
	}

	bool TriggerManager::hasTrigger()
	{
		return !_triggers.empty();
	}

	void TriggerManager::reset()
	{
#if 0
		for (TriggerArrayItr itr = _triggers.begin();
			itr != _triggers.end();
			itr ++)
		{
			if( (*itr) != NULL)
			{
				delete (*itr);

				(*itr) = NULL;
			}
		}
#endif
		_triggers.clear();
	}
	//----------------------------------------------------------------
	
}//namespace vgMod
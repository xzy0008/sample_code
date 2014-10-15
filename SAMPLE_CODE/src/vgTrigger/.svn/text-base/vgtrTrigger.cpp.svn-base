
#include <vgStableHeaders.h>
#include <vgTrigger/vgtrTrigger.h>
#include <vgKernel/vgkRendererManager.h>
#include <vgKernel/vgkRendererObserver.h>

namespace vgTrigger{

	VGK_RENDERER_IMPLEMENT( Trigger, RENDERER_TYPE_TRIGGER )

	//----------------------------------------------------------------
	Trigger::Trigger(vgKernel::Renderer *pInnerRenderer) : vgKernel::Renderer(RENDERER_TYPE_TRIGGER)
	{	
		m_lastStateIsOut = true;
		m_enable = true;
		m_innerVisible = true;

		m_pRendererImpl = NULL;
		setInnerRenderer(pInnerRenderer);

		if (m_pRendererImpl != NULL)
		{
			m_triggerName = m_pRendererImpl->getName() + "_trigger";
			m_innerVisible = m_pRendererImpl->getVisible();
		}
	}
	
	//----------------------------------------------------------------
	Trigger::~Trigger()
	{
		TRACE("Delete Trigger %s \n", this->getName().c_str());

		if (m_pRendererImpl != NULL)
		{
			m_pRendererImpl->unregisterObserver(this);
			//m_pRendererImpl->setVisible(true);
			m_pRendererImpl->setSelectable(true);
		}
	}
	//----------------------------------------------------------------

	bool Trigger::setInnerRendererByName(string rendererName)
	{
		if (m_pRendererImpl != NULL)
		{
			m_pRendererImpl->unregisterObserver(this);
			// m_pRendererImpl->setVisible(true);
			m_pRendererImpl->setSelectable(true);
		}

		m_pRendererImpl = vgKernel::RendererManager::getSingleton().getRendererbyName(rendererName);

		if (m_pRendererImpl != NULL)
		{
			m_pRendererImpl->registerObserver(this);
			// m_pRendererImpl->setVisible(false);
			m_pRendererImpl->setSelectable(false);

			return true;
		}

		return false;
	}

	bool Trigger::setInnerRenderer(vgKernel::Renderer *pInnerRenderer)
	{
		//assert(pInnerRenderer != NULL);
		if (pInnerRenderer == NULL)
		{
			return false;
		}

		if (m_pRendererImpl != NULL)
		{
			m_pRendererImpl->unregisterObserver(this);
			// m_pRendererImpl->setVisible(true);
			m_pRendererImpl->setSelectable(true);
		}

		m_pRendererImpl = pInnerRenderer;
		m_pRendererImpl->registerObserver(this);
		// m_pRendererImpl->setVisible(false);
		m_pRendererImpl->setSelectable(false);

		m_innerVisible = false;
		
		return true;
	}
	
	bool Trigger::positionCheck(vgKernel::Vec3& position)
	{
		bool inObject = m_pRendererImpl->testPointInObject(position);

		if (m_lastStateIsOut)
		{
			if (inObject)
			{
				m_lastStateIsOut = false;
				this->fireOnEntrence();
			
				return true;
			}
		}
		else
		{
			if (! inObject)
			{
				m_lastStateIsOut = true;
				this->fireOnExit();
				
				return true;
			}
		}

		return false;
	}

	bool Trigger::onDelete()
	{
		m_pRendererImpl = NULL;

		vgKernel::RendererManager::getSingleton().deleteRenderer(this);

		return true;
	}

	bool Trigger::fireOnClicked()
	{
		// AfxMessageBox("Fire On Clicked \n");
		
		for (int i=0; i<m_eventArray.size(); i++)
		{
			m_eventArray[i]->doCommand(TRIGGER_EVENT_CLICK);
		}

		return true;
	}

	bool Trigger::fireOnEntrence()
	{
		// AfxMessageBox("Fire on Entrence ");

		for (int i=0; i<m_eventArray.size(); i++)
		{
			m_eventArray[i]->doCommand(TRIGGER_EVENT_ENTRENCE);
		}

		return true;
	}

	bool Trigger::fireOnExit()
	{
		// AfxMessageBox("Fire on Exit ");

		for (int i=0; i<m_eventArray.size(); i++)
		{
			m_eventArray[i]->doCommand(TRIGGER_EVENT_EXIT);
		}

		return true;
	}

	bool Trigger::regeditEvent(CommandPtr cmdPtr)
	{
		CommandPtrArray::iterator iter
			= find(m_eventArray.begin(), m_eventArray.end(), cmdPtr);

		if (iter == m_eventArray.end())
		{
			m_eventArray.push_back(cmdPtr);

			return true;
		}

		return false;
	}

	bool Trigger::unregeditEvent(CommandPtr cmdPtr)
	{
		CommandPtrArray::iterator iter
			= find(m_eventArray.begin(), m_eventArray.end(), cmdPtr);

		if (iter != m_eventArray.end())
		{
			m_eventArray.erase(iter);
			
			return true;
		}

		return false;
	}

	CommandPtr Trigger::getCommandByName(String name)
	{
		for (int i=0; i<m_eventArray.size(); i++)
		{
			if (m_eventArray[i]->getName() == name)
			{
				return m_eventArray[i];
			}
		}

		return CommandPtr();
	}

	bool Trigger::deleteCommandByName(String name)
	{
		CommandPtrArray::iterator iter = m_eventArray.begin();
		CommandPtrArray::iterator iter_end = m_eventArray.end();
	
		while (iter != iter_end)
		{
			if ((*iter)->getName() == name)
			{
				// iter = m_eventArray.erase(iter);
				return unregeditEvent(*iter);
			}
			else
			{
				iter ++;
			}
		}

		return false;
	}

	String* Trigger::getInnerNamePtr()
	{
		return m_pRendererImpl->getNamePtr();
	}
}

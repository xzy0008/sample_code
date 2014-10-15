#include <vgStableHeaders.h>
#include <vgKernel/vgkSingletonLifeTimeDefine.h>
#include <vgKernel/vgkPropertyManager.h>
#include <vgKernel/vgkProperty.h>

namespace vgKernel
{
	PropertyManager::PropertyManager() : vgKernel::Singleton<PropertyManager>(VGK_SINGLETON_LEFE_PROPERTYMGR)
	{

	}

	PropertyManager::~PropertyManager()
	{

	}

	bool PropertyManager::initialise()
	{
		return true;
	}

	bool PropertyManager::shutdown()
	{
		return true;
	}

	bool PropertyManager::addProperty(UnTypedPropertyPtr pProperty)
	{
		for (int i=0; i<m_propertyPtrVec.size(); i++)
		{
			if (m_propertyPtrVec[i]->getName() == pProperty->getName())
			{
				return false;
			}
		}

		m_propertyPtrVec.push_back(pProperty);

		return true;
	}

	bool PropertyManager::deleteProperty(string name)
	{
		UntypedPropertyPtrVec::iterator iter = m_propertyPtrVec.begin();
		UntypedPropertyPtrVec::iterator iter_end = m_propertyPtrVec.end();

		while (iter != iter_end)
		{
			if ((*iter)->getName() == name)
			{
				delete (*iter);
				m_propertyPtrVec.erase(iter);

				return true;
			}
			iter ++;
		}

		return false;
	}

    UnTypedPropertyPtr PropertyManager::getProperty(string name)
	{
		for (int i=0; i<m_propertyPtrVec.size(); i++)
		{
			if (m_propertyPtrVec[i]->getName() == name)
			{			
				return m_propertyPtrVec[i];;
			}
		}

		return NULL;
	}

	bool PropertyManager::isExistProperty(string name)
	{
		for (int i=0; i<m_propertyPtrVec.size(); i++)
		{
			if (m_propertyPtrVec[i]->getName() == name)
			{
				return true;
			}
		}

		return false;
	}

	bool PropertyManager::registerPropertyObserver(string propertyName, Observer* pObserver)
	{
		UnTypedPropertyPtr re = NULL;

		re = getProperty(propertyName);

		if (re != NULL)
		{
			re->registerObserver(pObserver);
			return true;
		}

		return false;
	}

	bool PropertyManager::removePropertyObserver(std::string propertyName, vgKernel::Observer *pObserver)
	{
		UnTypedPropertyPtr re = NULL;

		re = getProperty(propertyName);

		if (re != NULL)
		{
			re->removeObserver(pObserver);
			return true;	
		}

		return false;
	}
}
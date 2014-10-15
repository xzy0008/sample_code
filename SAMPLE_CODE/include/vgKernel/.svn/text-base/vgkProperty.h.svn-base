#pragma once 

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSharePtr.h>
#include <vgKernel/vgkObserver.h>
#include <string>

using std::string;

namespace vgKernel
{ 
	class VGK_EXPORT UnTypedProperty : public ObserverTarget
	{
	public:
		const static unsigned int PROPERTY_ON_CHANGE = 1;

	public:
		UnTypedProperty(string name) : m_name(name){}
		virtual ~UnTypedProperty() {} 

		string getName() { return m_name; }
		void   setName(string name) { m_name = name; }

	protected:
		string m_name;
	};

	template < class T >
	class Property 
		: public UnTypedProperty
	{
	public:
		Property(string name, T val) 
			:UnTypedProperty(name), m_value(val) {}
		
		Property(string name)
			:UnTypedProperty(name) {}

		virtual ~Property(){}

		T getValue() { return m_value; }

		void setValue(T val)
		{
			m_value = val;
			for (int i=0; i<m_observerVec.size(); i++)
			{
				m_observerVec[i]->
					onEvent(UnTypedProperty::PROPERTY_ON_CHANGE, &m_value);
			}
		}

		virtual bool registerObserver(Observer *pObserver)
		{
			bool re = __super::registerObserver(pObserver);
		
			if (re)
			{
				pObserver->onEvent(UnTypedProperty::PROPERTY_ON_CHANGE, &m_value);
			}

			return re;
		}

	private:
		T m_value;
	};

	typedef UnTypedProperty*				UnTypedPropertyPtr; 
	typedef vector<UnTypedPropertyPtr>		UntypedPropertyPtrVec;
}
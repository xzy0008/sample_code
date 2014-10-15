#pragma once

#include <vgKernel/vgkSingleton.h>
#include <vgKernel/vgkProperty.h>

namespace vgKernel
{
	class VGK_EXPORT PropertyManager 
		: public vgKernel::Singleton<PropertyManager>
	{
		friend class vgKernel::Singleton<PropertyManager>;
		 
	private:
		PropertyManager();
		virtual ~PropertyManager();

	public:
		// 增加删除某个全局属性
		bool addProperty(UnTypedPropertyPtr pProperty);
		bool deleteProperty(string name);
		
		// 检查是否存在某个属性
		bool isExistProperty(string name);

		// 得到某个全局属性的指针，可对其进行更改
		// 更改的结果会通知所有的Observer
		UnTypedPropertyPtr getProperty(string name);
		
		// 针对某个属性增加或删o除对其感兴趣的Observer
		bool registerPropertyObserver(string propertyName, Observer* pObserver);
		bool removePropertyObserver(string propertyName, Observer* pObserver);
		
	protected:
		bool initialise();
		bool shutdown();

	private:
		UntypedPropertyPtrVec m_propertyPtrVec;
	};
}
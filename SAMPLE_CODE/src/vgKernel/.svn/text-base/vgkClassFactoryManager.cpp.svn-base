


#include <vgStableHeaders.h>
#include <vgKernel/vgkClassFactory.h>
#include <vgKernel/vgkClassFactoryManager.h>


namespace vgKernel {
	
	
	
	
	//----------------------------------------------------------------
	ClassFactoryManager::ClassFactoryManager() 
		: Singleton<ClassFactoryManager>( VGK_SINGLETON_LEFE_CLASSFACTORYMGR )
	{
		VGK_TRACE(_T("ClassFactoryManager created."));
	}
	//----------------------------------------------------------------
	ClassFactoryManager::~ClassFactoryManager()
	{
		VGK_TRACE(_T("ClassFactoryManager destroyed."));
	}
	//----------------------------------------------------------------
	ClassFactory* ClassFactoryManager::getFactoryByClassName( 
		const String& classname )
	{
		RendererFactoryMap::iterator findres = 
			_factories.find( classname );

		if ( findres == _factories.end() )
		{
			return NULL;
		}

		return findres->second;
	}
	//----------------------------------------------------------------
	bool ClassFactoryManager::shutdown()
	{
		RendererFactoryMap::iterator iter = _factories.begin();
		RendererFactoryMap::iterator iter_end =_factories.end();
#if 0
		for ( ; iter != iter_end ; ++ iter )
		{
			delete iter->second;
		}
#endif
		_factories.clear();
		return true;
	}
	//----------------------------------------------------------------
	bool ClassFactoryManager::registerFactory( ClassFactory* fac )
	{
		if ( getFactoryByClassName( fac->getClassName() ) != NULL )
		{
			return false;
		}

		_factories.insert( std::make_pair( fac->getClassName() , fac ) );
		return true;
	}
	//----------------------------------------------------------------
	String ClassFactoryManager::getDetails()
	{
		std::ostringstream o;

		RendererFactoryMap::iterator iter = _factories.begin();
		RendererFactoryMap::iterator iter_end =_factories.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			o << "<" << iter->first << ", " << iter->second << ">\n";
		}

		return o.str();
	}
	//----------------------------------------------------------------



}// end of namespace vgKernel

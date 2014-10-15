


#ifndef __VGKSERIALIZERMANAGER_H__
#define __VGKSERIALIZERMANAGER_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSingleton.h>
#include <vgKernel/vgkSerializer.h>

	
namespace vgKernel {

	/**
		@date 	2009/05/11  20:49	
		@author  xy
	
		@brief 	
	
		@see    
	*/
	class SerializerManager : 
		public vgKernel::Singleton<SerializerManager>,
		public vgKernel::ObserverContainer
	{
	private:
		friend class vgKernel::Singleton<SerializerManager>;
	private:
		SerializerManager()
			: vgKernel::Singleton<SerializerManager>( VGK_SINGLETON_LEFE_SERIALIZERMGR )
		{
			_version = 0;
		}

	public:

		virtual ~SerializerManager()
		{

		}

	protected:

		virtual bool initialise()
		{

			return true;
		}
		virtual bool shutdown()
		{
			return true;
		}


	public:

		int getVersionNumber()
		{
			return _version;
		}
		
		//bool pushSerializer( Serializer* serial );

		// 注意,这里不负责释放
		void clearSerializers();

		bool readProject( const String& projpath , const String& projname );

		bool saveProject(  const String& projpath , const String& projname  );

	private:


		//SerializerPtrVector _serializers;

		int _version;

	};
	
	
	
}// end of namespace vgKernel
	


#endif // end of __VGKSERIALIZERMANAGER_H__
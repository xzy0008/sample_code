

#ifndef __VGKSINGLETON_H__
#define __VGKSINGLETON_H__


#include <vgKernel/vgkSharePtr.h>
#include <vgKernel/vgkSingletonLifeTimeDefine.h>
#include <vgThreads/ScopedLock.h>
#include <vgThreads/CriticalSection.h>
#include <vgKernel/vgkClassIdentify.h>

	
namespace vgKernel {


	class SingletonInstance;


	/**
		@date 	2007/12/23  18:28	
		@author  xy
	
		@brief 	控制所有singleton生命周期的类.
			本身为singleton.

		 Control all singletons' life time.
		 The bigger weight is, the longer time life is.
		 Itself is just a singleton pattern.
	*/
	class VGK_EXPORT SingletonManager
	{
		friend class SingletonInstance;

	public:

		static SingletonManager& getSingleton()
		{ 
			return *getSingletonPtr();
		}

		static SingletonManager* getSingletonPtr()
		{ 
			// Unique point of access 

			if (0 == _instance) 
			{
				// set locale here
				std::locale::global(std::locale(""));

				_instance = new SingletonManager();
				atexit(Destroy); // Register Destroy function 
			}

			return _instance;
		}

		void deleteSingletonInstance( SingletonInstance* need_to_delete );

	private:

		static void registerSingleton( int weight , SingletonInstance* singleton )
		{
			if ( _otherInstancesPtrMap == NULL )
			{
				_otherInstancesPtrMap = new SingletonInstanceMap;
			}

		#if _DEBUG
			typedef std::pair<SingletonInstanceMap::iterator, bool> InsertResult;
			InsertResult res = _otherInstancesPtrMap->insert( 
				std::make_pair( weight , singleton ) );

			if ( res.second == false )
			{
				assert(0 && "Singleton insert failed!The weight should be different!");
			}
			return;
		#else
			(*_otherInstancesPtrMap)[ weight ].bind( singleton );
		#endif
		}

		static void Destroy() 
		{ 
			// Destroy the only instance 
			if ( _instance != 0  ) 
			{
				deleteSingletonsByWeight();

				delete _instance;
				_instance = 0 ;
			}
		}

		// 定义在最下面
		static void deleteSingletonsByWeight();

		// Prevent clients from creating a new Singleton 
		SingletonManager(){} 

		// Prevent clients from deleting a Singleton 
		~SingletonManager(){} 

		// Prevent clients from copying a Singleton 
		SingletonManager( const SingletonManager&); 
		SingletonManager& operator = ( const SingletonManager& );

	private:

		// The one and only instance 
		static SingletonManager *_instance; 

		// int -->weight: more weight, more life time
		typedef std::map<int, SharePtr<SingletonInstance> > SingletonInstanceMap;
		static SingletonInstanceMap* _otherInstancesPtrMap;
	};
	
	/**
		subclass this to implement Singleton.
		Only doing this can insert into SingletonManager.
	*/
	class SingletonInstance /*: public ClassIdentify*/
	{
		friend class SingletonManager;
		friend class SharePtr<SingletonInstance>;

	protected:

		SingletonInstance( int weight )
		{
			SingletonManager::getSingleton().registerSingleton( weight , this );
			//std::cout << "SingletonInstance()" << std::endl;
		}
		virtual ~SingletonInstance()
		{
			//std::cout << "~SingletonInstance()" << std::endl;
		}

	protected:

		// 通知删除static 的instance
		virtual void notifyDeleteInstance() = 0;

		/**
		用于初始化操作.在new之后进行.
		*/
		virtual bool initialise() = 0; 

		/**
		用于删除操作,在delete之前进行. 
		*/
		virtual bool shutdown() = 0;

	};
	
	/**
		@date 	2007/12/22  19:06	
		@author  xy
	
		@brief 	

			The template Singleton implementation. Created by xy
			Attention:
			   1.The child class must declared as follows:
			   
					(take class AAA for example)

					// first, declare the life time.
					// more int is, more life time is.
					// second, use it.

					const int AAA_LIFT_TIME = 100;

					class AAA:public Singleton<AAA>
					{
						friend class Singleton<AAA>;
					private:
						AAA() : Singleton<AAA>( AAA_LIFT_TIME ) {}
						~AAA(){};

					public:
						//...
					};

					or use it this way to trace generate information:

						class ImageManager : public vgKernel::Singleton<ImageManager>
						{
							friend class vgKernel::Singleton<ImageManager>;
						private:
							ImageManager() 
								: Singleton<ImageManager>( VG_SINGLETON_LEFE_IMAGEMGR ) 
							{
								VG_TRACE(_T("ImageManager created."));
							}
							~ImageManager()
							{
								VG_TRACE(_T("ImageManager destroyed."));
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
							//...
						};

				2.MultiInheritance is forbided.

			Then use it freely:
			   for example:
				  TextureManager::getSingleton().getTexture( file ); 
	*/
	template < class T > 
	class Singleton : public SingletonInstance
	{
	protected:

		virtual void notifyDeleteInstance()
		{
			*_ppInstance = NULL;
		}

	public:

		static T* getSingletonPtr()
		{ 
			static T* pointer= NULL;

			if ( pointer == NULL )
			{
				// 08-12-4更改.由于static变量的初始化顺序不确定
				// 所以将其作为local变量.
				static vgThreads::CriticalSection _createSection;

				vgThreads::ScopedLock lock(_createSection);

				// 在加锁的情况下再次判断
				if ( pointer == NULL )
				{
					pointer= new T();
					pointer->_ppInstance = &pointer;

					bool init_result = pointer->initialise();

					//assert( init_result == true );

					if( init_result == false )
					{
						// 这里系统产生严重错误,需要退出
						//assert(0);
					}
				}
			}

			//assert( pointer != NULL );
			return pointer;
		}

		static T& getSingleton()
		{
			return *getSingletonPtr();
		}


	protected:

		Singleton(int weight)
			:SingletonInstance( weight ),
		_ppInstance( NULL ) {}

		virtual ~Singleton(){}

	private:


		T** _ppInstance;
	};

	
	
}// end of namespace vgKernel
	

#define VGK_SINGLETON_IN_DECLARE( classname ) \
	VGK_CLASS_IN_DECLARE( classname ) 



#endif // end of __VGKSINGLETON_H__
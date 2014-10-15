
#ifndef		SINGLETON_H_
#define		SINGLETON_H_



//////////////////////////////////////////////////////////////////////////
///The template Singleton implemention. Added by Leven,07-1-22
///Attention:
///   1.the child class must override 3 funcions,such as:
///			TextureManager* TextureManager::getSingletonPtr(void)
///			{
///				return ms_Singleton;
///			}
///			TextureManager& TextureManager::getSingleton(void)
///			{  
///				assert( ms_Singleton );  return ( *ms_Singleton );  
///			}
///   2.the child class must declare the deflaut static variable,such as :
///			template<> 
///			TextureManager* Singleton<TextureManager>::ms_pSingleton = 0;
///   3.the singleton class must create when the application init. It is
///          it's life time should be as long as the application.
///How to use:
///   for example:
///      ManagerSystem::TextureManager::getSingleton().getTexture( file );
//////////////////////////////////////////////////////////////////////////
///单件模式


template < class T > 
class  VGDEP_EXPORT Singleton
{
protected:
	static T* ms_pSingleton;

public:
	Singleton( void )
	{
		assert( !ms_pSingleton );
		ms_pSingleton = static_cast< T* >( this );//static_cast 强制转化
	}

	~Singleton( void )
	{  
		assert( ms_pSingleton );  
		//ms_pSingleton = static_cast< T* >( this );
		ms_pSingleton = 0; 
	}

	static T& getSingleton( void )
	{	assert( ms_pSingleton );  return ( *ms_pSingleton ); }

	static T* getSingletonPtr( void )
	{ return ms_pSingleton; }
};


#endif		
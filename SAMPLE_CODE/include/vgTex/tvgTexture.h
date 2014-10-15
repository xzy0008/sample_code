

#ifndef __TVGTEXTURE_H__
#define __TVGTEXTURE_H__

#include <vgCore/vgPrerequisites.h>
#include <vgCore/vgSharedPtr.h>
#include <vgTex/tvgString.h>
#include <vgThreads/CriticalSection.h>
#include <vgThreads/ScopedLock.h>

namespace vgCore {

	enum  TexturePixelFormat
	{
		TEXTURE_PIXFORMAT_UNKOWN = 0,
		TEXTURE_PIXFORMAT_RGB	,		// 注意此时R为低位.
		TEXTURE_PIXFORMAT_RGBA	,		// 注意此时A为最高位.
		TEXTURE_PIXFORMAT_DXT1	,
		TEXTURE_PIXFORMAT_DXT3	,
		TEXTURE_PIXFORMAT_DXT5	,
	};

	enum TextureFlag 
	{
		TEXTURE_FLAG_UNINITIALISED = 0,
		TEXTURE_FLAG_TEXTURE_2D = 1 << 1,
		TEXTURE_FLAG_COMPRESSED = 1 << 2,
	};

	/// this file include classes:
	class Texture;
	class TextureBuildOption;
	class TextureBuildOptionPtr;
	class TextureUtility;


	class TextureUtility
	{
	public:

		static const String getPixelFormatDescription( 
			const TexturePixelFormat& format );

		static const String getTexFlagDescription( const TextureFlag& flag );

	};


	class TextureBuildOption 
	{
	public:
		//// the unique name. If null , then auto generate names.
		//String  mUniqueName;

		// for pixel format.
		TexturePixelFormat  mTexPixelFormat;

		// for generating huge map flag 
		bool	mIfHasBorder;

		// for auto generating mipmap flag
		bool	mIfGenMipmap;

		// for loading all DDS mipmap flag 
		bool	mIfLoadMipmap;

		// for texture FilterAnisotropic
		bool	mIfTurnOnFilterAnisotropic;

		// for DDS only : select an exact mip to load , -1 means load all mipmaps.
		Integer	mMiplevel;


		TextureBuildOption()
		{
			this->setParametersDefault();
		}

		TextureBuildOption( 
			const String&  uniquename ,
			const TexturePixelFormat& format ,
			const bool&	 border , const bool& genMip ,
			const bool& loadMip , const uint& miplevel = -1 ,
			const bool& turnOnAnisotropic = true )
		{
			this->setParameters( uniquename , format , border ,
				genMip , loadMip , miplevel ,turnOnAnisotropic);
		}

		~TextureBuildOption()
		{

		}

		inline void setParameters( 
			const String&  uniquename ,
			const TexturePixelFormat& format ,
			const bool&	 border , const bool& genMip ,
			const bool& loadMip , const uint& miplevel ,
			const bool& turnOnAnisotropic )
		{
			//this->mUniqueName			= uniquename;
			this->mTexPixelFormat		= format;
			this->mIfHasBorder			= border;
			this->mIfGenMipmap			= genMip;
			this->mIfLoadMipmap			= loadMip;
			this->mMiplevel				= miplevel;
			this->mIfTurnOnFilterAnisotropic = turnOnAnisotropic;
		}

		//inline bool isDefaultOption() const
		//{
		//	return (*this) == DEFAULT_OPTION ;
		//}

		const String getDetails() const;

		bool operator == ( const TextureBuildOption& op2 ) const;

		bool operator != ( const TextureBuildOption& op2 ) const
		{
			return !( (*this) == op2 );
		}

	private:

		void setParametersDefault();

	};


	/**
		@date 	2007/05/14  15:21	
		@author  Leven
			
		@brief 	
			the pointer of TextureBuildOption.
			
		@see    
	*/
	class TextureBuildOptionPtr : public SharedPtr<TextureBuildOption>
	{
	public:
		TextureBuildOptionPtr() : SharedPtr<TextureBuildOption>() {}

		explicit TextureBuildOptionPtr(TextureBuildOption* rep)
			: SharedPtr<TextureBuildOption>(rep) {}

		TextureBuildOptionPtr(const TextureBuildOptionPtr& r)
			: SharedPtr<TextureBuildOption>(r) {} 

		static const TextureBuildOptionPtr  DEFAULT_OPTION;
		static const TextureBuildOptionPtr  DEFAULT_OPTION_RGB;
		static const TextureBuildOptionPtr  DEFAULT_DXT_OPTION;

		static const TextureBuildOptionPtr  DEFAULT_DXT_LEVEL0;
		static const TextureBuildOptionPtr  DEFAULT_DXT_LEVEL1;
		static const TextureBuildOptionPtr  DEFAULT_DXT_LEVEL2;
		static const TextureBuildOptionPtr  DEFAULT_DXT_LEVEL3;
		static const TextureBuildOptionPtr  DEFAULT_DXT_LEVEL4;
		static const TextureBuildOptionPtr  DEFAULT_DXT_LEVEL5;


		static const TextureBuildOptionPtr  DEFAULT_HUGE_MAP_DXT_OPTION;
	};


	/**
		@date 	2007/05/14  15:21	
		@author  Leven
			
		@brief 	纹理类，核心。
			
		@see    
	*/
	class Texture
	{
		friend class DdsImage;
		friend class NormalImage;
		friend class TextureBuilder;
		friend class TextureManager;
		friend class TexturePtr;

		///newadding...begin
//		friend class vgTextureLoadingQueue;
		
		///newadding...end

	public:
		
		static const uint	 DEFAULT_EMPTY_TEXTURE_ID;
		static const Integer DEFAULT_EMPTY_TEXTURE_WIDTH;
		static const Integer DEFAULT_EMPTY_TEXTURE_HEIGHT;

		static const uint	 DEFAULT_UNDEFINED_TEXTURE_ID;
		static const Integer DEFAULT_UNDEFINED_TEXTURE_WIDTH;
		static const Integer DEFAULT_UNDEFINED_TEXTURE_HEIGHT;

		/**
			TEXTURE_STATE_UNDEFINED	: 最初的状态.
			TEXTURE_STATE_UNBINDED : 由builder创建的没有和uniquename绑定的状态
			TEXTURE_STATE_LOADED : 完全加载,可以使用的状态.
			TEXTURE_STATE_UNLOADED : 卸载了纹理内存,但含有文件信息,可以加载的状态.
		*/
		enum TextureState
		{
			TEXTURE_STATE_EMPTY			= -1 ,
			TEXTURE_STATE_UNDEFINED		= 0 ,
			TEXTURE_STATE_UNBINDED ,
			TEXTURE_STATE_LOADED ,
			TEXTURE_STATE_UNLOADED 
		};

		Texture();

		/// used for empty texture only.
		Texture( TextureState empty );

		~Texture();

	public:

		void	release();

		inline void	useBind();

		inline bool isInitialised() ;

		inline bool isBinded() ;

		inline bool isEmptyTexture() ;

		inline bool isNotEmptyTexture() 
		{
			return !isEmptyTexture();
		}

		String getDetails() const;

	private:

		void  makeLoadedFromUnloaded( const uint& texid );

		void  makeUnloadedFromLoaded();


		void  makeUnbindedFromUndefined( const uint& texid , const String& filePath ,
			const Integer& width , const Integer& height , 
			const TexturePixelFormat& pixformat , const TextureFlag& flag ,
			const TextureBuildOptionPtr& optionPtr );


		void  makeLoadedFromUnbinded( const StringPtr& uniName );


		void  makeUnloadedFromUndefined(const StringPtr& uniName ,
			const String& filePath ,
			const Integer& width , const Integer& height , 
			const TexturePixelFormat& pixformat , const TextureFlag& flag ,
			const TextureBuildOptionPtr& optionPtr );

		void  deleteTexture();

		void  setParametersDefault();

		void setEmptyTextureParameters();


		// used for getDetails public function.
		static String getStateDescription( volatile const TextureState& state );


	public:


// 		inline const TextureState getTextureState() const
// 		{
// 			return this->mTexState;
// 		}

		StringPtr		getUniqueName()  
		{ 
			StringPtr pstr;

			vgThreads::ScopedLock locker(m_CriticalSect);
			pstr = this->mpUniqueName; 

			return pstr;
		}

		inline String		getFilePath()  
		{ 
			String str;
			vgThreads::ScopedLock locker(m_CriticalSect);
			str = this->mFilePath; 


			return str;
		}

		inline const Integer		getWidth() const 
		{ 
			return this->mWidth; 
		}

		inline const Integer		getHeight() const 
		{ 
			return this->mHeight; 
		}

		inline uint		getTextureID()  
		{ 
			uint tmp;
			vgThreads::ScopedLock locker(m_CriticalSect);
			tmp = this->mTextureID;

			return tmp;
		}

		inline const TextureFlag		getTexFlag() const 
		{ 
			return this->mTexFlag; 
		}

		inline const TexturePixelFormat		getTexPixelFormat() const 
		{ 
			return this->mTexPixelFormat; 
		}

	private:

		void		setUniqueName( const StringPtr& val ) 
		{ 
			this->mpUniqueName = val;
		}

		void		setUniqueName( String* const val ) 
		{ 
			assert( this->mpUniqueName.isEmpty() );

			this->mpUniqueName.setNull();
			this->mpUniqueName.bind( val );
		}


	private:
		
		StringPtr	mpUniqueName;
		String		mFilePath;
		Integer		mWidth;
		Integer		mHeight;

		volatile uint		mTextureID;

		TextureBuildOptionPtr mTexBuildOptionPtr;

		TexturePixelFormat mTexPixelFormat;

		TextureFlag		 mTexFlag;

		///newadding...begin
		volatile TextureState	mTexState;

		vgThreads::CriticalSection m_CriticalSect;
		
		void setTextureID(const uint& id )
		{
			vgThreads::ScopedLock locker(m_CriticalSect);
			this->mTextureID = id;

		}

	public:
		

		TextureState getTextureState()
		{
			TextureState tmp;
			vgThreads::ScopedLock locker(m_CriticalSect);
			tmp = this->mTexState;

			return tmp;
		}

		TextureState setTextureState( const TextureState& newstate)
		{
			vgThreads::ScopedLock locker(m_CriticalSect);
			this->mTexState = newstate;

		}
		///newadding...end
		
	
	};

	#include <vgTex/tvgTexture.inl>


	//------------------------------------------
	// Singlethread TexturePtr
	//------------------------------------------

//	/// the pointer of Texture.
//	class TexturePtr : public SharedPtr<Texture>
//	{
//	public:
//		TexturePtr() : SharedPtr<Texture>() {}
//		explicit TexturePtr(Texture* rep) : SharedPtr<Texture>(rep) {}
//		TexturePtr(const TexturePtr& r) : SharedPtr<Texture>(r) {} 
//		
//		inline bool isEmpty() const
//		{
//			if ( SharedPtr<Texture>::isNull() )
//			{
//				return true;
//			}
//			if ( SharedPtr<Texture>::operator ->()->isEmptyTexture() )
//			{
//				return true;
//			}
//			return false;
//		}
//
//		static const TexturePtr EmptyTexturePtr; 
//	};
//	

	//------------------------------------------
	// multithread TexturePtr
	//------------------------------------------
	class VGDEP_EXPORT TexturePtr 
	{
	public:

		vgThreads::CriticalSection mpCriticalSect;

		uint* pInviewCount;

		//void addInviewRef()
		//{
		//	vgThreads::ScopedLock locker(mpCriticalSect);
		//	assert(pInviewCount);
		//	++(*pInviewCount);

		//}

		//uint inviewCount()
		//{
		//	vgThreads::ScopedLock locker(mpCriticalSect);

		//	assert(pInviewCount);

		//	uint t = *pInviewCount;

		//	return t;
		//}

		//void releaseInviewRef();

		String getPtrDetails()
		{
			vgThreads::ScopedLock locker(mpCriticalSect);
			std::stringstream result;
			result << "TexturePtr Detail: ( " 
				<< "InviewCount = " <<  *pInviewCount
				<< " , UseCount = " << *pUseCount
				<< " , Rep = " << pRep->getDetails() << " )";


			return result.str();
		}

		///newadding...end

	protected:
		Texture* pRep;
		unsigned int* pUseCount;

	public:

		/// 注意!这个时候要马上bind,不然使用"->"和"*"符号会抛出错误.
		TexturePtr() 
		{
			vgThreads::ScopedLock locker(mpCriticalSect);
			pRep = NULL;
			pUseCount = NULL;
			pInviewCount = NULL;
		}


		explicit TexturePtr(Texture* rep) 
		{
			vgThreads::ScopedLock locker(mpCriticalSect);
			pRep = rep;
			pUseCount = new unsigned int(1);
			pInviewCount = new uint(0);
		}

		TexturePtr(const TexturePtr& r)
			: pRep(0), pUseCount(0) , pInviewCount(0)
		{
			vgThreads::ScopedLock locker(mpCriticalSect);
			pRep = NULL;
			pUseCount = NULL;

			pRep = r.pRep;
			pUseCount = r.pUseCount; 
			pInviewCount = r.pInviewCount;
			// Handle zero pointer gracefully to manage STL containers
			if(pUseCount)
			{
				++(*pUseCount); 
			}
		}

		~TexturePtr() 
		{
			vgThreads::ScopedLock locker(mpCriticalSect);
			bool destroyThis = false;

			if (pUseCount)
			{
				if (--(*pUseCount) == 0) 
				{
					destroyThis = true;
				}
			}

			if (destroyThis)
			{
				delete pRep;
				delete pUseCount;
			}
		}

		inline TexturePtr& operator = (const TexturePtr& r)
		{
			vgThreads::ScopedLock locker(mpCriticalSect);

			if (pRep == r.pRep)
			{
				return *this;
			}

			/*
			release();
			pRep = r.pRep;
			pUseCount = r.pUseCount;
			if (pUseCount)
			{
			++(*pUseCount);
			}

			return *this;
			*/

			// Swap current data into a local copy
			// this ensures we deal with rhs and this being dependent
			TexturePtr tmp(r);
			swap(tmp);

			return *this;
		}

		inline Texture& operator*() const 
		{ 
			vgThreads::ScopedLock locker(
				*const_cast<vgThreads::CriticalSection*>(&mpCriticalSect) );
			assert(pRep);
			Texture* tmp = pRep;

			return *tmp;
		}
		inline Texture* operator->() const 
		{ 
			vgThreads::ScopedLock locker(
				*const_cast<vgThreads::CriticalSection*>(&mpCriticalSect) );
			assert(pRep);
			Texture* tmp = pRep;

			return tmp;
		}

		///得到T*.
		//inline T* get() const { return pRep; }

		inline Texture* getPointer() const
		{
			vgThreads::ScopedLock locker(
				*const_cast<vgThreads::CriticalSection*>(&mpCriticalSect) );
			Texture* t= pRep;

			return t;
		}

		/// 将一个指针绑定.注意必须保证未初始化!
		/// 这是一个经常易犯的错误,要注意检查.
		inline void bind(Texture* rep)
		{
			vgThreads::ScopedLock locker(mpCriticalSect);

			assert(!pRep && !pUseCount);

			pUseCount = new unsigned int(1);
			pRep = rep;

		}

		inline bool isEmpty() const
		{
			vgThreads::ScopedLock locker(
				*const_cast<vgThreads::CriticalSection*>(&mpCriticalSect) );

			if ( (pRep == 0) )
			{
				return true;
			}
			if ( pRep->isEmptyTexture() )
			{
				return true;
			}

			return false;
		}


		inline unsigned int useCount() const
		{ 
			vgThreads::ScopedLock locker(
				*const_cast<vgThreads::CriticalSection*>(&mpCriticalSect) );
			assert(pUseCount); 
			uint tmp = *pUseCount;

			return tmp; 
		}

		/// 返回计数器的指针.
		inline unsigned int* useCountPointer() const
		{ 
			vgThreads::ScopedLock locker(
				*const_cast<vgThreads::CriticalSection*>(&mpCriticalSect) );
			unsigned int* tmp = pUseCount;

			return tmp;
		}

		inline bool isNull(void) const 
		{ 
			vgThreads::ScopedLock locker(
				*const_cast<vgThreads::CriticalSection*>(&mpCriticalSect) );
			const bool tmp = (pRep == 0);

			return tmp;
		}

		/// 设置为空.相当于boost::shared_ptr中的reset().
		inline void setNull(void) 
		{ 
			vgThreads::ScopedLock locker(mpCriticalSect);

			if (pRep)
			{
				// can't scope lock mutex before release incase deleted
				bool destroyThis = false;

				if (pUseCount)
				{
					if (--(*pUseCount) == 0) 
					{
						destroyThis = true;
					}
				}

				if (destroyThis)
				{
					delete pRep;
					delete pUseCount;
				}

				pRep = 0;
				pUseCount = 0;
			}
		}

		///newadding...begin
		//新加的!很诡异的函数!
		// 直接放弃指针.没办法,多线程用
		inline void unbind()
		{
			vgThreads::ScopedLock locker(mpCriticalSect);
			if (pRep)
			{
				// can't scope lock mutex before release incase deleted
				pRep = 0;
				pUseCount = 0;
			}
		}

	protected:

		

		//inline void destroy(void)
		//{
		//	delete pRep;
		//	delete pUseCount;
		//}

		inline void swap(TexturePtr &other) 
		{
			std::swap(pRep, other.pRep);
			std::swap(pUseCount, other.pUseCount);
			std::swap(pInviewCount , other.pInviewCount );
		}

	public:
		static const TexturePtr EmptyTexturePtr; 
	};






}// end of namespace 

#endif // end of __TVGTEXTURE_H__
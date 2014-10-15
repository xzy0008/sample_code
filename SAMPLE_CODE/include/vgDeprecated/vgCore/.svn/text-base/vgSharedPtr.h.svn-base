

#ifndef __VGSHAREDPTR_H__
#define __VGSHAREDPTR_H__

#include <vgThreads/CriticalSection.h>
#include <vgThreads/ScopedLock.h>


namespace vgCore {

	/**
	@date 	2007/03/01  12:15	
	@author  leven

	@brief 	boost::shared_ptr实现.注意,这里的实现并不是线程安全的,只是临时实现,
	若要较好的实现,要使用boost::shared_ptr.

	另外注意,使用了shared_ptr之后不要再对原实例化物体进行delete操作,否则引起内存
	指针指向未初始化地址错误.

	@see   ogre::shardPtr.boost::shared_ptr.
	*/

//#if VG_SINGLE_THREAD

	template<class T>
	class SharedPtr 
	{

	protected:
		T* pRep;
		unsigned int* pUseCount;

	public:

		/// 注意!这个时候要马上bind,不然使用"->"和"*"符号会抛出错误.
		SharedPtr() : pRep(0), pUseCount(0)
		{
		}

		template<class Y>
		explicit SharedPtr(Y* rep) : pRep(rep), pUseCount(new unsigned int(1))
		{

		}
		SharedPtr(const SharedPtr& r)
			: pRep(0), pUseCount(0)
		{
			pRep = r.pRep;
			pUseCount = r.pUseCount; 
			// Handle zero pointer gracefully to manage STL containers
			if(pUseCount)
			{
				++(*pUseCount); 
			}

		}

		virtual ~SharedPtr() 
		{
			release();
		}

		inline SharedPtr& operator = (const SharedPtr& r)
		{
			if (pRep == r.pRep)
				return *this;

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
			SharedPtr<T> tmp(r);
			swap(tmp);
			return *this;
		}

#if _MSC_VER > 1200	

		template< class Y >
		inline SharedPtr& operator = (const SharedPtr<Y>& r) 
		{
			/// 若相等,则返回(无变化)
			if (pRep == r.pRep)
				return *this;


			// Swap current data into a local copy
			// this ensures we deal with rhs and this being dependent
			SharedPtr<T> tmp(r);
			swap(tmp);
			return *this;
		}

		template< class Y>
		SharedPtr(const SharedPtr<Y>& r)
			: pRep(0), pUseCount(0)
		{
			pRep = r.getPointer();
			pUseCount = r.useCountPointer();
			// Handle zero pointer gracefully to manage STL containers
			if(pUseCount)
			{
				++(*pUseCount);
			}
		}

#endif

		inline T& operator*() const { assert(pRep); return *pRep; }
		inline T* operator->() const { assert(pRep); return pRep; }

		///得到T*.
		//inline T* get() const { return pRep; }
		inline T* getPointer() const { return pRep; }

		/// 将一个指针绑定.注意必须保证未初始化!
		/// 这是一个经常易犯的错误,要注意检查.
		inline void bind(T* rep)
		{
			assert(!pRep && !pUseCount);

			pUseCount = new unsigned int(1);
			pRep = rep;
		}

		inline bool unique() const
		{ 
			assert(pUseCount); 
			return *pUseCount == 1;
		}
		inline unsigned int useCount() const
		{ 
			assert(pUseCount); 
			return *pUseCount; 
		}

		/// 返回计数器的指针.
		inline unsigned int* useCountPointer() const
		{ 
			return pUseCount;
		}

		inline bool isNull(void) const 
		{ 
			return pRep == 0; 
		}

		/// 设置为空.相当于boost::shared_ptr中的reset().
		inline void setNull(void) 
		{ 
			if (pRep)
			{
				// can't scope lock mutex before release incase deleted
				release();
				pRep = 0;
				pUseCount = 0;
			}
		}

	protected:

		inline void release(void)
		{
			bool destroyThis = false;

			if (pUseCount)
			{
				if (--(*pUseCount) == 0) 
				{
					destroyThis = true;
				}
			}

			if (destroyThis)
				destroy();
		}

		inline void destroy(void)
		{
			delete pRep;
			delete pUseCount;
		}

		inline void swap(SharedPtr<T> &other) 
		{
			std::swap(pRep, other.pRep);
			std::swap(pUseCount, other.pUseCount);
		}


	};

	template<class T, class U> 
	inline bool operator == ( SharedPtr<T> const& a , SharedPtr<U> const& b)
	{
		return a.getPointer() == b.getPointer();
	}

	template<class T, class U> 
	inline bool operator != ( SharedPtr<T> const& a , SharedPtr<U> const& b)
	{
		return a.getPointer() != b.getPointer();
	}


}

#endif // end of __VGSHAREDPTR_H__
#ifndef __VGKSHAREPTR_H__
#define __VGKSHAREPTR_H__


namespace vgKernel {


	template<class T>
	class SharePtr 
	{

	protected:
		T* pRep;
		unsigned int* pUseCount;

	public:

		// 注意!这个时候要马上bind,不然使用"->"和"*"符号会抛出错误.
		SharePtr() : pRep(0), pUseCount(0)
		{
		}

		template<class Y>
		explicit SharePtr(Y* rep) : pRep(rep), pUseCount(new unsigned int(1))
		{

		}
		SharePtr(const SharePtr& r)
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

		~SharePtr() 
		{
			release();
		}

		inline SharePtr& operator = (const SharePtr& r)
		{
			if (pRep == r.pRep)
				return *this;


			SharePtr<T> tmp(r);
			swap(tmp);
			return *this;
		}

		template< class Y >
		inline SharePtr& operator = (const SharePtr<Y>& r) 
		{
			/// 若相等,则返回(无变化)
			if ( pRep == r.getPointer() )
				return *this;

			SharePtr<T> tmp(r);
			swap(tmp);
			return *this;
		}

		template< class Y>
		SharePtr(const SharePtr<Y>& r)
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

		inline T& operator*() const 
		{ 
#if _DEBUG
			if ( pRep == NULL )
			{
				assert(pRep);
			}
#endif
			return *pRep; 
		}
		inline T* operator->() const 
		{ 
			
#if _DEBUG
			if ( pRep == NULL )
			{
				assert(pRep);
			}
#endif
			
			return pRep; 
		
		}

		inline T* getPointer() const { return pRep; }

		// 将一个指针绑定.注意必须保证未初始化!
		// 这是一个经常易犯的错误,要注意检查.
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

		// 慎用！
		inline void addRef(void) 
		{ 
			if (pUseCount)
			{
				++*pUseCount;
			}
		}
		inline void releaseRef(void) 
		{ 
			if (pUseCount && *pUseCount>0)
			{
				--*pUseCount;
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

		inline void swap(SharePtr<T> &other) 
		{
			std::swap(pRep, other.pRep);
			std::swap(pUseCount, other.pUseCount);
		}
	};
	


	template<class T, class U> 
	inline bool operator == (SharePtr<T> const& a, SharePtr<U> const& b)
	{
		return a.getPointer() == b.getPointer();
	}

	template<class T, class U>
	inline bool operator != (SharePtr<T> const& a, SharePtr<U> const& b)
	{
		return a.getPointer() != b.getPointer();
	}

}// end of namespace vgKernel
	


#endif // end of __VGKSHAREPTR_H__
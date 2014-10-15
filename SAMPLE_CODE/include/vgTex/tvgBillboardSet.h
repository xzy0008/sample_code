

#ifndef __TVGBILLBOARDSET_H__
#define __TVGBILLBOARDSET_H__

#include <vgCore/vgPrerequisites.h>
#include <vgCore/vgSharedPtr.h>
#include <vgTex/tvgBillboard.h>

namespace vgCore {


	/**
		@date 	2007/04/29  9:30	
		@author  Leven
			
		@brief 	billboard的集合类,包含一类的billboard,方便查找操作.

		@note 单个操作billboard会带来诸多不便,比如在生成森林的时候.这里便是"群"的概念.
			
		@see    Billboard
	*/
	class BillboardSet
	{
	public:
		/**
			定义存储的数据类型.
		*/
		typedef map< StringPtr , BillboardPtr >  BillboardMap;


		BillboardSet()
		{
		}
		~BillboardSet()
		{
			
		}
	
	
		/**
			渲染billboard的列表.是个依次遍历的过程.
		*/
		void  drawList() const;


		/**
			根据id值移除billboard.
		*/
		bool  removeBillboardPtr( const StringPtr& uniname );

		/**
			根据id值移除billboard.
		*/
		bool  removeBillboardPtr( const String& uniname );

		/**
			添加billboard.
				
			@note	此操作适合手动操作单个billboard的时候.
				
			@param	pbbd billboard的指针.
			@param	replace 是否覆盖.当本集合中含有相同的billboard时所采取的操作方式.
				
			@returns	void 
		*/
		void addBillboardPtr( const BillboardPtr& pbbd , const bool& replace = true );

		/**
			添加billboard.
				
			@note	此函数会对提供的参数创建billboard,然后将其添加进自身.
				
			@param	uniname 唯一个id名字
			@param	texUniName 纹理的唯一名字.函数中会对TextureManager申请纹理.
			@param	pos 位置信息.
			@param	replace 是否覆盖.当本集合中含有相同的billboard时所采取的操作方式.
				
			@returns	void 
		*/
		void addBillboardPtr( const String& uniname , const String& texUniName ,
			const Vector3& pos = Vector3::ZERO ,
			const bool& replace = true );

		/**
			添加billboard.
				
			@note	此函数会对提供的参数创建billboard,然后将其添加进自身.
				
			@param	uniname 唯一个id.
			@param	ptex 纹理指针.
			@param	pos 位置信息.
			@param	replace 是否覆盖.当本集合中含有相同的billboard时所采取的操作方式.
				
			@returns	void 
		*/
		void addBillboardPtr( const String& uniname , const TexturePtr& ptex ,
			const Vector3& pos = Vector3::ZERO ,
			const bool& replace = true );

		/**
			清除所有的billboard.
		*/
		void clearAll() 
		{
			this->mBillboardMap.clear();
		}

		/**
			设置渲染方式.
				
			@note	此操作会对含有的billboard做一个set操作.
		*/
		void setListRenderType( 
			const Billboard::RenderTypes& type );

		inline void setListScale( const Real& scale )
		{
			assert( scale > 0 && scale < 10000000);

			BillboardMap::iterator iter_end = mBillboardMap.end();
			for ( BillboardMap::iterator iter = mBillboardMap.begin() ;
				iter != iter_end ;
				++ iter )
			{
				iter->second->setScale( scale );
			}
		}

		/**
			通过唯一的id值来获得想要的billboard.
			@note 这里是指针的形式.
		*/
		BillboardPtr getBillboardPtr( const StringPtr& pUniName );

		/**
			通过唯一的id值来获得想要的billboard.
		*/
		BillboardPtr getBillboardPtr( const String& uniName )
		{
			return this->getBillboardPtr( StringUtil::createStringPtr( uniName ) );
		}

		/**
			得到具体的信息.
		*/
		String  getDetails() const;

		friend istream& operator >> ( istream& in , BillboardSet& bbdset );

		friend ostream& operator << ( ostream& out , BillboardSet& bbdset );

	private:

		/// 存储成对的billboard序列.
		BillboardMap	mBillboardMap;
	
	};
	
	
	typedef SharedPtr<BillboardSet>  BillboardSetPtr;
	
}// end of namespace vgCore

#endif // end of __TVGBILLBOARDSET_H__
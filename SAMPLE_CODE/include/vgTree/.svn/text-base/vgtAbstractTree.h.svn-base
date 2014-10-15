


#ifndef __VGTABSTRACTTREE_H__
#define __VGTABSTRACTTREE_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkRenderer.h>
#include <vgKernel/vgkAbstractTree.h>


	
namespace vgTree {



	/**
		@date 	2008/08/05  21:06	
		@author  leven
	
		@brief 	任何继承AbstractTree的类都要负责以下的职责:
			1. 对输入的AbstractLeaf队列做裁剪,输出可视队列.
			2. 对输出的可视队列需要设置DistanceToViewer.
			如有必要,对可视队列做渲染先后顺序的排列.
			比如,视点近的位置先渲染,这样可以优先申请io请求.
	
		@see    
	*/

	enum	TREE_TYPE
	{
		TREE_LINEAR,
		TREE_BINARY,
		TREE_QUAD
	};

	class AbstractTree : public vgKernel::AbstractTree
	{
	public:
		AbstractTree()
		{
			
		}
		virtual ~AbstractTree()
		{
			
		}
	

	public:

		// 设置远处裁剪的参数
		// 当为负数时,表示disable了这个参数
		virtual void setDistanceCull( float distance_cull ) = 0;

		virtual float getDistanceCull() = 0;

		/**
			输入队列
		*/
		virtual void setRendererPackage( vgKernel::RendererPackage* package ) = 0;


		/**
			重新构造内部结构.
			比如,四叉树在第一次getVisibleSet的时候生成.
			移动物体后,需要重新生成,则使用此函数.
		*/
		virtual void invalidate() = 0;

		/**
			 注意,visible_set是输出队列
			 Tree在这里计算并生成.
			 这里为了防止不必要的拷贝.
		*/
		virtual void getVisibleSet( vgKernel::RendererPackage* visible_set ) = 0;


		/**
			渲染树结构，测试用
		*/
		virtual void renderTreeStruct(bool bDrawStruct = false)		= 0;
		
		/**
			切换遍历方式，树或是线性
		*/
		virtual void switchTreeStruct( )		= 0;
		virtual bool isUseTree(	)	= 0;
		virtual TREE_TYPE	getType()	= 0;

	};


	
	
}// end of namespace vgTree
	


#endif // end of __VGTABSTRACTTREE_H__



#ifndef __VGKABSTRACTTREE_H__
#define __VGKABSTRACTTREE_H__

#include <vgKernel/vgkForward.h>

	
namespace vgKernel {

	/**
		@date 	2009/06/03  10:46	
		@author  xy
	
		@brief 	
	
		@see    
	*/

	class AbstractTree
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

	};


	
}// end of namespace vgKernel
	


#endif // end of __VGKABSTRACTTREE_H__
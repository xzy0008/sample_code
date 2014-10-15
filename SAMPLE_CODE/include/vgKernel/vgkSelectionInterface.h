


#ifndef __VGKSELECTIONINTERFACE_H__
#define __VGKSELECTIONINTERFACE_H__

#include <vgKernel/vgkForward.h>

	
namespace vgKernel {

	/**
		@date 	2009/01/05  10:45	
		@author  xy
	
		@brief 	
	
		@see    
	*/
	class SelectionInterface
	{
	public:
		SelectionInterface()
		{
			_canBeSelected = true;
		}
		virtual ~SelectionInterface()
		{
			
		}
	
	public:

		virtual std::pair<bool, float> testIntersectWithTriangles( 
			const vgKernel::Ray& ray ) = 0;

		// 是否和线段相交.默认与包围盒进行相交测试
		virtual bool testIntersectWithTriangles( 
			const vgKernel::Segment3& segment ) = 0;

		virtual bool isSelectable()
		{
			return _canBeSelected;
		}

		virtual void setSelectable( bool canbeselect )
		{
			_canBeSelected = canbeselect;
		}


	private:
	
		bool _canBeSelected;
	
	};
	
	
}// end of namespace vgKernel
	


#endif // end of __VGKSELECTIONINTERFACE_H__
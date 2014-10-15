




#ifndef __VGUSPROPERTYITEM_H__
#define __VGUSPROPERTYITEM_H__

#include <vgKernel/vgkForward.h>

	
namespace vgUserInterface {

	/**
		@date 	2009/06/26  9:49	
		@author  xy
	
		@brief 	≥ÈœÛCBCGPProp
	
		@see    
	*/
	class PropertyItem
	{
	public:
		PropertyItem()
		{
			
		}
		~PropertyItem()
		{
			
		}

	public:

		virtual bool addSubItem( PropertyItem* item ) = 0;

	
	};
	
	
}// end of namespace vgUserInterface
	


#endif // end of __VGUSPROPERTYITEM_H__
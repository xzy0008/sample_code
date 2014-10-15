


#ifndef __VGKEDITABLEINTERFACE_H__
#define __VGKEDITABLEINTERFACE_H__

#include <vgKernel/vgkForward.h>

	
namespace vgKernel {

	class Polygon2D;

	/**
		@date 	2009/01/07  11:07	
		@author  xy
	
		@brief 	
	
		@see    
	*/
	class LevellingInterface
	{
	public:
		LevellingInterface()
		{
			
		}
		virtual ~LevellingInterface()
		{
			
		}
	
	
	public:


		virtual bool doLevelling( const Polygon2D& polygons , float level_height ) = 0;
		

	};
	
	
}// end of namespace vgKernel
	


#endif // end of __VGKEDITABLEINTERFACE_H__





#ifndef __VGSHEXTENDEDUTILITY_H__
#define __VGSHEXTENDEDUTILITY_H__



#include <vgShape/vgshDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgShape/vgshDefinition.h>


namespace vgShape{

	//using namespace vgXXX;
	
	/**
		@action		creation
		@date 		2009/03/31  9:13	
		@author  	lss
	
		@brief 	
	
		@see    
		*/
	class	 VGSH_EXPORT ExtendedUtility
	{
	public:
		ExtendedUtility();
		~ExtendedUtility();

		static	void	translateAllShape(const double& offsetX, const double& offsetY,
			const double& offsetZ);
		static	void	exportAttributeToDatabase();
	};
}//namespace vgShape

#endif//__VGSHEXTENDEDUTILITY_H__
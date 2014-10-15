#pragma once

#include <vgGis/vggisDefinition.h>
#include <vgKernel/vgkForward.h>


namespace vgGIS3D{

	//using namespace vgXXX;
	
	/**
		@action		creation
		@date 		2009/03/31  9:13	
		@author  	lss
	
		@brief 	
	
		@see    
		*/
	class	 VGG_EXPORT ExtendedUtility
	{
	public:
		ExtendedUtility();
		~ExtendedUtility();

		static	void	translateAllShape(const double& offsetX, const double& offsetY,
			const double& offsetZ);
		static	void	exportAttributeToDatabase();
	};
}//namespace  

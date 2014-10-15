


#ifndef __VGENTRYREG_H__
#define __VGENTRYREG_H__

#include <vgKernel/vgkForward.h>

	#include <vgUIController/vgRendererToEntryRegister.h>


namespace vgGlobal {

	/**
		@date 	2009/07/22  14:24	
		@author  xy
	
		@brief 	
	
		@see    
	*/

	class EntriesReg: public vgUI::RendererToEntryRegister
	{
	public:
		EntriesReg()
		{

		}
		virtual ~EntriesReg()
		{

		}


	public:

		virtual vgKernel::AbstractEntry* rendererToEntry( vgKernel::Renderer* renderer );

	};
	
	
}// end of namespace vgGlobal
	


#endif // end of __VGENTRYREG_H__
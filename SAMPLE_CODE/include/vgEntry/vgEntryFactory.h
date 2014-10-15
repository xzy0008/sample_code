


#ifndef __VGENTRYFACTORY_H__
#define __VGENTRYFACTORY_H__

#include <vgKernel/vgkForward.h>
#include <vgEntry/vgBaseEntry.h>


#include <vgUIController/vgRendererToEntryRegister.h>

	
class  VGUI_EXPORT vgEntryFactory
{
private:
	vgEntryFactory()
	{
		
	}
	~vgEntryFactory()
	{
		
	}


public:

	//------------------------------------------
	// 这里写转换信息
	// 由renderer到vgbaseentry的转换
	//------------------------------------------

	static vgBaseEntry* createEntryFromRenderer( vgKernel::Renderer* renderer );


	static bool registerRendererToEntry( 
		vgUI::RendererToEntryRegister* reg );

private:

	static vgUI::RendererToEntryRegisterPtrVec _regs;
};

#endif // end of __VGENTRYFACTORY_H__
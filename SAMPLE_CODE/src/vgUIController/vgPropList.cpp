
#include <vgStableHeaders.h>
#include "vgUIcontroller/vgPropList.h"
#include <vgKernel/vgkInputSystem.h>
#include <vgKernel/vgkSelectManager.h>

BOOL PropList::EndEditItem(BOOL bUpdateData)
{

	m_closeCnt --;
	if (m_closeCnt != 1)
	{
		// TRACE("Open Input System \n");
		//vgKernel::InputSystem::getSingleton().SetEnable(true);
	}

	return CBCGPPropList::EndEditItem(bUpdateData);
}

BOOL PropList::EditItem(CBCGPProp*pProp,LPPOINT lptClick)
{
	m_closeCnt = 2;

	TRACE("Close Input System \n");
	//vgKernel::InputSystem::getSingleton().SetEnable(false);
	return CBCGPPropList::EditItem(pProp, lptClick);
}

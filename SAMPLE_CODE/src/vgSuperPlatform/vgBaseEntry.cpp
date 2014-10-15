



#include <vgStableHeaders.h>
#include "vgBaseEntry.h"

#include "vgUIController.h"



bool vgBaseEntry::onDelete()
{
	vgUIController::GetInstance()->DeleteNode( this , true );
	return true;
}



#include <vgStableHeaders.h>


#include <vgUIController/vgUIController.h>


using namespace vgUI;

void	UIController_reset()
{
	UIController::getSingleton().reset();
}

void	UIController_initUIControl()
{
	UIController::getSingleton().initUIControl();
}




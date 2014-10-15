
#include <vgStableHeaders.h>

#include <vgUIControllerDLL/vgUIControllerPlugin.h>

#include <vgUIController/vgUIController.h>


namespace	vgUI
{
	void UIControllerPlugin::render()
	{
		//vgGIS3D::GisManager::getSingleton().renderGisElements();
	}

	String UIControllerPlugin::getName()
	{
		return VGUI_DLL_NAME;	
	}

	bool UIControllerPlugin::uninitInOpenGL()
	{
		vgUI::UIController::getSingleton().unload();

		return true;
	}
}



#include <vgStableHeaders.h>
#include <vgUserInterface/vgusGuiManager.h>
#include <vgUserInterface/vgusAbstractGuiFactory.h>
#include <vgUserInterface/vgusTreePanel.h>


namespace vgUserInterface {
	
	
	
	

	GuiManager::GuiManager() : Singleton<GuiManager>( VGK_SIGNLETON_LEFE_GUIMGR )
	{
		
		_treePanel = NULL;
		_absGuiFac = NULL;
		VGK_TRACE(_T("GuiManager created."));
	}

	bool GuiManager::shutdown()
	{
		if ( _absGuiFac != NULL )
		{
			delete _absGuiFac;
			_absGuiFac = NULL;
		}


		if ( _treePanel != NULL )
		{
			delete _treePanel;
			_treePanel = NULL;
		}

		return true;
	}
}// end of namespace vgUserInterface

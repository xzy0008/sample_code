


#include <vgStableHeaders.h>
#include <vgTrigger/vgtrTriggerPlugin.h>
#include <vgTrigger/vgtrTriggerManager.h>
#include <vgTrigger/vgTriggerEntry.h>
//#include <vgPlan/vgPlanbox.h>

namespace vgTrigger {



	bool TriggerPlugin::initInOpenGL()
	{
		HWND hWND = AfxGetApp()->GetMainWnd()->GetActiveWindow()->GetSafeHwnd();
		HDC hDC = ::GetDC(hWND);

		//FontManager::getSingleton().initialiseFonts(hDC);
		return true;
	}

	void TriggerPlugin::render()
	{
	}

	vgKernel::AbstractEntry* TriggerPlugin::rendererToEntry( vgKernel::Renderer* renderer )
	{
		vgKernel::RendererType type = 
			renderer->getType();

		vgBaseEntry* ret = NULL;

		switch( type )
		{
			// SoundManager
		case vgTrigger::RENDERER_TYPE_TRIGGER :
			ret = new vgTriggerEntry( (vgTrigger::Trigger*)renderer );	
			break;

		default:
			break;
		}

		return ret;
	}

	bool TriggerPlugin::uninitInOpenGL()
	{
		//FontManager::getSingleton().uninitBeforeOpenGLDestroy();
		return true;
	}

	void TriggerPlugin::reset()
	{
		//FontManager::getSingleton().reset();
		return;
	}

	void TriggerPlugin::readProject( const String& projpath , const String& projname )
	{
	}

	void TriggerPlugin::saveProject( const String& projpath , const String& projname )
	{
	}

}// end of namespace vgTrigger

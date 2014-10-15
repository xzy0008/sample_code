#include <vgstableheaders.h>
#include <vgPlandll/vgpPlanPlugin.h>
#include <vgPlan/vgPlanmanager.h>
#include <vgPlan/vgBlockEntry.h>
#include <vgPlan/vgPlanbox.h>

namespace vgPlan
{
	void PlanPlugin::render()
	{
		vgPlanManager::getSingleton().render();
	}


	vgKernel::AbstractEntry* PlanPlugin::rendererToEntry( vgKernel::Renderer* renderer )
	{
		vgKernel::RendererType type = 
			renderer->getType();

		vgBaseEntry* ret = NULL;

		switch( type )
		{
			// SoundManager
		case vgPlan::RENDERER_TYPE_PLANBLOCK :
			ret = new vgBlockEntry( (vgPlan::vgPlanbox*)renderer );
			break;

		default:
			break;
		}

		return ret;
	}
}
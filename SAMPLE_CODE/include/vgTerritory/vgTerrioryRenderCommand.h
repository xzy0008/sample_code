#include <vgKernel/vgkRenderCommand.h>
#include <vgTerritory/vgtDefinition.h>
#include <vgTerritory/vgtTerrainManager.h>

namespace vgTerritory
{
	class VGT_EXPORT vgTerrainRenderCommand : public vgKernel::RenderCommand
	{
	public:

		vgTerrainRenderCommand() : vgKernel::RenderCommand(VG_RP_TERRAIN){}
		
		inline virtual bool render()
		{
			TerrainManager::getSingleton().render();
			
			return true;
		}
	};
}

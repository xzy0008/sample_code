


#include <vgStableHeaders.h>
#include <vgGlobal/vgEntryReg.h>

#include <vgGlobal/vgObjectEntry.h>
#include <vgGlobal/vgGPUSpecialEntry.h>
#include <vgGlobal/vgparticleentry.h>
#include <vgGlobal/vgMovingEntry.h>
#include <vgGlobal/vgBillboardEntry.h>
#include <vgGlobal/vgDynamicBillboardEntry.h>
#include <vgGlobal/vgMs3dEntry.h>
#include <vgGlobal/GisMatchEntry.h>


namespace vgGlobal {
	
	
	

	vgKernel::AbstractEntry* EntriesReg::rendererToEntry( vgKernel::Renderer* renderer )
	{

		vgKernel::RendererType type = 
			renderer->getType();

		vgBaseEntry* ret = NULL;

		vgMod::ObjFrameNode* pObjFrameNode = NULL;

		switch( type )
		{
		case vgMod::RENDERER_TYPE_MODOJBECT:
			pObjFrameNode = 
				dynamic_cast<vgMod::ObjFrameNode*>(renderer);
			//assert( pObjNode != NULL );
			if( pObjFrameNode && pObjFrameNode->hasKeyFrame() )
			{
				ret = new vgMovingEntry<vgMod::ObjFrameNode>( pObjFrameNode );
			}
			else
			{
				vgMod::ObjectNode* pObjNode = dynamic_cast<vgMod::ObjectNode*>(renderer);

				ret = new vgMod::vgObjectEntry( pObjNode );
			}
			break;


			// MovingManager
		case vgMs3d::RENDERER_TYPE_MS3D:
			ret = new vgMs3dEntry((vgMs3d::CMs3d*) renderer );
			break;

		case RENDERER_TYPE_GISMATCH://  [9/23/2008 YX]
			ret = new vgCore::vgGisMatchEntry( (vgMod::GisRoadMatch*) renderer );
			break;

		case vgMod::RENDERER_TYPE_BILLBOARD:
			ret = new vgMod::vgBillboardEntry((vgMod::BillboardNode*) renderer);
			break;

		case vgMod::RENDERER_TYPE_DYNAMICBILLBOARD:
			ret = new vgMod::vgDynamicBillboardEntry((vgMod::DynamicBillboardNode*) renderer);
			break;

		case vgMod::RENDERER_TYPE_PARTICLE:
			ret = new vgMod::vgParticleEntry( (vgMod::vgParticle*)renderer );
			break;

		case vgMod::RENDERER_TYPE_GPUSPECIAL_WARTER:
			ret = new vgCore::vgGPUSpecialEntry<vgMod::WaterNode>( (vgMod::WaterNode*)renderer );
			break;
		case vgMod::RENDERER_TYPE_GPUSPECIAL_SKYNODE:
			ret = new vgCore::vgGPUSpecialEntry<vgMod::SkyboxNode>( (vgMod::SkyboxNode*)renderer );
			break;
		case vgMod::RENDERER_TYPE_GPUSPECIAL_MIRROR:
			ret = new vgCore::vgGPUSpecialEntry<vgMod::MirrorNode>( (vgMod::MirrorNode*)renderer );
			break;
		case vgMod::RENDERER_TYPE_GPUSPECIAL_METAL:
			ret = new vgCore::vgGPUSpecialEntry<vgMod::MetalNode>( (vgMod::MetalNode*)renderer );
			break;
		case vgMod::RENDERER_TYPE_GPUSPECIAL_FLOOR:
			ret = new vgCore::vgGPUSpecialEntry<vgMod::BrightfloorNode>( (vgMod::BrightfloorNode*)renderer );
			break;
		case vgMod::RENDERER_TYPE_GPUSPECIAL_AVI:
			ret = new vgCore::vgGPUSpecialEntry<vgMod::AviNode>( (vgMod::AviNode*)renderer );
			break;
		case vgMod::RENDERER_TYPE_GPUSPECIAL_GLASS:
			ret = new vgCore::vgGPUSpecialEntry<vgMod::GlassNode>( (vgMod::GlassNode*)renderer );
			break;
		}

		return ret;
	}

}// end of namespace vgGlobal

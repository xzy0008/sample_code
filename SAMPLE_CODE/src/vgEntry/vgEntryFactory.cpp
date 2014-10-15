


#include <vgStableHeaders.h>
#include <vgEntry/vgEntryFactory.h>



#include <vgMesh/vgmMeshItem.h>
#include <vgEntry/vgMeshEntry.h>

//#include "vgObjectEntry.h"
#include <vgEntry/vgViewCamEntry.h>
#include <vgCam/vgcaViewCam.h>
//#include "vgparticleentry.h"
//#include "vgGPUSpecialEntry.h"
//#include "vgSound/vgSound3D.h"
//#include <vgEntry/vgSound3DEntry.h>
//#include "vgMs3dEntry.h"
//#include "vgMovingEntry.h"
#include <vgEntry/vgCameraRecordEntry.h>
//#include "vgBillboardEntry.h"

//#include "GisMatchEntry.h"
//#include "vgVecStringEntry.h"

//#include "vgVectorLayerEntry.h"
//#include "vgVectorGeometryEntry.h"

//#include "vgMod/vgobjframenode.h"

//#include <vgEntry/vgShapeLayerEntryEx.h>
//#include <vgAutoBuild/vgAutoBuildNode.h>
//#include "vgAutoBuildEntry.h"


#include <vgKernel/vgkPluginManager.h>
#include <vgTrigger/vgTriggerEntry.h>
//#include <vgGIS3D/vgPipeLineEntry.h>



vgUI::RendererToEntryRegisterPtrVec vgEntryFactory::_regs;





bool vgEntryFactory::registerRendererToEntry( vgUI::RendererToEntryRegister* reg )
{
	using namespace vgUI;

	RendererToEntryRegisterPtrVec::iterator iter = _regs.begin();
	RendererToEntryRegisterPtrVec::iterator iter_end = _regs.end();

	for ( ; iter != iter_end ; ++ iter )
	{
		if ( *iter == reg )
		{
			return false;
		}
	}

	_regs.push_back( reg );

	return true;
}

#if 1
vgBaseEntry* vgEntryFactory::createEntryFromRenderer( vgKernel::Renderer* renderer )
{

	using namespace vgKernel;
	PluginPointerVec* vec = PluginManager::getSingleton().getPluginVecRef();

	if ( vec == NULL )
	{
		return NULL;
	}

	PluginPointerVec::iterator iter = vec->begin();
	PluginPointerVec::iterator iter_end = vec->end();

	for ( ; iter != iter_end ; ++ iter )
	{
		Plugin* plg = *iter;
		assert( plg != NULL );

		AbstractEntry* abentry = plg->rendererToEntry( renderer );
		if (  abentry != NULL )
		{
			vgBaseEntry* baentry = dynamic_cast<vgBaseEntry*>( abentry );

			if ( baentry != NULL )
			{
				return baentry;
			}
		}
	}

	{
		using namespace vgUI;

		RendererToEntryRegisterPtrVec::iterator iter = _regs.begin();
		RendererToEntryRegisterPtrVec::iterator iter_end = _regs.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			RendererToEntryRegister* reg = *iter;

			AbstractEntry* abentry = reg->rendererToEntry( renderer );
			if (  abentry != NULL )
			{
				vgBaseEntry* baentry = dynamic_cast<vgBaseEntry*>( abentry );

				if ( baentry != NULL )
				{
					return baentry;
				}
			}
		}
	}


#if 1

	//------------------------------------------
	// 
	//------------------------------------------

	vgKernel::RendererType type = 
		renderer->getType();

	vgBaseEntry* ret = NULL;


	switch( type )
	{
		// MeshManager
	case  vgMesh::RENDERER_TYPE_MESH:
		ret = new vgMeshEntry( (vgMesh::MeshItem*)renderer );
		break;

		// CamManager
	case vgCam::RENDERER_TYPE_VIEWCAMERA:
		ret = new vgViewCamEntry( (vgCam::ViewCam*)renderer );
		break;	
	case vgCam::RENDERER_TYPE_CAMRECORD://zhu
		ret = new vgCameraRecordEntry( (vgCam::CameraRecord*) renderer );
		break;


	//case vgMod::RENDERER_TYPE_MODOJBECT:
	//	vgMod::ObjFrameNode* pObjFrameNode = 
	//		dynamic_cast<vgMod::ObjFrameNode*>(renderer);
	//	//assert( pObjNode != NULL );
	//	if( pObjFrameNode && pObjFrameNode->hasKeyFrame() )
	//	{
	//		ret = new vgMovingEntry<vgMod::ObjFrameNode>( pObjFrameNode );
	//	}
	//	else
	//	{
	//		vgMod::ObjectNode* pObjNode = dynamic_cast<vgMod::ObjectNode*>(renderer);

	//		ret = new vgMod::vgObjectEntry( pObjNode );
	//	}
	//	break;


	//	// SoundManager
	//case vgSound::RENDERER_TYPE_SOUND:
	//	ret = new vgSound3DEntry( (vgSound::Sound3D*)renderer );
	//	break;

	//case vgShape::RENDERER_TYPE_SHAPE_LAYER:
	//	//ret = new ShapeLayerEntry( (vgShape::Layer*)renderer );
	//	ret = new ShapeLayerEntryEx( (vgShape::Layer*)renderer );
	//	break;
	//

	//case vgGIS3D::RENDERER_TYPE_PIPELINE_LAYER:
	//	ret = new vgPipeLineEntry((vgGIS3D::OGRPipeLineMap*) renderer);
	//	break;

	default:
		assert( 0 );
	    break;
	}

	//assert( ret != NULL );

	return ret;

#endif
}

#else
vgBaseEntry* vgEntryFactory::createEntryFromRenderer( vgKernel::Renderer* renderer )
{
	vgKernel::RendererType type = 
		renderer->getType();

	vgBaseEntry* ret = NULL;

	vgMod::ObjFrameNode*	pObjFrameNode = NULL;


	switch( type )
	{
		// MeshManager
	case  vgMesh::RENDERER_TYPE_MESH:
		ret = new vgMeshEntry( (vgMesh::MeshItem*)renderer );
		break;

		// CamManager
	case vgCam::RENDERER_TYPE_VIEWCAMERA:
		ret = new vgViewCamEntry( (vgCam::ViewCam*)renderer );
		break;	
	case vgCam::RENDERER_TYPE_CAMRECORD://zhu
		ret = new vgCameraRecordEntry( (vgCam::CameraRecord*) renderer );
		break;

		// SoundManager
	case vgSound::RENDERER_TYPE_SOUND:
		ret = new vgSound3DEntry( (vgSound::Sound3D*)renderer );
		break;

		// MovingManager
	case vgMs3d::RENDERER_TYPE_MS3D:
		ret = new vgMs3dEntry((vgMs3d::CMs3d*) renderer );
		break;

	case RENDERER_TYPE_GISMATCH://  [9/23/2008 YX]
		ret = new vgCore::vgGisMatchEntry( (vgMod::GisRoadMatch*) renderer );
		break;

	case vgMod::RENDERER_TYPE_MODOJBECT:
		pObjFrameNode = dynamic_cast<vgMod::ObjFrameNode*>(renderer);
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

	case vgMod::RENDERER_TYPE_BILLBOARD:
		ret = new vgMod::vgBillboardEntry((vgMod::BillboardNode*) renderer);
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

	case vgShape::RENDERER_TYPE_SHAPE_LAYER:
		//ret = new ShapeLayerEntry( (vgShape::Layer*)renderer );
		ret = new ShapeLayerEntryEx( (vgShape::Layer*)renderer );
		break;

	case vgAutoBuild::RENDERER_TYPE_AUTOBUILD:
		ret = new vgCore::vgAutoBuildEntry((vgAutoBuild::AutoBuildNode*)renderer);
		break;

	default:
		assert( 0 );
		break;
	}

	assert( ret != NULL );

	return ret;
}


#endif
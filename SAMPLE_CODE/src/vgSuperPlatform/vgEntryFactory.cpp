


#include <vgStableHeaders.h>
#include "vgEntryFactory.h"
#include <vgMesh/vgmMeshItem.h>

#include "vgObjectEntry.h"
#include "vgViewCamEntry.h"
#include <vgCam/vgcaViewCam.h>
#include "vgparticleentry.h"
#include "vgGPUSpecialEntry.h"
#include "vgSound/vgSound3D.h"
#include "vgSound3DEntry.h"
#include "vgMs3dEntry.h"
#include "vgMovingEntry.h"
#include "vgCameraRecordEntry.h"
#include "vgBillboardEntry.h"

#include "GisMatchEntry.h"
#include "vgVecStringEntry.h"

#include "vgVectorLayerEntry.h"
#include "vgVectorGeometryEntry.h"

#include "vgobjframenode.h"

#include "vgShapeLayerEntryEx.h"
#include <vgVector/vgAutoBuildNode.h>
#include "vgAutoBuildEntry.h"

vgBaseEntry* vgEntryFactory::createEntryFromRenderer( vgKernel::Renderer* renderer )
{
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
	case vgCam::RENDERER_TYPE_VCR://zhu
		ret = new vgCameraRecordEntry( (vgCam::CameraRecord*) renderer );
		break;

		// SoundManager
	case vgCore::RENDERER_TYPE_SOUND:
		ret = new vgSound3DEntry( (vgCore::Sound3D*)renderer );
		break;

		// MovingManager
	case vgMs3d::RENDERER_TYPE_MS3D:
		ret = new vgMs3dEntry((vgMs3d::CMs3d*) renderer );
		break;
	case vgCore::RENDERER_TYPE_KEYFRAME://chunyongma
		ret = new vgMovingEntry<vgCore::ObjFrameNode>( (vgCore::ObjFrameNode*) renderer );
		break;
	case RENDERER_TYPE_GISMATCH://  [9/23/2008 YX]
		ret = new vgCore::vgGisMatchEntry( (vggismatch*) renderer );
		break;

	case vgGIS3D::RENDERER_TYPE_VEC_STRING:
		ret = new vgVecStringEntry( (vgGIS3D::VertexStringClass*)renderer );
		break;
	
		// QuadtreeSceneManager
	case vgCore::RENDERER_TYPE_MODTERRAIN:
	case vgCore::RENDERER_TYPE_MODOJBECT:
		ret = new vgCore::vgObjectEntry( (vgCore::ObjectNode*)renderer );
		break;

	case vgCore::RENDERER_TYPE_BILLBOARD:
		ret = new vgCore::vgBillboardEntry((vgCore::BillboardNode*) renderer);
		break;

	case vgCore::RENDERER_TYPE_PATICLE:
		ret = new vgCore::vgParticleEntry( (vgCore::vgParticle*)renderer );
		break;

	case vgCore::RENDERER_TYPE_GPUSPECIAL_WARTER:
		ret = new vgCore::vgGPUSpecialEntry<vgCore::WaterNode>( (vgCore::WaterNode*)renderer );
		break;
	case vgCore::RENDERER_TYPE_GPUSPECIAL_SKYNODE:
		ret = new vgCore::vgGPUSpecialEntry<vgCore::SkyboxNode>( (vgCore::SkyboxNode*)renderer );
		break;
	case vgCore::RENDERER_TYPE_GPUSPECIAL_MIRROR:
		ret = new vgCore::vgGPUSpecialEntry<vgCore::MirrorNode>( (vgCore::MirrorNode*)renderer );
		break;
	case vgCore::RENDERER_TYPE_GPUSPECIAL_METAL:
		ret = new vgCore::vgGPUSpecialEntry<vgCore::MetalNode>( (vgCore::MetalNode*)renderer );
		break;
	case vgCore::RENDERER_TYPE_GPUSPECIAL_FLOOR:
		ret = new vgCore::vgGPUSpecialEntry<vgCore::BrightfloorNode>( (vgCore::BrightfloorNode*)renderer );
		break;
	case vgCore::RENDERER_TYPE_GPUSPECIAL_AVI:
		ret = new vgCore::vgGPUSpecialEntry<vgCore::AviNode>( (vgCore::AviNode*)renderer );
		break;
	case vgCore::RENDERER_TYPE_GPUSPECIAL_GLASS:
		ret = new vgCore::vgGPUSpecialEntry<vgCore::GlassNode>( (vgCore::GlassNode*)renderer );
		break;
// 	case vgCore::RENDERER_TYPE_AUTOBUILD:
// 		ret = new vgCore::vgAutoBuildEntry((vgVector::AutoBuildNode*)renderer);
// 		break;

		// layer
	case vgVector::RENDERER_TYPE_VECTORLAYER:
		ret = new vgVectorLayerEntry( (vgVector::vgvLayer*)renderer );
		break;

		// geometry
	case vgVector::RENDERER_TYPE_VECTORGEOMETRY:
		ret = new vgVectorGeometryEntry( (vgVector::vgvGeometry*)renderer );
		break;

	case vgShape::RENDERER_TYPE_SHAPE_LAYER:
		ret = new ShapeLayerEntry( (vgShape::Layer*)renderer );
		//ret = new ShapeLayerEntryEx( (vgShape::Layer*)renderer );
		break;
	
	case vgVector::RENDERER_TYPE_AUTOBUILD:
		ret = new vgCore::vgAutoBuildEntry((vgVector::AutoBuildNode*)renderer);
		break;

	default:
		assert( 0 );
	    break;
	}

	assert( ret != NULL );

	return ret;
}
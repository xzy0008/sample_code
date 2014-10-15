
#include <vgStableHeaders.h>

#include <vgShapeDLL/vgshpPlugin.h>

#include <vgShape/vgshShapeManager.h>

#include <vgEntry/vgShapeLayerEntry.h>

namespace	vgShape
{
	void ShapePlugin::render()
	{
		vgShape::ShapeManager::getSingleton().renderShapes();
	}

	
	String ShapePlugin::getName()
	{
		return VGSH_DLL_NAME;	
	}

	
	bool ShapePlugin::initInOpenGL()
	{
		return vgShape::ShapeManager::getSingleton().initAfterOpenGLSetup();
	}

	
	bool ShapePlugin::uninitInOpenGL()
	{
		return vgShape::ShapeManager::getSingleton().uninitBeforeOpenGLDestroy();
	}

	
	void ShapePlugin::reset()
	{
		vgShape::ShapeManager::getSingleton().reset();
	}
	
	vgKernel::AbstractEntry* ShapePlugin::rendererToEntry( vgKernel::Renderer* renderer )
	{
		vgKernel::RendererType type = 
			renderer->getType();

		vgBaseEntry* ret = NULL;

		switch( type )
		{
			// SoundManager
		case vgShape::RENDERER_TYPE_SHAPE_LAYER:
			ret = new	ShapeLayerEntry( (vgShape::Layer*)renderer );
			break;

		default:
			break;
		}

		return ret;
	}
}
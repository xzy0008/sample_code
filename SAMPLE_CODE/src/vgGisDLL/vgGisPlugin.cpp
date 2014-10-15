
#include <vgStableHeaders.h>

#include <vgGisDLL/vgGisPlugin.h>

#include <vgGIS/vgGisManager.h>

#include <vgGIS3D/vggiPrerequisite.h>
 
#include <vgGIS3D/vggiGisDataManager.h>

namespace	vgGIS3D
{
	void GisPlugin::render()
	{
		// vgGIS3D::GisManager::getSingleton().renderGisElements();
	}

	String GisPlugin::getName()
	{
		return VGG_DLL_NAME;	
	}

	bool GisPlugin::uninitInOpenGL()
	{
		vgGIS3D::GisManager::getSingleton().uninitBeforeOpenGLDestroy();

		return true;
	}

	vgKernel::AbstractEntry* GisPlugin::rendererToEntry( vgKernel::Renderer* renderer )
	{
		//if (renderer->getType() == vgGIS3D::RENDERER_TYPE_GIS_LAYER)
		//{
		//	vgKernel::AbstractEntry *pEntry = 
		//		new GisLayerEntry(dynamic_cast<vgGIS3D::Layer*>(renderer));

		//	return pEntry;
		//}

		switch (renderer->getType())
		{
		   case vgGIS3D::RENDERER_TYPE_GIS_LAYER:
			   {
				   vgKernel::AbstractEntry *pEntry = 
					   new GisLayerEntry(dynamic_cast<vgGIS3D::Layer*>(renderer));

				   return pEntry;
				   break;
			   }

		   case vgGIS3D::RENDERER_TYPE_PIPELINE_LAYER:
			   {
				   vgKernel::AbstractEntry *pEntry = 
					   new vgPipeLineEntry(dynamic_cast<vgGIS3D::OGRPipeLineMap*>(renderer));

				   return pEntry;
				   break;
			   }

		   default:
			  // assert (0);
			   break;




		}

		return NULL;
	}

	void GisPlugin::readProject(const String& projpath , const String& projname)
	{
		GisDataManager::getSingleton().readProject(projpath);
	}

	void GisPlugin::saveProject( const String& projpath , const String& projname )
	{
		GisDataManager::getSingleton().saveProject(projpath);
	}
}
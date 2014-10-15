#pragma once

#include <vgKernel/vgkRenderCommand.h>
#include <vgMesh/vgmMeshManager.h>

namespace vgMesh
{
	class MeshRenderCommand : public vgKernel::RenderCommand
	{
	public:
		MeshRenderCommand() : vgKernel::RenderCommand(VG_RP_MESH_RENDER) {}

		inline virtual bool render() 
		{
			vgMesh::MeshManager::getSingleton().render();

			return true;
		}
	};
}
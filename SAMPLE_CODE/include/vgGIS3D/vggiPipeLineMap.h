#pragma once

#include <vgKernel/vgkVec3.h>
#include <vgKernel/vgkUniqueID.h>

namespace vgGIS3D
{
	class PipeLineMap
	{
	public:

		virtual void render() {}

		virtual void findPipeLine(vgKernel::Vec3 startPoint, vgKernel::Vec3 endPoint, vector<int>& PipeLine) {}
		
		virtual bool getPipeLineInfo(vgKernel::Vec3 pointInPipe) { return false; }
		
		virtual bool getPipeLineInfo(string PipeName) { return false; }

		//virtual bool isPipeLineConnected(string PipeName1, string PipeName2) { return false; }

		//virtual bool isPipeLineConnected(vgKernel::Vec3 pointInPipe1, vgKernel::Vec3 pointInPipe2) { return false;}
	};
}
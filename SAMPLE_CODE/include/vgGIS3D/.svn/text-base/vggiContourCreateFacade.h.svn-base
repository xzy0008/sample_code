#pragma once

#include <vgGIS3D/vggiContourGeoData.h>

namespace vgGIS3D
{
	class ContourCreateFacade
	{
	public:
		static bool createFromVtrArea(const vector<vgKernel::Vec3>& boundPoints);
		
		static bool createFromGrdFile(string name, const vector<vgKernel::Vec3>& boundPoints);

		// slice 为切分粒度 numOfLine 是等值线数 specialVal 是要特别生成的点
		static bool createContour(string name, vgKernel::Box area, 
			int numOfLine, GridDataInfo info, float **ppRawData, 
			float* specialVal = NULL, bool use3DCoord = false);
		
#if 0
		static bool createFromPureData();

		static bool createFromGrdFile();
#endif

	};
}
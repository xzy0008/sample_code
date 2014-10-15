//PipelineDatabase.h
//
////////////////////////////////////////////////////////////////////////////////////
#ifndef _PIPELINE_DATABASE_H
#define _PIPELINE_DATABASE_H

#include "afxtempl.h"
#include "string.h"
#include <vgKernel/vgkSharePtr.h>
namespace vgGIS3D
{
	class LINE3D
	{
	public:	
		std::vector <vgKernel::Vec3> PointArray;		//每条管线包含的管点

		LINE3D()
		{
		}

		LINE3D& operator=(const LINE3D &s)
		{
			for(int i = 0; i < s.PointArray.size(); i++)
				PointArray.push_back(s.PointArray.at(i));
			return *this;
		}

		LINE3D(const LINE3D &s)
		{
			for(int i = 0; i < s.PointArray.size(); i++)
				PointArray.push_back(s.PointArray.at(i));
		}

		~LINE3D()
		{
			PointArray.clear();
		}
	};


}

#endif
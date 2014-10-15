#pragma once

#include <gdal/ogrsf_frmts.h>
#include <gdal/ogr_api.h>
#include <vgKernel/vgkForward.h>
#include <vgShape/vgshDefinition.h>
#include <vgKernel/vgkSharePtr.h>
#include <vgPlan/vgpShpArea.h>

namespace vgPlan
{
	class vgExcludeArea : public vgShpArea
	{
	public:
		vgExcludeArea();
		~vgExcludeArea();

// 		bool setGeometry(OGRGeometry* pGeom, const vgKernel::Mat4 &mat);
//  
//  		OGRGeometry* getGeometry()
//  		{
//  			return m_pGeometry;
//  		}
// 
//  		void setName(string name)
//  		{ 
//  			m_areaName = name;
//  		}
// 
//  		string getName()
//  		{
//  			return m_areaName;
//  		}

	private:
// 		// 应使用clone出来的geometry
//  		OGRGeometry* m_pGeometry;
//  
//  		string m_areaName;
	};

	typedef vgKernel::SharePtr<vgExcludeArea> vgExcludeAreaPtr;
}
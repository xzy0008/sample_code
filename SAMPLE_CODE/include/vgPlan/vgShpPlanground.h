#ifndef __VGPLANSHPGROUND__
#define __VGPLANSHPGROUND__

#include <vgShape/vgshGeometry.h>
#include <vgShape/vgshSelector.h>
#include <vgPlan/vgPlanground.h>
#include <vgShape/vgshLayer.h>

#include <vgKernel/vgkForward.h>
#include <vgShape/vgshDefinition.h>
#include <vgKernel/vgkSharePtr.h>
#include <vgPlan/vgpShpArea.h>

namespace  vgPlan
{
	/*
		初始底图类，将在此类上构建最后的放置底图
	*/

	class vgShpPlanground : public vgShpArea
	{
	public:

		vgShpPlanground()
		{
		}
		
		vgShpPlanground(OGRGeometry* pGemo) 
		{
			__super::setGeometry(pGemo);
		}

		~vgShpPlanground()
		{
		}



		bool diffGemotry(OGRGeometry *pGemo);
		

	private:
// 		// 使用的Geometry应该是clone出来的，否则可能成为野指针
//  		OGRGeometry *m_pGeometry;
//  
//  		string m_groundName;

	};

	// 智能指针声明.
	typedef vgKernel::SharePtr<vgPlan::vgShpPlanground> vgShpPlangroundPtr;
}

#endif
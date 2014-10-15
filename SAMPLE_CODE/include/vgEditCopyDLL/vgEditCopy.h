
#ifndef VGEDITCOPY_H_INCLUDED
#define VGEDITCOPY_H_INCLUDED

#include <vgEditCopyDLL/vgEditCopyDefinition.h>
#include <vgKernel/vgkRenderer.h>
/********************************************************************
	created:	2010/04/26
	filename: 	vgEditCopy.h
	file path:	\include\vgEditCopyDLL
	file base:	vgEditCopy
	file ext:	h
	author:		LSS
	
	purpose:	实现模型拷贝功能
*********************************************************************/

namespace vgEdit{

	class EditCopy
	{
	public:
		EditCopy();
		~EditCopy();

	public:
		vgKernel::RendererQueue* 	copyRenderer(vgKernel::RendererQueue* pRenders,
			AxisTypeEnum axisTypeEnum = AXIS_NONE);

	protected:
		vgKernel::Renderer*	copyRenderer(vgKernel::Renderer* pRender);

	protected:
		virtual	bool	reLocate(vgKernel::Renderer* pRender,
			vgKernel::Renderer* pRenderRef);

		bool	reName(vgKernel::Renderer* pRender,
			vgKernel::Renderer* pRenderRef);

		AxisTypeEnum	getAxisType();
		//static	bool	addToUI(vgMod::NodePtrVec* modItems);
	protected:
		AxisTypeEnum m_axisTypeEnum;
	};//EditCopy
}
#endif//VGEDITCOPY_H_INCLUDED  

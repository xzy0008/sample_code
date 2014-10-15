
#ifndef VGEDITMIRROR_H_INCLUDED
#define VGEDITMIRROR_H_INCLUDED

#include <vgEditCopyDLL/vgEditCopy.h>
#include <vgKernel/vgkRenderer.h>
/********************************************************************
	created:	2010/04/26
	filename: 	vgEditMirror.h
	file path:	\include\vgEditCopyDLL
	file base:	vgEditCopy
	file ext:	h
	author:		LSS
	
	purpose:	实现模型拷贝功能
*********************************************************************/

namespace vgEdit{

	class EditMirror : public EditCopy
	{
	public:
		EditMirror();
		~EditMirror();

	protected:
		virtual	bool	reLocate(vgKernel::Renderer* pRender,
			vgKernel::Renderer* pRenderRef);

		void	mirrorByAxis(int axis);

	protected:
		vgKernel::Renderer* m_pRendererOld;

		vgKernel::Renderer* m_pRendererNew;

	};//EditMirror
}
#endif//VGEDITMIRROR_H_INCLUDED  

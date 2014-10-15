


#ifndef __VGEDITCOPYMANAGER_H__
#define __VGEDITCOPYMANAGER_H__


#include <vgEditCopyDLL/vgEditCopyDefinition.h>
#include <vgKernel/vgkSingleton.h>

#include <vgKernel/vgkRenderer.h>

#include <vgEditCopyDLL/vgEditCopy.h>
#include <vgEditCopyDLL/vgEditMirror.h>

namespace  vgEdit {

	/**
	@date 	2008/05/21  20:23	
	@author  leven

	@brief 	

	@see    
	*/
	class  VGEDITCOPY_EXPORT EditCopyManager  : 
		 public vgKernel::Singleton<EditCopyManager>
	{
	public:
		EditCopyManager();
		~EditCopyManager();

		bool initialise()
		{
			return true;
		}

		bool shutdown()
		{		

			return true;
		}


		bool initialise( HWND hWnd );	


	   	void unloadData();

		void reset();



	public:
		vgKernel::RendererQueue* 	copyRenderer(vgKernel::RendererQueue* pRenders = NULL,
			AxisTypeEnum axisTypeEnum = AXIS_NONE );
		
		vgKernel::RendererQueue* 	mirrorRenderer(vgKernel::RendererQueue* pRenders = NULL,
			AxisTypeEnum axisTypeEnum = AXIS_NONE);

		AxisTypeEnum	getAxisType();
		void	setAxisType(AxisTypeEnum axisType);
	private:
		 HWND _hwnd ;

		 EditCopy	_utilityEdit;
		 EditMirror	_utilityMirror;

		 AxisTypeEnum m_axisTypeEnum;


	};




}// end of namespace 

#endif // end of __VGEDITCOPYMANAGER_H__


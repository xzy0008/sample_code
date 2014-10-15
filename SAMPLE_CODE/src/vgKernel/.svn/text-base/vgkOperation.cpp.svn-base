// Operation.cpp: implementation of the Operation class.
//
//////////////////////////////////////////////////////////////////////

#include <vgStableHeaders.h>
#include <vgKernel/vgkOperation.h>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace vgKernel{


	void vgkOperator::execute()
	{
		RendererOperatorObserverQueue::iterator  itr = _renderqueue->begin();
		RendererOperatorObserverQueue::iterator  itr_end = _renderqueue->end();

		for ( ; itr != itr_end ; ++ itr )
		{
			if ( (*itr)->GetRender() != NULL )
			{
				_operation->Redo((*itr)->GetRender());
			}
		}

	}

	void vgkOperator::unexecute()
	{
		RendererOperatorObserverQueue::iterator  itr = _renderqueue->begin();
		RendererOperatorObserverQueue::iterator  itr_end = _renderqueue->end();

		for ( ; itr != itr_end ; ++ itr )
		{
			if ( (*itr)->GetRender() != NULL )
			{
				_operation->Undo((*itr)->GetRender());
			}
		}

	}

}
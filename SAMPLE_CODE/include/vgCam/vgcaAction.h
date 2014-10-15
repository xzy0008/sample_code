


#ifndef __VGCAACTION_H__
#define __VGCAACTION_H__
#include <vgCam/vgcaDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSharePtr.h>

	
namespace vgCam {


	typedef int ActionType;


	/**
		@date 	2009/02/06  15:37	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class Action
	{
	public:
		Action( ActionType type)
		{
			_type = type;
		}
		virtual ~Action()
		{
			
		}
	
	
		virtual void doAction() = 0;

		ActionType getActionType() const
		{
			return _type;
		}

	protected:

		ActionType _type;
	};
	

	typedef vgKernel::SharePtr<Action> ActionPtr;

	typedef std::map< ActionType , ActionPtr > ActionPtrMap;


	typedef std::pair<bool , ActionPtrMap::iterator > ActionPtrMapInsertRes;
	
}// end of namespace vgCam
	


#endif // end of __VGCAACTION_H__
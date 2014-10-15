


#include <vgStableHeaders.h>
#include <vgCam/vgcaActionHolder.h>


namespace vgCam {
	

	
	
	
	//----------------------------------------------------------------
	bool ActionHolder::doActionByActionType( const ActionType& act_type )
	{
		ActionPtrMap::iterator iter = _actionMap.find( act_type );

		if ( iter != _actionMap.end() )
		{
			ActionPtr act = iter->second;
			assert( act.isNull() == false );

			act->doAction();

			return true;
		}

		return false;
	}
	//----------------------------------------------------------------
	bool ActionHolder::registerAction( ActionPtr act )
	{
		if ( act.isNull() == true )
		{
			return false;
		}

		ActionPtrMap::iterator iter = _actionMap.find( act->getActionType() );

		if ( iter != _actionMap.end() )
		{
			iter->second = act;
			return true;
		}

		_actionMap.insert( std::make_pair( act->getActionType() , act ) );

		return true;
	}
	//----------------------------------------------------------------
	void ActionHolder::deleteActionByActionPtr( ActionPtr act )
	{
		assert( act.isNull() == false );

		ActionPtrMap::iterator iter = _actionMap.find( act->getActionType() );

		if ( iter != _actionMap.end() )
		{
			_actionMap.erase( iter );
		}

		return;
	}
	//----------------------------------------------------------------
	void ActionHolder::deleteActionByActionType( const ActionType& act_type )
	{
		ActionPtrMap::iterator iter = _actionMap.find( act_type );

		if ( iter != _actionMap.end() )
		{
			_actionMap.erase( iter );
		}

		return;
	}
	//----------------------------------------------------------------


}// end of namespace vgCam

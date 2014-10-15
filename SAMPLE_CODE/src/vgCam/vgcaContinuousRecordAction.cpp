


#include <vgStableHeaders.h>
#include <vgCam/vgcaContinuousRecordAction.h>
#include <vgCam/vgcaCamManager.h>


namespace vgCam {
	
	
	

	//----------------------------------------------------------------
	void ContinuousRecordAction::doAction()
	{
		if( _nextPlayingRecord.isNull() == false )
		{
			CamManager::getSingleton().setCurrentCameraRecordPtr(
				_nextPlayingRecord );

			_nextPlayingRecord->startPlaying();
		}
		if( _fatherHolder.isNull() == false )
		{
			_fatherHolder->clearActions();
		}
	}
	//----------------------------------------------------------------
}// end of namespace vgCam




#ifndef __VGCACONTINUOUSRECORDACTION_H__
#define __VGCACONTINUOUSRECORDACTION_H__
#include <vgCam/vgcaDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgCam/vgcaRecordAction.h>
#include <vgCam/vgcaCameraRecord.h>

	
namespace vgCam {

	/**
		@date 	2009/02/09  10:09	
		@author  leven
	
		@brief 	注册需要手动来执行
	
		@see    
	*/
	class  VGCA_EXPORT ContinuousRecordAction : public RecordAction
	{
	public:
		ContinuousRecordAction( CameraRecordPtr current_record ,
			CameraRecordPtr next_record )
			: RecordAction( RecordActionType_finish )
		{
			_nextPlayingRecord = next_record;
			_fatherHolder = current_record;
		}
		~ContinuousRecordAction()
		{
			
		}
	
		virtual void doAction();

	private:
	
		CameraRecordPtr _fatherHolder;
		CameraRecordPtr _nextPlayingRecord;

	};
	
	
}// end of namespace vgCam
	


#endif // end of __VGCACONTINUOUSRECORDACTION_H__
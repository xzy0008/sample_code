



#ifndef __VGMOKEYFRAMECONTROL_H__
#define __VGMOKEYFRAMECONTROL_H__

#include <vgModel/vgmoDefinition.h>
#include <vgKernel/vgkForward.h>

	
namespace vgModel {

	class Timer;
	struct VmdKeyFrame;


	/**
		@date 	2009/06/02  19:48	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class VGMO_EXPORT KeyFrameControl
	{
	public:
		KeyFrameControl();
		~KeyFrameControl();
	
	
	public:

		long readBuf( char* buf );

		virtual void multKeyFrameMatrix();


		KeyFrameControl* createCopy() const;
	
	private:


		int _frameCount;
		int _startFrame;
		int _endFrame;

		int _timeIntervalMS;
		int _curFrameIndex;
		int _currentTimeMS;
		int _lastTimeMS;

		bool _play;
		bool _loop;
		VmdKeyFrame* _frames;

		Timer* _timer;
		int _currentFrame;
	
	
	};
	
	
}// end of namespace vgModel
	


#endif // end of __VGMOKEYFRAMECONTROL_H__



#ifndef __VGMOFILEMODKEYFRAMEINFO_H__
#define __VGMOFILEMODKEYFRAMEINFO_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkVec3.h>
#include <vgModel/vgmoFileDefinitionVmd.h>

	
namespace vgModel {



	struct ModKeyFrame
	{
		int		m_fTime;		//	Time at which keyframe is started
		vgKernel::Vec3 key_translate;	//	Translation or Rotation values
		float	key_rotate[4];
		vgKernel::Vec3 key_scale;
	};

	/**
		@date 	2009/05/21  20:21	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class ModKeyFrameInfo
	{
	public:
		ModKeyFrameInfo()
		{
			_frameCount = 0;
			 _startFrame = 0;
			 _endFrame = 0;

			 _play = true;
			 _loop = true;

			 _frames = NULL;
		}
		~ModKeyFrameInfo()
		{
			if ( _frames != NULL )
			{
				delete[] _frames;
				_frames = NULL;
			}
				
		}
	
		ModKeyFrameInfo* createCopy()
		{
			ModKeyFrameInfo* ret = new ModKeyFrameInfo;
			ret->_frameCount = _frameCount;
			ret->_startFrame = _startFrame;
			ret->_endFrame = _endFrame;

			ret->_play = _play;
			ret->_loop = _loop;

			ret->_frames = new ModKeyFrame[ _frameCount ];
			memcpy( ret->_frames , _frames , sizeof( ModKeyFrame ) * 
				_frameCount );

			return ret;
		}

		VmdKeyFrameInfo* createVmdKeyFrameInfo()
		{
			VmdKeyFrameInfo* ret = new VmdKeyFrameInfo;
			ret->_frameCount = _frameCount;
			ret->_startFrame = _startFrame;
			ret->_endFrame = _endFrame;

			ret->_play = _play;
			ret->_loop = _loop;

			ret->_frames = createVmdKeyFrame();

			return ret;
		}

		VmdKeyFrame* createVmdKeyFrame();


	public:

		int _frameCount;
		int _startFrame;
		int _endFrame;
		
		bool _play;
		bool _loop;

		ModKeyFrame* _frames;
	};
	
	
}// end of namespace vgModel
	


#endif // end of __VGMOFILEMODKEYFRAMEINFO_H__
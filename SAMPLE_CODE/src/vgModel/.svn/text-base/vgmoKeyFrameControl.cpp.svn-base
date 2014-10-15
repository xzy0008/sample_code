


#include <vgStableHeaders.h>
#include <vgModel/vgmoKeyFrameControl.h>

#include <vgModel/vgmoFileDefinitionVmd.h>
#include <vgModel/vgmoTimer.h>


namespace vgModel {
	
	
	

	KeyFrameControl::KeyFrameControl()
	{
		_frameCount = 0;
		_startFrame = 0;
		_endFrame = 0;
		_timeIntervalMS = 0;
		_currentTimeMS = 0;
		_curFrameIndex = 0;
		_lastTimeMS = 0;

		_play = true;
		_loop = true;
		_frames = NULL;

		_timer = NULL;
		_currentFrame = 0;
	}

	KeyFrameControl::~KeyFrameControl()
	{
		if ( _timer != NULL)
		{ 
			delete _timer;
			_timer = NULL;
		}

		if ( _frames != NULL )
		{
			delete[] _frames;
			_frames = NULL;
		}
	}
	//----------------------------------------------------------------
	long KeyFrameControl::readBuf( char* buf )
	{
		long pos  =0;

		_frameCount = *(int*)( buf + pos );
		pos += sizeof( int );
		assert( _frameCount > 0 );

		_startFrame = *(int*)( buf + pos );
		pos += sizeof( int );

		_endFrame = *(int*)( buf + pos );
		pos += sizeof( int );

		_play =* (bool*)( buf + pos );
		pos += sizeof( bool );

		_loop = *(bool*)( buf + pos );
		pos += sizeof( bool );

		_frames = new VmdKeyFrame[ _frameCount ];

		memcpy( _frames , buf + pos,  sizeof( VmdKeyFrame ) * _frameCount );
		//_frames = (VmdKeyFrame*)( buf + pos );
		pos += sizeof( VmdKeyFrame ) * _frameCount;

		//for ( int i = 0 ; i < _frameCount ; ++ i )
		//{
		//	_frames[i].m_fTime *= 1000;
		//}

		_timer = new Timer;
		_timer->initialise();

		assert( _startFrame <= _endFrame );
		assert( _startFrame >= 0 );
		assert( _endFrame >= 0 );
		assert( _endFrame <= _frameCount - 1 );

		_timeIntervalMS =
			_frames[_endFrame ].m_fTime - _frames[ _startFrame ].m_fTime;

		assert( _timeIntervalMS > 0 );

		return pos;
	}

	void KeyFrameControl::multKeyFrameMatrix()
	{
		if ( _frameCount != 0 )
		{
#if 0
			static int aa=0;

			int which = aa% _frameCount;

			glMultMatrixf( _frames[which]._matrix._m );

			aa++;

#else

			//------------------------------------------
			// 
			//------------------------------------------
			assert( _frameCount > 1 );

			int mss = _timer->getMS();
			_currentTimeMS = ( _lastTimeMS + mss ) % _timeIntervalMS;
			_lastTimeMS = _currentTimeMS;

			assert( _currentTimeMS >= 0 );

			_curFrameIndex = 0;
			while ( _frames[ _curFrameIndex].m_fTime < _currentTimeMS )
			{
				_curFrameIndex++;
			}

			//------------------------------------------
			// 开始插值
			// _currentFrameIndex必然大于1
			//------------------------------------------
			int fDeltaT = 
				_frames[ _curFrameIndex ].m_fTime - _frames[ _curFrameIndex - 1 ].m_fTime;

			float fInterp = 
				(_currentTimeMS - _frames[ _curFrameIndex - 1 ].m_fTime) / (float)fDeltaT;


			vgKernel::Mat4 result;


			result = 
				_frames[ _curFrameIndex - 1 ]._matrix * ( 1.0f - fInterp )+
				_frames[ _curFrameIndex  ]._matrix *  fInterp;

			glMultMatrixf( result._m );
			//glMultMatrixf( _frames[ _curFrameIndex  ]._matrix._m );

#endif
		}
	}

	KeyFrameControl* KeyFrameControl::createCopy() const
	{
		KeyFrameControl*ret = new KeyFrameControl;

		ret-> _frameCount = _frameCount;
		ret-> _startFrame = _startFrame;
		ret-> _endFrame = _endFrame;

		ret-> _timeIntervalMS = _timeIntervalMS;

		assert( _timeIntervalMS != 0 );
		assert( _timeIntervalMS > 0);

		ret-> _play = _play;
		ret-> _loop = _loop;

		ret->_frames = new VmdKeyFrame[ _frameCount ];
		memcpy( ret->_frames, _frames , 
			sizeof( VmdKeyFrame ) * _frameCount );

		ret->_timer = new Timer;
		ret->_timer->initialise();

		return ret;
	}
	//----------------------------------------------------------------


}// end of namespace vgModel

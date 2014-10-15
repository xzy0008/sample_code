



#ifndef __VGKPROCESSOBSERVER_H__
#define __VGKPROCESSOBSERVER_H__

#include <vgKernel/vgkForward.h>
#include <vgThreads/ScopedLock.h>

	
namespace vgKernel {

	/**
		@date 	2008/08/29  8:41	
		@author  xy
	
		@brief 	
	
		@see    
	*/
	class ProcessObserver
	{
	public:
		ProcessObserver()
		{
			
		}
		virtual ~ProcessObserver()
		{
			
		}
	
		virtual void onStart( const String& text , const int& range_lower , 
			const int& range_upper ) = 0;
	
		// 显示进度.0到100之间
		virtual void onNotify( const String& msg , 
			const int& process_pos ) = 0;

		virtual void onFinish( const String& msg ) = 0;
	
	};
	

	/**
		暂时不考虑obs的删除
		而且注意,这里不考虑对observer的管理控制.
	*/
	class ProcessNotifier
	{
	public:
		ProcessNotifier()
		{
			_currentPos = 0;
		}
		virtual ~ProcessNotifier()
		{
			
		}

		virtual bool registerProcessObs( const std::vector<ProcessObserver*>& obs )
		{
			std::vector<ProcessObserver*>::const_iterator iter = obs.begin();
			std::vector<ProcessObserver*>::const_iterator iter_end = obs.end();

			for ( ; iter != iter_end ; ++ iter )
			{
				_processObservers.push_back( *iter );
			}
			
			return true;
		}

		virtual bool registerProcessObs( ProcessObserver* obs )
		{
			_processObservers.push_back( obs );
			return true;
		}

		virtual void clearProcessObservers()
		{
			_processObservers.clear();
		}

		void notifyProcessObserversStart( const String& text , const int& range_lower , 
			const int& range_upper )
		{
			std::vector<ProcessObserver*>::iterator iter = _processObservers.begin();
			std::vector<ProcessObserver*>::iterator iter_end = _processObservers.end();

			for ( ; iter != iter_end ; ++ iter )
			{
				(*iter)->onStart(text , range_lower , range_upper);
			}
		}

		void setCurrentProcessPos( const String& msg , 
			const int& processing_pos )
		{
			vgThreads::ScopedLock locker( _sect );
			_currentString = msg;
			_currentPos = processing_pos;
		}

		void notifyCurrentProcessObserversPos()
		{
			vgThreads::ScopedLock locker( _sect );
			notifyProcessObserversPos( _currentString , _currentPos );
		}

		void notifyProcessObserversPos(const String& msg , 
			const int& processing_pos )
		{
			std::vector<ProcessObserver*>::iterator iter = _processObservers.begin();
			std::vector<ProcessObserver*>::iterator iter_end = _processObservers.end();

			for ( ; iter != iter_end ; ++ iter )
			{
				(*iter)->onNotify( msg , processing_pos );
			}
		}
	
		void notfiyProcessObserversFinish( const String& msg )
		{
			std::vector<ProcessObserver*>::iterator iter = _processObservers.begin();
			std::vector<ProcessObserver*>::iterator iter_end = _processObservers.end();

			for ( ; iter != iter_end ; ++ iter )
			{
				(*iter)->onFinish( msg );
			}
		}
	
		std::vector<ProcessObserver*> getProcessObs()
		{
			return _processObservers;
		}

	private:

		vgThreads::CriticalSection _sect;
		String _currentString;
		long _currentPos;

		std::vector<ProcessObserver*> _processObservers;
	
	
	};
	
}// end of namespace vgKernel
	


#endif // end of __VGKPROCESSOBSERVER_H__
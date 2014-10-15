




#ifndef __VGAIOSERVER_H__
#define __VGAIOSERVER_H__
#include <vgAsyn/vgaDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSingleton.h>
#include <vgKernel/vgkTrace.h>


namespace vgAsyn {

	class FileHandle;

	/**
		@date 	2008/06/20  15:45	
		@author  leven
	
		@brief 	注意!IoSever的初始化必须由外部完成!

		@see    
	*/
	class  VGA_EXPORT IoServer : public vgKernel::Singleton<IoServer>
	{
		friend class vgKernel::Singleton<IoServer>;
	private:
		IoServer() 
			: Singleton<IoServer>( VGK_SINGLETON_LEFE_IOSERVER ) 
		{
			_useMultithreadMode = true;
			_initialisedOK = false;
			_completionPort = INVALID_HANDLE_VALUE;

			VGK_TRACE(_T("IoServer created."));
		}
		~IoServer()
		{
			VGK_TRACE(_T("IoServer destroyed."));
		}

	protected:

		virtual bool initialise();

		virtual bool shutdown()
		{
			if ( _completionPort != INVALID_HANDLE_VALUE )
			{
				CloseHandle( _completionPort );
				_completionPort = INVALID_HANDLE_VALUE;
			}
			return true;
		}


	public:

		virtual void reset(){};//need to write

		inline const bool isMultithreadMode() const
		{
			return _useMultithreadMode;
		}

	
		HANDLE getCompletionPort()
		{
			assert( _useMultithreadMode == true );
			return _completionPort;
		}

		bool associateWithFileHandle( FileHandle* handle );
	
	private:

		static void fatalError( const String& errcode )
		{
			MessageBox( NULL , "Error occured in IOCP" , 
				errcode.c_str() , MB_OK );

			return;
		}

		static DWORD WINAPI workerThreadFunc(LPVOID pVoid);

	private:

		bool _initialisedOK;

		HANDLE _completionPort;

		// 用以标识是否使用IO completion ports
		bool _useMultithreadMode;
	
	};
	
	
	
	
}// end of namespace vgAsyn

#endif // end of __VGAIOSERVER_H__
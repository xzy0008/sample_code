


#include <vgStableHeaders.h>
#include <vgKernel/vgkLog.h>


namespace vgKernel {
	
	//-----------------------------------------------------------------------
	Log::Log( const String& name, bool debuggerOuput, bool suppressFile ) 
		: mLogLevel(LL_NORMAL), mDebugOut(debuggerOuput),
		mSuppressFile(suppressFile), mLogName(name)
	{
		_createok = false;

		if (!mSuppressFile)
		{
			mfpLog.open( name.c_str() ,std::fstream::out);
			mfpLog.close();
			mfpLog.open( name.c_str() ,std::fstream::in|std::fstream::out|std::fstream::trunc);		///生成log文件

			if ( mfpLog.fail() )
			{
				std::ostringstream o;
				o << "创建：" << name << "失败";
				MessageBox( NULL , o.str().c_str() , "Error", MB_OK );
				assert(0 && _T("create Log failed.") );

			}
			else
			{
				_createok = true;
			}
		}
	}
	//-----------------------------------------------------------------------
	Log::~Log()
	{
		if (!mSuppressFile)
		{
			mfpLog.close();
		}
	}
	//-----------------------------------------------------------------------
	void Log::logMessage( const String& message, LogMessageLevel lml, bool maskDebug )
	{
		if ( _createok == false )
		{
			return;
		}

		if ((mLogLevel + lml) >= VG_LOG_THRESHOLD)
		{
			for( mtLogListener::iterator i = mListeners.begin(); i != mListeners.end(); ++i )
				(*i)->messageLogged( message, lml, maskDebug, mLogName );

			// 此处李文修改。没有必要输出这样的信息
			//if (mDebugOut && !maskDebug)
			//	std::cerr << message << std::endl;

			// Write time into log
			if (!mSuppressFile)
			{
				struct tm *pTime;
				time_t ctTime; time(&ctTime);
				pTime = localtime( &ctTime );
				mfpLog << std::setw(2) << std::setfill(_T('0')) << pTime->tm_hour
					<<  _T(":") << std::setw(2) << std::setfill(_T('0')) << pTime->tm_min
					<<  _T(":") << std::setw(2) << std::setfill(_T('0')) << pTime->tm_sec 
					<<  _T(": ") << message << std::endl;

				// Flush stcmdream to ensure it is written (incase of a crash, we need log to be up to date)
				mfpLog.flush();
			}
		}
	}

	//-----------------------------------------------------------------------
	void Log::setLogDetail(LoggingLevel ll)
	{
		mLogLevel = ll;
	}

	//-----------------------------------------------------------------------
	void Log::addListener(LogListener* listener)
	{
		mListeners.push_back(listener);
	}

	//-----------------------------------------------------------------------
	void Log::removeListener(LogListener* listener)
	{
		mListeners.erase(std::find(mListeners.begin(), mListeners.end(), listener));
	}

	//----------------------------------------------------------------
	String Log::getLogContents()
	{
		if ( _createok == false )
		{
			return String();
		}
		std::ostringstream tmpsstream;

		/// 定位读文件开始位置.
		/// 注意:seekg是读文件专用.
		///		 seekp是写文件专用.
		mfpLog.seekg( std::ios::beg );


		tmpsstream <<  _T("------------ Log File Name: ")
			<< mLogName 
			<<  _T(" LogLevel: ") 
			<< mLogLevel 
			<<  _T("------------\n")
			<< mfpLog.rdbuf();

		//String content( tmpsstream.str() );
		//Integer size = content.size();

		//String resultheder = "------------ Log File Name: " 
		//	+ mLogName 
		//	+ " LogLevel: " 
		//	+ ConvertUtil::textCast(mLogLevel) 
		//	+ " LogSize: " 
		//	+ ConvertUtil::textCast(size)
		//	+ "------------\n";

		return tmpsstream.str();
	}
	//----------------------------------------------------------------
	void Log::clearLogContent()
	{
		mfpLog.close();

		mfpLog.open( mLogName.c_str() ,
			std::fstream::in| std::fstream::out| std::fstream::trunc);		///生成log文件

		if ( mfpLog.fail() )
		{
			assert(0 && _T("open Log failed."));
		}
	}

}// end of namespace vgKernel

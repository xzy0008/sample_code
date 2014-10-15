




#include <vgStableHeaders.h>
#include <vgKernel/vgkLogManager.h>
#include <vgKernel/vgkSystemUtility.h>
#include <vgKernel/vgkStringUtility.h>

namespace vgKernel {
	
	//----------------------------------------------------------------
	void LogManager::destroyAllLogs()
	{
		LogList::iterator i;
		for (i = mLogs.begin(); i != mLogs.end(); ++i)
		{
			delete i->second;
		}
		mLogs.clear();
		mDefaultLog = NULL;
	}
    //-----------------------------------------------------------------------
    Log* LogManager::createLog( const String& name, bool defaultLog, bool debuggerOutput, 
		bool suppressFileOutput)
    {
		String logname = name;

		if ( logname == "" )
		{
			String exepath = SystemUtility::getCurrentProcessPath();

			exepath += SystemUtility::getCurrentProcessName();

			exepath = exepath.substr( 0 , exepath.find_last_of(".") );
			logname = exepath + ".log";
			//StringUtility::getFilenameWithoutExtension( exepath ) + ".log";
		}

        Log* newLog = new Log(logname, debuggerOutput, suppressFileOutput);

        if( !mDefaultLog || defaultLog )
        {
            mDefaultLog = newLog;
        }

        mLogs.insert( LogList::value_type( logname, newLog ) );

        return newLog;
    }
    //-----------------------------------------------------------------------
    Log* LogManager::getDefaultLog()
    {
        return mDefaultLog;
    }
    //-----------------------------------------------------------------------
    Log* LogManager::setDefaultLog(Log* newLog)
    {
        Log* oldLog = mDefaultLog;
        mDefaultLog = newLog;
        return oldLog;
    }
    //-----------------------------------------------------------------------
    Log* LogManager::getLog( const String& name)
    {
        LogList::iterator i = mLogs.find(name);
        if (i != mLogs.end())
            return i->second;
        else
		{
            assert(_T("Log not found. "));

			return NULL;
		}
    }
	//-----------------------------------------------------------------------
	void LogManager::destroyLog(const String& name)
	{
		LogList::iterator i = mLogs.find(name);
		if (i != mLogs.end())
		{
			if (mDefaultLog == i->second)
			{
				mDefaultLog = 0;
			}
			delete i->second;
			mLogs.erase(i);
		}

		// Set another default log if this one removed
		if (!mDefaultLog && !mLogs.empty())
		{
			mDefaultLog = mLogs.begin()->second;
		}
	}
	//-----------------------------------------------------------------------
	void LogManager::destroyLog(Log* log)
	{
		destroyLog(log->getName());
	}
    //-----------------------------------------------------------------------
    void LogManager::logMessage( const String& message, LogMessageLevel lml, bool maskDebug)
    {
		if (mDefaultLog)
		{
			mDefaultLog->logMessage(message, lml, maskDebug);
		}
    }
    //-----------------------------------------------------------------------
    void LogManager::setLogDetail(LoggingLevel ll)
    {
		if (mDefaultLog)
		{
	        mDefaultLog->setLogDetail(ll);
		}
    }
	//----------------------------------------------------------------

	
	
}// end of namespace vgKernel

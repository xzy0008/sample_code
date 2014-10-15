/*
-----------------------------------------------------------------------------
  VRES(Virtual Reality GIS Engine System)    
  -------------------------------------------------------------
  License details ... waiting to add...
  -------------------------------------------------------------
  Copyright  (C) 2007 , leven - All Rights Reserved
-----------------------------------------------------------------------------
*/

#ifndef __VGLOG_H__
#define __VGLOG_H__
#if 0
#include <vgPrerequisites.h>


namespace vgCore {
	/**
		@date 	2007/02/26  1:30	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	///将级别设高,则部分message不会被记录.
	// LogMessageLevel + LoggingLevel > OGRE_LOG_THRESHOLD = message logged
    #define VG_LOG_THRESHOLD 4

	///LoggingLevel和LogMessageLevel共同决定了message是否会被记录.
    /** The level of detail to which the log will go into.
    */
    enum LoggingLevel
    {
        LL_LOW = 1,
        LL_NORMAL = 2,
        LL_BOREME = 3
    };

    /** The importance of a logged message.
    */
    enum LogMessageLevel
    {
        LML_TRIVIAL = 1,
        LML_NORMAL = 2,
        LML_CRITICAL = 3
    };

	///任何继承此类的类将会监听message.具体参见Log::logMessage方法的源代码.
    /** @remarks Pure Abstract class, derive this class and register to the Log to listen to log messages */
    class LogListener
    {
	public:
        virtual ~LogListener() {};

        /**
        @remarks
            This is called whenever the log recieves a message and is about to write it out
        @param message
            The message to be logged
        @param lml
            The message level the log is using
        @param maskDebug
            If we are printing to the console or not
        @param logName
            the name of this log (so you can have several listeners for different logs, and identify them)
        */
        virtual void messageLogged( const String& message, LogMessageLevel lml, bool maskDebug, const String &logName ) = 0;
    };

    /**
    @remarks
         Log class for writing debug/log data to files.
    @note
        <br>Should not be used directly, but trough the LogManager class.
    */
    class VgesExport Log
    {
    protected:
        std::fstream	mfpLog;		///输出文件流,生成在构造函数中.
        LoggingLevel	mLogLevel;
        bool			mDebugOut;		///设置为true并且maskDebug为false时将产生std::cerr输出.
        bool			mSuppressFile;		///设为true时不生成Log文件.
        String			mLogName;

        typedef std::vector<LogListener*> mtLogListener;
        mtLogListener mListeners;

    public:
		 // public to allow external locking
        /**
        @remarks
            Usual constructor - called by LogManager.
        */
        Log( const String& name, bool debugOutput = true, bool suppressFileOutput = false);

        /**
        @remarks
        Default destructor.
        */
        ~Log();

		/// Return the name of the log
		const String& getName() const { return mLogName; }
		/// Get whether debug output is enabled for this log
		bool isDebugOutputEnabled() const { return mDebugOut; }
		/// Get whether file output is suppressed for this log
		bool isFileOutputSuppressed() const { return mSuppressFile; }

        /** Log a message to the debugger and to log file (the default is
            "<code>OGRE.log</code>"),
        */
        void logMessage( const String& message, LogMessageLevel lml = LML_NORMAL, bool maskDebug = false );

        /**
        @remarks
            Sets the level of the log detail.
        */
        void setLogDetail(LoggingLevel ll);
		/** Gets the level of the log detail.
		*/
		LoggingLevel getLogDetail() const { return mLogLevel; }
        /**
        @remarks
            Register a listener to this log
        @param
            A valid listener derived class
        */
        void addListener(LogListener* listener);

        /**
        @remarks
            Unregister a listener from this log
        @param
            A valid listener derived class
        */
        void removeListener(LogListener* listener);


		void clearLogContent();

		/// 得到log文件内容.
		String getLogContents() ;
    };

	
	
}// end of namespace vgCore


#endif // end of __VGLOG_H__
#endif

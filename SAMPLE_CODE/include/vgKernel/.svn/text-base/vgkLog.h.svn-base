


#ifndef __VGKLOG_H__
#define __VGKLOG_H__

#include <vgKernel/vgkForward.h>
#include <fstream>

	
namespace vgKernel {

    #define VG_LOG_THRESHOLD 4

	// LoggingLevel和LogMessageLevel共同决定了message是否会被记录.
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
		LML_SHOW	= 3,
        LML_CRITICAL = 4
    };

	///任何继承此类的类将会监听message.具体参见Log::logMessage方法的源代码.
    class LogListener
    {
	public:
        virtual ~LogListener() {};
        virtual void messageLogged( const String& message, LogMessageLevel lml, bool maskDebug, const String &logName ) = 0;
    };


    class   VGK_EXPORT Log
    {
    protected:
		bool _createok;


        std::fstream	mfpLog;		///输出文件流,生成在构造函数中.
        LoggingLevel	mLogLevel;
        bool			mDebugOut;		///设置为true并且maskDebug为false时将产生std::cerr输出.
        bool			mSuppressFile;		///设为true时不生成Log文件.
        String			mLogName;

        typedef std::vector<LogListener*> mtLogListener;
        mtLogListener mListeners;

    public:

		 // public to allow external locking
        Log( const String& name, bool debugOutput = true, bool suppressFileOutput = false);

        ~Log();

		// Return the name of the log
		const String& getName() const { return mLogName; }
		// Get whether debug output is enabled for this log
		bool isDebugOutputEnabled() const { return mDebugOut; }
		// Get whether file output is suppressed for this log
		bool isFileOutputSuppressed() const { return mSuppressFile; }

        void logMessage( const String& message, LogMessageLevel lml = LML_NORMAL, bool maskDebug = false );


        void setLogDetail(LoggingLevel ll);

		LoggingLevel getLogDetail() const { return mLogLevel; }

        void addListener(LogListener* listener);


        void removeListener(LogListener* listener);


		void clearLogContent();

		// 得到log文件内容.
		String getLogContents() ;
    };

	
	
}// end of namespace vgKernel
	


#endif // end of __VGKLOG_H__
/*
-----------------------------------------------------------------------------
  VRES(Virtual Reality GIS Engine System)    
  -------------------------------------------------------------
  License details ... waiting to add...
  -------------------------------------------------------------
  Copyright  (C) 2007 , leven - All Rights Reserved
-----------------------------------------------------------------------------
*/

#ifndef __VGLOGMANAGER_H__
#define __VGLOGMANAGER_H__
#if 0
#include <vgPrerequisites.h>
#include <vgSingleton.h>
#include <vgLog.h>

namespace vgCore {

	/**
		@date 	2007/02/26  9:36	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	/** The log manager handles the creation and retrieval of logs for the
        application.
        @remarks
            This class will create new log files and will retrieve instances
            of existing ones. Other classes wishing to log output can either
            create a fresh log or retrieve an existing one to output to.
            One log is the default log, and is the one written to when the
            logging methods of this class are called.
		@par
			By default, Root will instantiate a LogManager (which becomes the 
			Singleton instance) on construction, and will create a default log
			based on the Root construction parameters. If you want more control,
			for example redirecting log output right from the start or suppressing
			debug output, you need to create a LogManager yourself before creating
			a Root instance, then create a default log. Root will detect that 
			you've created one yourself and won't create one of its own, thus
			using all your logging preferences from the first instance.
    */
    class VgesExport LogManager : public Singleton<LogManager>
    {
	protected:
        typedef std::map<String, Log*, std::less<String> >	LogList;

        /// A list of all the logs the manager can access
        LogList mLogs;

        /// The default log to which output is done
        Log* mDefaultLog;

    public:
		 // public to allow external locking

        LogManager();
        ~LogManager();

        /** Creates a new log with the given name.
            @param
                name The name to give the log e.g. 'Ogre.log'
            @param
                defaultLog If true, this is the default log output will be
                sent to if the generic logging methods on this class are
                used. The first log created is always the default log unless
                this parameter is set.
            @param
                debuggerOutput If true, output to this log will also be
                routed to the debugger's output window.
            @param
                suppressFileOutput If true, this is a logical rather than a physical
				log and no file output will be written. If you do this you should
				register a LogListener so log output is not lost.
        */
        Log* createLog( const String& name = "VgesLog.log", bool defaultLog = false, bool debuggerOutput = true, 
			bool suppressFileOutput = false);

        /** Retrieves a log managed by this class.
        */
        Log* getLog( const String& name);

        /** Returns a pointer to the default log.
        */
        Log* getDefaultLog();

		/** Closes and removes a named log. */
		void destroyLog(const String& name);
		/** Closes and removes a log. */
		void destroyLog(Log* log);

		void destroyAllLogs();

		/** Sets the passed in log as the default log.
        @returns The previous default log.
        */
        Log* setDefaultLog(Log* newLog);

        /** Log a message to the default log.
        */
        void logMessage( const String& message, LogMessageLevel lml = LML_NORMAL, 
            bool maskDebug = false);

        /** Log a message to the default log (signature for backward compatibility).
        */
        void logMessage( LogMessageLevel lml, const String& message,  
			bool maskDebug = false) { logMessage(message, lml, maskDebug); }

		/** Sets the level of detail of the default log.
        */
        void setLogDetail(LoggingLevel ll);



        static LogManager& getSingleton(void);

        static LogManager* getSingletonPtr(void);

    };


	
}// end of namespace vgCore

#endif // end of __VGLOGMANAGER_H__
#endif
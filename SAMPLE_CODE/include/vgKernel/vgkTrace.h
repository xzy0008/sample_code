

#ifndef __VGKTRACE_H__
#define __VGKTRACE_H__



#if _DEBUG
	#define VGK_USE_TRACE 1
#else
	#define VGK_USE_TRACE 1
#endif 





#include <vgKernel/vgkLogManager.h>

	
namespace vgKernel {

	class Trace
	{
	public:
#if VGK_USE_TRACE
		template <class T>
		static void createTrace( const T& info , const String& source ,
			const String& file , const long& line )
		{
			LogManager *logmgr = LogManager::getSingletonPtr();
			if ( logmgr != NULL )
			{
				std::ostringstream desc;

				desc <<  _T("- Trace Infomation: ") << info << _T("\n\t\t")
					<< _T(" in ") << source;

				if( line > 0 )
				{
					desc << _T(" at ") << file << _T(" (line ") << line << _T(")");
				}
				String fullDesc = desc.str();

				logmgr->logMessage( LML_CRITICAL , fullDesc , true );

				// TRACE( fullDesc.c_str() );
			}
		}
#endif


		template <class T>
		static void createShow( const T& info)
		{
			LogManager *logmgr = LogManager::getSingletonPtr();
			if ( logmgr != NULL )
			{
// 				std::ostringstream desc;
// 
// 				desc <<  _T("- Trace Infomation: ") << info << _T("\n\t\t")
// 					<< _T(" in ") << source;
// 
// 				if( line > 0 )
// 				{
// 					desc << _T(" at ") << file << _T(" (line ") << line << _T(")");
// 				}
// 				String fullDesc = desc.str();

				logmgr->logMessage( LML_SHOW , info , true );

				// TRACE( fullDesc.c_str() );
			}
		}

#if VGK_USE_TRACE
		template <class T>
		static void createShortTrace( const T& info )
		{
			LogManager *logmgr = LogManager::getSingletonPtr();
			if ( logmgr != NULL )
			{
				std::ostringstream desc;
				desc << info ;
				String fullDesc = desc.str();

				logmgr->logMessage( LML_CRITICAL , fullDesc , true );
			}
		}
#endif

	};

}// end of namespace vgKernel
	
#if VGK_USE_TRACE
	#define VGK_TRACE(description) vgKernel::Trace::createTrace( \
		description, _T(""), _T( __FILE__ ), ( __LINE__ ) );

	#define VGK_TRACE_SHORT(description) vgKernel::Trace::createShortTrace(description);

	#define VGK_SHOW(description) vgKernel::Trace::createShow(description)
#else 


	#define VGK_TRACE(description) 

	#define VGK_TRACE_SHORT(description) 

	#define VGK_SHOW(description) vgKernel::Trace::createShow(description)

#endif // end of VGK_USE_TRACE

#endif // end of __VGKTRACE_H__
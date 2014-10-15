



#ifndef __VGAASYNUTILITY_H__
#define __VGAASYNUTILITY_H__
#include <vgAsyn/vgaDefinition.h>
#include <vgKernel/vgkForward.h>
#include <crtdbg.h>

namespace vgAsyn {

	/**
		@date 	2008/06/23  13:35	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGA_EXPORT AsynUtility
	{
	private:
		AsynUtility()
		{
			
		}
		~AsynUtility()
		{
			
		}
	
	
	
	public:


		static __inline void checkFatalError(LPSTR linedesc, 
			LPSTR filename, int lineno, DWORD errnum)
		{
			LPSTR lpBuffer;
			char errbuf[256];
			char modulename[MAX_PATH];


			FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER
				| FORMAT_MESSAGE_FROM_SYSTEM,
				NULL,
				errnum,
				LANG_NEUTRAL,
				(LPTSTR)&lpBuffer,
				0,
				NULL );

			wsprintf(errbuf, "\nThe following call failed at line %d in %s:\n\n"
				"    %s\n\nReason: %s\n", lineno, filename, linedesc, lpBuffer);

			GetModuleFileName(NULL, modulename, MAX_PATH);
			MessageBox(NULL, errbuf, modulename, MB_ICONWARNING|MB_OK|MB_TASKMODAL|MB_SETFOREGROUND);

			exit(EXIT_FAILURE);
		}

	
	};


#define VG_ASYN_ASSERT(a) _ASSERTE(a)
	
#define VG_ASYN_VERIFY(a) if (!(a)) AsynUtility::checkFatalError(#a,__FILE__,__LINE__,GetLastError())

	
	
}// end of namespace vgAsyn

#endif // end of __VGAASYNUTILITY_H__
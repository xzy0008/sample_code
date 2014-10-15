



#ifndef __VGUSDEFINITION_H__
#define __VGUSDEFINITION_H__

#include <vgKernel/vgkForward.h>

	

#define VGUS_DESC  "vgUserInterfaceDLL"

#ifdef VGUS_DLL
#	ifdef VGUS_NONCLIENT_BUILD_DLL
#		define  VGUS_EXPORT __declspec( dllexport )
#	else
#		define  VGUS_EXPORT __declspec( dllimport )
#	endif
#else
#	define  VGUS_EXPORT VGK_EXPORT
#endif




#	ifdef _DEBUG
#		define  VGUS_DLL_NAME VGUS_DESC##"_Debug.dll"
#		define  VGUS_LIB_NAME VGUS_DESC##"_Debug.lib"
#	else
#		define  VGUS_DLL_NAME VGUS_DESC##"_Release.dll"
#		define  VGUS_LIB_NAME VGUS_DESC##"_Release.lib"
#	endif




namespace vgUserInterface
{
	class TreePanel;
	class AbstractEntry;
	class GuiManager;
	class OutputPanel;
	class TreePanel;
	class EntryManager;
	class DefaultEntry;
	class DefaultEntryGroup;
	class PropertiesPanel;
	class AbstractGuiFactory;
	class PropertyItem;
	class AbstractEntryFactory;
};
	


#endif // end of __VGUSDEFINITION_H__



#ifndef __VGCHANDEFINITION_H__
#define __VGCHANDEFINITION_H__

#include <vgKernel/vgkForward.h>




#define VGCHAN_DESC  "vgChannelDLL"

#ifdef VGCHAN_DLL
#	ifdef VGCHAN_NONCLIENT_BUILD_DLL
#		define  VGCHAN_EXPORT __declspec( dllexport )
#	else
#		define  VGCHAN_EXPORT __declspec( dllimport )
#	endif
#else
#	define  VGCHAN_EXPORT VGK_EXPORT
#endif




#	ifdef _DEBUG
#		define  VGCHAN_DLL_NAME VGCHAN_DESC##"_Debug.dll"
#		define  VGCHAN_LIB_NAME VGCHAN_DESC##"_Debug.lib"
#	else
#		define  VGCHAN_DLL_NAME VGCHAN_DESC##"_Release.dll"
#		define  VGCHAN_LIB_NAME VGCHAN_DESC##"_Release.lib"
#	endif

namespace vgChannel {

}



#ifdef __cplusplus
extern "C" {
#endif



	typedef bool (*pfnChannelManager_startChannel)( 
		int channelNum);
	extern VGCHAN_EXPORT  bool ChannelManager_startChannel( 
		int channelNum );

	typedef void (*pfnChannelManager_SetChannelFromFile)();
	extern VGCHAN_EXPORT  void ChannelManager_SetChannelFromFile();

	// 开启几何校正 Added By FengYK @2010-04-03 11:19
	typedef void (*pfnChannelManager_setBlendAndAdjustEnable)( 
		bool b_able );
	extern VGCHAN_EXPORT  void ChannelManager_setBlendAndAdjustEnable( 
		bool b_able );

	// 开启边缘融合
	typedef void (*pfnChannelManager_setEdgeBlendEnable)( 
		bool b_able );
	extern VGCHAN_EXPORT  void ChannelManager_setEdgeBlendEnable( 
		bool b_able );

#ifdef __cplusplus
}
#endif


#endif // end of __VGCHANDEFINITION_H__
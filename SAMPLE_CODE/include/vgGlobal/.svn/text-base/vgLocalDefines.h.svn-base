#ifndef	_VGLOCAL_DEFINES_H_INCLUDED_
#define	_VGLOCAL_DEFINES_H_INCLUDED_

//!  当前工程自定义. 
/*!
当前工程特定的宏或头文件包含.
*/

#define VGDEP_DESC "vgDeprecatedMFCDLL"

#ifdef VGDEP_DLL
#	ifdef VGDEP_NONCLIENT_BUILD
#		define  VGDEP_EXPORT __declspec( dllexport )
#	else
#		define  VGDEP_EXPORT __declspec( dllimport )
#	endif
#else
#	define  VGDEP_EXPORT
#endif


#ifdef VGDEP_DLL
#	ifdef _DEBUG
#		define  VGDEP_DLL_NAME VGDEP_DESC##"_Debug.dll"
#		define  VGDEP_LIB_NAME VGDEP_DESC##"_Debug.lib"
#	else
#		define  VGDEP_DLL_NAME VGDEP_DESC##"_Release.dll"
#		define  VGDEP_LIB_NAME VGDEP_DESC##"_Release.lib"
#	endif
#else
#	define  VGDEP_DLL_NAME
#	define VGDEP_LIB_NAME
#endif

//	vgKernel库
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkBox.h>
#include <vgKernel/vgkException.h>
#include <vgKernel/vgkCrcUtility.h>
#include <vgKernel/vgkLogManager.h>
#include <vgKernel/vgkMat4.h>
#include <vgKernel/vgkOpenGLSupport.h>
#include <vgKernel/vgkQuat.h>
#include <vgKernel/vgkSharePtr.h>
#include <vgKernel/vgkSingleton.h>
#include <vgKernel/vgkStreamReader.h>
#include <vgKernel/vgkStreamWriter.h>
#include <vgKernel/vgkStringUtility.h>
#include <vgKernel/vgkStringVector.h>
#include <vgKernel/vgkSystemUtility.h>
#include <vgKernel/vgkTrace.h>
#include <vgKernel/vgkUniqueID.h>
#include <vgKernel/vgkVec3.h>
#include <vgKernel/vgkWarning.h>

// vgMod库
#include <vgCore/vgPrerequisites.h>
#include <vgCore/vgSharedPtr.h>
#include <vgCore/vgSingleton.h>
//#include <vgTrace.h>
#include <vgCore/vgWarning.h>
#include <vgCore/vgException.h>
#include <vgCore/vgLog.h>
#include <vgCore/vgLogManager.h>
#include <vgMath/vgfStableHeaders.h>
#include <vgTex/tvgArchive.h>
#include <vgTex/tvgArchiveFactory.h>
#include <vgTex/tvgArchiveManager.h>
#include <vgTex/tvgArchiveSaver.h>
#include <vgTex/tvgBillboard.h>
#include <vgTex/tvgBillboardSet.h>
#include <vgTex/tvgDdsImage.h>
#include <vgTex/tvgFileStreamReader.h>
#include <vgTex/tvgGpuManager.h>
#include <vgTex/tvgGpuProgram.h>
#include <vgTex/tvgGpuSupport.h>
#include <vgTex/tvgImage.h>
#include <vgTex/tvgImageFactory.h>
#include <vgTex/tvgImagePos.h>
#include <vgTex/tvgImageRect.h>
#include <vgTex/tvgImageUtil.h>
#include <vgTex/tvgImageUtil.h>
#include <vgTex/tvgOpenGLSupport.h>
#include <vgTex/tvgStreamFactory.h>
#include <vgTex/tvgStreamReader.h>
#include <vgTex/tvgStreamWriter.h>
#include <vgTex/tvgString.h>
#include <vgTex/tvgTexture.h>
#include <vgTex/tvgTextureBuilder.h>
#include <vgTex/tvgTextureManager.h>
#include <vgTex/tvgWaterGpuProgram.h>
#include <vgTex/tvgZipArchive.h>
#include <vgTex/vgConvertUtil.h>


// vgPluginManager
#include <vgGlobal/vgglDefinition.h>


#endif//_VGLOCAL_DEFINES_H_INCLUDED_

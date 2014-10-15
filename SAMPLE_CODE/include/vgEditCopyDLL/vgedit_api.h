


#ifndef __VGEDITCOPYAPI_H__
#define __VGEDITCOPYAPI_H__

#include <vgKernel/vgkForward.h>

#ifdef __cplusplus
extern "C" {
#endif


	typedef bool (*pfnEditCopyManager_initialise)( HWND hWnd );

	extern VGEDITCOPY_EXPORT bool EditCopyManager_initialise(  HWND hWnd );

	typedef void (*pfnEditCopyManager_reset)();
	extern VGEDITCOPY_EXPORT void EditCopyManager_reset();

#ifdef __cplusplus
}
#endif

enum	AxisTypeEnum
{
	AXIS_NONE,
	AXIS_ONE	= 1,

	AXIS_X		= AXIS_ONE << 1,
	AXIS_Y		= AXIS_ONE << 2,
	AXIS_YX		= AXIS_Y | AXIS_X,
	AXIS_Z		= AXIS_ONE << 3,
	AXIS_ZX		= AXIS_Z | AXIS_X,
	AXIS_ZY		= AXIS_Z | AXIS_Y,
	AXIS_ZYX	= AXIS_Z | AXIS_Y | AXIS_X,
	AXIS_XMINUS = AXIS_ONE << 4,
	AXIS_YMINUS = AXIS_ONE << 5,
	AXIS_ZMINUS = AXIS_ONE << 6,

	AXIS_TYPE_COUNT
};

#endif // end of __VGSOUAPI_H__
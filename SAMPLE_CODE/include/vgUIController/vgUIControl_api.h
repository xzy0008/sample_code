




#ifndef __VGUICONTROL_API_H__
#define __VGUICONTROL_API_H__

#include <vgUIController/vgUIControlDefinition.h>

#ifdef __cplusplus
extern "C" {
#endif

	typedef void	(*pfnUIController_reset)();
	extern VGUI_EXPORT  void UIController_reset();

	typedef void	(*pfnUIController_initUIControl)();
	extern VGUI_EXPORT  void UIController_initUIControl();


#ifdef __cplusplus
}
#endif


#endif // end of __VGUICONTROL_API_H__

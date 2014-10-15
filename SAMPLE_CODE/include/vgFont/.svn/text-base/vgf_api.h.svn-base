/*! \file vglo_api.h
\brief 字体 模块接口函数
*/

#ifdef __cplusplus
extern "C" {
#endif

	/** \fn void FontManager_reset(）
	\brief 复位
	*/
	typedef void (*pfnFontManager_reset)();
	extern VGF_EXPORT void FontManager_reset();
	/** \fn void FontManager_initialiseFonts(HDC hDC)
	\brief 初始化字体
	\param hDC 设备上下文句柄
	*/
	typedef void (*pfnFontManager_initialiseFonts)(HDC hDC);
	extern VGF_EXPORT void FontManager_initialiseFonts(HDC hDC);
	/** \fn void FontManager_uninitBeforeOpenGLDestroy()
	\brief 在OpenGL销毁之前注销字体
	\param hDC 设备上下文句柄
	*/
	typedef void (*pfnFontManager_uninitBeforeOpenGLDestroy)();
	extern VGF_EXPORT void FontManager_uninitBeforeOpenGLDestroy();
	/** \fn void FontManager_getOriginX()
	\brief 得到字体的x坐标原点
	*/
	typedef float (*pfnFontManager_getOriginX)();
	extern VGF_EXPORT float FontManager_getOriginX();
	/** \fn void pfnFontManager_setOriginX(float x)
	\brief 设置x坐标原点
	\param x x坐标值
	*/
	typedef void (*pfnFontManager_setOriginX)(float x);
	extern VGF_EXPORT void FontManager_setOriginX(float x);
	/** \fn void FontManager_getOriginY()
	\brief 得到字体y坐标原点
	*/
	typedef float (*pfnFontManager_getOriginY)();
	extern VGF_EXPORT float FontManager_getOriginY();
	/** \fn void FontManager_setOriginY(float y)
	\brief 设置y坐标原点
	\param y y坐标原点
	*/
	typedef void (*pfnFontManager_setOriginY)(float y);
	extern VGF_EXPORT void FontManager_setOriginY(float y);
	/** \fn void FontManager_getFontSize()
	\brief 得到字体大小
	*/
	typedef float (*pfnFontManager_getFontSize)();
	extern VGF_EXPORT float FontManager_getFontSize();
	/** \fn void FontManager_setFontSize(float fontSize)
	\brief 设置字体大小
	\param fontSize 字体大小
	*/
	typedef void (*pfnFontManager_setFontSize)(float fontSize);
	extern VGF_EXPORT void FontManager_setFontSize(float fontSize);
	/** \fn void FontManager_setDefaultDiaplay(String& str)
	\brief 设置要显示的文字
	\param str 要显示的字符串
	*/
	typedef void (*pfnFontManager_setDefaultDisplay)(String& str );
	extern VGF_EXPORT void FontManager_setDefaultDiaplay(String& str);
	/** \fn void FontManager_rebuildFontSize(int fontSize)
	\brief 重设字体大小
	\param fontSize 字体大小
	*/
	typedef void (*pfnFontManager_rebuildFontSize)(int fontSize);
	extern VGF_EXPORT void FontManager_rebuildFontSize(int fontSize);
	/** \fn void FontManager_drawNumber(float h)
	\brief 设置要渲染的数字
	\param h 所要显示的数字
	*/
	typedef void (*pfnFontManager_drawNumber)(float h);
	extern VGF_EXPORT void FontManager_drawNumber(float h);
	/** \fn void FontManager_drawString(const std::string& str)
	\brief 设置要渲染的文字
	\param str 所要显示的文字
	*/
	typedef void(*pfnFontManager_drawString)(const std::string& str);
	extern VGF_EXPORT void FontManager_drawString(const std::string& str);
	/** \fn void FontManager_splitToMultiLine(const std::string &str)
	\brief 多行显示文字
	\param str 所要显示的文字
	*/
	typedef vgKernel::StringVector* (*pfnFontManager_splitToMultiLine)(const std::string &str);
	extern VGF_EXPORT vgKernel::StringVector* FontManager_splitToMultiLine(const std::string &str);


#ifdef __cplusplus
}
#endif

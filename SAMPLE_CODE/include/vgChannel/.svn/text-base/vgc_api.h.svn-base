/*! \file vglo_api.h
\brief 字体 模块接口函数
*/

#ifdef __cplusplus
extern "C" {
#endif

	/** \fn bool renderBegin()
	\brief 开始渲染
	*/
	typedef bool (*pfnrenderBegin)();
	extern VGF_EXPORT bool renderBegin();

	/** \fn bool clientRenderBegin()
	\brief 客户端开始渲染
	*/
	typedef bool (*pfnclientRenderBegin)();
	extern VGF_EXPORT bool clientRenderBegin();

	/** \fn bool serverRenderBegin()
	\brief 服务器端开始渲染
	*/
	typedef bool (*pfnserverRenderBegin)();
	extern VGF_EXPORT bool serverRenderBegin();

	/** \fn bool renderEnd()
	\brief 结束渲染
	*/
	typedef bool (*pfnrenderEnd)();
	extern VGF_EXPORT bool renderEnd();

	/** \fn void blendAndAdujst()
	\brief 几何校正
	*/
	typedef void (*pfnblendAndAdjust)();
	extern VGF_EXPORT void blendAndAdjust();

	/** \fn void setScreenSize()
	\brief 设置屏幕大小
	\x y 屏幕大小的坐标数
	*/
	typedef void (*pfnsetScreenSize)();
	extern VGF_EXPORT void setScreenSize(int x, int y);

	/** \fn void FontManager_setOriginY(float y)
	\brief 设置y坐标原点
	\param y y坐标原点
	*/
	//typedef void (*pfnFontManager_setOriginY)(float y);
	//extern VGF_EXPORT void FontManager_setOriginY(float y);
	/** \fn void FontManager_getFontSize()
	\brief 得到字体大小
	*/
	//typedef float (*pfnFontManager_getFontSize)();
	//extern VGF_EXPORT float FontManager_getFontSize();
	/** \fn void FontManager_setFontSize(float fontSize)
	\brief 设置字体大小
	\param fontSize 字体大小
	*/
	//typedef void (*pfnFontManager_setFontSize)(float fontSize);
	//extern VGF_EXPORT void FontManager_setFontSize(float fontSize);
	/** \fn void FontManager_rebuildFontSize(int fontSize)
	\brief 重设字体大小
	\param fontSize 字体大小
	*/
	//typedef void (*pfnFontManager_rebuildFontSize)(int fontSize);
	//extern VGF_EXPORT void FontManager_rebuildFontSize(int fontSize);
	/** \fn void FontManager_drawNumber(float h)
	\brief 设置要渲染的数字
	\param h 所要显示的数字
	*/
	//typedef void (*pfnFontManager_drawNumber)(float h);
	//extern VGF_EXPORT void FontManager_drawNumber(float h);
	/** \fn void FontManager_drawString(const std::string& str)
	\brief 设置要渲染的文字
	\param str 所要显示的文字
	*/
	//typedef void(*pfnFontManager_drawString)(const std::string& str);
	//extern VGF_EXPORT void FontManager_drawString(const std::string& str);
	/** \fn void FontManager_splitToMultiLine(const std::string &str)
	\brief 多行显示文字
	\param str 所要显示的文字
	*/
	//typedef vgKernel::StringVector* (*pfnFontManager_splitToMultiLine)(const std::string &str);
	//extern VGF_EXPORT vgKernel::StringVector* FontManager_splitToMultiLine(const std::string &str);


#ifdef __cplusplus
}
#endif

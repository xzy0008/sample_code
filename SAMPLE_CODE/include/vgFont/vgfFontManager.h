#ifndef _VGFONT_H_INCLUDED_
#define _VGFONT_H_INCLUDED_

#include <vgFont/vgfDefinition.h>

#include <vgKernel/vgkSingleton.h>


namespace vgFont
{

	class  VGF_EXPORT FontManager: 
		public vgKernel::Singleton<FontManager>
	{
		friend class vgKernel::Singleton<FontManager>;
	//成员函数
	public :
		FontManager();
		virtual ~FontManager();

	protected:
		virtual bool initialise()
		{
			return true;
		}
		virtual bool shutdown()
		{
			return true;
		}

	protected:
		String	_defaultDisplay;

	public :
		void reset();


		void initialiseFonts(HDC hDC);	

		void uninitBeforeOpenGLDestroy();

		float	getOriginX();
		void	setOriginX(float x);
		float	getOriginY();
		void	setOriginY(float y);
		float	getFontSize();
		void	setFontSize(float fontSize);

		void rebuildFontSize(int fontSize);	

		void	setDefaultDisplay(String& str);		
		
		void drawNumber(float h);
		void drawString( const std::string& str);

		vgKernel::StringVector*	splitToMultiLine( const std::string& str );

	private:

		void KillFont(void);
		void   PrintfText (LPCTSTR lpszText, int x = 0, int y =0/*,HFONT hFont*/);
		void   PrintfText (std::string str, float x = 0.0f, float y =0.0f);
		void glPrint(const char *fmt, ...);

	private:

		int		_maxLineWidth;
		float	_originX ,_originY;
		int		_fontSize;
		HFONT	_font;										// Windows Font ID
		HDC		_hDC;
		GLuint	_fontLists;				// Base Display List For The Font Set

	}; 
}//vgFont命名空间


#endif//_VGMGIS_H_INCLUDED_
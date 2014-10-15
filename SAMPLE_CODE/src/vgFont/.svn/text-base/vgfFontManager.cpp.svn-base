

#include <vgStableHeaders.h>
#include "vgFont/vgfFontManager.h"

#include <vgKernel/vgkStringUtility.h>




namespace vgFont//vgFont命名空间
{


	FontManager::FontManager()
		:Singleton<FontManager>(VGK_SINGLETON_LEFE_FONT)
	{
		_maxLineWidth = 11;
		_originX = 0.25f;	
		_originY = 0.35f;
		_fontSize= 40;

		_font = NULL;
		_hDC = NULL;
	}
	FontManager::~FontManager()
	{

	}
	void FontManager::initialiseFonts(HDC hDC)								// Build Our Bitmap Font
	{
		_hDC = hDC;
		HFONT	oldfont;									// Used For Good House Keeping

		_fontLists = glGenLists(96);								// Storage For 96 Characters

		_font = CreateFont(	_fontSize/*-24*/,							// Height Of Font
			0,								// Width Of Font
			0,								// Angle Of Escapement
			0,								// Orientation Angle
			FW_BOLD,						// Font Weight
			FALSE,							// Italic
			FALSE,							// Underline
			FALSE,							// Strikeout
			ANSI_CHARSET,					// Character Set Identifier
			OUT_TT_PRECIS,					// Output Precision
			CLIP_DEFAULT_PRECIS,			// Clipping Precision
			ANTIALIASED_QUALITY,			// Output Quality
			FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
			"Courier New");					// Font Name
			//"Arial");					// Font Name

		oldfont = (HFONT)SelectObject(hDC, _font);           // Selects The Font We Want
		wglUseFontBitmaps(hDC, 32, 96, _fontLists);				// Builds 96 Characters Starting At Character 32
		SelectObject(_hDC, oldfont);							// Selects The Font We Want
		//DeleteObject(_font);									// Delete The Font
	}
	void FontManager::rebuildFontSize(int fontSize)								// Build Our Bitmap Font
	{
		if (_font)
		{
			DeleteObject(_font);
		}

		_fontSize = fontSize;

		HFONT	oldfont;									// Used For Good House Keeping

		_font = CreateFont(	_fontSize/*-24*/,							// Height Of Font
			0,								// Width Of Font
			0,								// Angle Of Escapement
			0,								// Orientation Angle
			FW_BOLD,						// Font Weight
			FALSE,							// Italic
			FALSE,							// Underline
			FALSE,							// Strikeout
			ANSI_CHARSET,					// Character Set Identifier
			OUT_TT_PRECIS,					// Output Precision
			CLIP_DEFAULT_PRECIS,			// Clipping Precision
			ANTIALIASED_QUALITY,			// Output Quality
			FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
			"Courier New");					// Font Name
		//"Arial");					// Font Name

		oldfont = (HFONT)SelectObject(_hDC, _font);           // Selects The Font We Want
		SelectObject(_hDC, oldfont);							// Selects The Font We Want
	}
	void FontManager::drawNumber(float h)
	{
		glPushAttrib(GL_CURRENT_BIT);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_TEXTURE_1D);
			glLoadIdentity();									// Reset The Current Modelview Matrix
			glTranslatef(0.0f,0.0f,-1.0f);						// Move One Unit Into The Screen
			glColor3f(255,255,255);                                                                                                                                                              
			glRasterPos2f(0.2f, 0.35f);
			glPrint("%.2f M",h);	// Print GL Text To The Screen	
		glEnable(GL_TEXTURE_1D);
		glEnable(GL_TEXTURE_2D);
		glPopAttrib();
	}

	void FontManager::glPrint(const char *fmt, ...)		// Custom GL "Print" Routine
	{
		char		text[256];								// Holds Our String
		va_list		ap;										// Pointer To List Of Arguments

		if (fmt == NULL)									// If There's No Text
			return;											// Do Nothing

		va_start(ap, fmt);									// Parses The String For Variables
			vsprintf(text, fmt, ap);						// And Converts Symbols To Actual Numbers
		va_end(ap);											// Results Are Stored In Text

		glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
		glListBase(_fontLists - 32);								// Sets The Base Character to 32
		glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
		glPopAttrib();										// Pops The Display List Bits
	}
	void FontManager::KillFont(void)									// Delete The Font List
	{
		glDeleteLists(_fontLists, 96);							// Delete All 96 Characters
		DeleteObject(_font);									// Delete The Font

	}

	void FontManager::drawString( const std::string& str )
	{
		// 拆分多行
		vgKernel::StringVector*	newMultiLineText
			= splitToMultiLine(str);

		glPushMatrix();

		glPushAttrib(GL_CURRENT_BIT);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_TEXTURE_1D);
		glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
		glLoadIdentity();									// Reset The Current Modelview Matrix
		glTranslatef(0.0f,0.0f,-1.0f);						// Move One Unit Into The Screen
		//glColor3f(255,255,255);                                                                                                                                                              
		glColor3f( 1.0f, 0.0f, 0.0f);                                                                                                                                                              
		//glRasterPos2f(0.2,0.35);
			
		int lineIndex = 0;
		for (vgKernel::StringVector::iterator itr = newMultiLineText->begin();
			itr != newMultiLineText->end();
			itr ++)
		{
			lineIndex ++  ;
			//glPrint("%s", itr->c_str());	// Print GL Text To The Screen	
			PrintfText( *itr , 0.0f, lineIndex * 0.025f);
		}
		
			
		glEnable(GL_TEXTURE_1D);
		glEnable(GL_TEXTURE_2D);
		glPopAttrib();

		glPopMatrix();

	}
	
	//////////////////////////////////////////////////////////////////////////
	void FontManager::PrintfText (LPCTSTR lpszText, int x, int y/*,HFONT hFont*/)
	{ 
		CBitmap bitmap;									//设备相关位图变量
		BITMAP bm;                                        //位图结构变量
		SIZE size;                                        //位图尺寸
		HDC MDC = ::CreateCompatibleDC(0);				//暂存设备场景
		//SelectObject(MDC,hFont);							//选择新字体
		::GetTextExtentPoint32(MDC,lpszText,strlen(lpszText),&size);//获取字符位图大小
		bitmap.CreateBitmap(size.cx, size.cy, 1, 1, NULL);//创建与MDC相关单色位图
		
		HBITMAP oldBmp=(HBITMAP)SelectObject(MDC,bitmap); //字符位图与MDC关连
		SetBkColor  (MDC, RGB(0,     0,   0));			//底色，黑色
		SetTextColor(MDC, RGB(255, 255, 255));			//字色，白色
		TextOut(MDC, 0, 0, lpszText, strlen(lpszText));	//输出文字到暂存MDC
		bitmap.GetBitmap(&bm);							//获得相关位图数据结构
		size.cx = (bm.bmWidth + 31) & (~31);				//边缘对齐
		int bufsize =size.cy * size.cx;					//图形数据长度
		
		struct {  BITMAPINFOHEADER bih;
		RGBQUAD col[2];
		}bic;                                      //定义单色位图结构
		
		BITMAPINFO *binf = (BITMAPINFO *)&bic;            //获取位图结构信息
		binf->bmiHeader.biSize     = sizeof(binf->bmiHeader);//
		binf->bmiHeader.biWidth    = bm.bmWidth;			//图形宽
		binf->bmiHeader.biHeight   = bm.bmHeight;			//图形高
		binf->bmiHeader.biPlanes   = 1;                   //
		binf->bmiHeader.biBitCount = 1;                   //单色
		binf->bmiHeader.biCompression = BI_RGB;           //颜色方式
		binf->bmiHeader.biSizeImage   = bufsize;          //图形数据长度
		UCHAR* Bits = new UCHAR[bufsize];					//定义图形数据块变量
		::GetDIBits(MDC,bitmap,0,bm.bmHeight,Bits,binf,DIB_RGB_COLORS); 
		//取设备无关数据到Bits
		glPixelStorei(GL_UNPACK_ALIGNMENT ,1);			//控制像素存储
//		glRasterPos2i(x,y);                               //平面定位
		glBitmap(size.cx,size.cy,0,0,0,0,Bits);           //平面位图显示
		delete Bits;                                      //删除Bits
		SelectObject(MDC, oldBmp);                        //恢复位图特性
		::DeleteDC(MDC);                                  //删除设备场景
	}

	void FontManager::PrintfText (std::string str, float dx /*= 0.0f*/, float dy/* =0.0f*/)
	{ 
		if (str.empty())
		{
			return;
		}


		glRasterPos2f(_originX + dx,_originY - dy);

		CBitmap bitmap;									//设备相关位图变量
		BITMAP bm;                                        //位图结构变量
		SIZE size;                                        //位图尺寸
		HDC MDC = ::CreateCompatibleDC(0);				//暂存设备场景
		SelectObject(MDC,_font);							//选择新字体
		::GetTextExtentPoint32(MDC, str.c_str(), str.length(), &size);//获取字符位图大小
		bitmap.CreateBitmap(size.cx, size.cy, 1, 1, NULL);//创建与MDC相关单色位图

		HBITMAP oldBmp=(HBITMAP)SelectObject(MDC,bitmap); //字符位图与MDC关连
		SetBkColor  (MDC, RGB(0,     0,   0));			//底色，黑色
		SetTextColor(MDC, RGB(255, 255, 255));			//字色，白色
		TextOut(MDC, 0, 0, str.c_str(), str.length() );	//输出文字到暂存MDC
		bitmap.GetBitmap(&bm);							//获得相关位图数据结构
		size.cx = (bm.bmWidth + 31) & (~31);				//边缘对齐
		int bufsize =size.cy * size.cx;					//图形数据长度

		struct {  BITMAPINFOHEADER bih;
		RGBQUAD col[2];
		}bic;                                      //定义单色位图结构

		BITMAPINFO *binf = (BITMAPINFO *)&bic;            //获取位图结构信息
		binf->bmiHeader.biSize     = sizeof(binf->bmiHeader);//
		binf->bmiHeader.biWidth    = bm.bmWidth;			//图形宽
		binf->bmiHeader.biHeight   = bm.bmHeight;			//图形高
		binf->bmiHeader.biPlanes   = 1;                   //
		binf->bmiHeader.biBitCount = 1;                   //单色
		binf->bmiHeader.biCompression = BI_RGB;           //颜色方式
		binf->bmiHeader.biSizeImage   = bufsize;          //图形数据长度
		UCHAR* Bits = new UCHAR[bufsize];					//定义图形数据块变量
		::GetDIBits(MDC,bitmap,0,bm.bmHeight,Bits,binf,DIB_RGB_COLORS); 
		//取设备无关数据到Bits
		glPixelStorei(GL_UNPACK_ALIGNMENT ,1);			//控制像素存储
		//		glRasterPos2i(x,y);                               //平面定位
		glBitmap(size.cx,size.cy,0,0,0,0,Bits);           //平面位图显示
		delete Bits;                                      //删除Bits
		SelectObject(MDC, oldBmp);                        //恢复位图特性
		::DeleteDC(MDC);                                  //删除设备场景
	}

	vgKernel::StringVector* FontManager::splitToMultiLine( const std::string& str )
	{
		vgKernel::StringVector	multiLineText
			= vgKernel::StringUtility::split(str, String("&"));

		vgKernel::StringVector*	newMultiLineTextSameLength 
			= new	vgKernel::StringVector;

		for (vgKernel::StringVector::iterator itr = multiLineText.begin();
			itr != multiLineText.end();
			itr ++)
		{
			newMultiLineTextSameLength->push_back(*itr);
			/*if ( itr->length() <= _maxLineWidth)
			{
				newMultiLineTextSameLength->push_back(*itr);
			}
			else
			{
				int newLinePos = 0, tempPos = 0;
				String	oneLineText;

				tempPos += _maxLineWidth;
				while( tempPos < itr->length())
				{	
					oneLineText = str.substr(newLinePos, tempPos - newLinePos);
					newMultiLineTextSameLength->push_back(oneLineText);
					
					newLinePos = tempPos + 1;
					tempPos += _maxLineWidth;
				} ;
				oneLineText = str.substr(newLinePos);
				newMultiLineTextSameLength->push_back(oneLineText);
			}*/
		}		

		return	newMultiLineTextSameLength;
	}

	float FontManager::getOriginX()
	{
		return _originX;
	}

	void FontManager::setOriginX( float x )
	{
		_originX = x;
	}

	float FontManager::getOriginY()
	{
		return _originY;
	}

	void FontManager::setOriginY( float y )
	{
		_originY = y;
	}

	float FontManager::getFontSize()
	{
		return _fontSize;
	}

	void FontManager::setFontSize( float fontSize )
	{
		_fontSize = fontSize;
	}

	void FontManager::setDefaultDisplay( String& str )
	{
		_defaultDisplay = str;
	}

	void FontManager::uninitBeforeOpenGLDestroy()
	{
		KillFont();
	}

	void FontManager::reset()
	{
		KillFont();

		_maxLineWidth = 11;
		_originX = 0.25f;	
		_originY = 0.35f;
		_fontSize= 40;
	}
}//vgFont命名空间结束


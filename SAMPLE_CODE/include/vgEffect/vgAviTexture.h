// AviTexture.h: interface for the AviTexture class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AVITEXTURE_H__7943A9A3_15D7_4FD7_8DC2_F245DA84E41A__INCLUDED_)
#define AFX_AVITEXTURE_H__7943A9A3_15D7_4FD7_8DC2_F245DA84E41A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vfw.h>
#pragma comment( lib, "vfw32.lib" )

class AviTexture  
{
public:
	AviTexture(string FileName);
	virtual ~AviTexture();
	int Update (bool bNeed);	// Perform Motion Updates
	void GrabAVIFrame(int frame);
	void flipIt(void* buffer);
	bool OpenAVI();
	void CloseAVI();

	bool init();

public:
	string szAviFile;
	int next;
	int frame;
	/*static */
	int lastTickCount;
	int newTickCount;

	GLuint				_glTextureID;


	AVISTREAMINFO		psi;			// Pointer To A Structure Containing Stream Info
	PAVISTREAM			pavi;			// Handle To An Open Stream
	PGETFRAME			pgf;			// Pointer To A GetFrame Object
	BITMAPINFOHEADER	bmih;			// Header Information For DrawDibDraw Decoding
	long				lastframe;		// Last Frame Of The Stream
	int					width;			// Video Width
	int					height;			// Video Height
	char				*pdata;			// Pointer To Texture Data
	int					mpf;			// Will Hold Rough Milliseconds Per Frame
	
	HDRAWDIB hdd;													// Handle For Our Dib
	HBITMAP hBitmap;												// Handle To A Device Dependant Bitmap
	HDC hdc ;								// Creates A Compatible Device Context
	unsigned char* data ;										// Pointer To Our Resized Image

};

#endif // !defined(AFX_AVITEXTURE_H__7943A9A3_15D7_4FD7_8DC2_F245DA84E41A__INCLUDED_)

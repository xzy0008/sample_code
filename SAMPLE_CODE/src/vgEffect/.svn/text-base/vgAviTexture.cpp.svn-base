// AviTexture.cpp: implementation of the AviTexture class.
//
//////////////////////////////////////////////////////////////////////

#include <vgStableHeaders.h>
#include "vgeffect/vgAviTexture.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AviTexture::AviTexture(string FileName)
{
	szAviFile=FileName;

	_glTextureID = 0;
}

AviTexture::~AviTexture()
{

}
void AviTexture::CloseAVI()
{	
	DeleteObject(hBitmap);										// Delete The Device Dependant Bitmap Object
	DrawDibClose(hdd);											// Closes The DrawDib Device Context
	AVIStreamGetFrameClose(pgf);								// Deallocates The GetFrame Resources
	AVIStreamRelease(pavi);										// Release The Stream
	AVIFileExit();		

}
int AviTexture::Update (bool bNeed)
{
	newTickCount=GetTickCount ();	

	if ( !bNeed )
	{
		lastTickCount=newTickCount;
		return frame;
	}

	int milliseconds=newTickCount-lastTickCount;
	lastTickCount=newTickCount;
	next+=milliseconds;											// Increase next Based On The Timer
	frame=next/mpf;												// Calculate The Current Frame
	
	if (frame>=lastframe)										// Are We At Or Past The Last Frame?
	{
		frame=0;												// Reset The Frame Back To Zero (Start Of Video)
		next=0;													// Reset The Animation Timer (next)
	}
	return frame;
}
void AviTexture::GrabAVIFrame(int frame)
{
	LPBITMAPINFOHEADER lpbi;									// Holds The Bitmap Header Information
	lpbi = (LPBITMAPINFOHEADER)AVIStreamGetFrame(pgf, frame);	// Grab Data From The AVI Stream
	pdata=(char *)lpbi+lpbi->biSize+lpbi->biClrUsed * sizeof(RGBQUAD);	// Pointer To Data Returned By AVIStreamGetFrame
	
	// Convert Data To Requested Bitmap Format
	DrawDibDraw (hdd, hdc, 0, 0, 256, 256, lpbi, pdata, 0, 0, width, height, 0);
	
	flipIt(data);												// Swap The Red And Blue Bytes (GL Compatability)
	

	assert( _glTextureID != 0 );
	glBindTexture( GL_TEXTURE_2D , _glTextureID );

	// Update The Texture
	glTexSubImage2D (GL_TEXTURE_2D, 0, 0, 0, 256, 256, GL_RGB, GL_UNSIGNED_BYTE, data);

}
bool AviTexture::OpenAVI()										// Opens An AVI File (szFile)
{
	
	AVIFileInit();												// Opens The AVIFile Library
	
	// Opens The AVI Stream
	if (AVIStreamOpenFromFile(&pavi, szAviFile.c_str(), streamtypeVIDEO, 0, OF_READ, NULL) !=0)
	{
		std::ostringstream o;
		o << "Failed To Open The AVI Stream: " <<szAviFile;
		// An Error Occurred Opening The Stream
		MessageBox (HWND_DESKTOP, o.str().c_str(), "Error", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	
	AVIStreamInfo(pavi, &psi, sizeof(psi));						// Reads Information About The Stream Into psi
	width=psi.rcFrame.right-psi.rcFrame.left;					// Width Is Right Side Of Frame Minus Left
	height=psi.rcFrame.bottom-psi.rcFrame.top;					// Height Is Bottom Of Frame Minus Top
	
	lastframe=AVIStreamLength(pavi);							// The Last Frame Of The Stream
	
	mpf=AVIStreamSampleToTime(pavi,lastframe)/lastframe;		// Calculate Rough Milliseconds Per Frame
	

	
	hBitmap = CreateDIBSection (hdc, (BITMAPINFO*)(&bmih), DIB_RGB_COLORS, (void**)(&data), NULL, NULL);
	SelectObject (hdc, hBitmap);								// Select hBitmap Into Our Device Context (hdc)
	
	pgf=AVIStreamGetFrameOpen(pavi, NULL);						// Create The PGETFRAME	Using Our Request Mode
	if (pgf==NULL)
	{
		// An Error Occurred Opening The Frame
		MessageBox (HWND_DESKTOP, "Failed To Open The AVI Frame", "Error", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	return true;
	
}
void AviTexture::flipIt(void* buffer)										// Flips The Red And Blue Bytes (256x256)
{
	void* b = buffer;											// Pointer To The Buffer
	__asm														// Assembler Code To Follow
	{
		mov ecx, 256*256										// Counter Set To Dimensions Of Our Memory Block
			mov ebx, b												// Points ebx To Our Data (b)
label:													// Label Used For Looping
		mov al,[ebx+0]										// Loads Value At ebx Into al
			mov ah,[ebx+2]										// Loads Value At ebx+2 Into ah
			mov [ebx+2],al										// Stores Value In al At ebx+2
			mov [ebx+0],ah										// Stores Value In ah At ebx
			
			add ebx,3											// Moves Through The Data By 3 Bytes
			dec ecx												// Decreases Our Loop Counter
			jnz label											// If Not Zero Jump Back To Label
	}
}

bool AviTexture::init()
{
	next=0;
	frame=0;
	lastTickCount=GetTickCount ();

	hdc = CreateCompatibleDC(0);
	data = 0;

	bmih.biSize = sizeof (BITMAPINFOHEADER);					// Size Of The BitmapInfoHeader
	bmih.biPlanes = 1;											// Bitplanes	
	bmih.biBitCount = 24;										// Bits Format We Want (24 Bit, 3 Bytes)
	bmih.biWidth = 256;											// Width We Want (256 Pixels)
	bmih.biHeight = 256;										// Height We Want (256 Pixels)
	bmih.biCompression = BI_RGB;								// Requested Mode = RGB

	hdd = DrawDibOpen();										// Grab A Device Context For Our Dib

	bool ret = OpenAVI();									// Open The AVI File

	if ( ret == false )
	{
		return false;
	}

	//------------------------------------------
	// ´´½¨ÎÆÀí
	//------------------------------------------

	glEnable(GL_TEXTURE_2D);	
	assert( _glTextureID == 0 );

	glGenTextures( 1, &_glTextureID );

	assert( _glTextureID != 0 );
	glBindTexture( GL_TEXTURE_2D , _glTextureID );

									// Enable Texture Mapping
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);	// Set Texture Max Filter
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);	// Set Texture Min Filter

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);		// Set The Texture Generation Mode For S To Sphere Mapping
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);		// Set The Texture Generation Mode For T To Sphere Mapping

	// Create The Texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	return true;
}
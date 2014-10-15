
#include "stdafx.h"
#include "IPictureLoader.h"
#include <olectl.h>

IPictureLoader::IPictureLoader(HDC hDC) : m_imageData(NULL), m_hDC(hDC), m_imageWidth(0), m_imageHeight(0)
{

}

IPictureLoader::~IPictureLoader()
{
   if (m_imageData) delete [] m_imageData; m_imageData = NULL;
}

GLboolean IPictureLoader::LoadFromFile(const char* imagePath)
{
   OLECHAR     uniPath[MAX_PATH+1];
   //char        filePath[MAX_PATH+1];
   IPicture*   imagePicture;

   // add the emage path to the current directory
 /*  GetCurrentDirectory(MAX_PATH, (LPWSTR)filePath);
   strcat(filePath, "\\");
   strcat(filePath, imagePath);*/

   // convert to unicode
   MultiByteToWideChar(CP_ACP, NULL, imagePath, -1, uniPath, MAX_PATH);

   // load the image
   HRESULT hRes = OleLoadPicturePath(uniPath, NULL, NULL, NULL, IID_IPicture, (void**)&imagePicture);

   if (FAILED(hRes))
      return false;

   // create a temporary bitmap to store the image in
   HDC hTempDC = CreateCompatibleDC(m_hDC);

   if (!hTempDC)
   {
      // clean up
      imagePicture->Release();
      return false;
   }

   // get the image dimensions
   long pictWidth   = 0;
   long pictHeight  = 0;
   long pixelWidth  = 0;
   long pixelHeight = 0;

   imagePicture->get_Width(&pictWidth);
   pixelWidth = MulDiv(pictWidth, GetDeviceCaps(hTempDC, LOGPIXELSX), 2540);
   m_imageWidth  = (GLuint)pixelWidth;

   imagePicture->get_Height(&pictHeight);
   pixelHeight = MulDiv(pictHeight, GetDeviceCaps(hTempDC, LOGPIXELSY), 2540);
   m_imageHeight = (GLuint)pixelHeight;

   BITMAPINFO Info;
   memset(&Info, 0, sizeof(Info));
   
   // create a 32 bit bitmap
   Info.bmiHeader.biSize         = sizeof(BITMAPINFOHEADER);
   Info.bmiHeader.biBitCount     = 32;
   Info.bmiHeader.biWidth        = pixelWidth;
   Info.bmiHeader.biHeight       = pixelHeight;
   Info.bmiHeader.biCompression  = BI_RGB;
   Info.bmiHeader.biPlanes       = 1;

   if (m_imageData) delete [] m_imageData; m_imageData = NULL;
   m_imageData = new GLuint[pixelWidth*pixelHeight*4];
   
   if (!m_imageData)
   {
      // clean up
      DeleteDC(hTempDC);
      imagePicture->Release();
   }

   DWORD* imageData = NULL;
   HBITMAP hBMP = CreateDIBSection(hTempDC, &Info, DIB_RGB_COLORS, (void**)&imageData, NULL, NULL);
   if (!hBMP)
   {
      // clean up
      DeleteDC(hTempDC);
      imagePicture->Release();

      return false;
   }
   
   // render into the bitmap
   SelectObject(hTempDC, hBMP);

   imagePicture->Render(hTempDC, 0, 0, pixelWidth, pixelHeight, 0, pictHeight, 
                        pictWidth, -pictWidth, 0);

   // copy the data
   GLuint imageSize = pixelWidth * pixelHeight;
   for (unsigned int j = 0; j < imageSize; j++)
   {
      m_imageData[j] = imageData[j];
   }

   // RGB to BGR with a 255 alpha channel
   for (unsigned int i = 0; i < imageSize; i++)
	{
		BYTE* pPixel	= (BYTE*)(&m_imageData[i]);
		BYTE  temp		= pPixel[0];
		pPixel[0]		= pPixel[2];
		pPixel[2]		= temp;
		pPixel[3]		= 255;
	}

   // clean up
   DeleteObject(hBMP);
   DeleteDC(hTempDC);
   imagePicture->Release();

   return true;
}

const GLuint* IPictureLoader::GetData(void) const
{
   return m_imageData;
}

const GLuint IPictureLoader::GetWidth(void) const
{
   return m_imageWidth;
}

const GLuint IPictureLoader::GetHeight(void) const
{
   return m_imageHeight;
}

const GLuint IPictureLoader::GetColourDepth(void) const
{
   return 32;
}

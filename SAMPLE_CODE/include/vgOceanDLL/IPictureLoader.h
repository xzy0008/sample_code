

#pragma once

#include <GL/gl.h>

class IPictureLoader  
{
public:
	IPictureLoader(HDC hDC);
	virtual ~IPictureLoader();

   GLboolean      LoadFromFile(const char* imagePath);
   const GLuint*  GetData(void) const;
   const GLuint   GetWidth(void) const;
   const GLuint   GetHeight(void) const;
   const GLuint   GetColourDepth(void) const;
private:
   GLuint*  m_imageData;
   HDC      m_hDC;
   GLuint   m_imageWidth;
   GLuint   m_imageHeight;
};

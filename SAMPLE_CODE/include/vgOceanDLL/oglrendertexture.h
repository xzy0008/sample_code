#ifndef __OGL_RENDER_TEXTURE_H__
#define __OGL_RENDER_TEXTURE_H__
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "VOdefinition.h"

//declare ---livenson 20081030
#define   WGL_NUMBER_PIXEL_FORMATS_ARB 0x2000   
typedef   bool   (APIENTRY   *   PFNGLGETPIXELFORMATATTRIBIVARBPROC )   (HDC   hdc,int   iPixelFormat,int   iLayerPlane,UINT   nAttributes,const   int   *piAttributes,int   *piValues);   
typedef   bool   (APIENTRY   *   PFNGLGETPIXELFORMATATTRIBFVARBPROC )   (HDC   hdc,int   iPixelFormat,int   iLayerPlane,UINT   nAttributes,const   int   *piAttributes,float   *pfValues);   
typedef   bool   (APIENTRY   *   PFNGLCHOOSEPIXELFORMATARBPROC )   (HDC   hdc,const   int   *piAttribIList,const   float   *pfAttribFList,UINT   nMaxFormats,int   *piFormats,UINT   *nNumFormats);   
/*extern PFNGLGETPIXELFORMATATTRIBIVARBPROC wglGetPixelFormatAttribivARB;  
extern PFNGLGETPIXELFORMATATTRIBFVARBPROC wglGetPixelFormatAttribfvARB;  
extern PFNGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;  */ 

//declare --livenson 20081030
typedef   HPBUFFERARB   (APIENTRY   *   PFNGLCREATEPBUFFERARBPROC )   (HDC   hDC,int   iPixelFormat,int   iWidth,int   iHeight,const   int   *piAttribList);   
typedef   HDC (APIENTRY   *   PFNGLGETPBUFFERDCARBPROC )   (HPBUFFERARB   hPbuffer);   
typedef   int (APIENTRY   *   PFNGLRELEASEPBUFFERDCARBPROC)   (HPBUFFERARB   hPbuffer,HDC   hDC);   
typedef   bool (APIENTRY   *   PFNGLDESTROYPBUFFERARBPROC )   (HPBUFFERARB   hPbuffer);   
typedef   bool (APIENTRY   *   PFNGLQUERYPBUFFERARB )   (HPBUFFERARB   hPbuffer,int   iAttribute,int   *piValue);   
//extern      PFNGLCREATEPBUFFERARBPROC wglCreatePbufferARB;   
//extern      PFNGLGETPBUFFERDCARBPROC wglGetPbufferDCARB;   
//extern      PFNGLRELEASEPBUFFERDCARBPROC wglReleasePbufferDCARB;   
//extern      PFNGLDESTROYPBUFFERARBPROC wglDestroyPbufferARB;   
//extern      PFNGLQUERYPBUFFERARB wglQueryPbufferARB;

//declare --livenson 20081030
typedef bool(APIENTRY * PFNGLRELEASETEXIMAGEARBPROC)(HPBUFFERARB, int);
typedef bool(APIENTRY * PFNGLBINDTEXIMAGEARBPROC)(HPBUFFERARB, int);
//extern PFNGLRELEASETEXIMAGEARBPROC wglReleaseTexImageARB;
//extern PFNGLBINDTEXIMAGEARBPROC wglBindTexImageARB;


namespace VR_Ocean
{
	class VO_EXPORT OglRenderTexture
	{    
	public:
		enum { MAX_ATTRIBS = 256, MAX_PFORMATS = 256 }; 

	public:
		HDC m_hWinDC;
		HDC m_hBufDC;
		HGLRC m_hWinGLRC;
		HGLRC m_hBufGLRC;
		HPBUFFERARB m_hpBuffer;

		PFNGLCREATEPBUFFERARBPROC wglCreatePbufferARB;
		PFNGLRELEASETEXIMAGEARBPROC wglReleaseTexImageARB;
		PFNGLBINDTEXIMAGEARBPROC wglBindTexImageARB;  
		PFNGLGETPBUFFERDCARBPROC wglGetPbufferDCARB;   
		PFNGLRELEASEPBUFFERDCARBPROC wglReleasePbufferDCARB;   
		PFNGLDESTROYPBUFFERARBPROC wglDestroyPbufferARB;   
		PFNGLQUERYPBUFFERARB wglQueryPbufferARB;
		PFNGLGETPIXELFORMATATTRIBIVARBPROC wglGetPixelFormatAttribivARB;  
		PFNGLGETPIXELFORMATATTRIBFVARBPROC wglGetPixelFormatAttribfvARB;  
		PFNGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB; 

	public:
		OglRenderTexture()
		{
			m_hWinDC = NULL;
			m_hBufDC = NULL;
			m_hWinGLRC = NULL;
			m_hBufGLRC = NULL;
			m_hpBuffer = NULL;

			wglGetPixelFormatAttribivARB=0;   
			wglGetPixelFormatAttribfvARB=0;   
			wglChoosePixelFormatARB = 0;  
			wglCreatePbufferARB =0;   
			wglGetPbufferDCARB = 0;   
			wglReleasePbufferDCARB = 0;   
			wglDestroyPbufferARB =0;   
			wglQueryPbufferARB =  0;  
			wglReleaseTexImageARB=0;
			wglBindTexImageARB = 0;  
		}

		bool Create(int nWidth, int nHeight)
		{    
			if (0==wglGetPixelFormatAttribivARB)
				wglGetPixelFormatAttribivARB=   (PFNGLGETPIXELFORMATATTRIBIVARBPROC )wglGetProcAddress("wglGetPixelFormatAttribivARB");   
			if (0==wglGetPixelFormatAttribfvARB)
				wglGetPixelFormatAttribfvARB=   (PFNGLGETPIXELFORMATATTRIBFVARBPROC )wglGetProcAddress("wglGetPixelFormatAttribfvARB");   
			if(0==wglChoosePixelFormatARB)
				wglChoosePixelFormatARB =   (PFNGLCHOOSEPIXELFORMATARBPROC )wglGetProcAddress("wglChoosePixelFormatARB"); 
			if (0==wglCreatePbufferARB)
				wglCreatePbufferARB =   (PFNGLCREATEPBUFFERARBPROC)wglGetProcAddress("wglCreatePbufferARB"); 
			if(0==wglGetPbufferDCARB)
				wglGetPbufferDCARB =   (PFNGLGETPBUFFERDCARBPROC)wglGetProcAddress("wglGetPbufferDCARB");   
			if(0==wglReleasePbufferDCARB)
				wglReleasePbufferDCARB =   (PFNGLRELEASEPBUFFERDCARBPROC)wglGetProcAddress("wglReleasePbufferDCARB");  
			if(0==wglDestroyPbufferARB)
				wglDestroyPbufferARB =   (PFNGLDESTROYPBUFFERARBPROC)wglGetProcAddress("wglDestroyPbufferARB"); 
			if(0==wglQueryPbufferARB)
				wglQueryPbufferARB =   (PFNGLQUERYPBUFFERARB)wglGetProcAddress("wglQueryPbufferARB"); 
			if(0==wglBindTexImageARB)
				wglBindTexImageARB =   (PFNGLBINDTEXIMAGEARBPROC)wglGetProcAddress("wglBindTexImageARB");  
			if(0==wglReleaseTexImageARB)
				wglReleaseTexImageARB=(PFNGLRELEASETEXIMAGEARBPROC)wglGetProcAddress("wglReleaseTexImageARB");
			// Record current context
			m_hWinDC = wglGetCurrentDC();
			m_hWinGLRC = wglGetCurrentContext();
			if(!m_hWinGLRC) return false;

			// Query for a suitable pixel format based on the specified mode.
			int     iAttributes[2*MAX_ATTRIBS];
			float   fAttributes[2*MAX_ATTRIBS];
			memset(iAttributes, 0, sizeof(int)*2*MAX_ATTRIBS);
			memset(fAttributes, 0, sizeof(float)*2*MAX_ATTRIBS);

			int nIndex = 0;
			iAttributes[nIndex++] = WGL_DRAW_TO_PBUFFER_ARB;
			iAttributes[nIndex++] = GL_TRUE;
			iAttributes[nIndex++] = WGL_BIND_TO_TEXTURE_RGBA_ARB;
			iAttributes[nIndex++] = GL_TRUE;

			unsigned int nFormats;  
			int pFormats[MAX_PFORMATS];
			wglChoosePixelFormatARB(m_hWinDC, iAttributes, fAttributes, MAX_PFORMATS, pFormats, &nFormats);//////////////////////////////
			//CHECKF(nFormats);

			// Choose the first one format
			int format = pFormats[0];

			// Set up the pbuffer attributes
			nIndex = 0;
			memset(iAttributes, 0, sizeof(int)*2*MAX_ATTRIBS);
			iAttributes[nIndex++] = WGL_TEXTURE_FORMAT_ARB;
			iAttributes[nIndex++] = WGL_TEXTURE_RGBA_ARB;
			iAttributes[nIndex++] = WGL_TEXTURE_TARGET_ARB;
			iAttributes[nIndex++] = WGL_TEXTURE_2D_ARB;
			iAttributes[nIndex++] = WGL_MIPMAP_TEXTURE_ARB;
			iAttributes[nIndex++] = TRUE;
			iAttributes[nIndex++] = WGL_PBUFFER_LARGEST_ARB;
			iAttributes[nIndex++] = FALSE;

			// Create the p-buffer.
			m_hpBuffer = wglCreatePbufferARB(m_hWinDC, format, nWidth, nHeight, iAttributes);//create p-buffer   --livenson 20081030

			if(m_hpBuffer)
			{    
				// Create p-buffer context
				m_hBufDC = wglGetPbufferDCARB(m_hpBuffer);////////////////////////////////////////////////////
				m_hBufGLRC = wglCreateContext(m_hBufDC);

				wglQueryPbufferARB(m_hpBuffer, WGL_PBUFFER_WIDTH_ARB, &nWidth);///////////////////////////////////////
				wglQueryPbufferARB(m_hpBuffer, WGL_PBUFFER_HEIGHT_ARB, &nHeight);

				// 仅使用 2D 模式
				wglMakeCurrent(m_hBufDC, m_hBufGLRC);
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				//glOrtho(0, nWidth, 0, nHeight, 0.0001, 10000);
				gluPerspective(45.0,1,0.001,1000000);
				glMatrixMode(GL_MODELVIEW);
				glEnable(GL_TEXTURE_2D);
				wglMakeCurrent(m_hWinDC, m_hWinGLRC);

				return true;
			}
			else return false;
		}

		void Destroy()
		{    
			if(m_hpBuffer)
			{    
				// Clean up all resource
				wglDeleteContext(m_hBufGLRC);
				wglReleasePbufferDCARB(m_hpBuffer, m_hBufDC);/////////////////////////////////////
				wglDestroyPbufferARB(m_hpBuffer);
				m_hBufDC = NULL;
				m_hBufGLRC = NULL;
				m_hpBuffer = NULL;
			}

			m_hWinDC = NULL;
			m_hWinGLRC = NULL;
		}

		bool BeginRender(GLuint texture)
		{
			if(m_hpBuffer  &&  m_hBufDC  &&  m_hBufGLRC)
			{
				// Record current context
				m_hWinDC = wglGetCurrentDC();
				m_hWinGLRC = wglGetCurrentContext();

				// Ensure this texture will be bound in EndRender!
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);

				// Release the pbuffer from the texture before render to it again!
				wglReleaseTexImageARB(m_hpBuffer, WGL_FRONT_LEFT_ARB); ////////////////////////////////

				// Switch to pbuffer context
				wglMakeCurrent(m_hBufDC, m_hBufGLRC);
				wglShareLists(m_hWinGLRC,m_hBufGLRC);// so that we can share textures between contexts---livenson 20081031
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glLoadIdentity();
				return true;
			}
			else return false;
		}

		void EndRender()
		{
			// Switch to original main window render context
			wglMakeCurrent(m_hWinDC, m_hWinGLRC);

			// Bind to texture
			wglBindTexImageARB(m_hpBuffer, WGL_FRONT_LEFT_ARB);/////////////////////////////////
		}

		void RectangleTexture(GLuint texture, int left, int bottom, int width, int height)
		{
			glBindTexture(GL_TEXTURE_2D, texture);
			glEnable(GL_TEXTURE_2D);
			glBegin(GL_TRIANGLE_FAN);
			glTexCoord2f(0.0f, 0.0f);    glVertex2i(left, bottom);
			glTexCoord2f(1.0f, 0.0f);    glVertex2i(left + width, bottom);
			glTexCoord2f(1.0f, 1.0f);    glVertex2i(left + width, bottom + height);
			glTexCoord2f(0.0f, 1.0f);    glVertex2i(left, bottom + height);
			glEnd();
		}
	};
}


#endif//__OGL_RENDER_TEXTURE_H__
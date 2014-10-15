/*************************************************************/
/*                          IMAGE.H                          */
/*                                                           */
/* Purpose: Definitions for the CImage class, image loading  */
/*          saving, and manipulation routines.               */
/*      Evan Pipho (evan@codershq.com)                       */
/*                                                           */
/*************************************************************/
#ifndef IMAGE_H
#define IMAGE_H

#if 0
#include <windows.h>
#include <gl/glew.h>
#include <gl/wglew.h>
//#include <gl/gl.h>
//#include <gl/glu.h>



namespace vgMs3d {

	//-------------------------------------------------------------
	//                          CImage                            -
	// author: Evan Pipho (evan@codershq.com)                     -
	// date  : Jul 10, 2002                                       -
	//-------------------------------------------------------------
	class CImage
	{
	public:

		//Load the image
		bool Load(char * szFilename, bool bMipmap = true);
		//Bind texture
		void Bind();
		//Unbind texture
		void UnBind();
		//Flip image
		void VFlip(unsigned char * ucpData, unsigned int uiHeight, unsigned int uiWidth, unsigned int uiBpp); //Vertically

		//Save a screenshot
		static void ScreenShot(char * szDstFile = "screenshot.tga");

		//Constructors
		CImage()
		{
			m_szFilename = 0;
			m_ucpBuffer = 0;
		}
		CImage(char * szFile, bool bMipMap = true)
		{
			m_ucpBuffer = 0;
			m_szFilename = 0;
			Load(szFile, bMipMap);
		}
		~CImage()
		{
			glDeleteTextures(1, &m_uiImage);
		}

	private:


		//Load various image formats
		bool LoadTGA(bool bCompressed);
		bool LoadBMP();
		bool LoadPCX();

		//dimentions
		unsigned int m_uiWidth;
		unsigned int m_uiHeight;
		unsigned int m_uiFileLen; //needed for PCX
		//Image ID
		unsigned int m_uiImage;
		//file buffer
		unsigned char * m_ucpBuffer;
		//mipmap?
		bool m_bMipMap;
		//filename
		char * m_szFilename;
	};

	//-------------------------------------------------------------
	//- Bind
	//- Binds the texture for opengl
	//-------------------------------------------------------------
	inline void CImage::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_uiImage);
	}

	//-------------------------------------------------------------
	//- UnBind
	//- UnBinds the texture for opengl , binds "no texture"
	//-------------------------------------------------------------
	inline void CImage::UnBind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}


}

#endif //IMAGE_H
#endif
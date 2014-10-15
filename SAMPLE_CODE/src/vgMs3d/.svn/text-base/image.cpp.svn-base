/*************************************************************/
/*                         IMAGE.CPP                         */
/*                                                           */
/* Purpose: Implementation of the CImage class, image loading*/
/*          saving, and manipulation routines.               */
/*      Evan Pipho (evan@codershq.com)                       */
/*                                                           */
/*************************************************************/
//-------------------------------------------------------------
//                        INCLUDES                            -
//-------------------------------------------------------------
#include <vgStableHeaders.h>
#if 0
#include "image.h"


namespace vgMs3d {


	const char BMP_HEADER[] = "BM";
	const char TGA_UHEADER[] = {0,0,2 ,0,0,0,0,0,0,0,0,0};
	const char TGA_CHEADER[] = {0,0,10,0,0,0,0,0,0,0,0,0};

	//-------------------------------------------------------------
	//- Load
	//- Loads an image of any supported image type
	//-------------------------------------------------------------
	bool CImage::Load(char * szFilename, bool bMipMap)
	{
		m_bMipMap = bMipMap;
		m_szFilename = szFilename;
		FILE * f;

		if(!(f = fopen(szFilename, "rb")))
		{
			//APP->Log(COLOR_RED, "Could not open %s", szFilename);
			return false;
		}

		fseek(f, 0, SEEK_END);
		int iEnd = ftell(f);
		fseek(f, 0, SEEK_SET);
		int iStart = ftell(f);
		m_uiFileLen = iEnd - iStart;

		m_ucpBuffer = new unsigned char[m_uiFileLen];

		if(!m_ucpBuffer)
		{
			//APP->Log(COLOR_RED, "Could not alloc memory for %s", szFilename);
			return false;
		}

		//get data
		if(fread(m_ucpBuffer, 1, m_uiFileLen, f) != m_uiFileLen)
		{
			//APP->Log(COLOR_RED, "Could not read from %s", szFilename);
			if(m_ucpBuffer)
				delete [] m_ucpBuffer;
			return false;
		}

		//Check for a valid filetype
		//Windows Bitmap
		if(memcmp(m_ucpBuffer, BMP_HEADER, 2) == 0)
		{
			return LoadBMP();
		}
		//Uncompressed TGA
		if(memcmp(m_ucpBuffer, TGA_UHEADER, 12) == 0)
		{
			return LoadTGA(false);
		}
		//Compressed TGA
		if(memcmp(m_ucpBuffer, TGA_CHEADER, 12) == 0)
		{
			return LoadTGA(true);
		}
		//PCX
		if(m_ucpBuffer[0] == 10)
		{
			return LoadPCX();
		}
		//APP->Log(COLOR_RED, "Could not load %s, Invalid filetype", szFilename);
		return false;
	}

	//-------------------------------------------------------------
	//- LoadBMP
	//- Loads a windows bitmap (24 bit)
	//-------------------------------------------------------------
	bool CImage::LoadBMP()
	{
		unsigned char * ucpPtr = m_ucpBuffer;
		unsigned char * ucpData = 0;

		//BMP File header 
		struct SBMPFHeader
		{
			unsigned char m_ucType[2];	//Identifier, must be BM
			unsigned int m_uiSize;		//Size of BMP file
			unsigned int m_uiReserved;	//0
			unsigned int m_uiOffset;	
		};
		//BMP Information Header
		struct SBMPIHeader
		{
			unsigned int m_uiSize;		//Number of bytes in structure
			unsigned int m_uiWidth;		//Width of Image
			unsigned int m_uiHeight;		//Height of Image
			unsigned short m_uiPlanes;	//Always 1
			unsigned short m_uiBpp;		//Bits Per Pixel (must be 24 for now)
			unsigned int m_uiCompression;	//Must be 0 (uncompressed)
			unsigned int m_uiXPPM;			//X Pels Per Meter
			unsigned int m_uiYPPM;			//Y Pels Per Meter
			unsigned int m_uiClrUsed;		//0 for 24 bpp bmps
			unsigned int m_uiClrImp;		//0

		};

		SBMPFHeader * pFileHeader = (SBMPFHeader *)ucpPtr;
		ucpPtr += 14;	//Skip the file header
		SBMPIHeader * pInfoHeader = (SBMPIHeader *)(ucpPtr);
		ucpPtr += 40;

		//make sure its 24 bpp and contains data 
		if(pInfoHeader->m_uiBpp != 24 || pInfoHeader->m_uiHeight == 0 || pInfoHeader->m_uiWidth == 0)
		{
			delete [] m_ucpBuffer;
			//APP->Log(COLOR_RED, "%s is an invalid BMP file", m_szFilename);
			return false;
		}


		//Fill in data for later use
		m_uiWidth = pInfoHeader->m_uiWidth;
		m_uiHeight = pInfoHeader->m_uiHeight;
		m_uiFileLen = pFileHeader->m_uiSize;

		//Fill in the data
		ucpData = new unsigned char[m_uiHeight * m_uiWidth * 3];
		if(!ucpData)
		{
			//APP->Log(COLOR_RED, "Out of memory");
			return false;
		}

		//Swap red and blue values to get RGB instead of BGR
		for(unsigned int i = 0; i < m_uiHeight * m_uiWidth * 3; i+=3)
		{
			ucpData[i] = ucpPtr[i+2];
			ucpData[i+1] = ucpPtr[i+1];
			ucpData[i+2] = ucpPtr[i];
		}

		VFlip(ucpData, m_uiWidth, m_uiHeight, 3);

		glGenTextures(1, &m_uiImage);
		glBindTexture(GL_TEXTURE_2D, m_uiImage);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);						

		if(m_bMipMap)
		{
			gluBuild2DMipmaps(GL_TEXTURE_2D, 3, m_uiWidth, m_uiHeight, GL_RGB, GL_UNSIGNED_BYTE, ucpData); 
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, 3, m_uiWidth, m_uiHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, ucpData);
		}
		delete [] ucpData;
		delete [] m_ucpBuffer;

		//APP->Log(COLOR_GREEN, "BMP Image: %s Loaded", m_szFilename);

		return true;
	}

	//-------------------------------------------------------------
	//- LoadTGA
	//- Loads an uncompressed or RLE  TGA image (24 or 32 bit)
	//-------------------------------------------------------------
	bool CImage::LoadTGA(bool bCompressed)
	{
		unsigned int uiBpp = 0;
		unsigned int uiType = 0;	//GL_RGB or GL_RGBA
		unsigned int uiImageSize = 0;
		unsigned char * ucpPtr = m_ucpBuffer;
		unsigned char * ucpData = 0;
		//skip 12 bytes for the already-compared header
		ucpPtr += 12;
		//Calculate the width and height
		m_uiWidth = (ucpPtr[1] << 8) + ucpPtr[0];
		m_uiHeight = (ucpPtr[3] << 8) + ucpPtr[2];
		uiBpp = ucpPtr[4];
		ucpPtr += 6;

		if(uiBpp == 24)
			uiType = GL_RGB;
		else if(uiBpp == 32)
			uiType = GL_RGBA;
		else
		{
			//APP->Log(COLOR_RED, "%s is an invalid TGA file", m_szFilename);
			delete [] m_ucpBuffer;
			return false;
		}

		uiImageSize = m_uiHeight * m_uiWidth * (uiBpp / 8);
		ucpData = new unsigned char[uiImageSize];

		if(!ucpData)
		{
			//APP->Log(COLOR_RED, "Out of memory");
			delete [] m_ucpBuffer;
			return false;
		}

		//If its uncompressed
		if(!bCompressed)
		{
			for(unsigned int i = 0; i < uiImageSize; i+= (uiBpp / 8))
			{
				//Swap red and blue bytes
				ucpData[i] = ucpPtr[i+2];
				ucpData[i+1] = ucpPtr[i+1];
				ucpData[i+2] = ucpPtr[i];

				if(uiBpp == 32)
					ucpData[i+3] = ucpPtr[i+3];
			}
		}
		//The image is RLE compressed
		else
		{
			unsigned int uiDataPos = 0;

			do
			{
				//Raw data
				if(ucpPtr[0] < 128)
				{
					unsigned int uiCount = ucpPtr[0] * (uiBpp / 8) + 1;
					ucpPtr++;
					for(unsigned int i = 0; i < uiCount; i+=(uiBpp/8))
					{
						ucpData[uiDataPos] = ucpPtr[i+2];
						ucpData[uiDataPos+1] = ucpPtr[i+1];
						ucpData[uiDataPos+2] = ucpPtr[i];
						ucpPtr += 3;
						uiDataPos += 3;

						if(uiBpp == 32)
						{
							ucpData[uiDataPos] = ucpPtr[i];
							ucpPtr ++;
							uiDataPos ++;
						}
					}
				}
				else
				{
					unsigned int uiCount = (ucpPtr[0] -= 127) * (uiBpp / 8);
					ucpPtr++;
					for(unsigned int i = 0; i < uiCount; i+=(uiBpp/8))
					{
						ucpData[uiDataPos] = ucpPtr[2];
						ucpData[uiDataPos+1] = ucpPtr[1];
						ucpData[uiDataPos+2] = ucpPtr[0];
						uiDataPos += 3;

						if(uiBpp == 32)
						{
							ucpData[uiDataPos] = ucpPtr[3];
							uiDataPos ++;
						}
					}
					ucpPtr += 3;
					if(uiBpp == 32)
						ucpPtr++;
				}
			}
			while(uiDataPos < uiImageSize);

		}


		glGenTextures(1, &m_uiImage);
		glBindTexture(GL_TEXTURE_2D, m_uiImage);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);						


		if(m_bMipMap)
		{
			gluBuild2DMipmaps(GL_TEXTURE_2D, uiType, m_uiWidth, m_uiHeight, uiType, GL_UNSIGNED_BYTE, ucpData); 
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, uiType, m_uiWidth, m_uiHeight, 0, uiType, GL_UNSIGNED_BYTE, ucpData);
		}


		delete [] ucpData;
		delete [] m_ucpBuffer;
		//APP->Log(COLOR_GREEN, "TGA Image: %s Loaded", m_szFilename);
		return true;
	}

	//-------------------------------------------------------------
	//- LoadPCX
	//- Loads a PCX image (may have problems loading non powers of 2 textures
	//-------------------------------------------------------------
	bool CImage::LoadPCX()
	{
		//Palette entry
		struct SPCXPal
		{	
			unsigned char m_ucColor[3];
		};

		SPCXPal Palette[256];
		unsigned char * ucpPtr = m_ucpBuffer;
		unsigned char * ucpPixData = 0;
		unsigned char * ucpData = 0;
		//Check out the header of the PCX
		if(ucpPtr[0] != 10 || ucpPtr[1] != 5 || ucpPtr[2] != 1 || ucpPtr[3] != 8)
		{
			//APP->Log(COLOR_RED, "%s is not a valid PCX texture", m_szFilename);
			delete [] m_ucpBuffer;
		}
		ucpPtr += 4;

		//Get the dimentions of the texture
		short sXMin = (ucpPtr[1] << 8) + ucpPtr[0];
		short sYMin = (ucpPtr[3] << 8) + ucpPtr[2];
		short sXMax = (ucpPtr[5] << 8) + ucpPtr[4];
		short sYMax = (ucpPtr[7] << 8) + ucpPtr[6];

		m_uiWidth = sXMax - sXMin + 1;
		m_uiHeight = sYMax - sYMin + 1;

		//move to 128 bytes into the file, where the px data is
		ucpPtr += 124;

		ucpPixData = new unsigned char[m_uiWidth * m_uiHeight];

		//decompress the pallete indexes data
		unsigned int uiIdx = 0;
		unsigned int uiPixel = 0;
		while(uiPixel < m_uiWidth * m_uiHeight)
		{
			if(ucpPtr[uiIdx] > 191)
			{
				uiIdx++;
				for(int i = 0; i < (63 & ucpPtr[uiIdx-1]); i++)
				{
					ucpPixData[uiPixel] = ucpPtr[uiIdx];
					uiPixel++;
				}
				uiIdx++;
			}
			else
			{
				ucpPixData[uiPixel] = ucpPtr[uiIdx];
				uiIdx++;
				uiPixel++;
			}
		}

		//go read the palette info
		ucpPtr = m_ucpBuffer + m_uiFileLen - 769;

		if(ucpPtr[0] != 12)
		{
			//APP->Log(COLOR_RED, "Bad palette in %s", m_szFilename);
			delete [] ucpPixData;
			return false;
		}
		ucpPtr++;

		memcpy(Palette, ucpPtr, sizeof(SPCXPal[256]));

		//use the palette to decompress to a 24 bit image
		ucpData = new unsigned char[m_uiWidth * m_uiHeight * 3];

		uiIdx = 0;
		for(unsigned int i = 0; i < m_uiWidth * m_uiHeight; i++)
		{
			ucpData[uiIdx  ] = Palette[ucpPixData[i]].m_ucColor[0];
			ucpData[uiIdx+1] = Palette[ucpPixData[i]].m_ucColor[1];
			ucpData[uiIdx+2] = Palette[ucpPixData[i]].m_ucColor[2];
			uiIdx+=3;
		}

		m_uiImage = 0;

		glGenTextures(1, &m_uiImage);
		glBindTexture(GL_TEXTURE_2D, m_uiImage);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);						

		if(m_bMipMap)
		{
			gluBuild2DMipmaps(GL_TEXTURE_2D, 3, m_uiWidth, m_uiHeight, GL_RGB, GL_UNSIGNED_BYTE, ucpData); 
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, 3, m_uiWidth, m_uiHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, ucpData);
		}

		delete [] m_ucpBuffer;
		delete [] ucpPixData;
		delete [] ucpData;	

		//APP->Log(COLOR_GREEN, "PCX Image: %s Loaded", m_szFilename);

		return true;
	}

	//-------------------------------------------------------------
	//- VFlip
	//- Flip the image vertically
	//-------------------------------------------------------------
	void CImage::VFlip(unsigned char * ucpData, unsigned int uiHeight, unsigned int uiWidth, unsigned int uiBpp)
	{
		unsigned char * ucpCopy = new unsigned char[uiWidth * uiHeight * uiBpp];
		if(!ucpCopy)
			return;
		for(unsigned int i = 0; i < uiHeight; i++)
			memcpy(ucpCopy + (uiWidth * uiBpp * i), ucpData + (uiWidth * uiBpp * (uiHeight - i)), uiWidth * uiBpp);
		memcpy(ucpData, ucpCopy, uiWidth * uiHeight * uiBpp);
		delete [] ucpCopy;
	}

	//-------------------------------------------------------------
	//- Screenshot
	//- Take a screenshot of the current app
	//-------------------------------------------------------------
	void CImage::ScreenShot(char * szDstFile)
	{
		//unsigned short usWidth = CWindow::m_uiWidth, usHeight = CWindow::m_uiHeight;
		//unsigned char ucBpp = 24, c = 0;
		//unsigned char * ucpData = new unsigned char[usHeight * usWidth * 3];
		//if(!ucpData)
		//	return;
		//glReadBuffer(GL_FRONT);
		////glReadPixels(0, 0, usWidth, usHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, ucpData);//6.0
		//glReadPixels(0, 0, usWidth, usHeight, GL_BGR, GL_UNSIGNED_BYTE, ucpData);//7.0

		//	FILE * f = fopen(szDstFile, "wb");
		//if(!f)
		//{
		//	//APP->Log(COLOR_RED, "Error taking screenshot");
		//	return;
		//}
		//Write TGA header
		//fwrite(TGA_UHEADER, 1, 12, f);
		////Write width, height, bpp
		//fwrite(&usWidth, 1, 2, f);
		//fwrite(&usHeight, 1, 2, f);
		//fwrite(&ucBpp, 1, 1, f);
		//fwrite(&c, 1, 1, f);
		//fwrite(ucpData, 1, usWidth * usHeight * 3, f);

		//fclose(f);
		//	delete [] ucpData;
	}





}

#endif
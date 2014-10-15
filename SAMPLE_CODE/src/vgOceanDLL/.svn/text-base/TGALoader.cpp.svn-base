

#include "stdafx.h"
#include "tgaloader.h"
#include <stdio.h>

TGALoader::TGALoader(void) : m_imageWidth(0), m_imageHeight(0), m_imageColourDepth(0), m_imageData(NULL)
{
}

TGALoader::~TGALoader(void)
{
}

// pretty much taken from NeHe's tuts on targas
bool TGALoader::LoadFromFile(const char* fileName)
{
   unsigned char  FileHeader[12];
   unsigned char  ImageHeader[6];
   unsigned char  UnCompressedTGA[12] = {0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};
   unsigned char  CompressedTGA[12] = {0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0};

   // open the file in binary mode
   FILE* pFile = fopen(fileName, "rb");
   
   if (pFile)
   {
      // read the file header
      if (fread(&FileHeader, sizeof(FileHeader), 1, pFile) == 0)
         return false;

      if(memcmp(UnCompressedTGA, &FileHeader, sizeof(FileHeader)) == 0)
	   {
         // read the image header
         if (fread(ImageHeader, sizeof(ImageHeader), 1, pFile) == 0)
            return false;

         m_imageWidth = ImageHeader[1] * 256 + ImageHeader[0];
         m_imageHeight = ImageHeader[3] * 256 + ImageHeader[2];
         m_imageColourDepth = ImageHeader[4];

         unsigned int iSize = (m_imageColourDepth/8) * m_imageWidth * m_imageHeight;

         if (iSize > 0)
            m_imageData = new unsigned char[iSize];

         if (!m_imageData)
            return false;

         // read in the data
         if (fread(m_imageData, 1, iSize, pFile) != iSize)
            return false;

         int iDimensions = m_imageHeight * m_imageHeight;         
         void* pData = m_imageData;

         int iBytes = 0;
         if (m_imageColourDepth == 24)
            iBytes = 3;
         else if (m_imageColourDepth == 32)
            iBytes = 4;
         else
            return false;

         // this is from a nehe tutorial
         // it swaps the R and B components 
         __asm
	      {
		      mov ecx, iDimensions // Set Up A Counter (Dimensions Of Memory Block)
		      mov ebx, pData       // Points ebx To Our Data (pData)
		      label:               // Label Used For Looping
			      mov al,[ebx+0]    // Loads Value At ebx Into al
			      mov ah,[ebx+2]    // Loads Value At ebx+2 Into ah
			      mov [ebx+2],al    // Stores Value In al At ebx+2
			      mov [ebx+0],ah    // Stores Value In ah At ebx
			      
			      add ebx,iBytes    // Moves Through The Data By 3 or 4 Bytes
			      dec ecx           // Decreases Our Loop Counter
			      jnz label         // If Not Zero Jump Back To Label
	      }
      }
      else
         return false;

      // close the file
      fclose(pFile);
   }
   else
      return false;

   return true;
}

const unsigned int TGALoader::GetWidth(void) const
{
   return m_imageWidth;
}

const unsigned int TGALoader::GetHeight(void) const
{
   return m_imageHeight;
}

const unsigned int TGALoader::GetColourDepth(void) const
{
   return m_imageColourDepth;
}

const unsigned char* TGALoader::GetData(void) const
{
   return m_imageData;
}
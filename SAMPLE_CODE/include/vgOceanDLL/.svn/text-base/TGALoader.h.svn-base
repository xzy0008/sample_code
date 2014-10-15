
#pragma once

class TGALoader
{
public:
   TGALoader(void);
   virtual ~TGALoader(void);

public:
   bool LoadFromFile(const char* fileName);
   const unsigned int GetWidth(void) const;
   const unsigned int GetHeight(void) const;
   const unsigned int GetColourDepth(void) const;
   const unsigned char* GetData(void) const; 
private:
   unsigned int m_imageWidth;
   unsigned int m_imageHeight;
   unsigned int m_imageColourDepth;
   unsigned char* m_imageData;
};

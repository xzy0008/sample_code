
#include <vgStableHeaders.h>
#include <vgTex/tvgGpuProgram.h>


#include <vgTex/tvgBrightfloorGpuProgram.h>
#include <vgTex/tvgOpenGLSupport.h>

#include <olectl.h>

namespace vgCore {
	

	GLenum  BrightfloorGpuProgram::FaceTarget[6] = {  
		GL_TEXTURE_CUBE_MAP_POSITIVE_X,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };


	char *BrightfloorGpuProgram::vertex_source = "\
				uniform float4x4 modelViewProj : state.matrix.mvp;\
				void main(\
					float4 in_position	:   POSITION ,\
					float2 in_texCoord	:   TEXCOORD0 , \
					out float4 out_Position	: POSITION ,\
					out float2 out_TexCoord	: TEXCOORD0 ,\
					out float3 out_I			: TEXCOORD1 ,\
					out float3 out_N : TEXCOORD2,\
					uniform float3 eyePosition )\
				{\
					out_Position = mul( modelViewProj, in_position );\
					out_TexCoord = in_texCoord;\
					out_I =in_position - eyePosition.xyz;\
				}\
			";

	char *BrightfloorGpuProgram::pixel_source = "\
				void main(\
					float2 in_texCoord : TEXCOORD0,\
					float3 in_I		 : TEXCOORD1 ,\
					float in_N		: TEXCOORD2 ,\
					out float4 out_Color : COLOR ,\
					uniform float bump,\
					uniform sampler2D decalMap : register(s0),\
					uniform samplerCUBE environmentMap  : register(s2))\
				{\
					float4 decal_color = tex2D( decalMap , in_texCoord );\
					/*float3 normal_map_coord = float3( in_texCoord.x , in_texCoord.y , 0.0 );*/\
					float3 out_R = reflect( in_I , in_N );\
					out_R.z = - out_R.z;\
					float4 reflect_color = texCUBE( environmentMap , out_R );\
					out_Color = lerp( decal_color , reflect_color , bump );\
					/*out_Color = reflect_color;*/\
			}";


	bool BrightfloorGpuProgram::buildFaceTextureUsingGDI( const string& filename , GLenum target )
	{


		FileInfoPtr pfile = ArchiveManager::getSingleton().getFileInfo( filename );

		if ( pfile.isNull() )
		{
			MessageBox(NULL , "创建立方体贴图时出错." , "Error"  , MB_OK );
			return false;
		}

		NormalImagePtr pimg = ImageFactory::createNormalImagePtr();

		bool ret = pimg->loadFromFileInfo( pfile);

		if ( ret == false )
		{
			assert(0);
		}

		pimg->buildTextureByGLEnum( target );

		//没有用，但是这样可以用于保存纹理。
		TextureManager::getSingleton().addTexturePtr( filename );


		return true;

		/*

		//////////////////////////////////////////////////////////////////////////
		const char *szPathName = filename.c_str();
		//////////////////////////////////////////////////////////////////////////

		HDC      hdcTemp;                        // The DC To Hold Our Bitmap
		HBITMAP    hbmpTemp;                        // Holds The Bitmap Temporarily
		IPicture  *pPicture;                        // IPicture Interface
		OLECHAR    wszPath[MAX_PATH+1];                  // Full Path To Picture (WCHAR)
		char    szPath[MAX_PATH+1];                    // Full Path To Picture
		long    lWidth;                          // Width In Logical Units
		long    lHeight;                        // Height In Logical Units
		long    lWidthPixels;                      // Width In Pixels
		long    lHeightPixels;                      // Height In Pixels
		GLint    glMaxTexDim ;                      // Holds Maximum Texture Size

// 		if (strstr(szPathName, "http://"))                  // If PathName Contains http:// Then...
// 		{
// 			strcpy(szPath, szPathName);                    // Append The PathName To szPath
// 		}
// 		else                                // Otherwise... We Are Loading From A File
// 		{
// 			GetCurrentDirectory(MAX_PATH, szPath);              // Get Our Working Directory
// 			strcat(szPath, "\\");                      // Append "\" After The Working Directory
// 			strcat(szPath, szPathName);                    // Append The PathName
// 		}

		strcpy( szPath , szPathName );

		MultiByteToWideChar(CP_ACP, 0, szPath, -1, wszPath, MAX_PATH);    // Convert From ASCII To Unicode
		HRESULT hr = OleLoadPicturePath(wszPath, 0, 0, 0, IID_IPicture, (void**)&pPicture);

		if(FAILED(hr))                            // If Loading Failed
			return false;                          // Return False

		hdcTemp = CreateCompatibleDC(GetDC(0));                // Create The Windows Compatible Device Context
		if(!hdcTemp)                            // Did Creation Fail?
		{

			pPicture->Release();                      // Decrements IPicture Reference Count
			return false;                          // Return False (Failure)
		}

		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &glMaxTexDim);          // Get Maximum Texture Size Supported

		pPicture->get_Width(&lWidth);                    // Get IPicture Width (Convert To Pixels)
		lWidthPixels  = MulDiv(lWidth, GetDeviceCaps(hdcTemp, LOGPIXELSX), 2540);
		pPicture->get_Height(&lHeight);                    // Get IPicture Height (Convert To Pixels)
		lHeightPixels  = MulDiv(lHeight, GetDeviceCaps(hdcTemp, LOGPIXELSY), 2540);

		// Resize Image To Closest Power Of Two
		if (lWidthPixels <= glMaxTexDim) // Is Image Width Less Than Or Equal To Cards Limit
			lWidthPixels = 1 << (int)floor((log((double)lWidthPixels)/log(2.0f)) + 0.5f); 
		else // Otherwise Set Width To "Max Power Of Two" That The Card Can Handle
			lWidthPixels = glMaxTexDim;

		if (lHeightPixels <= glMaxTexDim) // Is Image Height Greater Than Cards Limit
			lHeightPixels = 1 << (int)floor((log((double)lHeightPixels)/log(2.0f)) + 0.5f);
		else // Otherwise Set Height To "Max Power Of Two" That The Card Can Handle
			lHeightPixels = glMaxTexDim;

		//  Create A Temporary Bitmap
		BITMAPINFO  bi = {0};                        // The Type Of Bitmap We Request
		DWORD    *pBits = 0;                        // Pointer To The Bitmap Bits

		bi.bmiHeader.biSize      = sizeof(BITMAPINFOHEADER);        // Set Structure Size
		bi.bmiHeader.biBitCount    = 32;                  // 32 Bit
		bi.bmiHeader.biWidth    = lWidthPixels;              // Power Of Two Width
		bi.bmiHeader.biHeight    = lHeightPixels;            // Make Image Top Up (Positive Y-Axis)
		bi.bmiHeader.biCompression  = BI_RGB;                // RGB Encoding
		bi.bmiHeader.biPlanes    = 1;                  // 1 Bitplane

		//  Creating A Bitmap This Way Allows Us To Specify Color Depth And Gives Us Imediate Access To The Bits
		hbmpTemp = CreateDIBSection(hdcTemp, &bi, DIB_RGB_COLORS, (void**)&pBits, 0, 0);

		if(!hbmpTemp)                            // Did Creation Fail?
		{
			DeleteDC(hdcTemp);                        // Delete The Device Context
			pPicture->Release();                      // Decrements IPicture Reference Count
			return false;                          // Return False (Failure)
		}

		SelectObject(hdcTemp, hbmpTemp);                  // Select Handle To Our Temp DC And Our Temp Bitmap Object

		// Render The IPicture On To The Bitmap
		pPicture->Render(hdcTemp, 0, 0, lWidthPixels, lHeightPixels, 0, lHeight, lWidth, -lHeight, 0);

		// Convert From BGR To RGB Format And Add An Alpha Value Of 255
		for(long i = 0; i < lWidthPixels * lHeightPixels; i++)        // Loop Through All Of The Pixels
		{
			BYTE* pPixel  = (BYTE*)(&pBits[i]);              // Grab The Current Pixel
			BYTE temp    = pPixel[0];                  // Store 1st Color In Temp Variable (Blue)
			pPixel[0]    = pPixel[2];                  // Move Red Value To Correct Position (1st)
			pPixel[2]    = temp;                      // Move Temp Value To Correct Blue Position (3rd)

			// This Will Make Any Black Pixels, Completely Transparent    (You Can Hardcode The Value If You Wish)
			if ((pPixel[0]==0) && (pPixel[1]==0) && (pPixel[2]==0))      // Is Pixel Completely Black
				pPixel[3]  = 0;                      // Set The Alpha Value To 0
			else                              // Otherwise
				pPixel[3]  = 255;                      // Set The Alpha Value To 255
		}

		glTexImage2D(target, 0, GL_RGBA, lWidthPixels, lHeightPixels, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, pBits);  // (Modify This If You Want Mipmaps)

		//glTexParameteri(target,GL_TEXTURE_WRAP_S ,GL_CLAMP_TO_EDGE);
		//glTexParameteri(target,GL_TEXTURE_WRAP_T ,GL_CLAMP_TO_EDGE);

		VG_CHECK_OPENGL_ERROR();

		//////////////////////////////////////////////////////////////////////////
		gluBuild2DMipmaps(target, GL_RGBA , lWidthPixels , 
			lHeightPixels , GL_RGBA , GL_UNSIGNED_BYTE, pBits );



		VG_CHECK_OPENGL_ERROR();

		//////////////////////////////////////////////////////////////////////////

		DeleteObject(hbmpTemp);                        // Delete The Object
		DeleteDC(hdcTemp);                          // Delete The Device Context

		pPicture->Release();                        // Decrements IPicture Reference Count

		return true;                            // Return True (All Good)

		*/


	}








		//----------------------------------------------------------------
		GLuint BrightfloorGpuProgram::buildCubeMapID( const StringVector& strVec )
		{
			GLuint textureID = 0;

			assert( strVec.size() == 6 );

			OpenGLSupport::makeErrorStackEmpty();

			glGenTextures(1, &textureID);
			glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
			//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
			//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT);      
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);   

			VG_CHECK_OPENGL_ERROR();

			for(int i = 0; i < 6; i++)
			{
				if ( !buildFaceTextureUsingGDI( strVec[i] , FaceTarget[i] ) )
				{
					std::ostringstream o;
					o << "图像：" << strVec[i] << "载入失败,立方体贴图创建失败。";
					MessageBox(NULL , o.str().c_str() , "载入图像时出错." , MB_OK );
					continue;
				}
			}
			return textureID;
		}
		//----------------------------------------------------------------
		GLuint BrightfloorGpuProgram::buildNormalMapID( const String& normalmap , 
			const float& bump )
		{
			TextureManager::getSingleton().addTexturePtr( normalmap );

			FileInfoPtr pfile = ArchiveManager::getSingleton().getFileInfo( normalmap );

			if ( pfile.isNull() )
			{
				return false;
			}

			NormalImagePtr pimg = ImageFactory::createNormalImagePtr();

			bool ret = pimg->loadFromFileInfo( pfile );

			if ( ret == false )
			{
				assert(0);
			}

			uchar* buffer = NULL;
			long size = 0;

			if (!pimg->mCximagePtr->Encode2RGB(buffer,size))
			{
				VG_EXCEPT(Exception::ERR_INTERNAL_ERROR
					,"Encode2RGB()失败,内部错误." 
					, "NormalImage::buildTextureByGLEnum()");
				return false;
			}

			assert( buffer != NULL );
			assert( size != 0 );

			const unsigned int width = pimg->getWidth();
			const unsigned int height = pimg->getHeight();

			const unsigned int arraysize = 3 * width * height;

			assert( size == arraysize );

			int pos = 0;
			float yScale = 1.0f;
			float xzScale = 1.0f;

			uchar* normal = new uchar[arraysize];

			//uchar* normal = buffer;

			memset(normal , 0 ,arraysize);

			for ( int x=0 ; x != width ; x++ )
			{
				for ( int y=0 ; y!= height ; y++ )
				{
					//把Height Map的每个像素和它右面的一个像素相减，得到一个高度差，作为该点法线的x值；
					unsigned int sx = 255 + getHeight( buffer ,width, x != width-1 ? x+1 : x, y) - getHeight(buffer ,width,x, y);
					//if (x == width-1)
					//{
					//	sx = getHeight(x, y) - getHeight(x-1, y);    
					//}

					//把Height Map的每个像素和它下面的一个像素相减，得到一个高度差，作为该点法线的z值；
					unsigned int sy = 255 + getHeight( buffer,width, x, y!=height-1 ? y+1 : y) - getHeight(buffer ,width, x, y);
					//if ( y == height -1)
					//{
					//	sx = getHeight(x, y) - getHeight(x, y-1);       
					//}

					unsigned int cx = sx/2;
					unsigned int cz = sy/2;

					assert(cx < 256);
					assert(cz < 256);

					int pos = width  * x * 3 + y * 3;

					normal[pos] = cx * bump;
					normal[pos + 1] = 255 /** yScale*/;
					normal[pos + 2] = cz * bump;
				}
			} // end of create normal map;

			memcpy( buffer , normal , arraysize );

			delete normal;

			//////////////////////////////////////////////////////////////////////////
			// 使之变为纹理！

			GLuint texture_id = 0;

			//OpenGLSupport::makeErrorStackEmpty();

			VG_CHECK_OPENGL_ERROR();

			glGenTextures(1, &texture_id);          
			glBindTexture(GL_TEXTURE_2D, texture_id); 

			VG_CHECK_OPENGL_ERROR();

			glTexImage2D(GL_TEXTURE_2D ,
				0,
				GL_RGB,
				width,
				height,
				0,
				GL_RGB, 
				GL_UNSIGNED_BYTE,
				buffer );

			VG_CHECK_OPENGL_ERROR();

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			if ( 1 )
			{
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR );  
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR ); 
				gluBuild2DMipmaps(GL_TEXTURE_2D, 
					GL_RGB , 
					width,
					height,
					GL_RGB ,
					GL_UNSIGNED_BYTE, 
					buffer );
			}


			VG_CHECK_OPENGL_ERROR();

			if(buffer) 
			{
				free(buffer);
			}

			return texture_id;
		}

		bool BrightfloorGpuProgram::init()
		{
			GpuManager& gpuMgr = GpuManager::getSingleton();
			mSupportPtr = gpuMgr.getGpuSupportPtr();

			this->mVertexProfile = mSupportPtr->getVertexProfile();
			this->mPixelProfile = mSupportPtr->getPixelProfile();


			mIsValid = true;

			/// 初始化CGprogram程序
			mCgVertexProgram = 	cgCreateProgram( 
				mSupportPtr->getGpuContextPtr()->getContext(),
				CG_SOURCE,
				vertex_source,
				mVertexProfile,
				NULL, NULL );

			GpuSupport::checkCgErrorStack();

			mCgPixelProgram = 	cgCreateProgram( 
				mSupportPtr->getGpuContextPtr()->getContext(),
				CG_SOURCE,
				pixel_source,
				mPixelProfile,
				NULL, NULL );

			GpuSupport::checkCgErrorStack();

			cgGLLoadProgram( mCgVertexProgram );

			GpuSupport::checkCgErrorStack();

			cgGLLoadProgram( mCgPixelProgram );

			GpuSupport::checkCgErrorStack();

			return true;
		}
		//----------------------------------------------------------------
		GLuint BrightfloorGpuProgram::buildDecalMapID( const String& decalmap )
		{
			GLuint textureID = 0;

			OpenGLSupport::makeErrorStackEmpty();

			glGenTextures(1, &textureID);
			glBindTexture(GL_TEXTURE_2D, textureID);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			VG_CHECK_OPENGL_ERROR();

			if ( !buildFaceTextureUsingGDI( decalmap , GL_TEXTURE_2D ) )
			{
				assert(0 && " DECALMAP图像载入失败! ");
			}

			return textureID;
		}

		void BrightfloorGpuProgram::destroy()
		{
			GpuSupport::checkCgErrorStack();
			if ( mCgPixelProgram != NULL )
			{
				cgDestroyProgram(mCgPixelProgram);
				GpuSupport::checkCgErrorStack();
				mCgPixelProgram = NULL;
			}

			if ( mCgVertexProgram != NULL )
			{
				cgDestroyProgram(mCgVertexProgram);
				GpuSupport::checkCgErrorStack();
				mCgVertexProgram = NULL;
			}

			//------------------------------------------
			// 删除纹理
			//------------------------------------------
			// make sure there is no error msg
			OpenGLSupport::makeErrorStackEmpty();
			String errMessage;

			if ( mCubeMapID != 0 )
			{
				glDeleteTextures( 1 , &mCubeMapID );
				mCubeMapID = 0;
			}

			if ( mNormalMapID != 0 )
			{
				glDeleteTextures( 1 , &mNormalMapID );
				mNormalMapID = 0;
			}

			if ( mDecalMapID != 0 )
			{
				glDeleteTextures( 1 , &mDecalMapID );
				mDecalMapID = 0;
			}

			if( OpenGLSupport::checkOpenGLErrorWithoutThrow( errMessage ) )
			{
				VG_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR ,
					"glDeleteTextures failed! Error Code: " + errMessage ,
					"Texture::deleteTexture()");

				return;
			}

			setDefault();
		}

		void BrightfloorGpuProgram::useBindBegin()
		{
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_TEXTURE_CUBE_MAP);
			cgGLSetParameter3fv(
				cgGetNamedParameter(mCgVertexProgram, "eyePosition"), 
				mEyePosition.v );

			//cgGLSetParameter2fv(
			//	cgGetNamedParameter(mCgVertexProgram, "time_line"), 
			//	mTimeLine );

			//cgGLSetTextureParameter(
			//	cgGetNamedParameter( mCgPixelProgram, "normalMap"), 
			//	mNormalMapID );


			cgGLSetParameter1f(
				cgGetNamedParameter( mCgPixelProgram, "bump"), 
				mBumpScale );



			//////////////////////////////////////////////////////////////////////////

			//cgGLSetTextureParameter(
			//	cgGetNamedParameter( mCgPixelProgram, "normalMap2"), 
			//	mNormalMapID2 );
			//////////////////////////////////////////////////////////////////////////

			cgGLSetTextureParameter(
				cgGetNamedParameter( mCgPixelProgram, "environmentMap"), 
				mCubeMapID );

			cgGLSetTextureParameter(
				cgGetNamedParameter( mCgPixelProgram, "decalMap"), 
				mDecalMapID );


			cgGLEnableProfile( mVertexProfile );
			cgGLEnableProfile( mPixelProfile );

			cgGLBindProgram( mCgPixelProgram );
			cgGLBindProgram( mCgVertexProgram );

			//cgGLEnableTextureParameter(
			//	cgGetNamedParameter(mCgPixelProgram, "normalMap") );
			//////////////////////////////////////////////////////////////////////////
			//cgGLEnableTextureParameter(
			//	cgGetNamedParameter(mCgPixelProgram, "normalMap2") );
			//////////////////////////////////////////////////////////////////////////

			cgGLEnableTextureParameter(
				cgGetNamedParameter(mCgPixelProgram, "environmentMap") );

			cgGLEnableTextureParameter(
				cgGetNamedParameter(mCgPixelProgram, "decalMap") );
		}

		void BrightfloorGpuProgram::useBindEnd()
		{
			//////////////////////////////////////////////////////////////////////////
			//cgGLDisableTextureParameter(
			//	cgGetNamedParameter(mCgPixelProgram, "normalMap2") );
			//////////////////////////////////////////////////////////////////////////

			cgGLDisableTextureParameter(
				cgGetNamedParameter(mCgPixelProgram, "decalMap") );

			//cgGLDisableTextureParameter(
			//	cgGetNamedParameter(mCgPixelProgram, "normalMap") );

			cgGLDisableTextureParameter(
				cgGetNamedParameter(mCgPixelProgram, "environmentMap") );

			cgGLDisableProfile( mVertexProfile );
			cgGLDisableProfile( mPixelProfile );

			glDisable(GL_TEXTURE_CUBE_MAP);
		}
		//----------------------------------------------------------------










}// end of namespace vgCore

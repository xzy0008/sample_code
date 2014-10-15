
#include "stdafx.h"
#include "CRenderer.hpp"
#include <limits>

#define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS_ARB   0x8B4C
#define GL_RGBA_FLOAT32_ATI                 0x8814
#define GL_RGB_FLOAT32_ATI                  0x8815
#define GL_ALPHA_FLOAT32_ATI                0x8816
#define GL_INTENSITY_FLOAT32_ATI            0x8817
#define GL_LUMINANCE_FLOAT32_ATI            0x8818
#define GL_LUMINANCE_ALPHA_FLOAT32_ATI      0x8819
#define GL_RGBA_FLOAT16_ATI                 0x881A
#define GL_RGB_FLOAT16_ATI                  0x881B
#define GL_ALPHA_FLOAT16_ATI                0x881C
#define GL_INTENSITY_FLOAT16_ATI            0x881D
#define GL_LUMINANCE_FLOAT16_ATI            0x881E
#define GL_LUMINANCE_ALPHA_FLOAT16_ATI      0x881F

#define RADIUS     (4)
#define CIRCLEPART 384

typedef int  intptrARB;
typedef unsigned int sizeiptrARB;

#define LandSize 128
BYTE LandH[LandSize][LandSize];
unsigned int VBO_ID = 0;
unsigned int IBO_ID = 0;
int nInd = 0, nVert = 0;

static CGprofile  fpProfile = CG_PROFILE_FP40;
static CGprofile  vpProfile = CG_PROFILE_VP40;



#define WaterImages 16
#define NUMINTERPOLATION 4
#define WaterTexSize 256

struct TVertexV1C {
	float XYZ[3];
	DWORD RGBA;
	void Set(float X, float Y, float Z, DWORD aRGBA = 0)
	{ 
		XYZ[0] = X; XYZ[1] = Y; XYZ[2] = Z;
	}
};

float GetTime() {
	return glutGet(GLenum(GLUT_ELAPSED_TIME)) * .001f;
}

void LoadRaw(char *RawFN, void *Data, int SizeBytes) {
	FILE *F = fopen(RawFN,"rb");
	if (!F)
	{
		AfxMessageBox(_T("can't open Raw file!"));
		exit(-1);
	}
	fread(Data, SizeBytes, 1, F);
	fclose(F);
}

static void StringToChar(CString strOriginal, char* ch)
{
	int j;
	for (j=0;j<strOriginal.GetLength();j++)
	{
		ch[j]=strOriginal.GetAt(j);
	}
	ch[j]='\0';
}

int make_tex(BYTE *pBuf, int texSize, int Wrap = 1, int nChan = 3) {
	GLuint ID; glGenTextures(1, &ID);

	glBindTexture(GL_TEXTURE_2D, ID);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (Wrap? GL_REPEAT : GL_CLAMP_TO_EDGE));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (Wrap? GL_REPEAT : GL_CLAMP_TO_EDGE));
	// SGIS_generate_mipmap extension must exist
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);

	glTexImage2D( GL_TEXTURE_2D, 0, nChan==3?GL_RGB8:GL_RGBA8, texSize, texSize, 0, 
		nChan==3?GL_RGB:GL_RGBA, GL_UNSIGNED_BYTE, pBuf);

	return ID;
}


int load_tex(char *string, int texSize, int Wrap = 1, int nChan = 3) {
	BYTE *pBuf = new BYTE[texSize*texSize*nChan];
	LoadRaw(string, pBuf, texSize*texSize*nChan);
	GLuint ID = make_tex(pBuf, texSize, Wrap, nChan);
	delete[] pBuf;
	return ID;
}

int load_texlist(char *stringmask, GLuint *IDS, int Count, int texSize, int Wrap = 1) {
	for (int i = 0; i < Count; i++) {
		char FN[80]; sprintf(FN, stringmask, i);
		IDS[i] = load_tex(FN, texSize, Wrap);
	}
	return 1;
}


int BuildFreshel_tex(int texSize) {
	float refractionIndexRatio = 1.3333333f; // Water refraction koef
	float FreshelK0 = pow(1.0-refractionIndexRatio, 2.0) / pow(1.0+refractionIndexRatio, 2.0);


	BYTE *pBuf = new BYTE[texSize*texSize*3];
	BYTE *pB = pBuf;
	for (int j = 0; j < texSize; j++) {
		float L = float(j)/((float)texSize);
		for (int i = 0; i < texSize; i++) {
			float CosT = float(i)/((float)texSize);
			float K = (FreshelK0+(1-FreshelK0)*pow((1-CosT),5))*L;
			pB[0] = pB[1] = pB[2] = int(K*255.0f);
			pB+=3;
		}
	}

	GLuint ID = make_tex(pBuf, texSize, 0);
	delete[] pBuf;
	return ID;
}

int load_cubemap(const char *string, int texSize) {
	GLenum CubeSides[6] = {
		GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB, 
			GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB,
			GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB,
			GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB
	};

	char CN[6][5] = {{"posx"}, {"negx"}, {"negy"}, {"posy"}, {"posz"}, {"negz"}};

	GLuint CubeMapID; glGenTextures(1, &CubeMapID);	

	glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, CubeMapID);	
	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);	

	BYTE *pBuf = new BYTE[texSize*texSize*3];
	for (int i = 0; i < 6; i++) {

		char buff[1024];
		sprintf(buff, string, CN[i]);
		LoadRaw(buff, pBuf, texSize*texSize*3);
		// SGIS_generate_mipmap extension must exist		

		glTexImage2D( CubeSides[i], 0, GL_RGB8, texSize, texSize, 0, GL_RGB, GL_UNSIGNED_BYTE, pBuf);
	}
	delete[] pBuf;
	return CubeMapID;
}

inline void EnableTexGenScreen() {
	float mtxTex[16] = {1.0, 0.0, 0.0, 0.0, 
		0.0, 1.0, 0.0, 0.0, 
		0.0, 0.0, 1.0, 0.0, 
		0.0, 0.0, 0.0, 1.0
	};
	glTexGeni (GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni (GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni (GL_R, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni (GL_Q, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGenfv(GL_S, GL_OBJECT_PLANE, mtxTex);
	glTexGenfv(GL_T, GL_OBJECT_PLANE, mtxTex+4);
	glTexGenfv(GL_R, GL_OBJECT_PLANE, mtxTex+8);
	glTexGenfv(GL_Q, GL_OBJECT_PLANE, mtxTex+12);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);
	glEnable(GL_TEXTURE_GEN_Q);
}

inline void DisableTexGenScreen() {
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_GEN_Q);
}


void SetScreenPrjMatrix() {
	//Use convertion to homogenies coord
	float mtxMView[16];
	float mtxPrj[16];

	glGetFloatv(GL_MODELVIEW_MATRIX, mtxMView);
	glGetFloatv(GL_PROJECTION_MATRIX, mtxPrj);   

	float ScaleMtx[16] = {0.5, 0.0, 0.0, 0.0, 
		0.0, 0.5, 0.0, 0.0, 
		0.0, 0.0, 1.0, 0.0, 
		0.5, 0.5, 0.0, 1.0
	};
	glLoadMatrixf(ScaleMtx);
	glMultMatrixf(mtxPrj);
	glMultMatrixf(mtxMView);
}

static void CheckCgError(CGcontext Context = 0)
{
	CGerror err = cgGetError();	
	if (err != CG_NO_ERROR) {
		printf("CG error: %s \n", cgGetErrorString(err));
		printf("%s \n", cgGetLastListing(Context));
	}
}


namespace VR_Ocean{

	// ***************************************************************************
	// ** Name  : CRenderer
	// ** Author: livenson 2009.11.26
	// ** Desc  : Initialize all resources that we need
	// ***************************************************************************
	CRenderer::CRenderer():Singleton<CRenderer>(VGK_SINGLETON_LEFE_OCEAN)
	{
		m_bHasLoaded=false;
		m_bPointAddStart=false;
		m_bRenderLargeArea=false;
		m_CurNodeIndex=-1;
		m_MirrorMode=0;

		m_pOceanInput=NULL;

		b_showLines = false;
	}
	void CRenderer::Initialize()
	{	
		//动态设定海平面的高度 --livenson 20091026
		//m_WaterHeight=735.0f;//for antarctic
		//m_WaterHeight=120.0f;//for qingdao
		m_WaterHeight=1.0;
		m_WaterScale=1.0f;
		m_TexScale=0.0025;
		m_Opacity=1.0;
		if(!m_RenderTexture.Create(1024,1024))
			AfxMessageBox(_T("render texture init wrong!"));
		
		// Create cgContext.
		Context = cgCreateContext();
		CheckCgError();	

		char dir[MAX_PATH],FileDir[MAX_PATH];
		GetModuleFileName(NULL,(LPWCH)dir, MAX_PATH);
		(_tcsrchr((wchar_t *)dir, (wchar_t)_T('\\')))[1] = 0; //删除文件名，只获得路径
		CString strEXE;
		strEXE.Format(_T("%s"),dir);
		CString strPath=_T("");
		
		strPath=strEXE+_T("Data\\VROCEAN\\caustics\\caustic_v.cg");
		CFileFind finder;
		BOOL bWorking = finder.FindFile(strPath);
		if (!bWorking)
		{
			AfxMessageBox(_T("can't find ocean caustics file!"));
			exit(-1);
		}

		strPath=strEXE+_T("Data\\VROCEAN\\fpWaterDM.cg");
		bWorking = finder.FindFile(strPath);
		if (!bWorking)
		{
			AfxMessageBox(_T("can't find ocean file!"));
			exit(-1);
		}
		//StringToChar(strPath,FileDir);		
		
		//char *newpath1 = new char;
		WideCharToMultiByte(CP_OEMCP,0,(LPCWSTR)strPath,-1,FileDir,260,0,false);
		
		//fragmentProgram = cgCreateProgramFromFile(Context,
			//CG_SOURCE,/*(const char*)FileDir*/"H:/平台/bin/Data/VROCEAN/fpWaterDM.cg", fpProfile, NULL, NULL);
		fragmentProgram = cgCreateProgramFromFile(Context,
			CG_SOURCE, FileDir, fpProfile, NULL, NULL);
		CheckCgError(Context);
		cgGLLoadProgram(fragmentProgram);
		CheckCgError(Context);

		for(int k = 0; k < 10; k++) {
			char S[4]; sprintf(S, "c%i", k);
			fpVars.c[k] = cgGetNamedParameter(fragmentProgram, S);
		}

		fpVars.dXYMap = cgGetNamedParameter(fragmentProgram, "dXYMap");
		fpVars.dXYMap1 = cgGetNamedParameter(fragmentProgram, "dXYMap1");
		fpVars.EnvCMap = cgGetNamedParameter(fragmentProgram, "EnvCMap");
		fpVars.FoamMap = cgGetNamedParameter(fragmentProgram, "FoamMap");
		fpVars.SkyMap=cgGetNamedParameter(fragmentProgram,"SkyMap");//livenson
		fpVars.ReflMap=cgGetNamedParameter(fragmentProgram,"RMap");

		CheckCgError(Context);
		strPath=strEXE+_T("Data\\VROCEAN\\vpWaterDM.cg");
		bWorking = finder.FindFile(strPath);
		if (!bWorking)
		{
			AfxMessageBox(_T("can't find ocean file!"));
			exit(-1);
		}
		//StringToChar(strPath,FileDir);
		
		//char *newpath2 = new char;
		WideCharToMultiByte(CP_OEMCP,0,(LPCTSTR)strPath,-1,FileDir,260,0,false);

		vertexProgram = cgCreateProgramFromFile(Context,
			CG_SOURCE,/*(char*)*/FileDir, vpProfile, NULL, NULL);

		CheckCgError(Context);
		CheckCgError();

		if(vertexProgram != NULL){
			cgGLLoadProgram(vertexProgram);
			CheckCgError();
		}

		vpVars.VOfs = cgGetNamedParameter(vertexProgram, "VOfs");
		vpVars.CPos = cgGetNamedParameter(vertexProgram, "CPos");
		vpVars.Gabarites = cgGetNamedParameter(vertexProgram, "Gabarites");
		vpVars.HMap0 = cgGetNamedParameter(vertexProgram, "HMap0");
		vpVars.HMap1 = cgGetNamedParameter(vertexProgram, "HMap1");
		
		// Freshel Texture
		FreshelID = BuildFreshel_tex(128);

		strPath=strEXE+_T("Data\\VROCEAN\\sky_%s.raw");
		//StringToChar(strPath,FileDir);

		//char *newpath3 = new char;
		WideCharToMultiByte(CP_OEMCP,0,(LPCTSTR)strPath,-1,FileDir,260,0,false);

		Cube0ID = load_cubemap(/*(const char*)FileDir*/FileDir, 512);

		strPath=strEXE+_T("Data\\VROCEAN\\noise.raw");
		//StringToChar(strPath,newPath);

		//char *newpath4 = new char;
		WideCharToMultiByte(CP_OEMCP,0,(LPCTSTR)strPath,-1,FileDir,260,0,false);

		NoiseID = load_tex(FileDir, 512);
		/*LoadRaw("Data/Land_H.raw", LandH, sizeof(LandH));
		LandCID  = load_tex("Data/Land_C.raw", 512);*/
	#if 1
		if (1) { //GL.NV_vertex_program3
			GLint vtex_units;
			glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS_ARB, &vtex_units);

			strPath=strEXE+_T("Data\\VROCEAN\\FoamNV40.raw");
			//StringToChar(strPath,FileDir);	

			//char *newpath5 = new char;
			WideCharToMultiByte(CP_OEMCP,0,(LPCTSTR)strPath,-1,FileDir,260,0,false);

			FoamID = load_tex(FileDir, WaterTexSize, 1, 4);

			float *BMap  = new float[WaterTexSize*WaterTexSize];
			BYTE *BMap1 = new BYTE[WaterTexSize*WaterTexSize];
			BYTE *BMap2 = new BYTE[WaterTexSize*WaterTexSize];
			float *pBuf = new float[WaterTexSize*WaterTexSize*4];
			float *pBuf2 = new float[WaterTexSize*WaterTexSize*4];
			float *pBuf4 = new float[WaterTexSize*WaterTexSize*4];

			// 8 step interpolation between animation frames
			
			for(int l = 0; l < WaterImages*NUMINTERPOLATION; l++)  {
				// Load Water maps, scale H to 0..1
				// To do quadric /\  waves distorsion				
				char LoadFN[256];//record the filename --livenson 20081018
				if ((l%NUMINTERPOLATION)==0) {
					if (l==0) {
						sprintf(LoadFN, "Data\\VROCEAN\\HMaps\\WaterH" "%02i" ".raw", l/8);
						strPath=strEXE;
						strPath+=LoadFN;
						//StringToChar(strPath,FileDir);
						//char *newpath6 = new char;
						WideCharToMultiByte(CP_OEMCP,0,(LPCTSTR)strPath,-1,FileDir,260,0,false);

						LoadRaw(FileDir, BMap1, WaterTexSize*WaterTexSize);
					}
					else { // Copy previous
						memcpy(BMap1, BMap2, WaterTexSize*WaterTexSize);
					}
				}

				// Interpolate intermediate map
				int l1= (l/NUMINTERPOLATION+1)&(WaterImages-1);
				if ((l%NUMINTERPOLATION)==0) {
					sprintf(LoadFN, "Data\\VROCEAN\\HMaps\\WaterH" "%02i" ".raw", l1);
					strPath=strEXE;
					strPath+=LoadFN;
					//StringToChar(strPath,FileDir);

					//char *newpath7 = new char ();
					WideCharToMultiByte(CP_OEMCP,0,(LPCTSTR)strPath,-1,FileDir,260,0,false);

					LoadRaw(FileDir, BMap2, WaterTexSize*WaterTexSize);
				}
				float R = float((l&(NUMINTERPOLATION-1)))/((float)(NUMINTERPOLATION));
				for (int y = 0; y < WaterTexSize; y++) {
					for (int x = 0; x < WaterTexSize; x++) {
						int PixAddr = y*WaterTexSize+x;
						float t = float(BMap1[PixAddr])*(1-R)+float(BMap2[PixAddr])*R;	 
						float H = pow((t/255.0f),1.7f);
						if (H < 0) H = 0; if(H > 1.0f) H = 1.0f; 
						BMap[PixAddr] = H;
					}
				}

				float *pB = pBuf;
				// float MinV = 1.0f, MaxV = 0;
				int Mask = WaterTexSize-1;
				for (int y = 0; y < WaterTexSize; y++)
				{
					for (int x = 0; x < WaterTexSize; x++) {
						float V = BMap[y*WaterTexSize+x];
						pB[0] = V;
						pB[1] = BMap[y*WaterTexSize+((x+1) & Mask)]-BMap[y*WaterTexSize+((x-1) & Mask)];
						pB[2] = BMap[x+((y+1) & Mask)*WaterTexSize]-BMap[x+((y-1) & Mask)*WaterTexSize];

						pB[1] = pB[1]*0.5*0.5+0.5;
						pB[2] = pB[2]*0.5*0.5+0.5;

						pB+=3;
					}
				}

				glGenTextures(1, &WaterReflDMID[l]); //HMap1  ---livenson 20081018
				glBindTexture(GL_TEXTURE_2D, WaterReflDMID[l]);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				int SZ = WaterTexSize;
				for (int y = 0; y < SZ; y++) {
					for (int x = 0; x < SZ; x++) {
						pBuf2[(y*SZ + x)*4+0] = pBuf[(y*SZ + x)*3+0];
					}
				}
				float *pBuf3 = new float[(SZ/2.0)*(SZ/2.0)*4], *pB3 = pBuf3;
				{ 
					for (int k = 0; k < 10; k++) {

						for (int y = 0; y < SZ; y++) {
							for (int x = 0; x < SZ; x++) {
								//pBuf2[(y*SZ + x)*4+0] = pBuf[(y*SZ + x)*4+0];
								pBuf2[(y*SZ + x)*4+1] = pBuf2[(y*SZ + (x+1)%SZ)*4+0];
								pBuf2[(y*SZ + x)*4+2] = pBuf2[(((y+1)%SZ)*SZ + x)*4+0];
								pBuf2[(y*SZ + x)*4+3] = pBuf2[(((y+1)%SZ)*SZ + (x+1)%SZ)*4+0];
							}
						}

						// Load 2x downscaled - save memory 4x times
						if (k > 0) {
							glTexImage2D(GL_TEXTURE_2D, k-1, GL_RGBA_FLOAT32_ATI/*GL_LUMINANCE_FLOAT32_ATI*/, 
								SZ, SZ, 0, /*GL_LUMINANCE*/GL_RGBA, GL_FLOAT, pBuf2);
						}
						SZ/=2;  int SZ2 = SZ*2;
						if (SZ < 1) break;
						for (int y = 0; y < SZ; y++) {
							for (int x = 0; x < SZ; x++) {
								float F = pBuf2[((y*2)*SZ2+x*2)*4+0];
								F += pBuf2[((y*2)*SZ2+x*2+1)*4+0];
								F += pBuf2[((y*2+1)*SZ2+x*2)*4+0]; 
								F += pBuf2[((y*2+1)*SZ2+x*2+1)*4+0]; 
								F/=4.0;
								pBuf3[(y*SZ+x)*4+0] = F;
							}
						}
						float *t = pBuf2; pBuf2 = pBuf3; pBuf3 = t;
					}
				}
				pBuf3 = pB3; delete[] pB3;

				glGenTextures(1, &WaterRefldXYID[l]); 
				glBindTexture(GL_TEXTURE_2D, WaterRefldXYID[l]);
				glTexParameteri(GL_TEXTURE_2D,GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				for (int y = 0; y < WaterTexSize; y++) {
					for (int x = 0; x < WaterTexSize; x++) {
						int ii = (y*WaterTexSize + x);
						pBuf4[ii*4+0] = pBuf[ii*3+0];
						pBuf4[ii*4+1] = pBuf[ii*3+1];
						pBuf4[ii*4+2] = pBuf[ii*3+2];
						pBuf4[ii*4+3] = 1.0f;
					}
				}
				// Load texture - with rejecting A-channel 
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB_FLOAT16_ATI, 
					WaterTexSize, WaterTexSize, 0, GL_RGBA, GL_FLOAT, pBuf4);					
			}
			
			delete [] pBuf;
			delete [] pBuf2;
			delete [] pBuf4;
			delete [] BMap;
			delete [] BMap1;
			delete [] BMap2;

			// Create radial grid ring
			{        
				TVertexV1C *pVB = new TVertexV1C[4*384];
				int *pIB = new int[(RADIUS+1)*(CIRCLEPART+1)*6];

				nVert = 0;
				int j;
				for(j = 0; j < RADIUS; j++) {
					float R0 = 1;//(SQR(j*RScale))*MaxR;
					for (int i = 0; i < CIRCLEPART; i++) {
						float A = (i*M_PI*2.0f)/((float)CIRCLEPART);
						float dX = cos(A), dY = sin(A); nVert++;
						pVB[j*CIRCLEPART+i].Set(R0*dX/**pow(j,4)*pow(1/512.0,4)*4500*/, R0*dY/**pow(j,4)*pow(1/512.0,4)*4500*/,  j); //glVertex3fv(A.Get());
					}
				}

				nInd = 0;
				for (int i = 0; i < CIRCLEPART+1; i++) { 
					for(j = 0; j < RADIUS-1; j++) {
						int Ind[4] = {j*CIRCLEPART+(i%CIRCLEPART), (j+1)*CIRCLEPART+(i%CIRCLEPART), (j+1)*CIRCLEPART+((i+1)%CIRCLEPART), (j)*CIRCLEPART+((i+1)%CIRCLEPART)};
						pIB[nInd++] = Ind[0];  pIB[nInd++] = Ind[1];  pIB[nInd++] = Ind[2];
						pIB[nInd++] = Ind[0];  pIB[nInd++] = Ind[2];  pIB[nInd++] = Ind[3];
					}
				}

				glGenBuffersARB(1, &VBO_ID);
				glBindBufferARB(GL_ARRAY_BUFFER_ARB, VBO_ID);
				glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(TVertexV1C)*nVert, pVB, GL_STATIC_DRAW_ARB); 

				glBindBufferARB( GL_ARRAY_BUFFER_ARB, NULL );
				glGenBuffersARB(1, &IBO_ID);
				glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, IBO_ID);
				glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, sizeof(int)*nInd, pIB, GL_STATIC_DRAW_ARB);

				glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, NULL);

				delete[] pVB;		

			} 
		}
	#endif  
		m_bHasLoaded=true;

	}

	#define GridSize 128
	#define FarR (4*4000.0)
	void CRenderer::RenderSky() {
		glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, Cube0ID);	
		glEnable(GL_TEXTURE_CUBE_MAP_ARB);	

		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP_EXT);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP_EXT);
		glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP_EXT);

		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
		glEnable(GL_TEXTURE_GEN_R);

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		glMatrixMode(GL_TEXTURE);
		glPushMatrix();
		glLoadIdentity();

		//glRotatef(-90.0, 1.0, 1.0, 0);    
		//glScalef(-1.0, -1.0, -1.0);      
		//glScalef(+1,+1,-1);
		glRotatef(-rRotationX, 0, 1, 0);
		glRotatef(-rRotationY, 1, 0, 0);      

		glRotatef(180, 0, 0, 1);
		//glRotatef(-90.0, 1.0, 0.0, 0);         
		//glRotatef(-rRotationY, 1, 0, 0);

		glutSolidSphere(FarR, 10, 10);

		glPopMatrix();

		glMatrixMode(GL_MODELVIEW);

		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
		glDisable(GL_TEXTURE_GEN_R);

		glDisable(GL_TEXTURE_CUBE_MAP_ARB);

	}

	void CRenderer::DropLoad()
	{
		glDeleteTextures(WaterImages*NUMINTERPOLATION,WaterReflDMID);
		glDeleteTextures(WaterImages*NUMINTERPOLATION,WaterRefldXYID);
		glDeleteBuffersARB(1,&VBO_ID);
		glDeleteBuffersARB(1,&IBO_ID);
		m_bHasLoaded=false;
		return;
	}

	void CRenderer::RenderSea() {
		if (!m_bHasLoaded)
		{
			return;
		}
		GetCurWaterHeight();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		float Time = GetTime();
		//Time=0;

		int Frame0 = int(0.13*Time*WaterImages*NUMINTERPOLATION) & (WaterImages*NUMINTERPOLATION-1);
		int Frame1 = int(0.16*Time*WaterImages*NUMINTERPOLATION+WaterImages*NUMINTERPOLATION-1) & (WaterImages*NUMINTERPOLATION-1);
		//Frame0=Frame1=1;

		float MaxR = 36000/8, RScale = 1.0f/512.0f;
		Weather = 0.0;

		float _S = (1-Weather)*0.5 + 0.25;
		float H = 2.5*_S;  //H *= 3;
		H*=1.5;
		
		//TexScale parameter determine the density of water texture -- livenson 20091114
		float TexScale = m_TexScale*(1.0+(0.5-abs(Weather-0.5))*4);//*12.5;

		

		cgGLEnableProfile(vpProfile);
		cgGLEnableProfile(fpProfile);
		cgGLBindProgram(vertexProgram);

		cgGLSetParameter4f(vpVars.VOfs, CamX, CamZ, pow(RScale, 4)*MaxR, 0);
		cgGLSetParameter4f(vpVars.CPos, CamX*0, CamY*0, CamY-m_WaterHeight, 0);
		cgGLSetParameter4f(vpVars.Gabarites, TexScale, 256.0f/2.0f, H, 1.0/TexScale);
		cgGLSetTextureParameter(vpVars.HMap0,  WaterReflDMID[Frame0]);
		cgGLEnableTextureParameter(vpVars.HMap0);
		cgGLSetTextureParameter(vpVars.HMap1,  WaterReflDMID[Frame1]);
		cgGLEnableTextureParameter(vpVars.HMap1);
		CheckCgError();
		cgGLBindProgram(fragmentProgram);
		cgGLSetTextureParameter(fpVars.dXYMap,  WaterRefldXYID[Frame0]);
		cgGLEnableTextureParameter(fpVars.dXYMap);
		cgGLSetTextureParameter(fpVars.dXYMap1,  WaterRefldXYID[Frame1]);
		cgGLEnableTextureParameter(fpVars.dXYMap1);
		cgGLSetTextureParameter(fpVars.EnvCMap, Cube0ID);
		cgGLEnableTextureParameter(fpVars.EnvCMap);

		cgGLSetTextureParameter(fpVars.FoamMap,  FoamID);
		cgGLEnableTextureParameter(fpVars.FoamMap);
		cgGLSetTextureParameter(fpVars.SkyMap,  NoiseID);//livenson 20081203
		cgGLEnableTextureParameter(fpVars.SkyMap);
		cgGLSetTextureParameter(fpVars.ReflMap,WaterReflID);
		cgGLEnableTextureParameter(fpVars.ReflMap);

		cgGLSetParameter4f(fpVars.c[0], 0.2*0.15,1*0.15,0.85*0.15,0.15); //diffuse+Ambient in w 
		cgGLSetParameter4f(fpVars.c[2], +0.9,-0.2, +0.1,m_Opacity); //Sun direction
		float cMaxIntensity  = 0.8, cMinIntensity = 0.05, FreshelCosClamp=-0.1;
		float Wavy = 0.125;// Wavy = 1 Normal, < 1 Wild
		float FoamB = +0.50+2*0.15, FoamKx = 0.8/(1-FoamB);
		cgGLSetParameter4f(fpVars.c[3], cMinIntensity, cMaxIntensity-cMinIntensity, FreshelCosClamp, Wavy*2);
		cgGLSetParameter4f(fpVars.c[9], FoamKx, -FoamB*FoamKx, 0, 0);
		cgGLSetParameter4f(fpVars.c[8],Time,0,m_MirrorMode,0);//livenson 20081128
		CheckCgError();

		glPushMatrix();
			glTranslatef(CamX, m_WaterHeight,CamZ);// Move grid Center --keep the point of eye coordinate with the scene --livenson 20081018
			glRotatef(90.0,1,0,0);
			glScalef(m_WaterScale,m_WaterScale,-1);
			glEnable(GL_TEXTURE_2D);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, VBO_ID);
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, IBO_ID);
			glVertexPointer(3, GL_FLOAT, sizeof(TVertexV1C), 0/*CylinderS*/);
			glEnableClientState(GL_VERTEX_ARRAY);
			if (m_bRenderLargeArea)
			{
				glDrawElements(GL_TRIANGLES, nInd, GL_UNSIGNED_INT, 0);  
			}
			glDisableClientState(GL_VERTEX_ARRAY);		
		glPopMatrix();

		if (m_WaterNodeArray.GetCount()>0)
		{
			glPushMatrix();
			glRotatef(90.0,1,0,0);
			glScalef(1,1,-1);
			for (int WaterNodeIndex=0;WaterNodeIndex<m_WaterNodeArray.GetSize();WaterNodeIndex++)
			{
				Ocean_WaterNode Node=m_WaterNodeArray.GetAt(WaterNodeIndex);
				cgGLSetParameter4f(vpVars.CPos, CamX, CamZ,CamY,  1);
				glBindBufferARB(GL_ARRAY_BUFFER_ARB, Node.m_VBO_ID);
				glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, Node.m_IBO_ID);
				glVertexPointer(3, GL_FLOAT, sizeof(TVertexV1C), 0);
				glEnableClientState(GL_VERTEX_ARRAY);
				glDrawElements(GL_TRIANGLES, Node.m_nInd, GL_UNSIGNED_INT, 0);  
				glDisableClientState(GL_VERTEX_ARRAY);	
			}					
			glPopMatrix();
		}
		

		cgGLDisableProfile(vpProfile);
		cgGLDisableProfile(fpProfile);
		cgGLDisableTextureParameter(vpVars.HMap0);
		cgGLDisableTextureParameter(vpVars.HMap1);
		cgGLDisableTextureParameter(fpVars.dXYMap);
		cgGLDisableTextureParameter(fpVars.dXYMap1);
		cgGLDisableTextureParameter(fpVars.EnvCMap);
		cgGLDisableTextureParameter(fpVars.FoamMap);
		cgGLDisableTextureParameter(fpVars.SkyMap);
		cgGLDisableTextureParameter(fpVars.ReflMap);
		
		glDisable(GL_BLEND);

	}

	void CRenderer::RenderIsland() {
		//return; 
		GLfloat s1_vector[4] = {1.0f/LandSize/4.0f, 0.0, 0.0, 0.0};
		GLfloat t1_vector[4] = {0.0,  0.0, 1.0f/LandSize/4.0f,0.0};
		glTexGeni (GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni (GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

		glTexGenfv(GL_S, GL_OBJECT_PLANE, s1_vector);
		glTexGenfv(GL_T, GL_OBJECT_PLANE, t1_vector);

		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, LandCID);

		glActiveTextureARB(GL_TEXTURE1_ARB);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, NoiseID);

		GLfloat s2_vector[4] = {11.0f/LandSize/4.0f, 0.0, 0.0, 0.0};
		GLfloat t2_vector[4] = {0.0,  0.0, 11.0f/LandSize/4.0f,0.0};
		glTexGeni (GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni (GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

		glTexGenfv(GL_S, GL_OBJECT_PLANE, s2_vector);
		glTexGenfv(GL_T, GL_OBJECT_PLANE, t2_vector);

		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);  

		// Render Landscape 
		for (int y = 0; y < LandSize-1; y++) {
			glBegin(GL_TRIANGLE_STRIP);
			for (int x = 0; x < LandSize-1; x++) {
				//glVertex3f(x*4, y*4, LandH[y][x]-6.0f);
				//glVertex3f(x*4, y*4+4, LandH[y+1][x]-6.0f);
			}
			glEnd();
		}

		glDisable(GL_TEXTURE_2D);
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);

		glActiveTextureARB(GL_TEXTURE0_ARB);
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
	}

	void CRenderer::Render(int Reflection) {
		//if (!Reflection) RenderSky();
		if (!Reflection)RenderSea();
		//if (!Reflection) RenderIsland();
		if ( b_showLines )RenderLines();
	}

	void CRenderer::CreateNoiseTexture()
	{
		for(int i = 0; i < TEXTUREWIDTH; i++)
			for(int j = 0; j < TEXTUREWIDTH; j++)
				m_pfNoiseTextureMap[i][j] = (PRNGenerator(i*TEXTUREWIDTH + j) + 1.0) / 2;
	}

	float CRenderer::PRNGenerator(int x)
	{
		x = (x << 13) ^ x;
		int Prime1 = 15731;
		int Prime2 = 789221;
		int Prime3 = 1376312589;

		return (1.0 - ((x * (x*x*Prime1 + Prime2) + Prime3) & 0x7fffffff) / 1073741824.0);
	}

	bool CRenderer::CreateCurrentWaterNode()
	{
		Ocean_WaterNode Node;

		if (m_PointArray.GetCount()<2)
		{
			return false;
		}

		//得到	Node.m_MaxXZ,Node.m_MinXZ,Node.m_Heighty
		for (int i=0;i<m_PointArray.GetSize();i++)
		{
			Ocean_Vec3 vec3=m_PointArray.GetAt(i);
			if (vec3.m_x>Node.m_MaxXZ.x)
			{
				Node.m_MaxXZ.x=vec3.m_x;
			}
			if (vec3.m_x<Node.m_MinXZ.x)
			{
				Node.m_MinXZ.x=vec3.m_x;
			}
			if (vec3.m_z>Node.m_MaxXZ.y)
			{
				Node.m_MaxXZ.y=vec3.m_z;
			}
			if (vec3.m_z<Node.m_MinXZ.y)
			{
				Node.m_MinXZ.y=vec3.m_z;
			}
			if (vec3.m_y<=Node.m_Heighty)
			{
				Node.m_Heighty=vec3.m_y;
			}
		}
		int DistanceX=Node.m_MaxXZ.x-Node.m_MinXZ.x;
		int DistanceZ=Node.m_MaxXZ.y-Node.m_MinXZ.y;
		if (DistanceX<5||DistanceZ<5)
		{
			AfxMessageBox(_T("所选水面区域长或宽太小，请重新选择！"));
			return false;
		}
		int Step=10;
		if (DistanceX<DistanceZ)
		{
			Step=DistanceX/3;
		}
		else
			Step=DistanceZ/3;
		int NumX=(DistanceX+10)/Step+1;
		int NumZ=(DistanceZ+10)/Step+1;

		Node.m_nVert = 0;
		TVertexV1C *pVB = new TVertexV1C[NumX*NumZ];
		int *pIB = new int[(NumX+1)*(NumZ+1)*6];
		for(int i=0;i<NumZ;i++)
		{
			for(int j=0;j<NumX;j++)
			{
				pVB[i*NumX+j].Set(Node.m_MinXZ.x-5+j*Step,Node.m_MinXZ.y-5+i*Step,Node.m_Heighty);
				Node.m_nVert++;
			}
		}
		Node.m_nInd = 0;
		for (int i = 0; i < NumX-1; i++) { 
			for(int j = 0; j < NumZ-1; j++) {
				int Ind[4] = {j*NumX+(i%NumX), (j+1)*NumX+(i%NumX), (j+1)*NumX+((i+1)%NumX), (j)*NumX+((i+1)%NumX)};
				pIB[Node.m_nInd++] = Ind[0];  pIB[Node.m_nInd++] = Ind[1];  pIB[Node.m_nInd++] = Ind[2];
				pIB[Node.m_nInd++] = Ind[0];  pIB[Node.m_nInd++] = Ind[2];  pIB[Node.m_nInd++] = Ind[3];
			}
		}
		glGenBuffersARB(1, &Node.m_VBO_ID);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, Node.m_VBO_ID);
		glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(TVertexV1C)*Node.m_nVert, pVB, GL_STATIC_DRAW_ARB); 

		glGenBuffersARB(1, &Node.m_IBO_ID);
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, Node.m_IBO_ID);
		glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, sizeof(int)*Node.m_nInd, pIB, GL_STATIC_DRAW_ARB);
		delete pIB;
		delete []pVB;
		m_WaterNodeArray.Add(Node);
		return true;
	}

	void CRenderer::CreateWaterFromNode(Ocean_WaterNode Node)
	{
		int DistanceX=Node.m_MaxXZ.x-Node.m_MinXZ.x;
		int DistanceZ=Node.m_MaxXZ.y-Node.m_MinXZ.y;
		int Step=10;
		if (DistanceX<DistanceZ)
		{
			Step=DistanceX/3;
		}
		else
			Step=DistanceZ/3;
		int NumX=(DistanceX+10)/Step+1;
		int NumZ=(DistanceZ+10)/Step+1;

		Node.m_nVert = 0;
		TVertexV1C *pVB = new TVertexV1C[NumX*NumZ];
		int *pIB = new int[(NumX+1)*(NumZ+1)*6];
		for(int i=0;i<NumZ;i++)
		{
			for(int j=0;j<NumX;j++)
			{
				pVB[i*NumX+j].Set(Node.m_MinXZ.x-5+j*Step,Node.m_MinXZ.y-5+i*Step,Node.m_Heighty);
				Node.m_nVert++;
			}
		}
		Node.m_nInd = 0;
		for (int i = 0; i < NumX-1; i++) { 
			for(int j = 0; j < NumZ-1; j++) {
				int Ind[4] = {j*NumX+(i%NumX), (j+1)*NumX+(i%NumX), (j+1)*NumX+((i+1)%NumX), (j)*NumX+((i+1)%NumX)};
				pIB[Node.m_nInd++] = Ind[0];  pIB[Node.m_nInd++] = Ind[1];  pIB[Node.m_nInd++] = Ind[2];
				pIB[Node.m_nInd++] = Ind[0];  pIB[Node.m_nInd++] = Ind[2];  pIB[Node.m_nInd++] = Ind[3];
			}
		}
		glGenBuffersARB(1, &Node.m_VBO_ID);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, Node.m_VBO_ID);
		glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(TVertexV1C)*Node.m_nVert, pVB, GL_STATIC_DRAW_ARB); 

		glGenBuffersARB(1, &Node.m_IBO_ID);
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, Node.m_IBO_ID);
		glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, sizeof(int)*Node.m_nInd, pIB, GL_STATIC_DRAW_ARB);
		delete pIB;
		delete []pVB;
		m_WaterNodeArray.Add(Node);
		return;
	}
	void CRenderer::ReadWaterFile()
	{
		char dir[MAX_PATH],FileDir[MAX_PATH];
		GetModuleFileName(NULL,(LPWCH)dir, MAX_PATH);
		(_tcsrchr((wchar_t *)dir, (wchar_t)_T('\\')))[1] = 0; //删除文件名，只获得路径
		CString strEXE;
		strEXE.Format(_T("%s"),dir);
		FILE *fp;
		CString StrWaterFile;
		StrWaterFile=strEXE+_T("Data\\VROCEAN\\ocean.txt");
		//StringToChar(StrWaterFile,FileDir);

		//char *newPath = new char;
		WideCharToMultiByte(CP_OEMCP,0,(LPCTSTR)StrWaterFile, -1, FileDir,260,0,false);

		fp = fopen(FileDir,"rb");

		if(!fp)
		{
			// AfxMessageBox(_T("no ocean file!"));
			return;
		}
		int NodeCount;
		fscanf(fp,"%d\n",&NodeCount);
		for(int i=0;i<NodeCount;i++)
		{
			VR_Ocean::Ocean_WaterNode Node;
			fscanf(fp,"%d %d %d %d %f\n",&Node.m_MinXZ.x,&Node.m_MinXZ.y,&Node.m_MaxXZ.x,&Node.m_MaxXZ.y,&Node.m_Heighty);
			CreateWaterFromNode(Node);
		}
		fclose(fp);
		return;
	}

	void CRenderer::GetCurWaterHeight()
	{
		for(int i=0;i<m_WaterNodeArray.GetCount();i++)
		{
			Ocean_WaterNode Node=m_WaterNodeArray.GetAt(i);
			if(this->CamX<=Node.m_MaxXZ.x&&CamX>=Node.m_MinXZ.x
				&&CamZ<=Node.m_MaxXZ.y&&CamZ>=Node.m_MinXZ.y)
			{
				m_WaterHeight=Node.m_Heighty;
				m_CurNodeIndex=i;
				return;
			}
		}
		m_CurNodeIndex=-1;
	}

	void CRenderer::SetCurWaterHeight(float height)
	{
		m_WaterNodeArray.GetAt(m_CurNodeIndex).m_Heighty = height;
	}

	void CRenderer::RenderLines()
	{
		if ( m_PointArray.GetCount() < 1 )
		{
			return;
		}

		glPushMatrix();

		glDisable( GL_TEXTURE_2D );
		glLineWidth(3.0f);
		glDisable( GL_DEPTH_TEST );

		glColor3f( 1.0, 0.0, 0.0 );

		//glBegin( GL_LINE_STRIP );
		//for (int i=0;i<m_PointArray.GetSize();i++)
		//{
		//	Ocean_Vec3 vec3=m_PointArray.GetAt(i);

		//	glVertex3f( vec3.m_x, vec3.m_y, vec3.m_z );
		//}
		//glEnd();

		glBegin( GL_LINE_STRIP );

		glVertex3f( roundPoint1.m_x, roundPoint1.m_y, roundPoint1.m_z );
		glVertex3f( roundPoint2.m_x, roundPoint2.m_y, roundPoint2.m_z );
		glVertex3f( roundPoint3.m_x, roundPoint3.m_y, roundPoint3.m_z );
		glVertex3f( roundPoint4.m_x, roundPoint4.m_y, roundPoint4.m_z );
		glVertex3f( roundPoint1.m_x, roundPoint1.m_y, roundPoint1.m_z );

		glEnd();

		glPopMatrix();
	}

	void CRenderer::calculateRounding()
	{
		if ( m_PointArray.GetCount() < 2 )
		{
			return;
		}

		double pointMinX = std::numeric_limits<double>::infinity();
		double pointMaxX = -(std::numeric_limits<double>::infinity());

		double pointMinY = std::numeric_limits<double>::infinity();

		double pointMinZ = std::numeric_limits<double>::infinity();
		double pointMaxZ = -(std::numeric_limits<double>::infinity());

		for (int i=0;i<m_PointArray.GetSize();i++)
		{
			Ocean_Vec3 vec3=m_PointArray.GetAt(i);

			if ( vec3.m_x < pointMinX )		// 求最小X
			{
				pointMinX = vec3.m_x;
			}

			if ( vec3.m_x > pointMaxX)		// 最大X
			{
				pointMaxX = vec3.m_x;
			}

			if ( vec3.m_y < pointMinY )		// 最小Y
			{
				pointMinY = vec3.m_y;
			}

			if ( vec3.m_z < pointMinZ )		// 最小Z
			{
				pointMinZ = vec3.m_z;
			}

			if ( vec3.m_z > pointMaxZ )		// 最大Z
			{
				pointMaxZ = vec3.m_z;
			}

		}
		roundPoint1.m_x = pointMinX;
		roundPoint1.m_y = pointMinY;
		roundPoint1.m_z = pointMinZ;

		roundPoint2.m_x = pointMaxX;
		roundPoint2.m_y = pointMinY;
		roundPoint2.m_z = pointMinZ;

		roundPoint3.m_x = pointMaxX;
		roundPoint3.m_y = pointMinY;
		roundPoint3.m_z = pointMaxZ;

		roundPoint4.m_x = pointMinX;
		roundPoint4.m_y = pointMinY;
		roundPoint4.m_z = pointMaxZ;

	}

	void CRenderer::initialRundPoint()
	{
		roundPoint1.m_x = 0.0;
		roundPoint1.m_y = 0.0;
		roundPoint1.m_z = 0.0;

		roundPoint2.m_x = 0.0;
		roundPoint2.m_y = 0.0;
		roundPoint2.m_z = 0.0;

		roundPoint3.m_x = 0.0;
		roundPoint3.m_y = 0.0;
		roundPoint3.m_z = 0.0;

		roundPoint4.m_x = 0.0;
		roundPoint4.m_y = 0.0;
		roundPoint4.m_z = 0.0;
	}

}
#pragma once

#include <vgKernel/vgkSingleton.h>
#include <vgKernel/vgkRenderCommand.h>
#include "vgNoise\vgnNoiseGeoData.h"
#include "vgNoise\vgnContour.h"
#include "vgNoise\vgnClrFileDialog.h"

#include <vgGIS3D/vggiGeometry.h>

#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glaux.h>		// Header File For The Glaux Library

namespace vgNoise
{
	class NoiseManager : public vgKernel::Singleton<NoiseManager>
	{
		friend class vgKernel::Singleton<NoiseManager>;
	private:
		NoiseManager();

	public:
		~NoiseManager();
		
		void RenderNoise();
	
		float m_faceWidth, m_faceHeight;
	public:

		void setInc(float  v) { m_inc = v; }
		float getInc() { return m_inc; }

	public:
		//Noise coutour add by huangbx from doc
		CContour* m_pContour;
		CCurveList* 	m_pCureList;
		CContourFillArray m_ContourFillSets;
		CContourObjArray m_ContourObjSets; //绘制对象集合
		float m_inc;
		CValueList m_Values;
		BOOL m_bDrawGrid;
		CColorLookUpTable m_ColorTable;
		CNoiseGeoData m_GeoData;
		typedef CArray<CGeoPoint,CGeoPoint&> CCurve;
		typedef CTypedPtrList<CPtrList, CCurve*> CCurveList;
		float m_value;
		CString str;

		//attribute from view
		CDC*	m_pDC;
		HGLRC	m_hGLContext;
		//网格大小
		float griddx;
		float griddz;
		int linecount;
		//包围盒信息
		float boxMinX;
		float boxMinY;
		float boxMinZ;
		float boxMaxX;
		float boxMaxY;
		float boxMaxZ;

		float bottomY;

		float getbottomY( ){return bottomY;}
		void setbottomY(float bottomy){bottomY=bottomy;}

		float getboxMinX( ){ return boxMinX;}
		void setboxMinX(float boxminx){ boxMinX=boxminx;}
		float getboxMinY( ){ return boxMinY;}
		void setboxMinY(float boxminy){ boxMinY=boxminy;}
		float getboxMinZ( ){ return boxMinZ;}
		void setboxMinZ(float boxminz){ boxMinZ=boxminz;}
		int getboxMaxX( )	{ return boxMaxX;}
		void setboxMaxX(float boxmaxx){ boxMaxX=boxmaxx;}
		int getboxMaxY( )	{ return boxMaxY;}
		void setboxMaxY(float boxmaxy){ boxMaxY=boxmaxy;}
		float getboxMaxZ( ) { return boxMaxZ;	}
		void setboxMaxZ(float boxmaxz){ boxMaxZ=boxmaxz;}
		//显示标识设定
		BOOL ContourShowFlag;
		BOOL ContourFillFlag;
		BOOL NoiseGridShowFlag;
		BOOL NoiseGridValueShowFlag;
		BOOL BgSupportFlag;
		BOOL SceneBorderFlag;
		BOOL NoiseAnnoyFlag;

		GLuint	texture[2];			// 底图支持纹理
		GLuint	base;		
		GLYPHMETRICSFLOAT gmf[256];	
		//噪声烦恼度
		int m_iX[76], m_iY[76], m_iZ[76];
		float m_reIX[76], m_reIY[76];
		float m_fTX[76], m_fTY[76], m_fTZ[76];

		int m_iFrom[166], m_iTo[166];


		BOOL m_bTextureOk;
		CString m_strBmp;
		BOOL g_bMesh;
		/*int	g_iAU1[17];
	    int	g_iAU2[33];
		int	g_iAU1625[13];
		int	g_iAU27[33];
		int	g_iAU4[57];
		int	g_iAU9[77];
		int	g_iAU10[29];
		int	g_iAU20[37];
		int	g_iAU12[49];
		int	g_iAU18[29];
		int	g_iAU45[49];
		int	g_iAU17[17];*/

		float g_fAU1;
		void setgfau1( float gfau1){ g_fAU1=gfau1;};
		float g_fAU2;
		void setgfau2( float gfau2){ g_fAU2=gfau2;};
		float g_fAU1625;
		void setgfau1625( float gfau1625){ g_fAU1625=gfau1625; };
		float g_fAU27;
		void setgfau27( float gfau27){ g_fAU27=gfau27; };
		float g_fAU4;
		void setgfau4( float gfau4){g_fAU4=gfau4; };
		float g_fAU9;
		void setgfau9( float gfau9){g_fAU9=gfau9; };
		float g_fAU10;
		void setgfau10( float gfau10){g_fAU10=gfau10; };
		float g_fAU20;
		void setgfau20( float gfau20){g_fAU20=gfau20; };
		float g_fAU12;
		void setgfau12( float gfau12){g_fAU12=gfau12; };
		float g_fAU18;
		void setgfau18( float gfau18){g_fAU18=gfau18; };
		float g_fAU45;
		void setgfau45( float gfau45){g_fAU45=gfau45; };
		float g_fAU17;
		void setgfau17( float gfau17){g_fAU17=gfau17; };

	public:
		bool NoiseManager::OnNoiseGridDataSet();
       //method from doc
		/*afx_msg void OnLoadcolortable();*/
		void CreateContourObjs();
		void CreateContourFill();
		void RemoveAllContourFill();

		//method from view
		void RenderNoiseContour();
		afx_msg void OnNoiseGridProperty();
				void NoiseManager::OnNoiseGridCalculate();
				void NoiseManager::OnNoiseMapVertical();
		afx_msg void OnNoiseGridContourLevel();
		void RenderNoiseBackground();
		void NoiseMapFill();
		void NoiseFillContours(CContourObj* pContourObj,int j);
		afx_msg void OnNoiseGridAppearance();
		void RenderNoiseGrid();
		GLvoid BuildFont(GLvoid) /* Build Our Bitmap Font */;
		GLvoid KillFont(GLvoid) /* Delete The Font */;
		GLvoid glPrint(const char *fmt, ...) /* Custom GL "Print" Routine */;
		afx_msg void OnNoiseBgsupport();
		void RenderNoiseBorder();
		AUX_RGBImageRec* Loadbgpic(const  char *Filename); /* Loads A Bitmap Image */
		int LoadBGTextures(std::string filename,int texid); /* Load Bitmaps And Convert To Textures */
		afx_msg void OnNoiseClosebgsupport();
		int NoiseManager::OnVgSceneBorder();
		void NoiseManager::OnAnnoyParameter();
		void NoiseManager::OnAUChanged( );
		void NoiseManager::OnAnnoyTexture( );
		void NoiseManager::OnVgSceneDisable();
		void NoiseManager::OnAnnoyStd();
		void NoiseManager::SaveGridCalValue();
		bool NoiseManager::OnNoiseDataOutput();
				//void NoiseManager::OnAnnoyFlag();
	protected:
		virtual bool initialise() { return true; }
		virtual bool shutdown() { return true; }
		void NoiseManager::InitFaceMesh();
		void recalculateMeshData();
		void NoiseManager::InitTextureMesh();
		void NoiseManager::InitVertexOrder();
		void NoiseManager::MeshView();
		void NoiseManager::NoiseAnnoyTextureView();

		float NoiseManager::NoiseValCalculate(float x,float z);
		void NoiseManager::NoiseFillContours01();
		void NoiseManager::NoiseMapFill01();

		vgKernel::RenderCommand *m_pRenderContourCommand;
	};

}
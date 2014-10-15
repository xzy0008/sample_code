#ifndef __CRENDERER_HPP__
#define __CRENDERER_HPP__

#include <cg/cgGL.h>
#include "VOdefinition.h"
#include "oglrendertexture.h"
#include "OceanInputHandler.h"


#define TEXTUREWIDTH 512


namespace VR_Ocean{

	struct TTexParam {
		CGparameter tmp[20];
		int Count;
		TTexParam() { Count = 0;}
		CGparameter Add(CGparameter p, int TexID = 0) { 
		  if (TexID != 0) cgGLSetTextureParameter(p, TexID);
		  tmp[Count++] = p;
		}
		void Enable(int bEnable) {
		  for (int k = 0; k < Count; k++)
			if (bEnable) cgGLEnableTextureParameter(tmp[k]);
					else cgGLDisableTextureParameter(tmp[k]);
		}
	    
	};
	class Ocean_Vec3{
	public:
		double m_x;
		double m_y;
		double m_z;
		Ocean_Vec3(double xin,double yin,double zin)
		{
			m_x=xin;
			m_y=yin;
			m_z=zin;
		}
		Ocean_Vec3& operator =(const Ocean_Vec3& pt)
		{		
			m_x=pt.m_x;
			m_y=pt.m_y;
			m_z=pt.m_z;
			return *this;
		}

		Ocean_Vec3()
		{
			m_x=0.0;
			m_y=0.0;
			m_z=0.0;
		}
		Ocean_Vec3(Ocean_Vec3& pt)
		{
			m_x=pt.m_x;
			m_y=pt.m_y;
			m_z=pt.m_z;
		}
	};

	class Ocean_WaterNode
	{
	public:
		unsigned int m_VBO_ID;
		unsigned int m_IBO_ID;
		int m_nInd;
		int m_nVert;
		float m_Heighty;

		//record minx,minz and maxx maxz
		CPoint m_MinXZ;
		CPoint m_MaxXZ;
		
		Ocean_WaterNode& operator =(const Ocean_WaterNode& pt)
		{		
			m_VBO_ID=pt.m_VBO_ID;
			m_IBO_ID=pt.m_IBO_ID;
			m_nInd=pt.m_nInd;
			m_nVert=pt.m_nVert;
			m_Heighty=pt.m_Heighty;
			m_MinXZ=pt.m_MinXZ;
			m_MaxXZ=pt.m_MaxXZ;
			return *this;
		}

		Ocean_WaterNode()
		{
			m_MaxXZ.x=m_MaxXZ.y=-1000000;
			m_MinXZ.x=m_MinXZ.y=1000000;
			m_Heighty=1000000;
		}
		Ocean_WaterNode(Ocean_WaterNode& pt)
		{
			m_VBO_ID=pt.m_VBO_ID;
			m_IBO_ID=pt.m_IBO_ID;
			m_nInd=pt.m_nInd;
			m_nVert=pt.m_nVert;
			m_Heighty=pt.m_Heighty;
			m_MinXZ=pt.m_MinXZ;
			m_MaxXZ=pt.m_MaxXZ;
		}
	};

	/*
	class name	: sea water renderer
	time		: 2009.11.10
	author		: livenson(LiWQ)
	use			: sea water and part water rendering,
				  dll export
	*/
	class VO_EXPORT CRenderer :public vgKernel::Singleton<CRenderer>
	{
	public:
	  CRenderer();
	  bool initialise()
	  {

		  m_pOceanInput=new VR_Ocean::COceanInputHandler(VG_INPUT_OCEAN);
		  return true;
	  }

	  bool shutdown()
	  {
		  if (m_pOceanInput)
		  {
			  delete m_pOceanInput;
		  }
		  return true;
	  }

	  void Initialize();
	  void DropLoad();
	  void Render(int bReflection);
	  GLuint GetReflID() {return WaterReflID;}
	  void SetReflID(GLuint ReflID) {WaterReflID=ReflID;}

	  float rRotationX;
	  float rRotationY;
	  float CamX;
	  float CamY;
	  float CamZ;
	  float Weather;
	  bool  m_bHasLoaded;

	  bool  m_bRenderLargeArea;

	  float m_WaterHeight;
	  int   m_CurNodeIndex;
	  float m_WaterScale;
	  float m_TexScale;
	  float m_Opacity;
	  CArray<Ocean_Vec3> m_PointArray;
	  bool   m_bPointAddStart;
	  CArray<Ocean_WaterNode> m_WaterNodeArray;
	  bool CreateCurrentWaterNode();
	  void CreateWaterFromNode(Ocean_WaterNode Node);
	  void ReadWaterFile();
	  void GetCurWaterHeight();
	  void SetCurWaterHeight(float height);
	  void calculateRounding();
	  void initialRundPoint();

	  OglRenderTexture m_RenderTexture;
	  int  m_MirrorMode;

	  bool b_showLines;

	private:
	  CGcontext Context;
	  
	  CGprogram fragmentProgram;
	  CGprogram vertexProgram;
	  struct {
		CGparameter c[10];
		CGparameter dXYMap, dXYMap1;
		CGparameter EnvCMap, FoamMap;
		CGparameter SkyMap,ReflMap;//livenson 20081203
	  } fpVars;

	  struct {
		CGparameter VOfs, CPos;
		CGparameter Gabarites;
		CGparameter HMap0, HMap1;
	  } vpVars;

	  void RenderSky();
	  void RenderSea();
	  void RenderIsland();
	  void RenderLines();		// Add By FengYK @2010-01-25 20:09

	  void CreateNoiseTexture();
	  float PRNGenerator(int x);
	  GLuint m_TextureID, Cube0ID, NMapID[16], LandCID, WaterReflID, FreshelID, NoiseID;
	  GLfloat m_pfNoiseTextureMap[TEXTUREWIDTH][TEXTUREWIDTH];
	  GLuint FoamID, WaterReflDMID[128], WaterRefldXYID[128];
	  
	  float m_LightPos[3];
	  float m_specExp;

	  VR_Ocean::COceanInputHandler *m_pOceanInput;

	  Ocean_Vec3 roundPoint1;
	  Ocean_Vec3 roundPoint2;
	  Ocean_Vec3 roundPoint3;
	  Ocean_Vec3 roundPoint4;

	};
	
}

#endif // __CRENDERER_HPP__
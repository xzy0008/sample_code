
#ifndef MS3D_H
#define MS3D_H

//-------------------------------------------------------------
//                       INCLUDES                             -
//-------------------------------------------------------------
#include "image.h"
//#include "timer.h"
#include "math.h"
#include "model.h"

#include <vgKernel/vgkTimer.h>
#include <vgKernel/vgkRendererObserver.h>
#include <vgKernel/vgkRenderer.h>
#include <vgImage/vgiTextureObserver.h>
#include <vgImage/vgiTextureManager.h>

namespace vgMs3d {

	const vgKernel::RendererType RENDERER_TYPE_MS3D = 5042;


// 必须要有.字节对齐选项.
#pragma pack(push, packing)
#pragma pack(1)

	//-------------------------------------------------------------
	//- SMs3dVertex
	//- A single vertex 
	struct SMs3dVertex
	{
		unsigned char m_ucFlags; //Editor flags, unused for the loader
		CVector3 m_vVert;       //X,Y,Z coordinates
		char m_cBone;            //Bone ID (-1 = no bone)
		unsigned char m_ucUnused;
	};

	//-------------------------------------------------------------
	//- SMs3dTriangle
	//- Triangle data structure
	struct SMs3dTriangle
	{
		unsigned short m_usFlags;          //Editor flags (unused for loader)
		unsigned short m_usVertIndices[3]; //Vertex indices
		CVector3 m_vNormals[3];            //Vertex normals;
		float m_fTexCoords[2][3];          //Texture coordinates
		unsigned char m_ucSmoothing;       //Smoothing group
		unsigned char m_ucGroup;           //Group index
	};

	//-------------------------------------------------------------
	//- SMs3dMesh
	//- Group of triangles in the ms3d file
	struct SMs3dMesh
	{
		unsigned char m_ucFlags;   //Editor flags again
		char m_cName[32];          //Name of the mesh
		unsigned short m_usNumTris;//Number of triangles in the group
		unsigned short * m_uspIndices; //Triangle indices
		char m_cMaterial;          //Material index, -1 = no material

		//Let itclean up after itself like usual
		SMs3dMesh()
		{
			m_uspIndices = 0;
		}
		~SMs3dMesh()
		{
			if(m_uspIndices)
			{
				delete [] m_uspIndices;
				m_uspIndices = 0;
			}
		}
	};

	//-------------------------------------------------------------
	//- SMs3dMaterial
	//- Material information for the mesh
	struct SMs3dMaterial
	{
		char m_cName[32];         //Material name
		float m_fAmbient[4];      //Ambient values
		float m_fDiffuse[4];      //Diffuse values
		float m_fSpecular[4];     //Specular values
		float m_fEmissive[4];     //Emissive values
		float m_fShininess;       //0 - 128
		float m_fTransparency;    //0 - 1
		char m_cMode;             //unused
		char m_cTexture[128];     //Texture map file
		char m_cAlpha[128];       //Alpha map file
		// CImage m_Texture;
		vgImage::TextureObserver* m_Texture;
	};

	//-------------------------------------------------------------
	//- SMs3dKeyFrame
	//- Rotation/Translation information for joints
	struct SMs3dKeyFrame
	{
		float m_fTime;     //Time at which keyframe is started
		float m_fParam[3]; //Translation or Rotation values
	};

	//-------------------------------------------------------------
	//- SMs3dJoint
	//- Bone Joints for animation
	struct SMs3dJoint
	{
	public:
		//Data from file
		unsigned char m_ucpFlags;             //Editor flags
		char m_cName[32];                     //Bone name
		char m_cParent[32];                   //Parent name
		float m_fRotation[3];                 //Starting rotation
		float m_fPosition[3];                 //Starting position
		unsigned short m_usNumRotFrames;      //Numbee of rotation frames
		unsigned short m_usNumTransFrames;    //Number of translation frames

		SMs3dKeyFrame * m_RotKeyFrames;       //Rotation keyframes
		SMs3dKeyFrame * m_TransKeyFrames;     //Translation keyframes

		//Data not loaded from file
		short m_sParent;                     //Parent joint index

		CMatrix4X4 m_matLocal;       
		CMatrix4X4 m_matAbs;			
		CMatrix4X4 m_matFinal;

		unsigned short m_usCurRotFrame;
		unsigned short m_usCurTransFrame;

		//Clean up after itself like usual
		SMs3dJoint()
		{
			m_RotKeyFrames = 0;
			m_TransKeyFrames = 0;
			m_usCurRotFrame = 0;
			m_usCurTransFrame = 0;
		}
		~SMs3dJoint()
		{
			if(m_RotKeyFrames)
			{
				delete [] m_RotKeyFrames;
				m_RotKeyFrames = 0;
			}
			if(m_TransKeyFrames)
			{
				delete [] m_TransKeyFrames;
				m_TransKeyFrames = 0;
			}
		}
	};

	//livenson 20091225
	struct SMs3dVertexRenderFormat
	{
		CVector2 TexCoord;
		CVector3 Normal;
		CVector3 Position;
	};


#pragma pack(pop, packing)

	//-------------------------------------------------------------
	//                        CMS3D                               -
	// author: Evan Pipho (evan@codershq.com)                     -
	// date  : Aug 23, 2002                                       -
	//-------------------------------------------------------------
	//zhu添加的继承node类
	using namespace vgCore;

	class Ms3dVertexArrayMesh 
	{
	public:
		Ms3dVertexArrayMesh()
		{
			materialID = 0;
			pVertexArray = NULL;
			numOfVertex = 0;
		}

		~Ms3dVertexArrayMesh()
		{
			if (pVertexArray != NULL)
			{
				delete pVertexArray;
				pVertexArray = NULL;
			}

			numOfVertex = 0;
		}

		int materialID;

		float * pVertexArray;

		int numOfVertex;
	};

	class Ms3dIntervelData 
	{
	public:
		Ms3dIntervelData()
		{
			m_pMesh = NULL;
			m_numberOfMesh = 0;
		}

		~Ms3dIntervelData()
		{
 			if (m_pMesh != NULL)
 			{
 				delete[] m_pMesh;
 				m_pMesh = NULL;
 			}
		}

	public:
		Ms3dVertexArrayMesh* m_pMesh;
		int m_numberOfMesh;
	};

	class VGDEP_EXPORT CMs3d:/*public vgCore::Node,*/ public vgKernel::Renderer
	{
		VGK_RENDERER_IN_DECLARE( CMs3d )
	public:
		//增加的变量
		//	bool m_changed;
		bool m_load;
		bool bFirstTime;
		float fLastTime;
		float fTime;
		vgKernel::Timer m_Timer;
		int vertexbegin;
		int vertexsize;
		//BoundingBox mbox;
		vgKernel::Box _dynamicBox;
		vgKernel::Box _staticBox;
		vgKernel::Mat4 _matrix;

		vgKernel::Vec3	_positionLast;

		string loadfilename; 

		float m_fAngle;
		char m_name[200];

		//Load the MS3D file
		bool Load(const char * szFilename);
		//Render the MS3D in its current position
		void Render();
		//Render the MS3D at a certain time (in seconds)
		void Render(float fTime);
		//Animate the model from based on time (seconds)
		void Animate(float fSpeed, float fStartTime, float fEndTime, bool bLoop);
		
		//Turn the drawing of bones on and off
		void SwapBoneDraw();
		//Turn the drawing of the mesh on and off
		void SwapMeshDraw();
		//Check if displays of bones and meshes are on or off
		bool AreBonesEnabled();
		bool AreMeshesEnabled();
		////////////////
		void ComputeBoundBoxmm(float *point);
		void PreSetup();
		//////////////////////////////////////////////////////////////////////////chunyongma
 		inline bool		GetPlayState()				{	return m_bPlay;		}
 		inline float	GetStartFrame()				{	return m_startframe;}
 		inline float	GetEndFrame()				{	return m_endframe;	}
 		inline bool	GetLoopState()				{	return b_loop;		}
 		
 		inline void		SetPlayState(bool play)			{	m_bPlay = play;			bNeedCalVertex=true;	}
 		inline void		SetStartFrame(float startframe)	{	m_startframe = startframe;	bFirstTime  =true;}//chunyongma
 		inline void		SetEndFrame(float endframe)		{	m_endframe = endframe;	bFirstTime = true;	}
 		inline void		SetLoopState(bool loop)			{	b_loop = loop;		bNeedCalVertex=true;		} 		

		float m_startframe, m_endframe;
		bool m_bPlay, b_loop;
		float maxreachtime;
		bool bNeedCalBoundBox;
		bool bNeedCalVertex;
		bool bUnderWater;
		//bool m_bSelected;


		//////////////////////////////////////////////////////////////////////////
		void Play();
		void Stop();


		//Constructors
		CMs3d();
		CMs3d(const char * szFilename);
		//Destructor
		~CMs3d();

	private:

		//Total time for model animation
		float m_fTotalTime;

		//Draw the bones?
		bool m_bDrawBones;
		//Draw the mesh?
		bool m_bDrawMesh;

		//Setup joints
		void Setup();
		//Reset the timer
		void Reset();
		//Render the transformed vertices
		void RenderT();

		void updateVertices( void );
		// multiply the number of triangles by three
		int NumVertices;
		// joint id for each vertices
		int *JointsID;
		// vertices actually rendered
		SMs3dVertexRenderFormat *ModelVertices;
		SMs3dVertexRenderFormat *ModelVerticesBackup;
		//
		int NumMeshes;
		//
		int *VerticesNumOfMeshes;
		//
		int *MaterialIDOfMeshes;

		//
		unsigned short *TrianglesIndices;
	public:
		//Data
		unsigned short m_usNumVerts;
		unsigned short m_usNumTriangles;
		unsigned short m_usNumMeshes;
		unsigned short m_usNumMaterials;
		unsigned short m_usNumJoints;

		SMs3dVertex * m_pVertices;
		SMs3dVertex * m_pVerticesBackup;
		SMs3dTriangle * m_pTriangles;
		SMs3dMesh * m_pMeshes;
		SMs3dMaterial * m_pMaterials;
		SMs3dJoint * m_pJoints;


		String	GetMs3dFilePath()					{	return loadfilename; }
		void	SetMs3dFilePath(String filePath)	{	loadfilename = filePath; }
		String  m_ms3dFileName;
		String	GetMs3dFileName()					{	return m_ms3dFileName; }
		//////////////////////////////////////////////////////////////////////////
		//node 继承

			void	WriteToFile(CFile &fp);
			void	ReadFromFile(CFile &fp);

		virtual	bool	testIntersection( vgMath::Ray* ray ){return false;}
		virtual	bool	testIntersection( const vgCore::ImageRect& rect ,
			int *viewport , GLdouble* proj_mat , GLdouble* model_mat ){return false;}

	//////////////////////////////////////////////////////////////////////////
		//render 继承
	public:
		//	继承Renderer而来的接口

		vgKernel::UniqueID _uniqueID;
		String _meshName;
		virtual String getName()
		{
			return _meshName;
		}

		virtual String* getNamePtr()
		{
			return &_meshName;
		}

		virtual void setName( const String& newname )
		{
			_meshName = newname;
		}
		
		virtual vgKernel::UniqueID getUniqueID()
		{
			return _uniqueID;
		}

		void translate(Vector3 offset);
		virtual void translate(const float& x, const float& y, const float& z)
		{
			translate(Vector3(x,y,z));
		}

		virtual void rotateSelf(const float& angle, const float& x, const float& y, const float& z);
		

		virtual void scale(const float& cx, const float& cy, const float& cz, const float& x, const float& y, const float& z)
		{

		}

		virtual void rotate(const float& angle, const float& cx, const float& cy, const float& cz, 
			const float& x, const float& y, const float& z) ;

		inline const vgKernel::Mat4& getTranslationMaxtrix()
		{
			return _matrix;
		}
		/**
		继承Renderer而来的接口
		*/
		virtual vgKernel::Box getBoundingBox()
		{
			_dynamicBox = _staticBox;
			_dynamicBox.matrixTranslation(_matrix);

			return _dynamicBox;
		}
		inline const vgKernel::Vec3 getPosition() const
		{
			return _dynamicBox.getCenter();
		}

		virtual std::pair<bool, float> testIntersectWithTriangles( 
			const vgKernel::Ray& ray )
		{
	 		return pair<bool, float>(false, 0.0f);
		}

		virtual long getNumOfTriangles()
		{
			return 1;
		}

		/**
		注意,返回的是Distance的平方
		*/
		virtual float setDistanceToViewer( const vgKernel::Vec3& viewer_pos  )
		{return 0;}
	
		// add by lss when 2008-10-13 20:58:50 for cull in QuadtreeSceneManager
		virtual void	render()	{	Render(); }

		private:
			void setupVertexArray();

			void renderByVertexArray();

			Ms3dIntervelData m_meshVertexData;
			unsigned int *m_pIndexArray;

			float	_speed;
			float   m_ThetaX;
		public:
			float	getSpeed();
			void	setSpeed(float speed);
			

			void	setDefault();
		};


		VGK_RENDERER_OUT_DECLARE( CMs3d )
}

#endif //MS3D_H
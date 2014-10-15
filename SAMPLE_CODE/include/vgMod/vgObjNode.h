


#ifndef __VGOBJNODE_H__
#define __VGOBJNODE_H__


#include <vgMod/vgModelStruct.h>
#include <vgMod/vgNode.h>
#include <vgMath/vgfBoundingBox.h>


#include <vgKernel/vgkRendererObserver.h>

#include <vgKernel/vgkRenderer.h>
//#include "vgPropertyPage.h"
#include <vgKernel/vgkTransparentObject.h>
#include <vgKernel/vgkPointInPolygon.h>
#include <vgKernel/vgkShadowCastObject.h>

#include <vgKernel/vgkColorableObject.h>
#include <vgKernel/vgkRgbaQuad.h>
#include "vgMod/vgTrigger.h"
#include <vgPhys/vgphCollisionObject.h>
#include <vgKernel/vgkDissolveObject.h>
#include <vgKernel/vgkFlickerObject.h>

#include <vgKernel/vgkTimelineObserver.h>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))
#define FACEAREA  30.0


namespace vgMod{
	
	//using namespace vgCore;

	/*
	5010 -- 5030之间为QuadTreeSceneMananger的管辖范围之内
	*/
	const vgKernel::RendererType RENDERER_TYPE_MODOJBECT			= 5010;
	//const vgKernel::RendererType RENDERER_TYPE_PATICLE			= 5011;
	//const vgKernel::RendererType RENDERER_TYPE_BILLBOARD			= 5012;
	//const vgKernel::RendererType RENDERER_TYPE_MODTERRAIN			= 5013;

	const vgKernel::RendererType RENDERER_TYPE_GPUSPECIAL_WARTER	= 5020;
	const vgKernel::RendererType RENDERER_TYPE_GPUSPECIAL_SKYNODE	= 5021;
	const vgKernel::RendererType RENDERER_TYPE_GPUSPECIAL_MIRROR	= 5022;
	const vgKernel::RendererType RENDERER_TYPE_GPUSPECIAL_METAL		= 5023;
	const vgKernel::RendererType RENDERER_TYPE_GPUSPECIAL_FLOOR		= 5024;
	const vgKernel::RendererType RENDERER_TYPE_GPUSPECIAL_AVI		= 5025;
	const vgKernel::RendererType RENDERER_TYPE_GPUSPECIAL_GLASS		= 5026;
	//const vgKe rnel::RendererType RENDERER_TYPE_AUTOBUILD			= 5028;
	


	class  VGDEP_EXPORT ObjectNode : 
		public Node, 
		public vgKernel::Renderer,
		public vgKernel::ShadowCastObject , 
		public vgKernel::TransparentObject,
		public vgKernel::ColorableObject, 
		public vgMod::Trigger,
		public vgPhys::CollisionObject,
		public vgKernel::DissolveObject,
		public vgKernel::FlickerObject,
		public vgKernel::TimelineTarget
	{
		VGK_RENDERER_IN_DECLARE( ObjectNode )
	public:
		//	Part 0 :新增属性，相对class Node
		String _meshName;
		vgKernel::UniqueID _uniqueID;
		float	_squaredDistanceToViewer;
		
		//int		m_PreRenderType;//  记录上一次绘制类型
		bool	_bOpacity;
		bool	_bRenderDoubleSides;
		
		//物体颜色属性
		struct  ColorProperty
		{
			vgKernel::RgbaQuad	m_rgbaColor;
			int					reserved;		
		};
		ColorProperty			m_ColorProperty;

		//	Part 1 :新增数据块，相对class Node
		
		//	点数据
		VertexElementStruct*	pVertex;

		//	面数据，包括有材质与无材质面
		ObjectRenderControl*	pMatRender;	
		int						m_numOfNoMat;
		FaceIndex*				pFaceNoMat;

		//	阴影数据
		Vector3*				pNormalOfFaces;
		long					m_numOfVertexs;
		Vector3*				pVert;
		ShadowFaceIndex*		pShadowFaces;
		int						mShadowVolume;

		//VR-Ocean property -- livenson 20091228
		bool                    m_bUnderWater;
	
	
	public:
		//	Part 2 :新增状态变量
		//	VBO
		GLuint					_elementBufferNoMat;
		GLuint					_vertexBufferObjectID;
		bool					_isReadyForVBORender;
		bool					_deleteVBO;

		//	显示列表
		GLuint					_displayListID;
		GLuint					_displayListWithoutTexID;
		bool					_readyForDisplayListRendering;
		bool					_readyForDisplayListRenderingWithoutTex;

#if 0
		//	AutoLOD
		bool					b_renderlod;
		int						lod_facenum;
		float					lod_eyeheight;
		float					lod_dis_big;
		float					lod_dis_small;
#endif

		//	MOD版本
		int						m_nVersionMod;

		//	其它
		int						m_nVertexStride;
		int						m_nOffsetForNormals;
		int						m_nOffsetForVertices;

		int						m_nMaterialStride;

		bool					m_bReadMod;

		//	Part 3 :访问属性（无）
	public:
		/*void	   setRenderTypeInt(int renderType)		
		{	
			m_PreRenderType = m_RenderTypeInt;
			m_RenderTypeInt = renderType;
		}
		int 	   getRenderTypeInt()					{	return m_RenderTypeInt;}
		int 	   getPreRenderTypeInt()				{	return m_PreRenderType;}
		bool	getOpacity(){ return 3 == m_RenderTypeInt;}
		void	setOpacity(bool bOpacity)
		{ 
			if (bOpacity&&!getOpacity())
			{
				setRenderTypeInt(3);
			}
			else
			{

			}
		}*/


		virtual bool isTransparent()
		{
			return getOpacity();
		}

		virtual void setTransparent( bool set_to_transp = true )
		{
			setOpacity( set_to_transp );
		}

		bool*	getOpacityPtr()				{	return &_bOpacity;}
		bool*   getUnderWaterPtr()			{return &m_bUnderWater;}
		bool	getOpacity()				{	return _bOpacity;}
		void	setOpacity(bool bOpacity)	
		{	
			_bOpacity = bOpacity;
			this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);
		}

		//	Part 4 :实现父类的纯虚函数，将作为固定的对外接口
	public:
		virtual	void	Initialize();
		virtual	void	Render();

		virtual	void	WriteNodeToVG(CFile &fp);
		virtual	void	ReadNodeFromVG(CFile &fp);

		virtual	unsigned long	PositDataToNode( char *pBytes);

		virtual	void	translate( Vector3 offset );
//		virtual	void	rotate(short axis, float angle)	;
		virtual	void	scale(Vector3 scale);

		virtual	bool	testIntersection( vgMath::Ray* ray );

		virtual	bool	testIntersection( const vgCore::ImageRect& rect ,
			int *viewport , GLdouble* proj_mat , GLdouble* model_mat );
		
		
		//	Part 4 :新增固定的对外接口，Mod读入
	public:
		void	ReadObjectFromMod(CFile&	oFile);

	
	public:
		//	Part 5 :重载父类的虚函数
		virtual BoundingBox		ComputeBoundBox();
		
		virtual void			RenderShadows();	
		virtual void			render_ForShadow();
		virtual void			update_ForShadowEveryTime();
		
		virtual void			RenderWithoutTex(float r, float g, float b);
	
		
		//	Part 6 :新增虚函数，通过重载个别函数，可以替换相应功能
	public:		
		//	接口Initialize的底层执行细节
		virtual void	configureCommonData();
		virtual void	configureExtraData()	{   return; }
		
		virtual void	sendVetexToVBOOnce();
		virtual void	clearUnvboDataExtra()	{	return;	}
		
		virtual void	renderToDisplaylistOnce();
		
		virtual void	initializeExtra()		{	return;	}
		
		
		//	接口Render的底层执行细节
		virtual	void	prepareMatrix()			{	return;	}
		virtual	void	prepareExtra()			{	return;	}

		virtual	void	resetMatrix()			{	return;	}
		virtual	void	resetExtra()			{	return;	}


		virtual void	assignColor(int i);
		virtual void	assignTexture(int i );
		virtual void	resetTexture()			{	return; }	
	

		//	接口Translate、Rotate、Scale的底层执行细节
		virtual	void	translateVetexArray( Vector3 offset );
		virtual	void	rotateVetexArray( short axis, float angle ,Vector3 centerVec  );
		virtual	void	scaleVetexArray( Vector3 scale  , Vector3 centerVec);


		//	接口ReadObjectFromMod的底层执行细节
		virtual	long	readMaterial(char	*pBytes);
		virtual	long	readVetex(char	*pBytes);
		virtual long readExtraData(char *pBytes);
		
		
		//	接口WriteNodeToVG、ReadNodeFromVG的底层执行细节
		virtual	void	writeMaterialToVG(CFile &fp);
		virtual	void	writeVertexToVG(CFile &fp);
		virtual	void	writePropertyExtraToVG(CFile &fp);
		virtual	void	writeExtraDataToVG(CFile &fp)		{	return; }

		virtual	void	readMaterialFromVG(CFile &fp);
		virtual	void	readVertexFromVG(CFile &fp);
		virtual	void	readPropertyExtraFromVG(CFile &fp);
		virtual	void	readStateExtraFromVG(CFile &fp)		{	return; }
		virtual	void	readExtraDataFromVG(CFile &fp)		{	return; }


		
		
		
		//	接口testIntersection的底层执行细节
		virtual	Vector3	getVertexElementPosition(int i);
		
			
		//	其它可重载的执行细节，顶点交错数组回写（显存与内存之间）
		virtual void	mapVertexBuffer();
		virtual void	unmapVertexBuffer();


		
		//	Part 7 :新增内部函数，功能比较稳定，一般无须重载
	protected:
		//	接口Initialize的中底层执行细节
		void	configureOnce();
		
		virtual void	sendRenderableDataToVBOOnce();

		void	sendFaceWithMaterialToVBOOnce();
		void	sendFaceNoMaterialToVBOOnce();

		void	sendRenderableDataToDisplaylistOnce();

		
		//	接口Render的中底层执行细节
		void	prepareForRender();
		void	resetAfterRender();
public:		
		void	renderInVBO();
		void	renderInDisplayList();
protected:
		void	renderFaceWithMaterial();
		void	renderFaceNoMaterial();
		
		void	renderFaceWithTexture(int i );
		virtual void	setOGLTestStates();
		virtual void	resetOGLTestStates();

		void	renderFaceWithColor(int i );
	
		void	clearUnvboData();
		
		bool	confirmVBO();

		//	接口ReadObjectFromMod的中底层执行细节
		long	readFromMemery(char *pBytes = NULL, int _length = 0);	

		long	readProperty(char	*pBytes);
		long	readPropertyExtra(char	*pBytes);
		long	readFace(char	*pBytes);
		long	readShadow(char	*pBytes);
		int		readRenderControl(char *pBytes , ObjectRenderControl &RenderControl );
		
		void	generateFace2( ObjectRenderControl &Rendercontrol);


		//	接口Translate、Rotate、Scale的底层执行细节
		void	translatePointArray( Vector3 offset );
		void	rotatePointArray( short axis, float angle ,Vector3 centerVec  );
		void	scalePointArray( Vector3 scale  , Vector3 centerVec);
		void	rotateNormalArray(  short axis, float angle );
		
		void	scalePoint( Vector3 scale , Vector3 centerVec, Vector3* pVert, int n=1);
		void	rotatePoint( short axis, float angle ,Vector3 centerVec , Vector3* pVert, int n=1);
		void	translatePoint( Vector3 offset , Vector3* pVert, int n=1);

		
		//	接口WriteNodeToVG、ReadNodeFromVG的底层执行细节
		void	writeObjectHead(CFile &fp);
		void	writePropertyToVG(CFile &fp);
		void	writeStateToVG(CFile &fp);
		void	writeFaceToVG(CFile &fp);
		void	writeShadowToVG(CFile &fp);

		void	readObjectHead(CFile &fp);
		void	readPropertyFromVG(CFile &fp);
		void	readStateFromVG(CFile &fp);
		void	readFaceFromVG(CFile &fp);
		void	readShadowFromVG(CFile &fp);

		long	readStateFromVG(char	*pBytes);

		void	writeOpacityFlag(CFile &fp);
		void	readOpacityFlag(CFile &fp);
		long	readOpacityFlag(char	*pBytes);

		//	其它稳定执行细节，面索引回写（显存与内存之间）
		void	renderWithoutTex();
		
		void	buildShadowVolume();	
		void	WriteDDS(CFile &fp , const string &filename);


		//	Part 8 :新增工具函数，功能比较稳定，一般无须重载
	public:
		float	calFaceArea( Vector3 a, Vector3 b, Vector3 c);
		//void	calLodLevel();
		virtual bool	cloneFromObjectNode(ObjectNode* src_node);
		
		void	mapFaceIndex();
		void	unmapFaceIndex();

		// 用二维多边形筛选模型中落入其中的点集，返回点集供修改
		Vec3PtrArray*	getSelectedVertexByFilter(vgKernel::PointInPolygon)
		{
			return	NULL;
		}
	
		//// 用于切块保存收集MOD特效贴图信息(water,glass,skybox,mirror,metal等)
		//virtual vgKernel::StringVector getTexNameVec() 
		//{ 
		//	vgKernel::StringVector texNameVec;
		//	return texNameVec;
		//}

	public:
		//	构造/析构
		ObjectNode(int nVersionMod = VERSION_1);
		virtual ~ObjectNode();
		
#if 1
	public:
		//	继承Renderer而来的接口
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

		virtual void translate(const float& x, const float& y, const float& z);

		virtual void rotateSelf(const float& angle, const float& x, const float& y, const float& z);

		virtual void scale(const float& cx, const float& cy, const float& cz, const float& x, const float& y, const float& z);

		virtual void rotate(const float& angle, const float& cx, const float& cy, const float& cz, 
			const float& x, const float& y, const float& z) ;

		virtual std::pair<bool, float> testIntersectWithTriangles( 
			const vgKernel::Ray& ray );
// 		{
// 			return pair<bool, float>(false, 0.0f);
// 		}

		virtual vgKernel::Box getBoundingBox()
		{
			vgMath::Vector3	maxVertex(GetBoundryBox().maxPoint);
			vgMath::Vector3 minVertex(GetBoundryBox().minPoint);
			vgKernel::Box	box;
			box.setMaximum(vgKernel::Vec3(maxVertex.x, maxVertex.y, maxVertex.z) );
			box.setMinimum(vgKernel::Vec3(minVertex.x, minVertex.y, minVertex.z) );
			return box;
		}

		virtual long getNumOfTriangles()
		{
			return m_numOfFaces;
		}

		/**
		注意,返回的是Distance的平方
		*/
		virtual float setDistanceToViewer( const vgKernel::Vec3& viewer_pos  );

		virtual void	render()
		{	
			// if ( GetVisable() )
			{
				Render();
			}
		}

		virtual void setVisible( bool visible )
		{ 
			vgKernel::Renderer::setVisible(visible);
			_visible = visible;
			SetVisable(visible);
		}

		virtual bool getVisible()
		{
			return GetVisable();
		}

		virtual	void	flip(bool x, bool y, bool z);

#endif		

		/**
			@action		add
			@date 		2009/03/11  11:02	
			@author  	lss
		
			@brief 	
		
			@see    
			*/
		public:

			virtual bool testIntersectWithTriangles( 
				const vgKernel::Segment3& segment );

			void	setRenderDoubleSidesState(bool bDouble)	{_bRenderDoubleSides = bDouble;}
			bool*	getRenderDoubleSidesStatePtr()	{	return &_bRenderDoubleSides;}	

			//static	ObjectNode*	ReadNodeFromVGByType(CFile &fp);

		public:

			//------------------------------------------
			// 继承ShadowCastObject来的接口 
			//------------------------------------------

			// 渲染shadow的caster
			virtual void renderInShadowMode();

			virtual void turnOffShadowCast();

			virtual void turnOnShadowCast( const vgKernel::Vec3& light_dir,
				bool force_to_load );

			// 光影的方向在第一次的时候进行设置
			// 包括光的方向变更的时候，也使用此函数进行通知。
			virtual void onLightDirectionChanged( const vgKernel::Vec3& light_dir );

			vgKernel::Mat4* _multiplyMatrix;

			//static Vector3* _shadowVector;

			// 触发器
	public:

		virtual	bool	testTriggered(const vgKernel::Vec3& eyePos);	//	触发条件
		virtual	void	respondAfterTriggered();	//	触发响应

		String&	getTriggerInfo();
		void	setTriggerInfo(const String& str);

		bool&	getTriggerFlag();
		void	setAsTrigger(const bool& bSet);
	protected:
		bool	_bSetAsTrigger;		//	是否触发器
		String	_strTriggerInfo;	//	触发信息
	
	public:
		inline virtual void collisionDetection(vgPhys::CollisionPacket& collistionPacket);
		
		virtual bool testPointInObject( const vgKernel::Vec3& pos );

		virtual bool cloneMtlFromObjectNode(ObjectNode* src_node);
		virtual bool cloneVertexFromObjectNode(ObjectNode* src_node);

	};//class ObjectNode


	typedef std::vector<ObjectNode>	ModItemVec;	
	typedef std::vector<ObjectNode>::iterator	ModItemVecItr;	
	typedef std::vector<ObjectNode*>	ModItemPtrVec;	
	typedef std::vector<ObjectNode*>::iterator	ModItemPtrVecItr;	


	VGK_RENDERER_OUT_DECLARE( ObjectNode )

}//namespace vgMod

#endif // end of __VGOBJNODE_H__

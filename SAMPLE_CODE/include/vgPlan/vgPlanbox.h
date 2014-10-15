
#ifndef __VGPLANBOX__
#define  __VGPLANBOX__

#include <vgKernel/vgkVec3.h>
#include <vgKernel/vgkSharePtr.h>
#include <vgKernel/vgkRenderer.h>
#include <vgplan/vgPlanBoxAB.h>
#include <vgplan/vgPlanbuilding.h>

#include <vgKernel/vgkShadowCastObject.h>
#include <vgKernel/vgkRenderer.h>

namespace vgPlan{

	typedef struct ShadowFaceIndex_t
	{
		//int	p1;
		//int p2;
		//int p3;
		int p1 , p2 , p3;  
		int	normal;

		int	p1p2AdjFaceIndex;
		int	p2p3AdjFaceIndex;
		int	p3p1AdjFaceIndex;

		bool faceVisible;

		bool p1p2Visible;
		bool p2p3Visible;
		bool p3p1Visible;	
	} ShadowFaceIndex;

	const vgKernel::RendererType RENDERER_TYPE_PLANBLOCK = 6000;

	class vgPlanbox : public vgPlanbuild, public vgKernel::ShadowCastObject, public vgKernel::Renderer
	{
		// friend class vgPlansimplestrategy;
		static PlanBoundboxAB calcuteABbox( float _length, float _width, float _angle );
	public:

		vgPlanbox();
		// pos 是地理坐标不是opengl坐标
		vgPlanbox( float _layernum, float _onelayerheight,
						float angle, float _length, float _width,
						vgKernel::Vec3 _pos = vgKernel::Vec3(0,0,0));

		virtual ~vgPlanbox();

		void vgPlanbox::setupBoxData(const vgKernel::Vec3& pos, float _length, float _width, float _height, float _angle);

		void vgPlanbox::setupBoxData( float length, float width, int layer, float heightPerLayer, float roateAngle);
		void render();

		// 编辑功能

		void setOrigiPositon(float x, float y)
		{
			m_oriX = x;
			m_oriY = y;
		}

		void setLayerNum(int num )
		{
			m_layerNum = num;
			m_height = m_layerNum * m_heightPerLayer;

			setupBoxData(/*m_pos,*/ m_length, m_width, m_layerNum, m_heightPerLayer, m_angle);
		}
		
		void setLength(float length)
		{
			m_length = length;

			setupBoxData(/*m_pos,*/ m_length, m_width, m_layerNum, m_heightPerLayer, m_angle);
		}

		void setWidth(float width)
		{
			m_width = width;

			setupBoxData(/*m_pos,*/ m_length, m_width, m_layerNum, m_heightPerLayer, m_angle);
		}

		void setHeightPerLayer(float heightPerHeight)
		{
			m_heightPerLayer = heightPerHeight;
			m_height = m_heightPerLayer * m_layerNum;

			setupBoxData(/*m_pos,*/ m_length, m_width, m_layerNum, m_heightPerLayer, m_angle);
		}

		float getAngle()
		{
			return m_angle;
		}

		void setAngle(float angle)
		{
			m_angle = angle;

			setupBoxData(/*m_pos,*/ m_length, m_width, m_layerNum, m_heightPerLayer, m_angle);
		}

		float getLength()
		{
			return m_length;
		}

		float getWidth()
		{
			return m_width;
		}

		float getHeightPerLayer()
		{
			return m_heightPerLayer;
		}

		int getLayerNum()
		{
			return m_layerNum;
		}

		OGRGeometry* getboxgeo();

		float getboxarea(){ return m_boxArea;  }

		void onsunlightanalysis();

		void drawshadow();

		void setupshadowdata();

		float getBuildArea(){ return m_boxArea; }
	
		float getBuildTotalArea()
		{
			return m_boxArea * m_layerNum;
		}

		void setSceneId(int sceneId)
		{
			m_sceneId = sceneId;
		}

		void attachToTerrain();

	public:
		void OnChangeToNormalMode();

		void OnChangeToEditMode();


		virtual vgKernel::RendererType  getType()
		{
			return RENDERER_TYPE_PLANBLOCK;
		}

		virtual string getTypeDesc()
		{
			string result;

			return result;
		}

		virtual string getClassName()
		{
			return "vgPlan.vgPlanBox";
		}

		virtual string getClassShortName()
		{
			return "vgPlanBox";
		}

		// 继承自renderer的函数
		virtual String getName() { return m_name; }

		virtual String* getNamePtr() { return &m_name; }

		virtual void setName( const String& newname ) { m_name = newname; }
		
		virtual vgKernel::UniqueID getUniqueID() { return m_uid; }

		virtual void moveTo( const vgKernel::Vec3& newpos );

		virtual void moveTo(const float& x, const float& y, const float& z);

		virtual void translate(const float& x, const float& y, const float& z);

		virtual vgKernel::Box getBoundingBox() { return m_dynamicBox; }

		virtual void rotate(const float& angle, const float& cx, const float& cy, const float& cz, const float& x, const float& y, const float& z);

		virtual void rotateSelf(const float& angle, const float& x, const float& y, const float& z);

		virtual void scale(const float& cx, const float& cy, const float& cz, const float& x, const float& y, const float& z) { return ;}

		virtual long getNumOfTriangles(/* = 0 */) { return 6; } 

		virtual float setDistanceToViewer( const vgKernel::Vec3& viewer_pos )
		{
			return 0;
		}

		virtual std::pair<bool, float> testIntersectWithTriangles( const vgKernel::Ray& ray );

		void calculategeo();

	protected:
		bool m_onEditMode;

		// renderer 相关的数据
		string m_name;
		vgKernel::UniqueID m_uid;
		
		float m_length;
		float m_width;
		float m_angle;
		float m_height;
		float m_heightPerLayer;
		int   m_layerNum;

		float m_oriX;
		float m_oriY;

		float m_onelayerheight;

		OGRGeometry* m_geometry;

		// 底面中心坐标
		vgKernel::Vec3 m_pos;

		vgKernel::Box m_dynamicBox;
		vgKernel::Box m_staticBox;

		vgKernel::Mat4 m_matrix;

	private:

		static void rotatevec(vgKernel::Vec2 &_result, vgKernel::Vec2 _vec, float angle );
	
	
		int sw_searchForAdjacent( int faceid ,  int& point1 , int& point2 );
	
		void computenormal();
	
		void buildShadowVolume();


	private:

		float m_boxArea;

		vgKernel::Vec3 m_floor[4];

		vgKernel::Vec3 m_ceil[4];

		// PlanBoundboxAB boundbox;

	private:
 
 		bool m_visiable;

		int m_sceneId;
		

	private:
		vgKernel::Vec3*				pNormalOfFaces;
		long						m_numOfVertexs;
		long						m_facenum;
		vgKernel::Vec3*				pVert;
		ShadowFaceIndex*			pShadowFaces;
		int							mShadowVolume;
		//////////////////////////////////////////////////////////////////////////

	public:
		vgPlanbuild *clone() ;

		void vgPlanbox::setupposition( vgKernel::Vec3 &pos , int laynum);



	public:

		// shadowcastobject接口

		// 渲染shadow的caster
		virtual void renderInShadowMode() 
		{
			drawshadow();
		}

		virtual void turnOffShadowCast()
		{
			__super::turnOffShadowCast();
		}

		virtual void turnOnShadowCast( const vgKernel::Vec3& light_dir,
			bool force_to_load );

		// 光影的方向在第一次的时候进行设置
		// 包括光的方向变更的时候，也使用此函数进行通知。
		virtual void onLightDirectionChanged( const vgKernel::Vec3& light_dir );

		vgKernel::Vec3 m_sunLightDir;

	};

	typedef vgKernel::SharePtr<vgPlanbox> PlanBoxSharedPtr;

}



#endif
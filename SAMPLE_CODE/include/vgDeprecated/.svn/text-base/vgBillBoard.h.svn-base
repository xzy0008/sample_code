

#ifndef __VGBILLBOARD_H__
#define __VGBILLBOARD_H__



//#include <vgStableHeaders.h>
#include <vgTex/tvgBillboard.h>

#include <vgMath/vgfBoundingBox.h>
#include <vgMod/vgNode.h>
#include <vgKernel/vgkRendererObserver.h>

#include <vgKernel/vgkRenderer.h>
namespace vgMod
{
	using namespace vgMod;
	using namespace vgMath;

	const vgKernel::RendererType RENDERER_TYPE_BILLBOARD = 5012;

	//const CategoryType NODE_TYPE_BB	= 2;


	class VGDEP_EXPORT BillboardNode : public Node , public vgKernel::Renderer
	{
		VGK_RENDERER_IN_DECLARE( BillboardNode )
	public:
		BillboardNode();
		virtual ~BillboardNode();



		virtual BoundingBox ComputeBoundBox();

	public:
		//void IniBillBoard();

		virtual void UpdatePos();

		Billboard mBillboard;

		float m_height;
		float m_width;

		string m_texturename;
		/*	Vector3 treepos;*/

	public:
		virtual void Render();

		float GetWidth(){ return m_width; }

		float GetHeight(){ return m_height; }
		void translate(Vector3 offset);
		void scale(Vector3 Scale);
		
		void WriteNodeToVG( CFile &fp );
		unsigned long PositDataToNode( char *pBytes );

		void	Initialize();				

		void	rotate(short axis, float Angle)	{	}

		bool	testIntersection( vgMath::Ray* ray )	{	return false;}// 用于精确单选(用box和ray相交判定)
		bool	testIntersection( const vgCore::ImageRect& rect ,
			int *viewport , GLdouble* proj_mat , GLdouble* model_mat )	{	return false;}
	
		string getTextureName() const
		{
			return m_texturename;
		}

	public:
		//	Part 0 :新增属性，相对class Node
		String _meshName;
		vgKernel::UniqueID _uniqueID;
		float	_squaredDistanceToViewer;

	
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

		virtual void translate(const float& x, const float& y, const float& z)
		{
			translate( Vector3(x,y,z) );
		}

		virtual void rotateSelf(const float& angle, const float& x, const float& y, const float& z)
		{};

		virtual void scale(const float& cx, const float& cy, const float& cz, const float& x, const float& y, const float& z)
		{
			return this->scale(Vector3(x,y,z));
		}

		virtual void rotate(const float& angle, const float& cx, const float& cy, const float& cz, 
			const float& x, const float& y, const float& z) 
		{};

		virtual std::pair<bool, float> testIntersectWithTriangles( 
			const vgKernel::Ray& ray );
		// 		{
		// 			return pair<bool, float>(false, 0.0f);
		// 		}

		virtual vgKernel::Box getBoundingBox()
		{
			ComputeBoundBox();
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

		virtual void	render(){	Render();}

	};

	VGK_RENDERER_OUT_DECLARE( BillboardNode )

}//namespace

#endif // end of __VGBILLBOARD_H__
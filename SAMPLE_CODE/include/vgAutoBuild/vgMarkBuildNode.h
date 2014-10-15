#pragma once

#include <vgMod/vgdepDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkRenderer.h>
#include <vgKernel/vgkFlickerObject.h>

#include <map>

using std::map;

namespace vgAutoBuild
{
	const vgKernel::RendererType RENDERER_TYPE_LANDMARKBUILD = 7002;

	class VGDEP_EXPORT MarkBuildNode : 
		public vgKernel::Renderer,
		public vgKernel::FlickerObject
		
	{
		VGK_RENDERER_IN_DECLARE( MarkBuildNode )

	public:
		MarkBuildNode(vgKernel::Vec3 polygon);

		MarkBuildNode()
		{

		}

		virtual ~MarkBuildNode()
		{

		}


	public:

		// 使用display list来创建
		void renderUsingDisplayList();

		// 渲染一次. 为了创建display list
		void renderOnceForDisplayList();  

		virtual void invalidateRendering();

		void renderWithoutDisplayList();

		void initialise();

	public:
		bool getMarkEnable(){ return m_markEnable; }

		void setMarkEnable(bool enable ){ m_markEnable = enable; }

		void fireClicked();

		vgKernel::Vec3 getSelectedPoint(){ return m_innerPoint; }

	protected:

		vgKernel::Vec3 m_innerPoint;

		GLuint _callListId;

		bool m_markEnable;
		
	public:
		//继承自Renderer接口

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

		virtual vgKernel::Box getBoundingBox()
		{
			computeBoundingBox();
			return _dynamicBox;
		}

		virtual long getNumOfTriangles()
		{
			return _numberOfTriangles;
		}

		virtual std::pair<bool, float> testIntersectWithTriangles( 
			const vgKernel::Ray& ray )
		{
			return vgKernel::Math::intersects( ray , getBoundingBox() );
		}

		virtual float setDistanceToViewer( const vgKernel::Vec3& viewer_pos  );

		virtual void render();

		virtual void computeBoundingBox();

	public:
		//读写接口
		void	writeToFile( CFile &fp );
		bool	readFromFile( CFile &fp );

	private:
		 String _meshName;

		 vgKernel::Box _dynamicBox;
		 vgKernel::Box _staticBox;

		 vgKernel::Mat4 _matrix;

		 long	_numberOfTriangles;

		 vgKernel::UniqueID _uniqueID;

		 float _squaredDistanceToViewer;


	};

	VGK_RENDERER_OUT_DECLARE( MarkBuildNode )

}

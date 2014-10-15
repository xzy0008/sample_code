


#ifndef __VGKRENDERER_H__
#define __VGKRENDERER_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkRendererObserver.h>
#include <vgKernel/vgkRay.h>
#include <vgKernel/vgkSegment3.h>
#include <vgKernel/vgkMath.h>
#include <vgKernel/vgkOcclusionInterface.h>
#include <vgKernel/vgkRendererDataInterface.h>
#include <vgKernel/vgkSelectionInterface.h>
#include <vgKernel/vgkUniqueID.h>
#include <vgKernel/vgkClassIdentify.h>


	
namespace vgKernel {


	 /**
	 	客户端负责类型.
		服务器端不需要知道具体的类型.
		所以在这里不参与定义.
	 */
	typedef int RendererType;

	const RendererType RENDERTYPE_UNKNOWN	= -1;


	/**
		@date 	2008/08/08  19:30	
		@author  xy
	
		@brief 	
	
		@see    
	*/
	class Renderer : 
		public ClassIdentify ,
		public ObserverContainer ,
		public OcclusionInterface ,
		public RendererDataInterface , 
		public SelectionInterface
	{
	public:
		Renderer()
		{
			_manualCulled = false;
			_visible = true; 
			_rendererType = RENDERTYPE_UNKNOWN;
			_renderingPriority = 0;
		}

		Renderer( RendererType type )
		{
			_manualCulled = false;
			_visible = true; 
			_rendererType = type;
			_renderingPriority = 0;
		}

		virtual ~Renderer()
		{
			notifyOberversOnDelete();
		}

	public:


	    virtual RendererType getType() = 0;
		virtual String getTypeDesc() = 0;

		virtual String getName() = 0;

		virtual String* getNamePtr() = 0;

		virtual void setName( const String& newname ) = 0;

		virtual bool getVisible(){ return _visible; }

		virtual UniqueID getUniqueID() = 0;

		virtual void moveTo( const vgKernel::Vec3& newpos )
		{
			moveTo( newpos.x , newpos.y , newpos.z );
		}

		virtual void moveTo(const float& x, const float& y, const float& z) 
		{
			vgKernel::Vec3 center = getBoundingBox().getCenter();
	
			if ( center.x != x || center.y != y || center.z != z)
			{
				translate(x-center.x, y-center.y, z-center.z);
			}
		}

		virtual void translate(const float& x, const float& y, const float& z) = 0;

		virtual void rotateSelf(const float& angle, 
			const float& x, const float& y, const float& z) = 0;

		virtual void scale(const float& cx, const float& cy, const float& cz, 
			const float& x, const float& y, const float& z) = 0;

		virtual void rotate(const float& angle, 
			const float& cx, const float& cy, const float& cz, 
			const float& x, const float& y, const float& z) = 0;


		virtual vgKernel::Box getBoundingBox() = 0;

		virtual long getNumOfTriangles() = 0;

		/**
			注意,返回的是Distance的平方
		*/
		virtual float setDistanceToViewer( const vgKernel::Vec3& viewer_pos  ) = 0;

		virtual void	render() = 0;

		virtual bool testPointInObject(const vgKernel::Vec3& point) { return false; }
		
		virtual bool testIntersectWithTriangles( 
			const vgKernel::Segment3& segment )
		{
			return false;
			//return vgKernel::Math::intersects( segment , getBoundingBox() );
		}

		virtual std::pair<bool, float> testIntersectWithTriangles( 
			const vgKernel::Ray& ray )
		{
			return vgKernel::Math::intersects( ray , getBoundingBox() );
		}

		virtual Vec3 getPosition()
		{
			return getBoundingBox().getCenter();
		}

		// 设置渲染优先级. 当为正数越大时, 越优先渲染. 可为负值.
		void setRenderingPriority( int prior_weight )
		{
			_renderingPriority = prior_weight;
		}

		int getRenderingPriority()
		{
			return _renderingPriority;
		}

		virtual void setVisible( bool visible ){ _visible = visible; }
		virtual void setSelected(bool bSelected){m_bSelected=bSelected;}
		bool GetSelected(){return m_bSelected;}

		virtual	void	flip(bool x, bool y, bool z){}
	protected:

		bool _visible;
		int _renderingPriority;

		bool _manualCulled;
		RendererType _rendererType;
		bool m_bSelected;
	};



	typedef std::deque<Renderer*> RendererQueue;
	typedef std::map< RendererType, RendererQueue > RendererPackage;


#define VGK_RENDERER_IN_DECLARE( classname ) \
		VGK_CLASS_IN_DECLARE( classname ) \
	private: \
		static vgKernel::RendererType _rendererType;\
	public: \
		virtual vgKernel::RendererType getType() { return _rendererType; }\
		virtual String getTypeDesc();


#define VGK_RENDERER_OUT_DECLARE( classname ) \
	VGK_CLASS_OUT_DECLARE( classname )


#define VGK_RENDERER_IMPLEMENT( classname , renderertype ) \
	\
	VGK_CLASS_IMPLEMENT( classname ) \
	\
	vgKernel::RendererType classname::_rendererType = renderertype;\
	\
	String classname::getTypeDesc()\
	{\
		return #renderertype;\
	}


}// end of namespace vgKernel
	


#endif // end of __VGKRENDERER_H__
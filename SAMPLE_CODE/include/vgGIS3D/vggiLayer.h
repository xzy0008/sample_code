#pragma once

#include <vgGis/vggisDefinition.h>
#include <vgKernel/vgkForward.h> 
#include <vgGis3d/vggiGeometry.h>

#include <vgKernel/vgkRenderer.h>
#include <vgKernel/vgkSharePtr.h>

class OGRLayer;
class OGRFeatureDefn;
	
namespace vgGIS3D {


	enum Layer_Type
	{
		Layer_Type_NONE,

		Layer_Type_SHP,
		Layer_Type_OCI,
		Layer_Type_DXF,

		Layer_Type_SIZE
	};

	class  VGG_EXPORT Layer : public vgKernel::Renderer
	{
		VGK_RENDERER_IN_DECLARE( Layer )
	public:
		Layer();

		virtual ~Layer()
		{
			destroy();
		}
	

	public:

		bool initialise( OGRLayer* ogrlayer );

		void setLayerType(Layer_Type t)
		{
			_type = t;
		}

		Layer_Type getLayerType()
		{
			return _type;
		}

		virtual String getName()
		{
			return _shapeName;
		}

		virtual String* getNamePtr()
		{
			return &_shapeName;
		}

		virtual void setName( const String& newname )
		{
			_shapeName = newname;
		}

		virtual vgKernel::UniqueID getUniqueID()
		{
			return _uniqueID;
		}

		virtual void translate(const float& x, const float& y, const float& z);

		virtual void rotateSelf(const float& angle, const float& x, const float& y, const float& z) 
		{
			//assert(0);
		}

		virtual void scale(const float& cx, const float& cy, const float& cz, 
			const float& x, const float& y, const float& z);

		virtual void rotate(const float& angle, 
			const float& cx, const float& cy, const float& cz, 
			const float& x, const float& y, const float& z)
		{
			//assert(0);
		}


		virtual vgKernel::Box getBoundingBox()
		{
			return _dynamicBox;
		}

		virtual long getNumOfTriangles()
		{
			return _numOfPoints;
		}


		virtual float setDistanceToViewer( const vgKernel::Vec3& viewer_pos  )
		{
			return 0.0f;
		}

		virtual void render();

		virtual OGRLayer* getOGRLayer()
		{
			return _ogrLayer;
		}

		//virtual bool getVisible(){ return m_visible; }

		//virtual void setVisible( bool visible ){ m_visible = visible; }


	public:

		void destroy();

		void pushGeometry( Geometry* geo );

		// 注意, 客户端负责删除.
		OGRFeature* getOGRFeatureByFID( const long& fid );

		void setOGRFeature( OGRFeature* feature );

		// 计算ray和哪个Geometry相交
		// 返回的是相交的geometry
		Geometry* testIntersectWithGeometry( 
			const RayLine3d& rayline );

		void setSelectedGeometry( Geometry* selected_geo );
		// 内部保证了插入的唯一性
		void addSelectedGeometry( Geometry* add_geo );
		void delSelectedGeometry( Geometry* del_geo );
		void clearSelectedGeometry();

		GeometryPointerVec* getSelectedGeometry()
		{
			return &_selectedGeometries;
		}

		GeometryPointerVec* getGeometries()
		{
			return & _geometries;
		}
		
		GeometryPointerVec& getGeometriesRef()
		{
			return _geometries;
		}

		/**
			将内部的static坐标转移到现今的opengl坐标
		*/
		vgKernel::Vec3 transStaticCoordToOpenGLCoord( 
			const vgKernel::Vec3& static_vec );

		float getHeightInOpenGL( const vgKernel::Vec3& static_vec );


		// 重新渲染display list
		void invalidateRendering();


		bool attachGeometriesToTerrain();

		vgKernel::Mat4 getMatrix() const 
		{
			return _matrix;
		}

		void setMatrix( const vgKernel::Mat4& matrix );

		void setEditMode( bool edit_mode )
		{
			if ( (_inEditMode == true && edit_mode == false ) ||
				( _inEditMode == false && edit_mode == true ) )
			{
				_inEditMode = edit_mode;
				invalidateRendering();
			}

			return;
		}

		bool isInEditMode() const
		{
			return _inEditMode;
		}

		bool getVisible() { return m_enableDepth; }
		void setVisible(bool d) { m_enableDepth = d; }
		bool getDepthEnable() { return m_enableDepth; }
		void setDepthEnable(bool d) { m_enableDepth = d; }
		bool selectByFieldString( const String& fieldname , const String& content );

		OGRFeatureDefn* getFeatureDefn();

	private:

		struct TravGeoForRender
		{
			inline void operator() ( Geometry* geo) 
			{
				geo->renderUsingDisplayList();
			}
		};

		struct TravGeoForCreateDisplayList
		{
			inline void operator() ( Geometry* geo) 
			{
				geo->renderOnceForDisplayList();
			}
		};


	public:
			bool m_visible;

	private:

		Layer_Type _type;

		bool _inEditMode;
	
		GLuint _displayListID;

		String _shapeName;

		vgKernel::UniqueID	_uniqueID;

		vgKernel::Box _dynamicBox;
		vgKernel::Box _staticBox;

		vgKernel::Mat4 _matrix;

		int _numOfPoints;

		GeometryPointerVec _geometries;

		OGRLayer* _ogrLayer;

		GeometryPointerVec _selectedGeometries;

		float _transX;
		float _transY;
		float _transZ;

		static TravGeoForRender _traverseGeoRender;
		static TravGeoForCreateDisplayList _traversForCreateDisplayList;
		
		bool m_enableDepth;
	};

	VGK_RENDERER_OUT_DECLARE( Layer )
	

	typedef vgKernel::SharePtr<Layer> LayerPtr;
	typedef std::vector<LayerPtr> LayerPtrVector;

	
}// end of namespace vgShape
	 
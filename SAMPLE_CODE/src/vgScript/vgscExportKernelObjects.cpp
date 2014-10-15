



#include <vgStableHeaders.h>
#include <vgScript/vgscExportKernelObjects.h>
#include <vgKernel/vgkRenderer.h>
#include <vgKernel/vgkSelectManager.h>
#include <vgKernel/vgkRendererManager.h>
#include <vgKernel/vgkRendererHolder.h>
#include <vgKernel/vgkStreamWriter.h>
#include <vgKernel/vgkStreamReader.h>
#include <vgKernel/vgkPolygon2D.h>

#include <vgScript/vgscBoostPythonInclude.h>
#include <vgScript/vgscSharePtrWrapper.h>
#include <vgKernel/vgkTransparentObject.h>
#include <vgKernel/vgkColorableObject.h>
#include <vgKernel/vgkCoordSystem.h>
#include <vgKernel/vgkDissolveObject.h>
#include <vgKernel/vgkFlickerObject.h>

struct void_;
BOOST_PYTHON_OPAQUE_SPECIALIZED_TYPE_ID(void_);


namespace vgKernel {
	
	

	using namespace boost::python;

	void ObserverContainer_onEvent( ObserverContainer& c , int eventId, void_ *param)
	{
		c.notifyOberversOnEvent( eventId , (void*)param );
	}

	TransparentObject* castRendererToTransparentObject( 
		Renderer* renderer )
	{
		TransparentObject* ret = NULL;
		ret = dynamic_cast<TransparentObject*>( renderer );

		return ret;
	}

	ColorableObject* castRendererToColorableObject( 
		Renderer* renderer )
	{
		ColorableObject* ret = NULL;
		ret = dynamic_cast<ColorableObject*>( renderer );

		return ret;
	}

	DissolveObject* castRendererToDissolveObject( 
		Renderer* renderer )
	{
		DissolveObject* ret = NULL;
		ret = dynamic_cast<DissolveObject*>( renderer );

		return ret;
	}

	FlickerObject* castRendererToFlickerObject(
		Renderer* renderer)
	{
		FlickerObject* ret = NULL;
		ret = dynamic_cast<FlickerObject*>( renderer);

		return ret;
	}

	class ColorableObjectWrapper: 
		public ColorableObject , public wrapper<ColorableObject>
	{
	public:
		ColorableObjectWrapper()
			: ColorableObject(),
			wrapper<ColorableObject>()
		{}
		virtual ~ColorableObjectWrapper()
		{

		}

		//virtual bool isTransparent()
		//{
		//	return this->get_override("isTransparent")();
		//}

		//virtual void setTransparent( bool set_to_transp = true )
		//{
		//	this->get_override("setTransparent") ( set_to_transp );
		//}
	};


	class TransparentObjectWrapper: 
		public TransparentObject , public wrapper<TransparentObject>
	{
	public:
		TransparentObjectWrapper()
			: TransparentObject(),
			wrapper<TransparentObject>()
		{}
		virtual ~TransparentObjectWrapper()
		{

		}

		virtual bool isTransparent()
		{
			return this->get_override("isTransparent")();
		}

		virtual void setTransparent( bool set_to_transp = true )
		{
			this->get_override("setTransparent") ( set_to_transp );
		}
	};

	class DissolveObjectWrapper: 
		public DissolveObject , public wrapper<DissolveObject>
	{
	public:
		DissolveObjectWrapper()
			: DissolveObject(),
			wrapper<DissolveObject>()
		{}
		virtual ~DissolveObjectWrapper()
		{

		}

		virtual bool isDissolveable()
		{
			if (override m = this->get_override("isDissolveable"))
				return isDissolveable();
			return DissolveObject::isDissolveable();
		}

		virtual void setDissolveState(const bool& dissolveable, const int& dissolvetype, const float& time)
		{
			if (override m = this->get_override("setDissolveState"))
			{
				setDissolveState(dissolveable,dissolvetype,time);
				return ;
			}

			DissolveObject::setDissolveState(dissolveable,dissolvetype,time);
		}

	};

	class FlickerObjectWrapper:
		public FlickerObject, public wrapper<FlickerObject>
	{
	public:
		FlickerObjectWrapper()
			:FlickerObject(),
			wrapper<FlickerObject>()
		{

		}
		virtual ~FlickerObjectWrapper()
		{

		}

		virtual bool isFlickered()
		{
			if (override m = this->get_override("isFlickered"))
				return isFlickered();
			return FlickerObject::isFlickered();
		}

		virtual void setFlickerState(const bool& flickerstate, const int& flickertype, const float & time)
		{
			if (override m = this->get_override("setFlickerState"))
			{
				setFlickerState(flickerstate,flickertype,time);
				return ;
			}

			FlickerObject::setFlickerState(flickerstate,flickertype,time);
		}
	};

	class StreamReaderWrapper: 
		public StreamReader , public wrapper<StreamReader>
	{
	public:
		StreamReaderWrapper()
			: StreamReader(),
			wrapper<StreamReader>()
		{}

		virtual ~StreamReaderWrapper()
		{}

		virtual String getDescription()
		{
			return this->get_override("getDescription")();
		}

		virtual String getFileName()
		{
			return this->get_override("getFileName")();
		}

		virtual bool create( const String& filename )
		{
			return this->get_override("create")( filename );
		}

		virtual bool isValid() 
		{
			return this->get_override("isValid")(  );
		}

		virtual size_t size(void)
		{
			return this->get_override("size")(  );
		}

		virtual size_t read( void* buf, size_t count )
		{
			return this->get_override("read")( buf , count );
		}

		virtual void skip(long count)
		{
			this->get_override("skip")( count );
		}

		virtual void seek( size_t pos )
		{
			this->get_override("seek")( pos );
		}

		virtual size_t tell(void) 
		{
			return this->get_override("tell")( );
		}

		virtual bool eof(void)
		{
			return this->get_override("eof")( );
		}

		virtual void close(void)
		{
			this->get_override("close")( );
		}

		virtual void flush(void)
		{
			this->get_override("flush")( );
		}

	};



	class RendererObserverWrapper : 
		public RendererObserver, public wrapper<RendererObserver>
	{
	public:
		RendererObserverWrapper()
			: RendererObserver(),
			wrapper<RendererObserver>()
		{

		}
		virtual ~RendererObserverWrapper()
		{

		}
		virtual void onChanged(int eventId, void *param)
		{
			this->get_override("onChanged")( eventId, param );
		}

		void RendererObserver_onChanged( int eventId, void_* p ) 
		{
			this->onChanged( eventId , (void*) p); 
		}

		virtual bool onDelete() 
		{
			return this->get_override("onDelete")(  );
		}

	};



	class RendererHolderWrapper : 
		public RendererHolder, public wrapper<RendererHolder>
	{
	public:
		RendererHolderWrapper()
			: RendererHolder(),
			wrapper<RendererHolder>()
		{
			
		}
		virtual ~RendererHolderWrapper()
		{
			
		}
	
		virtual bool onDeleteRenderer( Renderer* renderer )
		{
			return this->get_override("onDeleteRenderer")( renderer );
		}
	};

	class RendererWrapper : public Renderer, public wrapper<Renderer>
	{
	public:
		RendererWrapper()
			: Renderer(),
			wrapper<Renderer>()
		{

		}
		virtual ~RendererWrapper()
		{

		}
	public:

		//----------------------------------------------------------------
		RendererType getType() 
		{
			return this->get_override("getType")();
		}


		String getTypeDesc()
		{
			return this->get_override("getTypeDesc")();
		}


		String getClassShortName()
		{
			return this->get_override("getClassShortName")();
		}

		String getClassName()
		{
			return this->get_override("getClassName")();
		}

		String getName()
		{
			return this->get_override("getName")();
		}

		virtual String* getNamePtr()
		{
			return this->get_override("getNamePtr")();
		}

		virtual void setName( const String& newname ) 
		{
			this->get_override("setName")( newname );
		}

		virtual UniqueID getUniqueID()
		{
			return this->get_override("getUniqueID")();
		}

		virtual void translate(const float& x, const float& y, const float& z) 
		{
			this->get_override("translate")( x, y ,z );
		}

		virtual void rotateSelf(const float& angle, const float& x, const float& y, const float& z) 
		{
			this->get_override("rotateSelf")( angle , x , y ,z);
		}

		virtual void scale(const float& cx, const float& cy, const float& cz, 
			const float& x, const float& y, const float& z) 
		{
			this->get_override("scale")( cx , cy, cz , x ,y ,z );
		}

		virtual void rotate(const float& angle, const float& cx, const float& cy, const float& cz, 
			const float& x, const float& y, const float& z) 
		{
			this->get_override("rotate")( angle , cx ,cy ,cz , x , y, z);
		}

		virtual vgKernel::Box getBoundingBox() 
		{
			return this->get_override("getBoundingBox")();
		}

		virtual long getNumOfTriangles() 
		{
			return this->get_override("getNumOfTriangles")();
		}


		virtual float setDistanceToViewer( const vgKernel::Vec3& viewer_pos  )
		{
			return this->get_override("setDistanceToViewer")( viewer_pos );
		}

		virtual void render()
		{
			this->get_override("render")();
		}


		//----------------------------------------------------------------
		void moveTo1(const float& x, const float& y, const float& z) 
		{
			if (override m = this->get_override("moveTo"))
				return moveTo( x , y , z );
			return Renderer::moveTo( x , y , z );
		}

		void default_moveTo1( const float& x, const float& y, const float& z )
		{ 
			return this->Renderer::moveTo( x , y , z ); 
		}

		void moveTo2(const vgKernel::Vec3& newpos) 
		{
			if (override m = this->get_override("moveTo"))
				return moveTo( newpos);
			return Renderer::moveTo( newpos );
		}

		void default_moveTo2(const vgKernel::Vec3& newpos )
		{ 
			return this->Renderer::moveTo( newpos ); 
		}

		//----------------------------------------------------------------
		void setVisible( bool visible )
		{
			if (override m = this->get_override("setVisible"))
				return setVisible( visible );
			return Renderer::setVisible( visible );
		}

		void default_setVisible( bool visible )
		{ 
			return this->Renderer::setVisible( visible ); 
		}
		//----------------------------------------------------------------
		bool getVisible()
		{
			if (override m = this->get_override("getVisible"))
				return getVisible( );
			return Renderer::getVisible(  );
		}

		bool default_getVisible()
		{ 
			return this->Renderer::getVisible(); 
		}
		//----------------------------------------------------------------
		bool isSelectable()
		{
			if (override m = this->get_override("isSelectable"))
				return isSelectable( );
			return Renderer::isSelectable(  );
		}

		bool default_isSelectable()
		{ 
			return this->Renderer::isSelectable(); 
		}
		void setSelectable(bool canbeselect )
		{
			if (override m = this->get_override("setSelectable"))
				return setSelectable( canbeselect);
			return Renderer::setSelectable(  canbeselect);
		}

		void default_setSelectable(bool canbeselect )
		{ 
			return this->Renderer::setSelectable(canbeselect); 
		}
		//----------------------------------------------------------------
		bool testIntersectWithTriangles( 
			const vgKernel::Segment3& segment )
		{
			if (override m = this->get_override("testIntersectWithTriangles"))
				return testIntersectWithTriangles( segment );
			return Renderer::testIntersectWithTriangles(segment);
		}

		bool default_testIntersectWithTrianglesA( 
			const vgKernel::Segment3& segment )
		{
			return this->Renderer::testIntersectWithTriangles( segment );
		}
		//----------------------------------------------------------------
		std::pair<bool, float> testIntersectWithTriangles( 
			const vgKernel::Ray& ray )
		{
			if (override m = this->get_override("testIntersectWithTriangles"))
				return testIntersectWithTriangles( ray );
			return Renderer::testIntersectWithTriangles(ray);
		}

		std::pair<bool, float> default_testIntersectWithTrianglesB( 
			const vgKernel::Ray& ray )
		{
			return this->Renderer::testIntersectWithTriangles( ray );
		}
	};


	std::pair<bool, float> (vgKernel::Renderer::*testIntersectWithTrianglesB)( 
		const vgKernel::Ray& )= &vgKernel::Renderer::testIntersectWithTriangles;

	bool  (vgKernel::Renderer::*testIntersectWithTrianglesA)( 
		const vgKernel::Segment3& )= &vgKernel::Renderer::testIntersectWithTriangles;


	void  (vgKernel::Renderer::*moveTo1)( 
		const float& , const float& , const float&  )= &vgKernel::Renderer::moveTo;

	void  (vgKernel::Renderer::*moveTo2)( 
		const vgKernel::Vec3&  )= &vgKernel::Renderer::moveTo;

}

namespace vgScript {
	

	
	//----------------------------------------------------------------
	void exportKernelObjects()
	{
		using namespace boost::python;
		using namespace vgKernel;

		class_< Vec2Vector > ("Vec2Vector")
			.def (indexing::container_suite< Vec2Vector >() )
			;

		class_< Polygon2D > ("Polygon2D")
			//.def( init<Vec2Vector*>() )
			//.def ( "setPoints" , &Polygon2D::setPoints )
			.def ( "contains" , &Polygon2D::contains )
			//.def ( "getPoints" , &Polygon2D::getPoints )
			;

		def( "castRendererToTransparentObject" , 
			&castRendererToTransparentObject ,
			return_value_policy<reference_existing_object>() );

		def( "castRendererToColorableObject" , 
			&castRendererToColorableObject ,
			return_value_policy<reference_existing_object>() );

		def( "castRendererToDissolveObject" ,
			&castRendererToDissolveObject ,
			return_value_policy<reference_existing_object>() );

		def( "castRendererToFlickerObject" ,
			&castRendererToFlickerObject ,
			return_value_policy<reference_existing_object>() );

		class_<TransparentObjectWrapper,
			boost::noncopyable >("TransparentObject")
			.def("isTransparent", pure_virtual(&TransparentObject::isTransparent) )
			.def("setTransparent", pure_virtual(&TransparentObject::setTransparent) )
			;

		class_<ColorableObjectWrapper,
			boost::noncopyable >("ColorableObject")
			.def("isColorable", &ColorableObject::isColorable )
			.def("setColorable", &ColorableObject::setColorable )
			.def("setColorableValue", &ColorableObject::setColorableValue )
			.def("getColorVal", &ColorableObject::getColorVal )
			.def("getRgbaQuadRef", &ColorableObject::getRgbaQuadRef ,
			return_value_policy<reference_existing_object>())

			//.def("setTransparent", pure_virtual(&TransparentObject::setTransparent) )
			;

		class_<DissolveObjectWrapper,
			boost::noncopyable >("DissolveObject")
			.def("isDissolveable", &DissolveObject::isDissolveable, &DissolveObjectWrapper::isDissolveable)
			.def("setDissolveState", &DissolveObject::setDissolveState, &DissolveObjectWrapper::setDissolveState)
			;

		class_<FlickerObjectWrapper,
			boost::noncopyable >("FlickerObject")
			.def("isFlickered", &FlickerObject::isFlickered, &FlickerObjectWrapper::isFlickered)
			.def("setFlickerState", &FlickerObject::setFlickerState, &FlickerObjectWrapper::setFlickerState)
			.def("setForeColor", &FlickerObject::setForeColor)
			.def("setBackColor", &FlickerObject::setBackColor)
			;

		class_<StreamReaderWrapper, 
			vgKernel::SharePtr<StreamReaderWrapper> ,
			boost::noncopyable >("StreamReader")
			.def("getDescription", pure_virtual(&StreamReader::getDescription) )
			.def("getFileName", pure_virtual(&StreamReader::getFileName) )
			.def("create", pure_virtual(&StreamReader::create) )
			.def("isValid", pure_virtual(&StreamReader::isValid) )
			.def("size", pure_virtual(&StreamReader::size) )
			.def("read", pure_virtual(&StreamReader::read) )
			.def("skip", pure_virtual(&StreamReader::skip) )

			.def("seek", pure_virtual(&StreamReader::seek) )
			.def("tell", pure_virtual(&StreamReader::tell) )
			.def("eof", pure_virtual(&StreamReader::eof) )
			.def("close", pure_virtual(&StreamReader::close) )
			.def("flush", pure_virtual(&StreamReader::flush) )
			;

		implicitly_convertible< vgKernel::SharePtr<StreamReaderWrapper>, vgKernel::SharePtr<StreamReader> >();
		register_ptr_to_python< vgKernel::SharePtr<StreamReader> >();

		class_<FileStreamReader, 
			vgKernel::SharePtr<FileStreamReader> , bases<StreamReader>,
			boost::noncopyable >("FileStreamReader")
			;

		implicitly_convertible< vgKernel::SharePtr<FileStreamReader>, vgKernel::SharePtr<StreamReader> >();


		class_<StreamReaderFactory >("StreamReaderFactory" ,no_init)
			.def("createFromFile", &StreamReaderFactory::createFromFile )
			.staticmethod("createFromFile")
			;


		class_<ObserverContainer>("ObserverContainer")
			.def("notifyOberversOnDelete", &ObserverContainer::notifyOberversOnDelete )
			.def("registerObserver", &ObserverContainer::registerObserver )
			.def("notifyOberversOnEvent", &ObserverContainer_onEvent )
			.def("unregisterObserver", &ObserverContainer::unregisterObserver )
			;


		class_<RendererObserverWrapper,boost::noncopyable >("RendererObserver")
			.def("onDelete", pure_virtual(&RendererObserver::onDelete) )
			.def("onChanged", pure_virtual(&RendererObserverWrapper::RendererObserver_onChanged) )
			;

		class_<RendererHolderWrapper,boost::noncopyable >("RendererHolder")
			.def("onDeleteRenderer", pure_virtual(&RendererHolder::onDeleteRenderer) )
		;


		class_<RendererWrapper,boost::noncopyable ,
		bases<ObserverContainer> >("Renderer")
			.def("getTypeDesc", pure_virtual(&Renderer::getTypeDesc) )
			.def("getClassShortName", pure_virtual(&Renderer::getClassShortName) )
			.def("getName", pure_virtual(&Renderer::getName) )
			.def("getClassName", pure_virtual(&Renderer::getClassName) )

			.def("getType", pure_virtual(&Renderer::getType) )

			.def("setName", pure_virtual(&Renderer::setName) )
			.def("getUniqueID", pure_virtual(&Renderer::getUniqueID) )
			.def("translate", pure_virtual(&Renderer::translate) )
			.def("rotateSelf", pure_virtual(&Renderer::rotateSelf) )
			.def("scale", pure_virtual(&Renderer::scale) )
			.def("rotate", pure_virtual(&Renderer::rotate) )
			.def("getBoundingBox", pure_virtual(&Renderer::getBoundingBox) )
			.def("getNumOfTriangles", pure_virtual(&Renderer::getNumOfTriangles) )
			.def("setDistanceToViewer", pure_virtual(&Renderer::setDistanceToViewer) )
			.def("render", pure_virtual(&Renderer::render) )

			.def("moveTo", moveTo1, &RendererWrapper::default_moveTo1 )
			.def("moveTo", moveTo2, &RendererWrapper::default_moveTo2 )
			
			.def("setVisible", &Renderer::setVisible, &RendererWrapper::default_setVisible )
			.def("getVisible", &Renderer::getVisible, &RendererWrapper::default_getVisible )

			.def("testIntersectWithTriangles", testIntersectWithTrianglesA, &RendererWrapper::default_testIntersectWithTrianglesA )
			.def("testIntersectWithTriangles", testIntersectWithTrianglesB, &RendererWrapper::default_testIntersectWithTrianglesB )

			.def("setRenderingPriority", &Renderer::setRenderingPriority )
			.def("getRenderingPriority", &Renderer::getRenderingPriority )

			.def("isSelectable", &Renderer::isSelectable, &RendererWrapper::default_isSelectable )
			.def("setSelectable", &Renderer::setSelectable, &RendererWrapper::default_setSelectable )
			;

		//class_< RendererQueue >("RendererQueue")
		//	.def(indexing::container_suite< RendererQueue , true >())
		//	;

		class_< RendererQueue > ("RendererQueue")
			.def (indexing::container_suite< RendererQueue >
			::with_policies (return_value_policy<reference_existing_object>()) )
			;


		//class_< RendererPackage >("RendererPackage")
		//	.def(map_indexing_suite< RendererPackage >() )
		//	;


		//class_< std::vector<int> > ("vector_int")
		//	.def (indexing::container_suite< std::vector<int> >());

		class_< RendererPackage > ("RendererPackage")
			.def (indexing::container_suite< RendererPackage >() );




		class_<SelectManager >( "SelectManager" , no_init )
			.def( "addSelection", &SelectManager::addSelection )
			.def( "clearSelection", &SelectManager::clearSelection )
			.def( "renderSelected", &SelectManager::renderSelected )

			.def( "getEnableRenderSelected", &SelectManager::getEnableRenderSelected )
			.def( "setEnableRenderSelected", &SelectManager::setEnableRenderSelected )

			.def( "mergeBox", &SelectManager::mergeBox )

			.def( "updateSelectedItem", &SelectManager::updateSelectedItem )
			.def( "updateBox", &SelectManager::updateBox )
			.def( "getSelectedItems", &SelectManager::getSelectedItems ,
			return_value_policy<reference_existing_object>() )
			.def( "getSelectedBox", &SelectManager::getSelectedBox )

			.def( "getSelectedCenter", &SelectManager::getSelectedCenter )

			.def( "translateGroup", &SelectManager::translateGroup )
			.def( "deleteSelectedRenderers", &SelectManager::deleteSelectedRenderers )

			.def( "updateUI", &SelectManager::updateUI )


			.def( "getSingleton", &SelectManager::getSingleton ,
			return_value_policy<reference_existing_object>() )
			.staticmethod( "getSingleton" )
			;

		class_<RendererManager >( "RendererManager" , no_init )
			.def( "clear", &RendererManager::clear )
			.def( "invalidate", &RendererManager::invalidate )
			.def( "renderBegin", &RendererManager::renderBegin )
			.def( "renderEnd", &RendererManager::renderEnd )

			.def( "addRenderer", &RendererManager::addRenderer ,
			return_value_policy<reference_existing_object>() )

			.def( "deleteRenderer", &RendererManager::deleteRenderer )
			.def( "deleteAllRenderers", &RendererManager::deleteAllRenderers )

			.def( "getRendererQueueByType", &RendererManager::getRendererQueueByType,
			return_value_policy<reference_existing_object>()  )

			.def( "getAllRendererPackage", &RendererManager::getAllRendererPackage,
			return_value_policy<reference_existing_object>() )

			.def( "getCulledRendererPackage", &RendererManager::getCulledRendererPackage,
			return_value_policy<reference_existing_object>() )

			.def( "getCulledRenderQueueByType", &RendererManager::getCulledRenderQueueByType,
			return_value_policy<reference_existing_object>() )

			.def( "getRendererbyName", &RendererManager::getRendererbyName,
			return_value_policy<reference_existing_object>() )

			.def( "translateAllRenderers", &RendererManager::translateAllRenderers )

			.def( "getSingleton", &RendererManager::getSingleton ,
			return_value_policy<reference_existing_object>() )
			.staticmethod( "getSingleton" )
			;




		class_<CoordSystem >( "CoordSystem" , no_init )
			.def( "reset", &CoordSystem::reset )
			.def( "getProjectionCoord", &CoordSystem::getProjectionCoord )
			.def( "setProjectionCoord", &CoordSystem::setProjectionCoord )

			.def( "transCoordOpenGLToProj", &CoordSystem::transCoordOpenGLToProj )
			.def( "transCoordProjToOpenGL", &CoordSystem::transCoordProjToOpenGL )

			.def( "getSingleton", &CoordSystem::getSingleton ,
			return_value_policy<reference_existing_object>() )
			.staticmethod( "getSingleton" )
			;



	}
	//----------------------------------------------------------------


}// end of namespace vgScript

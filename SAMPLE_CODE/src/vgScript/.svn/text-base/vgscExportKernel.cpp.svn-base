


#include <vgStableHeaders.h>
#include <vgScript/vgscExportKernel.h>
#include <vgScript/vgscDefinition.h>
#include <vgKernel/vgkStringUtility.h>
#include <vgKernel/vgkVec2.h>
#include <vgKernel/vgkMath.h>
#include <vgKernel/vgkSegment3.h>
#include <vgkernel/vgkPlane.h>
#include <vgKernel/vgkRay.h>
#include <vgKernel/vgkQuat.h>
#include <vgScript/vgscSharePtrWrapper.h>
#include <vgKernel/vgkRgbaQuad.h>
#include <vgScript/vgscBoostPythonInclude.h>
#include <vgKernel/vgkStandardOutput.h>


namespace vgScript {
	


	//----------------------------------------------------------------

	using namespace vgKernel;
	VGSC_STATIC_FUNC_DECLARE( Vec3 , ZERO )
	VGSC_STATIC_FUNC_DECLARE( Vec3 , UNIT_X )
	VGSC_STATIC_FUNC_DECLARE( Vec3 , UNIT_Y )
	VGSC_STATIC_FUNC_DECLARE( Vec3 , UNIT_Z )
	VGSC_STATIC_FUNC_DECLARE( Vec3 , NEGATIVE_UNIT_X )
	VGSC_STATIC_FUNC_DECLARE( Vec3 , NEGATIVE_UNIT_Y )
	VGSC_STATIC_FUNC_DECLARE( Vec3 , NEGATIVE_UNIT_Z )
	VGSC_STATIC_FUNC_DECLARE( Vec3 , UNIT_SCALE )

	VGSC_STATIC_FUNC_DECLARE( Vec2 , ZERO )
	VGSC_STATIC_FUNC_DECLARE( Vec2 , UNIT_X )
	VGSC_STATIC_FUNC_DECLARE( Vec2 , UNIT_Y )
	VGSC_STATIC_FUNC_DECLARE( Vec2 , NEGATIVE_UNIT_X )
	VGSC_STATIC_FUNC_DECLARE( Vec2 , NEGATIVE_UNIT_Y )
	VGSC_STATIC_FUNC_DECLARE( Vec2 , UNIT_SCALE )

	VGSC_STATIC_FUNC_DECLARE( Mat4 , ZERO )
	VGSC_STATIC_FUNC_DECLARE( Mat4 , IDENTITY )

	void    (Box::*merge1)(const Vec3&)    = &Box::merge;
	void    (Box::*merge2)(const Box&)    = &Box::merge;

	std::pair<bool, float> (*intersects1)(const vgKernel::Ray& ,
		const Box& )  = &vgKernel::Math::intersects;

	std::pair<bool, float> (*intersects2)(const vgKernel::Ray& , 
		Vec3& , Vec3& , Vec3& )= &vgKernel::Math::intersects;

	std::pair<bool, float> (*intersects3)(const vgKernel::Ray& , 
		const Vec3& ,
		const Vec3& , const Vec3& , const Vec3& ,
		bool , bool )= &vgKernel::Math::intersects;



	vgKernel::Plane::Side (vgKernel::Plane::*getSide1)( const Vec3& ) const= &vgKernel::Plane::getSide;
	vgKernel::Plane::Side (vgKernel::Plane::*getSide2)( const Box& ) const = &vgKernel::Plane::getSide;
	vgKernel::Plane::Side (vgKernel::Plane::*getSide3)( const Vec3&, const Vec3&  ) const= &vgKernel::Plane::getSide;

	void (vgKernel::Plane::*redefine1)( const Vec3& , const Vec3& ) = &vgKernel::Plane::redefine;
	void (vgKernel::Plane::*redefine2)( const Vec3& , const Vec3& ,
		const Vec3& ) = &vgKernel::Plane::redefine;


	String getDetailsOfStringVector( const StringVector& strvec )
	{
		std::ostringstream o;
		for ( int i = 0 ; i < strvec.size() ; ++ i )
		{
			o << "[ " << i << " ] : " << strvec[i] << "\n";
		}

		return o.str();
	}

	//----------------------------------------------------------------

	//----------------------------------------------------------------
	void exportKernel()
	{
		using namespace boost::python;
		using namespace vgKernel;


		def( "dumpToOutput",StandardOutput::dumpToOutput );
		def( "dumpToOutputW",StandardOutput::dumpToOutputW );
		def( "restoreToDefaultOutput",StandardOutput::restoreToDefaultOutput );

		// SystemUtility
		def( "getCurrentProcessName",SystemUtility::getCurrentProcessName );
		def( "getCurrentProcessPath",SystemUtility::getCurrentProcessPath );
		def( "getSystemTempPath",SystemUtility::getSystemTempPath );
		def( "getUUID",SystemUtility::getUUID );
		def( "getUUIDStr",SystemUtility::getUUIDStr );
		def( "checkFileExist",SystemUtility::checkFileExist );
		def( "copyFile",SystemUtility::copyFile );
		def( "getCurrentDirectory",SystemUtility::getCurrentDirectory );
		def( "setCurrentDirectory",SystemUtility::setCurrentDirectory );
		def( "createDirectory",SystemUtility::createDirectory );
		def( "removeEmptyDirectory",SystemUtility::removeEmptyDirectory );
		def( "removeFile",SystemUtility::removeFile );
		def( "createInputBox",SystemUtility::createInputBox );
		
		//def( "outputMessage" , outputMessageW );


		class_< StringVector , StringVectorPtr >("StringVector")
			.def (indexing::container_suite< StringVector >() )

			.def("__str__", &getDetailsOfStringVector )
			;

		class_<CrcUtility>("CrcUtility" , no_init )
			.def("getFileCrc32Code", &CrcUtility::getFileCrc32Code )
			.staticmethod( "getFileCrc32Code" )

			.def("initCrc32Code", &CrcUtility::initCrc32Code )
			.staticmethod( "initCrc32Code" )
			;


		class_<OpenGLSupport>("OpenGLSupport" , no_init )
			.def("initialiseOpenGLExtension", &OpenGLSupport::initialiseOpenGLExtension )
			.staticmethod( "initialiseOpenGLExtension" )

			.def("checkTextureCompresstionSupport", &OpenGLSupport::checkTextureCompresstionSupport )
			.staticmethod( "checkTextureCompresstionSupport" )

			.def("checkCubeMapSupport", &OpenGLSupport::checkCubeMapSupport )
			.staticmethod( "checkCubeMapSupport" )

			.def("checkTextureFilterAnisotropicSupport", &OpenGLSupport::checkTextureFilterAnisotropicSupport )
			.staticmethod( "checkTextureFilterAnisotropicSupport" )

			.def("turnOnLargestTexFilterAnisotropic", &OpenGLSupport::turnOnLargestTexFilterAnisotropic )
			.staticmethod( "turnOnLargestTexFilterAnisotropic" )

			.def("checkOpenGLErrorWithoutThrow", &OpenGLSupport::checkOpenGLErrorWithoutThrow )
			.staticmethod( "checkOpenGLErrorWithoutThrow" )

			.def("makeErrorStackEmpty", &OpenGLSupport::makeErrorStackEmpty )
			.staticmethod( "makeErrorStackEmpty" )

			.def("getOpenGLDetails", &OpenGLSupport::getOpenGLDetails )
			.staticmethod( "getOpenGLDetails" )
			;


		class_<StringUtility>("StringUtility" , no_init )
			.def("getFileExtension", &StringUtility::getFileExtension )
			.staticmethod( "getFileExtension" )

			.def("getFilenameWithoutExtension", &StringUtility::getFilenameWithoutExtension )
			.staticmethod( "getFilenameWithoutExtension" )

			.def("getPathFromAbsoluteFilename", &StringUtility::getPathFromAbsoluteFilename )
			.staticmethod( "getPathFromAbsoluteFilename" )

			.def("getFilenameWithoutExtFromAbsPath", &StringUtility::getFilenameWithoutExtFromAbsPath )
			.staticmethod( "getFilenameWithoutExtFromAbsPath" )

			.def("getFilenameFromAbsolutePath", &StringUtility::getFilenameFromAbsolutePath )
			.staticmethod( "getFilenameFromAbsolutePath" )

			.def("toLowerCase", &StringUtility::toLowerCase ) 
			.staticmethod( "toLowerCase" )

			.def("toUpperCase", &StringUtility::toUpperCase )
			.staticmethod( "toUpperCase" )
			;

		class_<UniqueID>("UniqueID" , init<>())
			.def( "isValid", &UniqueID::isValid )
			.def( "getString", &UniqueID::getString )

			.def( "__str__", &UniqueID::getString )

			.def(self == self)
			.def(self < self)
			.def(self > self)

			.def_readwrite( "_id1" , &UniqueID::_id1 )
			.def_readwrite( "_id2" , &UniqueID::_id2 )
		;

		class_<UniqueIDFactory>("UniqueID" , no_init )
			.def( "getUniqueID", &UniqueIDFactory::getUniqueID )
			.staticmethod( "getUniqueID" )

			.def( "getUniqueIDPtr", &UniqueIDFactory::getUniqueIDPtr ,
				return_value_policy<reference_existing_object>() )
			.staticmethod( "getUniqueIDPtr" )
			;

		class_< UniqueIDVector >("UniqueIDVector")
			.def(vector_indexing_suite< UniqueIDVector >())
		;


		class_<Segment3>("Segment3" , init<Vec3, Vec3, float>())
			.def( init<Vec3, Vec3 >() )
			.def( "getPosEnd", &Segment3::getPosEnd )
			.def( "getNegEnd", &Segment3::getNegEnd )

			.def_readwrite( "Origin" , &Segment3::Origin )
			.def_readwrite( "Direction" , &Segment3::Direction )
			.def_readwrite( "Extent" , &Segment3::Extent )
			;

		//------------------------------------------
		// 不能对pair进行绑定
		//------------------------------------------

		typedef std::pair<bool,float> PairBoolFloat;

		class_<PairBoolFloat>("PairBoolFloat")
			.def_readwrite( "first" , &PairBoolFloat::first )
			.def_readwrite( "second" , &PairBoolFloat::second )
			;

		class_<vgKernel::Math>("Math" , no_init )
			.def("floatEqual", &vgKernel::Math::floatEqual )
			.staticmethod( "floatEqual" )

			.def("Sqrt", &vgKernel::Math::Sqrt )
			.staticmethod( "Sqrt" )

			.def("Abs", &vgKernel::Math::Abs )
			.staticmethod( "Abs" )

			.def("trans2DPointTo3DVec", &vgKernel::Math::trans2DPointTo3DVec )
			.staticmethod( "trans2DPointTo3DVec" )

			.def("intersects", intersects1 )
			.def("intersects", intersects2 )
			.def("intersects", intersects3 )
			.staticmethod( "intersects" )

			.def("loadIdentityMatrix", &vgKernel::Math::loadIdentityMatrix , 
			( VGARG("matrix")) )
			.staticmethod( "loadIdentityMatrix" )

			.def("createTranslationMatrix", &vgKernel::Math::createTranslationMatrix , 
			( VGARG("x"), VGARG("y"), VGARG("z"),VGARG("mTranslate") ) )
			.staticmethod( "createTranslationMatrix" )

			.def("createScaleMatrix", &vgKernel::Math::createScaleMatrix , 
			( VGARG("x"), VGARG("y"), VGARG("z"),VGARG("mScale") ) )
			.staticmethod( "createScaleMatrix" )

			.def("createRotationMatrix", &vgKernel::Math::createRotationMatrix , 
			(  VGARG("angle"), VGARG("x"), VGARG("y"), VGARG("z"),VGARG("mMatrix") ) )
			.staticmethod( "createRotationMatrix" )

			.def("multiplyMatrix", &vgKernel::Math::multiplyMatrix, 
			( VGARG("m1"), VGARG("m2"), VGARG("mProduct") ) )
			.staticmethod( "multiplyMatrix" )

			.def("invertMatrix", &vgKernel::Math::invertMatrix, 
			( VGARG("mat"), VGARG("mInverse") ) )
			.staticmethod( "invertMatrix" )

			.def("translateVec3", &vgKernel::Math::translateVec3, 
			( VGARG("mat"), VGARG("v1") ) )
			.staticmethod( "translateVec3" )

			.def("checkPointInTriangle", &vgKernel::Math::checkPointInTriangle,
			( VGARG("point"), VGARG("pa") , VGARG("pb") , VGARG("pc") ) )
			.staticmethod( "checkPointInTriangle" )
		;

		class_<Vec2>("Vec2")
			.def( init<float, float>() )
			.def( init<Vec2>() )
			.def( "length", &Vec2::length )
			.def( "squaredLength", &Vec2::squaredLength )
			.def( "dotProduct", &Vec2::dotProduct )


			.def( "normalise", &Vec2::normalise )
			//.def( "normalisedRef", &Vec2::normalisedRef )
			.def( "midPoint", &Vec2::midPoint )
			.def( "makeFloor", &Vec2::makeFloor )
			.def( "makeCeil", &Vec2::makeCeil )

			.def( "perpendicular", &Vec2::perpendicular )
			.def( "crossProduct", &Vec2::crossProduct )
			.def( "isZeroLength", &Vec2::isZeroLength )
			.def( "normalisedCopy", &Vec2::normalisedCopy )
			.def( "reflect", &Vec2::reflect )

			.def( "getDetails", &Vec2::getDetails )

			.def( "floorProduct", &Vec2::floorProduct )
			.def( "ceilProduct", &Vec2::ceilProduct )

			.def( -self )
			.def(self += self)
			.def(self += float() )
			.def(self + self)
			.def(self -= self)
			.def(self -= float() )
			.def(self - self)
			.def(self *= float() )
			.def(self * float() )
			.def(self /= float() )
			.def(self / float() )
			.def(self == self)
			.def(self != self)

			.def("__str__", &Vec2::getDetails )

			.def_readwrite( "x" , &Vec2::x )
			.def_readwrite( "y" , &Vec2::y )

			.add_static_property( "ZERO" , 
			&VGSC_STATIC_FUNC_PTR( Vec2 , ZERO ) )
			.add_static_property( "UNIT_X" , 
			&VGSC_STATIC_FUNC_PTR( Vec2 , UNIT_X ) )
			.add_static_property( "UNIT_Y" , 
			&VGSC_STATIC_FUNC_PTR( Vec2 , UNIT_Y ) )
			.add_static_property( "NEGATIVE_UNIT_X" , 
			&VGSC_STATIC_FUNC_PTR( Vec2 , NEGATIVE_UNIT_X ) )
			.add_static_property( "NEGATIVE_UNIT_Y" , 
			&VGSC_STATIC_FUNC_PTR( Vec2 , NEGATIVE_UNIT_Y ) )
			.add_static_property( "UNIT_SCALE" , 
			&VGSC_STATIC_FUNC_PTR( Vec2 , UNIT_SCALE ) )
		;


		class_<Vec3>("Vec3")
			.def( init<float, float,float>() )
			.def( init<Vec3>() )
			.def( "length", &Vec3::length )
			.def( "setLength", &Vec3::setLength )
			.def( "getDetails", &Vec3::getDetails )
			.def( "reset", &Vec3::reset )
			.def( "reflect", &Vec3::reflect )
			.def( "normalisedCopy", &Vec3::normalisedCopy )
			.def( "isZeroLength", &Vec3::isZeroLength )
			.def( "perpendicular", &Vec3::perpendicular )
			.def( "floorProduct", &Vec3::floorProduct )
			.def( "ceilProduct", &Vec3::ceilProduct )
			.def( "makeCeil", &Vec3::makeCeil )
			.def( "makeFloor", &Vec3::makeFloor )
			.def( "midPoint", &Vec3::midPoint )
			.def( "normalise", &Vec3::normalise )
			.def( "crossProduct", &Vec3::crossProduct )
			.def( "dotProduct", &Vec3::dotProduct )
			.def( "absDotProduct", &Vec3::absDotProduct )
			.def( "distance", &Vec3::distance )
			.def( "squaredDistance", &Vec3::squaredDistance )
			.def( "squaredLength", &Vec3::squaredLength )

			.def( -self )
			.def( self <= self )
			.def( self >= self )
			.def(self += self)
			.def(self += float() )
			.def(self + self)
			.def(self -= self)
			.def(self -= float() )
			.def(self - self)
			.def(self *= float() )
			.def(self * float() )
			.def(self /= float() )
			.def(self / float() )
			.def(self == self)
			.def(self != self)

			.def("__str__", &Vec3::getDetails )

			.def_readwrite( "x" , &Vec3::x )
			.def_readwrite( "y" , &Vec3::y )
			.def_readwrite( "z" , &Vec3::z )

			.add_static_property( "ZERO" , 
			&VGSC_STATIC_FUNC_PTR( Vec3 , ZERO ) )
			.add_static_property( "UNIT_X" , 
			&VGSC_STATIC_FUNC_PTR( Vec3 , UNIT_X ) )
			.add_static_property( "UNIT_Y" , 
			&VGSC_STATIC_FUNC_PTR( Vec3 , UNIT_Y ) )
			.add_static_property( "UNIT_Z" , 
			&VGSC_STATIC_FUNC_PTR( Vec3 , UNIT_Z ) )
			.add_static_property( "NEGATIVE_UNIT_X" , 
			&VGSC_STATIC_FUNC_PTR( Vec3 , NEGATIVE_UNIT_X ) )
			.add_static_property( "NEGATIVE_UNIT_Y" , 
			&VGSC_STATIC_FUNC_PTR( Vec3 , NEGATIVE_UNIT_Y ) )
			.add_static_property( "NEGATIVE_UNIT_Z" , 
			&VGSC_STATIC_FUNC_PTR( Vec3 , NEGATIVE_UNIT_Z ) )
			.add_static_property( "UNIT_SCALE" , 
			&VGSC_STATIC_FUNC_PTR( Vec3 , UNIT_SCALE ) )
		;


		class_<RgbaQuad>("RgbaQuad")
			.def( init<BYTE , BYTE , BYTE , BYTE >() )

			.def_readwrite( "blue" , &RgbaQuad::blue )
			.def_readwrite( "green" , &RgbaQuad::green )
			.def_readwrite( "red" , &RgbaQuad::red )
			.def_readwrite( "alpha" , &RgbaQuad::alpha )
			;

		class_<Mat4>("Mat4")
			.def( "concatenate", &Mat4::concatenate )

			.def(self + self)
			.def(self - self)
			.def(self * self )
			.def( self * other<Vec3>() )
			.def(self == self)

			.def("__str__", &Mat4::getDetails )

			.def("__getitem__", &Mat4::getItem)
			.def("__setitem__", &Mat4::setItem)

			.add_static_property( "ZERO" , 
			&VGSC_STATIC_FUNC_PTR( Mat4 , ZERO ) )
			.add_static_property( "IDENTITY" , 
			&VGSC_STATIC_FUNC_PTR( Mat4 , IDENTITY ) )
		;

		class_<Box>("Box")
			.def( init<Vec3 , Vec3>() )
			.def( "getCenter", &Box::getCenter )
			.def( "getSize", &Box::getSize )
			.def( "getMinimum", &Box::getMinimum )
			.def( "getMaximum", &Box::getMaximum )
			.def( "setMaximum", &Box::setMaximum )
			.def( "setMinimum", &Box::setMinimum )
			.def( "matrixTranslation", &Box::matrixTranslation )
			.def( "render", &Box::render )

			.def( "merge", merge1 )
			.def( "merge", merge2 )

			.def( "getHalfSize", &Box::getHalfSize )
			.def( "intersects", &Box::intersects )

			.def("__str__", &Box::getDetails )

			.def_readwrite( "_minVertex" , &Box::_minVertex )
			.def_readwrite( "_maxVertex" , &Box::_maxVertex )
		;

		enum_<vgKernel::Plane::Side>("PlaneSide")
			.value("NO_SIDE", vgKernel::Plane::NO_SIDE)
			.value("POSITIVE_SIDE", vgKernel::Plane::POSITIVE_SIDE)
			.value("NEGATIVE_SIDE", vgKernel::Plane::NEGATIVE_SIDE)
			.value("BOTH_SIDE", vgKernel::Plane::BOTH_SIDE)
			;



		class_<vgKernel::Plane>("Plane")
			.def( init<>() )
			.def( init<vgKernel::Plane>() )
			.def( init<Vec3 ,float >() )
			.def( init<Vec3 ,Vec3 >() )
			.def( init<Vec3 ,Vec3, Vec3 >() )

			.def( "getSide", getSide1 )
			.def( "getSide", getSide2 )
			.def( "getSide", getSide3 )

			.def( "redefine", redefine1 )
			.def( "redefine", redefine2 )

			.def( "getDistance", &vgKernel::Plane::getDistance )

			.def( "normalise", &vgKernel::Plane::normalise )

			.def( "isFrontFacingTo", &vgKernel::Plane::isFrontFacingTo )

			.def( "getDetails", &vgKernel::Plane::getDetails )

			.def("__str__", &vgKernel::Plane::getDetails )

			.def_readwrite( "_normal" , &vgKernel::Plane::_normal )
			.def_readwrite( "_distance" , &vgKernel::Plane::_distance )
			;

		class_<vgKernel::Ray>("Ray")
			.def( init<>() )
			.def( init<Vec3 ,Vec3 >() )

			.def( "setOrigin", &vgKernel::Ray::setOrigin )
			.def( "getOrigin", &vgKernel::Ray::getOrigin )
			.def( "setDirection", &vgKernel::Ray::setDirection )
			.def( "getDirection", &vgKernel::Ray::getDirection )

			.def( "getPoint", &vgKernel::Ray::getPoint )
			.def( "render", &vgKernel::Ray::render )
			.def( "getPerpendicularVertex", &vgKernel::Ray::getPerpendicularVertex )

			.def("__str__", &vgKernel::Ray::getDetails )

			.def_readwrite( "mOrigin" , &vgKernel::Ray::mOrigin )
			.def_readwrite( "mDirection" , &vgKernel::Ray::mDirection )
			;

		class_<vgKernel::Quat>("Quat")
			.def( init<>() )
			.def( init<float ,float,float,float >() )
			.def( init<Vec3 ,float>() )

			.def( "createFromAxisAngle", &vgKernel::Quat::createFromAxisAngle )
			.def( "createFromAxisRadian", &vgKernel::Quat::createFromAxisRadian )
			.def( "normalize", &vgKernel::Quat::normalize )
			.def( "slerp", &vgKernel::Quat::slerp )
			.def( "magnitude", &vgKernel::Quat::magnitude )

			.def( "getPitchDegrees", &vgKernel::Quat::getPitchDegrees )
			.def( "getHeadDegrees", &vgKernel::Quat::getHeadDegrees )

			.def("getDetails", &vgKernel::Quat::getDetails )

			.def("__str__", &vgKernel::Quat::getDetails )

			.def_readwrite( "m_x" , &vgKernel::Quat::m_x )
			.def_readwrite( "m_y" , &vgKernel::Quat::m_y )
			.def_readwrite( "m_z" , &vgKernel::Quat::m_z )
			.def_readwrite( "m_w" , &vgKernel::Quat::m_w )
			;

	}
	//----------------------------------------------------------------



}// end of namespace vgScript

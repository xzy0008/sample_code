/*
-----------------------------------------------------------------------------
  VRES(Virtual Reality GIS Engine System)    
  -------------------------------------------------------------
  License details ... waiting to add...
  -------------------------------------------------------------
  Copyright  (C) 2007 , leven - All Rights Reserved
-----------------------------------------------------------------------------
*/

#ifndef __VGFPREREQUISITE_H__
#define __VGFPREREQUISITE_H__

#include <vgMath/vgfGlobalDefinition.h>
#include <vgMath/vgfStandardHeaders.h>


///float的有效数字是7.22个,若要考虑更高的精度,需要使用double,12个有效数字
typedef float	Real;	

namespace vgMath {


#ifdef UNICODE
	typedef std::string			MbsString;

	typedef std::wstring		String;
	typedef std::wfstream		StdFStream;
	typedef std::wstringstream  StdStringStream;
	typedef std::wostringstream StdOStringStream;
	typedef std::wostream		StdOStream;
	typedef std::wistream		StdIStream;

#else
	typedef std::string			MbsString;

	typedef std::fstream		StdFStream;
	typedef std::stringstream	StdStringStream;
	typedef std::ostringstream	StdOStringStream;
	typedef std::ostream		StdOStream;
	typedef std::istream		StdIStream;

#endif

	/**
		@date 	2007/02/21  9:52	
		@author  leven
	
		@brief 	此文件包含大多数对类型的定义.
		另外,包含减少编译时间而采用的对类的定义.(详见Effective C++)
	
		@see    
	*/
	
	


	typedef unsigned short	ushort;

	typedef unsigned long	ulong;

	//typedef uchar byte;

	// Integer formats of fixed bit width
	typedef unsigned int uint32;
	typedef unsigned short uint16;
	typedef unsigned char uint8;

	typedef uint32 RGBA;
	typedef uint32 ARGB;
	typedef uint32 ABGR;
	typedef uint32 BGRA;





	/// 所有类的声明,减少编译时间,具体见Effective C++
	class Angle;
	class AxisAlignedBox;
	class ColorValue;
	class Degree;
	class Math;
	class Matrix3;
	class Matrix4;
	class Plane;
	class Quaternion;
	class Radian;
	class Ray;
	class Sphere;
	class Vector2;
	class Vector3;
	class Vector4;

	class Frustum;
	
} // end of namespace vgMath


#endif // end of __VGFPREREQUISITE_H__
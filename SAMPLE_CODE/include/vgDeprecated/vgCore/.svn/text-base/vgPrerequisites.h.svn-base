

#ifndef __VGPREREQUISITES_H__
#define __VGPREREQUISITES_H__



#include <vgMath/vgfPrerequisites.h>
#include <vgGlobalDefinition.h>
//#include <vgImportStaticLib.h>
//#include <vgStandardHeaders.h>

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdarg>
#include <cmath>
//#include <xutility>


// STL containers
#include <vector>
#include <map>
#include <string>
#include <set>
#include <list>
#include <deque>
#include <queue>
//#include <bitset>

//#include <hash_map>

// STL algorithms & functions
#include <algorithm>
#include <functional>
#include <limits>

// C++ Stream stuff
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

/// 使用全局std命名域.虽然这不是推荐的做法.
using namespace std;

#include <vgTex/tvgString.h>



namespace vgCore {

	using namespace vgMath;


	///float的有效数字是7.22个,若要考虑更高的精度,需要使用double,12个有效数字
	//typedef float	Real;		

	//typedef unsigned char	uchar;
	//typedef unsigned short	ushort;
	//typedef unsigned int	uint;
	//typedef unsigned long	ulong;

	//// Integer formats of fixed bit width
	//typedef unsigned int uint32;
	//typedef unsigned short uint16;
	//typedef unsigned char uint8;

	//typedef uint32 RGBA;
	//typedef uint32 ARGB;
	//typedef uint32 ABGR;
	//typedef uint32 BGRA;

	/// 定义整数单位.
	typedef long  Integer;


	typedef  std::wstring WString;


	//typedef  vgMath::String  String;
	typedef  std::wstring WString;


	typedef  std::vector<String> StringVector;

	template<class T>
	class SharedPtr;



	typedef SharedPtr<StringVector> StringVectorPtr;


	typedef std::pair<String,String> StringPair;
	typedef std::vector< StringPair > StringPairList;
	typedef SharedPtr< StringPairList > StringPairListPtr;



	//typedef streamoff StreamPos;
	typedef long StreamPos;

	typedef ios_base::seek_dir StreamWriterSeekDir;



	class  Root;
	class  Warning;
	class  WarningFactory;


	//class ColorValue;

	class Billboard;
	class BillboardSet;
	class Texture;
	class TextureBuilder;
	class TextureBuilderUtil;
	class TextureManager;


	class TexturePtr;
	class TextureBuildOption;
	class HugeImageRender;
	class HugeImageProcessor;

	class GpuSupport;
	class GpuContext;
	class GpuProgram;
	class GpuManager;

	class Archive;
	class ArchiveManager;
	class ArchiveFactory;
	class ZipArchive;
	class FileSystemArchive;
}





#endif // end of __VGPREREQUISITES_H__
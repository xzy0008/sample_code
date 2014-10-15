


#ifndef __VGIFILEDEFINITIONVGI_H__
#define __VGIFILEDEFINITIONVGI_H__
#include <vgImage/vgiDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSharePtr.h>

	
namespace vgImage {


	using namespace vgKernel;


#define VGI_NAME_LENGTH	64


//#define VGI_MAX_FILENUM		2048

// 单个vgi文件的最大容量.以字节为单位
#define VGI_MAX_SINGLE_FILE_SIZE		( 512 * 1024 * 1024 )
//#define VGI_MAX_SINGLE_FILE_SIZE		( 512 * 1024 )

	class VgiBrief;

	class  VGI_EXPORT VgiHeader
	{
	public:
		VgiHeader()
		{
			setDefault();
		}
		~VgiHeader()
		{

		}

	private:

		void setDefault();
	public:

		char	_fourCC[4];
		int		_version;
		long	_sizeOfHeader;
		long	_sizeOfWholeFile;
		long	_numberOfBriefs;
		long	_lengthOfOneBrief;
		long	_positionOfBriefs;


		//long	_reserved1;
		// 使用_reserved1用来指代下一个链接的vgi文件
		// 例如, "test.vgi" , 如果为0, 表示没有下一个链接文件.
		// 如果为1,表示下一个文件为test.part1.vgi
		long _nextFileID;

		long	_reserved2;
		long	_reserved3;
		long	_reserved4;

	};


	enum VgiBriefType
	{
		VGI_BRIEF_TYPE_DDS
	};

	class  VGI_EXPORT VgiBrief
	{
	public:
		VgiBrief()
		{
			setDefault();
		}
		~VgiBrief()
		{
			setDefault();
		}

		// load from whole image buffer.
		bool getInfoFromBuffer( const String& filemetaname , 
			const char* const buffer, 
			const long& buffer_size );

	private:
		void caluateLodOffsetAndSize();

		void setDefault();

		static long getMaxMipmapNum(const long& width,const long& height);

	public:

		VgiBriefType _type;

		// 注意,保存的都是小写形式
		char _fileName[VGI_NAME_LENGTH];

		long  _metaFileOffset;
		long  _metaFileSize;

		// lod0 is coarsest.
		// 注意!这里是相对于_metaFileOffset的偏移!!
		// _mipMapLod是每层LOD的lod参数
		long  _offsetLod[VGLOD_N];
		long  _sizeLod[VGLOD_N];
		long   _mipMapLod[VGLOD_N];


		long   _width;
		long   _height;

		GLenum  _openGLFormat;


	};

	typedef vgKernel::SharePtr<VgiBrief> VgiBriefPtr;

	typedef std::vector<VgiBriefPtr> VgiBriefPtrVec;
	
	
}// end of namespace vgImage
	


#endif // end of __VGIFILEDEFINITIONVGI_H__
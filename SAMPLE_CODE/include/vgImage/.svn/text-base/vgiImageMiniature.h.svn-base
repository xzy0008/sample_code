


#ifndef __VGIIMAGEMINIATURE_H__
#define __VGIIMAGEMINIATURE_H__
#include <vgImage/vgiDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgImage/vgiFileDefinitionVgi.h>
#include <vgAsyn/vgaFileHandle.h>



namespace vgImage {



	class FileHandleVgi;



	/**
		图像文件的索引信息
	*/
	class  VGI_EXPORT ImageMiniature
	{
	public:

		ImageMiniature( VgiBrief* brief ,
			vgAsyn::FileHandle* pfilehandle );


		~ImageMiniature()
		{

		}


		inline bool isValid()
		{
			return _isValid;
		}

		inline String getMetaFileName() const
		{
			return _metaFileName;
		}

		/**
			注意,客户端负责删除
		*/
		vgAsyn::FileInfo* getMetaFileInfo();

		long getMetaFileSize() const
		{
			return _metaFileSize;
		}

		vgAsyn::FileInfo* getFileInfoByLod( const int& lod );

		GLuint createTextureID( char* buf_input , const int& buf_size ,
			const int& lod );

		long getWidth() const
		{
			return _width;
		}

		long getHeight() const
		{
			return _height;
		}

		String getMetaFileName()
		{
			return _metaFileName;
		}

	private:

		void setDefault();

	private:

		bool  _isValid;

		String  _metaFileName;

		long  _metaFileOffset;
		long  _metaFileSize;

		// lod0 is coarsest.
		// 注意!这里是绝对的offset,已经加过metafileoffset
		long  _offsetLod[VGLOD_N];
		long  _sizeLod[VGLOD_N];
		long   _mipMapLod[VGLOD_N];

		long   _width;
		long   _height;

		GLenum  _openGLFormat;



		vgAsyn::FileHandle* _pFilehandle;
	};




}// end of namespace vgImage



#endif // end of __VGIIMAGEMINIATURE_H__
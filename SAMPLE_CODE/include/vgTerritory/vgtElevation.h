


#ifndef __VGTERRITORY_TELEVATION_H__
#define __VGTERRITORY_TELEVATION_H__


#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgTerritory/vgtFileDefinitionVtr.h>
#include <vgAsyn/vgaFileInfo.h>
	
namespace vgTerritory {

	class ElevationItem;

	/**
		@date 	2008/09/08  19:24	
		@author  leven
	
		@brief 	相当于vgMesh中的Mesh类.

		在这里发送IoRequest
	
		@see    
	*/
	class  VGT_EXPORT Elevation
	{
	public:
		Elevation( ElevationItem* father , 
			VtrBrief* brief , 
			vgAsyn::FileHandle* pfilehandle , int lod );

		~Elevation();

	public:

		const int getReferenceCount() const
		{
			return _referenceCount;
		}

		/**
			获得读取外存的IoRequest,注意,是同步模式.
			目前只用于保存操作, 客户端负责删除操作
			_deleteBufferWhenDestruction是true的.用户可以手动设置。
		*/
		vgAsyn::IoRequest* getIoRequest();

		void addReference();

		void releaseReference();

		ElevationItem* getFatherElevItem()
		{
			return _fatherItem;
		}

		vgAsyn::FileInfo* getFileInfoClone()
		{
			assert( _lodInfo != NULL );
			return _lodInfo->clone();
		}

		vgAsyn::FileInfo* getFileInfoPtr()
		{
			return _lodInfo;
		}

		const GLuint getHeightMapID() const
		{
			return _heightMapID;
		}

		const int getLod() const
		{
			return _lod;
		}

		/**
			通过内存中的buffer区域,到显存.注意
			buf_size是以字节为单位.
		*/
		bool setHeightMapID( void* buffer,  long buf_size );

		bool isEmptyHeightMap() const
		{
			return _heightMapID == VG_NULL_TEXTURE_ID;
		}

		/**
			当数据在显存中时,可以获得buffer的指针.
			反之,将返回NULL.
		*/
		float* getHeightMapBuffer();

		/**
			注意和ElevationItem的getHeightMapWidth的区别.
		*/
		long getBufferHeightMapWidth() const
		{
			assert( _heightMapBufWidth != 0 );
			return _heightMapBufWidth;
		}

		/**
			 把当前的buffer区域的数据dump到显存.
			 注意,当_heightMapID == VG_NULL_TEXTURE_ID时
			 或者buffer为空时,直接返回false
		*/
		bool dumpBufferToHeightMap();

	private:

		/**
			用于提交IoRequest的时候需要
		*/
		ElevationItem* _fatherItem;

		int _lod;

		vgAsyn::FileInfo* _lodInfo;

		int	 _referenceCount;

		/**
			存储高度图的信息
		*/
		GLuint _heightMapID;

		float* _heightMapBuffer;
		GLint _heightMapBufWidth;
		GLint _heightMapBufHeight;

	};
	
	
}// end of namespace vgTerritory
	


#endif // end of __VGTERRITORY_TELEVATION_H__



#ifndef __VGTERRITORY_VGTRHEADER_H__
#define __VGTERRITORY_VGTRHEADER_H__


#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkStreamReader.h>
#include <vgKernel/vgkStreamWriter.h>
#include <vgKernel/vgkForward.h>



namespace vgTerritory {


#define VG_VGTR_NAME_LENGTH	64

	class  VGT_EXPORT VgtrHeader
	{
	public:
		VgtrHeader();
		~VgtrHeader()
		{
			
		}
	
	public:
	
		char fourCC[4];		// 为"vgtr",注意是小写的

		int version;		// 1

		/**
			本文件名,最大为64长度的名称
			注意,在vtr文件中,每一个vgtr文件的name并不保证其意义一定
			和vtr brief相一致的.有可能保存的是最最原始的vgtr文件名称.
			后续的工作中将会对此信息做出撤出操作.
		*/
		char name[ VG_VGTR_NAME_LENGTH ];

		/**
			对应的纹理的文件名
		*/
		char texname[ VG_VGTR_NAME_LENGTH ];	


		/**
			N值,默认为8,即每层256个网格数
		*/
		long N;	

		/**
			每个cell对应的texture大小,注意是最精细层的.	
		*/
		long cellTexSize;

		/**
			x和z方向数量
			注意!这里必须一样才行!
		*/
		uint xNum;			
		uint zNum;

		/**
			逻辑原点,注意!!有了vtr之后这个值一般用不到!
		*/
		double originX;		
		double originY;
		double originZ;

		/**
			需要传入GPU的参数
		*/
		float displaceScaleY;	// Y轴的放大值
		float displaceChunkScale;	// 本小块相对于大图的放大值
		float displaceChunkBiasX;	// 本小块相对于大图的偏移, x 方向
		float displaceChunkBiasZ;	// 本小块相对于大图的偏移, z 方向

		/**
			间距
		*/
		float cellsize;	// 间距

		/**
			数据区起始和大小
			注意!这里的length是以字节为单位!!并且是相对于本文件!!
			这里,VGLOD_CLEAR指代最清晰的一级
		*/
		long dataPosition[ VGLOD_N ];
		long dataLen[ VGLOD_N ];	


	public:
		String getDetails();

	};


	typedef vgKernel::SharePtr<VgtrHeader> VgtrHeaderPtr;

	class  VGT_EXPORT VgtrFile
	{
	public:
		VgtrFile();
		~VgtrFile();

		long writeToStream( const vgKernel::StreamWriterPtr pwriter );

		bool readFromStream( const vgKernel::StreamReaderPtr preader );


		String getDetails();

#if 0
		void render();
#endif

	public:

		VgtrHeaderPtr _headerPtr;

		/**
			没有lod数据的data
		*/
		float* _dataLod[ VGLOD_N ];
	};
	
	typedef vgKernel::SharePtr<VgtrFile> VgtrFilePtr;

	typedef std::vector<VgtrFilePtr> VgtrFilePtrVec;

	
	
}// end of namespace vgTerritory

#endif // end of __VGTERRITORY_VGTRHEADER_H__




#ifndef __VGTERRITORY_TERRAINHUGEIMAGEPROCESSOR_H__
#define __VGTERRITORY_TERRAINHUGEIMAGEPROCESSOR_H__

#include <vgKernel/vgkForward.h>
#include <vgTerritory/vgTerrainHugeImageUtil.h>
#include <vgKernel/vgkSharePtr.h>
#include <vgImage/vgiCximageWrapper.h>
#include <vgKernel/vgkStringUtility.h>
#include <vgKernel/vgkProcessObserver.h>


#include <vgTerritory/vgtHugeProcessProcessor.h>


namespace vgTerritory {

	

	/**
		@date 	2007/04/05  11:06	
		@author  Leven
	
		@brief 	巨图处理机类,负责将大图切成小图.
	
		@see    
	*/

	class HugeImagesProcessor : public vgKernel::ProcessNotifier
	{
	public:
		HugeImagesProcessor()
			: m_pFileNamesInfo (),
			m_pAimsblocksOption (),
			m_pfblockVector (),
			m_pSmallblockLayout ()
		{
		}

		virtual ~HugeImagesProcessor();

		/// 初始化文件名称参数.
		bool initialiseFileNames(
			const TCHAR** const &chararray ,
			const long& col ,
			const long& row , 
			const bool& loginfo = true );


		/// 初始化文件名称参数.
		bool initialiseFileNames( const FileNamesInfoPtr& inputFileInfo )
		{
			if ( inputFileInfo.isNull() )
			{
				return false;
			}
			this->m_pFileNamesInfo = inputFileInfo;
			return true;
		}

		void initialiseFileBlocks( const fileBlockVectorPtr inputfileblocks );

		/// 初始化生成参数.
		bool initialiseParameters(
			uchar* filledColor,
			const bool& remove_input_files,
			const String& temp_file_ext , 
			const String& tmp_path , 
			const bool& remove_tmp_file,
			const String& fileprefix,
			const long& width,
			const long& height,
			const String& tmpfilepostfix		= _T( "bmp" ),
			const String& fileposfix			= _T( "dds" ),
			const bool& reverseSequence			= false,
			const bool& axisLeftTop				= false,
			const bool& loginfo					= true,
			const bool& overrid					= false,
			const bool& outputcombinesblock		= false,
			const String& outcombinesblockname	= _T( "" ),
			const bool& outputcombinefblock		= false,
			const String& outcombinefblockname	= _T( "" ),
			const bool& drawinfo				= false,
			const ImagePos& offset				= ImagePos::ZERO,
			const long& pixceloverlap		= 1,
			const long& sblocknum			= -1 ,
			const long& width_and_height_add_one = 0 );


		/// 通过默认的参数构造.
		bool initDefaultParameters(const String& fileprefix);


		/// 关键运行程序,在这里会将提交的参数一并处理,例如计算大小,保存文件等.
		/// 注意和makeProcessing的区别:
		///   1.makeProcessing()只会产生必要的数据而不保存,这里会处理并保存.
		///   2.这个函数和makeProcessing()是getHugeImageBlockInfos()的必要条件
		///   3.为什么要分开呢?有时候我已经处理完了,只想得到数据而已,并不想再浪费
		/// 时间保存一下了,所以只要计算就可以了,便于手动操作.
		///  TODO: 考虑是否有必要将计算好的信息存入一个文本文件,然后再读取出来.
		bool makeProcessingAndSaving();

		/// 分开的2个程序.注意:要顺序执行.
		bool makeProcessing();
		bool makeSaving();

		/// 如果指针存在指向,删除之.
		void  clear();

		HugeImageBlockInfoVectorPtr getHugeImageBlockInfos();


		FileNamesInfoPtr getFileNamesInfo() const
		{
			return this->m_pFileNamesInfo;
		}

	private:


		/// 查看文件是否存在.此用来检查初始化时之前产生的文件.
		static bool checkFileExist( const String& filename );

		/// 删除存在的文件.即封装::remove ( from stdio.h )
		/// 注意,此时并不捕获异常.
		static bool removeFile( const String& filename , const bool& iflog = true );


		/// 这里暂时这样写.以后要更改!!!!!!!!!!
		/// 正确的做法应该是在UniformImageFile中声明getImageFileRect()
		static bool readImageFileRect( const String& filename , ImageRect& rect )
		{
			CximageWrapperPtr pimg( new CximageWrapper );

			bool load = pimg->loadHeaderFromFile( filename );

			if ( load == false )
			{
				return false;
			}

			rect = pimg->getImageSize().getLocalRect();

			return true;
		}

		/// 查看必要的初始化指针是否都存在,以确认安全性.
		inline bool isSafe() const
		{
			//if ( m_pFileNamesInfo.isNull() )
			//{
			//	return false;
			//}
			if ( m_pAimsblocksOption.isNull() )
			{
				return false;
			}
			return true;
		}

		/// 处理文件块布局.
		static fileBlockVectorPtr createFileblockLayout( const FileNamesInfo& fileinfo ,
			const AimSmallBlocksOption& aiminfo );

		/// 处理小文件块布局.
		static smallBlockVectorPtr createDefaultSmallblockLayout( const fileBlockVector& fblockvec , 
			const AimSmallBlocksOption& aiminfo );

		/// 处理fileBlockVector中的tasklist.
		/// 在这之前要处理好smallBlockVector
		/// 在这里只要计算他们之间的交叉部分,然后保存tasklist即可.
		static bool coreFunction( fileBlockVector& fblockvec ,
			const smallBlockVector& sblockvec , 
			const AimSmallBlocksOption& aimblockinfo );

		/// 初始化保存文件的环境.
		/// 前提:fileBlockVector已知.
		/// 注意:这里要传入smallblockLayout值,因为其中含有所要生成的最终文件列表.
		static bool initSavingEnvironment( const fileBlockVector& fblockvec ,
			const AimSmallBlocksOption& aiminfo ,
			const smallBlockVector& sblockLayout );

		/// 保存fileBlock中taskList文件列表.
		/// 注意此项对生成的tmp文件并不做处理.
		bool processSaving( const fileBlockVector& fblockvec ,
			const AimSmallBlocksOption& aiminfo );

		static bool processTempFiles( fileBlockVector& fblockvec ,
			const AimSmallBlocksOption& aiminfo );

		static bool processCombining( const fileBlockVector& fblockvec ,
			const AimSmallBlocksOption& aiminfo ,
			const smallBlockVector& sblockLayout);
		
		static HugeImageBlockInfoVectorPtr getHugeImageBlockInfoVector(
			const smallBlockVector& sblockLayout ,
			const AimSmallBlocksOption& aiminfo );


	private:

		FileNamesInfoPtr		m_pFileNamesInfo;
		AimSmallBlocksOptionPtr	m_pAimsblocksOption;

		fileBlockVectorPtr	m_pfblockVector;

		/// 为什么要有这一项?就算有,为什么最后不删除?
		/// 这是因为,这只是个layout,相当于覆盖整个区域的块的集合,
		/// 试想,如果删掉后我又想更改上次保存的Layout,怎么办呢?从
		/// m_pfblockVector中提取吗?虽然可以节省内存,但速度上不是我要的.
		/// 先让它留在内存,必要时我可以保存在硬盘上,然后读取.这个是简单的.
		/// 综合考虑,在易用性和扩展性上,我保留此项.
		smallBlockVectorPtr	m_pSmallblockLayout;

		HugeProcess::Processor _hugeProcessor;

	};

	
	
}// end of namespace vgTerritory

#endif // end of __VGTERRITORY_TERRAINHUGEIMAGEPROCESSOR_H__
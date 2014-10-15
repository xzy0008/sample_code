


#ifndef __VGTERRITORY_TERRAINHUGEIMAGEUTIL_H__
#define __VGTERRITORY_TERRAINHUGEIMAGEUTIL_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkImageRect.h>
#include <vgKernel/vgkVec2.h>
#include <vgKernel/vgkVec3.h>
#include <vgImage/vgiImageUtility.h>
#include <vgKernel/vgkStringUtility.h>


namespace vgTerritory {

	
	using namespace vgKernel;
	using namespace vgImage;

	class fileBlock;

	/// 小块数据保存类.
	/// 此时是保存数据的最小单位.
	class smallBlock 
	{
	public:
		smallBlock()
			:hasIntersect(false) 
		{
		}
		~smallBlock()
		{

		}
		/// 小块图像在整个拼接好的大图中的位置,可理解为绝对位置.
		ImageRect absoluteRect;

		/// 小块图像在当前文件中的相对位置.
		/// 这个时候的长宽应该和absoluteRect一样.
		ImageRect relativeRect;

		/// 小块图像的文件名,即欲保存的文件名.
		String blockFileName;

		/// 查看是否有交叠部分.
		bool  hasIntersect;

		/// 表示当前相对于此block的intersect区域.
		/// 可以打印出来,调试的时候可以添加上.
		//ImageRect  IntersectRect;

		/// 在一系列smallblock中的标号.
		/// 如 x=1,y=3.指的是以(0,0)为起点,(1,3)的位置.
		ImagePos  worldSequenceNumber;

	public:
		inline bool isInFileBlock(const fileBlock& fblock) const;

		inline String getDetails() const ;

		/// 通过序号得到文件名后缀.
		String getPostfixNumFlag( const bool& reverseSeq ) const;

	private:
		inline bool checkSafe() const
		{
			if ( worldSequenceNumber.x < 0 || worldSequenceNumber.y < 0 )
			{
				return false;
			}
			return true;
		}
	};
	

	class smallBlockVector : public std::vector<smallBlock>
	{
	public:
		smallBlockVector()
		{

		}
		~smallBlockVector()
		{

		}
	
		ImageRect getWorldImageRect() const
		{
			ImagePos minpos = ImagePos::MAX;
			ImagePos maxpos = ImagePos::MIN;
			for ( std::vector<smallBlock>::const_iterator i = std::vector<smallBlock>::begin() ;
				i != std::vector<smallBlock>::end() ;
				++ i )
			{
				maxpos = ImageUtility::getMaximalPos( maxpos , i->absoluteRect.maxPos );
				minpos = ImageUtility::getMinimalPos( minpos , i->absoluteRect.minPos );
			}

			/// 注意此时ImageRect的最小点并不一定是ImagePos::ZERO!
			return ImageRect( minpos , maxpos );
		}
	};

	typedef  vgKernel::SharePtr<smallBlockVector> smallBlockVectorPtr;

	/// 这里为了方便起见还是都用了public,理应使用friend来使几个类耦合.
	/// 但这里尝试了一下,由于fileBlockVector是继承,所以很多友员弄的不明不白.
	/// 为了清晰,这里使用public.也要注意:此后非有必要,不得使用其裸露的数据成员.
	class fileBlock 
	{
	public:

		fileBlock()
		{

		}
		~fileBlock()
		{

		}

		/// 获得本地Rect,即原点开始,长宽处结束.
		inline ImageRect  getLocalRect() const 
		{
			ImagePos  p(fileAbsoluteRect.getWidth() ,fileAbsoluteRect.getHeight() );
			ImageRect rect( ImagePos::ZERO , p);
			return rect;
		}
		inline ImageSize getImageSize() const
		{
			return ImageSize(fileAbsoluteRect.getWidth() ,fileAbsoluteRect.getHeight());
		}


		String  getDetails() const;

	public:
		/// 图像块的绝对位置.
		ImageRect fileAbsoluteRect;

		/// 原始的文件名.
		String fileSrcName;

		/// 即为任务表.
		/// 将计算好的smallBlock保存进tasklist,然后处理这个列表即可.
		smallBlockVector  taskList;	
	};
	
	class fileBlockVector : public std::vector<fileBlock>
	{
	public:
		fileBlockVector()
		{
		}
		~fileBlockVector()
		{
		}

		ImageRect getWorldImageRect() const;
	
	};

	typedef vgKernel::SharePtr<fileBlockVector>  fileBlockVectorPtr;

	/// 添加的文件信息类
	struct FileNamesInfo
	{
	public:
		FileNamesInfo(StringVector namevec ,
			long col,
			long row)
			: filenameVector(namevec) ,
			columnNum(col) ,
			rowNum(row) 
		{

		}

		FileNamesInfo()
			: filenameVector() ,
			columnNum(0) ,
			rowNum(0) 
		{
		}

		StringVector filenameVector;
		long		 columnNum;
		long		 rowNum;

		String getDetails() const;
	};


	typedef vgKernel::SharePtr<FileNamesInfo> FileNamesInfoPtr;


	class AimFileBlocksOption
	{
	public:
		AimFileBlocksOption()
		{
			this->setParametersDefault();
		}
		~AimFileBlocksOption()
		{

		}
	
		long aimFileWidth;
		long aimFileHeight;

		String  aimFileExtension;
		String  aimFilePrefix;

		bool	ifLog;

		const String getAimFileName( const long& col , 
			const long& row ) const 
		{
			std::ostringstream o;
			o << aimFilePrefix << _T( "_") 
			  <<  col  <<  _T( "_" )  <<  row  <<  _T( "." )  <<  aimFileExtension; 

			return o.str();
		}

		void setParameters( const long& width ,
			const long& height , 
			const String& ext ,
			const String& prefix , 
			const bool& iflog )
		{
			this->aimFileHeight = height;
			this->aimFileWidth = width;
			this->aimFileExtension = ext;
			this->aimFilePrefix = prefix;
			this->ifLog = iflog;
		}

	
	protected:
	
		
		void setParametersDefault()
		{
			aimFileWidth = 1024;
			aimFileHeight = 1024;
			this->aimFileExtension = _T( "bmp" );
			this->aimFilePrefix = _T( "TEMP_NAME" );
			this->ifLog = false;
		}
	
	private:
	
	
	};


	typedef vgKernel::SharePtr<AimFileBlocksOption> AimFileBlocksOptionPtr;

	/// 期待得到的smallBlock的信息.
	struct AimSmallBlocksOption 
	{
		/// 必要时还可以添加诸如边界上如何处理等信息.
		/// 比如:我想限制大小,可以在这里写入num值,然后在程序中控制.
	public:

		static const long DEFAULT_WIDTH;
		static const long DEFAULT_HEIGHT;

		/// 期待得到的smallBlock的长宽.
		long aimWidth;
		long aimHeight;

		/// 欲得到的文件前缀
		String  aimFilePrefix;

		/// 欲得到的文件后缀,要包含文件类型.如"dds"
		/// 注意大小写.
		String  aimFilePostfix;

		/// 中间文件后缀,也要包含类型.如"bmp"
		/// 注意大小写.
		String  aimTempFilePostfix;

		/// 期待得到的像素重叠信息.
		/// 为0时没有重叠.
		/// 为1时表示一个像素的重叠,依次类推.
		long aimPixcelOverlap;

		/// 期待得到的smallBlock的数目.
		/// 为-1时生成所有.
		/// 为其他值时表示生成特定的数目.
		long aimSmallBlocksNum;

		/// 欲得到的像素偏移.
		ImagePos aimOffset;

		/// 是否在图像上写明信息.
		bool  ifDrawInfo;

		///是否生成log日志信息.
		bool  ifLogInfo;

		/// 最后是否输出最大图(即所有文件的拼合图)
		/// 这里是拼合原始图呢?还是拼合小图?
		/// 由于smallBlock可能是限定的,即拼合后的图并不一定和
		/// 原始的拼合图一样,所以在这里给出2个选项.
		bool  ifOutputCombinedFileBlocks;

		/// 是否翻转序列,即保存的文件名
		/// 如:
		/// 为false时,行顺序为(0,0) , (1,0) ,(2 , 0)...
		/// 若为true时,行顺序为(0,0) , (0,1) ,(0 , 2)...
		bool  ifReverseSequence;

		/// 坐标是否在左上角,
		/// 为true时表示左上角,
		/// 为false时为左下角.
		bool  ifAxisLeftTop;

		/// 此时输出的拼合fileblock的文件名
		/// 为什么这里不用prefix和postfix的形式了?
		/// 这里只是单个文件,没有太多的必要就不要复杂.
		/// 而且,最终的文件还要满足与切割好的图片不相同
		/// 文件格式的需求,所以这里这么设定还是有些必要性.
		String aimCombinedFBlockName;

		bool  ifOutputCombinedSmallBlocks;

		/// 此时输出的拼合smallblock的文件名
		String aimCombinedSBlockName;

		/// 覆盖已存在文件选项.
		bool  ifOverrideExist;

		//------------------------------------------
		// 后来添加.长宽为512时,创建513长度时要用到这个参数.
		//------------------------------------------
		long widthAndHeightAddOne;

	public:
		AimSmallBlocksOption()
		{
			this->setParametersDefault();
		}

		AimSmallBlocksOption(const String& filename)
		{
			this->setParametersDefault( filename );
		}

		AimSmallBlocksOption(
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
			const long& width_and_height_add_one = 0);


		~AimSmallBlocksOption()
		{

		}

		/// 设定参数.
		void setParameters(
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
			const long& width_and_height_add_one = 0);

		/// 设定默认值.
		void  setParametersDefault(const String& fileprefix = _T( "cuttedimage" ));

		/// 得到详细的内容.
		String getDetails() const;

		/// 查看输入的参数是否正确.
		bool  checkParametersIsAllRight();
	};


	typedef vgKernel::SharePtr<AimSmallBlocksOption> AimSmallBlocksOptionPtr;

	/// 文件块信息,用于HugeImageProcessor的输出.
	/// 可用此产生渲染的图像.
	class HugeImageBlockInfo 
	{
	public:
		HugeImageBlockInfo( float ratio = 1.0f)
		{
			this->m_Ratio = ratio;
		}
		~HugeImageBlockInfo()
		{

		}
	
		vgKernel::Vec3 getVertexAsVector3( const long& n ) const
		{
			assert( n >= 0 && n < 4 );
			return vgKernel::Vec3( m_Vertex[n].x , 0 , m_Vertex[n].y );
		}

		inline void setRatio( const float& r )
		{
			this->m_Ratio = r;
			this->updateRatio();
		}

		
		/// 保存的图片序号.
		ImagePos m_WorldNumber;

		/// 此block块对应的文件名称.
		String   m_BlockFileName;

		/// 从integer转换到float所使用的ratio.
		float m_Ratio;

		/// 此block块的四个顶点.
		/// 注意为2维定点.
		/// 要想获得三维定点,可使用方法getVertexAsVector3
		vgKernel::Vec2  m_Vertex[4];


		String getDetails() const
		{
			String result(_T( "HugeImageBlockInfo details : " ));
			result += _T( "FileName = " ) + m_BlockFileName 
				+ _T( " , Ratio = " ) + StringUtility::textCast( m_Ratio )
				+ _T( " , Vertex = " );
			for ( int i = 0 ; i < 4 ; ++ i )
			{
				result += m_Vertex[i].getDetails() + _T( "  " ) ;
			}

			result += _T( "\n" );
			return result;
		}


	//private:


		inline void updateRatio()
		{
			const ImagePos& pos = m_WorldNumber;
			m_Vertex[3] =
				ImageUtility::getVector2FromImagePos( pos , m_Ratio ); 

			m_Vertex[2] =
				ImageUtility::getVector2FromImagePos( ImagePos( pos.x + 1 , pos.y ) , m_Ratio ); 

			m_Vertex[1] =
				ImageUtility::getVector2FromImagePos( ImagePos( pos.x + 1 , pos.y + 1 ) , m_Ratio ); 

			m_Vertex[0] =
				ImageUtility::getVector2FromImagePos( ImagePos( pos.x , pos.y + 1 ) , m_Ratio ); 
		}

	};

	/// 在这里添加必要的信息,比如想获取总的长宽,
	/// 再比如设置总的大小,通过一个ratio值伸展等等.
	class HugeImageBlockInfoVector : public std::vector<HugeImageBlockInfo>
	{
	public:
		HugeImageBlockInfoVector()
		{
			VGK_TRACE_SHORT( _T( "huge imageblockvec created" ));
		}
		~HugeImageBlockInfoVector()
		{
			VGK_TRACE_SHORT( _T( "huge imageblockvec destructed" ));
		}

		inline String getDetails() const
		{
			String result;
			for ( std::vector<HugeImageBlockInfo>::const_iterator i = std::vector<HugeImageBlockInfo>::begin() ;
				i != std::vector<HugeImageBlockInfo>::end() ;
				++ i )
			{
				result += i->getDetails();
			}
			return result;
		}
		inline void setRatio( const float& r )
		{
			for ( std::vector<HugeImageBlockInfo>::iterator i = std::vector<HugeImageBlockInfo>::begin() ;
				i != std::vector<HugeImageBlockInfo>::end() ;
				++ i )
			{
				i->setRatio( r );
			}
		}
		
	};

	typedef  vgKernel::SharePtr<HugeImageBlockInfoVector>  HugeImageBlockInfoVectorPtr;


	class HugeImageUtil
	{
	public:
		HugeImageUtil();
		~HugeImageUtil();
	
		/// 从char *数组创建FileNamesInfo
		/// 注意: 要保证数组容量和col以及row对应,否则出现越权内存访问错误.
		static FileNamesInfoPtr  createFileNamesInfoFormArray( 
			const StringVector& stringvec ,
			const long& col ,
			const long& row , 
			const bool& loginfo );


		/// 从String *数组创建FileNamesInfo
		/// 注意: 要保证数组容量和col以及row对应,否则出现越权内存访问错误.
		static FileNamesInfoPtr  createFileNamesInfoFormArray( 
			const TCHAR** const &chararray ,
			const long& col , 
			const long& row , 
			const bool& loginfo );
	
	
	};




#include "vgTerrainHugeImageUtil.inl"
	
	
	
}// end of namespace vgTerritory

#endif // end of __VGTERRITORY_TERRAINHUGEIMAGEUTIL_H__

#ifndef __VGMVGFILEDEFINITIONVG_H__
#define __VGMVGFILEDEFINITIONVG_H__

#include <vgKernel/vgkStreamWriter.h>

namespace vgMod{

	/**
	@date 	2009/03/02  15:12	
	@author  lss

	@brief 	

	@see    
	*/
	class   VGDEP_EXPORT VGFileHeader 
	{
	public:
		char	vgfileheader[20];	// Part 1: 标识文件版本的字符串

		int		m_nodenum;			// Part 2: 节点索引块的文件位置

		int		abstractNodePos ;	// Part 3: 节点数目

		VGFileHeader();

		//读写文件_vgKernel::StreamReaderPtr
		bool	read(vgKernel::StreamReaderPtr pfile);
		void	write(vgKernel::StreamWriterPtr pfile);

		//读写文件_CFile*
		bool	read(CFile*  pfile);
		void	write(CFile* pfile);

		//读写文件_String filename
		bool	read(String filename);
	};

	union	ModType
	{
		unsigned int nType;
		bool		 bType;
	};
	class   VGDEP_EXPORT MODFileHeader 
	{
	public:
		char			strFileFormat[32];	// Part 1: 标识文件格式的字符串

		unsigned int	uiFileVersion;		// Part 2: 标识文件格式的整数

		Vector3			vSceneCenter;		// Part 3: 所有mod模型的总偏移量
		
		unsigned int	uiObjectCount;		// Part 4: mod模型数目
	
		vector<unsigned int>	arrModPosIndex;	// Part 5: mod模型在文件中的索引位置

		vector<ModType>		arrModType;			// Part 6: mod模型的类型数组


		MODFileHeader();

		//读写文件_vgKernel::StreamReaderPtr
		bool	read(vgKernel::StreamReaderPtr pfile);
		void	write(vgKernel::StreamWriterPtr pfile);
	};

}//namespace vgMod

#endif//__VGMVGFILEWRITER_H__

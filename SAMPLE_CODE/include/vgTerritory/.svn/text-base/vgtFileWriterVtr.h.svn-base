


#ifndef __VGTFILEWRITERVTR_H__
#define __VGTFILEWRITERVTR_H__


#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgTerritory/vgtFileDefinitionVtr.h>
#include <vgTerritory/vgtElevationItem.h>
#include <vgKernel/vgkProcessObserver.h>
	
namespace vgTerritory {

	/**
		@date 	2008/11/12  19:10	
		@author  leven
	
		@brief 	
	
		@see    
	*/

	typedef std::vector< int > ptIndexVec;
	typedef std::map< std::string, ptIndexVec* > ptIndexMap;

	class  VGT_EXPORT FileWriterVtr : public vgKernel::ProcessNotifier
	{
	public:
		FileWriterVtr()
		{
			
		}
		~FileWriterVtr()
		{
			
		}

		//bool writeToVtrFromItemNames( 
		//	const StringVectorPtr item_names , 
		//	const String& out_fileabsname );

		/**
			main_vtr_handle的传入是为了得到vtrheader.
			本函数会直接调用writeToVtrFromItems
			注意,传入的new_terrain_name最后都会被转化成为小写.
		*/
		bool writeToVtrFromItems(
			const FileHandleVtr* const main_vtr_handle ,
			const String& terrain_name,
			const ElevationItemVectorPtr pitems , 
			const String& out_filepath );


		bool writeToVtrFromItems( 
			const VtrHeaderPtr input_new_vtrheader,
			const ElevationItemVectorPtr pitems , 
			const String& out_filepath );


		/**
			注意,这里的input_vtrheader不是原始的vtrheader, 是更改后的vtrheader
			另外,这里的out_filepath不是文件名. 
			要保存的文件名 = out_filepath + input_new_vtrheader->name + ".vtr";
		*/
		bool writeToVtrFromItemsWithoutDecomposition( 
			const VtrHeaderPtr input_new_vtrheader,
			const long& next_fileid,
			const ElevationItemVectorPtr pitems , 
			const String& out_filepath );

		ptIndexMap* getPixelIndexMap()
		{
			return &m_pixelIndexMap;
		}

	private:

		bool writeToVtrFromItemsImplement( 
			const ElevationItemVectorPtr &pitems, 
			const String &out_filepath,
			const VtrHeaderPtr input_new_vtrheader );


		bool writeToVgiForVtrFromItems( 
			const String& new_terrain_name , 
			const ElevationItemVectorPtr pitems , 
			const String& out_filepath );


		/**
			add by ZhouZY 2009-1-12  15:21
			用于地形切块保存
			将选定区域之处的点的高程值置为0
		*/
		bool setUnSelectAreaHeightToZERO( 
			char* buf, 
			ElevationItem* elevItem );

		bool setHeightToZEROFromIndexVec( 
			char* buf, 
			ElevationItem* elevItem,
			int bufSize,
			const ptIndexVec* vec );

		void clearPointIndexMap();
		void clearPixelIndexMap();

		ptIndexMap m_pointIndexMap;
		ptIndexMap m_pixelIndexMap;


	};
	
	
}// end of namespace vgTerritory
	


#endif // end of __VGTFILEWRITERVTR_H__
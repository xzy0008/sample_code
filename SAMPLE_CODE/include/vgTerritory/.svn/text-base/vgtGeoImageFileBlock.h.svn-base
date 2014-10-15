



#ifndef __VGTGEOIMAGEFILEBLOCK_H__
#define __VGTGEOIMAGEFILEBLOCK_H__

#include <vgKernel/vgkForward.h>

	
namespace vgTerritory {

	/**
		@date 	2008/09/28  10:41	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class GeoImageFileBlock
	{
	public:
		GeoImageFileBlock( String imgpath , ImageRect rect )
		{
			_imageFilePath = imgpath;
			_imageRect = rect;
		}
		~GeoImageFileBlock()
		{
			
		}

		fileBlock* getFileBlock()
		{
			fileBlock* ret = new fileBlock;
			ret->fileAbsoluteRect = _imageRect;
			ret->fileSrcName = _imageFilePath;
			return ret;
		}

		String getFilePath() const
		{
			return _imageFilePath;
		}

	private:

		String _imageFilePath;

		ImageRect _imageRect;
	
	};


	class GeoImageFileBlockVec : public std::vector<GeoImageFileBlock>
	{
	public:
		GeoImageFileBlockVec()
		{
			
		}
		~GeoImageFileBlockVec()
		{
			
		}

		vgKernel::StringVectorPtr getFileNameList()
		{
			vgKernel::StringVectorPtr ret( new vgKernel::StringVector );

			GeoImageFileBlockVec::iterator iter = begin();
			GeoImageFileBlockVec::iterator iter_end = end();

			for ( ; iter != iter_end ; ++ iter )
			{
				ret->push_back(  (*iter).getFilePath() );
			}

			if ( ret->empty() == true )
			{
				return vgKernel::StringVectorPtr();
			}

			return ret;
		}
	
		fileBlockVectorPtr getFileBlockVecPtr()
		{
			fileBlockVectorPtr ret( new fileBlockVector );

			GeoImageFileBlockVec::iterator iter = begin();
			GeoImageFileBlockVec::iterator iter_end = end();

			for ( ; iter != iter_end ; ++ iter )
			{
				fileBlock* block = (*iter).getFileBlock();
				assert( block != NULL );
				ret->push_back( *block );
				delete block;
			}

			if ( ret->empty() == true )
			{
				return fileBlockVectorPtr();
			}

			return ret;
		}
	};

	typedef vgKernel::SharePtr<GeoImageFileBlockVec> GeoImageFileBlockVecPtr;
	
	
}// end of namespace vgTerritory
	


#endif // end of __VGTGEOIMAGEFILEBLOCK_H__
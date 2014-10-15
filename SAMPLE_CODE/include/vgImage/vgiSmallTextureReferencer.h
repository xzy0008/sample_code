


#ifndef __VGISMALLTEXTUREREFERENCER_H__
#define __VGISMALLTEXTUREREFERENCER_H__
#include <vgImage/vgiDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgImage/vgiDefinition.h>

	
namespace vgImage {


	class TextureItem;
	class TextureObserver;

#define  VGI_LOADFILESIZETHRESHOLD	VGI_CONF_SMALLIMGREF_LOADTHRESHOLD_DEFAULT

	/**
		@date 	2009/04/28  10:00	
		@author  leven
	
		@brief 	对于小型的texture一次性载入即可。
	
		@see    
	*/
	class VGI_EXPORT SmallTextureReferencer
	{
		//typedef std::vector<TextureItem*> TextureItemPtrVector;
		typedef std::vector<TextureObserver*> TextureObserverPtrVector;
	public:
		SmallTextureReferencer();
		~SmallTextureReferencer();

	public:
	
		bool filterSmallTextures( TextureItem* itm );

		// unref并且删除掉所持有的textureitm
		void unRefAllSmallTextures();
	
		

		int getLoadFileSizeThreshold() const
		{
			return _loadFileSizeThreshold;
		}

		void setLoadFileSizeThreshold( int new_threshold )
		{
			assert( new_threshold > 0 );
			_loadFileSizeThreshold = new_threshold;
		}

		const bool getFilterEnable() const { return _filterEnable; }
		bool getFilterEnable() { return _filterEnable; }
		void setFilterEnable( const bool& val ) { _filterEnable = val; }

	private:

		bool checkExist( TextureObserver* itm );

	private:
	
		// 因为载入都是一次性的，所以依次遍历带来的效率损失也不大
		TextureObserverPtrVector _smallTextures;

		// 是否addref的文件大小，以字节计算
		// 可以写入vgConf
		int _loadFileSizeThreshold;
	
		bool _filterEnable;


	};
	
	
}// end of namespace vgImage
	


#endif // end of __VGISMALLTEXTUREREFERENCER_H__
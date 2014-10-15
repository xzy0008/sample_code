



#ifndef __VGITEXTUREITEM_H__
#define __VGITEXTUREITEM_H__

#include <vgImage/vgiDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgImage/vgiTexture.h>


namespace vgImage {

	class Texture;

	/**
		@date 	2008/06/19  19:39	
		@author  leven
	
		@brief 	实际上TextureItem对外是不可见的.
	
		@see    
	*/
	class  VGI_EXPORT TextureItem
	{
		friend class TextureObserver;
	public:

		TextureItem( String texname , ImageMiniature* imgmini );

		~TextureItem();


		TextureObserver* getObserver( const int& lod )
		{
			return _texObservers[ lod ];
		}

		// only for internal use
		Texture* getTexture( const int& lod )
		{
			return _textureLodPyramid[ lod ];
		}

	private:

		void addRef( const int& lod )
		{
			_textureLodPyramid[ lod ]->addReference();
		}

		void releaseRef( const int& lod )
		{
			_textureLodPyramid[ lod ]->releaseReference();
		}

		bool containEmptyTexture()
		{
			for ( int i = VGLOD_N - 1 ; i >=0 ; --i )
			{
				if ( _textureLodPyramid[i]->isEmptyTextrue() == false )
				{
					return false;
				}
			}
			return true;
		}

		void useBind( const int& lod , const bool& useClearestTex )
		{
			if ( useClearestTex == false )
			{
				_textureLodPyramid[ lod ]->useBind();
				return;
			}

			// 在这里,首先从最高清晰度的纹理开始检查

			for ( int i = VGLOD_N - 1 ; i >=0 ; --i )
			{
				if ( _textureLodPyramid[i]->isEmptyTextrue() == false )
				{
					_textureLodPyramid[ i ]->useBind();
					return;
				}
				else
				{
					continue;
				}
			}
			
			// 其他的情况
			return _textureLodPyramid[ lod ]->useBind();
		}
	
		GLuint getTextureID( const int& lod , const bool& useClearestTex )
		{
			if ( useClearestTex == false )
			{
				return _textureLodPyramid[ lod ]->getTextureID();
			}

			// 在这里,首先从最高清晰度的纹理开始检查

			for ( int i = VGLOD_N - 1 ; i >=0 ; --i )
			{
				if ( _textureLodPyramid[i]->isEmptyTextrue() == false )
				{
					return _textureLodPyramid[ i ]->getTextureID();
				}
				else
				{
					continue;
				}
			}

			// 其他的情况
			return _textureLodPyramid[ lod ]->getTextureID();
		}

	private:

		String _textureName;

		TextureObserver* _texObservers[ VGLOD_N ];
	
		Texture* _textureLodPyramid[ VGLOD_N ];
	
	};
	
	
	
	
}// end of namespace vgImage

#endif // end of __VGITEXTUREITEM_H__

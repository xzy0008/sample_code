




#ifndef __VGITEXTURE_H__
#define __VGITEXTURE_H__

#include <vgImage/vgiDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgAsyn/vgaIoRequest.h>


namespace vgImage {


	class ImageMiniature;
	class TextureItem;


	/**
		@date 	2008/06/18  19:10	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGI_EXPORT Texture
	{
		friend class TextureItem;
	public:

		//enum TextureStatus 
		//{
		//	TEXTURE_STATUS_UNLOADED,
		//	TEXTURE_STATUS_LOADED,
		//	TEXTURE_STATUS_ISUPDATING
		//};

	public:

		Texture( String texname , int lod ,
			ImageMiniature* img );

		~Texture();

		inline void useBind()
		{
			glBindTexture( GL_TEXTURE_2D , _textureID );
		}

		inline GLuint getTextureID() const
		{
			return _textureID;
		}

		void addReference();

		void releaseReference();
	
		inline void setTextureID( const GLuint& texid )
		{
			assert( texid != VG_NULL_TEXTURE_ID );
			_textureID = texid;
		}

		inline String getTextureName() const 
		{
			return _texName;
		}
		inline int getLodNumber() const 
		{
			return _lod;
		}

		inline const int getReferenceCounter() const
		{
			return _referenceCounter;
		}

		inline const bool isEmptyTextrue() const
		{
			return _textureID == VG_NULL_TEXTURE_ID;
		}

		// 客户端负责删除
		vgAsyn::IoRequest* getIoRequest();

		ImageMiniature* getImageMiniature()
		{
			assert( _imgMini != NULL );
			return _imgMini;
		}

		bool createTextureByBuffer( char* buffer , long size );

	public:

		void unloadTextureData();

	private:


		String _texName;
	
		int _referenceCounter;

		GLuint _textureID;

		int _lod;

		// 本类不负责释放
		ImageMiniature* _imgMini;
	};
	
	
	
}// end of namespace vgImage

#endif // end of __VGITEXTURE_H__